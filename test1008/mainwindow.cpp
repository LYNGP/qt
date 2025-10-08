#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_changeButton_clicked()
{
    if(ui->label->text() == "hello"){
        ui->label->setText("nihao-guopeng");
    }
    else{
        ui->label->setText("hello");
    }
}

