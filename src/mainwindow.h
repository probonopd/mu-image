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
    void load();
    void save();
    void resize();
    void crop();
    void transparency();
    void resize_apply();
    void crop_apply();
    void transparency_apply();
    void help();
private:
    void createActions();

    void close();
    void show_error_message(QString message);
    void enable_action_buttons();
    void disable_action_buttons();

	Ui::MainWindow *ui;
    Image image;
};
#endif
