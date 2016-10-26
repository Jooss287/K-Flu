#include "mainwindow.h"
#include <stdio.h>
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <define.h>
#include <algorithm>  

#include <sstream>

#include <qstring.h>

using namespace std;
#define toKor(str) QString::fromLocal8Bit(str)


/*input 관련 변수들*/
int PopulationTotal =Population[Age0to6]+Population[Age7to12]+Population[Age13to18]+Population[Age19to64]+Population[Age65toEnd];

int contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
int contactTotal7to12 =  ContactMatrix[Age7to12][Age7to12]+ ContactMatrix[Age7to12][Age13to18]+ ContactMatrix[Age7to12][Age19to64]+ ContactMatrix[Age7to12][Age65toEnd];
int contactTotal13to18 =  ContactMatrix[Age13to18][Age13to18]+ ContactMatrix[Age13to18][Age19to64]+ ContactMatrix[Age13to18][Age65toEnd];
int contactTotal19to64 =  ContactMatrix[Age19to64][Age19to64]+ ContactMatrix[Age19to64][Age65toEnd];
int contactTotal65toEnd = ContactMatrix[Age65toEnd][Age65toEnd];

int contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;

/*output 관련 변수들*/
int goal=200;
double day = 0;
int steps=0;
int evals = 0;
/**
* The current x value.
*/

double y[OutputArray] = {};
double h = 1;
double maxError = 0.02;
double minError = maxError / 4;

double yInVector[OutputArray] = {};
double k1[OutputArray] = {};
double k2[OutputArray] = {};
double k3[OutputArray] = {};
double k4[OutputArray] = {};

int GraphAge = Age0to6; //default
bool AgeAll = true;


QVector<double> SusceptibleArray(NumberofArray);
QVector<double> ExposedArray(NumberofArray);
QVector<double> AsymptomaticArray(NumberofArray);
QVector<double> ModerateArray(NumberofArray);
QVector<double> SevereArray(NumberofArray);
QVector<double> DeadArray(NumberofArray);
QVector<double> ImmuneArray(NumberofArray);

QVector<double> MaskArray(NumberofArray);
QVector<double> RespArray(NumberofArray);
QVector<double> AntiviralsArray(NumberofArray);

QVector<double> SpecimenArray(NumberofArray);

QVector<double> DailyOutpatientArray(NumberofArray);
QVector<double> DailyICUArray(NumberofArray);
QVector<double> DailyNICUArray(NumberofArray);

