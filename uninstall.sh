#!/bin/bash

GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${RED}================================${NC}"
echo -e "${RED}   QC Compiler Uninstaller${NC}"
echo -e "${RED}================================${NC}"
echo ""

read -p "Are you sure you want to uninstall QC? (y/N): " -n 1 -r
echo
if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo "Uninstall cancelled."
    exit 0
fi

echo ""
echo -e "${BLUE}Removing QC compiler...${NC}"

if [ -f "/usr/bin/qc" ]; then
    sudo rm -f /usr/bin/qc
    echo -e "${GREEN}✓ Removed /usr/bin/qc${NC}"
else
    echo -e "${YELLOW}qc binary not found${NC}"
fi

if [ -d "/usr/share/qc" ]; then
    sudo rm -rf /usr/share/qc
    echo -e "${GREEN}✓ Removed /usr/share/qc${NC}"
else
    echo -e "${YELLOW}stdlib directory not found${NC}"
fi

SHELL_RC=""
if [ -f "$HOME/.bashrc" ]; then
    SHELL_RC="$HOME/.bashrc"
elif [ -f "$HOME/.zshrc" ]; then
    SHELL_RC="$HOME/.zshrc"
fi

if [ -n "$SHELL_RC" ]; then
    if grep -q "# QC Compiler" "$SHELL_RC"; then
        echo -e "${BLUE}Removing QC from $SHELL_RC...${NC}"
        grep -v "# QC Compiler" "$SHELL_RC" | grep -v "QC_STDLIB" > "${SHELL_RC}.tmp"
        mv "${SHELL_RC}.tmp" "$SHELL_RC"
        echo -e "${GREEN}✓ Removed QC configuration${NC}"
    fi
fi

echo ""
echo -e "${GREEN}================================${NC}"
echo -e "${GREEN}   Uninstall Complete!${NC}"
echo -e "${GREEN}================================${NC}"
echo ""
echo -e "${YELLOW}Restart your terminal or run:${NC}"
echo -e "  ${BLUE}source ~/.bashrc${NC}  (bash)"
