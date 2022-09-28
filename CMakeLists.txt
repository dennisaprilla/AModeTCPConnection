# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("AmodeTCPConnection")

# Boost library
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(BOOST_INCLUDEDIR "C:\\boost_1_80_0\\boost")
set(BOOST_LIBRARYDIR "C:\\boost_1_80_0\\stage\\lib")
set(BOOST_ROOT "C:\\boost_1_80_0")
find_package(Boost 1.80.0 COMPONENTS REQUIRED system filesystem)
include_directories(${Boost_INCLUDE_DIRS} )

# Opencv library
# Don't forget to put the C:\opencv\build\x64\vc15\bin to PATH
set(OpenCV_DIR "C:\\opencv\\build")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories( ${OpenCV_LIB_DIR} )

# set(OpenCV_STATIC ON)
# set(OpenCV_LIBS opencv_core460d opencv_imgcodecs460d)
# set(OpenCV_INCLUDE_DIRS "C:\\opencv-4.6.0\\build\\install\\include")
# set(OpenCV_LIB_DIR "C:\\opencv-4.6.0\\build\\install\\x64\\vc16\\lib")
# set(OpenCV_COMPUTE_CAPABILITIES "")
# set(OpenCV_ANDROID_NATIVE_API_LEVEL "")
# set(OpenCV_VERSION 4.6.0)
# set(OpenCV_VERSION_MAJOR 4)
# set(OpenCV_VERSION_MINOR 6)
# set(OpenCV_VERSION_PATCH 0)
# set(OpenCV_VERSION_STATUS "")
# set(OpenCV_SHARED ON)
# set(OpenCV_INSTALL_PATH "C:\\opencv-4.6.0\\build\\install")
# set(OpenCV_LIB_COMPONENTS opencv_world)
# set(OpenCV_USE_MANGLED_PATHS FALSE)
# set(OpenCV_VERSION_TWEAK 0)
# include_directories(${OpenCV_INCLUDE_DIRS})
# link_directories( ${OpenCV_LIB_DIR} )

# message(STATUS "OpenCV_LIBS = ${OpenCV_LIBS}")
# message(STATUS "OpenCV_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")
# message(STATUS "OpenCV_COMPUTE_CAPABILITIES = ${OpenCV_COMPUTE_CAPABILITIES}")
# message(STATUS "OpenCV_ANDROID_NATIVE_API_LEVEL = ${OpenCV_ANDROID_NATIVE_API_LEVEL}")
# message(STATUS "OpenCV_VERSION = ${OpenCV_VERSION}")
# message(STATUS "OpenCV_VERSION_MAJOR = ${OpenCV_VERSION_MAJOR}")
# message(STATUS "OpenCV_VERSION_MINOR = ${OpenCV_VERSION_MINOR}")
# message(STATUS "OpenCV_VERSION_PATCH = ${OpenCV_VERSION_PATCH}")
# message(STATUS "OpenCV_VERSION_STATUS = ${OpenCV_VERSION_STATUS}")
# message(STATUS "OpenCV_SHARED = ${OpenCV_SHARED}")
# message(STATUS "OpenCV_INSTALL_PATH = ${OpenCV_INSTALL_PATH}")
# message(STATUS "OpenCV_LIB_COMPONENTS = ${OpenCV_LIB_COMPONENTS}")
# message(STATUS "OpenCV_USE_MANGLED_PATHS = ${OpenCV_USE_MANGLED_PATHS}")
# message(STATUS "OpenCV_VERSION_TWEAK = ${OpenCV_VERSION_TWEAK}")

# TCLAP library (only headers, so no installation)
include_directories("C:\\tclap-1.4.0-rc1\\include")

# Our own include directory
include_directories(include)

# Include sub-projects.
add_subdirectory ("src")
add_subdirectory ("external/synch")
