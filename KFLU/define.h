#pragma once

#include <Eigen/Dense>

//**********************************************
//Define Value ���
//==============================================
//���ɺ� ����
#define Age0to6 0
#define Age7to12 1
#define Age13to18 2
#define Age19to64 3
#define Age65toEnd 4
#define HCW 5
//#define AgeTotal 5	//ContactMatrix �հ� Part
#define StageofAgeGroups 6
#define StageofAgeTotal 6

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

//�����ܰ� k to m
#define Stageofk 7		//���� ����

//BinarySearch �Լ� input data�� ���
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
//Define Function ���
//==============================================
double percentage(double);
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
//Input ȭ�� �� �Էº��� ���
//==============================================
//--�α�
unsigned int Population[StageofAgeGroups] = { 0, 0, 0, 0, 0, 0 };	//0to6, 7to12, 13to18, 19to64, 65toEnd, HCW
unsigned int ContactMatrix[StageofAgeGroups][StageofAgeGroups] = { { 0, 0, 0, 0, 0, 0 },
																	{ 0, 0, 0, 0, 0, 0 },
																	{ 0, 0, 0, 0, 0, 0 },
																	{ 0, 0, 0, 0, 0, 0 },
																	{ 0, 0, 0, 0, 0, 0 },
																	{ 0, 0, 0, 0, 0, 0 } };
double SchoolContactRate = 50.0;
//�Ἦ���� ��� ������ ��ȭ�Ǵ� ����
unsigned int AbsenceContactRatio = 3;

//--���� TAB
double LatentPeriod = 1.9;
double InfectiousDuration[StageofSevere][StageofWorkAge] = { { 7.0, 4.1, 4.1 },{ 7.0, 7.0, 7.0 } };

double ReturntoWorkPeriod = 5.0;
double SevereRate = 33.3;
double MildRate = 50.0;
double HighRiskRate[StageofWorkAge] = { 6.0, 14.0, 47.0 };
double LowRiskHospitalRate[StageofWorkAge] = { 0.187, 14.0, 47.0 };
double HighRiskHospitalRate[StageofWorkAge] = { 1.333, 2.762, 7.768 };
double DeadRate[StageofWorkAge] = { 5.541, 16.541, 39.505 };

//--������ TAB
//���� ���� �� �����
double R0 = 2.5;
//�� ���� ���� �Ⱓ �� ���� �Ⱓ ���� ���� ������ ����
double HalfInfectiousRate = 90.0;
//�������� ���� ���� �� ���� �� ����� ������
double LastLatentPeriodCase = 50.0;
double AsymptomaticCase = 50.0;
double ModerateCase = 100.0;
//�κ� �ݸ�
double ModerateCaseIsolation = 50.0;
double SevereHomeCaseIsolation = 50.0;
double SevereHospitalCaseIsolation = 100.0;
double RangeofIsolation = 0;

//--ġ�� TAB
//�׹��̷����� ���� ���� ����
double AntiviralsInjectionRate = 100.0;
//�ǷἭ�� �̿밡�� �ð�
double MedicalHelp = 24.0;
double AntiviralsHelp = 48.0;
//Very Sick Case ġ��
double VerySickTreatRate = 0;
double VerySickTreatRange = 0.0;
//Extremely Sick Case ġ��
double ExtremelySickTreatRate = 0;
double ExtremelySickTreatRange = 0.0;
//ġ�� ȿ��
double ContagiousnessReduction = 80.0;
double DiseaseDurationReduction = 25.0;
double HospitalizationReduction = 50.0;

//--�ݸ� TAB
//�Ϲ����� ���� ���� �� �Ⱓ
double ContactReductionRate = 0.0;
double ContactReductionRange = 0;
//�ޱ� �� �׿� ���� ���� ���� ����
double SchoolCloseRange = 0;
double SchoolCloseContactRatio = 2;
//������ȸ ��� �� �׿� ���� ���� ���� ����
double GatheringCancelReductionRate = 0.0;
double GatheringCancleRange = 0;;

//--�Կ� TAB
//��� ����Ⱓ
double HospitalizationNICU = 5;
double HospitalizationICU = 10;

//--��� TAB
//���ɺ� ��� ������
double VaccineAgeRate[StageofAgeGroups] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
//���ɺ� ��� ����ȿ��
double VaccineEffectAgeRate[StageofAgeGroups] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
//��ü�����Ⱓ
double AntibodyCreateRange = 14;
//��� ���� �ñ�
double VaccineStart = 0;

