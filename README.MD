# [JS-CMP](https://github.com/JS-CMP/JS_CMP)

## Description

**JS-CMP** is a transpiler that converts JavaScript code into C++ code, and then compiles the generated C++ code into a
binary. It enables JavaScript developers to leverage the performance of C++ by converting their JavaScript codebases
into optimized executables. The project is written in C++ and uses Boost libraries.

## Build Instructions

### Prerequisites

Ensure that you have `git`, `cmake` and `g++` or another C++ compiler installed on your system.

### 1. Clone the Repository

```bash
git clone https://github.com/JS-CMP/JS-CMP.git
```

### 2. Navigate to the Project Directory

```bash
cd JS-CMP
```

### 3. Initialize Git Submodules

```bash
git submodule update --init --recursive
```

### 4. Install Dependencies

#### Linux

**Debian-based:**

```bash
sudo apt install libboost-all-dev
```

**Arch-based:**

```bash
sudo pacman -S boost
```

**Fedora:**

```bash
sudo dnf install boost-devel
```

#### macOS

```bash
brew install boost
```

### 5. Build the Project

```bash
cmake . && make
```

## Usage

To transpile a JavaScript file and execute the resulting binary:

```bash
./js_cmp <input-file> && ./<output-file>
```

## Platform Support

JS-CMP currently supports **Linux** and **macOS** platforms. While it may be possible to build on Windows using tools
like WSL or Cygwin, official support and testing have not been provided for Windows environments. Contributions for
Windows compatibility are welcome.

---
Organization: https://github.com/JS-CMP
Road Map: https://github.com/orgs/JS-CMP/projects/2
