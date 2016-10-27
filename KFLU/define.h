#pragma once

//#include <Eigen/Dense>
#include <Eigen/Dense>
#include <iostream>

//**********************************************
//System Define
//==============================================
#define Maximumday 200
#define TimeResolution 10
#define NumberofArray Maximumday*TimeResolution
//**********************************************
//Define Value ���
//==============================================
//���ɺ� ����
#define Age0to6 0
#define Age7to12 1
#define Age13to18 2
#define Age19to64 3
#define Age65toEnd 4
//#define HCW 5
//#define AgeTotal 5	//ContactMatrix �հ� Part
#define StageofAgeGroups 5
//#define StageofAgeWithoutHCW 5
#define ChildClass 3

//�ٷα��� ���ɺ���
#define Child 0
#define Worker 1
#define Elderly 2
#define StageofWorkAge 3

//Severe ���� -> AM / VX�� ����
#define NonSevere 0
#define Severe 1
#define StageofSevere 2

//Risk ����
#define LowRisk 0
#define HighRisk 1
#define StageofRisk 2

//�����ܰ� E, I, R
#define Estage1 0
#define Estage2 1
#define EstageLast 6
#define EstageGroups 7

#define Istage1 0
#define Istage2 1
#define IstageLast 18
#define IstageGroups 19

#define Rstage1 0
#define Rstage2 1
#define RstageLast 8
#define RstageGroups 9

//BinarySearch �Լ� input data�� ���
#define typeR0 0
#define typeF50 1
#define typeDeadFraction 2

#define MedNO 0
#define MedYES 1
#define MedGroups 2

#define IsoNO 0
#define IsoYES 1
#define IsoGroups 2

//#define Non 0
//#define NICU 1
//#define ICU 2
//#define ICUGroups 3

#define Estage1 0
#define Estage2 1
#define EstageLast 6
#define EstageGroups 7

#define Istage1 0
#define Istage2 1
#define IstageLast 18
#define IstageGroups 19

#define Rstage1 0
#define Rstage2 1
#define RstageLast 8
#define RstageGroups 9

#define ItypeA 0
#define ItypeM 1
#define ItypeV 2
#define ItypeW 3
#define ItypeX 4
#define ItypeH 5
#define ItypeGroups 6


//**********************************************
//Ouput ���� Define
//==============================================
#define Ssize (StageofAgeGroups * StageofRisk)
#define Esize (StageofAgeGroups * StageofRisk * EstageGroups)
#define Asize (StageofAgeGroups * IstageGroups)
#define Msize (StageofAgeGroups * IstageGroups)
#define Vsize (StageofAgeGroups * IstageGroups)
#define Wsize (StageofAgeGroups * IstageGroups * MedGroups)
#define Xsize (StageofAgeGroups * IstageGroups)
#define Hsize (StageofAgeGroups * IstageGroups * MedGroups)
#define Rsize (StageofAgeGroups * RstageGroups)
#define Dsize StageofAgeGroups
#define Isize StageofAgeGroups
//���� ���ľ� ����Ʈ
#define APsize StageofAgeGroups
#define CAPsize StageofAgeGroups
#define CCIsize StageofAgeGroups

//�߰� ����Ʈ
#define N95maskSize StageofAgeGroups
#define RespiratorSize StageofAgeGroups
#define AntiviralsSize StageofAgeGroups
#define SpecimenSize StageofAgeGroups

#define OutpatientsSize StageofAgeGroups
#define HospitalICUSize StageofAgeGroups
#define HospitalNICUSize StageofAgeGroups

#define CumOutpatientsSize StageofAgeGroups
#define CumHospitalICUSize StageofAgeGroups
#define CumHospitalNICUSize StageofAgeGroups

//ouput array list
#define Soffset 0
#define Eoffset (Soffset + Ssize)	//10
#define Aoffset (Eoffset + Esize)	//80
#define Moffset (Aoffset + Asize)	//30
#define Voffset (Moffset + Msize)	//40
#define Woffset (Voffset + Vsize)	//50
#define Xoffset (Woffset + Wsize)	//50
#define Hoffset (Xoffset + Xsize)	//50
#define Roffset (Hoffset + Hsize)	//50
#define Doffset (Roffset + Rsize)	//50
#define Ioffset (Doffset + Dsize)	//50

#define APoffset (Ioffset + Isize)
//#define CAPoffset (APoffset + APsize)
//#define CCIoffset (CAPoffset + CAPsize)

// ������ TAB : Susceptibles, exposed, asymptomatic, moderate, severe, dead, immune
// �Ƿ��ڿ� TAB : N-95mask, respirator,  Antivirals
// ��ü�� TAB : Specimen

#define N95mask (APoffset + APsize)
#define Respirator (N95mask + N95maskSize)
#define Antivirals (Respirator + RespiratorSize)
#define Specimen (Antivirals + AntiviralsSize)

// ���� TAB : outpatients, HospitalICU, HospitalNICU
// ���� TAB : outpatients, HospitalICU, HospitalNICU
#define Outpatients (Specimen + SpecimenSize)
#define HospitalICU (Outpatients + OutpatientsSize)
#define HospitalNICU (HospitalICU + HospitalICUSize)
#define CumOutpatients (HospitalNICU + HospitalNICUSize)
#define CumHospitalICU (CumOutpatients + CumOutpatientsSize)
#define CumHospitalNICU (CumHospitalICU + CumHospitalICUSize)

//#define Outpatients1 (CumHospitalNICU + CumHospitalNICUSize)
//#define Antivirals1 (Outpatients + OutpatientsSize)
#define Hospitalisation (CumHospitalNICU + CumHospitalNICUSize)

//#define InfectedC (Hospitalisation + 1)
//#define CasesC (InfectedC + 1)
//#define HCWWorkReduction (CasesC + 1)
#define OutputArray (Hospitalisation + 1)

//**********************************************
//Output variables ���
//==============================================
// ������ TAB : Susceptibles, exposed, asymptomatic, moderate, severe, dead, immune
double PlotSusceptibles[StageofAgeGroups][NumberofArray];
double PlotExposed[StageofAgeGroups][NumberofArray];
double PlotAsymptomatic[StageofAgeGroups][NumberofArray];
double PlotModerate[StageofAgeGroups][NumberofArray];
double PlotSevere[StageofAgeGroups][NumberofArray];
double PlotDead[StageofAgeGroups][NumberofArray];
double PlotImmune[StageofAgeGroups][NumberofArray];

// �Ƿ��ڿ� TAB : N-95mask, respirator,  Antivirals
double PlotN95mask[StageofAgeGroups][NumberofArray];
double PlotRespirator[StageofAgeGroups][NumberofArray];
double PlotAntivirals[StageofAgeGroups][NumberofArray];

// ��ü�� TAB : Specimen
double PlotSpecimen[StageofAgeGroups][NumberofArray];

// ���� TAB : outpatients, HospitalICU, HospitalNICU
double PlotOutpatients[StageofAgeGroups][NumberofArray];
double PlotHospitalICU[StageofAgeGroups][NumberofArray];
double PlotHospitalNICU[StageofAgeGroups][NumberofArray];

// ���� TAB : outpatients, HospitalICU, HospitalNICU
double PlotCumOutpatients[StageofAgeGroups][NumberofArray];
double PlotCumHospitalICU[StageofAgeGroups][NumberofArray];
double PlotCumHospitalNICU[StageofAgeGroups][NumberofArray];

// ���� Output
double InitY[OutputArray];
//double OutputY[OutputArray];
//double VectorY[OutputArray];

double kk;

//**********************************************
//Define Function ���
//==============================================
double percentage(double);
double changehour(double hour);

int S(int age, int risk);
int E(int age, int risk, int eStages);
int A(int age, int iStage);
int M(int age, int iStage);
int V(int age, int iStage);
int W(int age, int iStage, int med);
int X(int age, int iStage);
int H(int age, int iStage, int med);
int R(int age, int rStage);
int D(int age);
int I(int age);
int AP(int age);
int CPA(int age);
int CIC(int age);

int N95(int age);
int Resp(int age);
int AV(int age);
int Spec(int age);

int Op(int age); //Outpatients
int HICU(int age);
int HNICU(int age);
int COp(int age);
int CHICU(int age);
int CHNICU(int age);

void InitialY();
void Initialize();
void Evaluation(double time, double VectorY[], double OutputY[]);
void KfluStep();
void ArrayforPlot(double day);

