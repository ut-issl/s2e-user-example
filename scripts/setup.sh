#!/usr/bin/env bash

set -euo pipefail

repo_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
build_64bit=ON
apple_silicon=OFF

case "$(uname -s)" in
  Darwin)
    case "$(uname -m)" in
      arm64)
        preset=macos-arm64-debug
        apple_silicon=ON
        ;;
      x86_64)
        preset=macos-x64-debug
        ;;
      *)
        echo "Unsupported macOS architecture: $(uname -m)" >&2
        exit 1
        ;;
    esac
    ;;
  Linux)
    case "$(uname -m)" in
      x86_64|amd64)
        preset=linux-debug
        ;;
      *)
        echo "Unsupported Linux architecture: $(uname -m)" >&2
        exit 1
        ;;
    esac
    ;;
  *)
    echo "Unsupported operating system: $(uname -s)" >&2
    echo "Windows users should run scripts/setup.ps1 from PowerShell." >&2
    exit 1
    ;;
esac

command -v git >/dev/null || { echo "git was not found." >&2; exit 1; }
command -v cmake >/dev/null || { echo "cmake was not found." >&2; exit 1; }

ext_build_dir="${repo_dir}/build/extlibraries-${preset}"

git -C "${repo_dir}" submodule update --init --recursive

cmake \
  -S "${repo_dir}/s2e-core/ExtLibraries" \
  -B "${ext_build_dir}" \
  -DEXT_LIB_DIR="${repo_dir}/ExtLibraries" \
  -DSETTINGS_DIR="${repo_dir}/settings" \
  -DBUILD_64BIT="${build_64bit}" \
  -DAPPLE_SILICON="${apple_silicon}" \
  -DCMAKE_BUILD_TYPE=Debug

cmake --build "${ext_build_dir}" --parallel
cmake --install "${ext_build_dir}"

(
  cd "${repo_dir}"
  cmake --preset "${preset}"
  cmake --build --preset "${preset}" --parallel
)

echo "Setup completed with preset: ${preset}"