QVector<double> CumulOutpatientArray(NumberofArray);
QVector<double> CumulICUArray(NumberofArray);
QVector<double> CumulNICUArray(NumberofArray);


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
void MainWindow::run(double input) {


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
	for (int i = 0; i < OutputArray; i++) {
		yInVector[i] = 0;
		k1[i] = 0;
		k2[i] = 0;
		k3[i] = 0;
		k4[i] = 0;
	}
	for (int i = 0; i < OutputArray; i++) yInVector[i] = InitY[i];


	qDebug(" %f", yInVector[A(2, IstageLast)]);


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
	
	SusceptibleArray[day] = 0;
	ExposedArray[day] = 0;
	AsymptomaticArray[day] = 0;
	ModerateArray[day] = 0;
	SevereArray[day]=0;
	DeadArray[day] = 0;
	ImmuneArray[day] = 0;

	if (AgeAll) {

		for (int age = 0; age < StageofAgeGroups; age++) {
			SusceptibleArray[day] += total*(InitY[S(age, LowRisk)] + InitY[S(age, HighRisk)]);
			if (day >= 20 && age == 2) {
				//qDebug("day:%f, susceptible, age:%d, low: %f, high: %f", day, age, total*(InitY[S(age, LowRisk)]), total*InitY[S(age, HighRisk)]);
			}

			for (int k = 0; k < EstageGroups; k++) {
				ExposedArray[day] += total*(InitY[E(age, LowRisk, k)] + InitY[E(age, HighRisk, k)]);
				if (day >= 20 && age==2) {
					//qDebug("day:%f, exposed, age:%d, estage:%d, low: %f, high: %f", day, age, k, total*(InitY[E(age, LowRisk, k)]), total*(InitY[E(age, HighRisk, k)]));
				}
			}

			for (int k = 0; k < IstageGroups; k++) {
				AsymptomaticArray[day] += total*(InitY[A(age, k)]);

				ModerateArray[day] += total*(InitY[M(age, k)]);
				if (day >= 20 && age == 2) {
					//qDebug("day:%f, untreatd asmyptomatic gamma, age:%d, istage:%d, %f", day, age, k, gamma[age][MedNO][ItypeA]);
					//qDebug("day:%f, Asymptomatic, age:%d, istage:%d, %f", day, age, k, total*(InitY[A(age, k)]));
					//qDebug("day:%f, untreatd moderate gamma, age:%d, istage:%d, %f", day, age, k, gamma[age][MedNO][ItypeM]);
					//qDebug("day:%f, Moderate, age:%d, istage:%d, %f", day, age, k, total*(InitY[M(age, k)]));

				}

				SevereArray[day] += total*(InitY[V(age, k)] + InitY[X(age, k)]);
				if (day >= 20 && age == 2) {

					//qDebug("day:%f, Severe V, age:%d, istage:%d, %f", day, age, k, total*(InitY[V(age, k)]));
					//qDebug("day:%f, Severe X, age:%d, istage:%d, %f", day, age, k, total*(InitY[X(age, k)]));
				}


				for (int m = 0; m < MedGroups; m++) {
					SevereArray[day] += total*(InitY[W(age, k, m)]);

					SevereArray[day] += total*(InitY[H(age, k, m)]);				
						if (day >= 20 && age == 2) {

						//qDebug("day:%f, Severe W, age:%d, istage:%d, med:%d, %f", day, age, k, m, total*(InitY[W(age, k, m)]));
						//qDebug("day:%f, Severe H, age:%d, istage:%d, med:%d, %f", day, age, k, m, total*(InitY[H(age, k, m)]));
						}
				}
			}

			DeadArray[day] += total*(InitY[D(age)]);
			ImmuneArray[day] += total*(InitY[I(age)]);

			if (day >= 20 && age == 2) {
				//qDebug("day:%f, dead, age:%d, %f ", day, age, total*(k4[D(age)]));
				//qDebug("day:%f, immune, age:%d, %f ", day, age, total*(k4[I(age)]));
			}


		}

	}
	else {
		SusceptibleArray[day] += total*(InitY[S(GraphAge, LowRisk)] + InitY[S(GraphAge, HighRisk)]);
		for (int k = 0; k < EstageGroups; k++)
			ExposedArray[day] += total*(InitY[E(GraphAge, LowRisk, k)] + InitY[E(GraphAge, HighRisk, k)]);

		for (int k = 0; k < IstageGroups; k++) {
			AsymptomaticArray[day] += total*(InitY[A(GraphAge, k)]);
			ModerateArray[day] += total*(InitY[M(GraphAge, k)]);
			SevereArray[day] += total*(InitY[V(GraphAge, k)] + InitY[X(GraphAge, k)]);

			for (int m = 0; m < MedGroups; m++) {
				SevereArray[day] += total*(InitY[W(GraphAge, k, m)]);

					SevereArray[day] += total*(InitY[H(GraphAge, k, m)]);
				
			}
		}
		DeadArray[day] += InitY[D(GraphAge)];
		ImmuneArray[day] += InitY[I(GraphAge)];
	}

}



