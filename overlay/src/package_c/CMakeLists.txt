cmake_minimum_required(VERSION 3.8)
project(package_c)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(package_a REQUIRED)
find_package(package_b REQUIRED)

add_library(${PROJECT_NAME}
  src/package_c.cpp
)
ament_target_dependencies(${PROJECT_NAME}
  PUBLIC
  package_b
  package_a
)

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

ament_export_targets(${PROJECT_NAME}Targets)
ament_export_dependencies(package_a package_b)

ament_package()
