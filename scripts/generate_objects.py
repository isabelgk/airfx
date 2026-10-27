#!/usr/bin/env python3
"""Generate per-plugin Max external source from airwindohhs plugin metadata.

Sources plugin *identity* (namespace/class name/header path/category) by
importing airwindohhs's own scripts/gen_meta.py from the pinned checkout --
the exact same logic that builds its registry.hpp -- rather than re-deriving
it independently. Sources per-parameter *runtime* metadata (names/titles/
labels/defaults, description text) from airwindohhs's compiled dump_meta
tool, since those values only exist once a plugin is actually instantiated.

For each plugin this writes/rewrites:
  - source/objects/<category>/airfx.<slug>_tilde/airfx.<slug>_tilde.cpp
  - source/objects/<category>/airfx.<slug>_tilde/CMakeLists.txt
  - docs/airfx.<slug>~.maxref.xml (a baseline stub -- refine by hand)

And always fully rewrites (regardless of --only/--force) two generated
manifests covering every plugin currently in the metadata:
  - objects.cmake (one add_subdirectory() per object, included from the root
    CMakeLists.txt)
  - init/objectmappings.txt (mc.<name> -> mc.wrapper~ aliases)

An existing object whose category changed upstream is moved to the new
category directory first, with its #include line and maxref category patched
in place so hand edits survive.

By default only generates objects that don't already have a .cpp file (so
re-running after a fresh upstream plugin lands only adds what's new). Pass
--force to regenerate every object's .cpp/CMakeLists.txt (e.g. after a base
header change), or --only <slug> [<slug> ...] to target specific plugins.
"""

import argparse
import json
import subprocess
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
SOURCE_OBJECTS_DIR = REPO_ROOT / "source" / "objects"
DOCS_DIR = REPO_ROOT / "docs"
OBJECTS_CMAKE = REPO_ROOT / "objects.cmake"
OBJECTMAPPINGS = REPO_ROOT / "init" / "objectmappings.txt"


def load_identity(airwindohhs_src):
    """namespace/class_name/category/rel_include per plugin, via airwindohhs's own gen_meta.py."""
    sys.path.insert(0, str(airwindohhs_src / "scripts"))
    import gen_meta

    return {p.slug: p for p in gen_meta.collect_plugins()}


def build_dump_meta(build_dir):
    binary = build_dir / "_deps" / "airwindohhs-build" / "dump_meta"
    if not binary.exists():
        subprocess.run(
            ["cmake", "--build", str(build_dir), "--target", "dump_meta"],
            check=True,
            cwd=REPO_ROOT,
        )
    return binary


def load_params(binary):
    result = subprocess.run([str(binary)], capture_output=True, text=True, check=True)
    return {p["slug"]: p for p in json.loads(result.stdout)}


CPP_TEMPLATE = """#include "ext.h"

#include "airfx.hpp"
#include "{rel_include}"

using TWrapped = airwindohhs::{namespace_}::{class_name}<double>;

extern "C" void ext_main(void *r)
{{
    airfx::init_class<TWrapped>("airfx.{slug}~", airwindohhs::{namespace_}::k_long_description.data());
}}
"""

CMAKE_TEMPLATE = """set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.{slug}_tilde) # output bundle: airfx.{slug}~.mxo (_tilde->~)

target_sources(airfx.{slug}_tilde
    PRIVATE
        airfx.{slug}_tilde.cpp)

target_include_directories(airfx.{slug}_tilde
    PRIVATE
        ${{CMAKE_CURRENT_SOURCE_DIR}}/../../../airfx)

target_link_libraries(airfx.{slug}_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
"""


def xml_escape(s):
    return (
        s.replace("&", "&amp;")
        .replace("<", "&lt;")
        .replace(">", "&gt;")
    )


def attr_names(parameters):
    """Matches source/airfx/airfx.hpp's init_attr_names: a repeated parameter
    name gets its occurrence number appended ("attack", "attack2")."""
    names = []
    for i, p in enumerate(parameters):
        occurrence = 1 + sum(q["name"] == p["name"] for q in parameters[:i])
        names.append(p["name"] if occurrence == 1 else f"{p['name']}{occurrence}")
    return names


