#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    createActions();
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    // QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    // exitAct->setShortcuts(QKeySequence::Quit);
	ui->actionQuit->setShortcut(QKeySequence::Quit);

    // QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    // QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
}

void MainWindow::quit()
{
	close();
}

/*
void MainWindow::about()
{
    QMessageBox::about(this, tr("About this sample"),
        tr("This <i>Sample</i> creates a window with a menu bar."));
}
*/
