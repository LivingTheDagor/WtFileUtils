add_executable(main
        main.cpp
)
target_link_libraries(main
        BS::BS
        BLK::BLK
        READER::READER
)
