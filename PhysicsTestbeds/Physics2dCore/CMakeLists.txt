# get our parent directory
get_filename_component(ParentDirectory ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

add_library(Physics2dCore "") 

target_include_directories(Physics2dCore
    PUBLIC 
        ${ParentDirectory}
        ${CurrentDirectory}
)

include(${CMAKE_CURRENT_LIST_DIR}/CMakeFiles.cmake)

target_link_libraries(Physics2dCore
                      PUBLIC
                      Common
                      Meta
                      Serialization
                      Geometry
                      SpatialPartition
)

zero_set_all_common_project_settings(
  Target Physics2dCore 
  Filter PhysicsTestbeds
  PrecompiledHeader "Precompiled.hpp"
  PrecompiledSource "Precompiled.cpp"
)
