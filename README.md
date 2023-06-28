# C OpenGL Template

`Version`: 0.0.1

https://github.com/the-homeless-god/C-OpenGL-template/assets/32175240/a2d39fae-2b0a-45a0-94d3-a3dbd928e2cf

- a few shaders (renders rotated cube with gradient of colors)
- OpenGL
- `Conan@1.x`
- cmake
- make
- glfw
- glew
- cunit
- cglm

## Note

- TODO: Fix file uploading of shaders by specific naming. Everything works as expected, excluding the issues with test of asset uploads, seems like I've not ability to verify it on my current system.
- TODO: Replace `main.old.c` with `main.c` 'cos currently we have `main.c` file that everything works, while in `main.old.c` there's good definition, but when I've debugged, I spent a lot of hours to understand what wrong with file reading, but temporarly it would be still on master to not forget to fix it and rebase commits when it would be fixed.
- TODO: add guide how to add new tests
- TODO: add GitHub Actions for each deployment state
- TODO: add build to WASM (as fast option to test at GitHub Pages)
- TODO: add more documentation about code structure and imperative places

## Requirements

- MacOS - (OS X) install tools

```shell
brew install conan@1
brew install cmake

conan profile detect --force
```

- Linux - install tools

```shell
sudo apt-get update
sudo apt-get install libgl-dev libgl1-mesa-dev libglu1-mesa-dev libx11-xcb-dev libfontenc-dev libxaw7-dev libxcomposite-dev libxcursor-dev libxdamage-dev libxfixes-dev libxi-dev libxinerama-dev libxkbfile-dev libxmu-dev libxmuu-dev libxpm-dev libxrandr-dev libxres-dev libxtst-dev libxv-dev libxvmc-dev libxxf86vm-dev libxcb-render0-dev libxcb-render-util0-dev libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-xinerama0-dev libxcb-dri3-dev libxcb-cursor-dev libxcb-util0-dev libxcb-util-dev

pip install --force-reinstall -v "conan==1.60.1"
pip install cmake

conan profile detect --force
```

- Build (Makefile)

```shell
# install deps, build
make 

# build without deps installation
make build

# start executable app
make start

# cleanup build folder
make clean

# run unit tests
make test
```

- Build (manually)

```shell
mkdir build && cd build
conan install ..
cmake ..
make
```
