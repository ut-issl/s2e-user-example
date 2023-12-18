# s2e-user-example
An example of S2E user side repository.  
This repository provides the following samples.
- A sample code to make S2E user side repository using `git submodule`.
- Sample codes for tutorials in [s2e-documents](https://github.com/ut-issl/s2e-documents).

## How to construct the repository

- This repository includes [s2e-core](https://github.com/ut-issl/s2e-core) with the `git submodule`. Please use the following commands to construct the directory.
  ```
  $ git clone git@github.com:ut-issl/s2e-user-example.git
  $ cd s2e-user-example/
  $ git submodule init
  $ git submodule update
  ```
  Or use the following command to clone the repository.
  ```
  $ git clone --recursive git@github.com:ut-issl/s2e-user-example.git
  ```

## Branches

- `main` branch
  - This is the simplest `s2e-user` repository.
  - This branch is a sample code for [How To Make New Simulation Scenario](https://github.com/ut-issl/s2e-documents/blob/develop/Tutorials/HowToMakeNewSimulationScenario.md) in the `s2e-documents`.
  - Users can refer this branch to make their `s2e-user`.
- `sample/*` branches
  - Sample codes for tutorials in [s2e-documents](https://github.com/ut-issl/s2e-documents).
  - The branch name is same with the tutorial titles.
- `feature/*`   # Developing codes
- `hotfix/*`    # Bug Fix codes

## How to use this branch

- This branch is a sample code for [How To Make New Simulation Scenario](https://github.com/ut-issl/s2e-documents/blob/develop/Tutorials/HowToMakeNewSimulationScenario.md) in the `s2e-documents`.
- Please follow the tutorial to learn how to use the sample code.
