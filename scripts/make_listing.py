import os
import re
from pathlib import Path


def get_names_from_source_dirs(source_dirs: Path) -> list:
    reformatted_directories = []
    pattern = re.compile(r"^ar\.(.*)_tilde$")

    # Walk through the root directory
    for entry in os.listdir(source_dirs):
        entry_path = os.path.join(source_dirs, entry)
        if os.path.isdir(entry_path):
            match = pattern.match(entry)
            if match:
                # Extract the desired part of the directory name
                reformatted_name = match.group(1)
                reformatted_directories.append(reformatted_name)

    # Sort the list of reformatted directory names
    reformatted_directories.sort()
    return reformatted_directories


def write(directories: list):
    with open("objects_list.txt", "w") as f:
        for directory in directories:
            f.write(f"{directory}\n")


if __name__ == "__main__":
    script_directory = Path(os.path.dirname(os.path.abspath(__file__)))
    root = Path(os.path.dirname(script_directory))
    print(f"Running from root directory `{root}`...")

    p = Path(os.path.join(root, "source", "projects"))
    write(get_names_from_source_dirs(p))
