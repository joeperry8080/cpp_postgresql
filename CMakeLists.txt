cmake_minimum_required(VERSION 3.20)
project(PostgresConnection)

# libpqxx 8.0+ requires C++20
set(CMAKE_CXX_STANDARD 20)

# Find the libpqxx package
find_package(libpqxx REQUIRED)

add_executable(PostgresConnection main.cpp
        database.h
        country_count.cpp
        country_count.h
        database.cpp)

# Link the library to your executable
target_link_libraries(PostgresConnection PRIVATE libpqxx::pqxx)

# Copy .env to the build directory automatically
configure_file(.env .env COPYONLY)