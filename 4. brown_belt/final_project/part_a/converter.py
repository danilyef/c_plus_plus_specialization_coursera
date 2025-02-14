import os

def concatenate_files():
    """Concatenates specified .h and .cpp files into a single main.cpp file in a defined order, ensuring #includes appear at the beginning and excluding #pragma once."""
    file_order = [
        "types.h", "utils.h", "database.h", "request.h",
        "types.cpp", "utils.cpp", "database.cpp", "request.cpp", "main.cpp"
    ]
    
    includes = []
    others = []
    
    for filename in file_order:
        if os.path.exists(filename):
            with open(filename, "r", encoding="utf-8", errors="ignore") as infile:
                content = infile.readlines()
                for line in content:
                    if line.strip().startswith("#include"):
                        if ".h" not in line:
                            includes.append(line)
                    elif not line.strip().startswith("#pragma once"):
                        others.append(line)
    
    with open("main_file.cpp", "w", encoding="utf-8") as outfile:
        outfile.writelines(sorted(set(includes)))  # Ensure unique includes sorted at the top
        outfile.write("\nusing namespace std;\n\n")  # Add using namespace std after includes
        outfile.writelines(others)
    
    print("main.cpp has been created with files in the specified order and #includes at the beginning.")

if __name__ == "__main__":
    concatenate_files()
