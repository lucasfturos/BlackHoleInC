# -------------------------------------------------------------------

set(SRC_HEADERS
    Common/util.h
    Common/Math/math_utils.h
    Vec/vec2.h
    Vec/vec3.h
    Vec/vec4.h
)

set(SRC_SOURCES
    Common/Math/math_utils.c
    # Vec/vec3.c
    # Vec/vec4.c    
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