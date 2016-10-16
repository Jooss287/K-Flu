#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <define.h>

/*output 관련 변수들*/
int GraphAge = Age0to6; //default

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setDefault();
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*tab별 그래프 그리는 함수들*/
void MainWindow::makeInfectionPlot(QVector<double>x, QVector<double>y, int size){

    // create graph and assign data to it:
    ui->customPlot_infection->addGraph();
    ui->customPlot_infection->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot_infection->xAxis->setLabel("x");
    ui->customPlot_infection->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot_infection->xAxis->setRange(-1, 1);
    ui->customPlot_infection->yAxis->setRange(0, 1);
    ui->customPlot_infection->replot();
}

void MainWindow::makeResourcePlot(QVector<double>x, QVector<double>y, int size){

}

void MainWindow::makeSpecimenPlot(QVector<double>x, QVector<double>y, int size){

}


void MainWindow::makeDailyPlot(QVector<double>x, QVector<double>y, int size){

}


void MainWindow::makeCumulativePlot(QVector<double>x, QVector<double>y, int size){

}



void MainWindow::setDefault()
{
    /*인구 tab 기본값 세팅*/
    ui->input_Age0to6->setText(QString::number(Population[Age0to6]));
    ui->input_Age7to12->setText(QString::number(Population[Age7to12]));
    ui->input_Age13to18->setText(QString::number(Population[Age13to18]));
    ui->input_Age19to64->setText(QString::number(Population[Age19to64]));
    ui->input_Age65toEnd->setText(QString::number(Population[Age65toEnd]));

    ui->input_SchoolRatio->setText(QString::number(SchoolContactRate));
    ui->input_AbsentRatio->setText(QString::number(AbsenceContactRatio));

    /*질병 tab 기본값 세팅*/
    ui->input_LatentPeriod->setText(QString::number(LatentPeriod));

    ui->input_infDuration_1_1->setText(QString::number(InfectiousDuration[NonSevere][Child]));
    ui->input_infDuration_1_2->setText(QString::number(InfectiousDuration[NonSevere][Worker]));
    ui->input_infDuration_1_3->setText(QString::number(InfectiousDuration[NonSevere][Elderly]));
    ui->input_infDuration_2_1->setText(QString::number(InfectiousDuration[Severe][Child]));
    ui->input_infDuration_2_2->setText(QString::number(InfectiousDuration[Severe][Worker]));
    ui->input_infDuration_2_3->setText(QString::number(InfectiousDuration[Severe][Elderly]));

    ui->input_returnToWork->setText(QString::number(ReturntoWorkPeriod));

    ui->input_MildRate->setText(QString::number(MildRate));
    ui->input_SevereRate->setText(QString::number(SevereRate));

    ui->input_high_1_1->setText(QString::number(HighRiskRate[Child]));
    ui->input_high_1_2->setText(QString::number(HighRiskRate[Worker]));
    ui->input_high_1_3->setText(QString::number(HighRiskRate[Elderly]));
    ui->input_high_2_1->setText(QString::number(LowRiskHospitalRate[Child]));
    ui->input_high_2_2->setText(QString::number(LowRiskHospitalRate[Worker]));
    ui->input_high_2_3->setText(QString::number(LowRiskHospitalRate[Elderly]));
    ui->input_high_3_1->setText(QString::number(HighRiskHospitalRate[Child]));
    ui->input_high_3_2->setText(QString::number(HighRiskHospitalRate[Worker]));
    ui->input_high_3_3->setText(QString::number(HighRiskHospitalRate[Elderly]));

    ui->input_dead_1->setText(QString::number(DeadRate[Child]));
    ui->input_dead_2->setText(QString::number(DeadRate[Worker]));
    ui->input_dead_3->setText(QString::number(DeadRate[Elderly]));

    /*전염성 tab 기본값 세팅*/
    ui->input_R0->setText(QString::number(R0));

    ui->input_halfInfectiosRate->setText(QString::number(HalfInfectiousRate)); 

    ui->input_lastLatent->setText(QString::number(LastLatentPeriodCase));
    ui->input_asymptomatic->setText(QString::number(AsymptomaticCase));
    ui->input_moderate->setText(QString::number(ModerateCase));

    ui->input_isolModerate->setText(QString::number(ModerateCaseIsolation));
    ui->input_isolSevereHome->setText(QString::number(SevereHomeCaseIsolation));
    ui->input_isolSevereHospital->setText(QString::number(SevereHospitalCaseIsolation));
    ui->input_isolRange->setText(QString::number(RangeofIsolation));

    /*치료 tab 기본값 세팅*/
    ui->input_antiviralsRate->setText(QString::number(AntiviralsInjectionRate));

    ui->input_medicalHelp->setText(QString::number(MedicalHelp));
    ui->input_antiviralsHelp->setText(QString::number(AntiviralsHelp));

    ui->input_verySickTreat->setText(QString::number(VerySickTreatRate));
    ui->input_verySickTreatRange->setText(QString::number(VerySickTreatRange));

    ui->input_extreamlySickTreat->setText(QString::number(ExtremelySickTreatRate));
    ui->input_extreamlySickTreatRange->setText(QString::number(ExtremelySickTreatRange));

    ui->input_contagiousnessReduct->setText(QString::number(ContagiousnessReduction));
    ui->input_durationReduct->setText(QString::number(DiseaseDurationReduction));
    ui->input_HospitailizationReduct->setText(QString::number(HospitalizationReduction));

    /*격리 tab 기본값 세팅*/
    ui->input_contactReduct->setText(QString::number(ContactReductionRate));
    ui->input_contactReductRange->setText(QString::number(ContactReductionRange));

    ui->input_schoolClose->setText(QString::number(SchoolCloseRange));
    ui->input_SchoolCloseContact->setText(QString::number(SchoolCloseContactRatio));

    ui->input_gatheringCancel->setText(QString::number(GatheringCancelReductionRate));
    ui->input_gatheringCancelRange->setText(QString::number(GatheringCancleRange));

    /*입원 tab 기본값 세팅*/
    ui->input_NICU->setText(QString::number(HospitalizationNICU));
    ui->input_ICU->setText(QString::number(HospitalizationICU));

    /*백신 tab 기본값 세팅*/
    ui->input_vaccine_1->setText(QString::number(VaccineAgeRate[Age0to6]));
    ui->input_vaccine_2->setText(QString::number(VaccineAgeRate[Age7to12]));
    ui->input_vaccine_3->setText(QString::number(VaccineAgeRate[Age13to18]));
    ui->input_vaccine_4->setText(QString::number(VaccineAgeRate[Age19to64]));
    ui->input_vaccine_5->setText(QString::number(VaccineAgeRate[Age65toEnd]));

    ui->input_vaccineEffect_1->setText(QString::number(VaccineEffectAgeRate[Age0to6]));
    ui->input_vaccineEffect_2->setText(QString::number(VaccineEffectAgeRate[Age7to12]));
    ui->input_vaccineEffect_3->setText(QString::number(VaccineEffectAgeRate[Age13to18]));
    ui->input_vaccineEffect_4->setText(QString::number(VaccineEffectAgeRate[Age19to64]));
    ui->input_vaccineEffect_5->setText(QString::number(VaccineEffectAgeRate[Age65toEnd]));

    ui->input_antibodyRange->setText(QString::number(AntibodyCreateRange));
    ui->input_vaccineStart->setText(QString::number(VaccineStart));

    /*자원 tab 기본값 세팅*/
    ui->input_mask_NICU->setText(QString::number(MaskNeedNICU));
    ui->input_mask_ICU->setText(QString::number(MaskNeedICU));

    ui->input_respRate->setText(QString::number(RespiratorNeedRate));

    /*검체 tab 기본값 세팅*/
    ui->input_reinspect->setText(QString::number(ReinspectionRate));
    ui->input_outpatient->setText(QString::number(OutpatientSpecimenTesting));
}

