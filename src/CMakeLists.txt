# -------------------------------------------------------------------

set(SRC_SOURCES
    main.c
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(${PROJECT_NAME} 
    ${SRC_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/Math
)

target_link_libraries(${PROJECT_NAME}
    # Math
    PRIVATE m
    # SDL2
    PRIVATE SDL2::SDL2
    PRIVATE SDL2_image::SDL2_image
)

# -------------------------------------------------------------------