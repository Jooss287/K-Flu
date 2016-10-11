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

    void on_input_Age0to6_textEdited(const QString &arg1);

    void on_input_Age7to12_textEdited(const QString &arg1);

    void on_input_Age13to18_textEdited(const QString &arg1);

    void on_input_Age19to64_textEdited(const QString &arg1);

    void on_input_Age65toEnd_textEdited(const QString &arg1);

    void on_input_SchoolRatio_textEdited(const QString &arg1);

    void on_input_AbsentRatio_textEdited(const QString &arg1);

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

    void on_input_isolRange_textEdited(const QString &arg1);

    void on_input_antiviralsRate_textEdited(const QString &arg1);

    void on_input_medicalHelp_textEdited(const QString &arg1);

    void on_input_antiviralsHelp_textEdited(const QString &arg1);

    void on_input_verySickTreat_textEdited(const QString &arg1);

    void on_input_verySickTreatRange_textEdited(const QString &arg1);

    void on_input_extreamlySickTreat_textEdited(const QString &arg1);

    void on_input_extreamlySickTreatRange_textEdited(const QString &arg1);

    void on_input_contagiousnessReduct_textEdited(const QString &arg1);

    void on_input_durationReduct_textEdited(const QString &arg1);

    void on_input_HospitailizationReduct_textEdited(const QString &arg1);

    void on_input_contactReduct_textEdited(const QString &arg1);

    void on_input_contactReductRange_textEdited(const QString &arg1);

    void on_input_schoolClose_textEdited(const QString &arg1);

    void on_input_SchoolCloseContact_textEdited(const QString &arg1);

    void on_input_gatheringCancel_textEdited(const QString &arg1);

    void on_input_gatheringCancelRange_textEdited(const QString &arg1);

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
