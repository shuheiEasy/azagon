# プロジェクト名を設定
project(dataObject)
set(PARENT_PROJECT_NAME common_library)

# インクルードフォルダ追加
set(INCLUDE_DIR include)
include_directories(${INCLUDE_DIR})
set(INCLUDE_DIR_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR} ${INCLUDE_DIR_PATHS} PARENT_SCOPE)

# # C++ファイル取得
file(GLOB_RECURSE source_list "src/*.cpp")

# ライブラリ設定
add_library(${PROJECT_NAME} SHARED ${source_list})
add_library(${PARENT_PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

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