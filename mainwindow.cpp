#include "mainwindow.h"
#include <stdio.h>
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <define.h>
#include <algorithm>  
#include <sstream>
#include <time.h>
#include <qstring.h>
#include <locale>
using namespace std;
#define toKor(str) QString::fromLocal8Bit(str)

/*input 관련 변수들*/
int PopulationTotal =Population[Age0to6]+Population[Age7to12]+Population[Age13to18]+Population[Age19to64]+Population[Age65toEnd];

int contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
int contactTotal7to12 =  ContactMatrix[Age7to12][Age7to12]+ ContactMatrix[Age7to12][Age13to18]+ ContactMatrix[Age7to12][Age19to64]+ ContactMatrix[Age7to12][Age65toEnd];
int contactTotal13to18 =  ContactMatrix[Age13to18][Age13to18]+ ContactMatrix[Age13to18][Age19to64]+ ContactMatrix[Age13to18][Age65toEnd];
int contactTotal19to64 =  ContactMatrix[Age19to64][Age19to64]+ ContactMatrix[Age19to64][Age65toEnd];
int contactTotal65toEnd = ContactMatrix[Age65toEnd][Age65toEnd];

double contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;

/*output 관련 변수들*/
bool outputFlag = false;
int goal=300;
double day = 0;
int steps=0;
int evals = 0;
/**
* The current x value.
*/
double h = 1;
double maxError = 0.02;
double minError = maxError / 4;
double yInVector[OutputArray] = {};
double k1[OutputArray] = {};
double k2[OutputArray] = {};
double k3[OutputArray] = {};
double k4[OutputArray] = {};

int GraphAge = Age65toEnd+1; //default
int csvOutput = 1;
int jpgOutput = 1;

QVector<QVector <double> > SusceptibleArray((NumberofArray));
QVector<QVector <double> > ExposedArray((NumberofArray));
QVector<QVector <double> > AsymptomaticArray((NumberofArray));
QVector<QVector <double> > ModerateArray((NumberofArray));
QVector<QVector <double> > SevereArray((NumberofArray));
QVector<QVector <double> > DeadArray((NumberofArray));
QVector<QVector <double> > ImmuneArray((NumberofArray));
QVector<QVector <double> > RArray((NumberofArray));

QVector<QVector <double> > MaskArray((NumberofArray));
QVector<QVector <double> > RespArray((NumberofArray));
QVector<QVector <double> > AntiviralsArray((NumberofArray));

QVector<QVector <double> > SpecimenArray((NumberofArray));

QVector<QVector <double> > DailyOutpatientArray((NumberofArray));
QVector<QVector <double> > DailyICUArray((NumberofArray));
QVector<QVector <double> > DailyNICUArray((NumberofArray));

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	QString img_path = "images/logo1.jpg";
	QImage img(img_path);
	QPixmap buf = QPixmap::fromImage(img);

	ui->logo1->setPixmap(buf);
	ui->logo1->resize(buf.width(), buf.height());

	QString img_path2 = "images/logo2.jpg";
	QImage img2(img_path2);
	QPixmap buf2 = QPixmap::fromImage(img2);

	ui->logo2->setPixmap(buf2);
	ui->logo2->resize(buf2.width(), buf2.height());

    setDefault();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run(double input) {
	SusceptibleArray.resize(Age65toEnd + 2);
	ExposedArray.resize(Age65toEnd + 2);
	AsymptomaticArray.resize(Age65toEnd + 2);
	ModerateArray.resize(Age65toEnd + 2);
	SevereArray.resize(Age65toEnd + 2);
	DeadArray.resize(Age65toEnd + 2);
	ImmuneArray.resize(Age65toEnd + 2);
	RArray.resize(Age65toEnd + 2);

	MaskArray.resize(Age65toEnd + 2);
	RespArray.resize(Age65toEnd + 2);
	AntiviralsArray.resize(Age65toEnd + 2);

	SpecimenArray.resize(Age65toEnd + 2);

	DailyOutpatientArray.resize(Age65toEnd + 2);
	DailyICUArray.resize(Age65toEnd + 2);
	DailyNICUArray.resize(Age65toEnd + 2);


	for (int r = 0; r < Age65toEnd + 2; r++) {
		SusceptibleArray[r].resize(NumberofArray);
		ExposedArray[r].resize(NumberofArray);
		AsymptomaticArray[r].resize(NumberofArray);
		ModerateArray[r].resize(NumberofArray);
		SevereArray[r].resize(NumberofArray);
		DeadArray[r].resize(NumberofArray);
		ImmuneArray[r].resize(NumberofArray);
		RArray[r].resize(NumberofArray);

		MaskArray[r].resize(NumberofArray);
		RespArray[r].resize(NumberofArray);
		AntiviralsArray[r].resize(NumberofArray);

		SpecimenArray[r].resize(NumberofArray);

		DailyOutpatientArray[r].resize(NumberofArray);
		DailyICUArray[r].resize(NumberofArray);
		DailyNICUArray[r].resize(NumberofArray);

	}

	Initialize();
	InitialY();
	while (day + h < input) {

		MainWindow::step();
	}
	double hold = h;
	while (abs((day - input) / input) > 1E-13) {
		h = min(input - day, h);

		MainWindow::step();
	}

	h = hold;
}
void MainWindow::step() {

	steps++;

	for (int i = 0; i < OutputArray; i++) yInVector[i] = InitY[i];

	// k1
	Evaluation(day, yInVector, k1);
	evals++;

	// k2
	for (int i = 0; i < OutputArray; i++) yInVector[i] = InitY[i] + 0.5 * h * k1[i];

	Evaluation(day + 0.5 * h, yInVector, k2);
	evals++;

	// k3
	for (int i = 0; i < OutputArray; i++) yInVector[i] = InitY[i] + 0.5 * h * k2[i];
	
	Evaluation(day + 0.5 * h, yInVector, k3);
	evals++;

	// Calculate error
	double normK = 0.0;
	double max = 0.0;

	for (int i = 0; i < OutputArray; i++) {
		double diffK1K2 = k1[i] - k2[i];

		normK += diffK1K2 * diffK1K2;

		double absK = abs(k2[i] - k3[i]);

		if (absK > max) max = absK;
	}

	double error = minError;

	if (normK > 0.0) error = max / sqrt(normK);

	// Discard step and decrease h if error is too large
	if (error > maxError) {
		h /= 2;
		return;
	}

	// k4
	for (int i = 0; i < OutputArray; i++) yInVector[i] = InitY[i] + h * k3[i];
	Evaluation(day + h, yInVector, k4);
	evals++;

	// Update x and y
	day += h;
	for (int i = 0; i < OutputArray; i++) InitY[i] += h*(k1[i] + 2 * (k2[i] + k3[i]) + k4[i])/6 ;

	// Increase h, if error was very small
	if (error < minError) h *= 2;

	for (int i = 0; i < StageofAgeGroups+1; i++) {
		SusceptibleArray[i][day] = 0;
		ExposedArray[i][day] = 0;
		AsymptomaticArray[i][day] = 0;
		ModerateArray[i][day] = 0;
		SevereArray[i][day] = 0;
		DeadArray[i][day] = 0;
		ImmuneArray[i][day] = 0;
		RArray[i][day] = 0;

		MaskArray[i][day] = 0;
		RespArray[i][day] = 0;
		AntiviralsArray[i][day] = 0;

		SpecimenArray[i][day] = 0;

		DailyOutpatientArray[i][day] = 0;
		DailyICUArray[i][day] = 0;
		DailyNICUArray[i][day] = 0;

	}
	for (int age = 0; age < StageofAgeGroups; age++) {
		SusceptibleArray[age][day] = total*(InitY[S(age, LowRisk)] + InitY[S(age, HighRisk)]);
		SusceptibleArray[Age65toEnd+1][day] += total*(InitY[S(age, LowRisk)] + InitY[S(age, HighRisk)]);

		for (int k = 0; k < EstageGroups; k++) {
			ExposedArray[age][day] += total*(InitY[E(age, LowRisk, k)] + InitY[E(age, HighRisk, k)]);
			ExposedArray[Age65toEnd + 1][day] += total*(InitY[E(age, LowRisk, k)] + InitY[E(age, HighRisk, k)]);
		}

		for (int k = 0; k < IstageGroups; k++) {
			AsymptomaticArray[age][day] += total*(InitY[A(age, k)]);
			AsymptomaticArray[Age65toEnd + 1][day] += total*(InitY[A(age, k)]);

			ModerateArray[age][day] += total*(InitY[M(age, k)]);
			ModerateArray[Age65toEnd + 1][day] += total*(InitY[M(age, k)]);

			MaskArray[age][day] = total*(MaskNeedICU * (InitY[H(age, k, MedYES, ICU)] + InitY[H(age, k, MedNO, ICU)])
				+ MaskNeedNICU * (InitY[H(age, k, MedYES, NICU)] + InitY[H(age, k, MedNO, NICU)]));
			MaskArray[Age65toEnd + 1][day] += total*(MaskNeedICU * (InitY[H(age, k, MedYES, ICU)] + InitY[H(age, k, MedNO, ICU)])
				+ MaskNeedNICU * (InitY[H(age, k, MedYES, NICU)] + InitY[H(age, k, MedNO, NICU)]));

			RespArray[age][day] = total*(percentage(RespiratorNeedRate) * (InitY[H(age, k, MedYES, ICU)] + InitY[H(age, k, MedNO, ICU)]));
			RespArray[Age65toEnd + 1][day] += total*(percentage(RespiratorNeedRate) * (InitY[H(age, k, MedYES, ICU)] + InitY[H(age, k, MedNO, ICU)]));


			DailyOutpatientArray[age][day] = total*(alpha  * (InitY[V(age, k)] + InitY[X(age, k)])
				+ alphaW[age] * (InitY[W(age, k, MedNO)] + InitY[W(age, k, MedYES)]));

			DailyOutpatientArray[Age65toEnd + 1][day] += total*(alpha  * (InitY[V(age, k)] + InitY[X(age, k)])
				+ alphaW[age] * (InitY[W(age, k, MedNO)] + InitY[W(age, k, MedYES)]));

			SevereArray[age][day] += total*(InitY[V(age, k)] + InitY[X(age, k)]);
			SevereArray[Age65toEnd + 1][day] += total*(InitY[V(age, k)] + InitY[X(age, k)]);

			for (int m = 0; m < MedGroups; m++) {
				SevereArray[age][day] += total*(InitY[W(age, k, m)]);
				SevereArray[Age65toEnd + 1][day] += total*(InitY[W(age, k, m)]);

				for (int c = 1; c < ICUGroups; c++) {
					SevereArray[age][day] += total*(InitY[H(age, k, m, c)]);
					SevereArray[Age65toEnd + 1][day] += total*(InitY[H(age, k, m, c)]);

					if (c == 1) {
						DailyNICUArray[age][day] += total*(InitY[H(age, k, m, c)]);
						DailyNICUArray[Age65toEnd + 1][day] += total*(InitY[H(age, k, m, c)]);
					}
					else if (c == 2) {
						DailyICUArray[age][day] += total*(InitY[H(age, k, m, c)]);
						DailyICUArray[Age65toEnd + 1][day] += total*(InitY[H(age, k, m, c)]);

					}

				}
			}
		}

		DeadArray[age][day] = total*(InitY[D(age)]);
		DeadArray[Age65toEnd + 1][day] += total*(InitY[D(age)]);

		ImmuneArray[age][day] = total*(InitY[I(age)]);
		ImmuneArray[Age65toEnd + 1][day] += total*(InitY[I(age)]);

		AntiviralsArray[age][day] = total*(InitY[AV(age)]);
		AntiviralsArray[Age65toEnd + 1][day] += total*(InitY[AV(age)]);

		SpecimenArray[age][day] = total*(InitY[Spec(age)]);
		SpecimenArray[Age65toEnd + 1][day] += total*(InitY[Spec(age)]);


		for (int rStage = Rstage1; rStage < RstageGroups; rStage++) {
			RArray[age][day] += total*(InitY[R(age, rStage)]);
			RArray[Age65toEnd + 1][day] += total*(InitY[R(age, rStage)]);
		}
	}

}

