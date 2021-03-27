# Vectors
add_executable(test_Vector test_Vector.cpp)
target_link_libraries(test_Vector
    gtest 
    gtest_main
    lumi_math
)
add_test(test_Vector test_Vector)