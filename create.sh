#!/bin/bash
set -e

PACKAGE="qc"
VERSION="0.1.0"
MAINTAINER_NAME="Your Name"
MAINTAINER_EMAIL="you@example.com"
DESCRIPTION="Quantum C compiler"
SHORT_DESC="QuantumC compiler"

# Create project structure
mkdir -p "${PACKAGE}/debian"
cd "${PACKAGE}"

# Create debian/control
cat > debian/control <<EOF
Source: ${PACKAGE}
Section: utils
Priority: optional
Maintainer: ${MAINTAINER_NAME} <${MAINTAINER_EMAIL}>
Standards-Version: 4.6.0
Build-Depends: debhelper (>= 12), g++, make

Package: ${PACKAGE}
Architecture: any
Depends: \${shlibs:Depends}, \${misc:Depends}
Description: ${SHORT_DESC}
 ${DESCRIPTION}
EOF

# Create debian/compat
echo "12" > debian/compat

# Create debian/rules
cat > debian/rules <<'EOF'
#!/usr/bin/make -f
%:
	dh $@

override_dh_auto_build:
	g++ *.cpp -o qc -std=c++23 -fconstexpr-ops-limit=100000000 -Iinclude

override_dh_auto_install:
	install -d $(DESTDIR)/usr/local/bin
	install -m 755 qc $(DESTDIR)/usr/local/bin/qc
	install -d $(DESTDIR)/usr/local/QC
	install -m 644 stdlib.qc $(DESTDIR)/usr/local/QC/stdlib.qc
	install -m 644 syntax.qc $(DESTDIR)/usr/local/QC/syntax.qc
EOF

chmod +x debian/rules

# Create debian/changelog
dch --create --package ${PACKAGE} --newversion ${VERSION} "Initial release."

# Create debian/copyright
cat > debian/copyright <<EOF
Format: https://www.debian.org/doc/packaging-manuals/copyright-format/1.0/
Upstream-Name: QuantumC
Source: https://github.com/YOUR_GITHUB/qc

Files: *
Copyright: (c) $(date +%Y) ${MAINTAINER_NAME}
License: MIT
EOF

# Create debian/install
cat > debian/install <<EOF
qc usr/local/bin
stdlib.qc usr/local/QC
syntax.qc usr/local/QC
EOF

echo "Debian packaging structure generated!"
echo "Now run:"
echo "  debuild -us -uc"
echo "Then upload with dput."
