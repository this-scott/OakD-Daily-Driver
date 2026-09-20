# testing cmake build which seperates testing from main
add_executable(test_program test_dai.cpp)
# TODO(Immediate): setup a CMakeLists library in in src
target_link_libraries(test_program PRIVATE oakd_webcam)

add_test(NAME RunAllTests COMMAND test_program)
