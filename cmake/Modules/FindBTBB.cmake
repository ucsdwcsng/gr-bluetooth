# Try to find the libbtbb library
#
# Once done this defines:
#  LIBBTBB_FOUND - system has libbtbb
#  LIBBTBB_INCLUDE_DIR - the libbtbb include directory
#  LIBBTBB_LIBRARIES - Link these to use libbtbb
#
# Copyright (c) 2013  Dominic Spill


if (LIBBTBB_INCLUDE_DIR AND LIBBTBB_LIBRARIES)

  # in cache already
  set(LIBBTBB_FOUND TRUE)

else (LIBBTBB_INCLUDE_DIR AND LIBBTBB_LIBRARIES)
  IF (NOT WIN32)
    # use pkg-config to get the directories and then use these values
    # in the FIND_PATH() and FIND_LIBRARY() calls
    find_package(PkgConfig)
    pkg_check_modules(PC_LIBBTBB QUIET libbtbb)
  ENDIF(NOT WIN32)

  FIND_PATH(LIBBTBB_INCLUDE_DIR
    NAMES btbb.h
    HINTS $ENV{LIBBTBB_DIR}/include ${PC_LIBBTBB_INCLUDEDIR}
    PATHS /usr/include /usr/local/include /usr/include/libbtbb
    /usr/local/include/libbtbb
    /usr/include ${CMAKE_SOURCE_DIR}/../libbtbb/src
    /opt/local/include/libbtbb
    ${LIBBTBB_INCLUDE_DIR}
  )

  set(libbtbb_library_names btbb)

  FIND_LIBRARY(LIBBTBB_LIBRARIES
    NAMES ${libbtbb_library_names}
    HINTS $ENV{LIBBTBB_DIR}/lib ${PC_LIBBTBB_LIBDIR}
    PATHS /usr/local/lib /usr/lib /opt/local/lib ${PC_LIBBTBB_LIBDIR}
    ${PC_LIBBTBB_LIBRARY_DIRS} ${CMAKE_SOURCE_DIR}/../libbtbb/src
  )

  if(LIBBTBB_INCLUDE_DIR)
    set(CMAKE_REQUIRED_INCLUDES ${LIBBTBB_INCLUDE_DIR})
  endif()

  if(LIBBTBB_LIBRARIES)
    set(CMAKE_REQUIRED_LIBRARIES ${LIBBTBB_LIBRARIES})
  endif()

  include(FindPackageHandleStandardArgs)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(BTBB DEFAULT_MSG LIBBTBB_LIBRARIES LIBBTBB_INCLUDE_DIR)

  MARK_AS_ADVANCED(LIBBTBB_INCLUDE_DIR LIBBTBB_LIBRARIES)

endif (LIBBTBB_INCLUDE_DIR AND LIBBTBB_LIBRARIES)