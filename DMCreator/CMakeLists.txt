project(DMCreator)
cmake_minimum_required(VERSION 2.8)
# 查找目录下的所有源文件
aux_source_directory(./src SRC_LIST)

# add_subdirectory(abseil-cpp)

find_package(dmtx)
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories(. ${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} /usr/local/lib/libdmtx.a)