/*tab별 그래프 그리는 함수들*/
void MainWindow::makeInfectionPlot(){

	ui->customPlot_infection->removeGraph(0);
	ui->customPlot_infection->removeGraph(1);
	ui->customPlot_infection->removeGraph(2);
	ui->customPlot_infection->removeGraph(3);
	ui->customPlot_infection->removeGraph(4);
	ui->customPlot_infection->removeGraph(5);
	ui->customPlot_infection->removeGraph(6);

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
	ui->customPlot_infection->xAxis->setRange(0, 210);
	ui->customPlot_infection->yAxis->setRange(0, total);

	QVector<double> x(goal);

	for (int i = 0; i<goal; i++) {

		x[i] = i;
	}

	//감수성기 그래프
	ui->customPlot_infection->addGraph();
    ui->customPlot_infection->graph(0)->setData(x, SusceptibleArray);
	ui->customPlot_infection->graph(0)->setName(toKor("감수성기에 있는 사람"));
	ui->customPlot_infection->graph(0)->setPen(QColor(255, 0, 0, 255));
    ui->customPlot_infection->replot();

	//잠복기 그래프
	ui->customPlot_infection->addGraph();
	ui->customPlot_infection->graph(1)->setData(x, ExposedArray);
	ui->customPlot_infection->graph(1)->setName(toKor("잠복기에 있는 사람"));
	ui->customPlot_infection->graph(1)->setPen(QColor(0, 0, 255, 255));
	ui->customPlot_infection->replot();

	//무증상자 그래프
	ui->customPlot_infection->addGraph();
	ui->customPlot_infection->graph(2)->setData(x, AsymptomaticArray);
	ui->customPlot_infection->graph(2)->setName(toKor("무증상자"));
	ui->customPlot_infection->graph(2)->setPen(QColor(0, 255, 0, 255));
	ui->customPlot_infection->replot();

	//중증도 중간 그래프
	ui->customPlot_infection->addGraph();
	ui->customPlot_infection->graph(3)->setData(x, ModerateArray);
	ui->customPlot_infection->graph(3)->setName(toKor("중증도가 중간인 사람"));
	ui->customPlot_infection->graph(3)->setPen(QColor(255, 228, 0, 255));
	ui->customPlot_infection->replot();

	//중증도 높음 그래프
	ui->customPlot_infection->addGraph();
	ui->customPlot_infection->graph(4)->setData(x, SevereArray);
	ui->customPlot_infection->graph(4)->setName(toKor("중증도가 높은 사람"));
	ui->customPlot_infection->graph(4)->setPen(QColor(255, 0, 221, 255));
	ui->customPlot_infection->replot();

	//사망자 그래프
	ui->customPlot_infection->addGraph();
	ui->customPlot_infection->graph(5)->setData(x, DeadArray);
	ui->customPlot_infection->graph(5)->setName(toKor("사망자"));
	ui->customPlot_infection->graph(5)->setPen(QColor(0, 216, 255, 255));
	ui->customPlot_infection->replot();

	//회복 그래프
	ui->customPlot_infection->addGraph();
	ui->customPlot_infection->graph(6)->setData(x, ImmuneArray);
	ui->customPlot_infection->graph(6)->setName(toKor("회복한 사람"));
	ui->customPlot_infection->graph(6)->setPen(QColor(255, 94, 0, 255));
	ui->customPlot_infection->replot();

	//테이블 크기 조절
    ui->infectionTable->setColumnWidth(0,130);
    ui->infectionTable->setColumnWidth(1,120);
    ui->infectionTable->setColumnWidth(2,90);
    ui->infectionTable->setColumnWidth(3,130);
	ui->infectionTable->setColumnWidth(4,130);
	ui->infectionTable->setColumnWidth(5,90);
	ui->infectionTable->setColumnWidth(6,90);

	//테이블 인풋 
	ui->infectionTable->setRowCount(goal);
	for (int i = 0; i < goal; i++) {
		ui->infectionTable->setItem(i, 0, new QTableWidgetItem(QString::number((double)SusceptibleArray[i], 'f')));
	}

	for (int i = 0; i < goal; i++) {
		ui->infectionTable->setItem(i, 1, new QTableWidgetItem(QString::number((double)ExposedArray[i], 'f')));
	}

	for (int i = 0; i < goal; i++) {
		ui->infectionTable->setItem(i, 2, new QTableWidgetItem(QString::number((double)AsymptomaticArray[i], 'f')));
	}

	for (int i = 0; i <goal; i++) {
		ui->infectionTable->setItem(i, 3, new QTableWidgetItem(QString::number((double)ModerateArray[i], 'f')));
	}

	for (int i = 0; i <goal; i++) {
		ui->infectionTable->setItem(i, 4, new QTableWidgetItem(QString::number((double)SevereArray[i], 'f')));
	}

	for (int i = 0; i < goal; i++) {
		ui->infectionTable->setItem(i, 5, new QTableWidgetItem(QString::number((double)DeadArray[i], 'f')));
	}

	for (int i = 0; i < 200; i++) {
		ui->infectionTable->setItem(i, 6, new QTableWidgetItem(QString::number((double)ImmuneArray[i], 'f')));
	}
}


