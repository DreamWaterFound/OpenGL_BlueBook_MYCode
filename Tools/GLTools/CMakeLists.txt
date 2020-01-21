# 生成库文件
# CMAKE_CURRENT_SOURCE_DIR

set(LIBRARY_OUTPUT_PATH    ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-result -std=c++11")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wno-unused-result")

# 添加宏, 不过这个宏可能会和后面的一些内容发生冲突
add_definitions(-Dlinux)

# 头文件前面咱们已经查找过了, 现在就直接编译文件
file(GLOB GLTOOLS_SOURCE_FILES ${GLTOOLS_BASE_DIR}/src/*.*)
add_library(GLTools SHARED 
    ${GLTOOLS_SOURCE_FILES}
)



