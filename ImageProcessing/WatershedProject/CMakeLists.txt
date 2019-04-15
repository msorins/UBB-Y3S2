cmake_minimum_required(VERSION 3.12)
project(WatershedProject)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
add_executable(WatershedProject main.cpp UI/mainwindow.cpp UI/mainwindow.h UI/ui_mainwindow.h Filters/FilterInterface.h Filters/ColorFilterL1.h Filters/NegativeOfImage.h Filters/BitExtraction.h Filters/WindowOperation.h Filters/WaterShedFilter.h Filters/Contour.h  Filters/Erosion.h Filters/Dilation.h Filters/SmoothingMedianFilter.h Filters/Translation.h Filters/TranslationInvariance.h Filters/Skeleton.h Filters/RGBtoHSL.h Filters/HighPassFilter.h Utils/Utils.h)


# OpenCV section
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(WatershedProject ${OpenCV_LIBS})

# Qt5 section
set(QT_DIR /Users/so/Qt/5.12.0/clang_64/lib/cmake/Qt5Core/)
set(Qt5Widgets_DIR /Users/so/Qt/5.12.0/clang_64/lib/cmake/Qt5Widgets/)
set(Qt5OpenGL_DIR /Users/so/Qt/5.12.0/clang_64/lib/cmake/Qt5OpenGL/)
set(Qt5Multimedia_DIR /Users/so/Qt/5.12.0/clang_64/lib/cmake/Qt5Multimedia/)

set (CMAKE_INSTALL_PREFIX /Users/so/Qt/5.12.0/clang_64/lib/cmake/Qt5Core)
set(CMAKE_PREFIX_PATH /Users/so/Qt/5.12.0/clang_64/lib/cmake/Qt5Core)

find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5OpenGL REQUIRED )
find_package( Qt5Multimedia REQUIRED )

target_link_libraries(WatershedProject Qt5::Core Qt5::Widgets Qt5::Gui)


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