//**********************************************
//Input ȭ�� �� �Էº��� ���
//==============================================
//--�α�
double Population[StageofAgeGroups] = { 5272, 6773, 7952, 55086, 24917 };	//0to6, 7to12, 13to18, 19to64, 65toEnd, HCW
double ContactMatrix[StageofAgeGroups][StageofAgeGroups] =
{	{ 169.14,	31.47,	17.76,	34.50,	11.47	},
	{ 0,		274.51,	32.31,	34.86,	11.5	},
	{ 0,		0,		224.25,	60.75,	14.96	},
	{ 0,		0,		0,		120.66,	25.08	},
	{ 0,		0,		0,		0,		54.23	} };
double SchoolContactRate[ChildClass] = { 80.0, 70.0, 50.0 };		/*percentage �Լ� �ʿ�*/
//�Ἦ���� ��� ������ ��ȭ�Ǵ� ����
double AbsenceContactRatio[ChildClass] = { 75.0, 50.0, 25.0 };

//--���� TAB
double LatentPeriod = 1.9;
double InfectiousDuration[StageofSevere][StageofWorkAge] = { { 7.0, 4.1, 4.1 },{ 7.0, 7.0, 7.0 } };

double ReturntoWorkPeriod = 5.0;
double SevereRate = 33.3;		/*percentage �Լ� �ʿ�*/
double MildRate = 50.0;		/*percentage �Լ� �ʿ�*/
double HighRiskRate[StageofWorkAge] = { 6.0, 14.0, 47.0 };		/*percentage �Լ� �ʿ�*/
double LowRiskHospitalRate[StageofWorkAge] = { 0.187, 14.0, 47.0 };		/*percentage �Լ� �ʿ�*/
double HighRiskHospitalRate[StageofWorkAge] = { 1.333, 2.762, 7.768 };		/*percentage �Լ� �ʿ�*/
double DeadRate[StageofWorkAge] = { 5.541, 16.541, 39.505 };		/*percentage �Լ� �ʿ�*/

//--������ TAB
//���� ���� �� �����
double R0 = 2.5;
//�� ���� ���� �Ⱓ �� ���� �Ⱓ ���� ���� ������ ����
double HalfInfectiousRate = 90.0;		/*percentage �Լ� �ʿ�*/
//�������� ���� ���� �� ���� �� ����� ������
double LastLatentPeriodCase = 50.0;		/*percentage �Լ� �ʿ�*/
double AsymptomaticCase = 50.0;		/*percentage �Լ� �ʿ�*/
double ModerateCase = 100.0;		/*percentage �Լ� �ʿ�*/
//�κ� �ݸ�
double ModerateCaseIsolation = 0.0;		/*percentage �Լ� �ʿ�*/
double SevereHomeCaseIsolation = 0.0;		/*percentage �Լ� �ʿ�*/
double SevereHospitalCaseIsolation = 0.0;		/*percentage �Լ� �ʿ�*/
unsigned int RangeofIsolationBegin = 0;
unsigned int RangeofIsolationEnd = 200;

//--ġ�� TAB
//�׹��̷����� ���� ���� ����
double AntiviralsInjectionRate = 0.0;		/*percentage �Լ� �ʿ�*/
//�ǷἭ�� �̿밡�� �ð�
double MedicalHelp = 24.0;			//consultationDelay day�� ȯ��
double AntiviralsHelp = 48.0;		//maxTreatmentDelay day�� ȯ��
//Very Sick Case ġ��
double VerySickTreatRate = 0;		/*percentage �Լ� �ʿ�*/
unsigned int  VerySickTreatRangeBegin = 0;
unsigned int  VerySickTreatRangeEnd = 200;
//Extremely Sick Case ġ��
double ExtremelySickTreatRate = 0;		/*percentage �Լ� �ʿ�*/
unsigned int  ExtremelySickTreatRangeBegin = 0;
unsigned int  ExtremelySickTreatRangeEnd = 200;
//ġ�� ȿ��
double ContagiousnessReduction = 80.0;		/*percentage �Լ� �ʿ�*/
double DiseaseDurationReduction = 25.0;		/*percentage �Լ� �ʿ�*/
double HospitalizationReduction = 50.0;		/*percentage �Լ� �ʿ�*/

//--�ݸ� TAB
//�Ϲ����� ���� ���� �� �Ⱓ
double ContactReductionRate = 0.0;		/*percentage �Լ� �ʿ�*/
unsigned int  ContactReductionRangeBegin = 0;
unsigned int  ContactReductionRangeEnd = 200;
//�ޱ� �� �׿� ���� ���� ���� ����
unsigned int  SchoolCloseRangeBegin = 0;
unsigned int  SchoolCloseRangeEnd = 200;
double SchoolCloseContactRatio[ChildClass] = { 75.0, 50.0, 25.0 };
//������ȸ ��� �� �׿� ���� ���� ���� ����
double GatheringCancelReductionRate = 0.0;		/*percentage �Լ� �ʿ�*/
unsigned int  GatheringCancleRangeBegin = 0;
unsigned int  GatheringCancleRangeEnd = 200;

//--�Կ� TAB
//��� ����Ⱓ
double HospitalizationNICU = 5.0;
double HospitalizationICU = 10.0;

//--��� TAB
//���ɺ� ��� ������
double VaccineAgeRate[StageofAgeGroups] = { 0.0, 0.0, 0.0, 0.0, 0.0 };		/*percentage �Լ� �ʿ�*/
//���ɺ� ��� ����ȿ��
double VaccineEffectAgeRate[StageofAgeGroups] = { 0.0, 0.0, 0.0, 0.0, 0.0 };		/*percentage �Լ� �ʿ�*/
//��ü�����Ⱓ
double AntibodyCreateRange = 14;
//��� ���� �ñ�
double VaccineStart = 200;

//--�ڿ� TAB
//N-95����ũ(1��, 1�ϴ� ����)
double MaskNeedNICU = 1;
double MaskNeedICU = 2;
//�ΰ�ȣ��� (�Կ�ȯ�� �� �ΰ�ȣ��� ��� ����)
double RespiratorNeedRate = 50.0;		/*percentage �Լ� �ʿ�*/

//--��ü TAB
//��ü �����
double ReinspectionRate = 10.0;		/*percentage �Լ� �ʿ�*/
//�ܷ�ȯ�� ��ü����
double OutpatientSpecimenTesting = 50.0;		/*percentage �Լ� �ʿ�*/

//**********************************************
//������ ��� �� �ʿ� ���� ���
//==============================================
//Number of prodromal stages
int prodromalStages = 2;

//Contagiousness distribution over the infectious stages.
double contagiousness[IstageGroups];

//Contagiousness (by course of disease).
double infFact[ItypeGroups];

//Rate at which severe and extremely severe cases seek medical help.
double alpha;
//Rate at which severe cases at home again seek medical help.
double alphaW[StageofAgeGroups];

//beta, ebeta
double eBeta[StageofAgeGroups][StageofAgeGroups];
/*medgroups yes no, ITypegroups 6, ISOGroups yes no.*/
double beta[StageofAgeGroups][StageofAgeGroups][MedGroups][ItypeGroups][IsoGroups]; 

double total;
// Initial fraction of newly infected individuals.
double initialExposed;
double ageDistribution[StageofAgeGroups];

unsigned int ageClass[StageofAgeGroups] = { Child, Child, Child, Worker, Elderly }; // 0, 0, 0, 1, 2

double redistributionFactor[ChildClass];
double redistributionFactorChildHealthCare[ChildClass];

double ageMatrix[StageofAgeGroups][StageofAgeGroups];

double infDur[StageofAgeGroups][MedGroups][ItypeGroups];

double symptomaticFraction;
double moderateCasesFraction;
double severeCasesFraction;

double infDurMild[StageofWorkAge] = { 7.0, 4.1, 4.1 };
double infDurSevere[StageofWorkAge] = { 7.0, 7.0, 7.0 };

double rho;

double hospFract[StageofAgeGroups][StageofAgeGroups];
double hospPrevTreat;
double deadFraction[StageofAgeGroups];

double Individuals[StageofAgeGroups];

double tau[StageofAgeGroups];

//The eigenvecor for the largest eigenvalue (used for initialisation of the population).
double eigenvector[StageofAgeGroups];

//Force of infection.
double lambda[StageofAgeGroups];

bool doSchoolClosure0to6[2000];
bool doSchoolClosure7to12[2000];
bool doSchoolClosure13to18[2000];


double Susceptibles[StageofAgeGroups][StageofRisk];
//incubate the infection
double delta; 

//Average time after onset of symptoms when severe and extremely severe cases seek medical help[days].
double consultationDelay = changehour(MedicalHelp);

//Average number of doctoral visits per severe case.
double outpatientVisits = 1;

//Course of disease(by age and risk group).
//destiny(influsim)
double Courseofdisease[StageofAgeGroups][StageofRisk][ItypeGroups];

//Transition rate during the contagious period (by age, medication and course of disease)
double gamma[StageofAgeGroups][MedGroups][ItypeGroups];

