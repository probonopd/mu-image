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
    // void about();
    void quit();
private:
	Ui::MainWindow *ui;
    void createActions();
};
#endif
