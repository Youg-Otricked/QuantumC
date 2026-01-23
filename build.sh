#!/bin/bash
set -e

NAME="qc"
VERSION="0.1.0"
ARCH="amd64"
BUILD_DIR="package"
INSTALL_DIR="$BUILD_DIR/usr/local"
DEBIAN_DIR="$BUILD_DIR/DEBIAN"

rm -rf $BUILD_DIR
mkdir -p $DEBIAN_DIR
mkdir -p $INSTALL_DIR/bin
mkdir -p $INSTALL_DIR/QC

# build
g++ *.cpp -o qc -std=c++23 -fconstexpr-ops-limit=100000000

# copy files
cp qc $INSTALL_DIR/bin/qc
cp stdlib.qc $INSTALL_DIR/QC/stdlib.qc
cp syntax.qc $INSTALL_DIR/QC/syntax.qc

# control
cat > $DEBIAN_DIR/control <<EOL
Package: $NAME
Version: $VERSION
Section: base
Priority: optional
Architecture: $ARCH
Maintainer: Your Name <you@example.com>
Description: QuantumC compiler
 QuantumC is a custom programming language compiler.
EOL

# postinst
cat > $DEBIAN_DIR/postinst <<'EOL'
#!/bin/bash
set -e

RC="$HOME/.bashrc"
if [ -f "$HOME/.zshrc" ]; then
  RC="$HOME/.zshrc"
fi

if ! grep -q "QC_STDLIB" "$RC"; then
  echo "" >> "$RC"
  echo "# QC Compiler" >> "$RC"
  echo "export QC_STDLIB=/usr/local/QC" >> "$RC"
fi
EOL

chmod 755 $DEBIAN_DIR/postinst

dpkg-deb --build $BUILD_DIR
mv $BUILD_DIR.deb qc_${VERSION}_${ARCH}.deb
echo "Built qc_${VERSION}_${ARCH}.deb"
