# Desktop-Barnyard
## Overview
A program that will display a creature sprite of the users choice. The sprite can interact with the desktop and the user and will behave just like a pet (and even annoy the user like one).

## Build Instructions
Step 1 (Linux and WSL only): Install Dependencies
```bash
sudo apt-get update
sudo apt-get upgrade
sudo apt install -y \ 
	pkg-config cmake xorg-dev \
	libxinerama-dev libxcursor-dev libxrandr-dev libxi-dev \ 
	libglfw3-dev libgl1-mesa-dev libwayland-dev libxkbcommon-dev libwayland-egl1-mesa
```

Step 2: Clone Repository and Update Submodules
```bash
git clone https://github.com/ZipCode-UA/Desktop-Barnyard.git
cd ./Desktop-Barnyard
git submodule update --init --recursive
```

Step 3: Build Project
```bash
mkdir build
cd build
cmake ..
make
```
