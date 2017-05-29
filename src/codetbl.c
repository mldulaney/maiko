/* $Id: codetbl.c,v 1.3 1999/05/31 23:35:26 sybalsky Exp $ (C) Copyright Venue, All Rights Reserved
 */
static char *id = "$Id: codetbl.c,v 1.3 1999/05/31 23:35:26 sybalsky Exp $ Copyright (C) Venue";

/************************************************************************/
/*									*/
/*	(C) Copyright 1989-95 Venue. All Rights Reserved.		*/
/*	Manufactured in the United States of America.			*/
/*									*/
/*	The contents of this file are proprietary information 		*/
/*	belonging to Venue, and are provided to you under license.	*/
/*	They may not be further distributed or disclosed to third	*/
/*	parties without the specific permission of Venue.		*/
/*									*/
/************************************************************************/

#include "version.h"

/***************************************************/
/* NS <-> EUC character code converstion program   */
/* file name : nstables.c                          */
/* function  : ns_euc --- NS to EUC conversion     */
/*           : euc_ns --- EUC to NS                */
/*	5, Aug '89                                 */
/*	by Shinichi Miyamoto                       */
/*						   */
/*	11,May '90 : table data update by Miyamoto */
/*	15,May '90 : table data update by Miyamoto */
/***************************************************/

#define TABLESIZE 256
#define EUCBITS 0x8080
#define NSBITS 0x7F7F

static unsigned short eucA1[TABLESIZE] = {
    41216, 41217, 41218, 41219, 41220, 41221, 41222, 41223, 41224, 41225, 41226, 41227, 41228,
    41229, 41230, 41231, 41232, 41233, 41234, 41235, 41236, 41237, 41238, 41239, 41240, 41241,
    41242, 41243, 41244, 41245, 41246, 41247, 41248, 41249, 41250, 41251, 41252, 41253, 41254,
    41255, 41256, 41257, 41258, 41259, 41260, 41261, 41262, 41263, 41264, 41265, 41266, 41267,
    41268, 41269, 41270, 41271, 41272, 41273, 41274, 41275, 41276, 41277, 41278, 41279, 41280,
    41281, 41282, 41283, 41284, 41285, 41286, 41287, 41288, 41289, 41290, 41291, 41292, 41293,
    41294, 41295, 41296, 41297, 41298, 41299, 41300, 41301, 41302, 41303, 41304, 41305, 41306,
    41307, 41308, 41309, 41310, 41311, 41312, 41313, 41314, 41315, 41316, 41317, 41318, 41319,
    41320, 41321, 41322, 41323, 41324, 41325, 41326, 41327, 41328, 41329, 41330, 41331, 41332,
    41333, 41334, 41335, 41336, 41337, 41338, 41339, 41340, 41341, 41342, 41343, 41344, 41345,
    41346, 41347, 41348, 41349, 41350, 41351, 41352, 41353, 41354, 41355, 41356, 41357, 41358,
    41359, 41360, 41361, 41362, 41363, 41364, 41365, 41366, 41367, 41368, 41369, 41370, 41371,
    41372, 41373, 41374, 41375, 41376, 8481,  8482,  8483,  44,    46,    183,   58,    59,
    63,    33,    8491,  8492,  194,   193,   200,   195,   9155,  204,   8499,  8500,  8501,
    8502,  8503,  8504,  8505,  8506,  8507,  8508,  61220, 8510,  47,    92,    126,   8514,
    124,   8516,  8517,  169,   39,    170,   186,   40,    41,    8524,  8525,  91,    93,
    123,   125,   61234, 61235, 171,   187,   8534,  8535,  8536,  8537,  8538,  8539,  43,
    45,    177,   180,   184,   61,    8546,  60,    62,    8549,  8550,  8551,  8552,  8553,
    8554,  176,   8556,  8557,  8558,  165,   164,   162,   163,   37,    35,    38,    42,
    64,    167,   8569,  8570,  8571,  8572,  8573,  8574,  41471};