/*tab별 그래프 그리는 함수들*/
void MainWindow::makeInfectionPlot(){


	for (int i = 7; i > -1; i--) {
		ui->customPlot_infection->removeGraph(i);
	}

	ui->customPlot_infection->setLocale(QLocale(QLocale::Korean));

	ui->customPlot_infection->legend->setVisible(true);
	ui->customPlot_infection->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));

	ui->customPlot_infection->axisRect()->setAutoMargins(QCP::msLeft | QCP::msTop | QCP::msBottom);
	ui->customPlot_infection->axisRect()->setMargins(QMargins(20, 0, 140, 0));
	ui->customPlot_infection->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipFree);
	ui->customPlot_infection->axisRect()->insetLayout()->setInsetRect(0, QRectF(1.0, 0, 0.2, 0.2));
    ui->customPlot_infection->xAxis->setLabel(toKor("일"));
	ui->customPlot_infection->yAxis->setLabel(toKor("인구"));

	// set axes ranges, so we see all data:
	ui->customPlot_infection->xAxis->setRange(0, goal+10);
	ui->customPlot_infection->yAxis->setRange(0, total);

	QVector<double> x(goal);

	for (int i = 0; i<goal; i++) {

		x[i] = i;
	}

	//감수성기 그래프
	ui->customPlot_infection->addGraph();
    ui->customPlot_infection->graph(0)->setData(x, SusceptibleArray[GraphAge]);
	ui->customPlot_infection->graph(0)->setName(toKor("감수성자"));
	ui->customPlot_infection->graph(0)->setPen(QColor(255, 0, 0, 255));
    ui->customPlot_infection->replot();

	//잠복기 그래프
	ui->customPlot_infection->addGraph();
	ui->customPlot_infection->graph(1)->setData(x, ExposedArray[GraphAge]);
	ui->customPlot_infection->graph(1)->setName(toKor("잠복기 감염자"));
	ui->customPlot_infection->graph(1)->setPen(QColor(0, 0, 255, 255));
	ui->customPlot_infection->replot();

	//무증상자 그래프
	ui->customPlot_infection->addGraph();
	ui->customPlot_infection->graph(2)->setData(x, AsymptomaticArray[GraphAge]);
	ui->customPlot_infection->graph(2)->setName(toKor("무증상 감염자"));
	ui->customPlot_infection->graph(2)->setPen(QColor(0, 255, 0, 255));
	ui->customPlot_infection->replot();

	//중증도 중간 그래프
	ui->customPlot_infection->addGraph();
	ui->customPlot_infection->graph(3)->setData(x, ModerateArray[GraphAge]);
	ui->customPlot_infection->graph(3)->setName(toKor("환자 (치료 불필요)"));
	ui->customPlot_infection->graph(3)->setPen(QColor(255, 228, 0, 255));
	ui->customPlot_infection->replot();

	//중증도 높음 그래프
	ui->customPlot_infection->addGraph();
	ui->customPlot_infection->graph(4)->setData(x, SevereArray[GraphAge]);
	ui->customPlot_infection->graph(4)->setName(toKor("환자 (치료 필요)"));
	ui->customPlot_infection->graph(4)->setPen(QColor(255, 0, 221, 255));
	ui->customPlot_infection->replot();

	//사망자 그래프
	ui->customPlot_infection->addGraph();
	ui->customPlot_infection->graph(5)->setData(x, DeadArray[GraphAge]);
	ui->customPlot_infection->graph(5)->setName(toKor("사망자"));
	ui->customPlot_infection->graph(5)->setPen(QColor(0, 216, 255, 255));
	ui->customPlot_infection->replot();

	//회복중 그래프
	ui->customPlot_infection->addGraph();
	ui->customPlot_infection->graph(6)->setData(x, RArray[GraphAge]);
	ui->customPlot_infection->graph(6)->setName(toKor("회복기 환자"));
	ui->customPlot_infection->graph(6)->setPen(QColor(50, 216, 50, 255));
	ui->customPlot_infection->replot();

	//회복 그래프
	ui->customPlot_infection->addGraph();
	ui->customPlot_infection->graph(7)->setData(x, ImmuneArray[GraphAge]);
	ui->customPlot_infection->graph(7)->setName(toKor("회복자"));
	ui->customPlot_infection->graph(7)->setPen(QColor(255, 94, 0, 255));
	ui->customPlot_infection->replot();


	//테이블 크기 조절
    ui->infectionTable->setColumnWidth(0,120);
    ui->infectionTable->setColumnWidth(1,120);
    ui->infectionTable->setColumnWidth(2,120);
    ui->infectionTable->setColumnWidth(3,120);
	ui->infectionTable->setColumnWidth(4,120);
	ui->infectionTable->setColumnWidth(5,100);
	ui->infectionTable->setColumnWidth(6,100);
	ui->infectionTable->setColumnWidth(7, 100);
	

	//테이블 인풋 
	ui->infectionTable->setRowCount(goal);

	for (int i = 0; i < goal; i++) {
		ui->infectionTable->setItem(i, 0, new QTableWidgetItem(QString::number((double)SusceptibleArray[GraphAge][i], 'f')));
	}

	for (int i = 0; i < goal; i++) {
		ui->infectionTable->setItem(i, 1, new QTableWidgetItem(QString::number((double)ExposedArray[GraphAge][i], 'f')));
	}

	for (int i = 0; i < goal; i++) {
		ui->infectionTable->setItem(i, 2, new QTableWidgetItem(QString::number((double)AsymptomaticArray[GraphAge][i], 'f')));
	}

	for (int i = 0; i <goal; i++) {
		ui->infectionTable->setItem(i, 3, new QTableWidgetItem(QString::number((double)ModerateArray[GraphAge][i], 'f')));
	}

	for (int i = 0; i <goal; i++) {
		ui->infectionTable->setItem(i, 4, new QTableWidgetItem(QString::number((double)SevereArray[GraphAge][i], 'f')));
	}

	for (int i = 0; i < goal; i++) {
		ui->infectionTable->setItem(i, 5, new QTableWidgetItem(QString::number((double)DeadArray[GraphAge][i], 'f')));
	}

	for (int i = 0; i < goal; i++) {
		ui->infectionTable->setItem(i, 6, new QTableWidgetItem(QString::number((double)RArray[GraphAge][i], 'f')));
	}

	for (int i = 0; i < goal; i++) {
		ui->infectionTable->setItem(i, 7, new QTableWidgetItem(QString::number((double)ImmuneArray[GraphAge][i], 'f')));
	}
}


