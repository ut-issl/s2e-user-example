# s2e-user-example
An example of S2E user side repository.  
This repository provides the following samples.
- A sample code to make S2E user side repository using `git submodule`.
- Sample codes for tutorials in [s2e-documents](https://github.com/ut-issl/s2e-documents).

## How to construct the repository

- This repository includes [s2e-core](https://github.com/ut-issl/s2e-core) as a Git submodule. Clone the repository with either of the following methods.
  ```
  $ git clone git@github.com:ut-issl/s2e-user-example.git
  $ cd s2e-user-example/
  $ git submodule update --init --recursive
  ```
  Or use the following command to clone the repository.
  ```
  $ git clone --recursive git@github.com:ut-issl/s2e-user-example.git
  ```

## Development environment setup

The setup scripts initialize the submodule, download and install the S2E external libraries, configure the platform-specific CMake preset, and build S2E. CMake 3.21 or later is required.

External libraries are installed in `ExtLibraries/`, and downloaded environment data is installed under `settings/environment/`. Both locations are ignored by Git.

### Linux and macOS

Run the setup script from the repository. It automatically selects Linux x64, Apple Silicon, or Intel Mac settings.

```sh
./scripts/setup.sh
```

The script selects one of the following presets:

- `linux-debug`
- `macos-arm64-debug`
- `macos-x64-debug`

The `linux-x86-debug` preset is also available for CI and manual 32-bit builds; it requires the compiler's multilib packages. The setup script selects the 64-bit preset on Linux.

The setup script builds both the external libraries and S2E, so no additional build command is required. Later, after changing only the S2E source code, you can optionally rebuild just S2E with:

```sh
cmake --build --preset linux-debug --parallel
```

Replace `linux-debug` with the preset selected by the setup script on macOS.

### Windows and Visual Studio

Visual Studio 2022 with the **Desktop development with C++** workload, CMake 3.21 or later, Git, and PowerShell are required.

For a 64-bit build, run:

```powershell
.\scripts\setup.ps1
```

For a 32-bit build, run:

```powershell
.\scripts\setup.ps1 -Architecture Win32
```

The script selects `windows-x64-debug` or `windows-win32-debug`. After setup, Visual Studio can open this repository as a CMake project and select the same preset. The generated Visual Studio solution is also available under the corresponding `build/windows-*-debug/` directory.

The PowerShell setup script also builds both the external libraries and S2E. Later, after changing only the S2E source code, you can optionally rebuild just S2E with:

```powershell
cmake --build --preset windows-x64-debug --parallel
```

The former Visual Studio-specific `CMakeSettings.json` has been replaced by `CMakePresets.json`, so Visual Studio, command-line builds, and automation share the same S2E configuration.

### List available presets

```sh
cmake --list-presets
cmake --build --list-presets
```

## Branches

- `main` branch
  - This is the simplest `s2e-user` repository.
  - This branch is a sample code for [How To Make New Simulation Scenario](https://github.com/ut-issl/s2e-documents/blob/develop/Tutorials/HowToMakeNewSimulationScenario.md) in the `s2e-documents`.
  - Users can refer this branch to make their `s2e-user`.
  - Currently, the branch uses s2e-core v8.
- `sample/*` branches
  - Sample codes for tutorials in [s2e-documents](https://github.com/ut-issl/s2e-documents).
  - The branch name is same with the tutorial titles.
- `feature/*`   # Developing codes
- `hotfix/*`    # Bug Fix codes

## How to use this branch

- This branch is a sample code for [How To Make New Simulation Scenario](https://github.com/ut-issl/s2e-documents/blob/develop/Tutorials/HowToMakeNewSimulationScenario.md) in the `s2e-documents`.
- Please follow the tutorial to learn how to use the sample code.
