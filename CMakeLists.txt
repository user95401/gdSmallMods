cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
cmake_policy(SET CMP0057 NEW)

project ("small mods")

#curly-eureka
file(GLOB_RECURSE curly-eureka-src ../curly-eureka/*.cpp)
set(curly-eureka-incl ../curly-eureka/minhook/include ../curly-eureka/gd.h/include ../curly-eureka/gd.h ../curly-eureka)
add_subdirectory(../curly-eureka/cocos-headers cocos-headers-build)
add_subdirectory(../curly-eureka/minhook minhook-build)

#logoAnim
file(GLOB_RECURSE logoAnim-src src/logoAnim*)
add_library(logoAnim SHARED ${logoAnim-src} ${curly-eureka-src})
target_include_directories(logoAnim PRIVATE ${curly-eureka-incl})
target_link_libraries(logoAnim minhook cocos2d)

#cocosTrailBugFix
file(GLOB_RECURSE cocosTrailBugFix-src src/cocosTrailBugFix*)
add_library(cocosTrailBugFix SHARED ${cocosTrailBugFix-src} ${curly-eureka-src})
target_include_directories(cocosTrailBugFix PRIVATE ${curly-eureka-incl})
target_link_libraries(cocosTrailBugFix cocos2d)

#EditorHacks
file(GLOB_RECURSE EditorHacks-src src/EditorHacks*)
add_library(EditorHacks SHARED ${EditorHacks-src} ${curly-eureka-src})
target_include_directories(EditorHacks PRIVATE ${curly-eureka-incl})
target_link_libraries(EditorHacks cocos2d)

#btnSFX
file(GLOB_RECURSE btnSFX-src src/btnSFX*)
add_library(btnSFX SHARED ${btnSFX-src} ${curly-eureka-src})
target_include_directories(btnSFX PRIVATE ${curly-eureka-incl})
target_link_libraries(btnSFX minhook cocos2d)