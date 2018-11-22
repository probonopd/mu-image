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
  - make the toolbar wider? and get it to stick on the top.
  - Set "movable" to false in designer.
- [x] read the main window from a `.ui` file
  - old qt manual: <https://wiki.qt.io/Using_CMake_build_system>
  - new cmake manual: <https://cmake.org/cmake/help/v3.0/manual/cmake-qt.7.html#manual:cmake-qt(7)>
  - a sample qt app with ui files: <https://doc-snapshots.qt.io/qt5-5.9/gettingstartedqt.html>
  - use the images icon from ui-editor as the icon for the application? (with a red border...)
- [ ] load an image into the central widget.
- [x] standard actions in the menus / toolbar
- [ ] high resolution?
  - http://doc.qt.io/qt-5.6/highdpi.html#high-dpi-support-in-qt
  - https://doc.qt.io/qt-5.6/qtlabscontrols-highdpi.html
- [x] add a right panel for the actions
- [ ] should it support jpg or only png?
- [ ] undo (without buttons, but in the context menu)
- [ ] should i keep "keep proportions" or i should make it the only behavior?
- [ ] open a file when it's passed as `argv`.
- [ ] getting the latest path from the settings:
  - https://stackoverflow.com/questions/3597900/qsettings-file-chooser-should-remember-the-last-directory
  - https://stackoverflow.com/questions/50347610/qt-file-dialog-doesnt-remember-the-last-directory-after-restarting-project
- [ ] On ESC, close the current tool panel
- [ ] use this https://openclipart.org/detail/244450/image-pics-icon as the application logo