static unsigned short eucA2[TABLESIZE] = {
    41472, 41473, 41474, 41475, 41476, 41477, 41478, 41479, 41480, 41481, 41482, 41483, 41484,
    41485, 41486, 41487, 41488, 41489, 41490, 41491, 41492, 41493, 41494, 41495, 41496, 41497,
    41498, 41499, 41500, 41501, 41502, 41503, 41504, 41505, 41506, 41507, 41508, 41509, 41510,
    41511, 41512, 41513, 41514, 41515, 41516, 41517, 41518, 41519, 41520, 41521, 41522, 41523,
    41524, 41525, 41526, 41527, 41528, 41529, 41530, 41531, 41532, 41533, 41534, 41535, 41536,
    41537, 41538, 41539, 41540, 41541, 41542, 41543, 41544, 41545, 41546, 41547, 41548, 41549,
    41550, 41551, 41552, 41553, 41554, 41555, 41556, 41557, 41558, 41559, 41560, 41561, 41562,
    41563, 41564, 41565, 41566, 41567, 41568, 41569, 41570, 41571, 41572, 41573, 41574, 41575,
    41576, 41577, 41578, 41579, 41580, 41581, 41582, 41583, 41584, 41585, 41586, 41587, 41588,
    41589, 41590, 41591, 41592, 41593, 41594, 41595, 41596, 41597, 41598, 41599, 41600, 41601,
    41602, 41603, 41604, 41605, 41606, 41607, 41608, 41609, 41610, 41611, 41612, 41613, 41614,
    41615, 41616, 41617, 41618, 41619, 41620, 41621, 41622, 41623, 41624, 41625, 41626, 41627,
    41628, 41629, 41630, 41631, 41632, 8737,  8738,  8739,  8740,  8741,  8742,  8743,  8744,
    8745,  174,   172,   173,   175,   8750,  8751,  8752,  8753,  8754,  8755,  8756,  8757,
    8758,  8759,  8760,  8761,  61258, 61260, 61273, 61272, 61275, 61274, 61271, 61270, 8770,
    8771,  8772,  8773,  8774,  8775,  8776,  8777,  61366, 61367, 61290, 61263, 61262, 61365,
    61364, 8785,  8786,  8787,  8788,  8789,  8790,  8791,  8792,  8793,  8794,  8795,  61292,
    61296, 61376, 61370, 61369, 61298, 8802,  61250, 61251, 61308, 64894, 61297, 61295, 61301,
    8810,  8811,  8812,  8813,  8814,  8815,  8816,  8817,  61736, 61249, 9148,  9132,  213,
    61232, 61233, 182,   8826,  8827,  8828,  8829,  8830,  41727};

static unsigned short eucA3[TABLESIZE] = {
    41728, 41729, 41730, 41731, 41732, 41733, 41734, 41735, 41736, 41737, 41738, 41739, 41740,
    41741, 41742, 41743, 41744, 41745, 41746, 41747, 41748, 41749, 41750, 41751, 41752, 41753,
    41754, 41755, 41756, 41757, 41758, 41759, 41760, 41761, 41762, 41763, 41764, 41765, 41766,
    41767, 41768, 41769, 41770, 41771, 41772, 41773, 41774, 41775, 41776, 41777, 41778, 41779,
    41780, 41781, 41782, 41783, 41784, 41785, 41786, 41787, 41788, 41789, 41790, 41791, 41792,
    41793, 41794, 41795, 41796, 41797, 41798, 41799, 41800, 41801, 41802, 41803, 41804, 41805,
    41806, 41807, 41808, 41809, 41810, 41811, 41812, 41813, 41814, 41815, 41816, 41817, 41818,
    41819, 41820, 41821, 41822, 41823, 41824, 41825, 41826, 41827, 41828, 41829, 41830, 41831,
    41832, 41833, 41834, 41835, 41836, 41837, 41838, 41839, 41840, 41841, 41842, 41843, 41844,
    41845, 41846, 41847, 41848, 41849, 41850, 41851, 41852, 41853, 41854, 41855, 41856, 41857,
    41858, 41859, 41860, 41861, 41862, 41863, 41864, 41865, 41866, 41867, 41868, 41869, 41870,
    41871, 41872, 41873, 41874, 41875, 41876, 41877, 41878, 41879, 41880, 41881, 41882, 41883,
    41884, 41885, 41886, 41887, 41888, 8993,  8994,  8995,  8996,  8997,  8998,  8999,  9000,
    9001,  9002,  9003,  9004,  9005,  9006,  9007,  48,    49,    50,    51,    52,    53,
    54,    55,    56,    57,    9018,  9019,  9020,  9021,  9022,  9023,  9024,  65,    66,
    67,    68,    69,    70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
    80,    81,    82,    83,    84,    85,    86,    87,    88,    89,    90,    9051,  9052,
    9053,  9054,  9055,  9056,  97,    98,    99,    100,   101,   102,   103,   104,   105,
    106,   107,   108,   109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
    119,   120,   121,   122,   9083,  9084,  9085,  9086,  41983};

