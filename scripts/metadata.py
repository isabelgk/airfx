import json
import xmltodict
import os
from pathlib import Path

objects = dict()
base_path = Path("C:/Users/Isabel Kaspriskie/Documents/Max 8/Packages/airfx/")


def get_tags(name):
    doc_file = Path(os.path.join(base_path, "docs/" + name + ".maxref.xml"))
    xml_dict = None
    with open(doc_file) as f:
        xml_dict = xmltodict.parse(f.read())

    tags = []
    for m_list in xml_dict["c74object"]["metadatalist"]["metadata"]:
        try:
            if str(m_list["@name"]) == "tag":
                tags.append(str(m_list["#text"]))
        except TypeError:
            pass

    return tags


def get_description(name):
    doc_file = Path(os.path.join(base_path, "docs/" + name + ".maxref.xml"))
    xml_dict = None
    with open(doc_file) as f:
        xml_dict = xmltodict.parse(f.read())

    return xml_dict["c74object"]["digest"]


def get_url(name):
    help_file = Path(os.path.join(base_path, "help/" + name + ".maxhelp"))
    lines = None
    with open(help_file) as f:
        lines = f.readlines()

    for line in lines:
        if "\"url\"" in line:
            return line.split("\"url\" :")[1].strip()

    return None


def get_names():
    doc_names = os.listdir(os.path.join(base_path, "docs"))
    names = []
    for n in doc_names:
        names.append(n.split(".maxref.xml")[0])
    return names


def main():
    names = get_names()
    for n in names:
        objects[n] = dict()
        objects[n]["tags"] = get_tags(n)
        objects[n]["digest"] = get_description(n)
        objects[n]["url"] = get_url(n)

    with open(Path(os.path.join(base_path, "misc/objects-dump.json")), 'a') as f:
        json.dump(objects, f)


if __name__ == "__main__":
    main()
