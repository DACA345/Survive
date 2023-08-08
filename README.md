<p align="center">
    <img alt="DACA: Survive logo" width="250px" src="./textures/icon/icon.png">
</p>

<h1 align="center">
    DACA: Survive
</h1>

<p align="center">
  <a href="https://github.com/DACA345/Survive/actions">
    <img src="https://github.com/DACA345/Survive/actions/workflows/release.yml/badge.svg" alt="Release status badge">
  </a>

  <a href="https://github.com/DACA345/Survive/actions">
    <img src="https://github.com/DACA345/Survive/actions/workflows/test.yml/badge.svg" alt="Unit test status badge">
  </a>

  <a href="https://github.com/DACA345/Survive/actions">
    <img src="https://github.com/DACA345/Survive/actions/workflows/documentation.yml/badge.svg" alt="Documentation status badge">
  </a>
</p>

DACA: Survive is an open source GUI based game in which you attempt to survive for as long as possible in real places using real data sets.

## Release packages
Releases can be found [here](https://github.com/DACA345/Survive/releases)

The [latest](https://github.com/DACA345/Survive/releases/tag/latest) release is auto generated on every push to the main branch.

Tagged pushes also auto generate a release with the tag name.

## How to build

### Requirements
1. Clone and cd into this repository: `git clone https://github.com/DACA345/Survive` & `cd Survive`
2. Download Qt6
    - [Qt 6 Open Source](https://www.qt.io/download-qt-installer-oss)
    - Select a Qt version in the select components page
    ##### Slow download fix
    - If the Qt installer is downloading very slow try running using a [mirror](https://download.qt.io/static/mirrorlist/) and choosing Qt6.3.2
        - `./qt-unified-{installer-version}-online.exe --mirror https://mirrors.ocf.berkeley.edu/qt/`

#### Building from the command line
3. Ensure CMake is added to the path
4. Run the following commands
    - `mkdir build`
    - `cd build`
    - `cmake .. -DCMAKE_INSTALL_PREFIX={Where you want to install to} -DQt6_INSTALL_PREFIX={Qt Install Path}/{Version}/{Build Type}`
    - `cmake --build . --config Release`
    - `cmake --install .`
5. The executable can then be found in the `bin` folder of your specified install prefix.

#### Building with Visual Studio
3. Ensure your Visual Studio install has CMake
4. Open the `CMakeLists.txt` in Visual Studio
5. Configure CMakeSettings.json (right click CMakeLists.txt -> CMake Settings) to use the Qt6 install path
    - CMake Command Arguments: `-DQt6_INSTALL_PREFIX={Qt Install Path}/{Version}/{Build Type}`
6. Select `(install) Survive.exe` as the target executable
7. Run the project

## Contributing

### Developer documentation
The developer documentation can be found [here](https://daca345.github.io/Survive/).

This is auto generated from the code using [Doxygen](https://www.doxygen.nl/index.html) on each push to the main branch.

### Setup pre-commit hooks
Pre-commit hooks are used to format code and check files.

To setup the pre-commit hooks follow these steps:
###### Note: Ensure you select the add to path box when installing python.
1. Install [Python](https://www.python.org/)
2. Install pre-commit through python `pip install pre-commit`
3. Install the git hooks using pre-commit `pre-commit install`
4. Install the git commit hooks using pre-commit `pre-commit install --hook-type commit-msg`

Whenever you commit your code it will be automatically formatted to follow the conventions.

### Git commit conventions
Commits must follow the [conventional commit format](https://www.conventionalcommits.org/en/v1.0.0/).

### Branches
The main repository branch is locked for editing. Please create a branch with the naming convention: `username/branch-feature`.
Then submit a [pull request](https://github.com/DACA345/Survive/pulls) and it will be merged once reviewed.
