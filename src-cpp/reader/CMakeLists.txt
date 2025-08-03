add_library(READER
        Readers.cpp
)

target_link_libraries(READER
        ZSTD
)
add_library(READER::READER ALIAS READER)

set(INCLUDES
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/arc/zstd-1.4.5"
        "${PROJECT_SOURCE_DIR}/arc"
)

target_include_directories(READER
        PUBLIC
        ${INCLUDES}
)

