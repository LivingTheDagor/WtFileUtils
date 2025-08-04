add_library(VROMFS
        VROMFs.cpp
)

target_link_libraries(VROMFS
        ZSTD::ZSTD
)
add_library(VROMFS::VROMFS ALIAS VROMFS)

set(INCLUDES
        "${BASE_DIR}/src/include"
        "${BASE_DIR}/3rdParty/arc/zstd-1.4.5"
        "${BASE_DIR}/3rdParty/arc"
)

target_include_directories(VROMFS
        PUBLIC
        ${INCLUDES}
)

