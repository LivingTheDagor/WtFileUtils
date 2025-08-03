add_library(FS
        FSObject.cpp
        Directory.cpp
        File.cpp
)

add_library(FS::FS ALIAS FS)

set(INCLUDES
        "${PROJECT_SOURCE_DIR}/include"
)

target_include_directories(FS
        PUBLIC
        ${INCLUDES}
)

