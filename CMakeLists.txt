project(ECS)
cmake_minimum_required(VERSION 2.8)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
message("BUILD TYPE= " ${CMAKE_BUILD_TYPE})
#-DCMAKE_BUILD_TYPE=Debug
set(ITEMS
    ${ITEMS}
    src/myecs/component_factory.cpp
    src/myecs/component_factory.h
    src/myecs/systemfactory.cpp
    src/myecs/systemfactory.h
    src/myecs/cposition.cpp
    src/myecs/cposition.h
    src/myecs/cspeed.cpp
    src/myecs/cspeed.h
    src/myecs/smovement.cpp
    src/myecs/smovement.h
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
#aux_source_directory(./ECS ECS_LIST)
set(ECS_LIST
${ECS_LIST}
    src/ECS/component.cpp
    src/ECS/component.h
    src/ECS/system.cpp
    src/ECS/system.h
    src/ECS/entities.cpp
    src/ECS/entities.h
    src/ECS/systemmanager.cpp
    src/ECS/systemmanager.h
)
#aux_source_directory(./Systems SRC_LIST)
#aux_source_directory(./Components SRC_LIST)
set(SIMPLE
    ${SIMPLE}
    ${CMAKE_SOURCE_DIR}/src/examples/simple.cpp
)
set(BIGGER
    ${BIGGER}
    ${CMAKE_SOURCE_DIR}/src/examples/bigger.cpp
)
set(TESTS
    ${TESTS}
    ${CMAKE_SOURCE_DIR}/src/tests/test1.cpp

)
set(TESTSYSTEM
    ${CMAKE_SOURCE_DIR}/src/tests/testSystem.cpp
)
add_library(ecs SHARED ${ECS_LIST})
add_library(myecs ${ITEMS})
#-- Add an Option to toggle the generation of the API documentation
option(BUILD_DOCUMENTATION "Use Doxygen to create the HTML based API documentation" OFF)
if(BUILD_DOCUMENTATION)
  FIND_PACKAGE(Doxygen)
  if (NOT DOXYGEN_FOUND)
    message(FATAL_ERROR
      "Doxygen is needed to build the documentation. Please install it correctly")
  endif()
  #-- Configure the Template Doxyfile for our specific project
  configure_file(Doxyfile.in
                 ${PROJECT_BINARY_DIR}/Doxyfile  @ONLY IMMEDIATE)
  #-- Add a custom target to run Doxygen when ever the project is built
  add_custom_target (Docs ALL
                                                                                COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
                                                                                SOURCES ${PROJECT_BINARY_DIR}/Doxyfile)
  # IF you do NOT want the documentation to be generated EVERY time you build the project
  # then leave out the 'ALL' keyword from the above command.
endif()
option(BUILD_EXAMPLES "Compile test programs" ON)
if(BUILD_EXAMPLES)
#add_definitions(-DCTEST)
    add_executable(simple ${SIMPLE})
    add_executable(bigger ${BIGGER})
    target_link_libraries(simple ecs myecs)
    target_link_libraries(bigger ecs myecs)
endif()
option(BUILD_TESTS "Compile tests" OFF)
if(BUILD_TESTS)
    add_definitions(-DUNITTEST)
    add_executable(test1 ${TESTS})
    add_executable(testSystem ${TESTSYSTEM})
    target_link_libraries(test1 ecs myecs -lgtest -lgtest_main)
    target_link_libraries(testSystem ecs myecs -lgtest -lgtest_main -lgmock -lgmock_main -lpthread)
endif()



