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

	void MainWindow::setStart(double startX);

	void MainWindow::step();

	QVector<double> setOutputArray(int x);

	void makeInfectionPlot();

	void makeResourcePlot();

	void makeSpecimenPlot();

	void makeDailyPlot();

	void makeCumulativePlot();

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setDefault();

private slots:

    void on_startButton_clicked();

    void on_areaButton_clicked();

    void on_areaSubmit_clicked();

    void on_outputPageBtn_clicked();

    void on_inputPageBtn_clicked();

    void on_input_Age0to6_textEdited(const QString &arg1);

    void on_input_Age7to12_textEdited(const QString &arg1);

    void on_input_Age13to18_textEdited(const QString &arg1);

    void on_input_Age19to64_textEdited(const QString &arg1);

    void on_input_Age65toEnd_textEdited(const QString &arg1);

    void on_input_SchoolRatio0to6_textEdited(const QString &arg1);

    void on_input_SchoolRatio7to12_textEdited(const QString &arg1);

    void on_input_SchoolRatio13to18_textEdited(const QString &arg1);

    void on_input_AbsentRatio0to6_textEdited(const QString &arg1);

    void on_input_AbsentRatio7to12_textEdited(const QString &arg1);

    void on_input_AbsentRatio13to18_textEdited(const QString &arg1);

    void on_input_LatentPeriod_textEdited(const QString &arg1);

    void on_input_infDuration_1_1_textEdited(const QString &arg1);

    void on_input_infDuration_1_2_textEdited(const QString &arg1);

    void on_input_infDuration_1_3_textEdited(const QString &arg1);

    void on_input_infDuration_2_1_textEdited(const QString &arg1);

    void on_input_infDuration_2_2_textEdited(const QString &arg1);

    void on_input_infDuration_2_3_textEdited(const QString &arg1);

    void on_input_returnToWork_textEdited(const QString &arg1);

    void on_input_MildRate_textEdited(const QString &arg1);

    void on_input_SevereRate_textEdited(const QString &arg1);

    void on_input_high_1_1_textEdited(const QString &arg1);

    void on_input_high_1_2_textEdited(const QString &arg1);

    void on_input_high_1_3_textEdited(const QString &arg1);

    void on_input_high_2_1_textEdited(const QString &arg1);

    void on_input_high_2_2_textEdited(const QString &arg1);

    void on_input_high_2_3_textEdited(const QString &arg1);

    void on_input_high_3_1_textEdited(const QString &arg1);

    void on_input_high_3_2_textEdited(const QString &arg1);

    void on_input_high_3_3_textEdited(const QString &arg1);

    void on_input_dead_1_textEdited(const QString &arg1);

    void on_input_dead_2_textEdited(const QString &arg1);

    void on_input_dead_3_textEdited(const QString &arg1);

    void on_input_R0_textEdited(const QString &arg1);

    void on_input_lastLatent_textEdited(const QString &arg1);

    void on_input_asymptomatic_textEdited(const QString &arg1);

    void on_input_moderate_textEdited(const QString &arg1);

    void on_input_isolModerate_textEdited(const QString &arg1);

    void on_input_isolSevereHome_textEdited(const QString &arg1);

    void on_input_isolSevereHospital_textEdited(const QString &arg1);

    void on_input_isolStart_textEdited(const QString &arg1);

    void on_input_isolEnd_textEdited(const QString &arg1);

    void on_input_antiviralsRate_textEdited(const QString &arg1);

    void on_input_medicalHelp_textEdited(const QString &arg1);

    void on_input_antiviralsHelp_textEdited(const QString &arg1);

    void on_input_verySickTreat_textEdited(const QString &arg1);

    void on_input_verySickTreatStart_textEdited(const QString &arg1);

    void on_input_verySickTreatEnd_textEdited(const QString &arg1);

    void on_input_extreamlySickTreat_textEdited(const QString &arg1);

    void on_input_extreamlySickTreatStart_textEdited(const QString &arg1);

    void on_input_extreamlySickTreatEnd_textEdited(const QString &arg1);

    void on_input_contagiousnessReduct_textEdited(const QString &arg1);

    void on_input_durationReduct_textEdited(const QString &arg1);

    void on_input_HospitailizationReduct_textEdited(const QString &arg1);

    void on_input_contactReduct_textEdited(const QString &arg1);

    void on_input_contactReductStart_textEdited(const QString &arg1);

    void on_input_contactReductEnd_textEdited(const QString &arg1);

    void on_input_SchoolCloseStart_textEdited(const QString &arg1);

    void on_input_SchoolCloseEnd_textEdited(const QString &arg1);

    void on_input_schoolCloseContact0to6_textEdited(const QString &arg1);

	void on_input_schoolCloseContact7to12_textEdited(const QString &arg1);

	void on_input_schoolCloseContact13to18_textEdited(const QString &arg1);

    void on_input_gatheringCancel_textEdited(const QString &arg1);

    void on_input_gatheringCancelStart_textEdited(const QString &arg1);

    void on_input_gatheringCancelEnd_textEdited(const QString &arg1);

    void on_input_NICU_textEdited(const QString &arg1);

    void on_input_ICU_textEdited(const QString &arg1);

    void on_input_vaccine_1_textEdited(const QString &arg1);

    void on_input_vaccine_2_textEdited(const QString &arg1);

    void on_input_vaccine_3_textEdited(const QString &arg1);

    void on_input_vaccine_4_textEdited(const QString &arg1);

    void on_input_vaccine_5_textEdited(const QString &arg1);

    void on_input_vaccineEffect_1_textEdited(const QString &arg1);

    void on_input_vaccineEffect_2_textEdited(const QString &arg1);

    void on_input_vaccineEffect_3_textEdited(const QString &arg1);

    void on_input_vaccineEffect_4_textEdited(const QString &arg1);

    void on_input_vaccineEffect_5_textEdited(const QString &arg1);

    void on_input_antibodyRange_textEdited(const QString &arg1);

    void on_input_vaccineStart_textEdited(const QString &arg1);

    void on_input_mask_NICU_textEdited(const QString &arg1);

    void on_input_mask_ICU_textEdited(const QString &arg1);

    void on_input_respRate_textEdited(const QString &arg1);

    void on_input_reinspect_textEdited(const QString &arg1);

    void on_input_outpatient_textEdited(const QString &arg1);

    void on_age_checkBox1_clicked();

    void on_age_checkBox2_clicked();

    void on_age_checkBox3_clicked();

    void on_age_checkBox4_clicked();

    void on_age_checkBox5_clicked();

    void on_age_checkBox6_clicked();

    void on_input_contact_1_1_textEdited(const QString &arg1);

    void on_input_contact_1_2_textEdited(const QString &arg1);

    void on_input_contact_1_3_textEdited(const QString &arg1);

    void on_input_contact_1_4_textEdited(const QString &arg1);

    void on_input_contact_1_5_textEdited(const QString &arg1);

    void on_input_contact_2_2_textEdited(const QString &arg1);

    void on_input_contact_2_3_textEdited(const QString &arg1);

    void on_input_contact_2_4_textEdited(const QString &arg1);

    void on_input_contact_2_5_textEdited(const QString &arg1);

    void on_input_contact_3_3_textEdited(const QString &arg1);

    void on_input_contact_3_4_textEdited(const QString &arg1);

    void on_input_contact_3_5_textEdited(const QString &arg1);

    void on_input_contact_4_4_textEdited(const QString &arg1);

    void on_input_contact_4_5_textEdited(const QString &arg1);

    void on_input_contact_5_5_textEdited(const QString &arg1);


    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionK_flu_triggered();

    void on_actionExport_triggered();

    void on_actionContact_triggered();

    void on_actionJPG_triggered();

    void on_actionCSV_triggered();

    void on_jpgSubmit_clicked();

    void on_csvSubmit_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
