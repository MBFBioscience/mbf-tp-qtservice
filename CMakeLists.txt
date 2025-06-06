################################################################################
cmake_minimum_required(VERSION 3.23.0)

################################################################################
# Project
################################################################################
project(mbf-tp-qtservice)

################################################################################
# Qt deps
################################################################################
find_package(Qt6 COMPONENTS Core Network REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${Qt6Core_INCLUDE_DIRS})
include_directories(${Qt6Network_INCLUDE_DIRS})
message(STATUS "QT INCLUDE DIRS : ${Qt6Core_INCLUDE_DIRS}")
message(STATUS "QT INCLUDE DIRS : ${Qt6Network_INCLUDE_DIRS}")

################################################################################
# Preprocessor definitions 
################################################################################
#add_definitions(-DXXXX)

################################################################################
# Files
################################################################################

list(APPEND QTSERVICE_FILES_SRC qtservice.cpp)
if(MSVC)
  list(APPEND QTSERVICE_FILES_SRC qtservice_win.cpp)
else()
  list(APPEND QTSERVICE_FILES_SRC qtservice_unix.cpp qtunixserversocket.cpp qtunixsocket.cpp)
endif()

list(APPEND QTSERVICE_FILES_HDR qtservice.h qtservice_qobjects.h qtservice_p.h)
if(MSVC)
  list(APPEND QTSERVICE_FILES_HDR qtservice_qobjects_win.h)
else()
  list(APPEND QTSERVICE_FILES_HDR qtservice_qobjects_unix.h qtunixsocket.h qtunixserversocket.h)
endif()

################################################################################
# Link libraries
################################################################################
add_library(${PROJECT_NAME} STATIC ${QTSERVICE_FILES_SRC})

################################################################################
# Build options
################################################################################
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (MSVC)
    add_definitions(-DUNICODE -D_UNICODE)
	add_compile_options(/permissive-)
	target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
	target_compile_options(${PROJECT_NAME} PUBLIC "/Zc:__cplusplus /permissive-")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /Zc:__cplusplus /permissive- ")
	string(APPEND CMAKE_CXX_FLAGS " /Zc:__cplusplus")
endif()

################################################################################
# Header file set
################################################################################
target_sources(${PROJECT_NAME} PUBLIC
	FILE_SET public_headers
	TYPE HEADERS
	FILES ${QTSERVICE_FILES_HDR}
)

################################################################################
# Build include directories
################################################################################
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

################################################################################
# Install target
################################################################################
install(TARGETS ${PROJECT_NAME}
		EXPORT ${PROJECT_NAME}-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		FILE_SET public_headers DESTINATION "include/qtservice"
)

################################################################################
# Export and install cmake configuration files
################################################################################
export(TARGETS ${PROJECT_NAME}
    NAMESPACE ${PROJECT_NAME}::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
)

install(EXPORT ${PROJECT_NAME}-targets
	FILE "${PROJECT_NAME}Config.cmake"
	NAMESPACE ${PROJECT_NAME}::
    DESTINATION "share/${PROJECT_NAME}"
)