void MainWindow::makeResourcePlot(){

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
	ui->customPlot_resource->xAxis->setRange(0, 210);
	ui->customPlot_resource->yAxis->setRange(0, 500000);

	QVector<double> x(NumberofArray);

	for (int i = 0; i<NumberofArray; i++) {
		x[i] = i;
	}

	//마스크 그래프
	ui->customPlot_resource->addGraph();
	ui->customPlot_resource->graph(0)->setData(x, MaskArray);
	ui->customPlot_resource->graph(0)->setName(toKor("외래 환자"));
	ui->customPlot_resource->graph(0)->setPen(QColor(255, 0, 0, 255));
	ui->customPlot_resource->replot();

	//인공호흡기 그래프
	ui->customPlot_resource->addGraph();
	ui->customPlot_resource->graph(1)->setData(x, RespArray);
	ui->customPlot_resource->graph(1)->setName(toKor("입원 환자"));
	ui->customPlot_resource->graph(1)->setPen(QColor(0, 0, 255, 255));
	ui->customPlot_resource->replot();

	//항바이러스제 그래프
	ui->customPlot_resource->addGraph();
	ui->customPlot_resource->graph(2)->setData(x, AntiviralsArray);
	ui->customPlot_resource->graph(2)->setName(toKor("항바이러스제"));
	ui->customPlot_resource->graph(2)->setPen(QColor(0, 255, 0, 255));
	ui->customPlot_resource->replot();


	//테이블 크기 조절
	ui->resourceTable->setColumnWidth(0, 150);
	ui->resourceTable->setColumnWidth(1, 150);
	ui->resourceTable->setColumnWidth(2, 150);


	//테이블 인풋 
	ui->resourceTable->setRowCount(NumberofArray);
	for (int i = 0; i < NumberofArray; i++) {
		ui->resourceTable->setItem(i, 0, new QTableWidgetItem(QString::number((double)MaskArray[i], 'f')));
	}

	for (int i = 0; i < NumberofArray; i++) {
		ui->resourceTable->setItem(i, 1, new QTableWidgetItem(QString::number(RespArray[i])));
	}

	for (int i = 0; i < NumberofArray; i++) {
		ui->resourceTable->setItem(i, 2, new QTableWidgetItem(QString::number(AntiviralsArray[i])));
	}
}

void MainWindow::makeSpecimenPlot(){
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
	ui->customPlot_specimen->xAxis->setRange(0, 210);
	ui->customPlot_specimen->yAxis->setRange(0, 500000);

	QVector<double> x(NumberofArray);

	for (int i = 0; i<200; i++) {
		x[i] = i;
	}

	//검체 수 그래프
	ui->customPlot_specimen->addGraph();
	ui->customPlot_specimen->graph(0)->setData(x, SpecimenArray);
	ui->customPlot_specimen->graph(0)->setName(toKor("검체 수"));
	ui->customPlot_specimen->graph(0)->setPen(QColor(255, 0, 0, 255));
	ui->customPlot_specimen->replot();


	//테이블 크기 조절
	ui->resourceTable->setColumnWidth(0, 150);


	//테이블 인풋 
	ui->specimenTable->setRowCount(200);
	for (int i = 0; i < 200; i++) {
		ui->specimenTable->setItem(i, 0, new QTableWidgetItem(QString::number((double)SpecimenArray[i], 'f')));
	}
}


