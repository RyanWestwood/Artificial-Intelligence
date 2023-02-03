cmake_minimum_required(VERSION 3.0)
project(Test)

enable_testing()
add_executable(tester test.cpp)
add_test(Tester tester)