#pragma once

#include <Eigen/Dense>

//**********************************************
//System Define
//==============================================
#define Maximumday 200
#define TimeResolution 10
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

//질병단계 k to m
#define Stageofk 7		//임의 값임

//BinarySearch 함수 input data로 사용
#define typeR0 0
#define typeF50 1
#define typeDeadFraction 2

#define MedNO 0
#define MedYES 1
#define MedGroups 2

#define ItypeA 0
#define ItypeM 1
#define ItypeV 2
#define ItypeW 3
#define ItypeX 4
#define ItypeH 5
#define ItypeGroups 6

#define IsoNO 0
#define IsoYES 1
#define IsoGroups 2




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
#define Antivirals (Outpatients + 1)
#define Hospitalisation (Antivirals + 1)

#define InfectedC (Hospitalisation + 1)
#define CasesC (InfectedC + 1)
#define HCWWorkReduction (CasesC + 1)
#define HCWReturnAntivirals (HCWWorkReduction + 1)
#define OupputArray (HCWReturnAntivirals + 1)


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

//**********************************************
//Input 화면 탭 입력변수 목록
//==============================================
//--인구
double Population[StageofAgeGroups] = { 5272, 6773, 7952, 55086, 29127, 0 };	//0to6, 7to12, 13to18, 19to64, 65toEnd, HCW
double ContactMatrix[StageofAgeWithoutHCW][StageofAgeWithoutHCW] =
{ { 169.14,	31.47,	17.76,	34.50,	11.47 },
{ 0,		274.51,	32.31,	34.86,	11.5 },
{ 0,		0,		224.25,	50.75,	14.96 },
{ 0,		0,		0,		75.66,	25.08 },
{ 0,		0,		0,		0,		54.23 } };
double SchoolContactRate[ChildClass] = { 80.0, 70.0, 50.0 };		/*percentage 함수 필요*/
//결석으로 어른과 접촉이 강화되는 정도
unsigned int AbsenceContactRatio = 3;

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
double SchoolCloseContactRatio = 2;
//대중집회 취소 및 그에 따른 접촉 수준 변동
double GatheringCancelReductionRate = 0.0;
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

// Initialize the contagiousness of cases (by course of disease).
double contagiousness[ItypeGroups]; // infFact(Influsim)

//Rate at which severe and extremely severe cases seek medical help.
double alpha;
//Rate at which severe cases at home again seek medical help.
double alphaW[StageofAgeGroups];

//beta, ebeta
double eBeta[StageofAgeGroups][StageofAgeGroups];
double beta[StageofAgeGroups][StageofAgeGroups][MedGroups][ItypeGroups][IsoGroups]; // medgroups yes no, ITypegroups 6, ISOGroups yes no.

//ageClass
unsigned int healthCareWorkers = 375;
double total;
double initialExposed; // Initial fraction of newly infected individuals.
double ageDistribution[StageofAgeGroups];

unsigned int ageClass[StageofAgeGroups] = { Child, Child, Child, Worker, Elderly, Worker }; // 0, 0, 0, 1, 2, 1(HCW)

double redistributionFactor[Age19to64];
double redistributionFactorChildHealthCare[Age19to64];

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

bool doSchoolClosure0to6[2000];
bool doSchoolClosure7to12[2000];
bool doSchoolClosure13to18[2000];


double Susceptible[StageofAgeGroups][StageofRisk];
double delta; //incubate the infection

//Average time after onset of symptoms when severe and extremely severe cases seek medical help[days].
double consultationDelay = 1.0;

//Average number of doctoral visits per severe case.
double outpatientVisits = 1;

//Course of disease(by age and risk group).
double Courseofdisease[StageofAgeGroups][StageofRisk][ItypeGroups];

//Transition rate during the contagious period (by age, medication and course of disease)
double gamma[StageofAgeGroups][MedGroups][ItypeGroups];

//Average duration of the infectious period (by age, medication and course of disease)
double infDur[StageofAgeGroups][MedGroups][ItypeGroups];

//Maximum stage of contagiousness during which antiviral treatment can be given (by age)
int maxTreatmentStage[StageofAgeGroups];

