#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QRubberBand>
#include "image.h"
#include "selection.h"

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
        none, resize, crop, transparency
    };

public:
	explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() override;
private slots:
    void do_load();
    void do_save();
    void do_resize();
    void do_crop();
    void do_transparency();
    void apply_resize();
    void apply_crop();
    void apply_transparency();
    void do_zoom_in();
    void do_zoom_default();
    void do_zoom_out();
    void do_help();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    void createActions();

    void do_close();
    void show_error_message(QString message);
    void hide_panels();
    void enable_action_buttons();
    void disable_action_buttons();

	Ui::MainWindow *ui;
    Image image;
    Selection selection{this};
    Action active_action{Action::none};
};
#endif
