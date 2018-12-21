CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(mu-image)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(mu-image
    src/main.cpp
    src/muimage.cpp
    src/mainwindow.cpp
    src/image.cpp
    src/cropcommand.cpp
    src/scalecommand.cpp
    src/selection.cpp
    resources/mu-image.qrc
)

install(TARGETS mu-image
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)

# follow the freedesktop standard
install(PROGRAMS assets/mu-image.desktop
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications
)

install(PROGRAMS assets/mu-image-128.png
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/128x128/apps/
)

target_link_libraries(mu-image
    Qt5::Widgets
)