//Maximum stage of contagiousness during which antiviral treatment can be given (by age)
int maxTreatmentStage[StageofAgeGroups];

//Fraction of immune individuals at start of simulation.
double immuneFract[StageofAgeGroups] = { 0.0, 0.0, 0.0, 0.0, 0.0 };

//**********************************************
//���� Variables
//==============================================
//Fraction of non-flu patients sent home.
double sentHomeFraction = 0.0;

//Daily fraction of treatment dose during antiviral prophylaxis.
double zeta = 0.1;

//Contact shift of flu patients to HCW [%].
double hcwContactFraction = 0.9;

//First day of health care worker prophylaxis.
double hcwProphylaxisBegin = 0.0;

//Day at which health care worker prophylaxis is terminated.
double hcwProphylaxisEnd = 0.0;

//Fraction of the population for which antiviral treatment is available.  /// 1.0
double antiviralRessource = percentage(AntiviralsInjectionRate);

//Treshold above which school closing is applied.
double schoolClosingTreshold = 1.0;

//Number of non-flu patients.
double nonFluPatients = 500;

//Reduction of susceptibility by antiviral prophylactic treatement.
double treatEfficacySusceptiblilty = 0.5;

//�Կ��� ���÷翣�� ����ȯ�� �� ICU Care�� �ʿ��� ��� ����(default 0.15)
double FractionofICU = 0.15;

//ICU �Կ� �� Sojourn time
double infDurforICU = 10.0;

//**********************************************
//Function & Class
//==============================================
class BinarySearch
{
public:
	double gam = 0;
	double dead = 0;

	double findRoot(double a, double b, int type) {
		if ((a <= 0) && (b >= 0))
			return find(a, b, type);
		else if ((b <= 0) && (a >= 0))
			return find(b, a, type);
		else
		{
		}//system Error massage
		return 0;
	}
	double ComputeR0(double b)
	{
		for (int ageSus = 0; ageSus < StageofAgeGroups; ageSus++) {
			for (int ageInf = 0; ageInf < StageofAgeGroups; ageInf++) {
				eBeta[ageSus][ageInf] = percentage(LastLatentPeriodCase) * b * ageMatrix[ageSus][ageInf];   // eBeta. LastLatentPeriodCase = eInfFact

				for (int type = ItypeA; type <= ItypeM; type++) { // type A, M
					beta[ageSus][ageInf][MedNO][type][IsoNO] = infFact[type] * b * ageMatrix[ageSus][ageInf];  // Contact Matrix�� ageMatrix�� �ٲ���ϳ�? fill matrix �Լ�
				}
			}
		}

		//Severly ill children do not go to school      beta���� ���ܺκ� ó��. �б��ٴϴ� ���̴�
		for (int type = ItypeV; type <= ItypeH; type++)  // type V, W, X, H
		{
			for (int ageSus = Age0to6; ageSus <= Age13to18; ageSus++) {
				for (int ageInf = Age0to6; ageInf <= Age13to18; ageInf++) {
					if (ageSus == ageInf) {
						beta[ageSus][ageInf][MedNO][type][IsoNO] = infFact[type] * b *  ageMatrix[ageSus][ageInf] * (1.0 - percentage(SchoolContactRate[ageInf])); // �Ἦ���� ���� �б� ���̴� ���μ��� ���� X
					}
					else {
						beta[ageSus][ageInf][MedNO][type][IsoNO] = infFact[type] * b * ageMatrix[ageSus][ageInf]; // �� �ܿ� ���� ������
					}
				}
			}
			for (int ageSus = Age19to64; ageSus <= StageofAgeGroups; ageSus++) { // �Ἦ�� �л����� care�����鼭 ����� ������. ����� �л����̴� ���� ����, HCW����
				for (int ageInf = Age0to6; ageInf <= Age13to18; ageInf++) {
					beta[ageSus][ageInf][MedNO][type][IsoNO] = infFact[type] * b *  ageMatrix[ageSus][ageInf] * redistributionFactorChildHealthCare[ageInf];
				}
			}

			//all other contacts remain untouched
			for (int ageSus = Age0to6; ageSus < StageofAgeGroups; ageSus++) {
				for (int ageInf = Age19to64; ageInf < StageofAgeGroups; ageInf++) {
					beta[ageSus][ageInf][MedNO][type][IsoNO] = infFact[type] * b * ageMatrix[ageSus][ageInf];
				}
			}
		}

		for (int ageSus = 0; ageSus < StageofAgeGroups; ageSus++) { // Med Yes�� ���
			for (int ageInf = 0; ageInf < StageofAgeGroups; ageInf++) {
				for (int type = ItypeA; type < ItypeGroups; type++) {
					beta[ageSus][ageInf][MedYES][type][IsoNO] = beta[ageSus][ageInf][MedNO][type][IsoNO] * (1.0 - percentage(ContagiousnessReduction));
				}
			}
		}

		//nextGenerationMatrix Calculation
		double nextGenerationMatrix[StageofAgeGroups][StageofAgeGroups];
		for (int ageSus = 0; ageSus < StageofAgeGroups; ageSus++) {
			for (int ageInf = 0; ageInf < StageofAgeGroups; ageInf++) {
				nextGenerationMatrix[ageSus][ageInf] = 
					(Susceptibles[ageSus][LowRisk] + Susceptibles[ageSus][HighRisk]) * eBeta[ageSus][ageInf] * LatentPeriod * prodromalStages / EstageGroups;

				for (int risk = 0; risk < StageofRisk; risk++) {
					for (int type = 0; type < ItypeGroups; type++) {
						double temp = Susceptibles[ageSus][risk] * Courseofdisease[ageInf][risk][type]
									* beta[ageSus][ageInf][MedNO][type][IsoNO] * infDur[ageInf][MedNO][type];
					if ((type == ItypeX) || (type == ItypeH))
						temp *= (1.0 - deadFraction[ageInf]);
					nextGenerationMatrix[ageSus][ageInf] += temp;
					}
				}
			}
		}
		
		Eigen::MatrixXd Ematirx(StageofAgeGroups, StageofAgeGroups);
		Eigen::MatrixXd realEigenvalues;
		Eigen::MatrixXd getEigenvector;
		Eigen::MatrixXd imagEigenvalues;
		

		for (int i = 0; i < StageofAgeGroups; i++)
		{
			for (int j = 0; j < StageofAgeGroups; j++)
			{
				Ematirx(i, j) = nextGenerationMatrix[i][j];
			}
		}

		Eigen::EigenSolver<Eigen::MatrixXd> Eigen_Matrix(Ematirx);
		realEigenvalues = Eigen_Matrix.eigenvalues().real();
		imagEigenvalues = Eigen_Matrix.eigenvalues().imag();
		getEigenvector = Eigen_Matrix.eigenvectors().real();
		double sizerealEigen = Eigen_Matrix.eigenvalues().real().size();

		double maxEigenvalue = -INFINITY;
		int maxI = -1;

		for (int i = 0; i < sizerealEigen; i++) {
			if (imagEigenvalues(i) != 0)
			{
			}//System.err.println("Imaginary eigenvalue (" + realEigenvalues[i] + ", " + imagEigenvalues[i] + " ) ignored."); //$NON-NLS-1$ //$NON-NLS-2$ //$NON-NLS-3$
			else if (realEigenvalues(i) > maxEigenvalue) {
				maxI = i;
				maxEigenvalue = realEigenvalues(i);
			}

		}

		/*
		for (int i = 0; i < sizerealEigen; i++) {
			std::cout << realEigenvalues(i) << std::endl;
		}*/

		double sum = 0.0;

		for (int age = 0; age < StageofAgeGroups; age++) {

			eigenvector[age] = getEigenvector(age, maxI);

			sum += eigenvector[age];
		}
		for (int age = 0; age < StageofAgeGroups; age++) {
			eigenvector[age] /= sum; // potential division by zero!
		}

		//m = nextGenerationMatrix;
		//bb = b;


		return maxEigenvalue - R0;

	}
	double computeDeadFraction(double gam, double t, double dead)
	{
		double result = 0.0;
		double product = 1.0;
		double temp = gam / (gam + t);
		for (int iStage = 0; iStage < IstageGroups; iStage++) {
			result += product;
			product *= temp;
		}
		result *= t / (t + gam);
		return result - dead;
	}
	double ComputeF50(double mu)
	{
		double product = 1.0;
		double sum = IstageGroups;
		if (mu < 1.0) sum = (1.0 - pow(mu, IstageGroups)) / (1.0 - mu);
		for (int i = 0; i < IstageGroups; i++) {
			contagiousness[i] = IstageGroups  * product / sum; // potential division by zero!
			product *= mu;
		}
		double allStagesInfectiosity = 0.0;
		for (int i = 0; i < IstageGroups; i++) {
			allStagesInfectiosity += contagiousness[i];
		}
		int halfInfectiousStages = IstageGroups / 2;
		double halfStagesInfectiosity = 0.0;
		for (int i = 0; i < halfInfectiousStages; i++) {
			halfStagesInfectiosity += contagiousness[i];
		}
		if (halfInfectiousStages + halfInfectiousStages < IstageGroups) {
			halfStagesInfectiosity += 0.5 * contagiousness[halfInfectiousStages];
		}

		return percentage(HalfInfectiousRate) - (halfStagesInfectiosity / allStagesInfectiosity);
	}
private:
	double find(double a, double b, int type) {
		double c = 0.5 * (a + b);
		double cval;
		
		if (b - a <= 1.0e-15)
			return c;
		switch (type)
		{
		case typeR0: cval = ComputeR0(c); break;
		case typeF50: cval = ComputeF50(c); break;
		case typeDeadFraction: cval = computeDeadFraction(gam, c, dead); break;
		default: return 0;
		}
		if (cval < 0)
			return find(c, b, type);
		if (cval > 0)
			return find(a, c, type);
		return c;
	}
};

