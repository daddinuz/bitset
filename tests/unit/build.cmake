add_executable(describe ${CMAKE_CURRENT_LIST_DIR}/describe.c)
target_link_libraries(describe PRIVATE bitset traits-unit)

add_test(describe describe)
enable_testing()
