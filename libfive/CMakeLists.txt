# Sanity-checking to make sure CMake was run against the correct directory
if (NOT DEFINED LIBFIVE_BUILD_FROM_ROOT)
    message(FATAL_ERROR "CMake must be called against top-level directory")
endif()

option(BUILD_TESTS "Build test suite" ON)

add_subdirectory(src)

if (BUILD_TESTS)
  add_subdirectory(test)
endif(BUILD_TESTS)

if (BUILD_GUILE_BINDINGS AND GUILE_FOUND)
    add_subdirectory(bind)
endif(BUILD_GUILE_BINDINGS AND GUILE_FOUND)

if(UNIX AND NOT(APPLE))
    set(DEST_DIR "${CMAKE_INSTALL_PREFIX}")
    CONFIGURE_FILE("libfive.pc.in" "libfive.pc" @ONLY)
    install(FILES ${CMAKE_BINARY_DIR}/libfive/libfive.pc DESTINATION lib/pkgconfig)
endif(UNIX AND NOT(APPLE))
