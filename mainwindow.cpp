#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "grid.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setStyleSheet("background-color: gray;");

    Grid* grid = new Grid();
    grid->setFixedSize(this->width(), this->height());

    setCentralWidget(grid);

    grid->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