double percentage(double value)
{
	return (value / 100);
}

double changehour(double hour)
{
	return (hour / 24);
}

int S(int age, int risk) {
	return Soffset + age * StageofRisk + risk;
}

int E(int age, int risk, int eStages) {
	return Eoffset + (age * StageofRisk + risk) * EstageGroups + eStages;
}

int A(int age, int iStage) {
	return Aoffset + age * IstageGroups + iStage;
}

int M(int age, int iStage) {
	return Moffset + age * IstageGroups + iStage;
}

int V(int age, int iStage) {
	return Voffset + age * IstageGroups + iStage;
}

int W(int age, int iStage, int med) {
	return Woffset + (age * IstageGroups + iStage) * MedGroups + med;
}

int X(int age, int iStage) {
	return Xoffset + age * IstageGroups + iStage;
}

int H(int age, int iStage, int med) {
	return Hoffset + ((age * IstageGroups + iStage) * MedGroups + med);
}

int R(int age, int rStage) {
	return Roffset + age * IstageGroups + rStage;
}

int D(int age) {
	return Doffset + age;
}

int I(int age) {
	return Ioffset + age;
}

int N95(int age) {
	return N95mask + age;
}
int Resp(int age) {
	return Respirator + age;
}
int AV(int age) {
	return Antivirals + age;
}
int Spec(int age) {
	return Specimen + age;
}

int Op(int age) {//Outpatients
	return Outpatients + age;
}
int HICU(int age) {
	return HospitalICU + age;
}
int HNICU(int age) {
	return HospitalNICU + age;
}

