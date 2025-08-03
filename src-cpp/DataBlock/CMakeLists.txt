add_library(BLK
        DataBlock.cpp
        BLK_serialize.cpp
        DataBlockShared.cpp
)

target_link_libraries(BLK
        ZSTD
)
add_library(BLK::BLK ALIAS BLK)

set(INCLUDES
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/json/include"
        "${PROJECT_SOURCE_DIR}/rapidjson/include"
        "${PROJECT_SOURCE_DIR}/arc/zstd-1.4.5"
        "${PROJECT_SOURCE_DIR}/arc"
)

target_include_directories(BLK
        PUBLIC
        ${INCLUDES}
)

