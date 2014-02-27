project(ECS)
cmake_minimum_required(VERSION 2.8)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
if(DOSFML OR DOSFMLFULL)
    find_package(SFML 2 REQUIRED system window graphics network audio)

endif(DOSFML OR DOSFMLFULL)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
message("BUILD TYPE= " ${CMAKE_BUILD_TYPE})
#-DCMAKE_BUILD_TYPE=Debug
set(ITEMS
    ${ITEMS}

    src/myecs/Components/cposition.cpp
    src/myecs/Components/cposition.h
    src/myecs/Components/csize.cpp
    src/myecs/Components/csize.h
    src/myecs/Components/cspeed.cpp
    src/myecs/Components/cspeed.h

    src/myecs/Components/cinput.cpp
    src/myecs/Components/cinput.h
    src/myecs/Components/cbounds.h
    src/myecs/Components/cbounds.cpp

    src/myecs/component_factory.cpp
    src/myecs/component_factory.h
    src/myecs/systemfactory.cpp
    src/myecs/systemfactory.h
)
if(NOT DOSFML AND NOT DOSFMLFULL)
    set(ITEMS
        ${ITEMS}

    src/myecs/Systems/smovement.cpp
    src/myecs/Systems/smovement.h
    src/myecs/Systems/sbounds.cpp
    src/myecs/Systems/sbounds.h
)

elseif(DOSFML)
add_definitions(-DDOSFML)
    set(ITEMS
        ${ITEMS}


    src/myecs/Systems/sdraw.cpp
    src/myecs/Systems/sdraw.h
    src/myecs/Systems/smovement.cpp
    src/myecs/Systems/smovement.h
    src/myecs/Systems/sbounds.cpp
    src/myecs/Systems/sbounds.h
)
elseif(DOSFMLFULL)
add_definitions(-DDOSFMLFULL)
    set(ITEMS
        ${ITEMS}
    src/myecs/Systems/sdraw-sfmlfull.cpp
    src/myecs/Systems/sdraw-sfmlfull.h
    src/myecs/Systems/smovement-sfmlfull.cpp
    src/myecs/Systems/smovement-sfmlfull.h
    src/myecs/Systems/sbounds-sfmlfull.cpp
    src/myecs/Systems/sbounds-sfmlfull.h
src/myecs/Components/caction.cpp
src/myecs/Components/caction.h
)
endif(NOT DOSFML AND NOT DOSFMLFULL)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
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
set(MANY
    ${CMAKE_SOURCE_DIR}/src/examples/many_entities.cpp
)
set(BIGGER
    ${BIGGER}
    ${CMAKE_SOURCE_DIR}/src/examples/bigger.cpp
)
set(BOUNDS
    ${CMAKE_SOURCE_DIR}/src/examples/bounding.cpp
)
set(TESTS
    ${TESTS}
    ${CMAKE_SOURCE_DIR}/src/tests/test1.cpp

)
set(SFMLEX1
    ${CMAKE_SOURCE_DIR}/src/examples/sfml1.cpp
)
set(SFMLEX2
    ${CMAKE_SOURCE_DIR}/src/examples/sfml2.cpp
)
set(SFMLFULL
    ${CMAKE_SOURCE_DIR}/src/examples/sfmlfull.cpp
)
set(TESTSYSTEM
    ${CMAKE_SOURCE_DIR}/src/tests/testSystem.cpp
)
add_library(ecs SHARED ${ECS_LIST})
add_library(myecs ${ITEMS} )
if(DOSFML OR DOSFMLFULL)
    target_link_libraries(myecs ${SFML_LIBRARIES})
endif(DOSFML OR DOSFMLFULL)
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
endif(BUILD_DOCUMENTATION)
option(BUILD_EXAMPLES "Compile test programs" ON)
option(DOSFML "Compile test programs" OFF)
option(DOSFMLFULL "Compile full sfml program" OFF)
if(BUILD_EXAMPLES)
#add_definitions(-DCTEST)
    add_executable(simple ${SIMPLE})
    add_executable(bigger ${BIGGER})
    add_executable(manyents ${MANY})
    add_executable(bounding ${BOUNDS})
    target_link_libraries(simple ecs myecs)
    target_link_libraries(bigger ecs myecs)
    target_link_libraries(manyents ecs myecs)
    target_link_libraries(bounding ecs myecs)
    if(DOSFML)
      include_directories(${SFML_INCLUDE_DIR})
      add_executable(sfmlex1 ${SFMLEX1})
      target_link_libraries(sfmlex1 ${SFML_LIBRARIES} ecs myecs)
      add_executable(sfmlex2 ${SFMLEX2})
      target_link_libraries(sfmlex2 ${SFML_LIBRARIES} ecs myecs)
    endif(DOSFML)
    if(DOSFMLFULL)
          include_directories(${SFML_INCLUDE_DIR})
          add_executable(sfmlfull ${SFMLFULL})
          target_link_libraries(sfmlfull ${SFML_LIBRARIES} ecs myecs)
    endif(DOSFMLFULL)
endif(BUILD_EXAMPLES)
option(BUILD_TESTS "Compile tests" OFF)
if(BUILD_TESTS)
    add_definitions(-DUNITTEST)
    add_executable(test1 ${TESTS})
    add_executable(testSystem ${TESTSYSTEM})
    target_link_libraries(test1 ecs myecs -lgtest -lgtest_main)
    target_link_libraries(testSystem ecs myecs -lgtest -lgtest_main -lgmock -lgmock_main -lpthread)
endif(BUILD_TESTS)



