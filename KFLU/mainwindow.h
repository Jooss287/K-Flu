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
	void MainWindow::run(double goal);

	void MainWindow::step();

	void makeInfectionPlot();

	void makeResourcePlot();

	void makeSpecimenPlot();

	void makeDailyPlot();


    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setDefault();
	
	void saveInput();

private slots:

    void on_startButton_clicked();

    void on_areaButton_clicked();

    void on_areaSubmit_clicked();

    void on_outputPageBtn_clicked();

    void on_inputPageBtn_clicked();

    void on_age_checkBox1_clicked();

    void on_age_checkBox2_clicked();

    void on_age_checkBox3_clicked();

    void on_age_checkBox4_clicked();

    void on_age_checkBox5_clicked();

    void on_age_checkBox6_clicked();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionK_flu_triggered();

    void on_actionExport_triggered();

    void on_actionContact_triggered();

    void on_actionJPG_triggered();

    void on_actionCSV_triggered();

    void on_jpgSubmit_clicked();

    void on_csvSubmit_clicked();

	void on_input_Age0to6_textChanged(const QString &arg1);

	void on_input_Age7to12_textChanged(const QString &arg1);

	void on_input_Age13to18_textChanged(const QString &arg1);

	void on_input_Age19to64_textChanged(const QString &arg1);

	void on_input_Age65toEnd_textChanged(const QString &arg1);

	void on_input_contact_1_1_textChanged(const QString &arg1);

	void on_input_contact_1_2_textChanged(const QString &arg1);

	void on_input_contact_1_3_textChanged(const QString &arg1);

	void on_input_contact_1_4_textChanged(const QString &arg1);

	void on_input_contact_1_5_textChanged(const QString &arg1);

	void on_input_contact_2_2_textChanged(const QString &arg1);

	void on_input_contact_2_3_textChanged(const QString &arg1);

	void on_input_contact_2_4_textChanged(const QString &arg1);

	void on_input_contact_2_5_textChanged(const QString &arg1);

	void on_input_contact_3_3_textChanged(const QString &arg1);

	void on_input_contact_3_4_textChanged(const QString &arg1);

	void on_input_contact_3_5_textChanged(const QString &arg1);

	void on_input_contact_4_4_textChanged(const QString &arg1);

	void on_input_contact_4_5_textChanged(const QString &arg1);

	void on_input_contact_5_5_textChanged(const QString &arg1);

    void on_saveBtn_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
