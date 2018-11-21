# mu-image

A small image editor for kids

## Resources

- Resize icon inspired by <https://openclipart.org/detail/304895/resize-icon>
- Crop icon inspired by <https://openclipart.org/detail/196865/mono-crop>
- Ghost icon inspired by <https://openclipart.org/detail/17847/cartoon-ghost>

## Todo

- [x] add a toolbar:
  - http://doc.qt.io/qt-5/designer-creating-mainwindows.html#toolbars
  - load, save, resize, crop, transparency, quit, help (zoom in and out?)
  - make the toolbar wider? and get it to stick on the top.
  - Set "movable" to false in designer.
- [x] read the main window from a `.ui` file
  - old qt manual: <https://wiki.qt.io/Using_CMake_build_system>
  - new cmake manual: <https://cmake.org/cmake/help/v3.0/manual/cmake-qt.7.html#manual:cmake-qt(7)>
  - a sample qt app with ui files: <https://doc-snapshots.qt.io/qt5-5.9/gettingstartedqt.html>
  - use the images icon from ui-editor as the icon for the application? (with a red border...)
- [ ] standard actions in the menus / toolbar
- [ ] high resolution?
- [ ] add a right panel for the actions