static unsigned short eucA6[TABLESIZE] = {
    42496, 42497, 42498, 42499, 42500, 42501, 42502, 42503, 42504, 42505, 42506, 42507, 42508,
    42509, 42510, 42511, 42512, 42513, 42514, 42515, 42516, 42517, 42518, 42519, 42520, 42521,
    42522, 42523, 42524, 42525, 42526, 42527, 42528, 42529, 42530, 42531, 42532, 42533, 42534,
    42535, 42536, 42537, 42538, 42539, 42540, 42541, 42542, 42543, 42544, 42545, 42546, 42547,
    42548, 42549, 42550, 42551, 42552, 42553, 42554, 42555, 42556, 42557, 42558, 42559, 42560,
    42561, 42562, 42563, 42564, 42565, 42566, 42567, 42568, 42569, 42570, 42571, 42572, 42573,
    42574, 42575, 42576, 42577, 42578, 42579, 42580, 42581, 42582, 42583, 42584, 42585, 42586,
    42587, 42588, 42589, 42590, 42591, 42592, 42593, 42594, 42595, 42596, 42597, 42598, 42599,
    42600, 42601, 42602, 42603, 42604, 42605, 42606, 42607, 42608, 42609, 42610, 42611, 42612,
    42613, 42614, 42615, 42616, 42617, 42618, 42619, 42620, 42621, 42622, 42623, 42624, 42625,
    42626, 42627, 42628, 42629, 42630, 42631, 42632, 42633, 42634, 42635, 42636, 42637, 42638,
    42639, 42640, 42641, 42642, 42643, 42644, 42645, 42646, 42647, 42648, 42649, 42650, 42651,
    42652, 42653, 42654, 42655, 42656, 9793,  9794,  9796,  9797,  9798,  9801,  9802,  9803,
    9804,  9805,  9806,  9807,  9808,  9809,  9810,  9811,  9813,  9814,  9816,  9817,  9818,
    9819,  9820,  9821,  9785,  9786,  9787,  9788,  9789,  9790,  9791,  9792,  9825,  9826,
    9828,  9829,  9830,  9833,  9834,  9835,  9836,  9837,  9838,  9839,  9840,  9841,  9842,
    9843,  9845,  9846,  9848,  9849,  9850,  9851,  9852,  9853,  42713, 42714, 42715, 42716,
    42717, 42718, 42719, 42720, 42721, 42722, 42723, 42724, 42725, 42726, 42727, 42728, 42729,
    42730, 42731, 42732, 42733, 42734, 42735, 42736, 42737, 42738, 42739, 42740, 42741, 42742,
    42743, 42744, 42745, 42746, 42747, 42748, 42749, 42750, 42751};

static unsigned short eucA8[TABLESIZE] = {
    43008, 43009, 43010, 43011, 43012, 43013, 43014, 43015, 43016, 43017, 43018, 43019, 43020,
    43021, 43022, 43023, 43024, 43025, 43026, 43027, 43028, 43029, 43030, 43031, 43032, 43033,
    43034, 43035, 43036, 43037, 43038, 43039, 43040, 43041, 43042, 43043, 43044, 43045, 43046,
    43047, 43048, 43049, 43050, 43051, 43052, 43053, 43054, 43055, 43056, 43057, 43058, 43059,
    43060, 43061, 43062, 43063, 43064, 43065, 43066, 43067, 43068, 43069, 43070, 43071, 43072,
    43073, 43074, 43075, 43076, 43077, 43078, 43079, 43080, 43081, 43082, 43083, 43084, 43085,
    43086, 43087, 43088, 43089, 43090, 43091, 43092, 43093, 43094, 43095, 43096, 43097, 43098,
    43099, 43100, 43101, 43102, 43103, 43104, 43105, 43106, 43107, 43108, 43109, 43110, 43111,
    43112, 43113, 43114, 43115, 43116, 43117, 43118, 43119, 43120, 43121, 43122, 43123, 43124,
    43125, 43126, 43127, 43128, 43129, 43130, 43131, 43132, 43133, 43134, 43135, 43136, 43137,
    43138, 43139, 43140, 43141, 43142, 43143, 43144, 43145, 43146, 43147, 43148, 43149, 43150,
    43151, 43152, 43153, 43154, 43155, 43156, 43157, 43158, 43159, 43160, 43161, 43162, 43163,
    43164, 43165, 43166, 43167, 43168, 61413, 61412, 10275, 10276, 10277, 10278, 10279, 10280,
    10281, 10282, 61414, 61410, 61409, 10286, 10287, 10288, 10289, 10290, 10291, 10292, 10293,
    61411, 10295, 10296, 10297, 10298, 10299, 10300, 10301, 10302, 10303, 10304, 43201, 43202,
    43203, 43204, 43205, 43206, 43207, 43208, 43209, 43210, 43211, 43212, 43213, 43214, 43215,
    43216, 43217, 43218, 43219, 43220, 43221, 43222, 43223, 43224, 43225, 43226, 43227, 43228,
    43229, 43230, 43231, 43232, 43233, 43234, 43235, 43236, 43237, 43238, 43239, 43240, 43241,
    43242, 43243, 43244, 43245, 43246, 43247, 43248, 43249, 43250, 43251, 43252, 43253, 43254,
    43255, 43256, 43257, 43258, 43259, 43260, 43261, 43262, 43263};

