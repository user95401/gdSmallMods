﻿cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
cmake_policy(SET CMP0057 NEW)

project ("small mods")

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)

#curly-eureka
file(GLOB_RECURSE curly-eureka-src ../curly-eureka/*.cpp)
set(curly-eureka-incl ../curly-eureka/minhook/include ../curly-eureka/gd.h/include ../curly-eureka/gd.h ../curly-eureka)
add_subdirectory(../curly-eureka/cocos-headers cocos-headers-build)
add_subdirectory(../curly-eureka/minhook minhook-build)

macro(setupMod a_name)
	file(GLOB_RECURSE ${a_name}-src src/${a_name}*)
	add_library(${a_name} SHARED ${${a_name}-src} ${curly-eureka-src})
	target_include_directories(${a_name} PRIVATE ${curly-eureka-incl})
	target_link_libraries(${a_name} minhook cocos2d)
endmacro()

setupMod(logoAnim)
setupMod(cocosTrailBugFix)
setupMod(EditorHacks)
setupMod(btnSFX)
setupMod(RandomizeMenuMusic)
setupMod(GarageHacks)
setupMod(setUrlHook)
setupMod(clickerBase)
setupMod(iconsCount)
setupMod(dailyAndWeeklyInMenuLayer)