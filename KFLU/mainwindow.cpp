#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <define.h>


/*input 관련 변수들*/
int PopulationTotal =Population[Age0to6]+Population[Age7to12]+Population[Age13to18]+Population[Age19to64]+Population[Age65toEnd];

int contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
int contactTotal7to12 =  ContactMatrix[Age7to12][Age7to12]+ ContactMatrix[Age7to12][Age13to18]+ ContactMatrix[Age7to12][Age19to64]+ ContactMatrix[Age7to12][Age65toEnd];
int contactTotal13to18 =  ContactMatrix[Age13to18][Age13to18]+ ContactMatrix[Age13to18][Age19to64]+ ContactMatrix[Age13to18][Age65toEnd];
int contactTotal19to64 =  ContactMatrix[Age19to64][Age19to64]+ ContactMatrix[Age19to64][Age65toEnd];
int contactTotal65toEnd = ContactMatrix[Age65toEnd][Age65toEnd];

int contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;

/*output 관련 변수들*/
int GraphAge = Age0to6; //default
bool AgeAll = true;

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
void MainWindow::makeInfectionPlot(QVector<double>x, QVector<double>y){

	ui->customPlot_infection->legend->setVisible(true);
	ui->customPlot_infection->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
	// by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
	ui->customPlot_infection->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom | Qt::AlignRight);

    ui->customPlot_infection->xAxis->setLabel("일");
	ui->customPlot_infection->yAxis->setLabel("인구");

	// set axes ranges, so we see all data:
	ui->customPlot_infection->xAxis->setRange(-1, 1);
	ui->customPlot_infection->yAxis->setRange(0, 1);

	// create graph and assign data to it:
	ui->customPlot_infection->addGraph();
    ui->customPlot_infection->graph(0)->setData(x, y);
	ui->customPlot_infection->graph(0)->setName("감수성기에 있는 사람");
    ui->customPlot_infection->replot();

    ui->infectionTable->setColumnWidth(0,80);
    ui->infectionTable->setColumnWidth(1,130);
    ui->infectionTable->setColumnWidth(2,120);
    ui->infectionTable->setColumnWidth(3,80);
    ui->infectionTable->setColumnWidth(4,130);
	ui->infectionTable->setColumnWidth(5,120);
	ui->infectionTable->setColumnWidth(6,70);
	ui->infectionTable->setColumnWidth(7,90);
}


void MainWindow::makeResourcePlot(QVector<double>x, QVector<double>y){

}

void MainWindow::makeSpecimenPlot(QVector<double>x, QVector<double>y){

}


void MainWindow::makeDailyPlot(QVector<double>x, QVector<double>y){

}


void MainWindow::makeCumulativePlot(QVector<double>x, QVector<double>y){

}



