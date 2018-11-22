CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

PROJECT(mu-image)

SET(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

ADD_EXECUTABLE(mu-image
    src/main.cpp
    src/muimage.cpp
    src/mainwindow.cpp
    src/image.cpp
    src/selection.cpp
    resources/mu-image.qrc
)

target_link_libraries(mu-image
    Qt5::Widgets
)
