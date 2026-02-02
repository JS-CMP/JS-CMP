#!/bin/bash

# JS-CMP Build Script
# This script provides a comprehensive build system for the JS-CMP project
# with support for different build types, architectures, and environments

set -e  # Exit on error

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'  # No Color

# Function to print colored messages
function echo_color() {
    local color=$1
    local message=$2
    printf "%b%s%b\n" "$color" "$message" "$NC"
}

# Function to check if a command exists
function command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Function to check dependencies
function check_dependencies() {
    echo_color "${BLUE}" "Checking dependencies..."
    
    local missing_deps=()
    
    # Check for required tools
    if ! command_exists cmake; then
        missing_deps+=("cmake")
    fi
    
    if ! command_exists make; then
        missing_deps+=("make")
    fi
    
    if ! command_exists git; then
        missing_deps+=("git")
    fi
    
    # Check for C++ compiler
    if ! command_exists g++ && ! command_exists clang++; then
        missing_deps+=("C++ compiler (g++ or clang++)")
    fi
    
    if [ ${#missing_deps[@]} -gt 0 ]; then
        echo_color "${RED}" "Error: Missing dependencies:"
        for dep in "${missing_deps[@]}"; do
            echo "  - $dep"
        done
        echo
        echo "Please install the missing dependencies and try again."
        exit 1
    fi
    
    echo_color "${GREEN}" "All dependencies found!"
}

# Global variables for platform and architecture
PLATFORM="unknown"
ARCH="unknown"

# Function to detect platform and architecture
function detect_platform() {
    echo_color "${BLUE}" "Detecting platform and architecture..."
    
    # Detect platform
    if [ "$(uname)" == "Darwin" ]; then
        PLATFORM="macos"
    elif [ "$(uname -s)" == "Linux" ]; then
        PLATFORM="linux"
    else
        echo_color "${RED}" "Error: Unsupported platform: $(uname)"
        exit 1
    fi
    
    # Detect architecture
    if [ "$(uname -m)" == "x86_64" ] || [ "$(uname -m)" == "amd64" ]; then
        ARCH="x86_64"
    elif [ "$(uname -m)" == "arm64" ] || [ "$(uname -m)" == "aarch64" ]; then
        ARCH="arm64"
    else
        echo_color "${YELLOW}" "Warning: Unknown architecture: $(uname -m), defaulting to x86_64"
        ARCH="x86_64"
    fi
    
    echo_color "${GREEN}" "Detected platform: ${PLATFORM}, architecture: ${ARCH}"
}

# Function to initialize submodules
function init_submodules() {
    echo_color "${BLUE}" "Initializing git submodules..."
    
    if [ ! -d "submodules/Lexer" ] || [ ! -d "submodules/SyntaxSmith" ]; then
        git submodule update --init --recursive
        if [ $? -ne 0 ]; then
            echo_color "${RED}" "Error: Failed to initialize submodules"
            exit 1
        fi
        echo_color "${GREEN}" "Submodules initialized successfully"
    else
        echo_color "${GREEN}" "Submodules already initialized"
    fi
}

# Function to configure build
function configure_build() {
    local build_type=$1
    local static_build=$2
    local build_dir=$3
    
    echo_color "${BLUE}" "Configuring ${build_type} build..."
    
    # Create build directory
    mkdir -p "${build_dir}"
    
    # Change to build directory
    cd "${build_dir}" || exit 1
    
    # Configure with appropriate options
    local cmake_cmd="cmake ${OLDPWD}"
    
    if [ "${build_type}" == "Release" ]; then
        cmake_cmd="${cmake_cmd} -DCMAKE_BUILD_TYPE=Release"
    else
        cmake_cmd="${cmake_cmd} -DCMAKE_BUILD_TYPE=Debug"
    fi
    
    if [ "${static_build}" == "true" ]; then
        # On macOS, we can't create fully static executables due to system limitations
        if [ "${PLATFORM}" == "macos" ]; then
            echo_color "${YELLOW}" "Warning: macOS does not support fully static executables. Building static library and dynamic executable."
            cmake_cmd="${cmake_cmd} -DBUILD_STATIC=ON -DBUILD_SHARED=ON -DFORCE_STATIC_DEPS=ON"
        else
            cmake_cmd="${cmake_cmd} -DBUILD_STATIC=ON -DBUILD_SHARED=OFF -DFORCE_STATIC_DEPS=ON"
        fi
    else
        cmake_cmd="${cmake_cmd} -DBUILD_STATIC=OFF -DBUILD_SHARED=ON -DFORCE_STATIC_DEPS=OFF"
    fi
    
    # Platform-specific settings
    if [ "${PLATFORM}" == "macos" ] && [ "${ARCH}" == "arm64" ]; then
        cmake_cmd="${cmake_cmd} -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_SYSTEM_PROCESSOR=arm64"
    fi
    
    echo "Running: ${cmake_cmd}"
    eval ${cmake_cmd}
    
    if [ $? -ne 0 ]; then
        echo_color "${RED}" "Error: CMake configuration failed"
        exit 1
    fi
    
    echo_color "${GREEN}" "Configuration successful"
}

# Function to build project
function build_project() {
    local build_dir=$1
    local parallel_jobs=$2
    
    echo_color "${BLUE}" "Building project..."
    
    # We should already be in the build directory from configure_build
    # cd "${build_dir}"
    
    # Use all available cores if parallel_jobs is 0 or not specified
    if [ "${parallel_jobs}" -eq 0 ]; then
        if command_exists nproc; then
            parallel_jobs=$(nproc)
        elif [ "${PLATFORM}" == "macos" ]; then
            parallel_jobs=$(sysctl -n hw.ncpu)
        else
            parallel_jobs=4
        fi
    fi
    
    echo "Building with ${parallel_jobs} parallel jobs..."
    make -j${parallel_jobs}
    
    if [ $? -ne 0 ]; then
        echo_color "${RED}" "Error: Build failed"
        exit 1
    fi
    
    echo_color "${GREEN}" "Build successful"
}

# Function to install project
function install_project() {
    local build_dir=$1
    local install_prefix=$2
    
    echo_color "${BLUE}" "Installing project..."
    
    cd "${build_dir}"
    
    local install_cmd="sudo make install"
    
    if [ -n "${install_prefix}" ]; then
        install_cmd="${install_cmd} DESTDIR=${install_prefix}"
    fi
    
    echo "Running: ${install_cmd}"
    eval ${install_cmd}
    
    if [ $? -ne 0 ]; then
        echo_color "${RED}" "Error: Installation failed"
        exit 1
    fi
    
    echo_color "${GREEN}" "Installation successful"
}

# Function to create package
function create_package() {
    local build_dir=$1
    local package_type=$2
    local output_dir=$3

    echo_color "${BLUE}" "Creating package..."

    # Save current directory and go to project root
    local current_dir=$(pwd)
    cd "${OLDPWD}"  # Go back to project root

    # Copy build artifacts to project root for packaging
    if [ -f "${build_dir}/js_cmp" ]; then
        cp "${build_dir}/js_cmp" .
        
        # Fix rpath for macOS to look for libraries in the same directory
        if [ "${PLATFORM}" == "macos" ]; then
            echo "Fixing rpath for macOS executable..."
            install_name_tool -change "@rpath/libjscmp.1.dylib" "@loader_path/libjscmp.1.dylib" js_cmp
            install_name_tool -add_rpath "@loader_path" js_cmp
        fi
    fi
    if [ -f "${build_dir}/libjscmp.a" ]; then
        cp "${build_dir}/libjscmp.a" .
    elif [ -f "${build_dir}/libjscmp.dylib" ]; then
        # Copy all dylib files including versioned symlinks
        cp -P "${build_dir}/libjscmp.dylib" .
        cp -P "${build_dir}/libjscmp.1.dylib" .
        cp -P "${build_dir}/libjscmp.0.1.0.dylib" .
    elif [ -f "${build_dir}/libjscmp.so" ]; then
        # Copy all so files including versioned symlinks
        cp "${build_dir}/libjscmp.so" .
        if [ -f "${build_dir}/libjscmp.so.1" ]; then
            cp "${build_dir}/libjscmp.so.1" .
        fi
        if [ -f "${build_dir}/libjscmp.so.0.1.0" ]; then
            cp "${build_dir}/libjscmp.so.0.1.0" .
        fi
    fi
    
    # Create output directory if it doesn't exist
    mkdir -p "${output_dir}"

    # Determine package name based on platform and architecture
    local package_name="js-cmp-${PLATFORM}-${ARCH}"
    
    # Build the list of files to include based on what actually exists
    local files_to_package=("./includes" "./cmake" "./submodules/Lexer/include" "./submodules/SyntaxSmith/includes" "./LICENSE" "./README.md")
    
    if [ -f "js_cmp" ]; then
        files_to_package+=("js_cmp")
    fi
    
    if [ -f "libjscmp.a" ]; then
        files_to_package+=("libjscmp.a")
    elif [ -f "libjscmp.dylib" ]; then
        files_to_package+=("libjscmp.dylib" "libjscmp.1.dylib" "libjscmp.0.1.0.dylib")
    elif [ -f "libjscmp.so" ]; then
        files_to_package+=("libjscmp.so" "libjscmp.so.1" "libjscmp.so.0.1.0")
    fi
    
    if [ "${package_type}" == "tar" ]; then
        echo "Creating tarball package: ${package_name}.tar.gz"
        tar czvhf "${output_dir}/${package_name}.tar.gz" "${files_to_package[@]}"
    elif [ "${package_type}" == "zip" ]; then
        echo "Creating zip package: ${package_name}.zip"
        zip -r "${output_dir}/${package_name}.zip" "${files_to_package[@]}"
    else
        echo_color "${RED}" "Error: Unknown package type: ${package_type}"
        return 1
    fi
    
    # Clean up temporary files
    rm -f js_cmp libjscmp.a
    
    # Restore original directory
    cd "${current_dir}"
    
    echo_color "${GREEN}" "Package created successfully: ${output_dir}/${package_name}.${package_type}"
}

# Function to show usage
function show_usage() {
    echo "Usage: $0 [options]"
    echo ""
    echo "Options:"
    echo "  -h, --help            Show this help message"
    echo "  -c, --clean           Clean build directories before building"
    echo "  -d, --debug           Build debug version"
    echo "  -s, --static          Build static version (default: dynamic)"
    echo "  -i, --install         Install after building"
    echo "  -p, --package         Create package after building (tar/zip)"
    echo "  -j, --jobs            Number of parallel build jobs (default: auto)"
    echo "  -o, --output          Output directory for packages"
    echo "  --prefix              Installation prefix"
    echo ""
    echo "Examples:"
    echo "  $0                          # Default build (Release, dynamic)"
    echo "  $0 --static                # Static build"
    echo "  $0 --debug                 # Debug build"
    echo "  $0 --static --install      # Static build and install"
    echo "  $0 --package --output dist # Create package in dist directory"
}

# Main script execution
function main() {
    # Parse command line arguments
    local clean_build=false
    local build_type="Release"
    local static_build=false
    local install_after=false
    local create_package=""
    local parallel_jobs=0
    local output_dir="dist"
    local install_prefix=""
    
    while [[ $# -gt 0 ]]; do
        case $1 in
            -h|--help)
                show_usage
                exit 0
                ;;
            -c|--clean)
                clean_build=true
                shift
                ;;
            -d|--debug)
                build_type="Debug"
                shift
                ;;
            -s|--static)
                static_build=true
                shift
                ;;
            -i|--install)
                install_after=true
                shift
                ;;
            -p|--package)
                create_package="tar"  # default to tar
                shift
                ;;
            -j|--jobs)
                parallel_jobs=$2
                shift 2
                ;;
            -o|--output)
                output_dir=$2
                shift 2
                ;;
            --prefix)
                install_prefix=$2
                shift 2
                ;;
            --package-type)
                create_package=$2
                shift 2
                ;;
            *)
                echo_color "${RED}" "Unknown option: $1"
                show_usage
                exit 1
                ;;
        esac
    done
    
    # Detect platform and architecture
    detect_platform
    
    # Check dependencies
    check_dependencies
    
    # Initialize submodules
    init_submodules
    
    # Determine build directory name
    local build_dir_suffix=""
    if [ "${static_build}" == true ]; then
        build_dir_suffix="static"
    else
        build_dir_suffix="dynamic"
    fi
    
    # Convert build type to lowercase
    local build_type_lower=$(echo "${build_type}" | tr '[:upper:]' '[:lower:]')
    
    local build_dir="build/${PLATFORM}-${ARCH}-${build_type_lower}-${build_dir_suffix}"
    
    # Clean build if requested
    if [ "${clean_build}" == true ]; then
        echo_color "${BLUE}" "Cleaning build directory..."
        rm -rf "${build_dir}"
    fi
    
    # Configure build
    configure_build "${build_type}" "${static_build}" "${build_dir}"
    
    # Build project
    build_project "${build_dir}" "${parallel_jobs}"
    
    # Install if requested
    if [ "${install_after}" == true ]; then
        install_project "${build_dir}" "${install_prefix}"
    fi
    
    # Create package if requested
    if [ -n "${create_package}" ]; then
        create_package "${build_dir}" "${create_package}" "${output_dir}"
    fi
    
    echo_color "${GREEN}" "Build process completed successfully!"
}

# Run main function
main "$@"