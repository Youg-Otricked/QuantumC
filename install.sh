#!/bin/bash

GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'
# export PATH="$HOME/.qc/bin:$PATH"
echo -e "${BLUE}================================${NC}"
echo -e "${BLUE}   QC Compiler Installer${NC}"
echo -e "${BLUE}================================${NC}"
echo ""
QC_HOME="$HOME/.qc"
QC_BIN="$QC_HOME/bin"
QC_LIB="$QC_HOME/lib"
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

OS="unknown"
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macos"
else
    echo -e "${RED}Unsupported OS: $OSTYPE${NC}"
    echo "Please use Windows Subsystem for Linux (WSL) or compile manually"
    exit 1
fi
install_deps() {
    echo "Installing dependancys (may need SUDO)"
    if [[ "$OS" == "linux" ]]; then
        if command -v apt &> /dev/null; then
            sudo apt install -y llvm-21 cmake
        elif command -v pacman &> /dev/null; then
            sudo pacman -S --noconfirm llvm cmake
        elif command -v dnf &> /dev/null; then
            sudo dnf install -y llvm-devel cmake
        else
            echo -e "${RED}Unknown package manager, install deps manually${NC}"
            exit 1
        fi
    elif [[ "$OS" == "macos" ]]; then
        brew install llvm@21 cmake
        echo -e "${YELLOW}Set LLVM_DIR manually, see README${NC}"
    fi
}
LLVM_CONFIG=$(command -v llvm-config || command -v llvm-config-21)

if [[ -z "$LLVM_CONFIG" ]]; then
    install_deps
    LLVM_CONFIG=$(command -v llvm-config || command -v llvm-config-21)
fi
LLVM_VER=$($LLVM_CONFIG --version | cut -d. -f1)
if [ "$LLVM_VER" -lt 21 ]; then
    echo -e "${RED}LLVM 21+ required, found $LLVM_VER${NC}"
    exit 1
fi
echo -e "${GREEN}Detected OS: $OS${NC}"
echo ""

if [ -f "$HOME/.qc/bin/qc" ]; then
    echo -e "${YELLOW}QC version $(qc -sv) is already installed. Reinstalling...${NC}"
    rm -f ~/.qc/bin/qc
fi

if [ -d "$QC_LIB" ]; then
    echo -e "${YELLOW}Removing old stdlib...${NC}"
    rm -rf "$QC_LIB"
fi

echo -e "${BLUE}Compiling QC compiler...${NC}"
cd "$SCRIPT_DIR"

if [ ! -f "compiler.cpp" ]; then
    echo -e "${RED}Error: compiler.cpp not found!${NC}"
    exit 1
fi
rm -rf CMakeCache.txt CMakeFiles
cmake .
cmake --build . -j$(nproc 2>/dev/null || sysctl -n hw.logicalcpu 2>/dev/null || echo 4) 2>build.log

if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed!${NC}"
    exit 1
fi

echo -e "${GREEN}Compilation successful${NC}"
echo ""

echo -e "${BLUE}Installing standard library...${NC}"
mkdir -p ~/.qc/bin
mkdir -p ~/.qc/lib
if [ -f "$SCRIPT_DIR/stdlib.qc" ]; then
    cp "$SCRIPT_DIR/stdlib.qc" $QC_LIB
    cp "$SCRIPT_DIR/syntax.qc" $QC_LIB
    echo -e "${GREEN}stdlib.qc installed to $QC_LIB${NC}"
else
    echo -e "${YELLOW}Warning: stdlib.qc not found (will be created later)${NC}"
    touch $QC_LIB/stdlib.qc
fi

echo -e "${BLUE}Installing qc compiler...${NC}"
cp "$SCRIPT_DIR/qc" ~/.qc/bin/qc
chmod +x ~/.qc/bin/qc
echo -e "${GREEN}qc installed to ~/.qc/bin/${NC}"
echo ""

SHELL_RC=""
case "$SHELL" in
    */bash)  SHELL_RC="$HOME/.bashrc" ;;
    */zsh)   SHELL_RC="$HOME/.zshrc" ;;
    */fish)  SHELL_RC="$HOME/.config/fish/config.fish" ;;
    */ksh)   SHELL_RC="$HOME/.kshrc" ;;
    */dash)  SHELL_RC="$HOME/.profile" ;;
    *)       SHELL_RC="$HOME/.profile" ;;
esac
if [ -n "$SHELL_RC" ]; then
    if grep -q "# QC Compiler" "$SHELL_RC"; then
        echo -e "${YELLOW}Removing old QC configuration...${NC}"
        grep -v "# QC Compiler\|QC_STDLIB\|QC_INTERP_TEST\|\.qc/bin" "$SHELL_RC" > "${SHELL_RC}.tmp"
        mv "${SHELL_RC}.tmp" "$SHELL_RC"
    fi
    if [[ "$SHELL" == */fish ]]; then
        echo "WHY FISH? THIS IS A SPECIAL CASE BECUASE ITS SO WEIRD"
        echo "" >> "$SHELL_RC"
        echo "# QC Compiler" >> "$SHELL_RC"
        echo "set -x QC_STDLIB \"$QC_LIB/stdlib.qc\"" >> "$SHELL_RC"
        echo "set -x QC_INTERP_TEST \"$QC_LIB/syntax.qc\"" >> "$SHELL_RC"
        echo "fish_add_path \"$HOME/.qc/bin\"" >> "$SHELL_RC"
        echo -e "${GREEN}Added QC_STDLIB to $SHELL_RC${NC}"
    else
        echo "" >> "$SHELL_RC"
        echo "# QC Compiler" >> "$SHELL_RC"
        echo "export QC_STDLIB=\"$QC_LIB/stdlib.qc\"" >> "$SHELL_RC"
        echo "export QC_INTERP_TEST=\"$QC_LIB/syntax.qc\"" >> "$SHELL_RC"
        echo "export PATH=\"\$HOME/.qc/bin:\$PATH\"" >> "$SHELL_RC"
        echo -e "${GREEN}Added QC_STDLIB to $SHELL_RC${NC}"
    fi
fi

export PATH="$HOME/.qc/bin:$PATH"

echo ""
echo -e "${GREEN}================================${NC}"
echo -e "${GREEN}   Installation Complete!${NC}"
echo -e "${GREEN}================================${NC}"
echo ""
echo -e "Compiler: ${BLUE}~/.qc/bin/qc${NC}"
echo -e "Stdlib:   ${BLUE}$QC_LIB${NC}"
echo ""
echo -e "${YELLOW}Run one of the following to reload your shell:${NC}"
echo -e "  ${BLUE}source ~/.bashrc${NC}  (bash)"
echo -e "${BLUE}source ~/.zshrc${NC}   (zsh)"
echo -e "${BLUE}Or restart your terminal${NC}"
echo ""
echo -e "Then test with: ${BLUE}qc --version${NC}"
echo ""