void MainWindow::makeResourcePlot(){

	for (int i = 2; i > -1; i--) {
		ui->customPlot_resource->removeGraph(i);
	}

	ui->customPlot_resource->setLocale(QLocale(QLocale::Korean));

	ui->customPlot_resource->legend->setVisible(true);
	ui->customPlot_resource->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));

	ui->customPlot_resource->axisRect()->setAutoMargins(QCP::msLeft | QCP::msTop | QCP::msBottom);
	ui->customPlot_resource->axisRect()->setMargins(QMargins(20, 0, 140, 0));
	ui->customPlot_resource->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipFree);
	ui->customPlot_resource->axisRect()->insetLayout()->setInsetRect(0, QRectF(1.0, 0, 0.2, 0.2));
	ui->customPlot_resource->xAxis->setLabel(toKor("일"));
	ui->customPlot_resource->yAxis->setLabel(toKor("인구"));


	// set axes ranges, so we see all data:
	ui->customPlot_resource->xAxis->setRange(0, goal + 10);
	ui->customPlot_resource->yAxis->setRange(0, total*0.08);

	QVector<double> x(goal);

	for (int i = 0; i<goal; i++) {
		x[i] = i;
	}

	//마스크 그래프
	ui->customPlot_resource->addGraph();
	ui->customPlot_resource->graph(0)->setData(x, MaskArray[GraphAge]);
	ui->customPlot_resource->graph(0)->setName(toKor("N-95 마스크"));
	ui->customPlot_resource->graph(0)->setPen(QColor(255, 0, 0, 255));
	ui->customPlot_resource->replot();

	//인공호흡기 그래프
	ui->customPlot_resource->addGraph();
	ui->customPlot_resource->graph(1)->setData(x, RespArray[GraphAge]);
	ui->customPlot_resource->graph(1)->setName(toKor("인공호흡기"));
	ui->customPlot_resource->graph(1)->setPen(QColor(0, 0, 255, 255));
	ui->customPlot_resource->replot();

	//항바이러스제 그래프
	ui->customPlot_resource->addGraph();
	ui->customPlot_resource->graph(2)->setData(x, AntiviralsArray[GraphAge]);
	ui->customPlot_resource->graph(2)->setName(toKor("항바이러스제"));
	ui->customPlot_resource->graph(2)->setPen(QColor(0, 255, 0, 255));
	ui->customPlot_resource->replot();


	//테이블 크기 조절
	ui->resourceTable->setColumnWidth(0, 150);
	ui->resourceTable->setColumnWidth(1, 150);
	ui->resourceTable->setColumnWidth(2, 150);


	//테이블 인풋 
	ui->resourceTable->setRowCount(goal*0.08);
	for (int i = 0; i < goal; i++) {
		ui->resourceTable->setItem(i, 0, new QTableWidgetItem(QString::number((double)MaskArray[GraphAge][i], 'f')));
	}

	for (int i = 0; i < goal; i++) {
		ui->resourceTable->setItem(i, 1, new QTableWidgetItem(QString::number((double)RespArray[GraphAge][i], 'f')));
	}

	for (int i = 0; i < goal; i++) {
		ui->resourceTable->setItem(i, 2, new QTableWidgetItem(QString::number((double)AntiviralsArray[GraphAge][i], 'f')));
	}
}

void MainWindow::makeSpecimenPlot(){
	ui->customPlot_specimen->removeGraph(0);

	ui->customPlot_specimen->setLocale(QLocale(QLocale::Korean));

	ui->customPlot_specimen->legend->setVisible(true);
	ui->customPlot_specimen->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));

	ui->customPlot_specimen->axisRect()->setAutoMargins(QCP::msLeft | QCP::msTop | QCP::msBottom);
	ui->customPlot_specimen->axisRect()->setMargins(QMargins(20, 0, 140, 0));
	ui->customPlot_specimen->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipFree);
	ui->customPlot_specimen->axisRect()->insetLayout()->setInsetRect(0, QRectF(1.0, 0, 0.2, 0.2));
	ui->customPlot_specimen->xAxis->setLabel(toKor("일"));
	ui->customPlot_specimen->yAxis->setLabel(toKor("인구"));


	// set axes ranges, so we see all data:
	ui->customPlot_specimen->xAxis->setRange(0, goal + 10);
	ui->customPlot_specimen->yAxis->setRange(0, total*0.08);

	QVector<double> x(goal);

	for (int i = 0; i<goal; i++) {
		x[i] = i;
	}

	//검체 수 그래프
	ui->customPlot_specimen->addGraph();
	ui->customPlot_specimen->graph(0)->setData(x, SpecimenArray[GraphAge]);
	ui->customPlot_specimen->graph(0)->setName(toKor("검체 수"));
	ui->customPlot_specimen->graph(0)->setPen(QColor(255, 0, 0, 255));
	ui->customPlot_specimen->replot();


	//테이블 크기 조절
	ui->specimenTable->setColumnWidth(0, 200);


	//테이블 인풋 
	ui->specimenTable->setRowCount(goal);
	for (int i = 0; i < goal; i++) {
		ui->specimenTable->setItem(i, 0, new QTableWidgetItem(QString::number((double)SpecimenArray[GraphAge][i], 'f')));
	}
}


void MainWindow::makeDailyPlot(){

	for (int i = 2; i > -1; i--) {
		ui->customPlot_daily->removeGraph(i);
	}


	ui->customPlot_daily->setLocale(QLocale(QLocale::Korean));

	ui->customPlot_daily->legend->setVisible(true);
	ui->customPlot_daily->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));

	ui->customPlot_daily->axisRect()->setAutoMargins(QCP::msLeft | QCP::msTop | QCP::msBottom);
	ui->customPlot_daily->axisRect()->setMargins(QMargins(20, 0, 140, 0));
	ui->customPlot_daily->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipFree);
	ui->customPlot_daily->axisRect()->insetLayout()->setInsetRect(0, QRectF(1.0, 0, 0.2, 0.2));
	ui->customPlot_daily->xAxis->setLabel(toKor("일"));
	ui->customPlot_daily->yAxis->setLabel(toKor("인구"));


	// set axes ranges, so we see all data:
	ui->customPlot_daily->xAxis->setRange(0, goal + 10);
	ui->customPlot_daily->yAxis->setRange(0, total*0.08);

	QVector<double> x(goal);

	for (int i = 0; i<goal; i++) {
		x[i] = i;
	}

	//외래환자 그래프
	ui->customPlot_daily->addGraph();
	ui->customPlot_daily->graph(0)->setData(x, DailyOutpatientArray[GraphAge]);
	ui->customPlot_daily->graph(0)->setName(toKor("외래환자 수"));
	ui->customPlot_daily->graph(0)->setPen(QColor(255, 0, 0, 255));
	ui->customPlot_daily->replot();

	//중환자실 병상 그래프
	ui->customPlot_daily->addGraph();
	ui->customPlot_daily->graph(1)->setData(x, DailyNICUArray[GraphAge]);
	ui->customPlot_daily->graph(1)->setName(toKor("일반병상수"));
	ui->customPlot_daily->graph(1)->setPen(QColor(0, 0, 255, 255));
	ui->customPlot_daily->replot();

	//일반 병상 그래프
	ui->customPlot_daily->addGraph();
	ui->customPlot_daily->graph(2)->setData(x, DailyICUArray[GraphAge]);
	ui->customPlot_daily->graph(2)->setName(toKor("중환자실병상수"));
	ui->customPlot_daily->graph(2)->setPen(QColor(0, 255, 0, 255));
	ui->customPlot_daily->replot();


	//테이블 크기 조절
	ui->dailyTable->setColumnWidth(0, 200);
	ui->dailyTable->setColumnWidth(1, 200);
	ui->dailyTable->setColumnWidth(2, 200);


	//테이블 인풋 
	ui->dailyTable->setRowCount(goal);
	for (int i = 0; i < goal; i++) {
		ui->dailyTable->setItem(i, 0, new QTableWidgetItem(QString::number((double) DailyOutpatientArray[GraphAge][i], 'f')));
	}

	for (int i = 0; i < goal; i++) {
		ui->dailyTable->setItem(i, 1, new QTableWidgetItem(QString::number((double) DailyNICUArray[GraphAge][i], 'f')));
	}

	for (int i = 0; i < goal; i++) {
		ui->dailyTable->setItem(i, 2, new QTableWidgetItem(QString::number((double)DailyICUArray[GraphAge][i], 'f')));
	}
}

