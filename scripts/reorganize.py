import os


def get_missing_object_names():
    headers_root = "/path/to/airfx/source/airwindohhs/include"
    objects_root = "/path/to/airfx/source/objects"

    missing = set()
    for subdir in os.listdir(headers_root):
        subdir_path = os.path.join(headers_root, subdir)

        if os.path.isdir(subdir_path):
            # Iterate through the header files in the subdirectory
            for header in os.listdir(subdir_path):
                if header.endswith(".hpp"):
                    # Extract the base name of the header (without .hpp extension)
                    base_name = os.path.splitext(header)[0]

                    # Construct the corresponding directory name
                    corresponding_dir = f"ar.{base_name}_tilde"
                    source_dir = os.path.join(objects_root, subdir, corresponding_dir)

                    # if it doesn't exist in the source dir, add to list
                    if not os.path.exists(source_dir):
                        missing.add(f"{subdir}/{base_name}")

    return missing


if __name__ == "__main__":
    names = get_missing_object_names()
    ordered = sorted(list(names))
    with open("missing.txt", "w") as f:
        for name in ordered:
            f.write(name + "\n")
