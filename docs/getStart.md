# Getting Started

## Installing

Choose one method:

- [Using prebuilt binaries](#using-prebuilt-binaries)
- [Building from source](#building-from-source)

## Using prebuilt binaries

1. Download the [Package And Version Manager](https://github.com/Youg-Otricked/quantum-c-version-manager/releases/latest). (Webi install coming soon)
2. Setup
```sh
./qcm setup // adds binary to path, makes .qc directory, .qcm directory, and adds .qc/bin to path
```
3. Install latest qc version.
```sh
qcm tooling install latest
```
4. Verify:

```bash
qc -sv
```

## Building from source

```sh
git clone https://github.com/Youg-Otricked/QuantumC
cd QuantumC
./install.sh
qc -sv
```

## Windows

Windows support is currently limited. Use WSL or build manually from source. I dont have the commands because I dont use windows.