MAXREF_TEMPLATE = """<?xml version="1.0" encoding="utf-8" standalone="yes"?>
<?xml-stylesheet href="./c74ref.xsl" type="text/xsl"?>

<c74object name="airfx.{slug}~" module="MSP" category="{category}">

\t<digest>
\t\t{short_description}
\t</digest>

\t<description>
\t\t{short_description}
\t</description>

\t<discussion>
\t\t{long_description}
\t</discussion>

\t<metadatalist>
\t\t<metadata name="author">Isabel Kaspriskie</metadata>
\t\t<metadata name="tag">Airwindows</metadata>
\t\t<metadata name="tag">{category}</metadata>
\t</metadatalist>

\t<inletlist>
\t\t<inlet id="0" type="signal">
\t\t\t<digest>(signal) Input L</digest>
\t\t</inlet>
\t\t<inlet id="1" type="signal">
\t\t\t<digest>(signal) Input R</digest>
\t\t</inlet>
\t</inletlist>

\t<outletlist>
\t\t<outlet id="0" type="signal">
\t\t\t<digest>(signal) Output L</digest>
\t\t</outlet>
\t\t<outlet id="1" type="signal">
\t\t\t<digest>(signal) Output R</digest>
\t\t</outlet>
\t\t<outlet id="2" type="anything">
\t\t\t<digest>Dump outlet</digest>
\t\t</outlet>
\t</outletlist>

\t<methodlist>
\t\t<method name="about">
\t\t\t<digest>Get the original Airwindows "about" text for this object</digest>
\t\t\t<description>
\t\t\t\tPrints the original Airwindows description for this plugin out the
\t\t\t\tdump outlet.
\t\t\t</description>
\t\t</method>
\t</methodlist>

\t<attributelist>
{attributes}\t</attributelist>

</c74object>
"""

ATTRIBUTE_TEMPLATE = """\t\t<attribute name="{name}" get="1" set="1" type="float64" size="1">
\t\t\t<digest>{title}</digest>
\t\t\t<description>
\t\t\t\tRange 0.0-1.0. Default {default}.
\t\t\t</description>
\t\t</attribute>
"""


def render_maxref(entry, params):
    attributes = "".join(
        ATTRIBUTE_TEMPLATE.format(
            name=xml_escape(name),
            title=xml_escape(p["title"]),
            default=p["default"],
        )
        for name, p in zip(attr_names(params["parameters"]), params["parameters"])
    )
    return MAXREF_TEMPLATE.format(
        slug=entry.slug,
        category=entry.category,
        short_description=xml_escape(params["short_description"]),
        long_description=xml_escape(params["long_description"]),
        attributes=attributes,
    )


def find_existing_objects():
    """slug -> object directory for every generated object, whatever category it sits in."""
    return {
        d.name.removeprefix("airfx.").removesuffix("_tilde"): d
        for d in SOURCE_OBJECTS_DIR.glob("*/airfx.*_tilde")
        if (d / f"{d.name}.cpp").exists()
    }


def relocate_object(entry, obj_dir):
    old_category = obj_dir.parent.name
    new_dir = SOURCE_OBJECTS_DIR / entry.category / obj_dir.name
    new_dir.parent.mkdir(parents=True, exist_ok=True)
    obj_dir.rename(new_dir)
    if not any(obj_dir.parent.iterdir()):
        obj_dir.parent.rmdir()

    cpp_path = new_dir / f"{new_dir.name}.cpp"
    cpp_path.write_text(
        cpp_path.read_text().replace(f'#include "{old_category}/', f'#include "{entry.category}/', 1)
    )

    maxref_path = DOCS_DIR / f"airfx.{entry.slug}~.maxref.xml"
    if maxref_path.exists():
        text = maxref_path.read_text()
        text = text.replace(f'category="{old_category}"', f'category="{entry.category}"', 1)
        text = text.replace(f'<metadata name="tag">{old_category}</metadata>',
                            f'<metadata name="tag">{entry.category}</metadata>', 1)
        maxref_path.write_text(text)
    return old_category


