# -------------------------------------------------------------------

set(SRC_SOURCES
    main.c
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(${PROJECT_NAME} 
    ${SRC_SOURCES}
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE src
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE m
    PRIVATE SDL2::SDL2
    PRIVATE SDL2_image::SDL2_image
)

# -------------------------------------------------------------------