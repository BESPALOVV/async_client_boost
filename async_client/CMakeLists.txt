
add_executable (async_client "async_client.cpp" "async_client.h" "main.cpp")

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

link_libraries(${Boost_LIBRARIES})
