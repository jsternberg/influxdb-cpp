cmake_minimum_required(VERSION 2.6)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(influxdb)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/include")

file(GLOB INFLUXDB_HEADERS "include/*.hpp" "include/**/*.hpp")
set(INFLUXDB_SOURCES
  src/client.cc
  src/point.cc
  src/protocol.cc
  src/writer.cc
  src/http_writer.cc
)

add_library(influxdb ${INFLUXDB_SOURCES})
target_link_libraries(influxdb ${CURL_LIBRARIES})
target_compile_features(influxdb PUBLIC cxx_std_11)

file(GLOB testfiles "src/*_test.cc")
add_executable(influxdb_test "${testfiles}")
target_link_libraries(influxdb_test influxdb)

include(CTest)
add_test(NAME influxdb COMMAND influxdb_test)

install(TARGETS influxdb DESTINATION lib)
install(FILES ${INFLUXDB_HEADERS} DESTINATION include)
