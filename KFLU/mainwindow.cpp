﻿#include "mainwindow.h"
#include "ui_mainwindow.h"

//**********************************************
//Define Value 목록
//==============================================
//연령별 분포
#define Age0to6 0
#define Age7to12 1
#define Age13to18 2
#define Age19to64 3
#define Age65toEnd 4
#define AgeTotal 5	//ContactMatrix 합계 Part

#define StageofAgeGroups 5
#define StageofAgeTotal 6


//근로기준 연령분포
#define Child 0
#define Worker 1
#define Elderly 2
#define StageofWorkAge 3

//Severe 분포 -> AM / VX에 적용
#define NonSevere 0
#define Severe 1
#define StageofSevere 2

//Risk 분포
#define LowRisk 0
#define HighRisk 1
#define StageofRisk 2

//질병단계 k to m
#define Stageofk 7		//임의 값임

//**********************************************
//Define Function 목록
//==============================================
double percentage(double);


//**********************************************
//Input 화면 탭 입력변수 목록
//==============================================
//--인구
unsigned int Population[StageofAgeTotal] = { 0, 0, 0, 0, 0, 0 };	//0to6, 7to12, 13to18, 19to64, 65toEnd, total
unsigned int ContactMatrix[StageofAgeTotal][StageofAgeTotal] = { { 0, 0, 0, 0, 0, 0 },
                                                                { 0, 0, 0, 0, 0, 0 },
                                                                { 0, 0, 0, 0, 0, 0 },
                                                                { 0, 0, 0, 0, 0, 0 },
                                                                { 0, 0, 0, 0, 0, 0 },
                                                                { 0, 0, 0, 0, 0, 0 } };
int SchoolContactRate = 50.0;
//결석으로 어른과 접촉이 강화되는 정도
unsigned int AbsenceContactRatio = 3;

//--질병 TAB
double LatentPeriod = 1.9;
double InfectiousDuration[StageofSevere][StageofWorkAge] = { { 0, 0 },
                                                            {0, 0} };

double ReturntoWorkPeriod = 5.0;
double SevereRate = 50.0;
double MildRate = 33.3;
double HighRiskRate[StageofWorkAge] = { 6.0, 14.0, 47.0 };
double LowRiskHospitalRate[StageofWorkAge] = { 0.187, 14.0, 47.0 };
double HighRiskHospitalRate[StageofWorkAge] = { 1.333, 2.762, 7.768 };
double DeadRate[StageofWorkAge] = { 5.541, 16.541, 39.505 };

//--전염성 TAB
//기초 감염 재 생산수
double R0 = 2.5;
//총 감염 가능 기간 중 절반 기간 동안 갖는 전염성 비율
double HalfInfectiousRate = 90.0;
//중증도가 높은 경우와 비교 했을 때 상대적 전염성
double LastLatentPeriodCase = 50.0;
double AsymptomaticCase = 50.0;
double ModerateCase = 100.0;
//부분 격리
double ModerateCaseIsolation = 50.0;
double SevereHomeCaseIsolation = 50.0;
double SevereHospitalCaseIsolation = 100.0;
double RangeofIsolation = 0;

//--치료 TAB
//항바이러스제 투여 가능 비율
double AntiviralsInjectionRate = 100.0;
//의료서비스 이용가능 시간
double MedicalHelp = 24.0;
double AntiviralsHelp = 48.0;
//Very Sick Case 치료
double VerySickTreatRate = 0;
double VerySickTreatRange = 0.0;
//Extremely Sick Case 치료
double ExtremelySickTreatRate = 0;
double ExtremelySickTreatRange = 0.0;
//치료 효과
double ContagiousnessReduction = 80.0;
double DiseaseDurationReduction = 25.0;
double HospitalizationReduction =50.0;

//--격리 TAB
//일반접촉 감소 비율 및 기간
double ContactReductionRate = 0.0;
double ContactReductionRange = 0;
//휴교 및 그에 따른 접촉 수준 변동
double SchoolCloseRange = 0;
double SchoolCloseContactRatio = 2;
//대중집회 취소 및 그에 따른 접촉 수준 변동
double GatheringCancelReductionRate = 0.0;
double GatheringCancleRange = 0;

//--입원 TAB
//평균 재원기간
double HospitalizationNICU = 5;
double HospitalizationICU = 10;

//--백신 TAB
//연령별 백신 접종률
double VaccineAgeRate[StageofAgeGroups] = {0, 0, 0, 0, 0 };
//연령별 백신 접종효과
double VaccineEffect[StageofAgeGroups] = {0, 0, 0, 0, 0 };
//항체생성기간
double AntibodyCreateRange= 14.0;
//백신 접종시기
double VaccineStart = 0; //아직 정의 안됨

//--자원 TAB
//N-95마스크(1명, 1일당 개수)
double MaskNeedNICU;
double MaskNeedICU;
//인공호흡기 (입원환자 중 인공호흡기 사용 비율)
double RespiratorNeedRate = 50.0;

//--검체 TAB
//검체 재검율
double ReinspectionRate = 10.0;
//외래환자 검체비율                (확인필요)
double OutpatientSpecimenTesting = 50.0;

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
    ui->input_extreamlySickTreatRate->setText(QString::number(ExtremelySickTreatRate));

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

    ui->input_vaccineEffect_1->setText(QString::number(VaccineEffect[Age0to6]));
    ui->input_vaccineEffect_2->setText(QString::number(VaccineEffect[Age7to12]));
    ui->input_vaccineEffect_3->setText(QString::number(VaccineEffect[Age13to18]));
    ui->input_vaccineEffect_4->setText(QString::number(VaccineEffect[Age19to64]));
    ui->input_vaccineEffect_5->setText(QString::number(VaccineEffect[Age65toEnd]));

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



void MainWindow::on_input_Age0to6_textChanged()
{
    Population[Age0to6] = (ui->input_Age0to6->toPlainText()).toInt();
    printf("here %d",Population[Age0to6]);
}
