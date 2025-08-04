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
        "${BASE_DIR}/src/include"
        "${BASE_DIR}/src/rapidjson/include"
        "${BASE_DIR}/3rdParty/arc/zstd-1.4.5"
        "${BASE_DIR}/3rdParty/arc"
)

target_include_directories(BLK
        PUBLIC
        ${INCLUDES}
)

