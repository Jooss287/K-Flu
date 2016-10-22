#pragma once

#include <Eigen/Dense>

//**********************************************
//System Define
//==============================================
#define Maximumday 200
#define TimeResolution 10
#define NumberofArray Maximumday*TimeResolution
//**********************************************
//Define Value 목록
//==============================================
//연령별 분포
#define Age0to6 0
#define Age7to12 1
#define Age13to18 2
#define Age19to64 3
#define Age65toEnd 4
#define HCW 5
//#define AgeTotal 5	//ContactMatrix 합계 Part
#define StageofAgeGroups 6
#define StageofAgeWithoutHCW 5
#define ChildClass 3

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

//질병단계 E, I, R
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

//BinarySearch 함수 input data로 사용
#define typeR0 0
#define typeF50 1
#define typeDeadFraction 2

#define MedNO 0
#define MedYES 1
#define MedGroups 2

#define IsoNO 0
#define IsoYES 1
#define IsoGroups 2

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
//Ouput 관련 Define
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
//아직 미파악 리스트
#define APsize StageofAgeGroups
#define CAPsize StageofAgeGroups
#define CCIsize StageofAgeGroups
//추가 리스트
#define OutpatientsSize StageofAgeGroups

//ouput array list
#define Soffset 0
#define Eoffset (Soffset + Ssize)
#define Aoffset (Eoffset + Esize)
#define Moffset (Aoffset + Asize)
#define Voffset (Moffset + Msize)
#define Woffset (Voffset + Vsize)
#define Xoffset (Woffset + Wsize)
#define Hoffset (Xoffset + Xsize)
#define Roffset (Hoffset + Hsize)
#define Doffset (Roffset + Rsize)
#define Ioffset (Doffset + Dsize)

#define APoffset (Ioffset + Isize)
#define CAPoffset (APoffset + APsize)
#define CCIoffset (CAPoffset + CAPsize)

#define Outpatients (CCIoffset + CCIsize)
#define Antivirals (Outpatients + OutpatientsSize)
#define Hospitalisation (Antivirals + 1)

// 감염자 TAB : Susceptibles, exposed, asymptomatic, moderate, severe, dead, immune
// 의료자원 TAB : N-95mask, respirator,  Antivirals
// 검체수 TAB : Specimen
// 일일 TAB : outpatients, HospitalICU, HospitalNICU
// 누적 TAB : outpatients, HospitalICU, HospitalNICU
#define InfectedC (Hospitalisation + 1)
#define CasesC (InfectedC + 1)
#define HCWWorkReduction (CasesC + 1)
#define HCWReturnAntivirals (HCWWorkReduction + 1)
#define OutputArray (HCWReturnAntivirals + 1)


//**********************************************
//Define Function 목록
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


void InitialY();
void Initialize();
void EvaluationY(double day);
void KfluStep();
void ArrayforPlot(double day);

//**********************************************
//Input 화면 탭 입력변수 목록
//==============================================
//--인구
double Population[StageofAgeGroups] = { 5272, 6773, 7952, 55086, 29127, 0 };	//0to6, 7to12, 13to18, 19to64, 65toEnd, HCW
double ContactMatrix[StageofAgeWithoutHCW][StageofAgeWithoutHCW] =
{	{ 169.14,	31.47,	17.76,	34.50,	11.47	},
	{ 0,		274.51,	32.31,	34.86,	11.5	},
	{ 0,		0,		224.25,	50.75,	14.96	},
	{ 0,		0,		0,		75.66,	25.08	},
	{ 0,		0,		0,		0,		54.23	} };
double SchoolContactRate[ChildClass] = { 80.0, 70.0, 50.0 };		/*percentage 함수 필요*/
//결석으로 어른과 접촉이 강화되는 정도
double AbsenceContactRatio[ChildClass] = { 75.0, 50.0, 25.0 };

//--질병 TAB
double LatentPeriod = 1.9;
double InfectiousDuration[StageofSevere][StageofWorkAge] = { { 7.0, 4.1, 4.1 },{ 7.0, 7.0, 7.0 } };

double ReturntoWorkPeriod = 5.0;
double SevereRate = 33.3;		/*percentage 함수 필요*/
double MildRate = 50.0;		/*percentage 함수 필요*/
double HighRiskRate[StageofWorkAge] = { 6.0, 14.0, 47.0 };		/*percentage 함수 필요*/
double LowRiskHospitalRate[StageofWorkAge] = { 0.187, 14.0, 47.0 };		/*percentage 함수 필요*/
double HighRiskHospitalRate[StageofWorkAge] = { 1.333, 2.762, 7.768 };		/*percentage 함수 필요*/
double DeadRate[StageofWorkAge] = { 5.541, 16.541, 39.505 };		/*percentage 함수 필요*/

//--전염성 TAB
//기초 감염 재 생산수
double R0 = 2.5;
//총 감염 가능 기간 중 절반 기간 동안 갖는 전염성 비율
double HalfInfectiousRate = 90.0;		/*percentage 함수 필요*/
//중증도가 높은 경우와 비교 했을 때 상대적 전염성
double LastLatentPeriodCase = 50.0;		/*percentage 함수 필요*/
double AsymptomaticCase = 50.0;		/*percentage 함수 필요*/
double ModerateCase = 100.0;		/*percentage 함수 필요*/
//부분 격리
double ModerateCaseIsolation = 50.0;		/*percentage 함수 필요*/
double SevereHomeCaseIsolation = 50.0;		/*percentage 함수 필요*/
double SevereHospitalCaseIsolation = 100.0;		/*percentage 함수 필요*/
unsigned int RangeofIsolationBegin = 0;
unsigned int RangeofIsolationEnd = 200;