//**********************************************
//Function & Class
//==============================================
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
				eBeta[ageSus][ageInf] = LastLatentPeriodCase * b * ContactMatrix[ageSus][ageInf];   // eBeta.             LastLatentPeriodCase = eInfFact

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
					//수정beta[ageSus][ageInf][MedNO][type][IsoNO] = contagiousness[type] * b * ContactMatrix[ageSus][ageInf] * redistributionFactorChildHealthCare; //????? 이 변수? influsim에는 계산해서 구하는 변수
																																							   // redistributionFraction을 이용해 redistributionFactorChildHealthCare을 구해야하지만 UI상에는 접촉강화정도 3.0만 표기.
																																							   // influsim 상에서 redistributionFraction는 디폴트로 있지만 인풋은 받지 않는 모양
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

		/*수정
		//nextGenerationMatrix Calculation
		double nextGenerationMatrix[StageofAgeGroups][StageofAgeGroups];
		for (int ageSus = 0; ageSus < StageofAgeGroups; ageSus++) {
			for (int ageInf = 0; ageInf < StageofAgeGroups; ageInf++) {
				nextGenerationMatrix[ageSus][ageInf] = (susceptibles[ageSus][LowRisk] + susceptibles[ageSus][HighRisk])
					* eBeta[ageSus][ageInf] * expDur[0] * prodromalStages / EstageGroups;
				for (int risk = 0; risk < StageofRisk; risk++) {
					for (int type = 0; type < ItypeGroups; type++) {
						double temp = susceptibles(ageSus, risk) * destiny(ageInf, risk, type)
							* beta[ageSus][ageInf][MedNO][type][IsoNO] * infDur[ageInf][MedNO][type];
						if ((type == ItypeX) || (type == ItypeH))
							temp *= (1.0 - deadFraction[ageInf]);
						nextGenerationMatrix[ageSus][ageInf] += temp;
					}
				}
			}
		}*/

		Eigen::MatrixXd Ematirx(7, 7);
		Eigen::MatrixXd realEigenvalues;
		Eigen::MatrixXd imagEigenvalues;
		Eigen::MatrixXd getEigenvector;

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				//수정Ematirx(i, j) = nextGenerationMatrix[i][j];
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

		double eigenvector[StageofAgeGroups];
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

/*Initialize function*/
void Initialize()
{
	//
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
		Susceptible[age][LowRisk] = ageDistribution[age] * (1.0 - percentage(HighRiskRate[ageClass[age]]));
		Susceptible[age][HighRisk] = ageDistribution[age] * percentage(HighRiskRate[ageClass[age]]);
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
		//수정redistributionFactor[ageSus] = 1.0 + percentage(SchoolContactRate[ageSus]) * percentage(redistributionFraction[ageSus]) * ageMatrix[ageSus][ageSus] * Individuals[ageSus] / denominator;
		//수정redistributionFactorChildHealthCare[ageSus] = 1.0 + percentage(SchoolContactRate[ageSus]) * percentage(AbsenceContactRatio[ageSus]) * ageMatrix[ageSus][ageSus] * Individuals[ageSus] / denominator;
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
		double dead = deadFraction[age];
		double gam = gamma[age][MedNO][ItypeH];
		tau[age] = Root.findRoot(0, 1, typeDeadFraction);
	}

	std::fill_n(doSchoolClosure0to6, (Maximumday*TimeResolution), false);
	std::fill_n(doSchoolClosure7to12, (Maximumday*TimeResolution), false);
	std::fill_n(doSchoolClosure13to18, (Maximumday*TimeResolution), false);


	//std::fill_n(cc + 3, 5, true); -> 0001111100000~
	if (SchoolCloseRangeBegin != SchoolCloseRangeEnd) {
		std::fill_n(doSchoolClosure0to6 + SchoolCloseRangeBegin, SchoolCloseRangeEnd - SchoolCloseRangeBegin, true);
		std::fill_n(doSchoolClosure7to12 + SchoolCloseRangeBegin, SchoolCloseRangeEnd - SchoolCloseRangeBegin, true);
		std::fill_n(doSchoolClosure13to18 + SchoolCloseRangeBegin, SchoolCloseRangeEnd - SchoolCloseRangeBegin, true);
	}
}