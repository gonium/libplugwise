# -*- mode: cmake; -*-

#set(hdrs 
#  common.hpp
#)
#install(FILES ${hdrs} DESTINATION include/plugwise)

configure_file(config.h.in ${CMAKE_BINARY_DIR}/config.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${Boost_INCLUDE_DIRS})
file(GLOB all_plugwise_src *.cpp *.hpp)
set(plugwise_src ${all_plugwise_src})
ADD_LIBRARY(plugwise ${plugwise_src})

target_link_libraries(plugwise ${Boost_IOSTREAMS_LIBRARY})

if(BUILD_SHARED_LIBS)
  install(TARGETS plugwise LIBRARY DESTINATION lib)
else(BUILD_SHARED_LIBS)
  install(TARGETS plugwise ARCHIVE DESTINATION lib)
endif(BUILD_SHARED_LIBS)

