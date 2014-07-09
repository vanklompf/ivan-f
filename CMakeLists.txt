# cmake required (http://www.cmake.org/)
#

cmake_minimum_required(VERSION 2.8)

project( Ivan_f C CXX )

# Check whether the compiler is x86 or x86_64
if( APPLE )
  # CMAKE_SYSTEM_PROCESSOR always returns i386 for x86 and x86_64 on Mac
  if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    set( BUILD_ARCH "x86_64" )
  elseif( CMAKE_SIZEOF_VOID_P EQUAL 4 AND CMAKE_SYSTEM_PROCESSOR STREQUAL "i386" )
    set( BUILD_ARCH "i386" )
  elseif( CMAKE_SIZEOF_VOID_P EQUAL 4 AND CMAKE_SYSTEM_PROCESSOR STREQUAL "ppc" )
    set( BUILD_ARCH "ppc" )
  else()
    set( BUILD_ARCH "Unknown" )
  endif()
elseif( WIN32 )
  # CMAKE_SYSTEM_PROCESSOR is not reliable under windows
  if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    set( BUILD_ARCH "x86_64" )
  elseif( CMAKE_SIZEOF_VOID_P EQUAL 4 )
    set( BUILD_ARCH "i386" )
  endif()
else()
  # CMAKE_SYSTEM_PROCESSOR is reliable for *nix
  if( CMAKE_SYSTEM_PROCESSOR MATCHES "i.86" )
    set( BUILD_ARCH "i386" )
  elseif( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" AND CMAKE_SIZEOF_VOID_P EQUAL 8)
    set( BUILD_ARCH "x86_64" )
  elseif( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" AND CMAKE_SIZEOF_VOID_P EQUAL 4 )
    set( BUILD_ARCH "x32" )
  else()
    set( BUILD_ARCH ${CMAKE_SYSTEM_PROCESSOR} )
  endif()
endif()

set( FELIB_DIR ${CMAKE_SOURCE_DIR}/FeLib/ )
set( MAIN_DIR ${CMAKE_SOURCE_DIR}/Main/ )

set( FELIB_LIST
	${FELIB_DIR}/Source/bitmap.cpp	
	${FELIB_DIR}/Source/config.cpp
	${FELIB_DIR}/Source/error.cpp
	${FELIB_DIR}/Source/feio.cpp
	${FELIB_DIR}/Source/felist.cpp
	${FELIB_DIR}/Source/femain.cpp
	${FELIB_DIR}/Source/femath.cpp
	${FELIB_DIR}/Source/festring.cpp
	${FELIB_DIR}/Source/fetime.cpp
	${FELIB_DIR}/Source/graphics.cpp
	${FELIB_DIR}/Source/hscore.cpp
	${FELIB_DIR}/Source/save.cpp
	${FELIB_DIR}/Source/rawbit.cpp
	${FELIB_DIR}/Source/whandler.cpp
)

FILE( GLOB FELIB_HEADERS ${FELIB_DIR}/Include/*.h )
set ( FELIB_LIST ${FELIB_LIST} ${FELIB_HEADERS} )

set( MAIN_LIST
	${MAIN_DIR}/Source/actset.cpp
	${MAIN_DIR}/Source/areaset.cpp
	${MAIN_DIR}/Source/charset.cpp
	${MAIN_DIR}/Source/charsset.cpp
	${MAIN_DIR}/Source/command.cpp
	${MAIN_DIR}/Source/coreset.cpp
	${MAIN_DIR}/Source/dataset.cpp
	${MAIN_DIR}/Source/dungeon.cpp
	${MAIN_DIR}/Source/game.cpp 
	${MAIN_DIR}/Source/godset.cpp
	${MAIN_DIR}/Source/iconf.cpp 
	${MAIN_DIR}/Source/id.cpp 
	${MAIN_DIR}/Source/igraph.cpp
	${MAIN_DIR}/Source/itemset.cpp
	${MAIN_DIR}/Source/levelset.cpp
	${MAIN_DIR}/Source/main.cpp
	${MAIN_DIR}/Source/materset.cpp
	${MAIN_DIR}/Source/message.cpp
	${MAIN_DIR}/Source/object.cpp
	${MAIN_DIR}/Source/roomset.cpp
	${MAIN_DIR}/Source/script.cpp
	${MAIN_DIR}/Source/slotset.cpp
	${MAIN_DIR}/Source/trapset.cpp
	${MAIN_DIR}/Source/wmapset.cpp
	${MAIN_DIR}/Source/wskill.cpp
)

FILE( GLOB MAIN_HEADERS ${MAIN_DIR}/Include/*.h )
set ( MAIN_LIST ${MAIN_LIST} ${MAIN_HEADERS} )

include_directories( ${FELIB_DIR}/Include ${MAIN_DIR}/Include )

if( WIN32 )
  set( SDL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/SDL-VC/ )
  include_directories( ${SDL_PATH}/include )
  
  if( ${BUILD_ARCH} STREQUAL "i386" )
	  set( SDL_LIBRARY ${SDL_PATH}/lib/x86/SDL.lib ${SDL_PATH}/lib/x86/SDLmain.lib )
  else()
	  set( SDL_LIBRARY ${SDL_PATH}/lib/x64/SDL.lib ${SDL_PATH}/lib/x64/SDLmain.lib )
  endif()
else()
  find_package( SDL REQUIRED )
  include_directories( ${SDL_INCLUDE_DIR} )
endif()

add_library( FeLib ${FELIB_LIST} )
target_link_libraries( FeLib ${SDL_LIBRARY} )
set_property( TARGET FeLib APPEND PROPERTY COMPILE_DEFINITIONS USE_SDL
	LOCAL_STATE_DIR=\"${CMAKE_BINARY_DIR}/var/\"
	IVAN_DATADIR=\"${CMAKE_SOURCE_DIR}/\" )


add_executable( Ivan ${MAIN_LIST} )
target_link_libraries( Ivan  FeLib ${SDL_LIBRARY} )
set_property( TARGET Ivan APPEND PROPERTY COMPILE_DEFINITIONS USE_SDL
	LOCAL_STATE_DIR=\"${CMAKE_BINARY_DIR}/var/\"
	IVAN_DATADIR=\"${CMAKE_SOURCE_DIR}/\" )
