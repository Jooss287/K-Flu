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
    ~MainWindow();
    void setDefault();

private slots:

    void on_inputButton_clicked();

    void on_areaButton_clicked();

    void on_areaSubmit_clicked();

    void on_outputPageBtn_clicked();

    void on_inputPageBtn_clicked();

    void on_outputButton_clicked();

    void on_input_Age0to6_textChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
