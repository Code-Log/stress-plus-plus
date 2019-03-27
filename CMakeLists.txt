cmake_minimum_required(VERSION 3.12)
project(Stress++)
set(CMAKE_CXX_STANDARD 17)

set(Stress_VERSION_MAJOR 0)
set(Stress_VERSION_MINOR 1)
set(Stress_VERSION_PATCH 2)

configure_file("${PROJECT_SOURCE_DIR}/StressConfig.h.in" "${PROJECT_BINARY_DIR}/StressConfig.h")
include_directories("${PROJECT_BINARY_DIR}")

add_executable(Stress++ main.cpp)
target_link_libraries(Stress++ pthread)

install(TARGETS Stress++ DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/StressConfig.h" DESTINATION include)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${Stress_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Stress_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${Stress_VERSION_PATCH}")
include(CPack)