void MainWindow::makeDailyPlot(){
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
	ui->customPlot_daily->xAxis->setRange(0, 210);
	ui->customPlot_daily->yAxis->setRange(0, 500000);

	QVector<double> x(NumberofArray);

	for (int i = 0; i<NumberofArray; i++) {
		x[i] = i;
	}

	//외래환자 그래프
	ui->customPlot_daily->addGraph();
	ui->customPlot_daily->graph(0)->setData(x, DailyOutpatientArray);
	ui->customPlot_daily->graph(0)->setName(toKor("외래환자 수"));
	ui->customPlot_daily->graph(0)->setPen(QColor(255, 0, 0, 255));
	ui->customPlot_daily->replot();

	//중환자실 병상 그래프
	ui->customPlot_daily->addGraph();
	ui->customPlot_daily->graph(1)->setData(x, DailyICUArray);
	ui->customPlot_daily->graph(1)->setName(toKor("중환자실 병상 수"));
	ui->customPlot_daily->graph(1)->setPen(QColor(0, 0, 255, 255));
	ui->customPlot_daily->replot();

	//일반 병상 그래프
	ui->customPlot_daily->addGraph();
	ui->customPlot_daily->graph(2)->setData(x, DailyNICUArray);
	ui->customPlot_daily->graph(2)->setName(toKor("일반 병상 수"));
	ui->customPlot_daily->graph(2)->setPen(QColor(0, 255, 0, 255));
	ui->customPlot_daily->replot();


	//테이블 크기 조절
	ui->dailyTable->setColumnWidth(0, 150);
	ui->dailyTable->setColumnWidth(1, 150);
	ui->dailyTable->setColumnWidth(2, 150);


	//테이블 인풋 
	ui->dailyTable->setRowCount(200);
	for (int i = 0; i < 200; i++) {
		ui->dailyTable->setItem(i, 0, new QTableWidgetItem(QString::number((double) DailyOutpatientArray[i], 'f')));
	}

	for (int i = 0; i < 200; i++) {
		ui->dailyTable->setItem(i, 1, new QTableWidgetItem(QString::number(DailyICUArray[i])));
	}

	for (int i = 0; i < 200; i++) {
		ui->dailyTable->setItem(i, 2, new QTableWidgetItem(QString::number(DailyNICUArray[i])));
	}
}


void MainWindow::makeCumulativePlot(){
	ui->customPlot_cumulative->setLocale(QLocale(QLocale::Korean));

	ui->customPlot_cumulative->legend->setVisible(true);
	ui->customPlot_cumulative->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));

	ui->customPlot_cumulative->axisRect()->setAutoMargins(QCP::msLeft | QCP::msTop | QCP::msBottom);
	ui->customPlot_cumulative->axisRect()->setMargins(QMargins(20, 0, 140, 0));
	ui->customPlot_cumulative->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipFree);
	ui->customPlot_cumulative->axisRect()->insetLayout()->setInsetRect(0, QRectF(1.0, 0, 0.2, 0.2));
	ui->customPlot_cumulative->xAxis->setLabel(toKor("일"));
	ui->customPlot_cumulative->yAxis->setLabel(toKor("인구"));


	// set axes ranges, so we see all data:
	ui->customPlot_cumulative->xAxis->setRange(0, 210);
	ui->customPlot_cumulative->yAxis->setRange(0, 500000);

	QVector<double> x(NumberofArray);

	for (int i = 0; i<NumberofArray; i++) {
		x[i] = i;
	}

	//외래환자 그래프
	ui->customPlot_cumulative->addGraph();
	ui->customPlot_cumulative->graph(0)->setData(x, CumulOutpatientArray);
	ui->customPlot_cumulative->graph(0)->setName(toKor("외래환자 수(누적)"));
	ui->customPlot_cumulative->graph(0)->setPen(QColor(255, 0, 0, 255));
	ui->customPlot_cumulative->replot();

	//중환자실 환자 그래프
	ui->customPlot_cumulative->addGraph();
	ui->customPlot_cumulative->graph(1)->setData(x, CumulICUArray);
	ui->customPlot_cumulative->graph(1)->setName(toKor("중환자실 환자 수(누적)"));
	ui->customPlot_cumulative->graph(1)->setPen(QColor(0, 0, 255, 255));
	ui->customPlot_cumulative->replot();

	//일반환자 그래프
	ui->customPlot_cumulative->addGraph();
	ui->customPlot_cumulative->graph(2)->setData(x, CumulNICUArray);
	ui->customPlot_cumulative->graph(2)->setName(toKor("일반 환자 수(누적)"));
	ui->customPlot_cumulative->graph(2)->setPen(QColor(0, 255, 0, 255));
	ui->customPlot_cumulative->replot();


	//테이블 크기 조절
	ui->cumulativeTable->setColumnWidth(0, 150);
	ui->cumulativeTable->setColumnWidth(1, 150);
	ui->cumulativeTable->setColumnWidth(2, 150);


	//테이블 인풋 
	ui->cumulativeTable->setRowCount(200);
	for (int i = 0; i < 200; i++) {
		ui->cumulativeTable->setItem(i, 0, new QTableWidgetItem(QString::number((double)CumulOutpatientArray[i], 'f')));
	}

	for (int i = 0; i < 200; i++) {
		ui->cumulativeTable->setItem(i, 1, new QTableWidgetItem(QString::number(CumulICUArray[i])));
	}

	for (int i = 0; i < 200; i++) {
		ui->cumulativeTable->setItem(i, 2, new QTableWidgetItem(QString::number(CumulNICUArray[i])));
	}
}


