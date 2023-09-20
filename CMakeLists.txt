cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
cmake_policy(SET CMP0057 NEW)

project ("small mods")

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)

#curly-eureka
include(C:\\Users\\Lenovo\\source\\curly-eureka\\CURLY-EUREKA-INCL.cmake)

macro(setupMod a_name)
	file(GLOB_RECURSE ${a_name}-src src/${a_name}* private_code/${a_name}*)
	add_library(${a_name} SHARED ${${a_name}-src} ${curly_eureka_src})
endmacro()

setupMod(logoAnim)
setupMod(cocosTrailBugFix)
setupMod(EditorHacks)
setupMod(btnSFX)
setupMod(RandomizeMenuMusic)
setupMod(GarageHacks)
setupMod(setUrlHook)
setupMod(clickerBase)
setupMod(ForceTextureQuality)
setupMod(dailyAndWeeklyInMenuLayer)
setupMod(noAnimForExtraItems)
setupMod(SpiderOrbAndPad)
setupMod(FUHD_SCALE_FACTOR)
setupMod(iconsPatch)