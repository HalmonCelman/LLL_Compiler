cmake_minimum_required(VERSION 3.25.0)

project(lllc VERSION 1.0)

set(lllc_INCLUDE_DIRECTORIES
Prepare/
Execute/
.
)

add_subdirectory(Prepare)
add_subdirectory(Execute)

add_executable(${PROJECT_NAME} ${lllc_SOURCE_FILES} main.cpp )

target_link_libraries(${PROJECT_NAME} Prepare)
target_link_libraries(${PROJECT_NAME} Execute)
target_include_directories(${PROJECT_NAME} PRIVATE ${lllc_INCLUDE_DIRECTORIES})


install(TARGETS ${PROJECT_NAME} DESTINATION bin)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)
