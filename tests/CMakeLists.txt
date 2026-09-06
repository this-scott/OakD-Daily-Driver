# testing cmake build which seperates testing from main
add_executable(test_program test_dai.cpp)
target_link_libraries(test_program PRIVATE program)

add_test(NAME RunAllTests COMMAND test_program)
