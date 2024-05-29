# -------------------------------------------------------------------

set(SRC_HEADERS)

set(SRC_SOURCES
    main.c
)

add_executable(${PROJECT_NAME} 
    ${SRC_HEADERS} 
    ${SRC_SOURCES}
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE src
)

target_link_libraries(${PROJECT_NAME} 
  PRIVATE m
)

# -------------------------------------------------------------------