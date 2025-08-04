add_library(FS
        FSObject.cpp
        Directory.cpp
        File.cpp
)

add_library(FS::FS ALIAS FS)

set(INCLUDES
        "${BASE_DIR}/src/include"
)

target_include_directories(FS
        PUBLIC
        ${INCLUDES}
)

