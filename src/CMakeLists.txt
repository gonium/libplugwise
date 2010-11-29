# -*- mode: cmake; -*-
set(pw-read_src pw-read.cpp)

include_directories(${CMAKE_SOURCE_DIR}/libplugwise 
                    ${CMAKE_CURRENT_SOURCE_DIR} 
                    ${Boost_INCLUDE_DIRS})
add_executable(pw-read ${pw-read_src})
#add_executable(foobar sourcetest.cpp)

# Link the executable 
target_link_libraries(pw-read plugwise ${Boost_IOSTREAMS_LIBRARY})

# add programs to the install target - do not install the hashbench benchmark program.
INSTALL(PROGRAMS 
  ${CMAKE_CURRENT_BINARY_DIR}/pw-read
  DESTINATION bin)

