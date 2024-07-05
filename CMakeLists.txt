cmake_minimum_required(VERSION 3.28)

project (H4_engine)

set (GAME_EXECUTABLE_NAME "game")
set (DEDICATED_SERVER_EXECUTABLE_NAME "dedicated_server")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof")

include_directories(${CMAKE_SOURCE_DIR}/engine)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/engine/*.cpp)

add_subdirectory(external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
add_subdirectory(external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
add_subdirectory(external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
add_subdirectory(external/assimp ${CMAKE_CURRENT_BINARY_DIR}/assimp)
add_subdirectory(external/stb_image ${CMAKE_CURRENT_BINARY_DIR}/stb_image)

set(FMOD_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/fmod/inc")
set(FMOD_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/external/fmod/lib/fmod.dll")

add_custom_target(copy_resources
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
)

add_definitions(-D GLM_ENABLE_EXPERIMENTAL)

### GAME
add_executable(${GAME_EXECUTABLE_NAME} ${SOURCES})

add_dependencies(${GAME_EXECUTABLE_NAME} copy_resources)

find_package(SDL2 REQUIRED)
find_package(Freetype REQUIRED)
target_include_directories(${GAME_EXECUTABLE_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${FMOD_INCLUDE_DIRS})

target_link_libraries(${GAME_EXECUTABLE_NAME} PUBLIC ${SDL2_LIBRARIES} ${FREETYPE_LIBRARIES} ${FMOD_LIBRARIES} spdlog glad glm stb_image assimp) 
target_include_directories(${GAME_EXECUTABLE_NAME} PRIVATE ${GAME_EXECUTABLE_NAME})
target_include_directories(${GAME_EXECUTABLE_NAME} PUBLIC "${PROJECT_BINARY_DIR}")

add_custom_command(TARGET ${GAME_EXECUTABLE_NAME} POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy -t "$<TARGET_FILE_DIR:${GAME_EXECUTABLE_NAME}>" "$<TARGET_RUNTIME_DLLS:${GAME_EXECUTABLE_NAME}>" 
  COMMAND_EXPAND_LISTS
)

### DEDICATED SERVER

add_executable(${DEDICATED_SERVER_EXECUTABLE_NAME} ${SOURCES})
target_compile_definitions(${DEDICATED_SERVER_EXECUTABLE_NAME} PRIVATE DEDICATED_SERVER=1)

add_dependencies(${DEDICATED_SERVER_EXECUTABLE_NAME} copy_resources)

target_link_libraries(${DEDICATED_SERVER_EXECUTABLE_NAME} PUBLIC spdlog glm stb_image assimp) 
target_include_directories(${DEDICATED_SERVER_EXECUTABLE_NAME} PRIVATE ${DEDICATED_SERVER_EXECUTABLE_NAME})
target_include_directories(${DEDICATED_SERVER_EXECUTABLE_NAME} PUBLIC "${PROJECT_BINARY_DIR}")

add_custom_command(TARGET ${DEDICATED_SERVER_EXECUTABLE_NAME} POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy -t "$<TARGET_FILE_DIR:${DEDICATED_SERVER_EXECUTABLE_NAME}>" "$<TARGET_RUNTIME_DLLS:${DEDICATED_SERVER_EXECUTABLE_NAME}>" 
  COMMAND_EXPAND_LISTS
)
###
