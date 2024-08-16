cmake_minimum_required(VERSION 3.10)
project(SokobanSolver VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 查找 SFML 和 TinyXML2 库
set(TinyXML2_DIR "/usr/local/lib/cmake/tinyxml2")  # 添加此行
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(TinyXML2 REQUIRED)

# 包含目录
include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(${TinyXML2_INCLUDE_DIRS})

# 检查必要的资源文件是否存在
set(SPRITES_FILE ${CMAKE_SOURCE_DIR}/res/sprites.png)
set(SPRITES_XML ${CMAKE_SOURCE_DIR}/res/sprites.xml)

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
 #   src/SpriteLoader.cpp
)

# 链接库
target_link_libraries(autoMap
    sfml-graphics
    sfml-window
    sfml-system
    ${TinyXML2_LIBRARIES}
)

# 创建资源目录
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources)

# 拷贝资源文件
add_custom_command(TARGET autoMap POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SPRITES_FILE} ${CMAKE_BINARY_DIR}/resources/sprites.png
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SPRITES_XML} ${CMAKE_BINARY_DIR}/resources/sprites.xml
)

# 设置目标输出路径
set_target_properties(autoMap PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# 添加编译选项（可选，增加调试信息）
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(autoMap PRIVATE -g)
endif()
