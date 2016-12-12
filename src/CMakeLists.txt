SET(pwd ${CMAKE_CURRENT_LIST_DIR})

AUX_SOURCE_DIRECTORY(${pwd} src)
add_executable(dsquare ${src})
message(STATUS "dsquare added")

target_link_libraries(dsquare ${stdgl_libraries})