void MainWindow::setDefault()
{

	QDoubleValidator *populationValidator = new QDoubleValidator(this);
	populationValidator->setBottom(0.00);
	populationValidator->setDecimals(4);
	populationValidator->setTop(10000000.00);
	populationValidator->setNotation(QDoubleValidator::StandardNotation);

	QDoubleValidator *percentValidator = new QDoubleValidator(this);
	percentValidator->setBottom(0.00);
	percentValidator->setDecimals(4);
	percentValidator->setTop(100.00);
	percentValidator->setNotation(QDoubleValidator::StandardNotation);

	QDoubleValidator *dayValidator = new QDoubleValidator(this);
	dayValidator->setBottom(0.00);
	dayValidator->setDecimals(4);
	dayValidator->setTop(300.00);
	dayValidator->setNotation(QDoubleValidator::StandardNotation);

	QDoubleValidator *thousandValidator = new QDoubleValidator(this);
	thousandValidator->setBottom(0.00);
	thousandValidator->setDecimals(4);
	thousandValidator->setTop(1000.00);
	thousandValidator->setNotation(QDoubleValidator::StandardNotation);

	QDoubleValidator *twentyValidator = new QDoubleValidator(this);
	twentyValidator->setBottom(0.00);
	twentyValidator->setDecimals(4);
	twentyValidator->setTop(1000.00);
	twentyValidator->setNotation(QDoubleValidator::StandardNotation);

	/*인구 tab 기본값 세팅*/
	ui->input_Age0to6->setText(QString::number(Population[0]));
	ui->input_Age7to12->setText(QString::number(Population[1]));
	ui->input_Age13to18->setText(QString::number(Population[2]));
	ui->input_Age19to64->setText(QString::number(Population[3]));
	ui->input_Age65toEnd->setText(QString::number(Population[4]));

	ui->input_contact_1_1->setText(QString::number(ContactMatrix[0][0]));
	ui->input_contact_1_2->setText(QString::number(ContactMatrix[0][1]));
	ui->input_contact_1_3->setText(QString::number(ContactMatrix[0][2]));
	ui->input_contact_1_4->setText(QString::number(ContactMatrix[0][3]));
	ui->input_contact_1_5->setText(QString::number(ContactMatrix[0][4]));

	ui->input_contact_2_2->setText(QString::number(ContactMatrix[1][1]));
	ui->input_contact_2_3->setText(QString::number(ContactMatrix[1][2]));
	ui->input_contact_2_4->setText(QString::number(ContactMatrix[1][3]));
	ui->input_contact_2_5->setText(QString::number(ContactMatrix[1][4]));

	ui->input_contact_3_3->setText(QString::number(ContactMatrix[2][2]));
	ui->input_contact_3_4->setText(QString::number(ContactMatrix[2][3]));
	ui->input_contact_3_5->setText(QString::number(ContactMatrix[2][4]));

	ui->input_contact_4_4->setText(QString::number(ContactMatrix[3][3]));
	ui->input_contact_4_5->setText(QString::number(ContactMatrix[3][4]));

	ui->input_contact_5_5->setText(QString::number(ContactMatrix[4][4]));

	ui->input_SchoolRatio0to6->setText(QString::number(SchoolContactRate[0]));
	ui->input_SchoolRatio7to12->setText(QString::number(SchoolContactRate[1]));
	ui->input_SchoolRatio13to18->setText(QString::number(SchoolContactRate[2]));

	/*인풋 예외 처리*/
	ui->input_Age0to6->setValidator(new QIntValidator(0, 10000000, this));
	ui->input_Age7to12->setValidator(new QIntValidator(0, 10000000, this));
	ui->input_Age13to18->setValidator(new QIntValidator(0, 10000000, this));
	ui->input_Age19to64->setValidator(new QIntValidator(0, 10000000, this));
	ui->input_Age65toEnd->setValidator(new QIntValidator(0, 10000000, this));

	ui->input_contact_1_1->setValidator(populationValidator);
	ui->input_contact_1_2->setValidator(populationValidator);
	ui->input_contact_1_3->setValidator(populationValidator);
	ui->input_contact_1_4->setValidator(populationValidator);
	ui->input_contact_1_5->setValidator(populationValidator);

	ui->input_contact_2_2->setValidator(thousandValidator);
	ui->input_contact_2_3->setValidator(thousandValidator);
	ui->input_contact_2_4->setValidator(thousandValidator);
	ui->input_contact_2_5->setValidator(thousandValidator);

	ui->input_contact_3_3->setValidator(thousandValidator);
	ui->input_contact_3_4->setValidator(thousandValidator);
	ui->input_contact_3_5->setValidator(thousandValidator);

	ui->input_contact_4_4->setValidator(thousandValidator);
	ui->input_contact_4_5->setValidator(thousandValidator);

	ui->input_contact_5_5->setValidator(thousandValidator);

	ui->input_SchoolRatio0to6->setValidator(percentValidator);
	ui->input_SchoolRatio7to12->setValidator(percentValidator);
	ui->input_SchoolRatio13to18->setValidator(percentValidator);

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


	/*인풋 예외 처리*/
	ui->input_LatentPeriod->setValidator(thousandValidator);

	ui->input_infDuration_1_1->setValidator(thousandValidator);
	ui->input_infDuration_1_2->setValidator(thousandValidator);
	ui->input_infDuration_1_3->setValidator(thousandValidator);
	ui->input_infDuration_2_1->setValidator(thousandValidator);
	ui->input_infDuration_2_2->setValidator(thousandValidator);
	ui->input_infDuration_2_3->setValidator(thousandValidator);

	ui->input_returnToWork->setValidator(thousandValidator);

	ui->input_MildRate->setValidator(percentValidator);
	ui->input_SevereRate->setValidator(percentValidator);

	ui->input_high_1_1->setValidator(percentValidator);
	ui->input_high_1_2->setValidator(percentValidator);
	ui->input_high_1_3->setValidator(percentValidator);
	ui->input_high_2_1->setValidator(percentValidator);
	ui->input_high_2_2->setValidator(percentValidator);
	ui->input_high_2_3->setValidator(percentValidator);
	ui->input_high_3_1->setValidator(percentValidator);
	ui->input_high_3_2->setValidator(percentValidator);
	ui->input_high_3_3->setValidator(percentValidator);

	ui->input_dead_1->setValidator(percentValidator);
	ui->input_dead_2->setValidator(percentValidator);
	ui->input_dead_3->setValidator(percentValidator);

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

	/*인풋 예외 처리*/
	QDoubleValidator *r0Validator = new QDoubleValidator(this);
	r0Validator->setBottom(0.00);
	r0Validator->setDecimals(4);
	r0Validator->setTop(5.00);
	r0Validator->setNotation(QDoubleValidator::StandardNotation);
	ui->input_R0->setValidator(r0Validator);

	ui->input_halfInfectiosRate->setValidator(percentValidator);

	ui->input_lastLatent->setValidator(percentValidator);
	ui->input_asymptomatic->setValidator(percentValidator);
	ui->input_moderate->setValidator(percentValidator);

	ui->input_isolModerate->setValidator(percentValidator);
	ui->input_isolSevereHome->setValidator(percentValidator);
	ui->input_isolSevereHospital->setValidator(percentValidator);
	ui->input_isolStart->setValidator(dayValidator);
	ui->input_isolEnd->setValidator(dayValidator);

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

	/*인풋 예외 처리*/
	ui->input_antiviralsRate->setValidator(percentValidator);

	ui->input_medicalHelp->setValidator(thousandValidator);
	ui->input_antiviralsHelp->setValidator(thousandValidator);

	ui->input_verySickTreat->setValidator(percentValidator);
	ui->input_verySickTreatStart->setValidator(dayValidator);
	ui->input_verySickTreatEnd->setValidator(dayValidator);

	ui->input_extreamlySickTreat->setValidator(percentValidator);
	ui->input_extreamlySickTreatStart->setValidator(dayValidator);
	ui->input_extreamlySickTreatEnd->setValidator(dayValidator);

	ui->input_contagiousnessReduct->setValidator(percentValidator);
	ui->input_durationReduct->setValidator(percentValidator);
	ui->input_HospitailizationReduct->setValidator(percentValidator);

	/*격리 tab 기본값 세팅*/
	ui->input_contactReduct->setText(QString::number(ContactReductionRate));
	ui->input_contactReductStart->setText(QString::number(ContactReductionRangeBegin));
	ui->input_contactReductEnd->setText(QString::number(ContactReductionRangeEnd));

	ui->input_schoolCloseRangeStart->setText(QString::number(SchoolCloseRangeBegin));
	ui->input_schoolCloseRangeEnd->setText(QString::number(SchoolCloseRangeEnd));

	ui->input_gatheringCancel->setText(QString::number(GatheringCancelReductionRate));
	ui->input_gatheringCancelStart->setText(QString::number(GatheringCancleRangeBegin));
	ui->input_gatheringCancelEnd->setText(QString::number(GatheringCancleRangeEnd));

	/*인풋 예외 처리*/
	ui->input_contactReduct->setValidator(percentValidator);
	ui->input_contactReductStart->setValidator(dayValidator);
	ui->input_contactReductEnd->setValidator(dayValidator);

	ui->input_schoolCloseRangeStart->setValidator(dayValidator);
	ui->input_schoolCloseRangeEnd->setValidator(dayValidator);

	ui->input_gatheringCancel->setValidator(percentValidator);
	ui->input_gatheringCancelStart->setValidator(dayValidator);
	ui->input_gatheringCancelEnd->setValidator(dayValidator);

	/*입원 tab 기본값 세팅*/
	ui->input_NICU->setText(QString::number(HospitalizationNICU));
	ui->input_ICU->setText(QString::number(HospitalizationICU));

	/*인풋 예외 처리*/
	ui->input_NICU->setValidator(twentyValidator);
	ui->input_ICU->setValidator(twentyValidator);

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

	/*인풋 예외 처리*/
	ui->input_vaccine_1->setValidator(percentValidator);
	ui->input_vaccine_2->setValidator(percentValidator);
	ui->input_vaccine_3->setValidator(percentValidator);
	ui->input_vaccine_4->setValidator(percentValidator);
	ui->input_vaccine_5->setValidator(percentValidator);

	ui->input_vaccineEffect_1->setValidator(percentValidator);
	ui->input_vaccineEffect_2->setValidator(percentValidator);
	ui->input_vaccineEffect_3->setValidator(percentValidator);
	ui->input_vaccineEffect_4->setValidator(percentValidator);
	ui->input_vaccineEffect_5->setValidator(percentValidator);

	ui->input_antibodyRange->setValidator(twentyValidator);
	ui->input_vaccineStart->setValidator(dayValidator);

	/*자원 tab 기본값 세팅*/
	ui->input_mask_NICU->setText(QString::number(MaskNeedNICU));
	ui->input_mask_ICU->setText(QString::number(MaskNeedICU));

	ui->input_respRate->setText(QString::number(RespiratorNeedRate));

	/*인풋 예외 처리*/
	ui->input_mask_NICU->setValidator(thousandValidator);
	ui->input_mask_ICU->setValidator(thousandValidator);

	ui->input_respRate->setValidator(percentValidator);

	/*검체 tab 기본값 세팅*/
	ui->input_reinspect->setText(QString::number(ReinspectionRate));
	ui->input_outpatient->setText(QString::number(OutpatientSpecimenTesting));


	/*인풋 예외 처리*/
	ui->input_reinspect->setValidator(percentValidator);
	ui->input_outpatient->setValidator(percentValidator);
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
	ui->input_Age0to6->setText(QString::number(Population[0]));
	ui->input_Age7to12->setText(QString::number(Population[1]));
	ui->input_Age13to18->setText(QString::number(Population[2]));
	ui->input_Age19to64->setText(QString::number(Population[3]));
	ui->input_Age65toEnd->setText(QString::number(Population[4]));

	ui->input_contact_1_1->setText(QString::number(ContactMatrix[0][0]));
	ui->input_contact_1_2->setText(QString::number(ContactMatrix[0][1]));
	ui->input_contact_1_3->setText(QString::number(ContactMatrix[0][2]));
	ui->input_contact_1_4->setText(QString::number(ContactMatrix[0][3]));
	ui->input_contact_1_5->setText(QString::number(ContactMatrix[0][4]));

	ui->input_contact_2_2->setText(QString::number(ContactMatrix[1][1]));
	ui->input_contact_2_3->setText(QString::number(ContactMatrix[1][2]));
	ui->input_contact_2_4->setText(QString::number(ContactMatrix[1][3]));
	ui->input_contact_2_5->setText(QString::number(ContactMatrix[1][4]));

	ui->input_contact_3_3->setText(QString::number(ContactMatrix[2][2]));
	ui->input_contact_3_4->setText(QString::number(ContactMatrix[2][3]));
	ui->input_contact_3_5->setText(QString::number(ContactMatrix[2][4]));

	ui->input_contact_4_4->setText(QString::number(ContactMatrix[3][3]));
	ui->input_contact_4_5->setText(QString::number(ContactMatrix[3][4]));

	ui->input_contact_5_5->setText(QString::number(ContactMatrix[4][4]));

    ui->areaWidget->hide();
}