static unsigned short eucF4[TABLESIZE] = {
    62464, 62465, 62466, 62467, 62468, 62469, 62470, 62471, 62472, 62473, 62474, 62475, 62476,
    62477, 62478, 62479, 62480, 62481, 62482, 62483, 62484, 62485, 62486, 62487, 62488, 62489,
    62490, 62491, 62492, 62493, 62494, 62495, 62496, 62497, 62498, 62499, 62500, 62501, 62502,
    62503, 62504, 62505, 62506, 62507, 62508, 62509, 62510, 62511, 62512, 62513, 62514, 62515,
    62516, 62517, 62518, 62519, 62520, 62521, 62522, 62523, 62524, 62525, 62526, 62527, 62528,
    62529, 62530, 62531, 62532, 62533, 62534, 62535, 62536, 62537, 62538, 62539, 62540, 62541,
    62542, 62543, 62544, 62545, 62546, 62547, 62548, 62549, 62550, 62551, 62552, 62553, 62554,
    62555, 62556, 62557, 62558, 62559, 62560, 62561, 62562, 62563, 62564, 62565, 62566, 62567,
    62568, 62569, 62570, 62571, 62572, 62573, 62574, 62575, 62576, 62577, 62578, 62579, 62580,
    62581, 62582, 62583, 62584, 62585, 62586, 62587, 62588, 62589, 62590, 62591, 62592, 62593,
    62594, 62595, 62596, 62597, 62598, 62599, 62600, 62601, 62602, 62603, 62604, 62605, 62606,
    62607, 62608, 62609, 62610, 62611, 62612, 62613, 62614, 62615, 62616, 62617, 62618, 62619,
    62620, 62621, 62622, 62623, 62624, 29985, 29986, 29987, 29988, 62629, 62630, 62631, 62632,
    62633, 62634, 62635, 62636, 62637, 62638, 62639, 62640, 62641, 62642, 62643, 62644, 62645,
    62646, 62647, 62648, 62649, 62650, 62651, 62652, 62653, 62654, 62655, 62656, 62657, 62658,
    62659, 62660, 62661, 62662, 62663, 62664, 62665, 62666, 62667, 62668, 62669, 62670, 62671,
    62672, 62673, 62674, 62675, 62676, 62677, 62678, 62679, 62680, 62681, 62682, 62683, 62684,
    62685, 62686, 62687, 62688, 62689, 62690, 62691, 62692, 62693, 62694, 62695, 62696, 62697,
    62698, 62699, 62700, 62701, 62702, 62703, 62704, 62705, 62706, 62707, 62708, 62709, 62710,
    62711, 62712, 62713, 62714, 62715, 62716, 62717, 62718, 62719};

/* initializeNSToeucConversionTables */

static unsigned short ns00[TABLESIZE] = {
    0,     1,     2,     3,     4,     5,     6,     7,     8,     9,     10,    11,    12,
    13,    14,    15,    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
    39,    40,    41,    42,    43,    44,    45,    46,    47,    41904, 41905, 41906, 41907,
    41908, 41909, 41910, 41911, 41912, 41913, 58,    59,    60,    61,    62,    63,    64,
    41921, 41922, 41923, 41924, 41925, 41926, 41927, 41928, 41929, 41930, 41931, 41932, 41933,
    41934, 41935, 41936, 41937, 41938, 41939, 41940, 41941, 41942, 41943, 41944, 41945, 41946,
    91,    92,    93,    94,    95,    96,    41953, 41954, 41955, 41956, 41957, 41958, 41959,
    41960, 41961, 41962, 41963, 41964, 41965, 41966, 41967, 41968, 41969, 41970, 41971, 41972,
    41973, 41974, 41975, 41976, 41977, 41978, 123,   124,   125,   126,   127,   128,   129,
    130,   131,   132,   133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
    143,   144,   145,   146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
    156,   157,   158,   159,   160,   161,   41457, 41458, 41456, 41455, 166,   41464, 168,
    41414, 41416, 41428, 41643, 41644, 41642, 41645, 41451, 41438, 178,   179,   41439, 181,
    41721, 41382, 41440, 41415, 41417, 41429, 188,   189,   190,   191,   192,   41390, 41389,
    41392, 196,   197,   198,   199,   41391, 201,   202,   203,   41394, 205,   206,   207,
    208,   209,   210,   211,   212,   41718, 214,   215,   216,   217,   218,   219,   220,
    221,   222,   223,   224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
    234,   235,   236,   237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
    247,   248,   249,   250,   251,   252,   253,   254,   255};

