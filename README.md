# Grabins!
This game might cause me tons of pain but I'll make it anyways!!
# What is this?
Grabins! is some game I wanted to make for like 1 1/2 years now.
It's some silly game about some creatures called who could've guessed: Grabins.

# Building

The GitHub Actions workflow builds Windows and macOS executables in parallel.
Push the project to GitHub, then download the `Grabins-windows-latest` and
`Grabins-macos-latest` artifacts from the completed workflow run.

To build locally, install CMake and a C++ compiler, then run:

```sh
cmake -S . -B build
cmake --build build
```

The first CMake configure downloads raylib 5.5. The resulting executable is in
the `build` directory.
