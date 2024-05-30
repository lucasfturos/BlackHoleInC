# -------------------------------------------------------------------

set(SRC_SOURCES
    main.c
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} 
    ${SRC_SOURCES}
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE src
    PRIVATE ${SDL2_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE m
    PRIVATE ${SDL2_LIBRARIES}
)

# -------------------------------------------------------------------