cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(OpenGL_Study)

# 设置编译标志
set(CMAKE_CXX_FLAGS   "${CMAKE_CXX_FLAGS} -fpermissive")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
list(APPEND LINK_LIBS ${OPENGL_LIBRARIES} GL rt dl)

# GLUT
set(FREEGLUT_BASE_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/freeglut-3.0.0")
include_directories(${FREEGLUT_BASE_DIR}/include)
link_directories(${FREEGLUT_BASE_DIR}/lib)
list(APPEND LINK_LIBS glut)

# GLEW
set(GLEW_BASE_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/glew-2.1.0")
include_directories(${GLEW_BASE_DIR}/include/GL)
link_directories(${GLEW_BASE_DIR}/lib)
list(APPEND LINK_LIBS glfw)

# GLTools
set(GLTOOLS_BASE_DIR "${CMAKE_SOURCE_DIR}/Tools/GLTools")
include_directories(${GLTOOLS_BASE_DIR}/GLTools)
include_directories(${GLTOOLS_BASE_DIR}/include)
add_subdirectory(${GLTOOLS_BASE_DIR})
list(APPEND LINK_LIBS GLTools)

# 设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/lib)

# 添加需要编译的子文件夹
include(BuildGroups)

# 注意添加引号, 不然只能够传递列表的第一项
# 第一章
build_groups(Block                  "01")

# 第二章 
build_groups(Triangle               "02")
build_groups(Move                   "02")
build_groups(Bounce                 "02")

# 第三章
build_groups(Primitives             "03")
build_groups(GeoTest                "03")
build_groups(Scissor                "03")
build_groups(Blending               "03")
build_groups(Smoother               "03")

# 第四章
build_groups(Move                   "04")
build_groups(Objects                "04")
build_groups(OrthoGraphic           "04")
build_groups(Perspective            "04")
build_groups(ModelViewProjection    "04")
build_groups(SphereWorld            "04")
build_groups(SphereWorld2           "04")
build_groups(SphereWorld3           "04")
build_groups(SphereWorld4           "04")


