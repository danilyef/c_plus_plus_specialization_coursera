import json
import sys

def convert_to_json(input_file, output_file):
    try:
        # Read the input file
        with open(input_file, 'r', encoding='utf-8') as f:
            content = f.read().strip()
        
        # If the file is empty, create an empty JSON object
        if not content:
            data = {}
        else:
            # Try to parse the content as JSON first
            try:
                data = json.loads(content)
            except json.JSONDecodeError:
                # If not valid JSON, create a simple structure
                # Split content into lines and create a dictionary
                lines = content.split('\n')
                data = {
                    "lines": lines,
                    "total_lines": len(lines)
                }
        
        # Write the JSON data to the output file
        with open(output_file, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=4, ensure_ascii=False)
        
        print(f"Successfully converted {input_file} to {output_file}")
        
    except FileNotFoundError:
        print(f"Error: The file {input_file} was not found.")
        sys.exit(1)
    except Exception as e:
        print(f"An error occurred: {str(e)}")
        sys.exit(1)

if __name__ == "__main__":
    input_file = "output.txt"
    output_file = "output.json"
    convert_to_json(input_file, output_file)
