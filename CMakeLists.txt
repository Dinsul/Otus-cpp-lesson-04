cmake_minimum_required(VERSION 3.2)

project(print_ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(Doxygen)

set(DOXYGEN_HAVE_DOT YES)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_PROJECT_LOGO "${CMAKE_SOURCE_DIR}/logo.svg")
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/doc")

#doxygen_add_docs(targetName
#    [filesOrDirs...]
#    [WORKING_DIRECTORY dir]
#    [COMMENT comment])

doxygen_add_docs(doc "${PROJECT_SOURCE_DIR}")

add_executable(${PROJECT_NAME} "${PROJECT_NAME}.hpp" "main.cpp")

add_executable(test_${PROJECT_NAME} "test_${PROJECT_NAME}.cpp" "${PROJECT_NAME}.hpp")

set_target_properties(${PROJECT_NAME} test_${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )

set_target_properties(test_${PROJECT_NAME} PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

target_link_libraries(test_${PROJECT_NAME}
    ${Boost_LIBRARIES}
    )

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dinsul2.0@gmail.com)

include (CPack)

enable_testing()

add_test(test_print test_${PROJECT_NAME})
