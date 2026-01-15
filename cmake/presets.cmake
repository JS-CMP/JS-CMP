# CMake presets for js_cmp

# Default build preset
set(presets
    "{
        \"version\": 3,
        \"vendor\": {
            \"js_cmp\": {
                \"displayName\": \"JS-CMP Build Presets\",
                \"description\": \"Configured build presets for JS-CMP project\"
            }
        },
        \"configurePresets\": [
            {
                \"name\": \"default\",
                \"displayName\": \"Default Build\",
                \"description\": \"Default build configuration\",
                \"generator\": \"Unix Makefiles\",
                \"binaryDir\": \"${sourceDir}/build\",
                \"cacheVariables\": {
                    \"CMAKE_BUILD_TYPE\": \"Release\",
                    \"BUILD_STATIC\": \"OFF\",
                    \"BUILD_SHARED\": \"ON\",
                    \"FORCE_STATIC_DEPS\": \"OFF\"
                },
                \"environment\": {
                    \"CXXFLAGS\": \"-Wall -Wextra -Wpedantic\"
                }
            },
            {
                \"name\": \"static-release\",
                \"displayName\": \"Static Release Build\",
                \"description\": \"Static library build for release\",
                \"inherits\": \"default\",
                \"cacheVariables\": {
                    \"CMAKE_BUILD_TYPE\": \"Release\",
                    \"BUILD_STATIC\": \"ON\",
                    \"BUILD_SHARED\": \"OFF\",
                    \"FORCE_STATIC_DEPS\": \"ON\"
                }
            },
            {
                \"name\": \"debug\",
                \"displayName\": \"Debug Build\",
                \"description\": \"Debug build with symbols\",
                \"inherits\": \"default\",
                \"cacheVariables\": {
                    \"CMAKE_BUILD_TYPE\": \"Debug\",
                    \"BUILD_STATIC\": \"OFF\",
                    \"BUILD_SHARED\": \"ON\",
                    \"FORCE_STATIC_DEPS\": \"OFF\"
                }
            },
            {
                \"name\": \"arm64-release\",
                \"displayName\": \"ARM64 Release Build\",
                \"description\": \"Release build for ARM64 architecture\",
                \"inherits\": \"static-release\",
                \"cacheVariables\": {
                    \"CMAKE_OSX_ARCHITECTURES\": \"arm64\",
                    \"CMAKE_SYSTEM_PROCESSOR\": \"arm64\"
                }
            }
        ],
        \"buildPresets\": [
            {
                \"name\": \"default-build\",
                \"displayName\": \"Default Build\",
                \"configurePreset\": \"default\",
                \"configuration\": \"Release\",
                \"targets\": [\"all\"]
            },
            {
                \"name\": \"static-build\",
                \"displayName\": \"Static Build\",
                \"configurePreset\": \"static-release\",
                \"configuration\": \"Release\",
                \"targets\": [\"all\"]
            },
            {
                \"name\": \"debug-build\",
                \"displayName\": \"Debug Build\",
                \"configurePreset\": \"debug\",
                \"configuration\": \"Debug\",
                \"targets\": [\"all\"]
            }
        ],
        \"testPresets\": [
            {
                \"name\": \"default-test\",
                \"displayName\": \"Default Tests\",
                \"configurePreset\": \"default\",
                \"configuration\": \"Release\",
                \"output\": {
                    \"outputFile\": \"${sourceDir}/build/test_results.xml\"
                }
            }
        ]
    }"
)

# Write presets to CMakeUserPresets.json
file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/CMakeUserPresets.json" "${presets}")