void MainWindow::setDefault()
{
    /*인구 tab 기본값 세팅*/

    ui->input_SchoolRatio0to6->setText(QString::number(SchoolCloseContactRatio)); //초기값 수정 필요
    ui->input_SchoolRatio7to12->setText(QString::number(SchoolCloseContactRatio)); //초기값 수정 필요
    ui->input_SchoolRatio13to18->setText(QString::number(SchoolCloseContactRatio)); //초기값 수정 필요

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
    ui->input_isolStart->setText(QString::number(RangeofIsolationBegin));
    ui->input_isolEnd->setText(QString::number(RangeofIsolationEnd));

    /*치료 tab 기본값 세팅*/
    ui->input_antiviralsRate->setText(QString::number(AntiviralsInjectionRate));

    ui->input_medicalHelp->setText(QString::number(MedicalHelp));
    ui->input_antiviralsHelp->setText(QString::number(AntiviralsHelp));

    ui->input_verySickTreat->setText(QString::number(VerySickTreatRate));
    ui->input_verySickTreatStart->setText(QString::number(VerySickTreatRangeBegin));
    ui->input_verySickTreatEnd->setText(QString::number(VerySickTreatRangeEnd));

    ui->input_extreamlySickTreat->setText(QString::number(ExtremelySickTreatRate));
    ui->input_extreamlySickTreatStart->setText(QString::number(ExtremelySickTreatRangeBegin));
    ui->input_extreamlySickTreatEnd->setText(QString::number(ExtremelySickTreatRangeEnd));

    ui->input_contagiousnessReduct->setText(QString::number(ContagiousnessReduction));
    ui->input_durationReduct->setText(QString::number(DiseaseDurationReduction));
    ui->input_HospitailizationReduct->setText(QString::number(HospitalizationReduction));

    /*격리 tab 기본값 세팅*/
    ui->input_contactReduct->setText(QString::number(ContactReductionRate));
    ui->input_contactReductStart->setText(QString::number(ContactReductionRangeBegin));
    ui->input_contactReductEnd->setText(QString::number(ContactReductionRangeEnd));

    ui->input_SchoolCloseStart->setText(QString::number(SchoolCloseRangeBegin));
    ui->input_SchoolCloseEnd->setText(QString::number(SchoolCloseRangeEnd));
    ui->input_SchoolCloseContact->setText(QString::number(SchoolCloseContactRatio));

    ui->input_gatheringCancel->setText(QString::number(GatheringCancelReductionRate));
    ui->input_gatheringCancelStart->setText(QString::number(GatheringCancleRangeBegin));
    ui->input_gatheringCancelEnd->setText(QString::number(GatheringCancleRangeEnd));

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

//시작버튼 클릭
void MainWindow::on_startButton_clicked()
{

    ui->inputWidget->show();
    ui->inputWidget->activateWindow();
    ui->inputWidget->raise();
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
    MainWindow::makeInfectionPlot(x,y);
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
    PopulationTotal =Population[Age0to6]+Population[Age7to12]+Population[Age13to18]+Population[Age19to64]+Population[Age65toEnd];
    ui->input_AgeTotal->setText(QString::number(PopulationTotal));
}

void MainWindow::on_input_Age7to12_textEdited(const QString &arg1)
{
    Population[Age7to12] = arg1.toInt();
    PopulationTotal =Population[Age0to6]+Population[Age7to12]+Population[Age13to18]+Population[Age19to64]+Population[Age65toEnd];
    ui->input_AgeTotal->setText(QString::number(PopulationTotal));
}

void MainWindow::on_input_Age13to18_textEdited(const QString &arg1)
{
    Population[Age13to18] = arg1.toInt();
    PopulationTotal =Population[Age0to6]+Population[Age7to12]+Population[Age13to18]+Population[Age19to64]+Population[Age65toEnd];
    ui->input_AgeTotal->setText(QString::number(PopulationTotal));
}

void MainWindow::on_input_Age19to64_textEdited(const QString &arg1)
{
    Population[Age19to64] = arg1.toInt();
    PopulationTotal =Population[Age0to6]+Population[Age7to12]+Population[Age13to18]+Population[Age19to64]+Population[Age65toEnd];
    ui->input_AgeTotal->setText(QString::number(PopulationTotal));
}

void MainWindow::on_input_Age65toEnd_textEdited(const QString &arg1)
{
    Population[Age65toEnd] = arg1.toInt();
    PopulationTotal =Population[Age0to6]+Population[Age7to12]+Population[Age13to18]+Population[Age19to64]+Population[Age65toEnd];
    ui->input_AgeTotal->setText(QString::number(PopulationTotal));
}

void MainWindow::on_input_contact_1_1_textEdited(const QString &arg1)
{
    ContactMatrix[Age0to6][Age0to6] = arg1.toInt();
    contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_1_2_textEdited(const QString &arg1)
{
    ContactMatrix[Age0to6][Age7to12] = arg1.toInt();
    contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_1_3_textEdited(const QString &arg1)
{
    ContactMatrix[Age0to6][Age13to18] = arg1.toInt();
    contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_1_4_textEdited(const QString &arg1)
{
    ContactMatrix[Age0to6][Age19to64] = arg1.toInt();
    contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_1_5_textEdited(const QString &arg1)
{
    ContactMatrix[Age0to6][Age65toEnd] = arg1.toInt();
    contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_2_2_textEdited(const QString &arg1)
{
    ContactMatrix[Age7to12][Age7to12] = arg1.toInt();
    contactTotal7to12 =  ContactMatrix[Age7to12][Age7to12]+ ContactMatrix[Age7to12][Age13to18]+ ContactMatrix[Age7to12][Age19to64]+ ContactMatrix[Age7to12][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_2_3_textEdited(const QString &arg1)
{
    ContactMatrix[Age7to12][Age13to18] = arg1.toInt();
    contactTotal7to12 =  ContactMatrix[Age7to12][Age7to12]+ ContactMatrix[Age7to12][Age13to18]+ ContactMatrix[Age7to12][Age19to64]+ ContactMatrix[Age7to12][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_2_4_textEdited(const QString &arg1)
{
    ContactMatrix[Age7to12][Age19to64] = arg1.toInt();
    contactTotal7to12 =  ContactMatrix[Age7to12][Age7to12]+ ContactMatrix[Age7to12][Age13to18]+ ContactMatrix[Age7to12][Age19to64]+ ContactMatrix[Age7to12][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_2_5_textEdited(const QString &arg1)
{
    ContactMatrix[Age7to12][Age65toEnd] = arg1.toInt();
    contactTotal7to12 =  ContactMatrix[Age7to12][Age7to12]+ ContactMatrix[Age7to12][Age13to18]+ ContactMatrix[Age7to12][Age19to64]+ ContactMatrix[Age7to12][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_3_3_textEdited(const QString &arg1)
{
    ContactMatrix[Age13to18][Age13to18] = arg1.toInt();
    contactTotal13to18 =  ContactMatrix[Age13to18][Age13to18]+ ContactMatrix[Age13to18][Age19to64]+ ContactMatrix[Age13to18][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_3_4_textEdited(const QString &arg1)
{
    ContactMatrix[Age13to18][Age19to64] = arg1.toInt();
    contactTotal13to18 =  ContactMatrix[Age13to18][Age13to18]+ ContactMatrix[Age13to18][Age19to64]+ ContactMatrix[Age13to18][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_3_5_textEdited(const QString &arg1)
{
    ContactMatrix[Age13to18][Age65toEnd] = arg1.toInt();
    contactTotal13to18 =  ContactMatrix[Age13to18][Age13to18]+ ContactMatrix[Age13to18][Age19to64]+ ContactMatrix[Age13to18][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_4_4_textEdited(const QString &arg1)
{
    ContactMatrix[Age19to64][Age19to64] = arg1.toInt();
    contactTotal19to64 =  ContactMatrix[Age19to64][Age19to64]+ ContactMatrix[Age19to64][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_4_5_textEdited(const QString &arg1)
{
    ContactMatrix[Age19to64][Age65toEnd] = arg1.toInt();
    contactTotal19to64 =  ContactMatrix[Age19to64][Age19to64]+ ContactMatrix[Age19to64][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_5_5_textEdited(const QString &arg1)
{
    ContactMatrix[Age65toEnd][Age65toEnd] = arg1.toInt();
    contactTotal65toEnd = ContactMatrix[Age65toEnd][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}


//인풋 변수 수정 필요
void MainWindow::on_input_SchoolRatio0to6_textEdited(const QString &arg1)
{
	SchoolCloseContactRatio = arg1.toDouble();
}
//인풋 변수 수정 필요
void MainWindow::on_input_SchoolRatio7to12_textEdited(const QString &arg1)
{
	SchoolCloseContactRatio = arg1.toDouble();
}
//인풋 변수 수정 필요
void MainWindow::on_input_SchoolRatio13to18_textEdited(const QString &arg1)
{
	SchoolCloseContactRatio = arg1.toDouble();
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

void MainWindow::on_input_isolStart_textEdited(const QString &arg1)
{
    RangeofIsolationBegin = arg1.toDouble();
}

void MainWindow::on_input_isolEnd_textEdited(const QString &arg1)
{
    ExtremelySickTreatRangeBegin = arg1.toDouble();
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

void MainWindow::on_input_verySickTreatStart_textEdited(const QString &arg1)
{
    VerySickTreatRangeBegin = arg1.toDouble();
}

void MainWindow::on_input_verySickTreatEnd_textEdited(const QString &arg1)
{
    VerySickTreatRangeEnd = arg1.toDouble();
}



void MainWindow::on_input_extreamlySickTreat_textEdited(const QString &arg1)
{
    ExtremelySickTreatRate = arg1.toDouble();
}

void MainWindow::on_input_extreamlySickTreatStart_textEdited(const QString &arg1)
{
    ExtremelySickTreatRangeBegin = arg1.toDouble();
}

void MainWindow::on_input_extreamlySickTreatEnd_textEdited(const QString &arg1)
{
    ExtremelySickTreatRangeEnd = arg1.toDouble();
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

void MainWindow::on_input_contactReductStart_textEdited(const QString &arg1)
{
    ContactReductionRangeBegin = arg1.toDouble();
}

void MainWindow::on_input_contactReductEnd_textEdited(const QString &arg1)
{
    ContactReductionRangeEnd = arg1.toDouble();
}

void MainWindow::on_input_SchoolCloseStart_textEdited(const QString &arg1)
{
	SchoolCloseRangeBegin = arg1.toDouble();
}

void MainWindow::on_input_SchoolCloseEnd_textEdited(const QString &arg1)
{
	SchoolCloseRangeEnd = arg1.toDouble();
}

void MainWindow::on_input_schoolCloseContact_textEdited(const QString &arg1)
{
    SchoolCloseContactRatio = arg1.toDouble();
}

void MainWindow::on_input_gatheringCancel_textEdited(const QString &arg1)
{
    GatheringCancelReductionRate = arg1.toDouble();
}

void MainWindow::on_input_gatheringCancelStart_textEdited(const QString &arg1)
{
	GatheringCancleRangeBegin = arg1.toDouble();
}

void MainWindow::on_input_gatheringCancelEnd_textEdited(const QString &arg1)
{
	GatheringCancleRangeEnd = arg1.toDouble();
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
    AgeAll = false;
}

void MainWindow::on_age_checkBox2_clicked()
{
    GraphAge = Age7to12;
    AgeAll = false;
}

void MainWindow::on_age_checkBox3_clicked()
{
    GraphAge = Age13to18;
    AgeAll = false;
}

void MainWindow::on_age_checkBox4_clicked()
{
    GraphAge = Age19to64;
    AgeAll = false;
}

void MainWindow::on_age_checkBox5_clicked()
{
    GraphAge = Age65toEnd;
    AgeAll = false;
}

void MainWindow::on_age_checkBox6_clicked()
{
    AgeAll = true;
}
