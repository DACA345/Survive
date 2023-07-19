# DACA: Survive
DACA: Survive is an open source GUI based game in which you attempt to survive for as long as possible in real places using real data sets.

## How to build

### Requirements
1. Clone and cd into this repository: `git clone https://github.com/DACA345/Survive` & `cd Survive`
2. Download Qt6
    - [Qt 6 Open Source](https://www.qt.io/download-qt-installer-oss)
    - Select a Qt version in the select components page
    ##### Slow download fix
    - If the Qt installer is downloading very slow try running using a mirror and choosing Qt6.3.2
        - `./qt-unified-{installer-version}-online.exe --mirror https://mirrors.ocf.berkeley.edu/qt/`

#### Building from the command line
3. Ensure CMake is added to the path
4. Run the following commands
    - `mkdir build`
    - `cd build`
    - `cmake .. `-DQt6_INSTALL_PREFIX={Qt Install Path}/{Version}/{Build Type}`
    - `cmake --build . --config Release`
5. The executable can then be found in `bin/Release/`

#### Building with Visual Studio
3. Ensure your Visual Studio install has CMake
4. Open the `CMakeLists.txt` in Visual Studio
5. Configure CMakeSettings.json to use the Qt6 install path
    - CMake Command Arguments: `-DQt6_INSTALL_PREFIX={Qt Install Path}/{Version}/{Build Type}`
6. Select Survive.cpp as the target executable
7. Run the project