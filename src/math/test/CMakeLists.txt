add_executable(math_test
    math_test.cpp
)
# add_dependencies(math_test IspcMathLib)
target_link_libraries(math_test LinearAlgebra)