//--�ڿ� TAB
//N-95����ũ(1��, 1�ϴ� ����)
double MaskNeedNICU;
double MaskNeedICU;
//�ΰ�ȣ��� (�Կ�ȯ�� �� �ΰ�ȣ��� ��� ����)
double RespiratorNeedRate = 50.0;

//--��ü TAB
//��ü �����
double ReinspectionRate = 10.0;
//�ܷ�ȯ�� ��ü����                (Ȯ���ʿ�)
double OutpatientSpecimenTesting = 50.0;

// Initialize the contagiousness of cases (by course of disease).
double contagiousness[ItypeGroups]; // infFact(Influsim)

#define AgeHCW 5 // HCW�� ����Ѵٸ� ���� Total�κ� ++

									//alpha, alphaW
									//Rate at which severe and extremely severe cases seek medical help.
double alpha;
//Rate at which severe cases at home again seek medical help.
double alphaW[StageofAgeGroups];

//beta, ebeta
double eBeta[StageofAgeGroups][StageofAgeGroups];
double beta[StageofAgeGroups][StageofAgeGroups][MedGroups][ItypeGroups][IsoGroups]; // medgroups yes no, ITypegroups 6, ISOGroups yes no.

																					//ageClass
int ageClass[StageofAgeGroups] = { Child, Child, Child, Worker, Elderly, Worker }; //0, 0, 0, 1, 2, 1(HCW)


double output; ///////// �ƿ�ǲ �� ���߿� �����ؾ��Ұ�

//**********************************************
//Function & Class
//==============================================
double percentage(double value)
{
	return (value / 100);
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
					beta[ageSus][ageInf][MedNO][type][IsoNO] = contagiousness[type] * b * ContactMatrix[ageSus][ageInf];  // Contact Matrix�� ageMatrix�� �ٲ���ϳ�? fill matrix �Լ�
				}
			}
		}

		//Severly ill children do not go to school      beta���� ���ܺκ� ó��. �б��ٴϴ� ���̴�
		for (int type = ItypeV; type <= ItypeH; type++)  // type V, W, X, H
		{
			for (int ageSus = Age0to6; ageSus <= Age13to18; ageSus++) {
				for (int ageInf = Age0to6; ageInf <= Age13to18; ageInf++) {
					if (ageSus == ageInf) {
						beta[ageSus][ageInf][MedNO][type][IsoNO] = contagiousness[type] * b * ContactMatrix[ageSus][ageInf] * (1.0 - SchoolContactRate); // �Ἦ���� ���� �б� ���̴� ���μ��� ���� X
					}
					else {
						beta[ageSus][ageInf][MedNO][type][IsoNO] = contagiousness[type] * b * ContactMatrix[ageSus][ageInf]; // �� �ܿ� ���� ������
					}
				}
			}
			for (int ageSus = Age19to64; ageSus <= AgeHCW; ageSus++) { // �Ἦ�� �л����� care�����鼭 ����� ������. ����� �л����̴� ���� ����, HCW����
				for (int ageInf = Age0to6; ageInf <= Age13to18; ageInf++) {
					//����beta[ageSus][ageInf][MedNO][type][IsoNO] = contagiousness[type] * b * ContactMatrix[ageSus][ageInf] * redistributionFactorChildHealthCare; //????? �� ����? influsim���� ����ؼ� ���ϴ� ����
																																							   // redistributionFraction�� �̿��� redistributionFactorChildHealthCare�� ���ؾ������� UI�󿡴� ���˰�ȭ���� 3.0�� ǥ��.
																																							   // influsim �󿡼� redistributionFraction�� ����Ʈ�� ������ ��ǲ�� ���� �ʴ� ���
				}
			}

			//all other contacts remain untouched
			for (int ageSus = Age0to6; ageSus < StageofAgeGroups; ageSus++) {
				for (int ageInf = Age19to64; ageInf < StageofAgeGroups; ageInf++) {
					beta[ageSus][ageInf][MedNO][type][IsoNO] = contagiousness[type] * b * ContactMatrix[ageSus][ageInf];
				}
			}
		}

		for (int ageSus = 0; ageSus < StageofAgeGroups; ageSus++) { // Med Yes�� ���
			for (int ageInf = 0; ageInf < StageofAgeGroups; ageInf++) {
				for (int type = ItypeA; type < ItypeGroups; type++) {
					beta[ageSus][ageInf][MedYES][type][IsoNO] = beta[ageSus][ageInf][MedNO][type][IsoNO] * (1.0 - ContagiousnessReduction);
				}
			}
		}

		/*����
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
				//����Ematirx(i, j) = nextGenerationMatrix[i][j];
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