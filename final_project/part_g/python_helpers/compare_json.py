import json
import math

def load_json_file(file_path):
    with open(file_path, 'r') as f:
        return json.load(f)

def compare_values(value1, value2):
    if isinstance(value1, (int, float)) and isinstance(value2, (int, float)):
        return abs(value1 - value2) > 0.000001
    return value1 != value2

def compare_total_time(item1, item2):
    """
    Compares the 'total_time' key between two items.
    Returns True if there's a significant difference, False otherwise.
    """
    if 'total_time' not in item1 or 'total_time' not in item2:
        return False
    
    time1 = item1['total_time']
    time2 = item2['total_time']
    
    # Compare with a small epsilon to account for floating point precision
    return abs(time1 - time2) > 0.000001


def find_differences(dict1, dict2):
    differences = []
    for key in set(dict1.keys()) | set(dict2.keys()):
        if key not in dict1:
            differences.append(f"Missing in first file: {key}")
            continue
        if key not in dict2:
            differences.append(f"Missing in second file: {key}")
            continue
        
        if isinstance(dict1[key], dict) and isinstance(dict2[key], dict):
            nested_diffs = find_differences(dict1[key], dict2[key])
            if nested_diffs:
                differences.extend([f"{key}.{diff}" for diff in nested_diffs])
        elif isinstance(dict1[key], list) and isinstance(dict2[key], list):
            if len(dict1[key]) != len(dict2[key]):
                differences.append(f"Different lengths for {key}: {len(dict1[key])} vs {len(dict2[key])}")
            else:
                for i, (item1, item2) in enumerate(zip(dict1[key], dict2[key])):
                    if isinstance(item1, dict) and isinstance(item2, dict):
                        nested_diffs = find_differences(item1, item2)
                        if nested_diffs:
                            differences.extend([f"{key}[{i}].{diff}" for diff in nested_diffs])
                    elif compare_values(item1, item2):
                        differences.append(f"{key}[{i}]: {item1} vs {item2}")
        elif compare_values(dict1[key], dict2[key]):
            differences.append(f"{key}: {dict1[key]} vs {dict2[key]}")
    
    return differences

def main():
    # Load both JSON files
    output = load_json_file('output.json')
    output_correct = load_json_file('output_correct.json')
    
    # Create a mapping by request_id
    output_map = {item['request_id']: item for item in output}
    output_correct_map = {item['request_id']: item for item in output_correct}
    
    # Find differences
    differences = []
    for request_id in set(output_map.keys()) | set(output_correct_map.keys()):
        if request_id not in output_map:
            differences.append(f"request_id: {request_id}\nMissing in output.json")
            continue
        if request_id not in output_correct_map:
            differences.append(f"request_id: {request_id}\nMissing in output_correct.json")
            continue
        
        #total_time_diff = compare_total_time(output_map[request_id], output_correct_map[request_id])
        #if total_time_diff:
  
        item_diffs = find_differences(output_map[request_id], output_correct_map[request_id])
        if item_diffs:
            differences.append(f"request_id: {request_id}")
            differences.extend(item_diffs)
            differences.append("")  # Empty line for readability
    
    # Write differences to file
    with open('differences.txt', 'w') as f:
        f.write('\n'.join(differences))

if __name__ == "__main__":
    main() 