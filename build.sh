#!/usr/bin/env bash
set -euo pipefail

project_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
mac_build_dir="$project_dir/build"
windows_build_dir="$project_dir/build-windows"

if [[ "$(uname -s)" != "Darwin" ]]; then
    echo "This script cross-compiles the Windows build from macOS." >&2
    exit 1
fi

for tool in cmake x86_64-w64-mingw32-gcc x86_64-w64-mingw32-g++ x86_64-w64-mingw32-windres; do
    if ! command -v "$tool" >/dev/null 2>&1; then
        echo "Required tool '$tool' was not found. Install CMake and MinGW-w64 (for example: brew install cmake mingw-w64)." >&2
        exit 1
    fi
done

cmake -S "$project_dir" -B "$mac_build_dir" -DCMAKE_BUILD_TYPE=Release
cmake --build "$mac_build_dir" --config Release

cmake -S "$project_dir" -B "$windows_build_dir" \
    -DCMAKE_TOOLCHAIN_FILE="$project_dir/cmake/mingw-w64.cmake" \
    -DCMAKE_BUILD_TYPE=Release
cmake --build "$windows_build_dir" --config Release

printf 'macOS build: %s/Grabins\n' "$mac_build_dir"
printf 'Windows build: %s/Grabins.exe\n' "$windows_build_dir"