int COp(int age) {
	return CumOutpatients + age;
}
int CHICU(int age) {
	return CumHospitalICU + age;
}
int CHNICU(int age) {
	return CumHospitalNICU + age;
}
int AP(int age) {
	return APoffset + age;
}
/*
int CPA(int age) {
	return CAPoffset + age;
}

int CIC(int age) {
	return CCIoffset + age;
}*/
/*Initialize function*/
void Initialize()
{
	Individuals[Age0to6] = Population[Age0to6];
	Individuals[Age7to12] = Population[Age7to12];
	Individuals[Age13to18] = Population[Age13to18];
	Individuals[Age19to64] = Population[Age19to64];
	Individuals[Age65toEnd] = Population[Age65toEnd];


	//Distribution of individuals (by age)
	total = 0.0;
	for (int age = 0; age < StageofAgeGroups; age++)
		total += Individuals[age];

	if (total > 0) {
		initialExposed = 1.0 / total;
		for (int age = 0; age < StageofAgeGroups; age++)
			ageDistribution[age] = Individuals[age] / total;
	}
	else {
		initialExposed = 0.0;
		for (int age = 0; age < StageofAgeGroups; age++)
			ageDistribution[age] = 0;
	}

	// Distribution of individuals (by age and risk group
	for (int age = 0; age < StageofAgeGroups; age++) {
		Susceptibles[age][LowRisk] = ageDistribution[age] * (1.0 - percentage(HighRiskRate[ageClass[age]]));
		Susceptibles[age][HighRisk] = ageDistribution[age] * percentage(HighRiskRate[ageClass[age]]);
	}

	//Initializae the contact matrix
	//agematirx�� contactmatrix�� ������ ����
	//for (int i = 0; i < StageofAgeWithoutHCW; i++)
	//{
	//	for (int j = i; j < StageofAgeWithoutHCW; j++)
	//	{
	//		ageMatrix[i][j] = ContactMatrix[i][j];
	//		ageMatrix[j][i] = ContactMatrix[i][j];
	//		qDebug("%f", ageMatrix[i][j]);
	//	}
	//}

	ageMatrix[0][0] = ContactMatrix[0][0];
	ageMatrix[0][1] = ContactMatrix[0][1]; ageMatrix[1][0] = ContactMatrix[0][1];
	ageMatrix[0][2] = ContactMatrix[0][2]; ageMatrix[2][0] = ContactMatrix[0][2];
	ageMatrix[0][3] = ContactMatrix[0][3]; ageMatrix[3][0] = ContactMatrix[0][3];
	ageMatrix[0][4] = ContactMatrix[0][4]; ageMatrix[4][0] = ContactMatrix[0][4];

	ageMatrix[1][1] = ContactMatrix[1][1];
	ageMatrix[1][2] = ContactMatrix[1][2]; ageMatrix[2][1] = ContactMatrix[1][2];
	ageMatrix[1][3] = ContactMatrix[1][3]; ageMatrix[3][1] = ContactMatrix[1][3];
	ageMatrix[1][4] = ContactMatrix[1][4]; ageMatrix[4][1] = ContactMatrix[1][4];

	ageMatrix[2][2] = ContactMatrix[2][2];
	ageMatrix[2][3] = ContactMatrix[2][3]; ageMatrix[3][2] = ContactMatrix[2][3];
	ageMatrix[2][4] = ContactMatrix[2][4]; ageMatrix[4][2] = ContactMatrix[2][4];

	ageMatrix[3][3] = ContactMatrix[3][3]; 
	ageMatrix[3][4] = ContactMatrix[3][4]; ageMatrix[4][3] = ContactMatrix[3][4];

	ageMatrix[4][4] = ContactMatrix[4][4];

	for (int ageSus = 0; ageSus < Age19to64; ageSus++) {
		double denominator = 0.0;
		for (int ageInf = Age19to64; ageInf < StageofAgeGroups; ageInf++) {
			denominator += ageMatrix[ageSus][ageInf] * Individuals[ageInf];
		}
		redistributionFactor[ageSus] = 1.0 + percentage(SchoolContactRate[ageSus]) * percentage(AbsenceContactRatio[ageSus]) * ageMatrix[ageSus][ageSus] * Individuals[ageSus] / denominator;
		redistributionFactorChildHealthCare[ageSus] = 1.0 + percentage(SchoolContactRate[ageSus]) * percentage(SchoolCloseContactRatio[ageSus]) * ageMatrix[ageSus][ageSus] * Individuals[ageSus] / denominator;
	}

	//Initialize transition rate delta for the latent period
	delta = EstageGroups / LatentPeriod;

	//Initialize the average duration of the infectious periods by age, medication and course of disease // ���ɺ� �ẹ�� ���� ��� ���� ���� �Ⱓ
	for (int age = 0; age < StageofAgeGroups; age++) {
		infDur[age][MedNO][ItypeA] = InfectiousDuration[NonSevere][ageClass[age]];
		infDur[age][MedNO][ItypeM] = InfectiousDuration[NonSevere][ageClass[age]];
		infDur[age][MedNO][ItypeV] = InfectiousDuration[Severe][ageClass[age]];
		infDur[age][MedNO][ItypeW] = InfectiousDuration[Severe][ageClass[age]];
		infDur[age][MedNO][ItypeX] = InfectiousDuration[Severe][ageClass[age]];
		infDur[age][MedNO][ItypeH] = InfectiousDuration[Severe][ageClass[age]];
		for (int type = 0; type < ItypeGroups; type++)
		{
			infDur[age][MedYES][type] = (1.0 - percentage(DiseaseDurationReduction)) * infDur[age][MedNO][type];
		}
	}

	//Initialize the fractions for asymptomatic, moderate and severe cases  // �������ڿ� ������ �� ���� ������� ����
	symptomaticFraction = 1.0 - percentage(SevereRate); // �Է¹޴� ���� �������� �����̱� ������ ������ ���� = 1.0 - �������� ������ ����
	moderateCasesFraction = (1.0 - percentage(MildRate)) * symptomaticFraction;
	severeCasesFraction = percentage(MildRate) * symptomaticFraction;

	// Initialize the transition rate rho for the reconvalescent period
	rho = RstageGroups / ReturntoWorkPeriod;

	//Initialize the fraction of extremely severe cases among all severe cases by age and risk group
	for (int age = 0; age < StageofAgeGroups; age++) {
		hospFract[age][LowRisk] = percentage(LowRiskHospitalRate[ageClass[age]]);
		hospFract[age][HighRisk] = percentage(HighRiskHospitalRate[ageClass[age]]);
	}

	//Initialize the fraction of hospitalisations prevented by treatment
	hospPrevTreat = percentage(HospitalizationReduction);

	//Initialize what fraction of extremely severe cases dies by age and medication
	for (int age = 0; age < StageofAgeGroups; age++) {
		deadFraction[age] = percentage(DeadRate[ageClass[age]]);
	}

	//Initialize the contagiousness of cases by course of disease
	infFact[ItypeA] = percentage(AsymptomaticCase);
	infFact[ItypeM] = percentage(ModerateCase);
	infFact[ItypeV] = 1.0;
	infFact[ItypeW] = 1.0;
	infFact[ItypeX] = 1.0;
	infFact[ItypeH] = 1.0;

	// Initialize the contagiousness distribution.
	BinarySearch Root;
	Root.findRoot(0, 1, typeF50);

	// Initialize the rate alpha at which severe and extremely severe cases seek medical help.
	alpha = 1.0 / consultationDelay; // potential division by zero!

	for (int age = 0; age < StageofAgeGroups; age++) {
		alphaW[age] = (outpatientVisits - 1) / (InfectiousDuration[Severe][ageClass[age]] - consultationDelay);
	}

	// Initialize what courses of disease cases of different age and risk group will take
	for (int age = 0; age < StageofAgeGroups; age++) {
		for (int risk = 0; risk < StageofRisk; risk++) {
			Courseofdisease[age][risk][ItypeA] = (1.0 - symptomaticFraction);
			Courseofdisease[age][risk][ItypeM] = moderateCasesFraction;
			Courseofdisease[age][risk][ItypeW] = 0.0;
			Courseofdisease[age][risk][ItypeH] = 0.0;
			Courseofdisease[age][risk][ItypeV] = severeCasesFraction * (1.0 - hospFract[age][risk]);
			Courseofdisease[age][risk][ItypeX] = severeCasesFraction * hospFract[age][risk];
		}
	}

	// Initialize the transition rate gamma during the contagious period 
	// and the highest stage of contagiousness maxTreatmentStage 
	// during which antiviral treatment can be given.
	for (int age = 0; age < StageofAgeGroups; age++) {
		for (int med = 0; med < MedGroups; med++) {
			for (int type = 0; type < ItypeGroups; type++) {
				gamma[age][med][type] = IstageGroups / infDur[age][med][type];

			}

		}
		maxTreatmentStage[age] = (int)ceil(changehour(AntiviralsHelp) * gamma[age][MedNO][ItypeV]);

	}


	// Find a factor x such that the resulting basic reproduction number is 
	// as desired. This will implicitly initialize the effective contact matrix beta.
	Root.findRoot(0, 1, typeR0);

	// Modify the effective contact matrix beta to consider the effect of partial isolation of cases.
	for (int ageSus = 0; ageSus < StageofAgeGroups; ageSus++) {
		for (int ageInf = 0; ageInf < StageofAgeGroups; ageInf++) {
			for (int med = 0; med < MedGroups; med++) {
				beta[ageSus][ageInf][med][ItypeA][IsoYES] = beta[ageSus][ageInf][med][ItypeA][IsoNO];
				beta[ageSus][ageInf][med][ItypeM][IsoYES] = beta[ageSus][ageInf][med][ItypeM][IsoNO] * (1.0 - percentage(ModerateCaseIsolation));
				beta[ageSus][ageInf][med][ItypeV][IsoYES] = beta[ageSus][ageInf][med][ItypeV][IsoNO] * (1.0 - percentage(SevereHomeCaseIsolation));
				beta[ageSus][ageInf][med][ItypeW][IsoYES] = beta[ageSus][ageInf][med][ItypeW][IsoNO] * (1.0 - percentage(SevereHomeCaseIsolation));
				beta[ageSus][ageInf][med][ItypeX][IsoYES] = beta[ageSus][ageInf][med][ItypeX][IsoNO] * (1.0 - percentage(SevereHomeCaseIsolation));
				beta[ageSus][ageInf][med][ItypeH][IsoYES] = beta[ageSus][ageInf][med][ItypeH][IsoNO] * (1.0 - percentage(SevereHospitalCaseIsolation));
			}
		}
	}

	// Initialize the rate tau at which extremely severe cases die (by age 
	// and medication). tau is chosen such that the chosen fraction dies 
	// during the period of contagiousness.
	for (int age = 0; age < StageofAgeGroups; age++) {
		Root.dead = deadFraction[age];
		Root.gam = gamma[age][MedNO][ItypeH] + gamma[age][MedNO][ItypeH];
		tau[age] = Root.findRoot(0, 1, typeDeadFraction);
	}

	std::fill_n(doSchoolClosure0to6, NumberofArray, false);
	std::fill_n(doSchoolClosure7to12, NumberofArray, false);
	std::fill_n(doSchoolClosure13to18, NumberofArray, false);


	//std::fill_n(cc + 3, 5, true); -> 0001111100000~
	if (SchoolCloseRangeBegin != SchoolCloseRangeEnd) {
		std::fill_n(doSchoolClosure0to6 + SchoolCloseRangeBegin, SchoolCloseRangeEnd - SchoolCloseRangeBegin, true);
		std::fill_n(doSchoolClosure7to12 + SchoolCloseRangeBegin, SchoolCloseRangeEnd - SchoolCloseRangeBegin, true);
		std::fill_n(doSchoolClosure13to18 + SchoolCloseRangeBegin, SchoolCloseRangeEnd - SchoolCloseRangeBegin, true);
	}
}

/*Initial Y data*/
void InitialY()
{
	std::fill_n(InitY, OutputArray, 0);

	for (int age = 0; age < StageofAgeGroups; age++) {
		for (int risk = 0; risk < StageofRisk; risk++) {
			InitY[S(age, risk)] = Susceptibles[age][risk] * (1.0 - immuneFract[age]);
			InitY[I(age)] = (Susceptibles[age][LowRisk] + Susceptibles[age][HighRisk]) * immuneFract[age];
		}
	}

	for (int age = 0; age < StageofAgeGroups; age++) {
		double exposedLowRisk = (1.0 - percentage(HighRiskRate[ageClass[age]])) * eigenvector[age] / total; // potential division by zero!
		InitY[S(age, LowRisk)] -= exposedLowRisk;
		InitY[E(age, LowRisk, Estage1)] = exposedLowRisk;
		double exposedHighRisk = percentage(HighRiskRate[ageClass[age]]) * eigenvector[age] / total; // potential division by zero!
		InitY[S(age, HighRisk)] -= exposedHighRisk;
		InitY[E(age, HighRisk, Estage1)] = exposedHighRisk;
	}
}

/////////////////////////////////////////////////////====================================================================================================
/////////////////////////////////////////////////////====================================================================================================

