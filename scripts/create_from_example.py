import os
import shutil
from pathlib import Path


def relative_path(*args) -> Path:
    project_root = Path(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    return Path(os.path.join(project_root, *args))


def create_new(category, name):
    new_lines = []
    output_name = f"airfx.{name.lower()}_tilde"
    with open(relative_path("scripts", "example.cpp"), "r") as f:
        lines = f.readlines()
        for line in lines:
            new_line = line.replace("Example", name)
            new_line = new_line.replace("example", name.lower())
            new_line = new_line.replace("category", category)
            new_lines.append(new_line)
    new_dir = relative_path("source", "objects", category, output_name)
    if not os.path.isdir(new_dir):
        os.mkdir(new_dir)
    with open(relative_path("source", "objects", category, output_name, f"{output_name}.cpp"), "w") as f:
        f.writelines(new_lines)
    shutil.copy(relative_path("scripts", "example.CMakeLists.txt"), os.path.join(new_dir, "CMakeLists.txt"))
    with open(relative_path("CMakeLists.txt"), "a") as f:
        f.write(f"add_airfx_object({category} {output_name})\n")


def main():
    d = {
        "ambience": [
            "BrightAmbience2",
            "BrightAmbience3",
            "ChorusEnsemble",
            "ClearCoat",
            "Doublelay",
            "Ensemble",
            "Hombre",
            "kChamberAR",
            "Melt",
            "Mv",
            "Mv2",
            "PitchDelay",
            "PurestEcho",
            "SampleDelay",
            "StarChild",
            "StarChild2",
            "StereoChorus",
            "StereoDoubler",
            "StereoEnsemble",
            "TapeDelay",
            "TapeDelay2",
            "TripleSpread",
        ],
        "amp-sims": [
            "BassAmp",
            "BassDrive",
            "BigAmp",
            "Cabs",
            "CrickBass",
            "FireAmp",
            "GrindAmp",
            "LeadAmp",
            "LilAmp",
            "MidAmp",
        ]
    }
    for category, names in d.items():
        for name in names:
            try:
                create_new(category, name)
            except Exception as e:
                print(e)


if __name__ == "__main__":
    main()
