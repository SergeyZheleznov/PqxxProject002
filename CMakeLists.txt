cmake_minimum_required(VERSION 3.28)

project(PqxxProject002)

set(PostgreSQL_ADDITIONAL_VERSIONS "16")

add_executable(PqxxProject002 main.cpp)

add_subdirectory("C:/work/projects/libpqxx-7.8.1/libpqxx-7.8.1" libpqxx-build)

target_compile_features(PqxxProject002 PRIVATE cxx_std_17)

target_link_libraries(PqxxProject002 pqxx)