void MainWindow::setDefault()
{
    /*인구 tab 기본값 세팅*/

    ui->input_SchoolRatio0to6->setText(QString::number(SchoolContactRate[0]));
    ui->input_SchoolRatio7to12->setText(QString::number(SchoolContactRate[1])); 
    ui->input_SchoolRatio13to18->setText(QString::number(SchoolContactRate[2]));

    ui->input_AbsentRatio0to6->setText(QString::number(AbsenceContactRatio[0]));
	ui->input_AbsentRatio7to12->setText(QString::number(AbsenceContactRatio[1]));
	ui->input_AbsentRatio13to18->setText(QString::number(AbsenceContactRatio[2]));

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
    ui->input_SchoolCloseContact0to6->setText(QString::number(SchoolCloseContactRatio[0]));
	ui->input_SchoolCloseContact7to12->setText(QString::number(SchoolCloseContactRatio[1]));
	ui->input_SchoolCloseContact13to18->setText(QString::number(SchoolCloseContactRatio[2]));

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
	MainWindow::run(goal);
    ui->outputWidget->show();
    ui->outputWidget->activateWindow();
    ui->outputWidget->raise();

	MainWindow::makeInfectionPlot();
	//MainWindow::makeResourcePlot();
	//MainWindow::makeSpecimenPlot();
	//MainWindow::makeDailyPlot();
	//MainWindow::makeCumulativePlot();
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
    ui->input_contact_total0to6->setText(QString::number(contactTotal0to6));
    ui->input_contact_totalAll->setText(QString::number(contactTotalAll));
}

void MainWindow::on_input_contact_1_2_textEdited(const QString &arg1)
{
    ContactMatrix[Age0to6][Age7to12] = arg1.toInt();
    contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
    ui->input_contact_total0to6->setText(QString::number(contactTotal0to6));
    ui->input_contact_totalAll->setText(QString::number(contactTotalAll));
}

void MainWindow::on_input_contact_1_3_textEdited(const QString &arg1)
{
    ContactMatrix[Age0to6][Age13to18] = arg1.toInt();
    contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
    ui->input_contact_total0to6->setText(QString::number(contactTotal0to6));
    ui->input_contact_totalAll->setText(QString::number(contactTotalAll));
}

void MainWindow::on_input_contact_1_4_textEdited(const QString &arg1)
{
    ContactMatrix[Age0to6][Age19to64] = arg1.toInt();
    contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
    ui->input_contact_total0to6->setText(QString::number(contactTotal0to6));
    ui->input_contact_totalAll->setText(QString::number(contactTotalAll));
}

