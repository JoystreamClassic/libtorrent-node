cmake_minimum_required(VERSION 3.2)

project (torrent_node_static)

include(conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#node or electron development headers
include_directories(${CMAKE_JS_INC})

# cmake-js cannot find the nan headers when our package is installed
# in parallel to it. This happens when pacakge is being installed as
# a dependency as opposed to just running npm install inside the package
include_directories("../nan/")

file(GLOB LIBTORRENT_SOURCE_FILES "src/*.cpp")
list(REMOVE_ITEM LIBTORRENT_SOURCE_FILES "src/LibtorrentAddon.cpp")

# plain static lib for reuse
add_library(torrent_node_static STATIC ${LIBTORRENT_SOURCE_FILES})

# libtorrent node native addon
add_library(LibtorrentAddon SHARED "src/LibtorrentAddon.cpp")
set_target_properties(LibtorrentAddon PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(LibtorrentAddon torrent_node_static ${CONAN_LIBS} ${CMAKE_JS_LIB})

# link statically against visual c++ runtime so addon will not require redistribution of runtime
IF(MSVC)
  if ("${MSVC_RUNTIME}" STREQUAL "static")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
  endif ()
ENDIF(MSVC)
