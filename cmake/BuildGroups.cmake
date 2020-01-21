
# 用于定义编译一组文件的宏
macro(build_groups TARGET_NAME CHAPTER_NUM)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/Chapter${CHAPTER_NUM})

# 获取所有文件
file(GLOB Ch${CHAPTER_NUM}_${TARGET_NAME}_SOURCE_FILES 
    ${CMAKE_SOURCE_DIR}/src/Chapter${CHAPTER_NUM}/${TARGET_NAME}/*.cpp 
    ${CMAKE_SOURCE_DIR}/src/Chapter${CHAPTER_NUM}/${TARGET_NAME}/*.c 
    ${CMAKE_SOURCE_DIR}/src/Chapter${CHAPTER_NUM}/${TARGET_NAME}/*.cc
    ${CMAKE_SOURCE_DIR}/src/Chapter${CHAPTER_NUM}/${TARGET_NAME}/*.cxx)

# 处理media, 最后面不要加/
set(Ch${CHAPTER_NUM}_${TARGET_NAME}_MEDIA_FILES
    ${PROJECT_SOURCE_DIR}/media/Chapter${CHAPTER_NUM}/${TARGET_NAME}
)
# add_definitions(-DMEDIA_PATH="${Ch${CHAPTER_NUM}_${TARGET_NAME}_MEDIA_FILES}")

# 默认包含自己的头文件
include_directories(${SRC_PATH})
# 构建工程
add_executable(Ch${CHAPTER_NUM}_${TARGET_NAME} ${Ch${CHAPTER_NUM}_${TARGET_NAME}_SOURCE_FILES})
target_link_libraries(Ch${CHAPTER_NUM}_${TARGET_NAME} ${LINK_LIBS})
  
endmacro(build_groups)