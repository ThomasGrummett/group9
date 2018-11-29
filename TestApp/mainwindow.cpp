#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>


/**
   @brief creates main UI Window
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

/**
   @brief deletes UI
*/
MainWindow::~MainWindow()
{
    delete ui;
}