void Evaluation(double time, double VectorY[], double OutputY[])
{

	// Initialize counters. 
	
	// ������ TAB : Susceptibles, exposed, asymptomatic, moderate, severe, dead, immune
	// �Ƿ��ڿ� TAB : N-95mask, respirator,  Antivirals
	// ��ü�� TAB : 
	// ���� TAB : outpatients, HospitalICU, HospitalNICU
	// ���� TAB : outpatients, HospitalICU, HospitalNICU
	for (int age = 0; age < StageofAgeGroups; age++)
	{
		OutputY[Op(age)] = 0.0;
		OutputY[AV(age)] = 0.0;
	}
	OutputY[Hospitalisation] = 0.0;

	double Antiviralstotal = 0.0;
	for (int age = 0; age < StageofAgeGroups; age++)
		Antiviralstotal = VectorY[AV(age)];

	bool doProphylaxis = false;
	if ((time >= hcwProphylaxisBegin) && (time<hcwProphylaxisEnd)) {
		if (antiviralRessource>Antiviralstotal) {
			doProphylaxis = true;
			OutputY[Antivirals] = zeta;
		}
	}
	//���
	if (SchoolCloseRangeBegin == SchoolCloseRangeEnd) {
		if (VectorY[AP(Age0to6)] * total / Individuals[Age0to6] > schoolClosingTreshold)
			doSchoolClosure0to6[(int)ceil(time)] = true;
		if (VectorY[AP(Age7to12)] * total / Individuals[Age7to12] > schoolClosingTreshold)
			doSchoolClosure7to12[(int)ceil(time)] = true;
		if (VectorY[AP(Age13to18)] * total / Individuals[Age13to18] > schoolClosingTreshold)
			doSchoolClosure13to18[(int)ceil(time)] = true;
	}

	bool doSchoolClosing0to6 = doSchoolClosure0to6[(int)floor(time)];
	bool doSchoolClosing6to12 = doSchoolClosure7to12[(int)floor(time)];
	bool doSchoolClosing13to19 = doSchoolClosure13to18[(int)floor(time)];

	// Calculate the current force of infection.
	for (int ageSus = 0; ageSus < StageofAgeGroups; ageSus++) {
		if (ageSus<StageofAgeGroups) lambda[ageSus] = 0.0;
		for (int ageInf = 0; ageInf < StageofAgeGroups; ageInf++) {

			double cancellingFactor = 1.0;
			double infChildCareFactor = 1.0;
			double susChildCareFactor = 1.0;
			int isolation = ((time >= RangeofIsolationBegin) && (time < RangeofIsolationEnd)) ? IsoYES : IsoNO;
			if ((ageSus <= Age13to18) && (ageInf <= Age13to18)) {/*�б� �ޱ��� ���� ����*/
				if (ageSus == ageInf) {
					if ((ageInf == Age0to6) && (doSchoolClosing0to6)) {
						cancellingFactor = (1.0 - percentage(SchoolContactRate[ageInf]));
					}
					if ((ageInf == Age7to12) && (doSchoolClosing6to12)) {
						cancellingFactor = (1.0 - percentage(SchoolContactRate[ageInf]));
					}
					if ((ageInf == Age13to18) && (doSchoolClosing13to19)) {
						cancellingFactor = (1.0 - percentage(SchoolContactRate[ageInf]));
					}
				}
			}
			else if ((ageSus >= Age19to64) && (ageInf >= Age19to64)) {/*������ȸ�� ���� ����*/
				if ((time >= GatheringCancleRangeBegin) && (time<GatheringCancleRangeEnd)) {
					cancellingFactor = (1.0 - percentage(GatheringCancelReductionRate));
				}
			}
			else {
				if (doSchoolClosing0to6) {
					if (ageInf == Age0to6) infChildCareFactor = redistributionFactor[ageInf];
					if (ageSus == Age0to6) susChildCareFactor = redistributionFactor[ageSus];
				}
				if (doSchoolClosing6to12) {
					if (ageInf == Age7to12) infChildCareFactor = redistributionFactor[ageInf];
					if (ageSus == Age7to12) susChildCareFactor = redistributionFactor[ageSus];
				}
				if (doSchoolClosing13to19) {
					if (ageInf == Age13to18) infChildCareFactor = redistributionFactor[ageInf];
					if (ageSus == Age13to18) susChildCareFactor = redistributionFactor[ageSus];
				}
			}
			
			double generalFactor = 1.0;
			if ((time >= ContactReductionRangeBegin) && (time <  ContactReductionRangeEnd))
				generalFactor *= (1.0 - percentage(ContactReductionRate));
			double temp = 0.0;
			
			for (int eStage = EstageGroups - prodromalStages; eStage < EstageGroups; eStage++) {
				temp += (VectorY[E(ageInf, LowRisk, eStage)] + VectorY[E(ageInf, HighRisk, eStage)])  * eBeta[ageSus][ageInf] * cancellingFactor * susChildCareFactor * infChildCareFactor;
			}
			
			for (int iStage = 0; iStage < IstageGroups; iStage++) {
				temp += (VectorY[A(ageInf, iStage)] * beta[ageSus][ageInf][MedNO][ItypeA][isolation] * cancellingFactor * susChildCareFactor * infChildCareFactor
					+ VectorY[M(ageInf, iStage)] * beta[ageSus][ageInf][MedNO][ItypeM][isolation] * cancellingFactor * susChildCareFactor * infChildCareFactor
					+ VectorY[V(ageInf, iStage)] * beta[ageSus][ageInf][MedNO][ItypeV][isolation] * susChildCareFactor
					+ VectorY[X(ageInf, iStage)] * beta[ageSus][ageInf][MedNO][ItypeX][isolation] * susChildCareFactor
					+ VectorY[W(ageInf, iStage, MedNO)] * beta[ageSus][ageInf][MedNO][ItypeW][isolation] * susChildCareFactor
					+ VectorY[W(ageInf, iStage, MedYES)] * beta[ageSus][ageInf][MedYES][ItypeW][isolation] * susChildCareFactor
					+ (VectorY[H(ageInf, iStage, MedNO)] * beta[ageSus][ageInf][MedNO][ItypeH][isolation] * susChildCareFactor
					+ VectorY[H(ageInf, iStage, MedYES)] * beta[ageSus][ageInf][MedYES][ItypeH][isolation] * susChildCareFactor) * (1.0 - hcwContactFraction) * contagiousness[iStage]);
			}
			lambda[ageSus] += temp * generalFactor;
		}
	}

	// Calculate what fraction of severe cases are treated.
	double todaySevereTreatFract = 0.0;
	if ((time >= VerySickTreatRangeBegin) && (time<VerySickTreatRangeEnd)) {
		todaySevereTreatFract = percentage(VerySickTreatRate);
		if (antiviralRessource <= Antiviralstotal) todaySevereTreatFract = 0.0;
	}

	// Calculate what fraction of extremely severe cases are treated.
	double todayExtremeTreatFract = 0.0;
	if ((time >= ExtremelySickTreatRangeBegin) && (time<ExtremelySickTreatRangeEnd)) {
		todayExtremeTreatFract = percentage(ExtremelySickTreatRate);
		if (antiviralRessource <= Antiviralstotal) todayExtremeTreatFract = 0.0;
	}

	// Susceptible individuals are infected.
	double ImmunebyVaccine;
	double Vaccine;
	if ((VaccineStart <= time) && (time < (VaccineStart + AntibodyCreateRange)))
		ImmunebyVaccine = 1;
	else
		ImmunebyVaccine = 0;
	for (int age = 0; age < StageofAgeGroups; age++) {
		for (int risk = 0; risk < StageofRisk; risk++) {
			Vaccine = ImmunebyVaccine * percentage(VaccineAgeRate[age]) / AntibodyCreateRange * percentage(VaccineEffectAgeRate[age]);
			OutputY[S(age, risk)] = -lambda[age] * (VectorY[S(age, risk)]);
		}
	}
	
	for (int age = 0; age < StageofAgeGroups; age++) {
		for (int risk = 0; risk < StageofRisk; risk++) {
			for (int k = 0; k < EstageGroups; k++) {
				if (k == Estage1)
					OutputY[E(age, risk, k)] = lambda[age] * VectorY[S(age, risk)] - delta * VectorY[E(age, risk, Estage1)];
				else {
					OutputY[E(age, risk, k)] = delta * (VectorY[E(age, risk, k - 1)] - VectorY[E(age, risk, k)]);
				}
			}

			// Some of the individuals who have just passed through 
			// the incubation period become asymptomatic cases now.
			OutputY[A(age, Istage1)]
				= delta * (Courseofdisease[age][LowRisk][ItypeA] * VectorY[E(age, LowRisk, EstageLast)]
					+ Courseofdisease[age][HighRisk][ItypeA] * VectorY[E(age, HighRisk, EstageLast)])
				- gamma[age][MedNO][ItypeA] * VectorY[A(age, Istage1)];
			// Some of the individuals who have just passed through 
			// the incubation period become moderately sick cases now.
			double mCases = delta * (Courseofdisease[age][LowRisk][ItypeM] * VectorY[E(age, LowRisk, EstageLast)]
				+ Courseofdisease[age][HighRisk][ItypeM] * VectorY[E(age, HighRisk, EstageLast)]);
			OutputY[M(age, Istage1)] = mCases - gamma[age][MedNO][ItypeM] * VectorY[M(age, Istage1)];
			// Some of the individuals who have just passed through 
			// the incubation period become severe cases now.
			double vCases = delta * (Courseofdisease[age][LowRisk][ItypeV] * VectorY[E(age, LowRisk, EstageLast)]
				+ Courseofdisease[age][HighRisk][ItypeV] * VectorY[E(age, HighRisk, EstageLast)]);
			OutputY[V(age, Istage1)] = vCases - (gamma[age][MedNO][ItypeV] + alpha) * VectorY[V(age, Istage1)];
			// Some of the individuals who have just passed through 
			// the incubation period become extremely severe cases now.
			double xCases = delta * (Courseofdisease[age][LowRisk][ItypeX] * VectorY[E(age, LowRisk, EstageLast)]
				+ Courseofdisease[age][HighRisk][ItypeX] * VectorY[E(age, HighRisk, EstageLast)]);
			OutputY[X(age, Istage1)] = xCases - (gamma[age][MedNO][ItypeX]+ (alpha + tau[age])) * VectorY[X(age, Istage1)];
			// Some severe cases in contagiousness stage 1 have received treatment.
			// Some extremely severe cases in contagiousness stage 1 whose 
			// hospitalization could be avoided through antiviral treatment, join this group.
			OutputY[W(age, Istage1, MedYES)]
				= alpha * (VectorY[V(age, Istage1)] * todaySevereTreatFract + hospPrevTreat * VectorY[X(age, Istage1)] * todayExtremeTreatFract)
				- gamma[age][MedYES][ItypeW] * VectorY[W(age, Istage1, MedYES)];
			// Some extremely severe cases in contagiousness stage 1 have received 
			// treatment and are hospitalized (hospitalization could not be prevented).
			// Istage1, Treated, ICU case
			OutputY[H(age, Istage1, MedYES)]
				= alpha * todayExtremeTreatFract * (1.0 - hospPrevTreat) * VectorY[X(age, Istage1)]
				- (gamma[age][MedYES][ItypeH] + tau[age]) * VectorY[H(age, Istage1, MedYES)];
			// Some severe cases in contagiousness stage 1 have seen the doctor 
			// but have not received treatment.
			OutputY[W(age, Istage1, MedNO)]
				= alpha * (1.0 - todaySevereTreatFract) * VectorY[V(age, Istage1)] - gamma[age][MedNO][ItypeW] * VectorY[W(age, Istage1, MedNO)];
			// Some extremely severe cases in contagiousness stage 1 have seen 
			// the doctor and have been hospitalized, but have not received treatment.
			//Istage1, UnTreated, ICU

			OutputY[H(age, Istage1, MedNO)]
				= alpha * (1.0 - todayExtremeTreatFract) * VectorY[X(age, Istage1)] - (gamma[age][MedNO][ItypeH] + tau[age]) * VectorY[H(age, Istage1, MedNO)];
			//Istage1, UnTreated, NICU

			for (int iStage = Istage2; iStage < IstageGroups; iStage++) {
				int previousStage = iStage - 1;
				// Progress through the contagious period for asymptomatic cases.
				OutputY[A(age, iStage)]
					= gamma[age][MedNO][ItypeA]* (VectorY[A(age, previousStage)] - VectorY[A(age, iStage)]);
				// Progress through the contagious period for moderately sick cases.
				OutputY[M(age, iStage)]
					= gamma[age][MedNO][ItypeM] * (VectorY[M(age, previousStage)] - VectorY[M(age, iStage)]);
				// Progress through the contagious period for severe cases 
				// (some seek medical help and possibly obtain treatment).
				OutputY[V(age, iStage)]
					= gamma[age][MedNO][ItypeV] * (VectorY[V(age, previousStage)] - VectorY[V(age, iStage)])
					- alpha * VectorY[V(age, iStage)];
				// Progress through the contagious period for extremely severe cases 
				// (some seek medical help, may be hospitalized and/or obtain antiviral treatment).
				OutputY[X(age, iStage)]
					= gamma[age][MedNO][ItypeX] * (VectorY[X(age, previousStage)] - VectorY[X(age, iStage)]) - (alpha + tau[age])  * VectorY[X(age, iStage)];
				if (iStage + 1 < maxTreatmentStage[age]) {
					// Some severe cases have just been treated, others simply progress 
					// in their contagious period. Some newly treated extremely severe 
					// cases whose hospitalization could be prevented by treatment, join this group.
					OutputY[W(age, iStage, MedYES)]
						= gamma[age][MedYES][ItypeW] * (VectorY[W(age, previousStage, MedYES)]
							- VectorY[W(age, iStage, MedYES)]) + alpha * (VectorY[V(age, iStage)] * todaySevereTreatFract
								+ hospPrevTreat * VectorY[X(age, iStage)] * todayExtremeTreatFract);
					// Some new severe cases have just seen the doctor without receiving 
					// antiviral treatment, others simply progress in their contagious period.
					OutputY[W(age, iStage, MedNO)]
						= gamma[age][MedNO][ItypeW] * (VectorY[W(age, previousStage, MedNO)]
							- VectorY[W(age, iStage, MedNO)]) + alpha * (1.0 - todaySevereTreatFract) * VectorY[V(age, iStage)];
					// Some new extremely severe cases have just been treated and 
					// hospitalized, other hospitalized casess simply progress in their 
					// contagious period.
					//Istage, UnTreat, ICU
					OutputY[H(age, iStage, MedYES)]
						= (alpha * todayExtremeTreatFract * (1.0 - hospPrevTreat) * VectorY[X(age, iStage)])
						+ gamma[age][MedYES][ItypeH] * (VectorY[H(age, previousStage, MedYES)] - VectorY[H(age, iStage, MedYES)])
						- tau[age] * VectorY[H(age, iStage, MedYES)];

					// Some new extremely severe cases have just been hospitalized 
					// without receiving antiviral treatment; other hospitalized cases 
					// simply progress in their contagious period.
					//Istage, UnTreat, ICU
					OutputY[H(age, iStage, MedNO)]
						= (alpha * (1.0 - todayExtremeTreatFract) * VectorY[X(age, iStage)])
						+ gamma[age][MedNO][ItypeH] * (VectorY[H(age, previousStage, MedNO)] - VectorY[H(age, iStage, MedNO)])
						- tau[age] * VectorY[H(age, iStage, MedNO)];

				}
				else {
					// Formerly treated severe cases progress in their contagious period.
					OutputY[W(age, iStage, MedYES)]
						= gamma[age][MedYES][ItypeW] * (VectorY[W(age, previousStage, MedYES)]
							- VectorY[W(age, iStage, MedYES)]);
					// Some new severe cases have just seen the doctor without receiving 
					// antiviral treatment, others simply progress in their contagious period.
					OutputY[W(age, iStage, MedNO)]
						= gamma[age][MedNO][ItypeW] * (VectorY[W(age, previousStage, MedNO)]
							- VectorY[W(age, iStage, MedNO)]) + alpha * VectorY[V(age, iStage)];
					// Formerly treated hospitalized cases progress in their contagious period.
					//Istage, Treat, NICU
					OutputY[H(age, iStage, MedYES)]
						= gamma[age][MedYES][ItypeH] * (VectorY[H(age, previousStage, MedYES)] - VectorY[H(age, iStage, MedYES)])
						- tau[age] * VectorY[H(age, iStage, MedYES)];

					// Some new extremely severe cases have just seen the doctor and 
					// have been hospitalized without receiving antiviral treatment, other 
					// formerly untreated hospitalized cases simply progress in their contagious period.
					//Istage, UnTreat, ICU
					OutputY[H(age, iStage, MedNO)]
						= alpha * VectorY[X(age, iStage)]
						+ gamma[age][MedNO][ItypeH] * (VectorY[H(age, previousStage, MedNO)] - VectorY[H(age, iStage, MedNO)])
						- tau[age] * VectorY[H(age, iStage, MedNO)];

				}
			}
		}
	}


	for (int age = 0; age < StageofAgeGroups; age++) {
		OutputY[R(age, Rstage1)] = 0.0;
		for (int rStage = Rstage2; rStage < RstageGroups; rStage++) {
			OutputY[R(age, rStage)] = 0.0;
		}
		OutputY[D(age)] = 0.0;
		OutputY[I(age)] = 0.0;

		// All severe and extremely severe cases have to go through a period
		// of reconvalcescence after passing through their contagious period.
		OutputY[R(age, Rstage1)]
			= gamma[age][MedNO][ItypeV] * VectorY[V(age, IstageLast)]
			+ gamma[age][MedNO][ItypeX] * VectorY[X(age, IstageLast)]
			+ gamma[age][MedNO][ItypeW] * VectorY[W(age, IstageLast, MedNO)]
			+ gamma[age][MedNO][ItypeH] * VectorY[H(age, IstageLast, MedNO)]
			+ gamma[age][MedYES][ItypeW] * VectorY[W(age, IstageLast, MedYES)]
			+ gamma[age][MedYES][ItypeH] * VectorY[H(age, IstageLast, MedYES)]
			- rho * VectorY[R(age, Rstage1)];

		//if (time == 0.01171875)
		//	OutputY[R(Age19to64, Rstage2)] = 0.0;
		//if (time == 0.015625)
		//	OutputY[R(Age19to64, Rstage2)] = 0.0;
		//if (VectorY[R(age,Rstage1)] - VectorY[R(age,Rstage2)] < 1.0e-15)
		//	OutputY[R(Age19to64, Rstage2)] = 0.0;
		// Progress during the reconvalescent period.
		for (int rStage = Rstage2; rStage < RstageGroups; rStage++) {
			if (rStage != Rstage2)
				if (age != Age19to64)
					OutputY[R(age, rStage)] = rho * (VectorY[R(age, rStage - 1)] - VectorY[R(age, rStage)]);

			//OutputY[R(age, rStage)] = rho * (VectorY[R(age, rStage - 1)] + VectorY[R(age, rStage)]);
			if (rStage == Rstage2)
				if (age == Age19to64) {
					kk = rho * (VectorY[R(age, rStage - 1)] - VectorY[R(age, rStage)]);
					OutputY[R(age, rStage)] = kk;
				}
		}

		// Update the number of cases who died.
		double dead = 0;
		for (int iStage = 0; iStage < IstageGroups; iStage++) {
			dead += tau[age] * (VectorY[X(age, iStage)] + VectorY[H(age, iStage, MedNO)]
				+ VectorY[H(age, iStage, MedYES)]);
		}
		OutputY[D(age)] = dead;


		// Update the number of fully recovered immune people.
		OutputY[I(age)] = gamma[age][MedNO][ItypeA] * VectorY[A(age, IstageLast)]
			+ gamma[age][MedNO][ItypeM] * VectorY[M(age, IstageLast)] + rho * VectorY[R(age, RstageLast)];
		
		// Update the number of outpatient visits.
		for (int iStage = 0; iStage < IstageGroups; iStage++) {
			OutputY[Op(age)] = alpha  * (VectorY[V(age, iStage)] + VectorY[X(age, iStage)]);
			OutputY[Op(age)] = alphaW[age] * (VectorY[W(age, iStage, MedNO)] + VectorY[W(age, iStage, MedYES)]);
		}

		// Update the number of antiviral doses used.
		for (int iStage = 0; iStage < maxTreatmentStage[age]; iStage++) {
			OutputY[AV(age)] = alpha * (VectorY[V(age, iStage)] * todaySevereTreatFract + VectorY[X(age, iStage)] * todayExtremeTreatFract);
		}

		// Update the number of hospitalizations.
		for (int iStage = 0; iStage < maxTreatmentStage[age]; iStage++) {
			OutputY[Hospitalisation] += alpha
				* (1.0 - todayExtremeTreatFract + todayExtremeTreatFract * (1.0 - hospPrevTreat)) * VectorY[X(age, iStage)];
		}
		for (int iStage = maxTreatmentStage[age]; iStage < IstageGroups; iStage++) {
			OutputY[Hospitalisation] += alpha * VectorY[X(age, iStage)];
		}


		// Update the cumulative cases incidence and absenteeism prevalence due to influenza.
		double caseIncidence = 0.0;
		double recoveryIncidence = 0.0;
		caseIncidence += delta
			* (Courseofdisease[age][LowRisk][ItypeV] * VectorY[E(age, LowRisk, EstageLast)]
				+ Courseofdisease[age][HighRisk][ItypeV] * VectorY[E(age, HighRisk, EstageLast)]
				+ Courseofdisease[age][LowRisk][ItypeX] * VectorY[E(age, LowRisk, EstageLast)]
				+ Courseofdisease[age][HighRisk][ItypeX] * VectorY[E(age, HighRisk, EstageLast)]);
		recoveryIncidence += rho * VectorY[R(age, RstageLast)];
		//OutputY[CIC(age)] = caseIncidence;
		OutputY[AP(age)] = caseIncidence - recoveryIncidence - dead;

		//Update the cumulative absenteeism prevalence due to influenza.
		//OutputY[CPA(age)] = VectorY[AP(age)];
	

		int N95(int age);
		int Resp(int age);
		int AV(int age);
		int Spec(int age);

		////////
		double ventilation = 0.0;

		for (int age = 0; age < StageofAgeGroups; age++)
		{
			for (int iStage = 0; iStage < IstageGroups; iStage++)
			{
				ventilation += percentage(RespiratorNeedRate) * (VectorY[H(age, iStage, MedYES)] + VectorY[H(age, iStage, MedNO)]);
			}
		}

		////////
		double NumberofTest = 0.0;
		for (int age = 0; age < StageofAgeGroups; age++)
		{
			NumberofTest += (1 + percentage(ReinspectionRate)) * (VectorY[H(age, Istage1, MedYES)] + VectorY[H(age, Istage1, MedNO)])
				+ percentage(OutpatientSpecimenTesting) * (VectorY[W(age, Istage1, MedYES)] + VectorY[W(age, Istage1, MedNO)]);
		}

		//////
		double N95maskNeed = 0.0;
		for (int age = 0; age < StageofAgeGroups; age++)
		{
			for (int iStage = 0; iStage < IstageGroups; iStage++)
			{
				N95maskNeed += MaskNeedICU * (VectorY[H(age, iStage, MedYES)] + VectorY[H(age, iStage, MedNO)]);
			}
		}
		//////
	}
	//qDebug("eval: %f %f %f %f %f %f %f", time, OutputY[I(Age0to6)] * total, OutputY[I(Age7to12)] * total, OutputY[I(Age13to18)] * total,
		//OutputY[I(Age19to64)] * total, OutputY[I(Age65toEnd)] * total, OutputY[I(HCW)] * total);
	//qDebug("%f %f %f %f %f", time, OutputY[R(Age19to64, Rstage2)]*total*total*total, VectorY[R(Age19to64, Rstage1)]*total*total*total
	//	, VectorY[R(Age19to64, Rstage2)]*total*total*total,kk*total*total*total);
}
/*
void KfluStep()
{
	double day;
	double inputy[NumberofArray];
	double outputy[NumberofArray];

	std::fill_n(inputy, OutputArray, 0);
	std::fill_n(outputy, OutputArray, 0);

	Initialize();
	InitialY();

	Evaluation(0.0, InitY, outputy);
	for (int i = 0; i < OutputArray; i++)
		inputy[i] = outputy[i] * 0.1 + InitY[i];
	for (day = 0.1; day < 10; day = day + (1.0 / TimeResolution))
	{
		int dayk = int(day * 10);
		Evaluation(day, inputy, outputy);
		for (int i = 0; i < OutputArray; i++)
		{
			inputy[i] = outputy[i] * day + inputy[i];
		}
		if (1) {

			for (int age = 0; age < StageofAgeGroups; age++) {
				SusceptibleArray[dayk] += total*(InitY[S(age, LowRisk)] + InitY[S(age, HighRisk)]);
				for (int k = 0; k < EstageGroups; k++) {
					ExposedArray[dayk] += total*(InitY[E(age, LowRisk, k)] + InitY[E(age, HighRisk, k)]);
				}


				for (int k = 0; k < IstageGroups; k++) {
					AsymptomaticArray[dayk] += total*(InitY[A(age, k)]);
					ModerateArray[dayk] += total*(InitY[M(age, k)]);
					SevereArray[dayk] += total*(InitY[V(age, k)] + InitY[X(age, k)]);

					for (int m = 0; m < MedGroups; m++) {
						SevereArray[dayk] += total*(InitY[W(age, k, m)]);

						SevereArray[dayk] += total*(InitY[H(age, k, m)]);
						//qDebug("day:%f, age:%d, istage:%d, med:%d, icu:%d %f", day, age, k,m,c, gamma[age][m][k][c]);
					}
				}
				for (int i = 0; i < RstageGroups; i++) {
					RecoveryArray[dayk] += total*(InitY[R(age, i)]);
				}

				DeadArray[dayk] += total*(InitY[D(age)]);
				ImmuneArray[dayk] += total*(InitY[I(age)]);
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
			for (int i = 0; i < RstageGroups;i++)
				RecoveryArray[day] += InitY[R(GraphAge, i)];
		}
	}
}*/

/*
void ArrayforPlot(double m)
{
	int day_t = round(m*10);
	
	for (int age = 0; age < StageofAgeGroups; age++)
	{
		PlotSusceptibles[age][day_t] = OutputY[S(age, LowRisk)] + OutputY[S(age, HighRisk)];
		for (int k = 0; k < EstageGroups; k++)
			PlotExposed[age][day_t] += OutputY[E(age, LowRisk, k)] + OutputY[E(age, HighRisk, k)];
		for (int k = 0; k < IstageGroups; k++) {
			PlotAsymptomatic[age][day_t] += OutputY[A(age, k)];
			PlotModerate[age][day_t] += OutputY[M(age, k)];
			//PlotSevere[age][day_t] += OutputY[S(age, k)];
		}
		PlotDead[age][day_t] = OutputY[D(age)];
		PlotImmune[age][day_t] = OutputY[I(age)];
	}
}*/