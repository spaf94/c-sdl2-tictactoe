cmake_minimum_required(VERSION 2.8)

project(tictactoe)

# Set source and include folders
set(SRC_DIR "./src")
set(INC_DIR "./include")

include_directories(${INC_DIR})

# Set include files
set(INCLUDES
    ${INC_DIR}/internal.h
    ${INC_DIR}/tictactoe_ctx.h)

# Set source files
set(SOURCES
    ${SRC_DIR}/main.c
    ${SRC_DIR}/tictactoe_ctx.c)

add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES})
