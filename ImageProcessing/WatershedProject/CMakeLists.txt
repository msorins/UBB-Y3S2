cmake_minimum_required(VERSION 3.12)
project(WatershedProject)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
add_executable(WatershedProject main.cpp UI/mainwindow.cpp UI/mainwindow.h UI/ui_mainwindow.h Filters/FilterInterface.h Filters/ColorFilterL1.h Filters/ColorFilterL1V2.h  Filters/WaterShedFilter.h  Utils/Utils.h)


# OpenCV section
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(WatershedProject ${OpenCV_LIBS})

# Qt5 section
set(QT_DIR /Users/so/Qt5.12.0/5.12/clang_64/lib/cmake/Qt5Core/)
set(Qt5Widgets_DIR /Users/so/Qt5.12.0/5.12/clang_64/lib/cmake/Qt5Widgets/)
set(Qt5OpenGL_DIR /Users/so/Qt5.12.0/5.12/clang_64/lib/cmake/Qt5OpenGL/)
set(Qt5Multimedia_DIR /Users/so/Qt5.12.0/5.12/clang_64/lib/cmake/Qt5Multimedia/)
set(Qt5Charts_DIR /Users/so/Qt5.12.0/5.12/clang_64/lib/cmake/Qt5Chartse/)

set (CMAKE_INSTALL_PREFIX /Users/so/Qt5.12.0/5.12/clang_64/lib/cmake/Qt5Core)
set(CMAKE_PREFIX_PATH /Users/so/Qt5.12.0/5.12/clang_64/lib/cmake/Qt5Core)

find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5OpenGL REQUIRED )
find_package( Qt5Multimedia REQUIRED )
find_package( Qt5Charts REQUIRED )

target_link_libraries(WatershedProject Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Charts)


# Boost Section
set(Boost_NO_SYSTEM_PATHS TRUE)
if (Boost_NO_SYSTEM_PATHS)
    set(BOOST_ROOT "/usr/local/")
    set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
    set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
endif (Boost_NO_SYSTEM_PATHS)
find_package(Boost REQUIRED regex date_time system filesystem thread graph program_options)
include_directories(${BOOST_INCLUDE_DIRS})
target_link_libraries(WatershedProject  ${Boost_LIBRARIES})