void MainWindow::saveInput() {

	/*인구 탭*/
	SchoolContactRate[0] = (double)ui->input_SchoolRatio0to6->text().toDouble();
	SchoolContactRate[1] = (double)ui->input_SchoolRatio7to12->text().toDouble();
	SchoolContactRate[2] = (double)ui->input_SchoolRatio13to18->text().toDouble();

	/*질병 탭*/

	LatentPeriod = (double)ui->input_LatentPeriod->text().toDouble();

	InfectiousDuration[NonSevere][0] = (double)ui->input_infDuration_1_1->text().toDouble();
	InfectiousDuration[NonSevere][1] = (double)ui->input_infDuration_1_2->text().toDouble();
	InfectiousDuration[NonSevere][2] = (double)ui->input_infDuration_1_3->text().toDouble();

	InfectiousDuration[Severe][0] = (double)ui->input_infDuration_2_1->text().toDouble();
	InfectiousDuration[Severe][1] = (double)ui->input_infDuration_2_2->text().toDouble();
	InfectiousDuration[Severe][2] = (double)ui->input_infDuration_2_3->text().toDouble();

	ReturntoWorkPeriod = (double)ui->input_returnToWork->text().toDouble();

	MildRate = (double)ui->input_MildRate->text().toDouble();
	SevereRate = (double)ui->input_SevereRate->text().toDouble();

	HighRiskRate[0] = (double)ui->input_high_1_1->text().toDouble();
	HighRiskRate[1] = (double)ui->input_high_1_2->text().toDouble();
	HighRiskRate[2] = (double)ui->input_high_1_3->text().toDouble();

	LowRiskHospitalRate[0] = (double)ui->input_high_2_1->text().toDouble();
	LowRiskHospitalRate[1] = (double)ui->input_high_2_2->text().toDouble();
	LowRiskHospitalRate[2] = (double)ui->input_high_2_3->text().toDouble();

	HighRiskHospitalRate[0] = (double)ui->input_high_3_1->text().toDouble();
	HighRiskHospitalRate[1] = (double)ui->input_high_3_2->text().toDouble();
	HighRiskHospitalRate[2] = (double)ui->input_high_3_3->text().toDouble();

	DeadRate[0] = (double)ui->input_dead_1->text().toDouble();
	DeadRate[1] = (double)ui->input_dead_2->text().toDouble();
	DeadRate[2] = (double)ui->input_dead_3->text().toDouble();

	/*감염성 탭*/
	R0 = (double)ui->input_R0->text().toDouble();

	HalfInfectiousRate = (double)ui->input_halfInfectiosRate->text().toDouble();

	LastLatentPeriodCase = (double)ui->input_lastLatent->text().toDouble();
	AsymptomaticCase = (double)ui->input_asymptomatic->text().toDouble();
	ModerateCase = (double)ui->input_moderate->text().toDouble();

	ModerateCaseIsolation = (double)ui->input_isolModerate->text().toDouble();
	SevereHomeCaseIsolation = (double)ui->input_isolSevereHome->text().toDouble();
	SevereHospitalCaseIsolation = (double)ui->input_isolSevereHospital->text().toDouble();

	RangeofIsolationBegin = (int)ui->input_isolStart->text().toInt();
	RangeofIsolationEnd = (int)ui->input_isolEnd->text().toInt();

	/*치료 탭*/
	AntiviralsInjectionRate = (double)ui->input_antiviralsRate->text().toDouble();
	antiviralRessource = percentage(AntiviralsInjectionRate);

	MedicalHelp = (double)ui->input_medicalHelp->text().toDouble();
	consultationDelay = changehour(MedicalHelp);
	AntiviralsHelp = (double)ui->input_antiviralsHelp->text().toDouble();

	VerySickTreatRate = (double)ui->input_verySickTreat->text().toDouble();
	VerySickTreatRangeBegin = (double)ui->input_verySickTreatStart->text().toDouble();
	VerySickTreatRangeEnd = (double)ui->input_verySickTreatEnd->text().toDouble();

	ExtremelySickTreatRate = (double)ui->input_extreamlySickTreat->text().toDouble();
	ExtremelySickTreatRangeBegin = (double)ui->input_extreamlySickTreatStart->text().toDouble();
	ExtremelySickTreatRangeEnd = (double)ui->input_extreamlySickTreatEnd->text().toDouble();

	ContagiousnessReduction = (double)ui->input_contagiousnessReduct->text().toDouble();
	DiseaseDurationReduction = (double)ui->input_durationReduct->text().toDouble();
	HospitalizationReduction = (double)ui->input_HospitailizationReduct->text().toDouble();

	/*격리 탭*/
	ContactReductionRate = (double)ui->input_contactReduct->text().toDouble();
	ContactReductionRangeBegin = (double)ui->input_contactReductStart->text().toDouble();
	ContactReductionRangeEnd = (double)ui->input_contactReductEnd->text().toDouble();

	SchoolCloseRangeBegin = (double)ui->input_schoolCloseRangeStart->text().toDouble();
	SchoolCloseRangeEnd = (double)ui->input_schoolCloseRangeEnd->text().toDouble();


	GatheringCancelReductionRate = (double)ui->input_gatheringCancel->text().toDouble();
	GatheringCancleRangeBegin = (double)ui->input_gatheringCancelStart->text().toDouble();
	GatheringCancleRangeEnd = (double)ui->input_gatheringCancelEnd->text().toDouble();

	/*입원 탭*/
	HospitalizationNICU = (double)ui->input_NICU->text().toDouble();
	HospitalizationICU = (double)ui->input_ICU->text().toDouble();

	/*백신 탭*/
	VaccineAgeRate[0] = (double)ui->input_vaccine_1->text().toDouble();
	VaccineAgeRate[1] = (double)ui->input_vaccine_2->text().toDouble();
	VaccineAgeRate[2] = (double)ui->input_vaccine_3->text().toDouble();
	VaccineAgeRate[3] = (double)ui->input_vaccine_4->text().toDouble();
	VaccineAgeRate[4] = (double)ui->input_vaccine_5->text().toDouble();

	VaccineEffectAgeRate[0] = (double)ui->input_vaccineEffect_1->text().toDouble();
	VaccineEffectAgeRate[1] = (double)ui->input_vaccineEffect_2->text().toDouble();
	VaccineEffectAgeRate[2] = (double)ui->input_vaccineEffect_3->text().toDouble();
	VaccineEffectAgeRate[3] = (double)ui->input_vaccineEffect_4->text().toDouble();
	VaccineEffectAgeRate[4] = (double)ui->input_vaccineEffect_5->text().toDouble();

	AntibodyCreateRange = (double)ui->input_antibodyRange->text().toDouble();
	VaccineStart = (double)ui->input_vaccineStart->text().toDouble();

	/*자원 탭*/
	MaskNeedNICU = (double)ui->input_mask_NICU->text().toDouble();
	MaskNeedICU = (double)ui->input_mask_ICU->text().toDouble();

	RespiratorNeedRate = (double)ui->input_respRate->text().toDouble();

	/*검체 탭*/
	ReinspectionRate = (double)ui->input_reinspect->text().toDouble();
	OutpatientSpecimenTesting = (double)ui->input_outpatient->text().toDouble();
}

//출력화면 이동 버튼 클릭
void MainWindow::on_outputPageBtn_clicked()
{
	outputFlag = true;
	MainWindow::saveInput();

	for (int i = 0; i < OutputArray; i++) {
		yInVector[i] = 0;
		k1[i] = 0;
		k2[i] = 0;
		k3[i] = 0;
		k4[i] = 0;
	}
	day = 0;
	steps = 0;
	evals = 0;
	h = 1;
	maxError = 0.02;
	minError = maxError / 4;

	MainWindow::run(goal);
    ui->outputWidget->show();
    ui->outputWidget->activateWindow();
    ui->outputWidget->raise();

	MainWindow::makeInfectionPlot();
	MainWindow::makeResourcePlot();
	MainWindow::makeSpecimenPlot();
	MainWindow::makeDailyPlot();
}
//입력화면 이동 버튼 클릭
void MainWindow::on_inputPageBtn_clicked()
{
    ui->inputWidget->show();
    ui->inputWidget->activateWindow();
    ui->inputWidget->raise();
}

/*인구 tab input 받아오기*/
void MainWindow::on_input_Age0to6_textChanged(const QString &arg1)
{
	
    Population[Age0to6] = ui->input_Age0to6->text().toDouble();
    PopulationTotal =Population[Age0to6]+Population[Age7to12]+Population[Age13to18]+Population[Age19to64]+Population[Age65toEnd];
    ui->input_AgeTotal->setText(QString::number(PopulationTotal));
}

void MainWindow::on_input_Age7to12_textChanged(const QString &arg1)
{
    Population[Age7to12] = ui->input_Age7to12->text().toDouble();
    PopulationTotal =Population[Age0to6]+Population[Age7to12]+Population[Age13to18]+Population[Age19to64]+Population[Age65toEnd];
    ui->input_AgeTotal->setText(QString::number(PopulationTotal));
}