//--치료 TAB
//항바이러스제 투여 가능 비율
double AntiviralsInjectionRate = 100.0;		/*percentage 함수 필요*/
//의료서비스 이용가능 시간
double MedicalHelp = 24.0;			//consultationDelay day로 환산
double AntiviralsHelp = 48.0;		//maxTreatmentDelay day로 환산
//Very Sick Case 치료
double VerySickTreatRate = 0;		/*percentage 함수 필요*/
unsigned int  VerySickTreatRangeBegin = 0;
unsigned int  VerySickTreatRangeEnd = 200;
//Extremely Sick Case 치료
double ExtremelySickTreatRate = 0;		/*percentage 함수 필요*/
unsigned int  ExtremelySickTreatRangeBegin = 0;
unsigned int  ExtremelySickTreatRangeEnd = 200;
//치료 효과
double ContagiousnessReduction = 80.0;		/*percentage 함수 필요*/
double DiseaseDurationReduction = 25.0;		/*percentage 함수 필요*/
double HospitalizationReduction = 50.0;		/*percentage 함수 필요*/

//--격리 TAB
//일반접촉 감소 비율 및 기간
double ContactReductionRate = 0.0;		/*percentage 함수 필요*/
unsigned int  ContactReductionRangeBegin = 0;
unsigned int  ContactReductionRangeEnd = 200;
//휴교 및 그에 따른 접촉 수준 변동
unsigned int  SchoolCloseRangeBegin = 0;
unsigned int  SchoolCloseRangeEnd = 200;
double SchoolCloseContactRatio[ChildClass] = { 75.0, 50.0, 25.0 };
//대중집회 취소 및 그에 따른 접촉 수준 변동
double GatheringCancelReductionRate = 0.0;		/*percentage 함수 필요*/
unsigned int  GatheringCancleRangeBegin = 0;
unsigned int  GatheringCancleRangeEnd = 200;

//--입원 TAB
//평균 재원기간
double HospitalizationNICU = 5.0;
double HospitalizationICU = 10.0;

//--백신 TAB
//연령별 백신 접종률
double VaccineAgeRate[StageofAgeGroups] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
//연령별 백신 접종효과
double VaccineEffectAgeRate[StageofAgeGroups] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
//항체생성기간
double AntibodyCreateRange = 14;
//백신 접종 시기
double VaccineStart = 200;

//--자원 TAB
//N-95마스크(1명, 1일당 개수)
double MaskNeedNICU = 1;
double MaskNeedICU = 2;
//인공호흡기 (입원환자 중 인공호흡기 사용 비율)
double RespiratorNeedRate = 50.0;		/*percentage 함수 필요*/

//--검체 TAB
//검체 재검율
double ReinspectionRate = 10.0;		/*percentage 함수 필요*/
//외래환자 검체비율
double OutpatientSpecimenTesting = 50.0;		/*percentage 함수 필요*/

//**********************************************
//방정식 계산 시 필요 변수 목록
//==============================================
//Number of prodromal stages
int prodromalStages = 2;

//Initialize the contagiousness of cases (by course of disease).
//infFact(Influsim)
double contagiousness[ItypeGroups]; 

//Rate at which severe and extremely severe cases seek medical help.
double alpha;
//Rate at which severe cases at home again seek medical help.
double alphaW[StageofAgeGroups];

//beta, ebeta
double eBeta[StageofAgeGroups][StageofAgeGroups];
/*medgroups yes no, ITypegroups 6, ISOGroups yes no.*/
double beta[StageofAgeGroups][StageofAgeGroups][MedGroups][ItypeGroups][IsoGroups]; 

unsigned int healthCareWorkers = 375;
double total;
// Initial fraction of newly infected individuals.
double initialExposed;
double ageDistribution[StageofAgeGroups];

unsigned int ageClass[StageofAgeGroups] = { Child, Child, Child, Worker, Elderly, Worker }; // 0, 0, 0, 1, 2, 1(HCW)

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
double consultationDelay = 1.0;

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
double immuneFract[StageofAgeGroups] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

