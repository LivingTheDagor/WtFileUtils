add_library(VROMFS
        VROMFs.cpp
)

target_link_libraries(VROMFS
        ZSTD
)
add_library(VROMFS::VROMFS ALIAS VROMFS)

set(INCLUDES
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/arc/zstd-1.4.5"
        "${PROJECT_SOURCE_DIR}/arc"
)

target_include_directories(VROMFS
        PUBLIC
        ${INCLUDES}
)