static unsigned short ns23[TABLESIZE] = {
    8960,  8961, 8962, 8963, 8964, 8965, 8966, 8967,  8968,  8969, 8970, 8971, 8972, 8973, 8974,
    8975,  8976, 8977, 8978, 8979, 8980, 8981, 8982,  8983,  8984, 8985, 8986, 8987, 8988, 8989,
    8990,  8991, 8992, 8993, 8994, 8995, 8996, 8997,  8998,  8999, 9000, 9001, 9002, 9003, 9004,
    9005,  9006, 9007, 9008, 9009, 9010, 9011, 9012,  9013,  9014, 9015, 9016, 9017, 9018, 9019,
    9020,  9021, 9022, 9023, 9024, 9025, 9026, 9027,  9028,  9029, 9030, 9031, 9032, 9033, 9034,
    9035,  9036, 9037, 9038, 9039, 9040, 9041, 9042,  9043,  9044, 9045, 9046, 9047, 9048, 9049,
    9050,  9051, 9052, 9053, 9054, 9055, 9056, 9057,  9058,  9059, 9060, 9061, 9062, 9063, 9064,
    9065,  9066, 9067, 9068, 9069, 9070, 9071, 9072,  9073,  9074, 9075, 9076, 9077, 9078, 9079,
    9080,  9081, 9082, 9083, 9084, 9085, 9086, 9087,  9088,  9089, 9090, 9091, 9092, 9093, 9094,
    9095,  9096, 9097, 9098, 9099, 9100, 9101, 9102,  9103,  9104, 9105, 9106, 9107, 9108, 9109,
    9110,  9111, 9112, 9113, 9114, 9115, 9116, 9117,  9118,  9119, 9120, 9121, 9122, 9123, 9124,
    9125,  9126, 9127, 9128, 9129, 9130, 9131, 41717, 9133,  9134, 9135, 9136, 9137, 9138, 9139,
    9140,  9141, 9142, 9143, 9144, 9145, 9146, 9147,  41716, 9149, 9150, 9151, 9152, 9153, 9154,
    41393, 9156, 9157, 9158, 9159, 9160, 9161, 9162,  9163,  9164, 9165, 9166, 9167, 9168, 9169,
    9170,  9171, 9172, 9173, 9174, 9175, 9176, 9177,  9178,  9179, 9180, 9181, 9182, 9183, 9184,
    9185,  9186, 9187, 9188, 9189, 9190, 9191, 9192,  9193,  9194, 9195, 9196, 9197, 9198, 9199,
    9200,  9201, 9202, 9203, 9204, 9205, 9206, 9207,  9208,  9209, 9210, 9211, 9212, 9213, 9214,
    9215};

static unsigned short ns26[TABLESIZE] = {
    9728,  9729,  9730,  9731,  9732,  9733,  9734,  9735,  9736,  9737,  9738,  9739,  9740,
    9741,  9742,  9743,  9744,  9745,  9746,  9747,  9748,  9749,  9750,  9751,  9752,  9753,
    9754,  9755,  9756,  9757,  9758,  9759,  9760,  9761,  9762,  9763,  9764,  9765,  9766,
    9767,  9768,  9769,  9770,  9771,  9772,  9773,  9774,  9775,  9776,  9777,  9778,  9779,
    9780,  9781,  9782,  9783,  9784,  42681, 42682, 42683, 42684, 42685, 42686, 42687, 42688,
    42657, 42658, 9795,  42659, 42660, 42661, 9799,  9800,  42662, 42663, 42664, 42665, 42666,
    42667, 42668, 42669, 42670, 42671, 42672, 9812,  42673, 42674, 9815,  42675, 42676, 42677,
    42678, 42679, 42680, 9822,  9823,  9824,  42689, 42690, 9827,  42691, 42692, 42693, 9831,
    9832,  42694, 42695, 42696, 42697, 42698, 42699, 42700, 42701, 42702, 42703, 42704, 9844,
    42705, 42706, 9847,  42707, 42708, 42709, 42710, 42711, 42712, 9854,  9855,  9856,  9857,
    9858,  9859,  9860,  9861,  9862,  9863,  9864,  9865,  9866,  9867,  9868,  9869,  9870,
    9871,  9872,  9873,  9874,  9875,  9876,  9877,  9878,  9879,  9880,  9881,  9882,  9883,
    9884,  9885,  9886,  9887,  9888,  9889,  9890,  9891,  9892,  9893,  9894,  9895,  9896,
    9897,  9898,  9899,  9900,  9901,  9902,  9903,  9904,  9905,  9906,  9907,  9908,  9909,
    9910,  9911,  9912,  9913,  9914,  9915,  9916,  9917,  9918,  9919,  9920,  9921,  9922,
    9923,  9924,  9925,  9926,  9927,  9928,  9929,  9930,  9931,  9932,  9933,  9934,  9935,
    9936,  9937,  9938,  9939,  9940,  9941,  9942,  9943,  9944,  9945,  9946,  9947,  9948,
    9949,  9950,  9951,  9952,  9953,  9954,  9955,  9956,  9957,  9958,  9959,  9960,  9961,
    9962,  9963,  9964,  9965,  9966,  9967,  9968,  9969,  9970,  9971,  9972,  9973,  9974,
    9975,  9976,  9977,  9978,  9979,  9980,  9981,  9982,  9983};