double OutputY[OutputArray];
double CumulateOutput[OutputArray];


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
	}
	double ComputeR0(double b)
	{
		for (int ageSus = 0; ageSus < StageofAgeGroups; ageSus++) {
			for (int ageInf = 0; ageInf < StageofAgeGroups; ageInf++) {
				eBeta[ageSus][ageInf] = LastLatentPeriodCase * b * ContactMatrix[ageSus][ageInf];   // eBeta. LastLatentPeriodCase = eInfFact

				for (int type = ItypeA; type <= ItypeM; type++) { // type A, M
					beta[ageSus][ageInf][MedNO][type][IsoNO] = contagiousness[type] * b * ContactMatrix[ageSus][ageInf];  // Contact Matrix를 ageMatrix로 바꿔야하나? fill matrix 함수
				}
			}
		}

		//Severly ill children do not go to school      beta에서 예외부분 처리. 학교다니는 나이대
		for (int type = ItypeV; type <= ItypeH; type++)  // type V, W, X, H
		{
			for (int ageSus = Age0to6; ageSus <= Age13to18; ageSus++) {
				for (int ageInf = Age0to6; ageInf <= Age13to18; ageInf++) {
					if (ageSus == ageInf) {
						beta[ageSus][ageInf][MedNO][type][IsoNO] = contagiousness[type] * b * ContactMatrix[ageSus][ageInf] * (1.0 - SchoolContactRate[ageSus]); // 결석으로 인해 학교 나이대 서로서로 접촉 X
					}
					else {
						beta[ageSus][ageInf][MedNO][type][IsoNO] = contagiousness[type] * b * ContactMatrix[ageSus][ageInf]; // 그 외에 영향 없도록
					}
				}
			}
			for (int ageSus = Age19to64; ageSus <= HCW; ageSus++) { // 결석한 학생들이 care받으면서 생기는 전염성. 대상은 학생나이대 이후 전부, HCW포함
				for (int ageInf = Age0to6; ageInf <= Age13to18; ageInf++) {
					beta[ageSus][ageInf][MedNO][type][IsoNO] = contagiousness[type] * b * ContactMatrix[ageSus][ageInf] * redistributionFactorChildHealthCare[ageInf];
				}
			}

			//all other contacts remain untouched
			for (int ageSus = Age0to6; ageSus < StageofAgeGroups; ageSus++) {
				for (int ageInf = Age19to64; ageInf < StageofAgeGroups; ageInf++) {
					beta[ageSus][ageInf][MedNO][type][IsoNO] = contagiousness[type] * b * ContactMatrix[ageSus][ageInf];
				}
			}
		}

		for (int ageSus = 0; ageSus < StageofAgeGroups; ageSus++) { // Med Yes의 경우
			for (int ageInf = 0; ageInf < StageofAgeGroups; ageInf++) {
				for (int type = ItypeA; type < ItypeGroups; type++) {
					beta[ageSus][ageInf][MedYES][type][IsoNO] = beta[ageSus][ageInf][MedNO][type][IsoNO] * (1.0 - ContagiousnessReduction);
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
		

		Eigen::MatrixXd Ematirx(7, 7);
		Eigen::MatrixXd realEigenvalues;
		Eigen::MatrixXd imagEigenvalues;
		Eigen::MatrixXd getEigenvector;

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
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
		return maxEigenvalue - 2.5;

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

		return 0;//halfInfectiosity - (halfStagesInfectiosity / allStagesInfectiosity);
	}
private:
	double find(double a, double b, int type) {
		double c = 0.5 * (a + b);
		double cval;
		
		if (b - a <= 1.8e-15)
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
	return Hoffset + (age * IstageGroups + iStage) * MedGroups + med;
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

int AP(int age) {
	return APoffset + age;
}

int CPA(int age) {
	return CAPoffset + age;
}

int CIC(int age) {
	return CCIoffset + age;
}
/*Initialize function*/
void Initialize()
{
	Individuals[Age0to6] = Population[Age0to6];
	Individuals[Age7to12] = Population[Age7to12];
	Individuals[Age13to18] = Population[Age13to18];
	Individuals[Age19to64] = Population[Age19to64] - healthCareWorkers;
	Individuals[Age65toEnd] = Population[Age65toEnd];
	Individuals[HCW] = healthCareWorkers;


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
	//agematirx는 contactmatrix와 동일한 구조
	for (int i = 0; i < StageofAgeWithoutHCW; i++)
	{
		for (int j = 0; j < StageofAgeWithoutHCW; j++)
		{
			ageMatrix[i][j] = ContactMatrix[i][j];
		}
	}

	for (int i = 0; i < StageofAgeGroups; i++)
	{
		ageMatrix[i][HCW] = ageMatrix[i][Age19to64];
		ageMatrix[HCW][i] = ageMatrix[Age19to64][i];
	}


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

	//Initialize the average duration of the infectious periods by age, medication and course of disease // 연령별 잠복기 이후 평균 감염 가능 기간
	for (int age = 0; age < StageofAgeGroups; age++) {
		infDur[age][MedNO][ItypeA] = infDurMild[ageClass[age]];
		infDur[age][MedNO][ItypeM] = infDurMild[ageClass[age]];
		infDur[age][MedNO][ItypeV] = infDurSevere[ageClass[age]];
		infDur[age][MedNO][ItypeW] = infDurSevere[ageClass[age]];
		infDur[age][MedNO][ItypeX] = infDurSevere[ageClass[age]];
		infDur[age][MedNO][ItypeH] = infDurSevere[ageClass[age]];
		for (int type = 0; type < ItypeGroups; type++)
		{
			infDur[age][MedYES][type] = (1.0 - percentage(DiseaseDurationReduction)) * infDur[age][MedNO][type];
		}
	}

	//Initialize the fractions for asymptomatic, moderate and severe cases  // 무증상자와 증상자 중 심한 사람들의 비율
	symptomaticFraction = 1.0 - percentage(SevereRate); // 입력받는 값이 무증상자 비율이기 때문에 증상자 비율 = 1.0 - 무증상자 비율로 수정
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
	contagiousness[ItypeA] = percentage(AsymptomaticCase);
	contagiousness[ItypeM] = percentage(ModerateCase);
	contagiousness[ItypeV] = 1.0;
	contagiousness[ItypeW] = 1.0;
	contagiousness[ItypeX] = 1.0;
	contagiousness[ItypeH] = 1.0;

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
			Courseofdisease[age][risk][ItypeA] = symptomaticFraction;
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
				gamma[age][med][type] = ItypeGroups / infDur[age][med][type]; // potential division by zero!
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
		Root.gam = gamma[age][MedNO][ItypeH];
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
	std::fill_n(OutputY, OutputArray, 0);

	for (int age = 0; age < StageofAgeGroups; age++) {
		for (int risk = 0; risk < StageofRisk; risk++) {
			if (age == HCW) {
				OutputY[S(age, risk)] = Susceptibles[age][risk] * (1.0 - immuneFract[Age19to64]);
				OutputY[I(age)] += Susceptibles[age][risk] * immuneFract[Age19to64];
			}
			else {
				OutputY[S(age, risk)] = Susceptibles[age][risk] * (1.0 - immuneFract[age]);
				OutputY[I(age)] += Susceptibles[age][risk] * immuneFract[age];
			}
		}
	}
	for (int age = 0; age < StageofAgeGroups; age++) {
		double exposedLowRisk = (1.0 - HighRiskRate[ageClass[age]]) * eigenvector[age] / total; // potential division by zero!
		OutputY[S(age, LowRisk)] -= exposedLowRisk;
		OutputY[E(age, LowRisk, Estage1)] = exposedLowRisk;
		double exposedHighRisk = HighRiskRate[ageClass[age]] * eigenvector[age] / total; // potential division by zero!
		OutputY[S(age, HighRisk)] -= exposedHighRisk;
		OutputY[E(age, HighRisk, Estage1)] = exposedHighRisk;
	}

	/*누적 데이터 초기값 설정*/
	for (int i = 0; i < OutputArray; i++)
		CumulateOutput[i] = OutputY[i];
}

/////////////////////////////////////////////////////====================================================================================================
/////////////////////////////////////////////////////====================================================================================================

//Daily fraction of treatment dose during antiviral prophylaxis.
double zeta = 0.1;

//Contact shift of flu patients to HCW [%].
double hcwContactFraction = 0.9;

//First day of health care worker prophylaxis.
double hcwProphylaxisBegin = 0.0;

//Day at which health care worker prophylaxis is terminated.
double hcwProphylaxisEnd = 0.0;

//Fraction of the population for which antiviral treatment is available.
double antiviralRessource = 1.0;

//Treshold above which school closing is applied.
double schoolClosingTreshold = 1.0;

//Number of non-flu patients.
double nonFluPatients = 500;

//Fraction of non-flu patients sent home.
double sentHomeFraction = 0.0;

//Reduction of susceptibility by antiviral prophylactic treatement.
double treatEfficacySusceptiblilty = 0.5;

void EvaluationY(double time)
{
	// Initialize counters. 
	
	// 감염자 TAB : Susceptibles, exposed, asymptomatic, moderate, severe, dead, immune
	// 의료자원 TAB : N-95mask, respirator,  Antivirals
	// 검체수 TAB : 
	// 일일 TAB : outpatients, HospitalICU, HospitalNICU
	// 누적 TAB : outpatients, HospitalICU, HospitalNICU
	OutputY[Outpatients] = 0.0;
	OutputY[Antivirals] = 0.0;
	OutputY[Hospitalisation] = 0.0;
	OutputY[HCWReturnAntivirals] = 0.0;



	bool doProphylaxis = false;
	if ((time >= hcwProphylaxisBegin) && (time<hcwProphylaxisEnd)) {
		if (antiviralRessource>CumulateOutput[Antivirals]) {
			doProphylaxis = true;
			OutputY[Antivirals] += zeta * (healthCareWorkers / total - CumulateOutput[D(HCW)] - CumulateOutput[HCWReturnAntivirals]);
		}
	}
	
	if (SchoolCloseRangeBegin == SchoolCloseRangeEnd) {
		if (CumulateOutput[AP(Age0to6)] * total / Individuals[Age0to6] > schoolClosingTreshold)
			doSchoolClosure0to6[(int)ceil(time)] = true;
		if (CumulateOutput[AP(Age7to12)] * total / Individuals[Age7to12] > schoolClosingTreshold)
			doSchoolClosure7to12[(int)ceil(time)] = true;
		if (CumulateOutput[AP(Age13to18)] * total / Individuals[Age13to18] > schoolClosingTreshold)
			doSchoolClosure13to18[(int)ceil(time)] = true;
	}

	bool doSchoolClosing0to6 = doSchoolClosure0to6[(int)floor(time)];
	bool doSchoolClosing6to12 = doSchoolClosure7to12[(int)floor(time)];
	bool doSchoolClosing13to19 = doSchoolClosure13to18[(int)floor(time)];

	// Calculate the current force of infection.
	lambda[HCW] = 0.0;
	for (int ageSus = 0; ageSus < StageofAgeGroups; ageSus++) {
		if (ageSus<HCW) lambda[ageSus] = 0.0;
		for (int ageInf = 0; ageInf < StageofAgeGroups; ageInf++) {

			double cancellingFactor = 1.0;
			double infChildCareFactor = 1.0;
			double susChildCareFactor = 1.0;
			int isolation = ((time >= RangeofIsolationBegin) && (time < RangeofIsolationEnd)) ? IsoYES : IsoNO;
			if ((ageSus <= Age13to18) && (ageInf <= Age13to18)) {/*학교 휴교에 따른 영향*/
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
			else if ((ageSus >= Age19to64) && (ageInf >= Age19to64)) {/*대중집회에 따른 영향*/
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
				generalFactor *= (1.0 - ContactReductionRate);
			double temp = 0.0;
			double tempHCW = 0.0;
			for (int eStage = EstageGroups - prodromalStages; eStage < EstageGroups; eStage++) {
				temp += (CumulateOutput[E(ageInf, LowRisk, eStage)] + CumulateOutput[E(ageInf, HighRisk, eStage)])  * eBeta[ageSus][ageInf] * cancellingFactor * susChildCareFactor * infChildCareFactor;
			}

			for (int iStage = 0; iStage < IstageGroups; iStage++) {
				temp += (CumulateOutput[A(ageInf, iStage)] * beta[ageSus][ageInf][MedNO][ItypeA][isolation] * cancellingFactor * susChildCareFactor * infChildCareFactor
					+ CumulateOutput[M(ageInf, iStage)] * beta[ageSus][ageInf][MedNO][ItypeM][isolation] * cancellingFactor * susChildCareFactor * infChildCareFactor
					+ CumulateOutput[V(ageInf, iStage)] * beta[ageSus][ageInf][MedNO][ItypeV][isolation] * susChildCareFactor
					+ CumulateOutput[X(ageInf, iStage)] * beta[ageSus][ageInf][MedNO][ItypeX][isolation] * susChildCareFactor
					+ CumulateOutput[W(ageInf, iStage, MedNO)] * beta[ageSus][ageInf][MedNO][ItypeW][isolation] * susChildCareFactor
					+ CumulateOutput[W(ageInf, iStage, MedYES)] * beta[ageSus][ageInf][MedYES][ItypeW][isolation] * susChildCareFactor
					+ (CumulateOutput[H(ageInf, iStage, MedNO)] * beta[ageSus][ageInf][MedNO][ItypeH][isolation] * susChildCareFactor
						+ CumulateOutput[H(ageInf, iStage, MedYES)] * beta[ageSus][ageInf][MedYES][ItypeH][isolation] * susChildCareFactor) * (1.0 - hcwContactFraction)) * contagiousness[iStage];

				tempHCW += (CumulateOutput[A(ageInf, iStage)] * beta[ageSus][ageInf][MedNO][ItypeA][isolation]
					+ CumulateOutput[M(ageInf, iStage)] * beta[ageSus][ageInf][MedNO][ItypeM][isolation]
					+ CumulateOutput[V(ageInf, iStage)] * beta[ageSus][ageInf][MedNO][ItypeV][isolation]
					+ CumulateOutput[X(ageInf, iStage)] * beta[ageSus][ageInf][MedNO][ItypeX][isolation]
					+ CumulateOutput[W(ageInf, iStage, MedNO)] * beta[ageSus][ageInf][MedNO][ItypeW][isolation]
					+ CumulateOutput[W(ageInf, iStage, MedYES)] * beta[ageSus][ageInf][MedYES][ItypeW][isolation])
					* Individuals[ageInf] * hcwContactFraction * contagiousness[iStage] * (nonFluPatients / total) * (1.0 - sentHomeFraction) / healthCareWorkers;

				tempHCW += (CumulateOutput[H(ageInf, iStage, MedNO)] * beta[ageSus][ageInf][MedNO][ItypeH][isolation]
					+ CumulateOutput[H(ageInf, iStage, MedYES)] * beta[ageSus][ageInf][MedYES][ItypeH][isolation])
					* Individuals[ageInf] * hcwContactFraction * contagiousness[iStage] / healthCareWorkers;
			}
			lambda[HCW] += tempHCW * generalFactor;
			lambda[ageSus] += temp * generalFactor;
		}
	}

	if (doProphylaxis) {
		lambda[HCW] *= (1.0 - treatEfficacySusceptiblilty);
	}

	// Calculate what fraction of severe cases are treated.
	double todaySevereTreatFract = 0.0;
	if ((time >= VerySickTreatRangeBegin) && (time<VerySickTreatRangeEnd)) {
		todaySevereTreatFract = percentage(VerySickTreatRate);
		if (antiviralRessource <= CumulateOutput[Antivirals]) todaySevereTreatFract = 0.0;
	}

	// Calculate what fraction of extremely severe cases are treated.
	double todayExtremeTreatFract = 0.0;
	if ((time >= ExtremelySickTreatRangeBegin) && (time<ExtremelySickTreatRangeEnd)) {
		todayExtremeTreatFract = percentage(ExtremelySickTreatRate);
		if (antiviralRessource <= CumulateOutput[Antivirals]) todayExtremeTreatFract = 0.0;
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
			Vaccine = ImmunebyVaccine * VaccineAgeRate[age] / AntibodyCreateRange * VaccineEffectAgeRate[age];
			OutputY[S(age, risk)] = -lambda[age] * (1 - Vaccine) * CumulateOutput[S(age, risk)] - Vaccine * CumulateOutput[S(age, risk)];
		}
	}
	/*
	for (int age = 0; age < StageofAgeGroups; age++) {
		for (int risk = 0; risk < StageofRisk; risk++) {
			for (int k = 0; k < EstageGroups; k++) {
				if (k == Estage1)
					OutputY[E(age, risk, k)] = lambda[age] * (1 - Vaccine) * CumulateOutput[S(age, risk)] - delta * CumulateOutput[E(age, risk, Estage1)];
				OutputY[E(age, risk, k)] = delta * (CumulateOutput[E(age, risk, k - 1)] - CumulateOutput[E(age, risk, k)]);
			}

			// Some of the individuals who have just passed through 
			// the incubation period become asymptomatic cases now.
			OutputY[A(age, Istage1)]
				= delta * (Courseofdisease[age][LowRisk][ItypeA] * CumulateOutput[E(age, LowRisk, EstageLast)]
					+ Courseofdisease[age][HighRisk][ItypeA] * CumulateOutput[E(age, HighRisk, EstageLast)])
				- gamma[age][MedNO][ItypeA] * CumulateOutput[A(age, Istage1)];
			// Some of the individuals who have just passed through 
			// the incubation period become moderately sick cases now.
			double mCases = delta * (Courseofdisease[age][LowRisk][ItypeM] * CumulateOutput[E(age, LowRisk, EstageLast)]
				+ Courseofdisease[age][HighRisk][ItypeM] * CumulateOutput[E(age, HighRisk, EstageLast)]);
			OutputY[M(age, Istage1)] = mCases - gamma[age][MedNO][ItypeM] * CumulateOutput[M(age, Istage1)];
			// Some of the individuals who have just passed through 
			// the incubation period become severe cases now.
			double vCases = delta * (Courseofdisease[age][LowRisk][ItypeV] * CumulateOutput[E(age, LowRisk, EstageLast)]
				+ Courseofdisease[age][HighRisk][ItypeV] * CumulateOutput[E(age, HighRisk, EstageLast)]);
			OutputY[V(age, Istage1)] = vCases - (gamma[age][MedNO][ItypeV] + alpha) * CumulateOutput[V(age, Istage1)];
			// Some of the individuals who have just passed through 
			// the incubation period become extremely severe cases now.
			double xCases = delta * (Courseofdisease[age][LowRisk][ItypeX] * CumulateOutput[E(age, LowRisk, EstageLast)]
				+ Courseofdisease[age][HighRisk][ItypeX] * CumulateOutput[E(age, HighRisk, EstageLast)]);
			OutputY[X(age, Istage1)] = xCases - (gamma[age][MedNO][ItypeX] + (alpha + tau[age])) * CumulateOutput[X(age, Istage1)];
			// Some severe cases in contagiousness stage 1 have received treatment.
			// Some extremely severe cases in contagiousness stage 1 whose 
			// hospitalization could be avoided through antiviral treatment, join this group.
			OutputY[W(age, Istage1, MedYES)]
				= alpha * (CumulateOutput[V(age, Istage1)] * todaySevereTreatFract + hospPrevTreat * CumulateOutput[X(age, Istage1)] * todayExtremeTreatFract)
				- gamma[age][MedYES][ItypeW] * CumulateOutput[W(age, Istage1, MedYES)];
			// Some extremely severe cases in contagiousness stage 1 have received 
			// treatment and are hospitalized (hospitalization could not be prevented).
			OutputY[H(age, Istage1, MedYES)]
				= alpha * todayExtremeTreatFract * (1.0 - hospPrevTreat) * CumulateOutput[X(age, Istage1)]
				- (gamma[age][MedYES][ItypeW] + tau[age]) * CumulateOutput[H(age, Istage1, MedYES)];
			// Some severe cases in contagiousness stage 1 have seen the doctor 
			// but have not received treatment.
			OutputY[W(age, Istage1, MedNO)]
				= alpha * (1.0 - todaySevereTreatFract) * CumulateOutput[V(age, Istage1)] - gamma[age][MedNO][ItypeW] * CumulateOutput[W(age, Istage1, MedNO)];
			// Some extremely severe cases in contagiousness stage 1 have seen 
			// the doctor and have been hospitalized, but have not received treatment.
			OutputY[H(age, Istage1, MedNO)]
				= alpha * (1.0 - todayExtremeTreatFract) * CumulateOutput[X(age, Istage1)] - (gamma[age][MedNO][ItypeH] + tau[age]) * CumulateOutput[H(age, Istage1, MedNO)];

			for (int iStage = Istage2; iStage < IstageGroups; iStage++) {
				int previousStage = iStage - 1;
				// Progress through the contagious period for asymptomatic cases.
				OutputY[A(age, iStage)]
					= gamma[age][MedNO][ItypeA] * (CumulateOutput[A(age, previousStage)] - CumulateOutput[A(age, iStage)]);
				// Progress through the contagious period for moderately sick cases.
				OutputY[M(age, iStage)]
					= gamma[age][MedNO][ItypeM] * (CumulateOutput[M(age, previousStage)] - CumulateOutput[M(age, iStage)]);
				// Progress through the contagious period for severe cases 
				// (some seek medical help and possibly obtain treatment).
				OutputY[V(age, iStage)]
					= gamma[age][MedNO][ItypeV] * (CumulateOutput[V(age, previousStage)] - CumulateOutput[V(age, iStage)])
					- alpha * CumulateOutput[V(age, iStage)];
				// Progress through the contagious period for extremely severe cases 
				// (some seek medical help, may be hospitalized and/or obtain antiviral treatment).
				OutputY[X(age, iStage)]
					= gamma[age][MedNO][ItypeX] * (CumulateOutput[X(age, previousStage)] - CumulateOutput[X(age, iStage)]) - (alpha + tau[age])  * CumulateOutput[X(age, iStage)];
				if (iStage + 1 < maxTreatmentStage[age]) {
					// Some severe cases have just been treated, others simply progress 
					// in their contagious period. Some newly treated extremely severe 
					// cases whose hospitalization could be prevented by treatment, join this group.
					OutputY[W(age, iStage, MedYES)]
						= gamma[age][MedYES][ItypeW] * (CumulateOutput[W(age, previousStage, MedYES)]
							- CumulateOutput[W(age, iStage, MedYES)]) + alpha * (CumulateOutput[V(age, iStage)] * todaySevereTreatFract
								+ hospPrevTreat * CumulateOutput[X(age, iStage)] * todayExtremeTreatFract);
					// Some new severe cases have just seen the doctor without receiving 
					// antiviral treatment, others simply progress in their contagious period.
					OutputY[W(age, iStage, MedNO)]
						= gamma[age][MedNO][ItypeW] * (CumulateOutput[W(age, previousStage, MedNO)]
							- CumulateOutput[W(age, iStage, MedNO)]) + alpha * (1.0 - todaySevereTreatFract) * CumulateOutput[V(age, iStage)];
					// Some new extremely severe cases have just been treated and 
					// hospitalized, other hospitalized casess simply progress in their 
					// contagious period.
					OutputY[H(age, iStage, MedYES)]
						= gamma[age][MedYES][ItypeH] * (CumulateOutput[H(age, previousStage, MedYES)]
							- CumulateOutput[H(age, iStage, MedYES)]) + (1.0 - hospPrevTreat) * todayExtremeTreatFract * alpha * CumulateOutput[X(age, iStage)]
						- tau[age] * CumulateOutput[H(age, iStage, MedYES)];
					// Some new extremely severe cases have just been hospitalized 
					// without receiving antiviral treatment; other hospitalized cases 
					// simply progress in their contagious period.
					OutputY[H(age, iStage, MedNO)]
						= gamma[age][MedNO][ItypeH] * (CumulateOutput[H(age, previousStage, MedNO)]
							- CumulateOutput[H(age, iStage, MedNO)]) + (1.0 - todayExtremeTreatFract) * alpha * CumulateOutput[X(age, iStage)]
						- tau[age] * CumulateOutput[H(age, iStage, MedNO)];
				}
				else {
					// Formerly treated severe cases progress in their contagious period.
					OutputY[W(age, iStage, MedYES)]
						= gamma[age][MedYES][ItypeW] * (CumulateOutput[W(age, previousStage, MedYES)]
							- CumulateOutput[W(age, iStage, MedYES)]);
					// Some new severe cases have just seen the doctor without receiving 
					// antiviral treatment, others simply progress in their contagious period.
					OutputY[W(age, iStage, MedNO)]
						= gamma[age][MedNO][ItypeW] * (CumulateOutput[W(age, previousStage, MedNO)]
							- CumulateOutput[W(age, iStage, MedNO)]) + alpha * CumulateOutput[V(age, iStage)];
					// Formerly treated hospitalized cases progress in their contagious period.
					OutputY[H(age, iStage, MedYES)]
						= gamma[age][MedYES][ItypeH] * (CumulateOutput[H(age, previousStage, MedYES)]
							- CumulateOutput[H(age, iStage, MedYES)]) - tau[age] * CumulateOutput[H(age, iStage, MedYES)];
					// Some new extremely severe cases have just seen the doctor and 
					// have been hospitalized without receiving antiviral treatment, other 
					// formerly untreated hospitalized cases simply progress in their contagious period.
					OutputY[H(age, iStage, MedNO)]
						= gamma[age][MedNO][ItypeH] * (CumulateOutput[H(age, previousStage, MedNO)]
							- CumulateOutput[H(age, iStage, MedNO)]) + alpha * CumulateOutput[X(age, iStage)] - tau[age] * CumulateOutput[H(age, iStage, MedNO)];
				}
			}
		}
	}


	for (int age = 0; age < StageofAgeGroups; age++) {
		out[R(age, Rstage1)] = 0.0;
		for (int rStage = Rstage2; rStage < RstageGroups; rStage++) {
			out[R(age, rStage)] = 0.0;
		}
		out[D(age)] = 0.0;
		out[I(age)] = 0.0;

		// All severe and extremely severe cases have to go through a period
		// of reconvalcescence after passing through their contagious period.
		out[R(age, Rstage1)]
			+= gamma(age, MedNO, ItypeV) 	* y[V(age, IstageLast)]
			+ gamma(age, MedNO, ItypeX) 	* y[X(age, IstageLast)]
			+ gamma(age, MedNO, ItypeW) 	* y[W(age, IstageLast, MedNO)]
			+ gamma(age, MedNO, ItypeH)	* y[H(age, IstageLast, MedNO)]
			+ gamma(age, MedYES, ItypeW)	* y[W(age, IstageLast, MedYES)]
			+ gamma(age, MedYES, ItypeH)	* y[H(age, IstageLast, MedYES)]
			- rho * y[R(age, Rstage1)];
		if (age == HCW) {
			out[HCWReturnAntivirals]
				+= gamma(HCW, MedNO, ItypeV)  * y[V(HCW, IstageLast)]
				+ gamma(HCW, MedNO, ItypeW) 	* y[W(HCW, IstageLast, MedNO)]
				+ gamma(HCW, MedNO, ItypeX) 	* y[X(HCW, IstageLast)]
				+ gamma(HCW, MedNO, ItypeH)    * y[H(HCW, IstageLast, MedNO)];
		}

		// Progress during the reconvalescent period.
		for (int rStage = Rstage2; rStage < RstageGroups; rStage++) {
			out[R(age, rStage)] += rho * (y[R(age, rStage - 1)] - y[R(age, rStage)]);
		}

		// Update the number of cases who died.
		double dead = 0;
		for (int iStage = 0; iStage < IstageGroups; iStage++) {
			dead += tau(age) * (y[X(age, iStage)] + y[H(age, iStage, MedNO)] + y[H(age, iStage, MedYES)]);
			if (age == HCW) {
				out[HCWReturnAntivirals] -= tau(HCW) * y[H(HCW, iStage, MedYES)];
			}
		}
		out[D(age)] += dead;

		// Update the number of fully recovered immune people.
		out[I(age)] += gamma(age, MedNO, ITYPE_A)
			* y[A(age, ISTAGE_LAST)] + gamma(age, MED_NO, ITYPE_M)
			* y[M(age, ISTAGE_LAST)] + rho * y[R(age, RSTAGE_LAST)];

		// Update the number of outpatient visits.
		for (int iStage = 0; iStage < ISTAGEGROUPS; iStage++) {
			out[Outpatients] += alpha  * (y[V(age, iStage)] + y[X(age, iStage)]);
			out[Outpatients] += alphaW[age] * (y[W(age, iStage, MED_NO)] + y[W(age, iStage, MedYES)]);
		}

		// Update the number of antiviral doses used.
		for (int iStage = 0; iStage < maxTreatmentStage[age]; iStage++) {
			double treated = alpha * (y[V(age, iStage)] * todaySevereTreatFract + y[X(age, iStage)] * todayExtremeTreatFract);
			out[Antivirals] += treated;
			if (age == HCW) {
				out[HCWReturnAntivirals] += treated;
			}
		}

		// Update the number of hospitalizations.
		for (int iStage = 0; iStage < maxTreatmentStage(age); iStage++) {
			out[Hospitalisation] += alpha
				* (1.0 - todayExtremeTreatFract + todayExtremeTreatFract * (1.0 - hospPrevTreat)) * y[X(age, iStage)];
		}
		for (int iStage = maxTreatmentStage(age); iStage < ISTAGEGROUPS; iStage++) {
			out[Hospitalisation] += alpha * y[X(age, iStage)];
		}


		// Update the cumulative cases incidence and absenteeism prevalence due to influenza.
		double caseIncidence = 0.0;
		double recoveryIncidence = 0.0;
		caseIncidence += delta
			* (destiny(age, RISK_LOW, ITYPE_V) * y[E(age, RISK_LOW, ESTAGE_LAST)]
				+ destiny(age, RISK_HIGH, ITYPE_V) * y[E(age, RISK_HIGH, ESTAGE_LAST)]
				+ destiny(age, RISK_LOW, ITYPE_X) * y[E(age, RISK_LOW, ESTAGE_LAST)]
				+ destiny(age, RISK_HIGH, ITYPE_X) * y[E(age, RISK_HIGH, ESTAGE_LAST)]);
		recoveryIncidence += rho * y[R(age, RSTAGE_LAST)];
		out[CIC(age)] = caseIncidence;
		out[AP(age)] = caseIncidence - recoveryIncidence - dead;

		//          Update the cumulative absenteeism prevalence due to influenza.
		out[CPA(age)] = y[AP(age)];
	}*/



	/*누적 데이터 계산(초기값 사용시에는 주석처리)*/
	for (int i = 0; i < OutputArray; i++)
		CumulateOutput[i] += OutputY[i];
}

// 감염자 TAB : Susceptibles, exposed, asymptomatic, moderate, severe, dead, immune
double PlotSusceptibles[StageofAgeGroups][NumberofArray];
double PlotExposed[StageofAgeGroups][NumberofArray];
double PlotAsymptomatic[StageofAgeGroups][NumberofArray];
double PlotModerate[StageofAgeGroups][NumberofArray];
double PlotSevere[StageofAgeGroups][NumberofArray];
double PlotDead[StageofAgeGroups][NumberofArray];
double PlotImmune[StageofAgeGroups][NumberofArray];

// 의료자원 TAB : N-95mask, respirator,  Antivirals
double PlotN95mask[StageofAgeGroups][NumberofArray];
double PlotRespirator[StageofAgeGroups][NumberofArray];
double PlotAntivirals[StageofAgeGroups][NumberofArray];

// 검체수 TAB : Specimen
double PlotSpecimen[StageofAgeGroups][NumberofArray];

// 일일 TAB : outpatients, HospitalICU, HospitalNICU
double PlotOutpatients[StageofAgeGroups][NumberofArray];
double PlotHospitalICU[StageofAgeGroups][NumberofArray];
double PlotHospitalNICU[StageofAgeGroups][NumberofArray];

// 누적 TAB : outpatients, HospitalICU, HospitalNICU
double PlotCumOutpatients[StageofAgeGroups][NumberofArray];
double PlotCumHospitalICU[StageofAgeGroups][NumberofArray];
double PlotCumHospitalNICU[StageofAgeGroups][NumberofArray];

void KfluStep()
{
	double day;
	
	Initialize();
	InitialY();
	for (day = 0.0; day < Maximumday; day = day + (1.0 / TimeResolution))
	{
		EvaluationY(day);
		ArrayforPlot(day);
		/*std::cout << '\r';
		for (int i = 0; i <= day*10; i++)
			std::cout << PlotSusceptibles[1][i] << ' ';
		*/
	}
}


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
}