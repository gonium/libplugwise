# -*- mode: cmake; -*-

#set(hdrs 
#  common.hpp
#)
#install(FILES ${hdrs} DESTINATION include/plugwise)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${Boost_INCLUDE_DIRS})
file(GLOB all_plugwise_src *.cpp *.hpp)
set(plugwise_src ${all_plugwise_src})
ADD_LIBRARY(libplugwise ${plugwise_src})

target_link_libraries(libplugwise ${Boost_IOSTREAMS_LIBRARY})

if(BUILD_SHARED_LIBS)
  install(TARGETS libplugwise LIBRARY DESTINATION lib)
else(BUILD_SHARED_LIBS)
  install(TARGETS libplugwise ARCHIVE DESTINATION lib)
endif(BUILD_SHARED_LIBS)

