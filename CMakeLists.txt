project( talker )
cmake_minimum_required( VERSION 2.8 )

# remove compiler checks if you are using VS2010, it supports
#   1. auto
#   2. lambda
#   3. const iterator
# and, sadly, it doesn't support `for(item, cotainer)'
include( CheckCXXCompilerFlag )
check_cxx_compiler_flag( "-std=c++11"   COMPILER_SUPPORTS_CXX11 )
check_cxx_compiler_flag( "-std=c++0x"   COMPILER_SUPPORTS_CXX0X )
if( COMPILER_SUPPORTS_CXX11 )
    if( CMAKE_COMPILER_IS_GNUCXX )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11" )
    else()
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
    endif()
elseif( COMPILER_SUPPORTS_CXX0X)
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )
else()
    # MSVC, On by default (if available)
endif()
find_package( Boost 1.54.0
  REQUIRED unit_test_framework system regex date_time thread filesystem
  program_options chrono atomic log)
aux_source_directory(/Users/aadebuger/ros_catkin_wsindigo/src/roscpp_core/rostime/src  rostime )

aux_source_directory(/Users/aadebuger/ros_catkin_wsindigo/src/roscpp_core/cpp_common/src  cpp_common )


aux_source_directory(/Users/aadebuger/ros_catkin_wsindigo/src/roscpp_core/roscpp_serialization/src  roscpp_serialization )


aux_source_directory(/Users/aadebuger/ros_catkin_wsindigo/src/ros_comm/roscpp/src/libros  libros )


aux_source_directory(/Users/aadebuger/ros_catkin_wsindigo/src/ros_comm/roscpp/src/libros/transport  librostransport )

#aux_source_directory(/Users/aadebuger/ros_catkin_wsindigo/src/ros_comm/rosconsole/src/rosconsole rosconsole )

file(GLOB_RECURSE rosconsole "/Users/aadebuger/ros_catkin_wsindigo/src/ros_comm/rosconsole/src/rosconsole/*.cpp" )

list(REMOVE_ITEM rosconsole  "/Users/aadebuger/ros_catkin_wsindigo/src/ros_comm/rosconsole/src/rosconsole/impl/rosconsole_glog.cpp")


aux_source_directory(/Users/aadebuger/ros_catkin_wsindigo/src/ros_comm/xmlrpcpp/src  xmlrpcpp )


#/Users/aadebuger/Documents/github/console_bridge/src

#aux_source_directory( ${CMAKE_SOURCE_DIR}/dep/rosconsole_bridge/src  rosconsole_bridge )
aux_source_directory( /Users/aadebuger/Documents/github/console_bridge/src rosconsole_bridge )




set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package (Log4CXX REQUIRED)    

if (LOG4CXX_FOUND)
#	ADD_DEFINITIONS(-DWITH_LOG4CXX)
	include_directories(${LOG4CXX_INCLUDE_DIR})
	message("Logging to file   : yes")
else()
#	set(LOG4CXX_LIBRARIES "")
	message("Logging to file   : no (install log4cxx-devel)")
endif()

add_library( rostimelib  ${rostime} ${roscpp_serialization}  ${cpp_common}) 

add_library( libroslib  ${libros}  ${librostransport} ${rosconsole}  ${rosconsole_bridge} ) 

add_library( xmlrpcpplib  ${xmlrpcpp} ) 


include_directories( ${Boost_INCLUDE_DIR} )
include_directories( /Users/aadebuger/ros_catkin_wsindigo/install_isolated/include )

add_executable( ${PROJECT_NAME} main.cpp )
target_link_libraries( ${PROJECT_NAME} rostimelib libroslib  xmlrpcpplib ${Boost_LIBRARIES} ${LOG4CXX_LIBRARIES})
