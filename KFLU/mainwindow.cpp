#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inputButton_clicked()
{
    ui->inputWidget->show();
    ui->inputWidget->activateWindow();
    ui->inputWidget->raise();
}
void MainWindow::on_outputButton_clicked()
{
    ui->outputWidget->show();
    ui->outputWidget->activateWindow();
    ui->outputWidget->raise();
}

void MainWindow::on_areaButton_clicked()
{
    ui->areaWidget->show();
    ui->areaWidget->activateWindow();
    ui->areaWidget->raise();
}

void MainWindow::on_areaSubmit_clicked()
{
    ui->areaWidget->hide();
}

void MainWindow::on_outputPageBtn_clicked()
{
    ui->outputWidget->show();
    ui->outputWidget->activateWindow();
    ui->outputWidget->raise();
}

void MainWindow::on_inputPageBtn_clicked()
{
    ui->inputWidget->show();
    ui->inputWidget->activateWindow();
    ui->inputWidget->raise();
}


