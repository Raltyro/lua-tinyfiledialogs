cmake_minimum_required (VERSION 3.13)

### Basic compilation settings
set (CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set (CMAKE_CXX_STANDARD 14)

include_directories (
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

### Compiler-specific flags
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	add_compile_options ("-fvisibility=hidden")
	add_link_options ("-fvisibility=hidden")
endif ()

if (LOVR)
  set(LUA_LIBRARIES ${LOVR_LUA})
else()
### Dependencies
	find_package (LuaJIT)
	if (LUAJIT_FOUND)
		set(LUA_INCLUDE_DIR ${LUAJIT_INCLUDE_DIR})
		set(LUA_LIBRARIES ${LUAJIT_LIBRARY})
	else ()
		find_package (Lua 5.1 REQUIRED)
	endif ()

	include_directories (${LUA_INCLUDE_DIR})
endif ()

### "Libraries"
add_library (lua-tinyfiledialogs MODULE main.cpp)

add_library (tinyfiledialogs STATIC tinyfiledialogs.c)

### Flags
if (WIN32)
	target_link_libraries(lua-tinyfiledialogs ${LUA_LIBRARIES})
elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
	if (NOT IOS)
		# macOS needs -undefined dynamic_lookuph
		target_link_options(lua-tinyfiledialogs PRIVATE -undefined dynamic_lookup)
	else ()
		target_link_libraries(lua-tinyfiledialogs ${LUA_LIBRARIES})
	endif ()
elseif (ANDROID)
	target_link_libraries(lua-tinyfiledialogs ${LUA_LIBRARIES})
endif ()

set_target_properties(lua-tinyfiledialogs PROPERTIES PREFIX "")

target_link_libraries (lua-tinyfiledialogs tinyfiledialogs)

### Install target
install(TARGETS lua-tinyfiledialogs DESTINATION .)