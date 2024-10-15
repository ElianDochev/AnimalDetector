# Used to extract the files from the UnsortedData(dowloaded from edge impulse) directory and organize them based on their labels.
import os
import json
import shutil

# Define paths
labels_file = './UnsortedData/info.labels'
base_dir = './UnsortedData'
output_dir = './Data'

# Create output directory if it doesn't exist
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

# Function to ensure directory for label exists
def ensure_label_dir(label):
    label_dir = os.path.join(output_dir, label)
    if not os.path.exists(label_dir):
        os.makedirs(label_dir)
    return label_dir

# Load the entire content as a JSON object
with open(labels_file, 'r') as f:
    labels_data = json.loads(f.read())  # Read and parse the entire JSON file

# Assuming the relevant data is inside a 'files' property which is a list of objects
for entry in labels_data['files']:
    # Extract the file path and label
    file_path = entry['path']
    label = entry['label']['label']  # Extract the label from the object
    
    # Ensure the label directory exists
    label_dir = ensure_label_dir(label)
    
    # Construct the full path to the source file
    full_file_path = os.path.join(base_dir, file_path)
    
    # Move the file to the appropriate label directory
    if os.path.exists(full_file_path):
        shutil.move(full_file_path, os.path.join(label_dir, os.path.basename(full_file_path)))
    else:
        print(f"File {full_file_path} not found!")

print("Files have been organized based on their labels.")