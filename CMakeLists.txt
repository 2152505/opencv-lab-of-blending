cmake_minimum_required( VERSION 3.5.1 )

project(lab_2_blending)


# Find libraries
find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME}
  main.cpp
  lab_2.h
  lab_2.cpp
  laplace_blending.h
  laplace_blending.cpp
  linear_blending.h
  linear_blending.cpp
  )

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_compile_options(${PROJECT_NAME} PRIVATE ${compiler_options})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON CXX_STANDARD 17)
