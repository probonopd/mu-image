CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

PROJECT(mu-image)

SET(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)

ADD_EXECUTABLE(mu-image
    src/main.cpp
    src/muimage.cpp
    src/mainwindow.cpp
)

target_link_libraries(mu-image
    Qt5::Widgets
)
