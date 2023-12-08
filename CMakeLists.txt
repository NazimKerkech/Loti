cmake_minimum_required(VERSION 3.27)
project(LoTI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
find_package( OpenCV REQUIRED )

add_executable(LoTI src/main.cpp "src/image.cpp" )

add_definitions(-DSOURCE_DIR="${CMAKE_SOURCE_DIR}")

target_link_libraries(LoTI
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( LoTI ${OpenCV_LIBS} )