static unsigned short ns75[TABLESIZE] = {
    29952, 29953, 29954, 29955, 29956, 29957, 29958, 29959, 29960, 29961, 29962, 29963, 29964,
    29965, 29966, 29967, 29968, 29969, 29970, 29971, 29972, 29973, 29974, 29975, 29976, 29977,
    29978, 29979, 29980, 29981, 29982, 29983, 29984, 62625, 62626, 62627, 62628, 62885, 62886,
    62887, 62888, 62889, 62890, 62891, 62892, 62893, 62894, 62895, 62896, 62897, 62898, 62899,
    62900, 62901, 62902, 62903, 62904, 62905, 62906, 62907, 62908, 62909, 62910, 62911, 62912,
    62913, 62914, 62915, 62916, 62917, 62918, 62919, 62920, 62921, 62922, 62923, 62924, 62925,
    62926, 62927, 62928, 62929, 62930, 62931, 62932, 62933, 62934, 62935, 62936, 62937, 62938,
    62939, 62940, 62941, 62942, 62943, 62944, 62945, 62946, 62947, 62948, 62949, 62950, 62951,
    62952, 62953, 62954, 62955, 62956, 62957, 62958, 62959, 62960, 62961, 62962, 62963, 62964,
    62965, 62966, 62967, 62968, 62969, 62970, 62971, 62972, 62973, 62974, 30079, 30080, 30081,
    30082, 30083, 30084, 30085, 30086, 30087, 30088, 30089, 30090, 30091, 30092, 30093, 30094,
    30095, 30096, 30097, 30098, 30099, 30100, 30101, 30102, 30103, 30104, 30105, 30106, 30107,
    30108, 30109, 30110, 30111, 30112, 30113, 30114, 30115, 30116, 30117, 30118, 30119, 30120,
    30121, 30122, 30123, 30124, 30125, 30126, 30127, 30128, 30129, 30130, 30131, 30132, 30133,
    30134, 30135, 30136, 30137, 30138, 30139, 30140, 30141, 30142, 30143, 30144, 30145, 30146,
    30147, 30148, 30149, 30150, 30151, 30152, 30153, 30154, 30155, 30156, 30157, 30158, 30159,
    30160, 30161, 30162, 30163, 30164, 30165, 30166, 30167, 30168, 30169, 30170, 30171, 30172,
    30173, 30174, 30175, 30176, 30177, 30178, 30179, 30180, 30181, 30182, 30183, 30184, 30185,
    30186, 30187, 30188, 30189, 30190, 30191, 30192, 30193, 30194, 30195, 30196, 30197, 30198,
    30199, 30200, 30201, 30202, 30203, 30204, 30205, 30206, 30207};

static unsigned short nsEE[TABLESIZE] = {
    60928, 60929, 60930, 60931, 60932, 60933, 60934, 60935, 60936, 60937, 60938, 60939, 60940,
    60941, 60942, 60943, 60944, 60945, 60946, 60947, 60948, 60949, 60950, 60951, 60952, 60953,
    60954, 60955, 60956, 60957, 60958, 60959, 60960, 60961, 60962, 60963, 60964, 60965, 60966,
    60967, 60968, 60969, 60970, 60971, 60972, 60973, 60974, 60975, 60976, 60977, 60978, 60979,
    60980, 60981, 60982, 60983, 60984, 60985, 60986, 60987, 60988, 60989, 60990, 60991, 60992,
    60993, 60994, 60995, 60996, 60997, 60998, 60999, 61000, 61001, 61002, 61003, 61004, 61005,
    61006, 61007, 61008, 61009, 61010, 61011, 61012, 61013, 61014, 61015, 61016, 61017, 61018,
    61019, 61020, 61021, 61022, 61023, 61024, 61025, 61026, 61027, 61028, 61029, 61030, 61031,
    61032, 61033, 61034, 61035, 61036, 61037, 61038, 61039, 61040, 61041, 61042, 61043, 61044,
    61045, 61046, 61047, 61048, 61049, 61050, 61051, 61052, 61053, 41409, 61055, 61056, 61057,
    61058, 61059, 61060, 61061, 61062, 61063, 61064, 61065, 61066, 61067, 61068, 61069, 61070,
    61071, 61072, 61073, 61074, 61075, 61076, 61077, 61078, 61079, 61080, 61081, 61082, 61083,
    61084, 61085, 61086, 61087, 61088, 61089, 61090, 61091, 61092, 61093, 61094, 61095, 61096,
    61097, 61098, 61099, 61100, 61101, 61102, 61103, 61104, 61105, 61106, 61107, 61108, 61109,
    61110, 61111, 61112, 61113, 61114, 61115, 61116, 61117, 61118, 61119, 61120, 61121, 61122,
    61123, 61124, 61125, 61126, 61127, 61128, 61129, 61130, 61131, 61132, 61133, 61134, 61135,
    61136, 61137, 61138, 61139, 61140, 61141, 61142, 61143, 61144, 61145, 61146, 61147, 61148,
    61149, 61150, 61151, 61152, 61153, 61154, 61155, 61156, 61157, 61158, 61159, 61160, 61161,
    61162, 61163, 61164, 61165, 61166, 61167, 61168, 61169, 61170, 61171, 61172, 61173, 61174,
    61175, 61176, 61177, 61178, 61179, 61180, 61181, 61182, 61183};

