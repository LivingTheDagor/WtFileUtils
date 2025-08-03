add_executable(VromfsTest
        main.cpp
)

# SET_TARGET_PROPERTIES(VromfsTest PROPERTIES LINK_FLAGS "/PROFILE")
target_link_libraries(VromfsTest
        # mimalloc-static
        BS::BS
        BLK::BLK
        READER::READER
        FS::FS
        VROMFS::VROMFS

)


# target_compile_definitions(VromfsTest PRIVATE MI_MALLOC_OVERRIDE)
# target_include_directories(VromfsTest PRIVATE mimalloc/include)