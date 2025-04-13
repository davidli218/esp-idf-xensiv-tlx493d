# Set core source files for TLx493D driver
set(tlx493d_core_srcs
    "tlx493d-arduino/src/tlx493d.c"
    "tlx493d-arduino/src/tlx493d_common.c"
    "tlx493d-arduino/src/tlx493d_gen_2_common.c"
    "tlx493d-arduino/src/tlx493d_gen_3_common.c"
    "tlx493d-arduino/src/TLx493D_A1B6.c"
    "tlx493d-arduino/src/TLx493D_A2B6.c"
    "tlx493d-arduino/src/TLx493D_A2BW.c"
    "tlx493d-arduino/src/TLx493D_W2B6.c"
    "tlx493d-arduino/src/TLx493D_W2BW.c"
    "tlx493d-arduino/src/TLx493D_P2B6.c"
    "tlx493d-arduino/src/TLx493D_P3B6.c"
    "tlx493d-arduino/src/TLx493D_P3I8.c"
)

# Set ESP-IDF platform-specific adaptation layer source files
set(tlx493d_esp_srcs
    "port/esp_tlx493d_com_interface.c"
    "port/esp_tlx493d_com_iic.c"
    "port/esp_tlx493d_logger.c"
)

# Set include paths visible to other components
SET(include_dirs
    "include"
    "port/include"
)

# Set include paths visible only to this component
SET(priv_include_dirs
    "tlx493d-arduino/src"
)


idf_component_register(
    SRCS ${tlx493d_core_srcs} ${tlx493d_esp_srcs}
    INCLUDE_DIRS ${include_dirs}
    PRIV_INCLUDE_DIRS ${priv_include_dirs}
    REQUIRES driver
)

include(package_manager)
cu_pkg_define_version(${CMAKE_CURRENT_LIST_DIR})