static unsigned short nsEF[TABLESIZE] = {
    61184, 61185, 61186, 61187, 61188, 61189, 61190, 61191, 61192, 61193, 61194, 61195, 61196,
    61197, 61198, 61199, 61200, 61201, 61202, 61203, 61204, 61205, 61206, 61207, 61208, 61209,
    61210, 61211, 61212, 61213, 61214, 61215, 61216, 61217, 61218, 61219, 41405, 41405, 61222,
    61223, 61224, 61225, 41426, 41427, 61228, 61229, 61230, 61231, 41719, 41720, 41426, 41427,
    61236, 61237, 61238, 61239, 61240, 61241, 61242, 61243, 61244, 61245, 61246, 61247, 61248,
    41715, 41699, 41700, 61252, 61253, 61254, 61255, 61256, 61257, 41658, 61259, 41659, 61261,
    41678, 41677, 61264, 61265, 61266, 61267, 61268, 61269, 41665, 41664, 41661, 41660, 41663,
    41662, 61276, 61277, 61278, 61279, 61280, 61281, 61282, 61283, 61284, 61285, 61286, 61287,
    61288, 61289, 41676, 61291, 41692, 61293, 61294, 41704, 41693, 41703, 41697, 61299, 61300,
    41705, 61302, 61303, 61304, 61305, 61306, 61307, 41701, 61309, 61310, 61311, 61312, 61313,
    61314, 61315, 61316, 61317, 61318, 61319, 61320, 61321, 61322, 61323, 61324, 61325, 61326,
    61327, 61328, 61329, 61330, 61331, 61332, 61333, 61334, 61335, 61336, 61337, 61338, 61339,
    61340, 61341, 61342, 61343, 61344, 61345, 61346, 61347, 61348, 61349, 61350, 61351, 61352,
    61353, 61354, 61355, 61356, 61357, 61358, 61359, 61360, 61361, 61362, 61363, 41680, 41679,
    41674, 41675, 61368, 41696, 41695, 61371, 61372, 61373, 61374, 61375, 41694, 61377, 61378,
    61379, 61380, 61381, 61382, 61383, 61384, 61385, 61386, 61387, 61388, 61389, 61390, 61391,
    61392, 61393, 61394, 61395, 61396, 61397, 61398, 61399, 61400, 61401, 61402, 61403, 61404,
    61405, 61406, 61407, 61408, 43181, 43180, 43190, 43170, 43169, 43179, 61415, 61416, 61417,
    61418, 61419, 61420, 61421, 61422, 61423, 61424, 61425, 61426, 61427, 61428, 61429, 61430,
    61431, 61432, 61433, 61434, 61435, 61436, 61437, 61438, 61439};

static unsigned short nsF1[TABLESIZE] = {
    61696, 61697, 61698, 61699, 61700, 61701, 61702, 61703, 61704, 61705, 61706, 61707, 61708,
    61709, 61710, 61711, 61712, 61713, 61714, 61715, 61716, 61717, 61718, 61719, 61720, 61721,
    61722, 61723, 61724, 61725, 61726, 61727, 61728, 61729, 61730, 61731, 61732, 61733, 61734,
    61735, 41714, 61737, 61738, 61739, 61740, 61741, 61742, 61743, 61744, 61745, 61746, 61747,
    61748, 61749, 61750, 61751, 61752, 61753, 61754, 61755, 61756, 61757, 61758, 61759, 61760,
    61761, 61762, 61763, 61764, 61765, 61766, 61767, 61768, 61769, 61770, 61771, 61772, 61773,
    61774, 61775, 61776, 61777, 61778, 61779, 61780, 61781, 61782, 61783, 61784, 61785, 61786,
    61787, 61788, 61789, 61790, 61791, 61792, 61793, 61794, 61795, 61796, 61797, 61798, 61799,
    61800, 61801, 61802, 61803, 61804, 61805, 61806, 61807, 61808, 61809, 61810, 61811, 61812,
    61813, 61814, 61815, 61816, 61817, 61818, 61819, 61820, 61821, 61822, 61823, 61824, 61825,
    61826, 61827, 61828, 61829, 61830, 61831, 61832, 61833, 61834, 61835, 61836, 61837, 61838,
    61839, 61840, 61841, 61842, 61843, 61844, 61845, 61846, 61847, 61848, 61849, 61850, 61851,
    61852, 61853, 61854, 61855, 61856, 61857, 61858, 61859, 61860, 61861, 61862, 61863, 61864,
    61865, 61866, 61867, 61868, 61869, 61870, 61871, 61872, 61873, 61874, 61875, 61876, 61877,
    61878, 61879, 61880, 61881, 61882, 61883, 61884, 61885, 61886, 61887, 61888, 61889, 61890,
    61891, 61892, 61893, 61894, 61895, 61896, 61897, 61898, 61899, 61900, 61901, 61902, 61903,
    61904, 61905, 61906, 61907, 61908, 61909, 61910, 61911, 61912, 61913, 61914, 61915, 61916,
    61917, 61918, 61919, 61920, 61921, 61922, 61923, 61924, 61925, 61926, 61927, 61928, 61929,
    61930, 61931, 61932, 61933, 61934, 61935, 61936, 61937, 61938, 61939, 61940, 61941, 61942,
    61943, 61944, 61945, 61946, 61947, 61948, 61949, 61950, 61951};

