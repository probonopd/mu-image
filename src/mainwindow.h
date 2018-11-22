#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "image.h"

class QLabel;
class QScrollArea;

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
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
    void do_help();
private:
    void createActions();

    void do_close();
    void show_error_message(QString message);
    void enable_action_buttons();
    void disable_action_buttons();

	Ui::MainWindow *ui;
    Image image;
};
#endif
