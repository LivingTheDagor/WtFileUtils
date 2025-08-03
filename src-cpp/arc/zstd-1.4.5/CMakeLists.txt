

add_library(ZSTD STATIC
        common/debug.c
        common/entropy_common.c
        common/error_private.c
        common/fse_decompress.c
        common/pool.c
        common/threading.c
        common/xxhash.c
        common/zstd_common.c
        compress/fse_compress.c
        compress/hist.c
        compress/huf_compress.c
        compress/zstd_compress.c
        compress/zstd_compress_sequences.c
        compress/zstd_compress_superblock.c
        compress/zstd_double_fast.c
        compress/zstd_fast.c
        compress/zstd_lazy.c
        compress/zstd_ldm.c
        compress/zstd_opt.c
        decompress/huf_decompress.c
        decompress/zstd_ddict.c
        decompress/zstd_decompress.c
        decompress/zstd_decompress_block.c
        dictBuilder/cover.c
        dictBuilder/divsufsort.c
        dictBuilder/fastcover.c
        dictBuilder/zdict.c
)

target_include_directories(ZSTD
    PUBLIC
        "${PROJECT_SOURCE_DIR}/arc/zstd-1.4.5"
        "${PROJECT_SOURCE_DIR}/arc/zstd-1.4.5/common"
        "${PROJECT_SOURCE_DIR}/arc/zstd-1.4.5/compress"
        "${PROJECT_SOURCE_DIR}/arc/zstd-1.4.5/decompress"
        "${PROJECT_SOURCE_DIR}/arc/zstd-1.4.5/dictBuilder"
        "${PROJECT_SOURCE_DIR}/arc/zstd-1.4.5/legacy"
)