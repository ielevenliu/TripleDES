set(SRC_LISTS TripleDES.c)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/library)
add_library(des_static STATIC ${SRC_LISTS})
add_library(des_shared SHARED ${SRC_LISTS})

set_target_properties(des_static PROPERTIES OUTPUT_NAME "TripleDES")
set_target_properties(des_shared PROPERTIES OUTPUT_NAME "TripleDES")
