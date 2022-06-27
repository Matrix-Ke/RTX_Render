cmake_minimum_required(VERSION 3.11)


# 防止直接在源文件下生成项目
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
        "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

# =====================================全局设置=======================================
set(PROJECT_VERSION 1.0.0)
set(PROJECT_NAME "RTX_Render")
Project(${PROJECT_NAME} LANGUAGES CXX VERSION ${PROJECT_VERSION})
message(STATUS "${PROJECT_NAME} Version: ${PROJECT_VERSION}")
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR})
# Cmake划分目录
set(ROOT_FOLDER_NAME "RTX_Render")
set(SECOND_FOLDER_NAME "")


#===================================引入CMake配置文件========================
if(NOT CMakeInit_FOUND)
    include(CMake/CMakeInit.cmake)
    message(STATUS ${PROJECT_NAME}.CMakeInit_FOUND = "${CMakeInit_FOUND}"  )
endif(NOT CMakeInit_FOUND)

if(NOT SetupProject_FOUND)
    include(Cmake/SetupProject.cmake)
    message(STATUS ${PROJECT_NAME}.SetupProject_FOUND= "${SetupProject_FOUND}" )
endif(NOT SetupProject_FOUND)



# ==================================引入外部包====================================
# include(CMake/SetUpConfigurations.cmake)


# =======================================添加子目录====================================
Add_all_subdirectory()
