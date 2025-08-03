add_library(BitStream
        BitStream.cpp
)
add_library(BS::BS ALIAS BitStream)

target_link_libraries(BitStream)

set(INCLUDES
        "${PROJECT_SOURCE_DIR}/include")


target_include_directories(BitStream
    PUBLIC
        ${INCLUDES}
)
