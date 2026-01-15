#!/bin/bash

# JS-CMP Clean Script
# This script cleans build artifacts and directories

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

# Function to show usage
function show_usage() {
    echo "Usage: $0 [options]"
    echo ""
    echo "Options:"
    echo "  -h, --help      Show this help message"
    echo "  -a, --all       Clean all build directories and artifacts"
    echo "  -b, --build     Clean only build directories"
    echo "  -d, --dist      Clean only distribution packages"
    echo "  -t, --test      Clean test files"
    echo "  -f, --force     Force clean without confirmation"
    echo ""
    echo "Examples:"
    echo "  $0              # Interactive clean"
    echo "  $0 --all        # Clean everything"
    echo "  $0 --build      # Clean only build directories"
    echo "  $0 --force      # Force clean without confirmation"
}

# Function to confirm action
function confirm_action() {
    local message=$1
    read -p "${message} (y/N): " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        echo_color "${YELLOW}" "Action cancelled"
        exit 0
    fi
}

# Function to clean build directories
function clean_build() {
    echo_color "${BLUE}" "Cleaning build directories..."
    
    local build_dirs=(
        "build"
        "build/*"
        "CMakeFiles"
        "CMakeCache.txt"
        "cmake_install.cmake"
        "Makefile"
        "*.cmake"
        "*.make"
        "*.dir"
    )
    
    local cleaned_something=false
    
    for dir in "${build_dirs[@]}"; do
        if [ -e "${dir}" ]; then
            echo "Removing ${dir}..."
            rm -rf "${dir}"
            cleaned_something=true
        fi
    done
    
    if [ "${cleaned_something}" == true ]; then
        echo_color "${GREEN}" "Build directories cleaned successfully"
    else
        echo_color "${YELLOW}" "No build directories found to clean"
    fi
}

# Function to clean distribution packages
function clean_dist() {
    echo_color "${BLUE}" "Cleaning distribution packages..."
    
    local dist_dirs=(
        "dist"
        "packages"
        "release"
        "*.tar.gz"
        "*.zip"
        "*.tgz"
        "*.txz"
    )
    
    local cleaned_something=false
    
    for item in "${dist_dirs[@]}"; do
        if [ -e "${item}" ]; then
            echo "Removing ${item}..."
            rm -rf "${item}"
            cleaned_something=true
        fi
    done
    
    if [ "${cleaned_something}" == true ]; then
        echo_color "${GREEN}" "Distribution packages cleaned successfully"
    else
        echo_color "${YELLOW}" "No distribution packages found to clean"
    fi
}

# Function to clean test files
function clean_test() {
    echo_color "${BLUE}" "Cleaning test files..."
    
    local test_files=(
        "test_basic_classes_es5.js"
        "test_*.js"
        "test_output*"
        "test_results*"
    )
    
    local cleaned_something=false
    
    for file in "${test_files[@]}"; do
        if [ -e "${file}" ]; then
            echo "Removing ${file}..."
            rm -f "${file}"
            cleaned_something=true
        fi
    done
    
    if [ "${cleaned_something}" == true ]; then
        echo_color "${GREEN}" "Test files cleaned successfully"
    else
        echo_color "${YELLOW}" "No test files found to clean"
    fi
}

# Function to clean everything
function clean_all() {
    echo_color "${BLUE}" "Cleaning everything..."
    
    clean_build
    clean_dist
    clean_test
    
    # Additional cleanup
    local other_files=(
        "*.o"
        "*.a"
        "*.so"
        "*.dylib"
        "*.exe"
        "*.out"
        "core"
        "*.stackdump"
    )
    
    local cleaned_something=false
    
    for pattern in "${other_files[@]}"; do
        for file in ${pattern}; do
            if [ -e "${file}" ]; then
                echo "Removing ${file}..."
                rm -f "${file}"
                cleaned_something=true
            fi
        done
    done
    
    echo_color "${GREEN}" "All artifacts cleaned successfully"
}

# Main function
function main() {
    local clean_all=false
    local clean_build=false
    local clean_dist=false
    local clean_test=false
    local force=false
    
    # Parse command line arguments
    while [[ $# -gt 0 ]]; do
        case $1 in
            -h|--help)
                show_usage
                exit 0
                ;;
            -a|--all)
                clean_all=true
                shift
                ;;
            -b|--build)
                clean_build=true
                shift
                ;;
            -d|--dist)
                clean_dist=true
                shift
                ;;
            -t|--test)
                clean_test=true
                shift
                ;;
            -f|--force)
                force=true
                shift
                ;;
            *)
                echo_color "${RED}" "Unknown option: $1"
                show_usage
                exit 1
                ;;
        esac
    done
    
    # If no specific options, show interactive menu
    if [ "${clean_all}" == false ] && 
       [ "${clean_build}" == false ] && 
       [ "${clean_dist}" == false ] && 
       [ "${clean_test}" == false ]; then
        
        echo "JS-CMP Clean Script"
        echo "==================="
        echo "What would you like to clean?"
        echo ""
        echo "1) Build directories only"
        echo "2) Distribution packages only"
        echo "3) Test files only"
        echo "4) Everything (build, dist, test, and other artifacts)"
        echo "5) Cancel"
        echo ""
        
        read -p "Enter your choice (1-5): " choice
        echo
        
        case $choice in
            1)
                clean_build=true
                ;;
            2)
                clean_dist=true
                ;;
            3)
                clean_test=true
                ;;
            4)
                clean_all=true
                ;;
            5)
                echo_color "${YELLOW}" "Cleaning cancelled"
                exit 0
                ;;
            *)
                echo_color "${RED}" "Invalid choice"
                exit 1
                ;;
        esac
    fi
    
    # Confirm action unless force flag is set
    if [ "${force}" == false ]; then
        local confirmation_message=""
        
        if [ "${clean_all}" == true ]; then
            confirmation_message="This will clean ALL build artifacts, distributions, and test files. Are you sure?"
        elif [ "${clean_build}" == true ]; then
            confirmation_message="This will clean build directories. Are you sure?"
        elif [ "${clean_dist}" == true ]; then
            confirmation_message="This will clean distribution packages. Are you sure?"
        elif [ "${clean_test}" == true ]; then
            confirmation_message="This will clean test files. Are you sure?"
        fi
        
        if [ -n "${confirmation_message}" ]; then
            confirm_action "${confirmation_message}"
        fi
    fi
    
    # Perform cleaning
    if [ "${clean_all}" == true ]; then
        clean_all
    else
        if [ "${clean_build}" == true ]; then
            clean_build
        fi
        
        if [ "${clean_dist}" == true ]; then
            clean_dist
        fi
        
        if [ "${clean_test}" == true ]; then
            clean_test
        fi
    fi
    
    echo_color "${GREEN}" "Cleaning completed!"
}

# Run main function
main "$@"