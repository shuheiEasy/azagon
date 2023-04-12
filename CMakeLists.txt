# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.11.0)

# プロジェクト名と使用する言語を設定
project(azagon LANGUAGES CXX VERSION 0.6.1)
set(PACKAGE_NAME ${PROJECT_NAME})

# 静的リンク制御
set(STATIC_LINK_FLAG OFF CACHE BOOL ON)

# doxygen制御
set(DOC_FLAG OFF CACHE BOOL ON)

# インストール制御
set(INSTALL_FLAG OFF CACHE BOOL ON)

# サブプロジェクト設定
add_subdirectory(dataObject)
add_subdirectory(threadSystem)
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
list(APPEND LIB_PATHS ${PROJECT_NAME}::dataObject )
list(APPEND LIB_PATHS ${PROJECT_NAME}::formatter )
list(APPEND LIB_PATHS ${PROJECT_NAME}::timeSystem )
list(APPEND LIB_PATHS ${PROJECT_NAME}::fileSystem )
list(APPEND LIB_PATHS ${PROJECT_NAME}::logSystem )

if(INSTALL_FLAG)
# インストール
install(
    EXPORT ${PROJECT_NAME}Targets
    DESTINATION cmake
    NAMESPACE ${PROJECT_NAME}::
    FILE ${PROJECT_NAME}Targets.cmake)

# config用変数
set(INCLUDE_DIRS_PATH ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})

# インストールさせるファイルを作成するライブラリ
include(CMakePackageConfigHelpers)

# configファイル
configure_package_config_file( 
    "Config.cmake.cfg" 
    "${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION cmake)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    DESTINATION "cmake")

# バージョン用ファイル
write_basic_package_version_file(
    "${PROJECT_NAME}ConfigVersion.cmake"
    COMPATIBILITY AnyNewerVersion)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "cmake"
)

else(INSTALL_FLAG)
    message("Install mode OFF")
endif(INSTALL_FLAG)

# ソースモード
if(NOT ${PROJECT_NAME}_IS_TOP_LEVEL)
    set(${PROJECT_NAME}_INCLUDE_DIR ${INCLUDE_DIR_PATHS} PARENT_SCOPE)
    set(${PROJECT_NAME}_LIBS ${LIB_PATHS} PARENT_SCOPE)
endif()