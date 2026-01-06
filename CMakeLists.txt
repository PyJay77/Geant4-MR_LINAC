cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(MRLINAC)

find_package(Geant4 REQUIRED ui_all vis_all)

file(GLOB sources ${PROJECT_SOURCE_DIR}/sources/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/headers/*.cpp)

add_executable(mrlinac mrlinac.cpp ${sources} ${headers})
target_include_directories(mrlinac PRIVATE ${PROJECT_SOURCE_DIR}/sources ${PROJECT_SOURCE_DIR}/headers)
target_link_libraries(mrlinac ${Geant4_LIBRARIES})

add_custom_target(MRLINAC DEPENDS mrlinac)