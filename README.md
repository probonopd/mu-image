# Mu-Image

A minimal bitmap image editor for beginner programmers.

## Introduction

Mu-Image allows to resize and crop images downloaded from the web and prepare them for the use in games.  
It can also add transparency to an image.

It does not allow to create new images nor tweak them.

For more complex tasks there are other free software projects that can be helpful to you:

- [Gimp](https:://gimp.org) for image editing.
- [Inkscape](https://inkscape.org) for vector drawing.
- [MyPaint](https://mypaint.org) for simple digital painting.
- [Krita](https://krita.org) for professional digital painting.

For the future, I'm considering creating a vector drawing program on par with the one in Scratch 3.0 (Mu-Draw?).

## Features

- Open existing PNGs.
- Only one file at a time. Opening a new file, closes the old one.
- Save to PNG (no question asked).
- Resize the image size (to a pixel count or a %)
- Crop with a visual rectangle selection (optionally with a fixed size selection).
- Pick the transparency color.

Possible features:

- Open JPGs (and convert to PNGs on save)
- Save as (mandatory for the confirmation? with the current file name as the default?)

## Resources

- Resize icon inspired by <https://openclipart.org/detail/304895/resize-icon>
- Crop icon inspired by <https://openclipart.org/detail/196865/mono-crop>
- Ghost icon inspired by <https://openclipart.org/detail/17847/cartoon-ghost>

Read chapter 5 of "Hands-on GUI programming with C++ and Qt5" for ideas on scaling and cropping an image.

## How-to

- Adding custom (`MainWindow`) slots in Qt Designer:
  - Go into "Edit Signal / Slot" mode.
  - Create a connection for any UI item.
  - Click on "Edit" for "MainWindow" and add slots that are definedin `mainwindow.h`.
- Creating an image viewer: http://doc.qt.io/qt-5/qtwidgets-widgets-imageviewer-example.html
## Todo

- [x] add a toolbar:
  - http://doc.qt.io/qt-5/designer-creating-mainwindows.html#toolbars
  - load, save, resize, crop, transparency, help, quit (zoom in and out?)
- [x] make the toolbar wider / the icons bigger
- [x] Make the toolbar and side panels not movable
- [x] read the main window from a `.ui` file
  - old qt manual: <https://wiki.qt.io/Using_CMake_build_system>
  - new cmake manual: <https://cmake.org/cmake/help/v3.0/manual/cmake-qt.7.html#manual:cmake-qt(7)>
  - a sample qt app with ui files: <https://doc-snapshots.qt.io/qt5-5.9/gettingstartedqt.html>
  - use the images icon from ui-editor as the icon for the application? (with a red border...)
- [x] load an image into the central widget.
- [x] find the right policy for the initial image size on screen.
- [ ] zoom in and out.
  - [x] make the zoom work
  - [ ] disable the zoom when it's too big or too small
  - [ ] mouse wheel?
    - https://stackoverflow.com/questions/19113532/qgraphicsview-zooming-in-and-out-under-mouse-position-using-mouse-wheel
  - https://stackoverflow.com/questions/47708282/zoom-functionality-using-qt
- [x] standard actions in the menus / toolbar
- [ ] implement crop
  - [ ] selection
    - [x] refactor the selection in its own class
    - [x] move the selection
    - [x] connect the selection with the crop panel
    - [x] make the selection work upwards
    - [x] make the QRubberBand a member of selection (do not extend it)
    - [ ] keep the selection inside of the image borders.
    - [x] As soon as the zoom is implemented, fix `Image::image_view_width()` to use the current view width.
    - [x] set the spinbox based on the image size.
    - [x] change the selection when the spinbox changes
      - https://wiki.qt.io/New_Signal_Slot_Syntax (see the overloaded signals)
    - [ ] add grips to the selection?
      - https://gist.github.com/Riateche/6743108
    - [x] change the selection when zooming
    - [x] should we (re-)add the "keep proportions"? probably, not... the target user won't probably understand it.
    - https://stackoverflow.com/questions/11881989/using-qrubberband-to-crop-image-in-qt
- [ ] avoid extending the widget in QImage and use the image (the issue is, how to put as little as possible in the MainWindow, for setting the centralContainer).
- [ ] implement resize
  - have a look at QSizeGrip (for QRubberBand?)
- [ ] high resolution?
  - http://doc.qt.io/qt-5.6/highdpi.html#high-dpi-support-in-qt
  - https://doc.qt.io/qt-5.6/qtlabscontrols-highdpi.html
- [x] add a left panel for the actions
- [ ] should it support jpg or only png?
- [ ] undo (without buttons, but in the context menu; and shortcuts)
  - [ ] as a first step undo actions (but not selection movements)
- [ ] should i keep "keep proportions" or i should make it the only behavior?
- [ ] open a file when it's passed as `argv`.
- [ ] getting the latest path from the settings:
  - https://stackoverflow.com/questions/3597900/qsettings-file-chooser-should-remember-the-last-directory
  - https://stackoverflow.com/questions/50347610/qt-file-dialog-doesnt-remember-the-last-directory-after-restarting-project
- [ ] On ESC, close the current tool panel
- [ ] use this https://openclipart.org/detail/244450/image-pics-icon as the application logo
- [ ] Setup continuos integration
    - read https://docs.travis-ci.com/user/tutorial/
    - go to trafvis-ci.org and activate the github repository from your account.
    - travis automatically adds a matching webhook on github.
    - create a `.travis.yml` file with `language:cpp` as the content.
    - add configurations for linux (gcc) and os x (clang)
    - get travis to install the needed packages through `apt-get` and `brew`
    - make sure that the `CMakeLists.txt` file has an install step
    - status:
      - i'm stuck at `Failed to find "GL/gl.h" in "/usr/include/libdrm". should i add  libdrm-dev?
    - todo:
      - read https://github.com/probonopd/linuxdeployqt/ and fix 
    - have a look at the mu-editor `conf/.desktop` file for more fields.
    - a sample by probono for creating an appimage for a qt app. it's different than <https://docs.appimage.org/packaging-guide/native-binaries.html> and <https://docs.appimage.org/packaging-guide/native-binaries.html#bundling-resources-into-the-appdir>
    - i had to change the target directories in the cmake install to match the structure defined in https://github.com/probonopd/linuxdeployqt#simplest-example
    - i should go back to linuxdeploy...
    - it needs at least one icon at 128x128... but you can add more of them with the cmake install into share/icons and they will be used (i think)
