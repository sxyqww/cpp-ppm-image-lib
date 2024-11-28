cmake_minimum_required(VERSION 3.11)

# Название проекта и язык программирования
project(ImgLib CXX)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указание папки с исходниками
set(IMGLIB_SRC_DIR ${CMAKE_SOURCE_DIR}/ImgLib)

# Автоматически находим все файлы .cpp в папке ImgLib
file(GLOB IMGLIB_MAIN_FILES ${IMGLIB_SRC_DIR}/*.cpp)
file(GLOB IMGLIB_FORMAT_FILES ${IMGLIB_SRC_DIR}/*.cpp)

# Добавление статической библиотеки
add_library(ImgLib STATIC ${IMGLIB_MAIN_FILES} ${IMGLIB_FORMAT_FILES})

# Указание папки с заголовочными файлами
target_include_directories(ImgLib PUBLIC ${IMGLIB_SRC_DIR})
