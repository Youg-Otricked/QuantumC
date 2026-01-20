#!/bin/bash

GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${BLUE}================================${NC}"
echo -e "${BLUE}   QC Compiler Installer${NC}"
echo -e "${BLUE}================================${NC}"
echo ""

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

OS="unknown"
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="linux"
    COMPILER="g++"
    STD_FLAG="-std=c++23"
    EXTRA_FLAGS="-fconstexpr-ops-limit=100000000"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macos"
    COMPILER="clang++"
    STD_FLAG="-std=c++20"
    EXTRA_FLAGS=""
else
    echo -e "${RED}Unsupported OS: $OSTYPE${NC}"
    echo "Please use Windows Subsystem for Linux (WSL) or compile manually"
    exit 1
fi

echo -e "${GREEN}Detected OS: $OS${NC}"
echo ""

if [ -f "/usr/local/bin/qc" ]; then
    echo -e "${YELLOW}QC is already installed. Reinstalling...${NC}"
    sudo rm -f /usr/local/bin/qc
fi

if [ -d "/usr/local/QC" ]; then
    echo -e "${YELLOW}Removing old stdlib...${NC}"
    sudo rm -rf /usr/local/QC
fi

echo -e "${BLUE}Compiling QC compiler...${NC}"
cd "$SCRIPT_DIR"

if [ ! -f "Ct4.cpp" ]; then
    echo -e "${RED}Error: Ct4.cpp not found!${NC}"
    exit 1
fi

$COMPILER *.cpp -o qc $STD_FLAG $EXTRA_FLAGS

if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed!${NC}"
    exit 1
fi

echo -e "${GREEN}Compilation successful${NC}"
echo ""

echo -e "${BLUE}Installing standard library...${NC}"
sudo mkdir -p /usr/local/QC

if [ -f "$SCRIPT_DIR/stdlib.qc" ]; then
    sudo cp "$SCRIPT_DIR/stdlib.qc" /usr/local/QC/stdlib.qc
    sudo cp "$SCRIPT_DIR/syntax.qc" /usr/local/QC/syntax.qc
    echo -e "${GREEN}stdlib.qc installed to /usr/local/QC/${NC}"
else
    echo -e "${YELLOW}Warning: stdlib.qc not found (will be created later)${NC}"
    sudo touch /usr/local/QC/stdlib.qc
fi

echo -e "${BLUE}Installing qc compiler...${NC}"
sudo cp "$SCRIPT_DIR/qc" /usr/local/bin/qc
sudo chmod +x /usr/local/bin/qc
echo -e "${GREEN}qc installed to /usr/local/bin/${NC}"
echo ""

SHELL_RC=""
if [ -f "$HOME/.bashrc" ]; then
    SHELL_RC="$HOME/.bashrc"
elif [ -f "$HOME/.zshrc" ]; then
    SHELL_RC="$HOME/.zshrc"
fi

if [ -n "$SHELL_RC" ]; then
    if grep -q "# QC Compiler" "$SHELL_RC"; then
        echo -e "${YELLOW}Removing old QC configuration...${NC}"
        grep -v "# QC Compiler" "$SHELL_RC" | grep -v "QC_STDLIB" > "${SHELL_RC}.tmp"
        mv "${SHELL_RC}.tmp" "$SHELL_RC"
    fi
    
    echo "" >> "$SHELL_RC"
    echo "# QC Compiler" >> "$SHELL_RC"
    echo "export QC_STDLIB=\"/usr/local/QC\"" >> "$SHELL_RC"
    
    echo -e "${GREEN}Added QC_STDLIB to $SHELL_RC${NC}"
fi

export PATH="/usr/local/bin:$PATH"
export QC_STDLIB="/usr/local/QC"

echo ""
echo -e "${GREEN}================================${NC}"
echo -e "${GREEN}   Installation Complete!${NC}"
echo -e "${GREEN}================================${NC}"
echo ""
echo -e "Compiler: ${BLUE}/usr/local/bin/qc${NC}"
echo -e "Stdlib:   ${BLUE}/usr/local/QC/stdlib.qc${NC}"
echo ""
echo -e "${YELLOW}Run one of the following to reload your shell:${NC}"
echo -e "  ${BLUE}source ~/.bashrc${NC}  (bash)"
echo -e "  ${BLUE}source ~/.zshrc${NC}   (zsh)"
echo -e "  ${BLUE}Or restart your terminal${NC}"
echo ""
echo -e "Then test with: ${BLUE}qc --version${NC}"
echo ""