void MainWindow::on_input_Age13to18_textChanged(const QString &arg1)
{
    Population[Age13to18] = ui->input_Age13to18->text().toDouble();
    PopulationTotal =Population[Age0to6]+Population[Age7to12]+Population[Age13to18]+Population[Age19to64]+Population[Age65toEnd];
    ui->input_AgeTotal->setText(QString::number(PopulationTotal));
}

void MainWindow::on_input_Age19to64_textChanged(const QString &arg1)
{
    Population[Age19to64] = ui->input_Age19to64->text().toDouble();
    PopulationTotal =Population[Age0to6]+Population[Age7to12]+Population[Age13to18]+Population[Age19to64]+Population[Age65toEnd];
    ui->input_AgeTotal->setText(QString::number(PopulationTotal));
}

void MainWindow::on_input_Age65toEnd_textChanged(const QString &arg1)
{
    Population[Age65toEnd] = ui->input_Age65toEnd->text().toDouble();
    PopulationTotal =Population[Age0to6]+Population[Age7to12]+Population[Age13to18]+Population[Age19to64]+Population[Age65toEnd];
    ui->input_AgeTotal->setText(QString::number(PopulationTotal));
}

void MainWindow::on_input_contact_1_1_textChanged(const QString &arg1)
{
    ContactMatrix[Age0to6][Age0to6] = ui->input_contact_1_1->text().toDouble();
    contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_1_2_textChanged(const QString &arg1)
{
    ContactMatrix[Age0to6][Age7to12] = ui->input_contact_1_2->text().toDouble();
    contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_1_3_textChanged(const QString &arg1)
{
    ContactMatrix[Age0to6][Age13to18] = ui->input_contact_1_3->text().toDouble();
    contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_1_4_textChanged(const QString &arg1)
{
    ContactMatrix[Age0to6][Age19to64] = ui->input_contact_1_4->text().toDouble();
    contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_1_5_textChanged(const QString &arg1)
{
    ContactMatrix[Age0to6][Age65toEnd] = ui->input_contact_1_5->text().toDouble();
    contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}


void MainWindow::on_input_contact_2_2_textChanged(const QString &arg1)
{
    ContactMatrix[Age7to12][Age7to12] = ui->input_contact_2_2->text().toDouble();
    contactTotal7to12 =  ContactMatrix[Age7to12][Age7to12]+ ContactMatrix[Age7to12][Age13to18]+ ContactMatrix[Age7to12][Age19to64]+ ContactMatrix[Age7to12][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
}

void MainWindow::on_input_contact_2_3_textChanged(const QString &arg1)
{
    ContactMatrix[Age7to12][Age13to18] = ui->input_contact_2_3->text().toDouble();
    contactTotal7to12 =  ContactMatrix[Age7to12][Age7to12]+ ContactMatrix[Age7to12][Age13to18]+ ContactMatrix[Age7to12][Age19to64]+ ContactMatrix[Age7to12][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;

}

void MainWindow::on_input_contact_2_4_textChanged(const QString &arg1)
{
    ContactMatrix[Age7to12][Age19to64] = ui->input_contact_2_4->text().toDouble();
    contactTotal7to12 =  ContactMatrix[Age7to12][Age7to12]+ ContactMatrix[Age7to12][Age13to18]+ ContactMatrix[Age7to12][Age19to64]+ ContactMatrix[Age7to12][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;

}

void MainWindow::on_input_contact_2_5_textChanged(const QString &arg1)
{
    ContactMatrix[Age7to12][Age65toEnd] = ui->input_contact_2_5->text().toDouble();
    contactTotal7to12 =  ContactMatrix[Age7to12][Age7to12]+ ContactMatrix[Age7to12][Age13to18]+ ContactMatrix[Age7to12][Age19to64]+ ContactMatrix[Age7to12][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;

}

void MainWindow::on_input_contact_3_3_textChanged(const QString &arg1)
{
    ContactMatrix[Age13to18][Age13to18] = ui->input_contact_3_3->text().toDouble();
    contactTotal13to18 =  ContactMatrix[Age13to18][Age13to18]+ ContactMatrix[Age13to18][Age19to64]+ ContactMatrix[Age13to18][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;

}

void MainWindow::on_input_contact_3_4_textChanged(const QString &arg1)
{
    ContactMatrix[Age13to18][Age19to64] = ui->input_contact_3_4->text().toDouble();
    contactTotal13to18 =  ContactMatrix[Age13to18][Age13to18]+ ContactMatrix[Age13to18][Age19to64]+ ContactMatrix[Age13to18][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;

}

void MainWindow::on_input_contact_3_5_textChanged(const QString &arg1)
{
    ContactMatrix[Age13to18][Age65toEnd] = ui->input_contact_3_5->text().toDouble();
    contactTotal13to18 =  ContactMatrix[Age13to18][Age13to18]+ ContactMatrix[Age13to18][Age19to64]+ ContactMatrix[Age13to18][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;

}

void MainWindow::on_input_contact_4_4_textChanged(const QString &arg1)
{
    ContactMatrix[Age19to64][Age19to64] = ui->input_contact_4_4->text().toDouble();
    contactTotal19to64 =  ContactMatrix[Age19to64][Age19to64]+ ContactMatrix[Age19to64][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;

}

void MainWindow::on_input_contact_4_5_textChanged(const QString &arg1)
{
    ContactMatrix[Age19to64][Age65toEnd] = ui->input_contact_4_5->text().toDouble();
    contactTotal19to64 =  ContactMatrix[Age19to64][Age19to64]+ ContactMatrix[Age19to64][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;

}

void MainWindow::on_input_contact_5_5_textChanged(const QString &arg1)
{
    ContactMatrix[Age65toEnd][Age65toEnd] = ui->input_contact_5_5->text().toDouble();
    contactTotal65toEnd = ContactMatrix[Age65toEnd][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;

}

/*output 나이 선택*/
void MainWindow::on_age_checkBox1_clicked()
{
    GraphAge = Age0to6;


	MainWindow::makeInfectionPlot();
	MainWindow::makeResourcePlot();
	MainWindow::makeSpecimenPlot();
	MainWindow::makeDailyPlot();
}

void MainWindow::on_age_checkBox2_clicked()
{
    GraphAge = Age7to12;

	MainWindow::makeInfectionPlot();
	MainWindow::makeResourcePlot();
	MainWindow::makeSpecimenPlot();
	MainWindow::makeDailyPlot();
}

void MainWindow::on_age_checkBox3_clicked()
{
    GraphAge = Age13to18;

	MainWindow::makeInfectionPlot();
	MainWindow::makeResourcePlot();
	MainWindow::makeSpecimenPlot();
	MainWindow::makeDailyPlot();
}

void MainWindow::on_age_checkBox4_clicked()
{
    GraphAge = Age19to64;

	MainWindow::makeInfectionPlot();
	MainWindow::makeResourcePlot();
	MainWindow::makeSpecimenPlot();
	MainWindow::makeDailyPlot();
}

void MainWindow::on_age_checkBox5_clicked()
{
    GraphAge = Age65toEnd;

	MainWindow::makeInfectionPlot();
	MainWindow::makeResourcePlot();
	MainWindow::makeSpecimenPlot();
	MainWindow::makeDailyPlot();
}

void MainWindow::on_age_checkBox6_clicked()
{

	GraphAge = Age65toEnd+1;

	MainWindow::makeInfectionPlot();
	MainWindow::makeResourcePlot();
	MainWindow::makeSpecimenPlot();
	MainWindow::makeDailyPlot();
}

void MainWindow::on_actionOpen_triggered()

{
	QString filter = "KISIM Files (*.kcim)";
	QString filename = QFileDialog::getOpenFileName(this, tr("open"), "", filter, &filter);
	QFile inputFile(toKor(filename.toLocal8Bit()));
	if (inputFile.open(QIODevice::ReadOnly))
	{

		int linecount = 0;
		QTextStream in(&inputFile);
		while (!in.atEnd())
		{
			QString line = in.readLine();
			
			switch (linecount) {

			case 0:
				Population[0] = line.toDouble();
				break;
			case 1:
				Population[1] = line.toDouble();
				break;
			case 2:
				Population[2] = line.toDouble();
				break;
			case 3:
				Population[3] = line.toDouble();
				break;
			case 4:
				Population[4] = line.toDouble();
				break;
			case 5:
				ContactMatrix[0][0] = line.toDouble();
				break;
			case 6:
				ContactMatrix[0][1] = line.toDouble();
				break;
			case 7:
				ContactMatrix[0][2] = line.toDouble();
				break;
			case 8:
				ContactMatrix[0][3] = line.toDouble();
				break;
			case 9:
				ContactMatrix[0][4] = line.toDouble();
				break;
			case 10:
				ContactMatrix[1][1] = line.toDouble();
				break;
			case 11:
				ContactMatrix[1][2] = line.toDouble();
				break;
			case 12:
				ContactMatrix[1][3] = line.toDouble();
				break;
			case 13:
				ContactMatrix[1][4] = line.toDouble();
				break;
			case 14:
				ContactMatrix[2][2] = line.toDouble();
				break;
			case 15:
				ContactMatrix[2][3] = line.toDouble();
				break;
			case 16:
				ContactMatrix[2][4] = line.toDouble();
				break;
			case 17:
				ContactMatrix[3][3] = line.toDouble();
				break;
			case 18:
				ContactMatrix[3][4] = line.toDouble();
				break;
			case 19:
				ContactMatrix[4][4] = line.toDouble();
				break;
			case 20:
				SchoolContactRate[0] = line.toDouble();
				break;
			case 21:
				SchoolContactRate[1] = line.toDouble();
				break;
			case 22:
				SchoolContactRate[2] = line.toDouble();
				break;
			case 23:
				LatentPeriod = line.toDouble();
				break;
			case 24:
				InfectiousDuration[0][0] = line.toDouble();
				break;
			case 25:
				InfectiousDuration[0][1] = line.toDouble();
				break;
			case 26:
				InfectiousDuration[0][2] = line.toDouble();
				break;
			case 27:
				InfectiousDuration[1][0] = line.toDouble();
				break;
			case 28:
				InfectiousDuration[1][1] = line.toDouble();
				break;
			case 29:
				InfectiousDuration[1][2] = line.toDouble();
				break;
			case 30:
				SevereRate = line.toDouble();
				break;
			case 31:
				MildRate = line.toDouble();
				break;
			case 32:
				ReturntoWorkPeriod = line.toDouble();
				break;
			case 33:
				HighRiskRate[0] = line.toDouble();
				break;
			case 34:
				HighRiskRate[1] = line.toDouble();
				break;
			case 35:
				HighRiskRate[2] = line.toDouble();
				break;
			case 36:
				LowRiskHospitalRate[0] = line.toDouble();
				break;
			case 37:
				LowRiskHospitalRate[1] = line.toDouble();
				break;
			case 38:
				LowRiskHospitalRate[2] = line.toDouble();
				break;
			case 39:
				HighRiskHospitalRate[0] = line.toDouble();
				break;
			case 40:
				HighRiskHospitalRate[1] = line.toDouble();
				break;
			case 41:
				HighRiskHospitalRate[2] = line.toDouble();
				break;
			case 42:
				DeadRate[0] = line.toDouble();
				break;
			case 43:
				DeadRate[1] = line.toDouble();
				break;
			case 44:
				DeadRate[2] = line.toDouble();
				break;
			case 45:
				R0 = line.toDouble();
				break;
			case 46:
				HalfInfectiousRate = line.toDouble();
				break;
			case 47:
				LastLatentPeriodCase = line.toDouble();
				break;
			case 48:
				AsymptomaticCase = line.toDouble();
				break;
			case 49:
				ModerateCase = line.toDouble();
				break;
			case 50:
				ModerateCaseIsolation = line.toDouble();
				break;
			case 51:
				SevereHomeCaseIsolation = line.toDouble();
				break;
			case 52:
				SevereHospitalCaseIsolation = line.toDouble();
				break;
			case 53:
				RangeofIsolationBegin = line.toInt();
				break;
			case 54:
				RangeofIsolationEnd = line.toInt();
				break;
			case 55:
				AntiviralsInjectionRate = line.toDouble();
				break;
			case 56:
				MedicalHelp = line.toDouble();
				break;
			case 57:
				AntiviralsHelp = line.toDouble();
				break;
			case 58:
				VerySickTreatRate = line.toDouble();
				break;
			case 59:
				VerySickTreatRangeBegin = line.toInt();
				break;
			case 60:
				VerySickTreatRangeEnd = line.toInt();
				break;
			case 61:
				ExtremelySickTreatRate = line.toDouble();
				break;
			case 62:
				ExtremelySickTreatRangeBegin = line.toInt();
				break;
			case 63:
				ExtremelySickTreatRangeEnd = line.toInt();
				break;
			case 64:
				ContagiousnessReduction = line.toDouble();
				break;
			case 65:
				DiseaseDurationReduction = line.toDouble();
				break;
			case 66:
				HospitalizationReduction = line.toDouble();
				break;
			case 67:
				ContactReductionRate = line.toDouble();
				break;
			case 68:
				ContactReductionRangeBegin = line.toInt();
				break;
			case 69:
				ContactReductionRangeEnd = line.toInt();
				break;
			case 70:
				SchoolCloseRangeBegin = line.toInt();
				break;
			case 71:
				SchoolCloseRangeEnd = line.toInt();
				break;
			case 72:
				GatheringCancelReductionRate = line.toDouble();
				break;
			case 73:
				GatheringCancleRangeBegin = line.toInt();
				break;
			case 74:
				GatheringCancleRangeEnd = line.toInt();
				break;
			case 75:
				HospitalizationNICU = line.toDouble();
				break;
			case 76:
				HospitalizationICU = line.toDouble();
				break;
			case 77:
				VaccineAgeRate[0] = line.toDouble();
				break;
			case 78:
				VaccineAgeRate[1] = line.toDouble();
				break;
			case 79:
				VaccineAgeRate[2] = line.toDouble();
				break;
			case 80:
				VaccineAgeRate[3] = line.toDouble();
				break;
			case 81:
				VaccineAgeRate[4] = line.toDouble();
				break;
			case 82:
				VaccineEffectAgeRate[0] = line.toDouble();
				break;
			case 83:
				VaccineEffectAgeRate[1] = line.toDouble();
				break;
			case 84:
				VaccineEffectAgeRate[2] = line.toDouble();
				break;
			case 85:
				VaccineEffectAgeRate[3] = line.toDouble();
				break;
			case 86:
				VaccineEffectAgeRate[4] = line.toDouble();
				break;
			case 87:
				AntibodyCreateRange = line.toDouble();
				break;
			case 88:
				VaccineStart = line.toDouble();
				break;
			case 90:
				MaskNeedNICU = line.toDouble();
				break;
			case 91:
				MaskNeedICU = line.toDouble();
				break;
			case 92:
				RespiratorNeedRate = line.toDouble();
				break;
			case 93:
				ReinspectionRate = line.toDouble();
				break;
			case 94:
				OutpatientSpecimenTesting = line.toDouble();
				break;

			}

			linecount++;

		}
		inputFile.close();

		MainWindow::setDefault();
	}
}

void MainWindow::on_actionSave_triggered()
{
	MainWindow::saveInput();

	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "output/%Y-%m-%d-%H%M%S.kcim", &tstruct);

	QString filter = "KISIM Files (*.kcim)";
	QString filename = QFileDialog::getSaveFileName(this, tr("save"), buf, filter, &filter);

	if (! filename.isNull()) {
		QFile f(toKor(filename.toLocal8Bit()));
		f.open(QIODevice::WriteOnly);
		// store data in f
		f.close();

		FILE* fp = fopen(toKor(filename.toLocal8Bit()).toStdString().c_str(), "w+");
		for (int i = 0; i < StageofAgeGroups; i++) {
			fprintf(fp, "%f \n", Population[i]);
		}

		for (int i = 0; i < StageofAgeGroups; i++) {
			for (int j = i; j < StageofAgeGroups; j++) {
				fprintf(fp, "%f \n", ContactMatrix[i][j]);
			}
		}

		for (int i = 0; i < ChildClass; i++) {
			fprintf(fp, "%f \n", SchoolContactRate[i]);
		}

		fprintf(fp, "%f \n", LatentPeriod);

		for (int i = 0; i < StageofSevere; i++) {
			for (int j = 0; j < StageofWorkAge; j++) {
				fprintf(fp, "%f \n", InfectiousDuration[i][j]);
			}
		}

		fprintf(fp, "%f \n", SevereRate);
		fprintf(fp, "%f \n", MildRate);

		fprintf(fp, "%f \n", ReturntoWorkPeriod);

		for (int i = 0; i < StageofWorkAge; i++) {
			fprintf(fp, "%f \n", HighRiskRate[i]);
		}
		for (int i = 0; i < StageofWorkAge; i++) {
			fprintf(fp, "%f \n", LowRiskHospitalRate[i]);
		}
		for (int i = 0; i < StageofWorkAge; i++) {
			fprintf(fp, "%f \n", HighRiskHospitalRate[i]);
		}
		for (int i = 0; i < StageofWorkAge; i++) {
			fprintf(fp, "%f \n", DeadRate[i]);
		}

		fprintf(fp, "%f \n", R0);

		fprintf(fp, "%f \n", HalfInfectiousRate);

		fprintf(fp, "%f \n", LastLatentPeriodCase);
		fprintf(fp, "%f \n", AsymptomaticCase);
		fprintf(fp, "%f \n", ModerateCase);

		fprintf(fp, "%f \n", ModerateCaseIsolation);
		fprintf(fp, "%f \n", SevereHomeCaseIsolation);
		fprintf(fp, "%f \n", SevereHospitalCaseIsolation);
		fprintf(fp, "%f \n", ModerateCaseIsolation);
		fprintf(fp, "%d \n", RangeofIsolationBegin);
		fprintf(fp, "%d \n", RangeofIsolationEnd);

		fprintf(fp, "%f \n", AntiviralsInjectionRate);

		fprintf(fp, "%f \n", MedicalHelp);
		fprintf(fp, "%f \n", AntiviralsHelp);

		fprintf(fp, "%f \n", VerySickTreatRate);
		fprintf(fp, "%d \n", VerySickTreatRangeBegin);
		fprintf(fp, "%d \n", VerySickTreatRangeEnd);

		fprintf(fp, "%f \n", ExtremelySickTreatRate);
		fprintf(fp, "%d \n", ExtremelySickTreatRangeBegin);
		fprintf(fp, "%d \n", ExtremelySickTreatRangeEnd);

		fprintf(fp, "%f \n", ContagiousnessReduction);
		fprintf(fp, "%f \n", DiseaseDurationReduction);
		fprintf(fp, "%f \n", HospitalizationReduction);

		fprintf(fp, "%f \n", ContactReductionRate);
		fprintf(fp, "%d \n", ContactReductionRangeBegin);
		fprintf(fp, "%d \n", ContactReductionRangeEnd);

		fprintf(fp, "%d \n", SchoolCloseRangeBegin);
		fprintf(fp, "%d \n", SchoolCloseRangeEnd);

		fprintf(fp, "%f \n", GatheringCancelReductionRate);
		fprintf(fp, "%d \n", GatheringCancleRangeBegin);
		fprintf(fp, "%d \n", GatheringCancleRangeEnd);

		fprintf(fp, "%f \n", HospitalizationNICU);
		fprintf(fp, "%f \n", HospitalizationICU);

		for (int i = 0; i < StageofAgeGroups; i++) {
			fprintf(fp, "%f \n", VaccineAgeRate[i]);
		}
		for (int i = 0; i < StageofAgeGroups; i++) {
			fprintf(fp, "%f \n", VaccineEffectAgeRate[i]);
		}

		fprintf(fp, "%f \n", AntibodyCreateRange);

		fprintf(fp, "%f \n", VaccineStart);

		fprintf(fp, "%f \n", MaskNeedNICU);
		fprintf(fp, "%f \n", MaskNeedICU);

		fprintf(fp, "%f \n", RespiratorNeedRate);

		fprintf(fp, "%f \n", ReinspectionRate);
		fprintf(fp, "%f \n", OutpatientSpecimenTesting);

		fclose(fp);
	}

}

void MainWindow::on_actionK_flu_triggered()
{

}


void MainWindow::on_actionExport_triggered()
{
}

void MainWindow::on_actionContact_triggered()
{

}

void MainWindow::on_actionJPG_triggered()
{
	if (outputFlag) {
		ui->jpgWidget->show();
		ui->jpgWidget->activateWindow();
		ui->jpgWidget->raise();
	}
	else {
		QMessageBox msgBox;
		msgBox.setText(toKor("결과 확인 후 변환 가능합니다."));
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
	}

}

void MainWindow::on_actionCSV_triggered()
{
	if (outputFlag) {
		ui->csvWidget->show();
		ui->csvWidget->activateWindow();
		ui->csvWidget->raise();
	}
	else {
		QMessageBox msgBox;
		msgBox.setText(toKor("결과 확인 후 변환 가능합니다."));
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
	}

}

void MainWindow::on_jpgSubmit_clicked()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "output/graph-%Y-%m-%d-%H%M%S.jpg", &tstruct);

	QString filename = QFileDialog::getSaveFileName(this, "Export to jpg", buf, ".jpg");

	if (!filename.isNull()) {

		QFile f(toKor(filename.toLocal8Bit()));

		f.open(QIODevice::WriteOnly);

		switch (jpgOutput)
		{
		case 1:
			ui->customPlot_infection->saveJpg(filename, 0, 0, 1.0, -1);
			break;
		case 2:
			ui->customPlot_daily->saveJpg(filename, 0, 0, 1.0, -1);
			break;
		case 3:
			ui->customPlot_resource->saveJpg(filename, 0, 0, 1.0, -1);
			break;
		case 4:
			ui->customPlot_specimen->saveJpg(filename, 0, 0, 1.0, -1);
			break;
		default:
			break;
		}

		f.close();
	}
    ui->jpgWidget->hide();
}

const char* ConvertDoubleToString(double value) {
	std::stringstream ss;
	ss << value;
	const char* str = ss.str().c_str();
	return str;
}

void MainWindow::on_csvSubmit_clicked()
{
	setlocale(LC_ALL, "korean");

	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "output/table-%Y-%m-%d-%H%M%S.csv", &tstruct);

	QString filename = QFileDialog::getSaveFileName(this, "Export to csv", buf, ".csv");

	if (!filename.isNull()) {
		QFile f(toKor(filename.toLocal8Bit()));

		f.open(QIODevice::WriteOnly);
		// store data in f


		//FILE* fp = fopen(toKor(filename.toLocal8Bit()).toStdString().c_str(), "w+");

		switch (GraphAge)
		{
		case 0:
			f.write("Age group 0~6,\n");
			break;
		case 1:
			f.write("Age group 7~12,\n");
			break;
		case 2:
			f.write("Age group 13~18,\n");
			break;
		case 3:
			f.write("Age group 19~64,\n");
			break;
		case 4:
			f.write("Age group 65 ~,\n");
			break;
		case 5:
			f.write("All ages,\n");
			break;
		default:
			break;
		}

		switch (csvOutput)
		{
		case 1:
			f.write("Susceptible,exposed,Asymptomatic,Moderate,Severe,dead,convalescent,Immune,total,\n");
			for (int i = 0; i < 500; i++) {
				double population_total = SusceptibleArray[GraphAge][i] + ExposedArray[GraphAge][i] + AsymptomaticArray[GraphAge][i] + ModerateArray[GraphAge][i] + SevereArray[GraphAge][i] + DeadArray[GraphAge][i] + RArray[GraphAge][i] + ImmuneArray[GraphAge][i] ;
				QString _str = QString("%1, %2, %3, %4, %5, %6, %7, %8, %9, \n").arg(SusceptibleArray[GraphAge][i]).arg(ExposedArray[GraphAge][i]).arg(AsymptomaticArray[GraphAge][i]).arg(ModerateArray[GraphAge][i]).arg(SevereArray[GraphAge][i]).arg(DeadArray[GraphAge][i]).arg(RArray[GraphAge][i]).arg(ImmuneArray[GraphAge][i]).arg(population_total);
				QByteArray str;
				str.append(_str);
				f.write(str);
			}
			break;
		case 2:
			f.write("outpatient(daily),NICU(daily),ICU(daily),\n");
			for (int i = 0; i < 500; i++) {
				QString _str = QString("%1,%2,%3,\n").arg(DailyOutpatientArray[GraphAge][i]).arg(DailyNICUArray[GraphAge][i]).arg(DailyICUArray[GraphAge][i]);
				QByteArray str;
				str.append(_str);
				f.write(str);
			}
			break;
		case 3:
			f.write("N-95 Mask, Respirator, Antivirals,\n");
			for (int i = 0; i < 500; i++) {
				QString _str = QString("%1,%2,%3,\n").arg(MaskArray[GraphAge][i]).arg(RespArray[GraphAge][i]).arg(AntiviralsArray[GraphAge][i]);
				QByteArray str;
				str.append(_str);
				f.write(str);
			}
			break;
		case 4:
			f.write("Specimen,\n");
			for (int i = 0; i < 500; i++) {
				QString _str = QString("%1,\n").arg(SpecimenArray[GraphAge][i]);
				QByteArray str;
				str.append(_str);
				f.write(str);
			}
			break;
		default:
			break;
		}

		f.close();
	}
    ui->csvWidget->hide();
}

void MainWindow::on_saveBtn_clicked()
{
	ui->closeWidget->hide();
	MainWindow::on_actionSave_triggered();
	this->close();
}
void MainWindow::on_closeBtn_clicked()
{
	ui->closeWidget->hide();
	this->close();
}

void MainWindow::on_csvoutput_1_clicked()
{
	csvOutput = 1;
}

void MainWindow::on_csvoutput_2_clicked()
{
	csvOutput = 2;
}

void MainWindow::on_csvoutput_3_clicked()
{
	csvOutput = 3;
}

void MainWindow::on_csvoutput_4_clicked()
{
	csvOutput = 4;
}
void MainWindow::on_jpgoutput_1_clicked()
{
	jpgOutput = 1;
}

void MainWindow::on_jpgoutput_2_clicked()
{
	jpgOutput = 2;
}

void MainWindow::on_jpgoutput_3_clicked()
{
	jpgOutput = 3;
}

void MainWindow::on_jpgoutput_4_clicked()
{
	jpgOutput = 4;
}

void MainWindow::on_areaButton_1_clicked()
{
	Population[0] = 384230;
	Population[1] = 769242;
	Population[2] = 543083;
	Population[3] = 6667747;
	Population[4] = 1202894;

	ContactMatrix[0][0] = 181;
	ContactMatrix[0][1] = 94.4;
	ContactMatrix[0][2] = 21.4;
	ContactMatrix[0][3] = 98.3;
	ContactMatrix[0][4] = 49.2;

	ContactMatrix[1][1] = 320.8;
	ContactMatrix[1][2] = 57.4;
	ContactMatrix[1][3] = 66.1;
	ContactMatrix[1][4] = 50.2;

	ContactMatrix[2][2] = 312.3;
	ContactMatrix[2][3] = 128.4;
	ContactMatrix[2][4] = 43.2;

	ContactMatrix[3][3] = 360.6;
	ContactMatrix[3][4] = 56;

	ContactMatrix[4][4] = 83.5;
}

void MainWindow::on_areaButton_2_clicked()
{
	Population[0] = 8469;
	Population[1] = 18084;
	Population[2] = 10762;
	Population[3] = 97835;
	Population[4] = 11956;

	ContactMatrix[0][0] = 179;
	ContactMatrix[0][1] = 87.4;
	ContactMatrix[0][2] = 15.8;
	ContactMatrix[0][3] = 84.3;
	ContactMatrix[0][4] = 19.8;

	ContactMatrix[1][1] = 340.4;
	ContactMatrix[1][2] = 67.2;
	ContactMatrix[1][3] = 68.8;
	ContactMatrix[1][4] = 28.2;

	ContactMatrix[2][2] = 347.3;
	ContactMatrix[2][3] = 134;
	ContactMatrix[2][4] = 19;

	ContactMatrix[3][3] = 362.4;
	ContactMatrix[3][4] = 41.3;

	ContactMatrix[4][4] = 79.9;

}

void MainWindow::on_areaButton_3_clicked()
{
	Population[0] = 7711;
	Population[1] = 18373;
	Population[2] = 14227;
	Population[3] = 132496;
	Population[4] = 33383;

	ContactMatrix[0][0] = 169.1;
	ContactMatrix[0][1] = 34;
	ContactMatrix[0][2] = 8.4;
	ContactMatrix[0][3] = 57.2;
	ContactMatrix[0][4] = 22.4;

	ContactMatrix[1][1] = 264.9;
	ContactMatrix[1][2] = 50.7;
	ContactMatrix[1][3] = 55.7;
	ContactMatrix[1][4] = 21;

	ContactMatrix[2][2] = 299.5;
	ContactMatrix[2][3] = 107.7;
	ContactMatrix[2][4] = 40.6;

	ContactMatrix[3][3] = 274.1;
	ContactMatrix[3][4] = 49.8;

	ContactMatrix[4][4] = 50.9;
}

void MainWindow::on_actionExit_triggered()
{
	ui->closeWidget->show();
	ui->closeWidget->activateWindow();
	ui->closeWidget->raise();
}
