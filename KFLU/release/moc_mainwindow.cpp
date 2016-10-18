/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[117];
    char stringdata0[3512];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "makeInfectionPlot"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 15), // "QVector<double>"
QT_MOC_LITERAL(4, 46, 1), // "x"
QT_MOC_LITERAL(5, 48, 1), // "y"
QT_MOC_LITERAL(6, 50, 16), // "makeResourcePlot"
QT_MOC_LITERAL(7, 67, 16), // "makeSpecimenPlot"
QT_MOC_LITERAL(8, 84, 13), // "makeDailyPlot"
QT_MOC_LITERAL(9, 98, 18), // "makeCumulativePlot"
QT_MOC_LITERAL(10, 117, 22), // "on_startButton_clicked"
QT_MOC_LITERAL(11, 140, 21), // "on_areaButton_clicked"
QT_MOC_LITERAL(12, 162, 21), // "on_areaSubmit_clicked"
QT_MOC_LITERAL(13, 184, 24), // "on_outputPageBtn_clicked"
QT_MOC_LITERAL(14, 209, 23), // "on_inputPageBtn_clicked"
QT_MOC_LITERAL(15, 233, 27), // "on_input_Age0to6_textEdited"
QT_MOC_LITERAL(16, 261, 4), // "arg1"
QT_MOC_LITERAL(17, 266, 28), // "on_input_Age7to12_textEdited"
QT_MOC_LITERAL(18, 295, 29), // "on_input_Age13to18_textEdited"
QT_MOC_LITERAL(19, 325, 29), // "on_input_Age19to64_textEdited"
QT_MOC_LITERAL(20, 355, 30), // "on_input_Age65toEnd_textEdited"
QT_MOC_LITERAL(21, 386, 35), // "on_input_SchoolRatio0to6_text..."
QT_MOC_LITERAL(22, 422, 36), // "on_input_SchoolRatio7to12_tex..."
QT_MOC_LITERAL(23, 459, 37), // "on_input_SchoolRatio13to18_te..."
QT_MOC_LITERAL(24, 497, 31), // "on_input_AbsentRatio_textEdited"
QT_MOC_LITERAL(25, 529, 32), // "on_input_LatentPeriod_textEdited"
QT_MOC_LITERAL(26, 562, 35), // "on_input_infDuration_1_1_text..."
QT_MOC_LITERAL(27, 598, 35), // "on_input_infDuration_1_2_text..."
QT_MOC_LITERAL(28, 634, 35), // "on_input_infDuration_1_3_text..."
QT_MOC_LITERAL(29, 670, 35), // "on_input_infDuration_2_1_text..."
QT_MOC_LITERAL(30, 706, 35), // "on_input_infDuration_2_2_text..."
QT_MOC_LITERAL(31, 742, 35), // "on_input_infDuration_2_3_text..."
QT_MOC_LITERAL(32, 778, 32), // "on_input_returnToWork_textEdited"
QT_MOC_LITERAL(33, 811, 28), // "on_input_MildRate_textEdited"
QT_MOC_LITERAL(34, 840, 30), // "on_input_SevereRate_textEdited"
QT_MOC_LITERAL(35, 871, 28), // "on_input_high_1_1_textEdited"
QT_MOC_LITERAL(36, 900, 28), // "on_input_high_1_2_textEdited"
QT_MOC_LITERAL(37, 929, 28), // "on_input_high_1_3_textEdited"
QT_MOC_LITERAL(38, 958, 28), // "on_input_high_2_1_textEdited"
QT_MOC_LITERAL(39, 987, 28), // "on_input_high_2_2_textEdited"
QT_MOC_LITERAL(40, 1016, 28), // "on_input_high_2_3_textEdited"
QT_MOC_LITERAL(41, 1045, 28), // "on_input_high_3_1_textEdited"
QT_MOC_LITERAL(42, 1074, 28), // "on_input_high_3_2_textEdited"
QT_MOC_LITERAL(43, 1103, 28), // "on_input_high_3_3_textEdited"
QT_MOC_LITERAL(44, 1132, 26), // "on_input_dead_1_textEdited"
QT_MOC_LITERAL(45, 1159, 26), // "on_input_dead_2_textEdited"
QT_MOC_LITERAL(46, 1186, 26), // "on_input_dead_3_textEdited"
QT_MOC_LITERAL(47, 1213, 22), // "on_input_R0_textEdited"
QT_MOC_LITERAL(48, 1236, 30), // "on_input_lastLatent_textEdited"
QT_MOC_LITERAL(49, 1267, 32), // "on_input_asymptomatic_textEdited"
QT_MOC_LITERAL(50, 1300, 28), // "on_input_moderate_textEdited"
QT_MOC_LITERAL(51, 1329, 32), // "on_input_isolModerate_textEdited"
QT_MOC_LITERAL(52, 1362, 34), // "on_input_isolSevereHome_textE..."
QT_MOC_LITERAL(53, 1397, 38), // "on_input_isolSevereHospital_t..."
QT_MOC_LITERAL(54, 1436, 29), // "on_input_isolStart_textEdited"
QT_MOC_LITERAL(55, 1466, 27), // "on_input_isolEnd_textEdited"
QT_MOC_LITERAL(56, 1494, 34), // "on_input_antiviralsRate_textE..."
QT_MOC_LITERAL(57, 1529, 31), // "on_input_medicalHelp_textEdited"
QT_MOC_LITERAL(58, 1561, 34), // "on_input_antiviralsHelp_textE..."
QT_MOC_LITERAL(59, 1596, 33), // "on_input_verySickTreat_textEd..."
QT_MOC_LITERAL(60, 1630, 38), // "on_input_verySickTreatStart_t..."
QT_MOC_LITERAL(61, 1669, 36), // "on_input_verySickTreatEnd_tex..."
QT_MOC_LITERAL(62, 1706, 38), // "on_input_extreamlySickTreat_t..."
QT_MOC_LITERAL(63, 1745, 43), // "on_input_extreamlySickTreatSt..."
QT_MOC_LITERAL(64, 1789, 41), // "on_input_extreamlySickTreatEn..."
QT_MOC_LITERAL(65, 1831, 40), // "on_input_contagiousnessReduct..."
QT_MOC_LITERAL(66, 1872, 34), // "on_input_durationReduct_textE..."
QT_MOC_LITERAL(67, 1907, 42), // "on_input_HospitailizationRedu..."
QT_MOC_LITERAL(68, 1950, 33), // "on_input_contactReduct_textEd..."
QT_MOC_LITERAL(69, 1984, 38), // "on_input_contactReductStart_t..."
QT_MOC_LITERAL(70, 2023, 36), // "on_input_contactReductEnd_tex..."
QT_MOC_LITERAL(71, 2060, 36), // "on_input_SchoolCloseStart_tex..."
QT_MOC_LITERAL(72, 2097, 34), // "on_input_SchoolCloseEnd_textE..."
QT_MOC_LITERAL(73, 2132, 38), // "on_input_schoolCloseContact_t..."
QT_MOC_LITERAL(74, 2171, 35), // "on_input_gatheringCancel_text..."
QT_MOC_LITERAL(75, 2207, 40), // "on_input_gatheringCancelStart..."
QT_MOC_LITERAL(76, 2248, 38), // "on_input_gatheringCancelEnd_t..."
QT_MOC_LITERAL(77, 2287, 24), // "on_input_NICU_textEdited"
QT_MOC_LITERAL(78, 2312, 23), // "on_input_ICU_textEdited"
QT_MOC_LITERAL(79, 2336, 29), // "on_input_vaccine_1_textEdited"
QT_MOC_LITERAL(80, 2366, 29), // "on_input_vaccine_2_textEdited"
QT_MOC_LITERAL(81, 2396, 29), // "on_input_vaccine_3_textEdited"
QT_MOC_LITERAL(82, 2426, 29), // "on_input_vaccine_4_textEdited"
QT_MOC_LITERAL(83, 2456, 29), // "on_input_vaccine_5_textEdited"
QT_MOC_LITERAL(84, 2486, 35), // "on_input_vaccineEffect_1_text..."
QT_MOC_LITERAL(85, 2522, 35), // "on_input_vaccineEffect_2_text..."
QT_MOC_LITERAL(86, 2558, 35), // "on_input_vaccineEffect_3_text..."
QT_MOC_LITERAL(87, 2594, 35), // "on_input_vaccineEffect_4_text..."
QT_MOC_LITERAL(88, 2630, 35), // "on_input_vaccineEffect_5_text..."
QT_MOC_LITERAL(89, 2666, 33), // "on_input_antibodyRange_textEd..."
QT_MOC_LITERAL(90, 2700, 32), // "on_input_vaccineStart_textEdited"
QT_MOC_LITERAL(91, 2733, 29), // "on_input_mask_NICU_textEdited"
QT_MOC_LITERAL(92, 2763, 28), // "on_input_mask_ICU_textEdited"
QT_MOC_LITERAL(93, 2792, 28), // "on_input_respRate_textEdited"
QT_MOC_LITERAL(94, 2821, 29), // "on_input_reinspect_textEdited"
QT_MOC_LITERAL(95, 2851, 30), // "on_input_outpatient_textEdited"
QT_MOC_LITERAL(96, 2882, 24), // "on_age_checkBox1_clicked"
QT_MOC_LITERAL(97, 2907, 24), // "on_age_checkBox2_clicked"
QT_MOC_LITERAL(98, 2932, 24), // "on_age_checkBox3_clicked"
QT_MOC_LITERAL(99, 2957, 24), // "on_age_checkBox4_clicked"
QT_MOC_LITERAL(100, 2982, 24), // "on_age_checkBox5_clicked"
QT_MOC_LITERAL(101, 3007, 24), // "on_age_checkBox6_clicked"
QT_MOC_LITERAL(102, 3032, 31), // "on_input_contact_1_1_textEdited"
QT_MOC_LITERAL(103, 3064, 31), // "on_input_contact_1_2_textEdited"
QT_MOC_LITERAL(104, 3096, 31), // "on_input_contact_1_3_textEdited"
QT_MOC_LITERAL(105, 3128, 31), // "on_input_contact_1_4_textEdited"
QT_MOC_LITERAL(106, 3160, 31), // "on_input_contact_1_5_textEdited"
QT_MOC_LITERAL(107, 3192, 31), // "on_input_contact_2_2_textEdited"
QT_MOC_LITERAL(108, 3224, 31), // "on_input_contact_2_3_textEdited"
QT_MOC_LITERAL(109, 3256, 31), // "on_input_contact_2_4_textEdited"
QT_MOC_LITERAL(110, 3288, 31), // "on_input_contact_2_5_textEdited"
QT_MOC_LITERAL(111, 3320, 31), // "on_input_contact_3_3_textEdited"
QT_MOC_LITERAL(112, 3352, 31), // "on_input_contact_3_4_textEdited"
QT_MOC_LITERAL(113, 3384, 31), // "on_input_contact_3_5_textEdited"
QT_MOC_LITERAL(114, 3416, 31), // "on_input_contact_4_4_textEdited"
QT_MOC_LITERAL(115, 3448, 31), // "on_input_contact_4_5_textEdited"
QT_MOC_LITERAL(116, 3480, 31) // "on_input_contact_5_5_textEdited"

    },
    "MainWindow\0makeInfectionPlot\0\0"
    "QVector<double>\0x\0y\0makeResourcePlot\0"
    "makeSpecimenPlot\0makeDailyPlot\0"
    "makeCumulativePlot\0on_startButton_clicked\0"
    "on_areaButton_clicked\0on_areaSubmit_clicked\0"
    "on_outputPageBtn_clicked\0"
    "on_inputPageBtn_clicked\0"
    "on_input_Age0to6_textEdited\0arg1\0"
    "on_input_Age7to12_textEdited\0"
    "on_input_Age13to18_textEdited\0"
    "on_input_Age19to64_textEdited\0"
    "on_input_Age65toEnd_textEdited\0"
    "on_input_SchoolRatio0to6_textEdited\0"
    "on_input_SchoolRatio7to12_textEdited\0"
    "on_input_SchoolRatio13to18_textEdited\0"
    "on_input_AbsentRatio_textEdited\0"
    "on_input_LatentPeriod_textEdited\0"
    "on_input_infDuration_1_1_textEdited\0"
    "on_input_infDuration_1_2_textEdited\0"
    "on_input_infDuration_1_3_textEdited\0"
    "on_input_infDuration_2_1_textEdited\0"
    "on_input_infDuration_2_2_textEdited\0"
    "on_input_infDuration_2_3_textEdited\0"
    "on_input_returnToWork_textEdited\0"
    "on_input_MildRate_textEdited\0"
    "on_input_SevereRate_textEdited\0"
    "on_input_high_1_1_textEdited\0"
    "on_input_high_1_2_textEdited\0"
    "on_input_high_1_3_textEdited\0"
    "on_input_high_2_1_textEdited\0"
    "on_input_high_2_2_textEdited\0"
    "on_input_high_2_3_textEdited\0"
    "on_input_high_3_1_textEdited\0"
    "on_input_high_3_2_textEdited\0"
    "on_input_high_3_3_textEdited\0"
    "on_input_dead_1_textEdited\0"
    "on_input_dead_2_textEdited\0"
    "on_input_dead_3_textEdited\0"
    "on_input_R0_textEdited\0"
    "on_input_lastLatent_textEdited\0"
    "on_input_asymptomatic_textEdited\0"
    "on_input_moderate_textEdited\0"
    "on_input_isolModerate_textEdited\0"
    "on_input_isolSevereHome_textEdited\0"
    "on_input_isolSevereHospital_textEdited\0"
    "on_input_isolStart_textEdited\0"
    "on_input_isolEnd_textEdited\0"
    "on_input_antiviralsRate_textEdited\0"
    "on_input_medicalHelp_textEdited\0"
    "on_input_antiviralsHelp_textEdited\0"
    "on_input_verySickTreat_textEdited\0"
    "on_input_verySickTreatStart_textEdited\0"
    "on_input_verySickTreatEnd_textEdited\0"
    "on_input_extreamlySickTreat_textEdited\0"
    "on_input_extreamlySickTreatStart_textEdited\0"
    "on_input_extreamlySickTreatEnd_textEdited\0"
    "on_input_contagiousnessReduct_textEdited\0"
    "on_input_durationReduct_textEdited\0"
    "on_input_HospitailizationReduct_textEdited\0"
    "on_input_contactReduct_textEdited\0"
    "on_input_contactReductStart_textEdited\0"
    "on_input_contactReductEnd_textEdited\0"
    "on_input_SchoolCloseStart_textEdited\0"
    "on_input_SchoolCloseEnd_textEdited\0"
    "on_input_schoolCloseContact_textEdited\0"
    "on_input_gatheringCancel_textEdited\0"
    "on_input_gatheringCancelStart_textEdited\0"
    "on_input_gatheringCancelEnd_textEdited\0"
    "on_input_NICU_textEdited\0"
    "on_input_ICU_textEdited\0"
    "on_input_vaccine_1_textEdited\0"
    "on_input_vaccine_2_textEdited\0"
    "on_input_vaccine_3_textEdited\0"
    "on_input_vaccine_4_textEdited\0"
    "on_input_vaccine_5_textEdited\0"
    "on_input_vaccineEffect_1_textEdited\0"
    "on_input_vaccineEffect_2_textEdited\0"
    "on_input_vaccineEffect_3_textEdited\0"
    "on_input_vaccineEffect_4_textEdited\0"
    "on_input_vaccineEffect_5_textEdited\0"
    "on_input_antibodyRange_textEdited\0"
    "on_input_vaccineStart_textEdited\0"
    "on_input_mask_NICU_textEdited\0"
    "on_input_mask_ICU_textEdited\0"
    "on_input_respRate_textEdited\0"
    "on_input_reinspect_textEdited\0"
    "on_input_outpatient_textEdited\0"
    "on_age_checkBox1_clicked\0"
    "on_age_checkBox2_clicked\0"
    "on_age_checkBox3_clicked\0"
    "on_age_checkBox4_clicked\0"
    "on_age_checkBox5_clicked\0"
    "on_age_checkBox6_clicked\0"
    "on_input_contact_1_1_textEdited\0"
    "on_input_contact_1_2_textEdited\0"
    "on_input_contact_1_3_textEdited\0"
    "on_input_contact_1_4_textEdited\0"
    "on_input_contact_1_5_textEdited\0"
    "on_input_contact_2_2_textEdited\0"
    "on_input_contact_2_3_textEdited\0"
    "on_input_contact_2_4_textEdited\0"
    "on_input_contact_2_5_textEdited\0"
    "on_input_contact_3_3_textEdited\0"
    "on_input_contact_3_4_textEdited\0"
    "on_input_contact_3_5_textEdited\0"
    "on_input_contact_4_4_textEdited\0"
    "on_input_contact_4_5_textEdited\0"
    "on_input_contact_5_5_textEdited"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
     111,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,  569,    2, 0x08 /* Private */,
       6,    2,  574,    2, 0x08 /* Private */,
       7,    2,  579,    2, 0x08 /* Private */,
       8,    2,  584,    2, 0x08 /* Private */,
       9,    2,  589,    2, 0x08 /* Private */,
      10,    0,  594,    2, 0x08 /* Private */,
      11,    0,  595,    2, 0x08 /* Private */,
      12,    0,  596,    2, 0x08 /* Private */,
      13,    0,  597,    2, 0x08 /* Private */,
      14,    0,  598,    2, 0x08 /* Private */,
      15,    1,  599,    2, 0x08 /* Private */,
      17,    1,  602,    2, 0x08 /* Private */,
      18,    1,  605,    2, 0x08 /* Private */,
      19,    1,  608,    2, 0x08 /* Private */,
      20,    1,  611,    2, 0x08 /* Private */,
      21,    1,  614,    2, 0x08 /* Private */,
      22,    1,  617,    2, 0x08 /* Private */,
      23,    1,  620,    2, 0x08 /* Private */,
      24,    1,  623,    2, 0x08 /* Private */,
      25,    1,  626,    2, 0x08 /* Private */,
      26,    1,  629,    2, 0x08 /* Private */,
      27,    1,  632,    2, 0x08 /* Private */,
      28,    1,  635,    2, 0x08 /* Private */,
      29,    1,  638,    2, 0x08 /* Private */,
      30,    1,  641,    2, 0x08 /* Private */,
      31,    1,  644,    2, 0x08 /* Private */,
      32,    1,  647,    2, 0x08 /* Private */,
      33,    1,  650,    2, 0x08 /* Private */,
      34,    1,  653,    2, 0x08 /* Private */,
      35,    1,  656,    2, 0x08 /* Private */,
      36,    1,  659,    2, 0x08 /* Private */,
      37,    1,  662,    2, 0x08 /* Private */,
      38,    1,  665,    2, 0x08 /* Private */,
      39,    1,  668,    2, 0x08 /* Private */,
      40,    1,  671,    2, 0x08 /* Private */,
      41,    1,  674,    2, 0x08 /* Private */,
      42,    1,  677,    2, 0x08 /* Private */,
      43,    1,  680,    2, 0x08 /* Private */,
      44,    1,  683,    2, 0x08 /* Private */,
      45,    1,  686,    2, 0x08 /* Private */,
      46,    1,  689,    2, 0x08 /* Private */,
      47,    1,  692,    2, 0x08 /* Private */,
      48,    1,  695,    2, 0x08 /* Private */,
      49,    1,  698,    2, 0x08 /* Private */,
      50,    1,  701,    2, 0x08 /* Private */,
      51,    1,  704,    2, 0x08 /* Private */,
      52,    1,  707,    2, 0x08 /* Private */,
      53,    1,  710,    2, 0x08 /* Private */,
      54,    1,  713,    2, 0x08 /* Private */,
      55,    1,  716,    2, 0x08 /* Private */,
      56,    1,  719,    2, 0x08 /* Private */,
      57,    1,  722,    2, 0x08 /* Private */,
      58,    1,  725,    2, 0x08 /* Private */,
      59,    1,  728,    2, 0x08 /* Private */,
      60,    1,  731,    2, 0x08 /* Private */,
      61,    1,  734,    2, 0x08 /* Private */,
      62,    1,  737,    2, 0x08 /* Private */,
      63,    1,  740,    2, 0x08 /* Private */,
      64,    1,  743,    2, 0x08 /* Private */,
      65,    1,  746,    2, 0x08 /* Private */,
      66,    1,  749,    2, 0x08 /* Private */,
      67,    1,  752,    2, 0x08 /* Private */,
      68,    1,  755,    2, 0x08 /* Private */,
      69,    1,  758,    2, 0x08 /* Private */,
      70,    1,  761,    2, 0x08 /* Private */,
      71,    1,  764,    2, 0x08 /* Private */,
      72,    1,  767,    2, 0x08 /* Private */,
      73,    1,  770,    2, 0x08 /* Private */,
      74,    1,  773,    2, 0x08 /* Private */,
      75,    1,  776,    2, 0x08 /* Private */,
      76,    1,  779,    2, 0x08 /* Private */,
      77,    1,  782,    2, 0x08 /* Private */,
      78,    1,  785,    2, 0x08 /* Private */,
      79,    1,  788,    2, 0x08 /* Private */,
      80,    1,  791,    2, 0x08 /* Private */,
      81,    1,  794,    2, 0x08 /* Private */,
      82,    1,  797,    2, 0x08 /* Private */,
      83,    1,  800,    2, 0x08 /* Private */,
      84,    1,  803,    2, 0x08 /* Private */,
      85,    1,  806,    2, 0x08 /* Private */,
      86,    1,  809,    2, 0x08 /* Private */,
      87,    1,  812,    2, 0x08 /* Private */,
      88,    1,  815,    2, 0x08 /* Private */,
      89,    1,  818,    2, 0x08 /* Private */,
      90,    1,  821,    2, 0x08 /* Private */,
      91,    1,  824,    2, 0x08 /* Private */,
      92,    1,  827,    2, 0x08 /* Private */,
      93,    1,  830,    2, 0x08 /* Private */,
      94,    1,  833,    2, 0x08 /* Private */,
      95,    1,  836,    2, 0x08 /* Private */,
      96,    0,  839,    2, 0x08 /* Private */,
      97,    0,  840,    2, 0x08 /* Private */,
      98,    0,  841,    2, 0x08 /* Private */,
      99,    0,  842,    2, 0x08 /* Private */,
     100,    0,  843,    2, 0x08 /* Private */,
     101,    0,  844,    2, 0x08 /* Private */,
     102,    1,  845,    2, 0x08 /* Private */,
     103,    1,  848,    2, 0x08 /* Private */,
     104,    1,  851,    2, 0x08 /* Private */,
     105,    1,  854,    2, 0x08 /* Private */,
     106,    1,  857,    2, 0x08 /* Private */,
     107,    1,  860,    2, 0x08 /* Private */,
     108,    1,  863,    2, 0x08 /* Private */,
     109,    1,  866,    2, 0x08 /* Private */,
     110,    1,  869,    2, 0x08 /* Private */,
     111,    1,  872,    2, 0x08 /* Private */,
     112,    1,  875,    2, 0x08 /* Private */,
     113,    1,  878,    2, 0x08 /* Private */,
     114,    1,  881,    2, 0x08 /* Private */,
     115,    1,  884,    2, 0x08 /* Private */,
     116,    1,  887,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->makeInfectionPlot((*reinterpret_cast< QVector<double>(*)>(_a[1])),(*reinterpret_cast< QVector<double>(*)>(_a[2]))); break;
        case 1: _t->makeResourcePlot((*reinterpret_cast< QVector<double>(*)>(_a[1])),(*reinterpret_cast< QVector<double>(*)>(_a[2]))); break;
        case 2: _t->makeSpecimenPlot((*reinterpret_cast< QVector<double>(*)>(_a[1])),(*reinterpret_cast< QVector<double>(*)>(_a[2]))); break;
        case 3: _t->makeDailyPlot((*reinterpret_cast< QVector<double>(*)>(_a[1])),(*reinterpret_cast< QVector<double>(*)>(_a[2]))); break;
        case 4: _t->makeCumulativePlot((*reinterpret_cast< QVector<double>(*)>(_a[1])),(*reinterpret_cast< QVector<double>(*)>(_a[2]))); break;
        case 5: _t->on_startButton_clicked(); break;
        case 6: _t->on_areaButton_clicked(); break;
        case 7: _t->on_areaSubmit_clicked(); break;
        case 8: _t->on_outputPageBtn_clicked(); break;
        case 9: _t->on_inputPageBtn_clicked(); break;
        case 10: _t->on_input_Age0to6_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->on_input_Age7to12_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->on_input_Age13to18_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->on_input_Age19to64_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->on_input_Age65toEnd_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->on_input_SchoolRatio0to6_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->on_input_SchoolRatio7to12_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: _t->on_input_SchoolRatio13to18_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: _t->on_input_AbsentRatio_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 19: _t->on_input_LatentPeriod_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 20: _t->on_input_infDuration_1_1_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 21: _t->on_input_infDuration_1_2_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: _t->on_input_infDuration_1_3_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: _t->on_input_infDuration_2_1_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: _t->on_input_infDuration_2_2_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 25: _t->on_input_infDuration_2_3_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 26: _t->on_input_returnToWork_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 27: _t->on_input_MildRate_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 28: _t->on_input_SevereRate_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 29: _t->on_input_high_1_1_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 30: _t->on_input_high_1_2_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 31: _t->on_input_high_1_3_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 32: _t->on_input_high_2_1_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 33: _t->on_input_high_2_2_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 34: _t->on_input_high_2_3_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 35: _t->on_input_high_3_1_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 36: _t->on_input_high_3_2_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 37: _t->on_input_high_3_3_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 38: _t->on_input_dead_1_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 39: _t->on_input_dead_2_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 40: _t->on_input_dead_3_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 41: _t->on_input_R0_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 42: _t->on_input_lastLatent_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 43: _t->on_input_asymptomatic_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 44: _t->on_input_moderate_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 45: _t->on_input_isolModerate_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 46: _t->on_input_isolSevereHome_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 47: _t->on_input_isolSevereHospital_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 48: _t->on_input_isolStart_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 49: _t->on_input_isolEnd_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 50: _t->on_input_antiviralsRate_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 51: _t->on_input_medicalHelp_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 52: _t->on_input_antiviralsHelp_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 53: _t->on_input_verySickTreat_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 54: _t->on_input_verySickTreatStart_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 55: _t->on_input_verySickTreatEnd_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 56: _t->on_input_extreamlySickTreat_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 57: _t->on_input_extreamlySickTreatStart_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 58: _t->on_input_extreamlySickTreatEnd_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 59: _t->on_input_contagiousnessReduct_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 60: _t->on_input_durationReduct_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 61: _t->on_input_HospitailizationReduct_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 62: _t->on_input_contactReduct_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 63: _t->on_input_contactReductStart_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 64: _t->on_input_contactReductEnd_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 65: _t->on_input_SchoolCloseStart_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 66: _t->on_input_SchoolCloseEnd_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 67: _t->on_input_schoolCloseContact_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 68: _t->on_input_gatheringCancel_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 69: _t->on_input_gatheringCancelStart_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 70: _t->on_input_gatheringCancelEnd_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 71: _t->on_input_NICU_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 72: _t->on_input_ICU_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 73: _t->on_input_vaccine_1_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 74: _t->on_input_vaccine_2_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 75: _t->on_input_vaccine_3_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 76: _t->on_input_vaccine_4_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 77: _t->on_input_vaccine_5_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 78: _t->on_input_vaccineEffect_1_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 79: _t->on_input_vaccineEffect_2_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 80: _t->on_input_vaccineEffect_3_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 81: _t->on_input_vaccineEffect_4_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 82: _t->on_input_vaccineEffect_5_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 83: _t->on_input_antibodyRange_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 84: _t->on_input_vaccineStart_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 85: _t->on_input_mask_NICU_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 86: _t->on_input_mask_ICU_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 87: _t->on_input_respRate_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 88: _t->on_input_reinspect_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 89: _t->on_input_outpatient_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 90: _t->on_age_checkBox1_clicked(); break;
        case 91: _t->on_age_checkBox2_clicked(); break;
        case 92: _t->on_age_checkBox3_clicked(); break;
        case 93: _t->on_age_checkBox4_clicked(); break;
        case 94: _t->on_age_checkBox5_clicked(); break;
        case 95: _t->on_age_checkBox6_clicked(); break;
        case 96: _t->on_input_contact_1_1_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 97: _t->on_input_contact_1_2_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 98: _t->on_input_contact_1_3_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 99: _t->on_input_contact_1_4_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 100: _t->on_input_contact_1_5_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 101: _t->on_input_contact_2_2_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 102: _t->on_input_contact_2_3_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 103: _t->on_input_contact_2_4_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 104: _t->on_input_contact_2_5_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 105: _t->on_input_contact_3_3_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 106: _t->on_input_contact_3_4_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 107: _t->on_input_contact_3_5_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 108: _t->on_input_contact_4_4_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 109: _t->on_input_contact_4_5_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 110: _t->on_input_contact_5_5_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 111)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 111;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 111)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 111;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
