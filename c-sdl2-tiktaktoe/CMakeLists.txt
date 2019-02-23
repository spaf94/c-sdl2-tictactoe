cmake_minimum_required(VERSION 2.8)

project(tiktaktoe)

# Set source and include folders
set(SRC_DIR "src")
set(INC_DIR "include")

# Set include files
set(INCLUDES
    ${INC_DIR}/internal.h
    ${INC_DIR}/tiktaktoe_ctx.h)

# Set source files
set(SOURCES
    ${SRC_DIR}/main.c
    ${SRC_DIR}/tiktaktoe_ctx.c)

add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES})