static unsigned short nsFD[TABLESIZE] = {
    64768, 64769, 64770, 64771, 64772, 64773, 64774, 64775, 64776, 64777, 64778, 64779, 64780,
    64781, 64782, 64783, 64784, 64785, 64786, 64787, 64788, 64789, 64790, 64791, 64792, 64793,
    64794, 64795, 64796, 64797, 64798, 64799, 64800, 64801, 64802, 64803, 64804, 64805, 64806,
    64807, 64808, 64809, 64810, 64811, 64812, 64813, 64814, 64815, 64816, 64817, 64818, 64819,
    64820, 64821, 64822, 64823, 64824, 64825, 64826, 64827, 64828, 64829, 64830, 64831, 64832,
    64833, 64834, 64835, 64836, 64837, 64838, 64839, 64840, 64841, 64842, 64843, 64844, 64845,
    64846, 64847, 64848, 64849, 64850, 64851, 64852, 64853, 64854, 64855, 64856, 64857, 64858,
    64859, 64860, 64861, 64862, 64863, 64864, 64865, 64866, 64867, 64868, 64869, 64870, 64871,
    64872, 64873, 64874, 64875, 64876, 64877, 64878, 64879, 64880, 64881, 64882, 64883, 64884,
    64885, 64886, 64887, 64888, 64889, 64890, 64891, 41701, 64893, 41702, 64895, 64896, 64897,
    64898, 64899, 64900, 64901, 64902, 64903, 64904, 64905, 64906, 64907, 64908, 64909, 64910,
    64911, 64912, 64913, 64914, 64915, 64916, 64917, 64918, 64919, 64920, 64921, 64922, 64923,
    64924, 64925, 64926, 64927, 64928, 64929, 64930, 64931, 64932, 64933, 64934, 64935, 64936,
    64937, 64938, 64939, 64940, 64941, 64942, 64943, 64944, 64945, 64946, 64947, 64948, 64949,
    64950, 64951, 64952, 64953, 64954, 64955, 64956, 64957, 64958, 64959, 64960, 64961, 64962,
    64963, 64964, 64965, 64966, 64967, 64968, 64969, 64970, 64971, 64972, 64973, 64974, 64975,
    64976, 64977, 64978, 64979, 64980, 64981, 64982, 64983, 64984, 64985, 64986, 64987, 64988,
    64989, 64990, 64991, 64992, 64993, 64994, 64995, 64996, 64997, 64998, 64999, 65000, 65001,
    65002, 65003, 65004, 65005, 65006, 65007, 65008, 65009, 65010, 65011, 65012, 65013, 65014,
    65015, 65016, 65017, 65018, 65019, 65020, 65021, 65022, 65023};

unsigned short euc_ns(short unsigned int euc) {
  unsigned short table;

  table = euc / TABLESIZE;
  switch (table) {
    case 0xA1: return (eucA1[euc % TABLESIZE]);
    case 0xA2: return (eucA2[euc % TABLESIZE]);
    case 0xA3: return (eucA3[euc % TABLESIZE]);
    case 0xA6: return (eucA6[euc % TABLESIZE]);
    case 0xA8: return (eucA8[euc % TABLESIZE]);
    case 0xF4: return (eucF4[euc % TABLESIZE]);
    default: return (euc & NSBITS);
  }
}

unsigned short ns_euc(short unsigned int ns) {
  unsigned short table;

  table = ns / TABLESIZE;
  switch (table) {
    case 0x00: return (ns00[ns % TABLESIZE]);
    case 0x23: return (ns23[ns % TABLESIZE]);
    case 0x26: return (ns26[ns % TABLESIZE]);
    case 0x75: return (ns75[ns % TABLESIZE]);
    case 0xEE: return (nsEE[ns % TABLESIZE]);
    case 0xEF: return (nsEF[ns % TABLESIZE]);
    case 0xF1: return (nsF1[ns % TABLESIZE]);
    case 0xFD: return (nsFD[ns % TABLESIZE]);
    default: return (ns | EUCBITS);
  }
}
