# Vectors
add_executable(Test_Vector Test_Vector.cpp)
target_link_libraries(Test_Vector
    gtest 
    gtest_main
)
add_test(Test_Vector Test_Vector)