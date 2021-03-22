# Configure with [fxsdk build-cg], which provide the
# toolchain file and module path of the fxSDK

cmake_minimum_required(VERSION 3.18)
project(AST3)

include(GenerateG1A)
include(GenerateG3A)
include(Fxconv)
find_package(Gint 2.1 REQUIRED)

include_directories(include)

add_custom_command(
	OUTPUT "${CMAKE_CURRENT_LIST_DIR}/src/setlevel.c"
	COMMENT "Generate src/setlevel.c"
	COMMAND python3 compile_levels.py
	WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
	DEPENDS compile_levels.py
	)
		
add_custom_command(
	OUTPUT
		"${CMAKE_CURRENT_LIST_DIR}/src/times.c"
		"${CMAKE_CURRENT_LIST_DIR}/include/define.h"
	COMMENT "Generate src/times.c & include/define.h"
	COMMAND sh generate_define.sh
	COMMAND python3 time.py
	WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
	DEPENDS time.py times.lvl generate_define.sh
	)

set(SOURCES
	src/collide.c
	src/drawlevel.c
	src/main.c
	src/menu.c
	src/save.c
	src/setlevel.c
	src/times.c)

set(ASSETS)
set(ASSETS_fx)
set(ASSETS_cg
	assets-cg/img/appear.png
	assets-cg/img/blackout.png
	assets-cg/img/chock.png
	assets-cg/img/chrono1.png
	assets-cg/img/chrono2.png
	assets-cg/img/coin.png
	assets-cg/img/damaged.png
	assets-cg/img/dead.png
	assets-cg/img/end.png
	assets-cg/img/endscreen.png
	assets-cg/img/ice.png
	assets-cg/img/key1.png
	assets-cg/img/key2.png
	assets-cg/img/medals.png
	assets-cg/img/menu.png
	assets-cg/img/new.png
	assets-cg/img/player.png
	assets-cg/img/solid.png
	assets-cg/img/speedrun.png
	assets-cg/img/switch.png)

set(FLAGS -Wall -Wextra -Os)

fxconv_declare_assets(${ASSETS} ${ASSETS_fx} ${ASSETS_cg} WITH_METADATA)

add_executable(${PROJECT_NAME} ${SOURCES} ${ASSETS} ${ASSETS_${FXSDK_PLATFORM}})
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
target_link_libraries(${PROJECT_NAME} Gint::Gint)

generate_g3a(TARGET ${PROJECT_NAME} OUTPUT "${PROJECT_NAME}.g3a"
	NAME "${PROJECT_NAME}" ICONS assets-cg/icon-uns.png assets-cg/icon-sel.png)
