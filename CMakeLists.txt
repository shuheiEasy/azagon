# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.11.0)

# プロジェクト名と使用する言語を設定
project(common_library LANGUAGES CXX VERSION 0.4.0)

# 引数一覧

# doxygen制御
set(DOC_FLAG OFF CACHE BOOL ON)
set(INSTALL_FLAG OFF CACHE BOOL ON)

# サブプロジェクト設定
add_subdirectory(dataObject)
add_subdirectory(formatter)
add_subdirectory(timeSystem)
add_subdirectory(fileSystem)
add_subdirectory(logSystem)

# doxygenプロジェクト設定
if(DOC_FLAG)
    add_subdirectory(docs)
else(DOC_FLAG)
    message("Doxygen OFF")
endif(DOC_FLAG)

# libraryの変数設定
list(APPEND LIB_PATHS common_library::dataObject )
list(APPEND LIB_PATHS common_library::formatter )
list(APPEND LIB_PATHS common_library::timeSystem )
list(APPEND LIB_PATHS common_library::fileSystem )
list(APPEND LIB_PATHS common_library::logSystem )

if(INSTALL_FLAG)
# インストール
install(
    EXPORT commonLibraryTargets
    DESTINATION cmake
    NAMESPACE common_library::
    FILE commonLibraryTargets.cmake)

# config用変数
set(INCLUDE_DIRS_PATH ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})

include(CMakePackageConfigHelpers)
configure_package_config_file( 
    "Config.cmake.cfg" 
    "common_libraryConfig.cmake"
    INSTALL_DESTINATION cmake)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/common_libraryConfig.cmake"
    DESTINATION "cmake")

else(INSTALL_FLAG)
    message("Install mode OFF")
endif(INSTALL_FLAG)

# ソースモード
if(NOT common_library_IS_TOP_LEVEL)
    set(common_library_INCLUDE_DIR ${INCLUDE_DIR_PATHS} PARENT_SCOPE)
    set(common_library_LIBS ${LIB_PATHS} PARENT_SCOPE)
endif()