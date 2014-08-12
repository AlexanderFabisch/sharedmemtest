project(shmtest)
include_directories(
  "."
)

add_definitions(
  -Wall
  -ggdb
)

add_executable(writer writer.cpp SharedMemory.cpp)
target_link_libraries(writer rt pthread)
add_executable(reader reader.cpp SharedMemory.cpp)
target_link_libraries(reader rt pthread)
