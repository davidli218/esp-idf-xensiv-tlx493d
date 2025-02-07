file(GLOB_RECURSE SOURCES "src/*.c")

set(
    PRIVATE_INCLUDES
    "private_include"
    "private_include/models"
)

idf_component_register(
    SRCS "${SOURCES}"
    INCLUDE_DIRS "include"
    PRIV_INCLUDE_DIRS "${PRIVATE_INCLUDES}"
    REQUIRES driver
)

include(package_manager)
cu_pkg_define_version(${CMAKE_CURRENT_LIST_DIR})
