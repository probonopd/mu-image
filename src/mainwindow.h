#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
	Ui::MainWindow *ui;
    void createActions();
};
#endif