//입력버튼 클릭
void MainWindow::on_inputButton_clicked()
{

    ui->inputWidget->show();
    ui->inputWidget->activateWindow();
    ui->inputWidget->raise();
}

//출력버튼 클릭
void MainWindow::on_outputButton_clicked()
{
    ui->outputWidget->show();
    ui->outputWidget->activateWindow();
    ui->outputWidget->raise();

    /*graph x,y 값 설정*/
    int size = 101;
    QVector<double>x(size), y(size); // initialize with entries 0..100
    for (int i=0; i<size; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    MainWindow::makeInfectionPlot(x,y,size);
}

//지역유형버튼 클릭
void MainWindow::on_areaButton_clicked()
{
    ui->areaWidget->show();
    ui->areaWidget->activateWindow();
    ui->areaWidget->raise();
}

//지역유형 확인 클릭
void MainWindow::on_areaSubmit_clicked()
{
    ui->areaWidget->hide();
}

//출력화면 이동 버튼 클릭
void MainWindow::on_outputPageBtn_clicked()
{
    ui->outputWidget->show();
    ui->outputWidget->activateWindow();
    ui->outputWidget->raise();

    /*graph x,y 값 설정*/
    int size = 101;
    QVector<double>x(size), y(size); // initialize with entries 0..100
    for (int i=0; i<size; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    MainWindow::makeInfectionPlot(x,y,size);
}
//입력화면 이동 버튼 클릭
void MainWindow::on_inputPageBtn_clicked()
{
    ui->inputWidget->show();
    ui->inputWidget->activateWindow();
    ui->inputWidget->raise();
}

/*인구 tab input 받아오기*/
void MainWindow::on_input_Age0to6_textEdited(const QString &arg1)
{
    Population[Age0to6] = arg1.toInt();
}

void MainWindow::on_input_Age7to12_textEdited(const QString &arg1)
{
    Population[Age7to12] = arg1.toInt();
}

void MainWindow::on_input_Age13to18_textEdited(const QString &arg1)
{
    Population[Age13to18] = arg1.toInt();
}

void MainWindow::on_input_Age19to64_textEdited(const QString &arg1)
{
    Population[Age19to64] = arg1.toInt();
}

void MainWindow::on_input_Age65toEnd_textEdited(const QString &arg1)
{
    Population[Age65toEnd] = arg1.toInt();
}

void MainWindow::on_input_SchoolRatio_textEdited(const QString &arg1)
{
    SchoolContactRate = arg1.toDouble();
}

void MainWindow::on_input_AbsentRatio_textEdited(const QString &arg1)
{
    AbsenceContactRatio = arg1.toDouble();
}

/*질병 tab input 받아오기*/
void MainWindow::on_input_LatentPeriod_textEdited(const QString &arg1)
{
    LatentPeriod = arg1.toDouble();
}

void MainWindow::on_input_infDuration_1_1_textEdited(const QString &arg1)
{
    InfectiousDuration[NonSevere][Child] = arg1.toDouble();
}

void MainWindow::on_input_infDuration_1_2_textEdited(const QString &arg1)
{
    InfectiousDuration[NonSevere][Worker] = arg1.toDouble();
}

void MainWindow::on_input_infDuration_1_3_textEdited(const QString &arg1)
{
    InfectiousDuration[NonSevere][Elderly] = arg1.toDouble();
}

void MainWindow::on_input_infDuration_2_1_textEdited(const QString &arg1)
{
    InfectiousDuration[Severe][Child] = arg1.toDouble();
}

void MainWindow::on_input_infDuration_2_2_textEdited(const QString &arg1)
{
    InfectiousDuration[Severe][Worker] = arg1.toDouble();
}

void MainWindow::on_input_infDuration_2_3_textEdited(const QString &arg1)
{
    InfectiousDuration[Severe][Elderly] = arg1.toDouble();
}

void MainWindow::on_input_returnToWork_textEdited(const QString &arg1)
{
    ReturntoWorkPeriod = arg1.toDouble();
}

void MainWindow::on_input_MildRate_textEdited(const QString &arg1)
{
    MildRate = arg1.toDouble();
}

void MainWindow::on_input_SevereRate_textEdited(const QString &arg1)
{
    SevereRate = arg1.toDouble();
}

void MainWindow::on_input_high_1_1_textEdited(const QString &arg1)
{
    HighRiskRate[Child] = arg1.toDouble();
}

void MainWindow::on_input_high_1_2_textEdited(const QString &arg1)
{
    HighRiskRate[Worker] = arg1.toDouble();
}

void MainWindow::on_input_high_1_3_textEdited(const QString &arg1)
{
    HighRiskRate[Elderly] = arg1.toDouble();
}

void MainWindow::on_input_high_2_1_textEdited(const QString &arg1)
{
    LowRiskHospitalRate[Child] = arg1.toDouble();
}

void MainWindow::on_input_high_2_2_textEdited(const QString &arg1)
{
    LowRiskHospitalRate[Worker] = arg1.toDouble();
}

void MainWindow::on_input_high_2_3_textEdited(const QString &arg1)
{
    LowRiskHospitalRate[Elderly] = arg1.toDouble();
}

void MainWindow::on_input_high_3_1_textEdited(const QString &arg1)
{
    HighRiskHospitalRate[Child] = arg1.toDouble();
}

void MainWindow::on_input_high_3_2_textEdited(const QString &arg1)
{
    HighRiskHospitalRate[Worker] = arg1.toDouble();
}

void MainWindow::on_input_high_3_3_textEdited(const QString &arg1)
{
    HighRiskHospitalRate[Elderly] = arg1.toDouble();
}

void MainWindow::on_input_dead_1_textEdited(const QString &arg1)
{
    DeadRate[Child] = arg1.toDouble();
}

void MainWindow::on_input_dead_2_textEdited(const QString &arg1)
{
    DeadRate[Worker] = arg1.toDouble();
}

void MainWindow::on_input_dead_3_textEdited(const QString &arg1)
{
    DeadRate[Elderly] = arg1.toDouble();
}

/*전염병 tab input 받아오기*/

void MainWindow::on_input_R0_textEdited(const QString &arg1)
{
    R0 = arg1.toDouble();
}

void MainWindow::on_input_lastLatent_textEdited(const QString &arg1)
{
    LastLatentPeriodCase = arg1.toDouble();
}

void MainWindow::on_input_asymptomatic_textEdited(const QString &arg1)
{
    AsymptomaticCase = arg1.toDouble();
}

void MainWindow::on_input_moderate_textEdited(const QString &arg1)
{
    ModerateCase = arg1.toDouble();
}

void MainWindow::on_input_isolModerate_textEdited(const QString &arg1)
{
    ModerateCaseIsolation = arg1.toDouble();
}

void MainWindow::on_input_isolSevereHome_textEdited(const QString &arg1)
{
    SevereHomeCaseIsolation = arg1.toDouble();
}

void MainWindow::on_input_isolSevereHospital_textEdited(const QString &arg1)
{
    SevereHospitalCaseIsolation = arg1.toDouble();
}

void MainWindow::on_input_isolRange_textEdited(const QString &arg1)
{
    RangeofIsolation = arg1.toDouble();
}

/*치료 tab input 받아오기*/

void MainWindow::on_input_antiviralsRate_textEdited(const QString &arg1)
{
    AntiviralsInjectionRate = arg1.toDouble();
}

void MainWindow::on_input_medicalHelp_textEdited(const QString &arg1)
{
    MedicalHelp = arg1.toDouble();
}

void MainWindow::on_input_antiviralsHelp_textEdited(const QString &arg1)
{
    AntiviralsHelp = arg1.toDouble();
}

void MainWindow::on_input_verySickTreat_textEdited(const QString &arg1)
{
    VerySickTreatRate = arg1.toDouble();
}

void MainWindow::on_input_verySickTreatRange_textEdited(const QString &arg1)
{
    VerySickTreatRange = arg1.toDouble();
}

void MainWindow::on_input_extreamlySickTreat_textEdited(const QString &arg1)
{
    ExtremelySickTreatRate = arg1.toDouble();
}

void MainWindow::on_input_extreamlySickTreatRange_textEdited(const QString &arg1)
{
    ExtremelySickTreatRange = arg1.toDouble();
}

void MainWindow::on_input_contagiousnessReduct_textEdited(const QString &arg1)
{
    ContagiousnessReduction = arg1.toDouble();
}

void MainWindow::on_input_durationReduct_textEdited(const QString &arg1)
{
    DiseaseDurationReduction = arg1.toDouble();
}

void MainWindow::on_input_HospitailizationReduct_textEdited(const QString &arg1)
{
    HospitalizationReduction = arg1.toDouble();
}

/*격리 tab input 받아오기*/

void MainWindow::on_input_contactReduct_textEdited(const QString &arg1)
{
    ContactReductionRate = arg1.toDouble();
}

void MainWindow::on_input_contactReductRange_textEdited(const QString &arg1)
{
    ContactReductionRange = arg1.toDouble();
}

void MainWindow::on_input_schoolClose_textEdited(const QString &arg1)
{
    SchoolCloseContactRatio = arg1.toDouble();
}

void MainWindow::on_input_SchoolCloseContact_textEdited(const QString &arg1)
{
    AbsenceContactRatio = arg1.toDouble();
}

void MainWindow::on_input_gatheringCancel_textEdited(const QString &arg1)
{
    GatheringCancelReductionRate = arg1.toDouble();
}

void MainWindow::on_input_gatheringCancelRange_textEdited(const QString &arg1)
{
    GatheringCancleRange = arg1.toDouble();
}

/*입원 tab input 받아오기*/

void MainWindow::on_input_NICU_textEdited(const QString &arg1)
{
   HospitalizationNICU = arg1.toDouble();
}

void MainWindow::on_input_ICU_textEdited(const QString &arg1)
{
     HospitalizationICU = arg1.toDouble();
}

/*백신 tab input 받아오기*/
void MainWindow::on_input_vaccine_1_textEdited(const QString &arg1)
{
    VaccineAgeRate[Age0to6] = arg1.toDouble();
}

void MainWindow::on_input_vaccine_2_textEdited(const QString &arg1)
{
    VaccineAgeRate[Age7to12] = arg1.toDouble();
}

void MainWindow::on_input_vaccine_3_textEdited(const QString &arg1)
{
    VaccineAgeRate[Age13to18] = arg1.toDouble();
}

void MainWindow::on_input_vaccine_4_textEdited(const QString &arg1)
{
     VaccineAgeRate[Age19to64] = arg1.toDouble();
}

void MainWindow::on_input_vaccine_5_textEdited(const QString &arg1)
{
    VaccineAgeRate[Age65toEnd] = arg1.toDouble();
}

void MainWindow::on_input_vaccineEffect_1_textEdited(const QString &arg1)
{
	VaccineEffectAgeRate[Age0to6] = arg1.toDouble();
}

void MainWindow::on_input_vaccineEffect_2_textEdited(const QString &arg1)
{
	VaccineEffectAgeRate[Age7to12] = arg1.toDouble();
}

void MainWindow::on_input_vaccineEffect_3_textEdited(const QString &arg1)
{
	VaccineEffectAgeRate[Age13to18] = arg1.toDouble();
}

void MainWindow::on_input_vaccineEffect_4_textEdited(const QString &arg1)
{
	VaccineEffectAgeRate[Age19to64] = arg1.toDouble();
}

void MainWindow::on_input_vaccineEffect_5_textEdited(const QString &arg1)
{
	VaccineEffectAgeRate[Age65toEnd] = arg1.toDouble();
}

void MainWindow::on_input_antibodyRange_textEdited(const QString &arg1)
{
    AntibodyCreateRange = arg1.toDouble();
}

void MainWindow::on_input_vaccineStart_textEdited(const QString &arg1)
{
    VaccineStart = arg1.toDouble();
}

/*자원 tab input 받아오기*/
void MainWindow::on_input_mask_NICU_textEdited(const QString &arg1)
{
    MaskNeedNICU = arg1.toDouble();
}

void MainWindow::on_input_mask_ICU_textEdited(const QString &arg1)
{
    MaskNeedICU = arg1.toDouble();
}

void MainWindow::on_input_respRate_textEdited(const QString &arg1)
{
    RespiratorNeedRate = arg1.toDouble();
}

/*검체 tab input 받아오기*/
void MainWindow::on_input_reinspect_textEdited(const QString &arg1)
{
    ReinspectionRate = arg1.toDouble();
}

void MainWindow::on_input_outpatient_textEdited(const QString &arg1)
{
    OutpatientSpecimenTesting = arg1.toDouble();
}

/*output 나이 선택*/
void MainWindow::on_age_checkBox1_clicked()
{
    GraphAge = Age0to6;
}

void MainWindow::on_age_checkBox2_clicked()
{
    GraphAge = Age7to12;
}

void MainWindow::on_age_checkBox3_clicked()
{
    GraphAge = Age13to18;
}

void MainWindow::on_age_checkBox4_clicked()
{
    GraphAge = Age19to64;
}

void MainWindow::on_age_checkBox5_clicked()
{
    GraphAge = Age65toEnd;
}
