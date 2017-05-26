project(cmaker)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
aux_source_directory(./ SRC_LIST)
aux_source_directory(./driver SRC_DRIVER)
aux_source_directory(./handler SRC_HANDLER)
aux_source_directory(./msg SRC_MSG)
aux_source_directory(./msg/lcm SRC_MSG)
aux_source_directory(./publisher SRC_PUBLISHER)
aux_source_directory(./viewer SRC_VIEWER)

FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(
  ./
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${SRC_DRIVER} ${SRC_HANDLER} ${SRC_MSG} ${SRC_PUBLISHER} ${SRC_VIEWER})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/driver/libcontrolcan.so pthread ${OpenCV_LIBS} lcm)
