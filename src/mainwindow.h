#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QScrollArea>
#include <QRubberBand>
#include <QUndoStack>
#include <QAction>
#include <QMenu>
#include "image.h"

class QLabel;
class QScrollArea;
class QMouseEvent;
class QMouseEvent;

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum class Action
    {
        none, scale, crop, transparency
    };

public:
	explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() override;
private slots:
    void do_load();
    void do_save();
    void do_scale();
    void do_crop();
    void do_transparency();
    void apply_scale();
    void apply_crop();
    void apply_transparency();
    void close_crop();
    void do_zoom_in();
    void do_zoom_default();
    void do_zoom_out();
    void do_help();
public slots:
    void change_crop_selection(QRect geometry);
private slots:
    void on_panel_focus(int i);
private:
    void createActions();

    void zoom_scroll_bar();

    void do_close();
    void show_error_message(QString message);
    void hide_panels();
    void enable_action_buttons();
    void disable_action_buttons();

	Ui::MainWindow *ui;
    Image image{this};
    QScrollArea scroll_area{};
    Action active_action{Action::none};

    QUndoStack undoStack{this};
    QAction* undoAction;
    QAction* redoAction;

    QMetaObject::Connection crop_selection_connection;
    QVector<QMetaObject::Connection> crop_connection;
public:
    QMenu contextMenu{&image};
};
#endif
