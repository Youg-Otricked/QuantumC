#!/bin/bash
# update_stdlib.sh - Replace system stdlib with local version

# Check if local stdlib.qc exists
if [ ! -f "./stdlib.qc" ]; then
    echo "Error: ./stdlib.qc not found in current directory"
    exit 1
fi

# Create /usr/share/qc directory if it doesn't exist
sudo mkdir -p /usr/share/qc

# Remove old stdlib if it exists
if [ -f "/usr/share/qc/stdlib.qc" ]; then
    echo "Removing old stdlib..."
    sudo rm /usr/share/qc/stdlib.qc
fi

# Copy new stdlib
echo "Installing new stdlib..."
sudo cp ./stdlib.qc /usr/share/qc/stdlib.qc

# Set permissions
sudo chmod 644 /usr/share/qc/stdlib.qc

echo "stdlib.qc updated successfully!"
echo "Location: /usr/share/qc/stdlib.qc"