void MainWindow::on_input_contact_1_5_textEdited(const QString &arg1)
{
    ContactMatrix[Age0to6][Age65toEnd] = arg1.toInt();
    contactTotal0to6 =  ContactMatrix[Age0to6][Age0to6]+ ContactMatrix[Age0to6][Age7to12]+ ContactMatrix[Age0to6][Age13to18]+ ContactMatrix[Age0to6][Age19to64]+ ContactMatrix[Age0to6][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
    ui->input_contact_total0to6->setText(QString::number(contactTotal0to6));
    ui->input_contact_totalAll->setText(QString::number(contactTotalAll));
}


void MainWindow::on_input_contact_2_2_textEdited(const QString &arg1)
{
    ContactMatrix[Age7to12][Age7to12] = arg1.toInt();
    contactTotal7to12 =  ContactMatrix[Age7to12][Age7to12]+ ContactMatrix[Age7to12][Age13to18]+ ContactMatrix[Age7to12][Age19to64]+ ContactMatrix[Age7to12][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
    ui->input_contact_total7to12->setText(QString::number(contactTotal7to12));
    ui->input_contact_totalAll->setText(QString::number(contactTotalAll));
}

void MainWindow::on_input_contact_2_3_textEdited(const QString &arg1)
{
    ContactMatrix[Age7to12][Age13to18] = arg1.toInt();
    contactTotal7to12 =  ContactMatrix[Age7to12][Age7to12]+ ContactMatrix[Age7to12][Age13to18]+ ContactMatrix[Age7to12][Age19to64]+ ContactMatrix[Age7to12][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
    ui->input_contact_total7to12->setText(QString::number(contactTotal7to12));
    ui->input_contact_totalAll->setText(QString::number(contactTotalAll));
}

void MainWindow::on_input_contact_2_4_textEdited(const QString &arg1)
{
    ContactMatrix[Age7to12][Age19to64] = arg1.toInt();
    contactTotal7to12 =  ContactMatrix[Age7to12][Age7to12]+ ContactMatrix[Age7to12][Age13to18]+ ContactMatrix[Age7to12][Age19to64]+ ContactMatrix[Age7to12][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
    ui->input_contact_total7to12->setText(QString::number(contactTotal7to12));
    ui->input_contact_totalAll->setText(QString::number(contactTotalAll));
}

void MainWindow::on_input_contact_2_5_textEdited(const QString &arg1)
{
    ContactMatrix[Age7to12][Age65toEnd] = arg1.toInt();
    contactTotal7to12 =  ContactMatrix[Age7to12][Age7to12]+ ContactMatrix[Age7to12][Age13to18]+ ContactMatrix[Age7to12][Age19to64]+ ContactMatrix[Age7to12][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
    ui->input_contact_total7to12->setText(QString::number(contactTotal7to12));
    ui->input_contact_totalAll->setText(QString::number(contactTotalAll));
}

void MainWindow::on_input_contact_3_3_textEdited(const QString &arg1)
{
    ContactMatrix[Age13to18][Age13to18] = arg1.toInt();
    contactTotal13to18 =  ContactMatrix[Age13to18][Age13to18]+ ContactMatrix[Age13to18][Age19to64]+ ContactMatrix[Age13to18][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
    ui->input_contact_total13to18->setText(QString::number(contactTotal13to18));
    ui->input_contact_totalAll->setText(QString::number(contactTotalAll));
}

void MainWindow::on_input_contact_3_4_textEdited(const QString &arg1)
{
    ContactMatrix[Age13to18][Age19to64] = arg1.toInt();
    contactTotal13to18 =  ContactMatrix[Age13to18][Age13to18]+ ContactMatrix[Age13to18][Age19to64]+ ContactMatrix[Age13to18][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
    ui->input_contact_total13to18->setText(QString::number(contactTotal13to18));
    ui->input_contact_totalAll->setText(QString::number(contactTotalAll));
}

void MainWindow::on_input_contact_3_5_textEdited(const QString &arg1)
{
    ContactMatrix[Age13to18][Age65toEnd] = arg1.toInt();
    contactTotal13to18 =  ContactMatrix[Age13to18][Age13to18]+ ContactMatrix[Age13to18][Age19to64]+ ContactMatrix[Age13to18][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
    ui->input_contact_total13to18->setText(QString::number(contactTotal13to18));
    ui->input_contact_totalAll->setText(QString::number(contactTotalAll));
}

void MainWindow::on_input_contact_4_4_textEdited(const QString &arg1)
{
    ContactMatrix[Age19to64][Age19to64] = arg1.toInt();
    contactTotal19to64 =  ContactMatrix[Age19to64][Age19to64]+ ContactMatrix[Age19to64][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
    ui->input_contact_total19to64->setText(QString::number(contactTotal19to64));
    ui->input_contact_totalAll->setText(QString::number(contactTotalAll));
}

void MainWindow::on_input_contact_4_5_textEdited(const QString &arg1)
{
    ContactMatrix[Age19to64][Age65toEnd] = arg1.toInt();
    contactTotal19to64 =  ContactMatrix[Age19to64][Age19to64]+ ContactMatrix[Age19to64][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
    ui->input_contact_total19to64->setText(QString::number(contactTotal19to64));
    ui->input_contact_totalAll->setText(QString::number(contactTotalAll));
}

void MainWindow::on_input_contact_5_5_textEdited(const QString &arg1)
{
    ContactMatrix[Age65toEnd][Age65toEnd] = arg1.toInt();
    contactTotal65toEnd = ContactMatrix[Age65toEnd][Age65toEnd];
    contactTotalAll = contactTotal0to6 + contactTotal7to12 + contactTotal13to18 + contactTotal19to64 + contactTotal65toEnd;
    ui->input_contact_total65toEnd->setText(QString::number(contactTotal65toEnd));
    ui->input_contact_totalAll->setText(QString::number(contactTotalAll));
}


//인풋 변수 수정 필요
void MainWindow::on_input_SchoolRatio0to6_textEdited(const QString &arg1)
{
    SchoolContactRate[0] = arg1.toDouble();
}
//인풋 변수 수정 필요
void MainWindow::on_input_SchoolRatio7to12_textEdited(const QString &arg1)
{
    SchoolContactRate[1] = arg1.toDouble();
}
//인풋 변수 수정 필요
void MainWindow::on_input_SchoolRatio13to18_textEdited(const QString &arg1)
{
    SchoolContactRate[2] = arg1.toDouble();
}

void MainWindow::on_input_AbsentRatio0to6_textEdited(const QString &arg1)
{

}

void MainWindow::on_input_AbsentRatio7to12_textEdited(const QString &arg1)
{

}

void MainWindow::on_input_AbsentRatio13to18_textEdited(const QString &arg1)
{

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

void MainWindow::on_input_schoolCloseContact0to6_textEdited(const QString &arg1)
{
    SchoolCloseContactRatio[0] = arg1.toDouble();
}

void MainWindow::on_input_schoolCloseContact7to12_textEdited(const QString &arg1)
{
	SchoolCloseContactRatio[1] = arg1.toDouble();
}

void MainWindow::on_input_schoolCloseContact13to18_textEdited(const QString &arg1)
{
	SchoolCloseContactRatio[2] = arg1.toDouble();
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

void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{

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
    ui->jpgWidget->show();
    ui->jpgWidget->activateWindow();
    ui->jpgWidget->raise();
}

void MainWindow::on_actionCSV_triggered()
{
    ui->csvWidget->show();
    ui->csvWidget->activateWindow();
    ui->csvWidget->raise();
}

void MainWindow::on_jpgSubmit_clicked()
{
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
	
	FILE* fp = fopen("output/result.csv", "w+");
	fprintf(fp, "KFLU Output,\n");
	fprintf(fp, "Susceptible,exposed,Asymptomatic,Moderate,Severe,dead,Immune,total\n");

	for (int i = 0; i < 500; i++) {
		double helpme = SusceptibleArray[i] + ExposedArray[i] + AsymptomaticArray[i] + ModerateArray[i] + SevereArray[i] + DeadArray[i] + ImmuneArray[i];
		fprintf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,\n",SusceptibleArray[i], ExposedArray[i], AsymptomaticArray[i], ModerateArray[i], SevereArray[i], DeadArray[i], ImmuneArray[i],helpme);
	}
	fclose(fp);
    ui->csvWidget->hide();
}
