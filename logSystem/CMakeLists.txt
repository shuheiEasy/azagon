# プロジェクト名を設定
project(logSystem)
set(PARENT_PROJECT_NAME common_library)

# インクルードフォルダ追加
set(INCLUDE_DIR include)
include_directories(${INCLUDE_DIR})
include_directories(../dataObject/include)
include_directories(../formatter/include)
include_directories(../timeSystem/include)
include_directories(../fileSystem/include)
set(INCLUDE_DIR_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR} ${INCLUDE_DIR_PATHS} PARENT_SCOPE)

# # C++ファイル取得
file(GLOB_RECURSE source_list "src/*.cpp")

# ライブラリ設定
add_library(${PROJECT_NAME} SHARED ${source_list})
add_library(${PARENT_PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# リンク呼び出し
target_link_libraries(${PROJECT_NAME} common_library::dataObject)
target_link_libraries(${PROJECT_NAME} common_library::formatter)
target_link_libraries(${PROJECT_NAME} common_library::timeSystem)
target_link_libraries(${PROJECT_NAME} common_library::fileSystem)

# ヘッダー
file(GLOB_RECURSE header_list "${INCLUDE_DIR}/*.hpp")
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    FRAMEWORK TRUE
    PUBLIC_HEADER "${header_list}")

# インストール
if(INSTALL_FLAG)
    install(
        TARGETS ${PROJECT_NAME}
        EXPORT commonLibraryTargets
        INCLUDES DESTINATION include
        PUBLIC_HEADER DESTINATION include/${PARENT_PROJECT_NAME}/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PARENT_PROJECT_NAME})
endif(INSTALL_FLAG)