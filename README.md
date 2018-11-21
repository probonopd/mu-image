# mu-image

A small image editor for kids

## Features

- The only features supported are:
  - Open existing PNGs.
  - Only one file at a time. Opening a new file, closes the old one.
  - Save to PNG (no question asked).
  - Resize the image size (to a pixel count or a %)
  - Crop with a visual rectangle selection (optionally with a fixed size selection).
  - Pick the transparency color.
- Possible features:
  - Open JPGs (and convert to PNGs on save)
  - Save as (mandatory for the confirmation? with the current file name as the default?)
- All features can be accessed through the toolbar's buttons.

## Resources

- Resize icon inspired by <https://openclipart.org/detail/304895/resize-icon>
- Crop icon inspired by <https://openclipart.org/detail/196865/mono-crop>
- Ghost icon inspired by <https://openclipart.org/detail/17847/cartoon-ghost>

## How-to

- Adding custom (`MainWindow`) slots in Qt Designer:
  - Go into "Edit Signal / Slot" mode.
  - Create a connection for any UI item.
  - Click on "Edit" for "MainWindow" and add slots that are definedin `mainwindow.h`.

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
- [ ] standard actions in the menus / toolbar
- [ ] high resolution?
  - http://doc.qt.io/qt-5.6/highdpi.html#high-dpi-support-in-qt
  - https://doc.qt.io/qt-5.6/qtlabscontrols-highdpi.html
- [ ] add a right panel for the actions
- [ ] should it support jpg or only png?
- [ ] undo (without buttons, but in the context menu)