def write_object(entry, params, force):
    obj_dir = SOURCE_OBJECTS_DIR / entry.category / f"airfx.{entry.slug}_tilde"
    cpp_path = obj_dir / f"airfx.{entry.slug}_tilde.cpp"
    cmake_path = obj_dir / "CMakeLists.txt"

    if cpp_path.exists() and not force:
        return False

    obj_dir.mkdir(parents=True, exist_ok=True)
    cpp_path.write_text(
        CPP_TEMPLATE.format(
            rel_include=entry.rel_include,
            namespace_=entry.namespace,
            class_name=entry.class_name,
            slug=entry.slug,
        )
    )
    cmake_path.write_text(CMAKE_TEMPLATE.format(slug=entry.slug))

    DOCS_DIR.mkdir(parents=True, exist_ok=True)
    maxref_path = DOCS_DIR / f"airfx.{entry.slug}~.maxref.xml"
    maxref_path.write_text(render_maxref(entry, params))
    return True


def rewrite_manifests(identities):
    # Reflects objects actually generated on disk, not everything available
    # upstream -- --only a subset (or a partial bulk regen) must not reference
    # add_subdirectory()s for plugins that don't have a .cpp yet. Paths come
    # from disk rather than the upstream category, so an object whose category
    # drifted fails the build loudly instead of silently vanishing.
    existing = find_existing_objects()
    plugins = sorted(
        (d.parent.name, slug) for slug, d in existing.items() if slug in identities
    )

    lines = [
        "# Generated by scripts/generate_objects.py -- do not edit by hand.",
        "# Regenerate with: python3 scripts/generate_objects.py",
    ]
    for category, slug in plugins:
        lines.append(f"add_subdirectory(source/objects/{category}/airfx.{slug}_tilde)")
    OBJECTS_CMAKE.write_text("\n".join(lines) + "\n")

    OBJECTMAPPINGS.parent.mkdir(parents=True, exist_ok=True)
    mapping_lines = [
        f"max objectfile mc.airfx.{slug}~ mc.wrapper~ airfx.{slug}~ multichannel;" for _, slug in plugins
    ]
    OBJECTMAPPINGS.write_text("\n".join(mapping_lines) + "\n")
    return len(plugins)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--build-dir", default=REPO_ROOT / "build", type=Path, help="CMake build directory (default: build)")
    parser.add_argument("--only", nargs="+", metavar="SLUG", help="only generate these plugins (still refreshes manifests for all)")
    parser.add_argument("--force", action="store_true", help="regenerate .cpp/CMakeLists.txt even if already present")
    args = parser.parse_args()

    build_dir = args.build_dir
    airwindohhs_src = build_dir / "_deps" / "airwindohhs-src"
    if not airwindohhs_src.is_dir():
        raise SystemExit(f"airwindohhs source not found at {airwindohhs_src} -- run `cmake -S . -B {build_dir}` first")

    identities = load_identity(airwindohhs_src)
    dump_meta_bin = build_dump_meta(build_dir)
    params_by_slug = load_params(dump_meta_bin)

    missing_params = set(identities) - set(params_by_slug)
    missing_identity = set(params_by_slug) - set(identities)
    if missing_params:
        print(f"warning: {len(missing_params)} plugin(s) have identity but no dump_meta params, skipping: "
              f"{sorted(missing_params)}", file=sys.stderr)
    if missing_identity:
        print(f"warning: {len(missing_identity)} plugin(s) have dump_meta params but no parsable identity, skipping: "
              f"{sorted(missing_identity)}", file=sys.stderr)

    usable_slugs = set(identities) & set(params_by_slug)
    identities = {slug: entry for slug, entry in identities.items() if slug in usable_slugs}

    targets = set(args.only) if args.only else set(identities)
    unknown = targets - set(identities)
    if unknown:
        raise SystemExit(f"unknown slug(s): {sorted(unknown)}")

    for slug, obj_dir in sorted(find_existing_objects().items()):
        entry = identities.get(slug)
        if entry and obj_dir.parent.name != entry.category:
            old_category = relocate_object(entry, obj_dir)
            print(f"moved airfx.{slug}~ from {old_category} to {entry.category}")

    written = 0
    for slug in sorted(targets):
        if write_object(identities[slug], params_by_slug[slug], args.force):
            written += 1

    total = rewrite_manifests(identities)
    print(f"wrote {written} object(s) ({len(targets) - written} already present, skipped); "
          f"refreshed objects.cmake and init/objectmappings.txt for {total} plugin(s) total")


if __name__ == "__main__":
    main()
