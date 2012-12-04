# cmake required (http://www.cmake.org/)
#

cmake_minimum_required(VERSION 2.8)

project( Ivan_f C CXX )

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

include_directories( ${FELIB_DIR}/Include ${MAIN_DIR}/Include )

find_package( SDL REQUIRED )
message( ${SDL_INCLUDE_DIR} )
include_directories( ${SDL_INCLUDE_DIR} )

add_library( FeLib ${FELIB_LIST} )
target_link_libraries( FeLib ${SDL_LIBRARY} )
set_property( TARGET FeLib APPEND PROPERTY COMPILE_DEFINITIONS LINUX USE_SDL
	GCC LOCAL_STATE_DIR=\"${CMAKE_BINARY_DIR}/var/\"
	DATADIR=\"${CMAKE_SOURCE_DIR}/\" )


add_executable( Ivan ${SDL_LIBRARY} ${MAIN_LIST} )
target_link_libraries( Ivan  FeLib )
set_property( TARGET Ivan APPEND PROPERTY COMPILE_DEFINITIONS LINUX USE_SDL
	GCC LOCAL_STATE_DIR=\"${CMAKE_BINARY_DIR}/var/\"
	DATADIR=\"${CMAKE_SOURCE_DIR}/\" )
