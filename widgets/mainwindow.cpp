#include "mainwindow.hpp"
#include "widgets/glwidget.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setCentralWidget(new GLWidget());
}

MainWindow::~MainWindow()
{

}
