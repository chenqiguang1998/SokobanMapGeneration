cmake_minimum_required(VERSION 3.10)
project(SokobanSolver VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

# 设置 TinyXML2 路径
set(TINYXML2_DIR "${CMAKE_SOURCE_DIR}/tool/tinyxml2")

# 查找 SFML 库
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# 检查 TinyXML2 路径
if (EXISTS "${TINYXML2_DIR}/tinyxml2.h" AND EXISTS "${TINYXML2_DIR}/tinyxml2.cpp")
    message(STATUS "TinyXML2 found in ${TINYXML2_DIR}. Copying files.")
    
    # 复制头文件和源文件
    file(COPY "${TINYXML2_DIR}/tinyxml2.h" DESTINATION "${CMAKE_SOURCE_DIR}/inc")
    file(COPY "${TINYXML2_DIR}/tinyxml2.cpp" DESTINATION "${CMAKE_SOURCE_DIR}/src")
    
    # 额外设置 TinyXML2 源文件
    set(TINYXML2_SRC "${CMAKE_SOURCE_DIR}/src/tinyxml2.cpp")
else()
    message(FATAL_ERROR "TinyXML2 not found. Please download it from https://github.com/leethomason/tinyxml2")
endif()

# 包含目录
include_directories(${PROJECT_SOURCE_DIR}/inc)

# 检查必要的资源文件是否存在
set(SPRITES_FILE ${CMAKE_SOURCE_DIR}/res/sprites.png)
set(SPRITES_XML ${CMAKE_SOURCE_DIR}/res/sprites.xml)
set(PARSESTACK ${CMAKE_SOURCE_DIR}/parse_stack.sh)

if (NOT EXISTS ${SPRITES_FILE})
    message(FATAL_ERROR "Resource file not found: ${SPRITES_FILE}")
endif()

if (NOT EXISTS ${SPRITES_XML})
    message(FATAL_ERROR "Resource file not found: ${SPRITES_XML}")
endif()

# 添加可执行文件
add_executable(autoMap
    src/AutoGenerateSokobanLevel.cpp
    src/GenerateLevel.cpp
    src/Map.cpp
    src/pch.cpp
    src/Solver.cpp
    src/State.cpp
    src/StateNode.cpp
    src/SignalHandler.cpp
    src/SpriteLoader.cpp
    ${TINYXML2_SRC}  # 添加 TinyXML2 源文件
)

# 链接库
target_link_libraries(autoMap
    sfml-graphics
    sfml-window
    sfml-system
)

# 创建资源目录
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources)

# 拷贝资源文件
add_custom_command(TARGET autoMap POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SPRITES_FILE} ${CMAKE_BINARY_DIR}/resources/sprites.png
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SPRITES_XML} ${CMAKE_BINARY_DIR}/resources/sprites.xml
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PARSESTACK} ${CMAKE_BINARY_DIR}/parse_stack.sh
)

# 设置目标输出路径
set_target_properties(autoMap PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# 添加编译选项和宏定义
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(autoMap PRIVATE -g3 -ggdb)
    target_compile_definitions(autoMap PRIVATE DEBUG_MODE)
endif()
