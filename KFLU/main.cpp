#include "mainwindow.h"
#include <QApplication>
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
	w.show();

    return a.exec();
}
