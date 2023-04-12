# プロジェクト名を設定
project(dataObject)

# インクルードフォルダ追加
set(INCLUDE_DIR include)
include_directories(${INCLUDE_DIR})
set(INCLUDE_DIR_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR} ${INCLUDE_DIR_PATHS} PARENT_SCOPE)

# C++ファイル取得
file(GLOB_RECURSE source_list "src/*.cpp")

# ライブラリ設定
if(STATIC_LINK_FLAG)
    add_library(${PROJECT_NAME} STATIC ${source_list})
else(STATIC_LINK_FLAG)
    add_library(${PROJECT_NAME} SHARED ${source_list})
endif(STATIC_LINK_FLAG)
add_library(${PACKAGE_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

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
        EXPORT ${PACKAGE_NAME}Targets
        INCLUDES DESTINATION include
        PUBLIC_HEADER DESTINATION include/${PACKAGE_NAME}/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PACKAGE_NAME})
endif(INSTALL_FLAG)