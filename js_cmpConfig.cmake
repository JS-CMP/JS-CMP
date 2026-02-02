# Configuration file for js_cmp
# This file is configured by CMake and should not be edited manually


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was js_cmpConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

# Include directory
set(js_cmp_INCLUDE_DIRS "${PACKAGE_PREFIX_DIR}/include")

# Library directory
set(js_cmp_LIBRARY_DIRS "${PACKAGE_PREFIX_DIR}/lib")

# Targets
include("${CMAKE_CURRENT_LIST_DIR}/js_cmpTargets.cmake")

# Version information
set(js_cmp_VERSION 0.1.0)

# Check if all required components are found
include("${CMAKE_CURRENT_LIST_DIR}/js_cmpTargets.cmake")

# Compatibility check
if(NOT TARGET js_cmp::jscmp)
    set(js_cmp_FOUND FALSE)
    set(js_cmp_NOT_FOUND_MESSAGE "js_cmp targets not found - project may not be installed correctly")
else()
    set(js_cmp_FOUND TRUE)
endif()
