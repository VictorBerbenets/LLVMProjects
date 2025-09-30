## Requirements
[Nix](https://nixos.org/download/) must be installed. 
## How to build
```bash
git clone git@github.com:VictorBerbenets/LLVMProjects.git
cd LLVMProjects/SDL
nix --extra-experimental-features "nix-command flakes" develop .
cmake -S ./ -B build/
cmake --build build
```
## How to run
```bash
./build/sdl
```
