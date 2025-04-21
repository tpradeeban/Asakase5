//TNO	TESTNAME			 			TEST FUNC	   ssarg={ SSmode ILmode   Term      DQnum   	SSCHK	Rate    FirstEdge Rise/ Fall	Timing      Mpat	   		PC,   	PassCheck    UBM   	 DQScount

////////////////////////
//DRAM (No RDEN) SS4  //
////////////////////////
//{7500,	"SS_DRAM PASS/16DQ/1WAY/LOW",				ss_check,	 {.ssarg={ "DRAM",	1, "LOW",	16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x000,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7501,	"SS_DRAM PASS/16DQ/1WAY/MID",				ss_check,	 {.ssarg={ "DRAM",	1, "MID",	16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x000,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7502,	"SS_DRAM PASS/16DQ/1WAY/HIGH",				ss_check,	 {.ssarg={ "DRAM",	1, "HIGH",	16,	   0xF,     5e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x020,	UT_ON,       UT_OFF,	 UT_ON	}}},

{7500,	"SS_DRAM PASS/16DQ/4WAY/LOW",				ss_check,	 {.ssarg={ "DRAM",	4, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x000,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7501,	"SS_DRAM PASS/16DQ/4WAY/MID",				ss_check,	 {.ssarg={ "DRAM",	4, "MID",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x000,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7502,	"SS_DRAM PASS/16DQ/4WAY/HIGH",				ss_check,	 {.ssarg={ "DRAM",	4, "HIGH",	16,	   0xF,     0.714e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x020,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7503,	"SS_DRAM PASS/16DQ/8WAY/LOW",				ss_check,	 {.ssarg={ "DRAM",	8, "LOW",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x000,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7504,	"SS_DRAM PASS/16DQ/8WAY/MID",				ss_check,	 {.ssarg={ "DRAM",	8, "MID",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x000,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7505,	"SS_DRAM PASS/16DQ/8WAY/HIGH",				ss_check,	 {.ssarg={ "DRAM",	8, "HIGH",	16,	   0xF,     0.370e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x020,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7510,	"SS_DRAM PASS/8DQ/1WAY/LOW",				ss_check,	 {.ssarg={ "DRAM",	1, "LOW",	 16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x000,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7511,	"SS_DRAM PASS/8DQ/1WAY/MID",				ss_check,	 {.ssarg={ "DRAM",	1, "MID",	 16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x000,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7512,	"SS_DRAM PASS/8DQ/1WAY/HIGH",				ss_check,	 {.ssarg={ "DRAM",	1, "HIGH",	 16,	   0xF,     5e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x020,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7510,	"SS_DRAM PASS/8DQ/4WAY/LOW",				ss_check,	 {.ssarg={ "DRAM",	4, "LOW",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x000,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7511,	"SS_DRAM PASS/8DQ/4WAY/MID",				ss_check,	 {.ssarg={ "DRAM",	4, "MID",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x000,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7512,	"SS_DRAM PASS/8DQ/4WAY/HIGH",				ss_check,	 {.ssarg={ "DRAM",	4, "HIGH",	 8,	   0xF,     0.714e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x020,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7513,	"SS_DRAM PASS/8DQ/8WAY/LOW",				ss_check,	 {.ssarg={ "DRAM",	8, "LOW",	 8,        0xF,	    0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x000,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7514,	"SS_DRAM PASS/8DQ/8WAY/MID",				ss_check,	 {.ssarg={ "DRAM",	8, "MID",	 8,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x000,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7515,	"SS_DRAM PASS/8DQ/8WAY/HIGH",				ss_check,	 {.ssarg={ "DRAM",	8, "HIGH",	 8,	   0xF,     0.370e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x020,	UT_ON,       UT_OFF,	 UT_ON	}}},

//{7520,	"SS_DRAM UBM/16DQ/1WAY/LOW", 				ss_check,	 {.ssarg={ "DRAM",	1, "LOW",	16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x040,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7521,	"SS_DRAM UBM/16DQ/1WAY/MID",				ss_check,	 {.ssarg={ "DRAM",	1, "MID",	16,	   0xF,     5e-9, 	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x040,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7522,	"SS_DRAM UBM/16DQ/1WAY/HIGH",				ss_check,	 {.ssarg={ "DRAM",	1, "HIGH",	16,	   0xF,     5e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x060,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7520,	"SS_DRAM UBM/16DQ/4WAY/LOW",				ss_check,	 {.ssarg={ "DRAM",	4, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x040,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7521,	"SS_DRAM UBM/16DQ/4WAY/MID",				ss_check,	 {.ssarg={ "DRAM",	4, "MID",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x040,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7522,	"SS_DRAM UBM/16DQ/4WAY/HIGH",				ss_check,	 {.ssarg={ "DRAM",	4, "HIGH",	16,	   0xF,     0.714e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x060,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7523,	"SS_DRAM UBM/16DQ/8WAY/LOW",				ss_check,	 {.ssarg={ "DRAM",	8, "LOW",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x040,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7524,	"SS_DRAM UBM/16DQ/8WAY/MID",				ss_check,	 {.ssarg={ "DRAM",	8, "MID",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x040,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7525,	"SS_DRAM UBM/16DQ/8WAY/HIGH",				ss_check,	 {.ssarg={ "DRAM",	8, "HIGH",	16,	   0xF,     0.370e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x060,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7530,	"SS_DRAM UBM/8DQ/1WAY/LOW", 				ss_check,	 {.ssarg={ "DRAM",	1, "LOW",	 16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x040,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7531,	"SS_DRAM UBM/8DQ/1WAY/MID",				ss_check,	 {.ssarg={ "DRAM",	1, "MID",	 16,	   0xF,     5e-9, 	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x040,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7532,	"SS_DRAM UBM/8DQ/1WAY/HIGH",				ss_check,	 {.ssarg={ "DRAM",	1, "HIGH",	 16,	   0xF,     5e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x060,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7530,	"SS_DRAM UBM/8DQ/4WAY/LOW",				ss_check,	 {.ssarg={ "DRAM",	4, "LOW",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x040,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7531,	"SS_DRAM UBM/8DQ/4WAY/MID",				ss_check,	 {.ssarg={ "DRAM",	4, "MID",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x040,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7532,	"SS_DRAM UBM/8DQ/4WAY/HIGH",				ss_check,	 {.ssarg={ "DRAM",	4, "HIGH",	 8,	   0xF,     0.714e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x060,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7533,	"SS_DRAM UBM/8DQ/8WAY/LOW",				ss_check,	 {.ssarg={ "DRAM",	8, "LOW",	 8,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x040,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7534,	"SS_DRAM UBM/8DQ/8WAY/MID",				ss_check,	 {.ssarg={ "DRAM",	8, "MID",	 8,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x040,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7535,	"SS_DRAM UBM/8DQ/8WAY/HIGH",				ss_check,	 {.ssarg={ "DRAM",	8, "HIGH",	 8,	   0xF,     0.370e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x060,	UT_OFF,      UT_ON,	 UT_ON	}}},

///////////////////////
//  DRAM (RDEN) SS4  //
///////////////////////
//{7540,	"SS_DRAM(RDEN) PASS/16DQ/1WAY/LOW",			ss_check,	 {.ssarg={ "DRAM_RDEN",	1, "LOW",	16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x200,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7541,	"SS_DRAM(RDEN) PASS/16DQ/1WAY/MID",			ss_check,	 {.ssarg={ "DRAM_RDEN",	1, "MID",	16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x200,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7542,	"SS_DRAM(RDEN) PASS/16DQ/1WAY/HIGH",			ss_check,	 {.ssarg={ "DRAM_RDEN",	1, "HIGH",	16,	   0xF,     5e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x220,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7540,	"SS_DRAM(RDEN) PASS/16DQ/4WAY/LOW",			ss_check,	 {.ssarg={ "DRAM_RDEN",	4, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x200,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7541,	"SS_DRAM(RDEN) PASS/16DQ/4WAY/MID",			ss_check,	 {.ssarg={ "DRAM_RDEN",	4, "MID",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x200,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7542,	"SS_DRAM(RDEN) PASS/16DQ/4WAY/HIGH",			ss_check,	 {.ssarg={ "DRAM_RDEN",	4, "HIGH",	16,	   0xF,     0.714e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x220,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7543,	"SS_DRAM(RDEN) PASS/16DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "LOW",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x200,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7544,	"SS_DRAM(RDEN) PASS/16DQ/8WAY/MID",			ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "MID",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x200,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7545,	"SS_DRAM(RDEN) PASS/16DQ/8WAY/HIGH",			ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "HIGH",	16,	   0xF,     0.370e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x220,	UT_ON,       UT_OFF,	 UT_ON	}}},

//{7550,	"SS_DRAM(RDEN) PASS/8DQ/1WAY/LOW",			ss_check,	 {.ssarg={ "DRAM_RDEN",	1, "LOW",	 16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x200,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7551,	"SS_DRAM(RDEN) PASS/8DQ/1WAY/MID",			ss_check,	 {.ssarg={ "DRAM_RDEN",	1, "MID",	 16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x200,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7552,	"SS_DRAM(RDEN) PASS/8DQ/1WAY/HIGH",			ss_check,	 {.ssarg={ "DRAM_RDEN",	1, "HIGH",	 16,	   0xF,     5e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x220,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7550,	"SS_DRAM(RDEN) PASS/8DQ/4WAY/LOW",			ss_check,	 {.ssarg={ "DRAM_RDEN",	4, "LOW",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x200,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7551,	"SS_DRAM(RDEN) PASS/8DQ/4WAY/MID",			ss_check,	 {.ssarg={ "DRAM_RDEN",	4, "MID",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x200,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7552,	"SS_DRAM(RDEN) PASS/8DQ/4WAY/HIGH",			ss_check,	 {.ssarg={ "DRAM_RDEN",	4, "HIGH",	 8,	   0xF,     0.714e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x220,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7553,	"SS_DRAM(RDEN) PASS/8DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "LOW",	 8,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x200,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7554,	"SS_DRAM(RDEN) PASS/8DQ/8WAY/MID",			ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "MID",	 8,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x200,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7555,	"SS_DRAM(RDEN) PASS/8DQ/8WAY/HIGH",			ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "HIGH",	 8,	   0xF,     0.370e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x220,	UT_ON,       UT_OFF,	 UT_ON	}}},


//{7560,	"SS_DRAM(RDEN) UBM/16DQ/1WAY/LOW", 			ss_check,	 {.ssarg={ "DRAM_RDEN",	1, "LOW",	16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x240,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7561,	"SS_DRAM(RDEN) UBM/16DQ/1WAY/MID",			ss_check,	 {.ssarg={ "DRAM_RDEN",	1, "MID",	16,	   0xF,     5e-9, 	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x240,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7562,	"SS_DRAM(RDEN) UBM/16DQ/1WAY/HIGH",			ss_check,	 {.ssarg={ "DRAM_RDEN",	1, "HIGH",	16,	   0xF,     5e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x260,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7560,	"SS_DRAM(RDEN) UBM/16DQ/4WAY/LOW",			ss_check,	 {.ssarg={ "DRAM_RDEN",	4, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x240,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7561,	"SS_DRAM(RDEN) UBM/16DQ/4WAY/MID",			ss_check,	 {.ssarg={ "DRAM_RDEN",	4, "MID",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x240,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7562,	"SS_DRAM(RDEN) UBM/16DQ/4WAY/HIGH",			ss_check,	 {.ssarg={ "DRAM_RDEN",	4, "HIGH",	16,	   0xF,     0.714e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x260,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7563,	"SS_DRAM(RDEN) UBM/16DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "LOW",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x240,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7564,	"SS_DRAM(RDEN) UBM/16DQ/8WAY/MID",			ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "MID",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x240,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7565,	"SS_DRAM(RDEN) UBM/16DQ/8WAY/HIGH",			ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "HIGH",	16,	   0xF,     0.370e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x260,	UT_OFF,      UT_ON,	 UT_ON	}}},

//{7570,	"SS_DRAM(RDEN) UBM/8DQ/1WAY/LOW", 			ss_check,	 {.ssarg={ "DRAM_RDEN",	1, "LOW",	 16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x240,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7571,	"SS_DRAM(RDEN) UBM/8DQ/1WAY/MID",			ss_check,	 {.ssarg={ "DRAM_RDEN",	1, "MID",	 16,	   0xF,     5e-9, 	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x240,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7572,	"SS_DRAM(RDEN) UBM/8DQ/1WAY/HIGH",			ss_check,	 {.ssarg={ "DRAM_RDEN",	1, "HIGH",	 16,	   0xF,     5e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x260,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7570,	"SS_DRAM(RDEN) UBM/8DQ/4WAY/LOW",			ss_check,	 {.ssarg={ "DRAM_RDEN",	4, "LOW",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x240,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7571,	"SS_DRAM(RDEN) UBM/8DQ/4WAY/MID",			ss_check,	 {.ssarg={ "DRAM_RDEN",	4, "MID",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x240,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7572,	"SS_DRAM(RDEN) UBM/8DQ/4WAY/HIGH",			ss_check,	 {.ssarg={ "DRAM_RDEN",	4, "HIGH",	 8,	   0xF,     0.714e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x260,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7573,	"SS_DRAM(RDEN) UBM/8DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "LOW",	 8,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x240,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7574,	"SS_DRAM(RDEN) UBM/8DQ/8WAY/MID",			ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "MID",	 8,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x240,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7575,	"SS_DRAM(RDEN) UBM/8DQ/8WAY/HIGH",			ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "HIGH",	 8,	   0xF,     0.370e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x260,	UT_OFF,      UT_ON,	 UT_ON	}}},


//////////////////////////
//  NAND MODE (SS1)     //
//////////////////////////
//{7600,	"SS_NAND PASS/16DQ/1WAY/LOW",				ss_check,	 {.ssarg={ "NAND",	1, "LOW",	16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7601,	"SS_NAND PASS/16DQ/1WAY/MID",				ss_check,	 {.ssarg={ "NAND",	1, "MID",	16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7602,	"SS_NAND PASS/16DQ/1WAY/HIGH",				ss_check,	 {.ssarg={ "NAND",	1, "HIGH",	16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7600,	"SS_NAND PASS/16DQ/4WAY/LOW",				ss_check,	 {.ssarg={ "NAND",	4, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7601,	"SS_NAND PASS/16DQ/4WAY/MID",				ss_check,	 {.ssarg={ "NAND",	4, "MID",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7602,	"SS_NAND PASS/16DQ/4WAY/HIGH",				ss_check,	 {.ssarg={ "NAND",	4, "HIGH",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7603,	"SS_NAND PASS/16DQ/8WAY/LOW",				ss_check,	 {.ssarg={ "NAND",	8, "LOW",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7604,	"SS_NAND PASS/16DQ/8WAY/MID",				ss_check,	 {.ssarg={ "NAND",	8, "MID",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7605,	"SS_NAND PASS/16DQ/8WAY/HIGH",				ss_check,	 {.ssarg={ "NAND",	8, "HIGH",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},

//{7610,	"SS_NAND PASS/8DQ/1WAY/LOW",				ss_check,	 {.ssarg={ "NAND",	1, "LOW",	 16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7611,	"SS_NAND PASS/8DQ/1WAY/MID",				ss_check,	 {.ssarg={ "NAND",	1, "MID",	 16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},
//{7612,	"SS_NAND PASS/8DQ/1WAY/HIGH",				ss_check,	 {.ssarg={ "NAND",	1, "HIGH",	 16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7610,	"SS_NAND PASS/8DQ/4WAY/LOW",				ss_check,	 {.ssarg={ "NAND",	4, "LOW",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7611,	"SS_NAND PASS/8DQ/4WAY/MID",				ss_check,	 {.ssarg={ "NAND",	4, "MID",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7612,	"SS_NAND PASS/8DQ/4WAY/HIGH",				ss_check,	 {.ssarg={ "NAND",	4, "HIGH",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7613,	"SS_NAND PASS/8DQ/8WAY/LOW",				ss_check,	 {.ssarg={ "NAND",	8, "LOW",	 8,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7614,	"SS_NAND PASS/8DQ/8WAY/MID",				ss_check,	 {.ssarg={ "NAND",	8, "MID",	 8,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},
{7615,	"SS_NAND PASS/8DQ/8WAY/HIGH",				ss_check,	 {.ssarg={ "NAND",	8, "HIGH",	 8,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_ON,       UT_OFF,	 UT_ON	}}},


//{7620,	"SS_NAND UBM/16DQ/1WAY/LOW", 				ss_check,	 {.ssarg={ "NAND",	1, "LOW",	16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7621,	"SS_NAND UBM/16DQ/1WAY/MID",				ss_check,	 {.ssarg={ "NAND",	1, "MID",	16,	   0xF,     5e-9, 	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7622,	"SS_NAND UBM/16DQ/1WAY/HIGH",				ss_check,	 {.ssarg={ "NAND",	1, "HIGH",	16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7620,	"SS_NAND UBM/16DQ/4WAY/LOW",				ss_check,	 {.ssarg={ "NAND",	4, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7621,	"SS_NAND UBM/16DQ/4WAY/MID",				ss_check,	 {.ssarg={ "NAND",	4, "MID",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7622,	"SS_NAND UBM/16DQ/4WAY/HIGH",				ss_check,	 {.ssarg={ "NAND",	4, "HIGH",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7623,	"SS_NAND UBM/16DQ/8WAY/LOW",				ss_check,	 {.ssarg={ "NAND",	8, "LOW",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7624,	"SS_NAND UBM/16DQ/8WAY/MID",				ss_check,	 {.ssarg={ "NAND",	8, "MID",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7625,	"SS_NAND UBM/16DQ/8WAY/HIGH",				ss_check,	 {.ssarg={ "NAND",	8, "HIGH",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},

//{7630,	"SS_NAND UBM/8DQ/1WAY/LOW", 				ss_check,	 {.ssarg={ "NAND",	1, "LOW",	 16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7631,	"SS_NAND UBM/8DQ/1WAY/MID",				ss_check,	 {.ssarg={ "NAND",	1, "MID",	 16,	   0xF,     5e-9, 	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},
//{7632,	"SS_NAND UBM/8DQ/1WAY/HIGH",				ss_check,	 {.ssarg={ "NAND",	1, "HIGH",	 16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7630,	"SS_NAND UBM/8DQ/4WAY/LOW",				ss_check,	 {.ssarg={ "NAND",	4, "LOW",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7631,	"SS_NAND UBM/8DQ/4WAY/MID",				ss_check,	 {.ssarg={ "NAND",	4, "MID",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7632,	"SS_NAND UBM/8DQ/4WAY/HIGH",				ss_check,	 {.ssarg={ "NAND",	4, "HIGH",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_4way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7633,	"SS_NAND UBM/8DQ/8WAY/LOW",				ss_check,	 {.ssarg={ "NAND",	8, "LOW",	 8,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7634,	"SS_NAND UBM/8DQ/8WAY/MID",				ss_check,	 {.ssarg={ "NAND",	8, "MID",	 8,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7635,	"SS_NAND UBM/8DQ/8WAY/HIGH",				ss_check,	 {.ssarg={ "NAND",	8, "HIGH",	 8,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x540,	UT_OFF,      UT_ON,	 UT_ON	}}},


//////////////////////////////
// SS Disable (Edge STRB)   //
//////////////////////////////

{7700,	"SS_DISABLE UBM/-/4WAY/LOW",				ss_check,	 {.ssarg={ "DISABLE",	4, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing2, "pat_ss_4way.mpa",		0x040,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7701,	"SS_DISABLE UBM/-/4WAY/MID",				ss_check,	 {.ssarg={ "DISABLE",	4, "MID",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing2, "pat_ss_4way.mpa",		0x040,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7702,	"SS_DISABLE UBM/-/4WAY/HIGH",				ss_check,	 {.ssarg={ "DISABLE",	4, "HIGH",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing2, "pat_ss_4way.mpa",		0x060,	UT_OFF,      UT_ON,	 UT_ON	}}},

{7703,	"SS_DISABLE UBM/-/8WAY/LOW",				ss_check,	 {.ssarg={ "DISABLE",	8, "LOW",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing2, "pat_ss_8way.mpa",		0x040,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7704,	"SS_DISABLE UBM/-/8WAY/MID",				ss_check,	 {.ssarg={ "DISABLE",	8, "MID",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing2, "pat_ss_8way.mpa",		0x040,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7705,	"SS_DISABLE UBM/-/8WAY/HIGH",				ss_check,	 {.ssarg={ "DISABLE",	8, "HIGH",	16,	   0xF,     0.370e-9,	 UT_ON,	UT_ON,	ss_timing2, "pat_ss_8way.mpa",		0x060,	UT_OFF,      UT_ON,	 UT_ON	}}},

//////////////////////////////////////////////////////////////////////////////// ///////// /////////////// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DQS PhaseAdjust to Per DUT CHECK
//////////////////////////////////////////////////////////////////////////////// ///////// /////////////// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{7750,	"SS_DRAM       AdjustPerDUT/16DQ/8WAY/LOW", ss_pDUTcheck,{.ssarg={ "DRAM"     ,	8, "LOW",	16,	  0x1F,     0.400e-9,	 UT_ON,	UT_ON,	ss_timing3, "pat_ss_8way.mpa",		0x700,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7751,	"SS_DRAM       AdjustPerDUT/ 8DQ/8WAY/LOW", ss_pDUTcheck,{.ssarg={ "DRAM"     ,	8, "LOW",	 8,	  0x1F,     0.400e-9,	 UT_ON,	UT_ON,	ss_timing3, "pat_ss_8way.mpa",		0x700,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7752,	"SS_DRAM(RDEN) AdjustPerDUT/16DQ/8WAY/LOW", ss_pDUTcheck,{.ssarg={ "DRAM_RDEN",	8, "LOW",	16,	  0x1F,     0.400e-9,	 UT_ON,	UT_ON,	ss_timing3, "pat_ss_8way.mpa",		0x700,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7753,	"SS_DRAM(RDEN) AdjustPerDUT/ 8DQ/8WAY/LOW", ss_pDUTcheck,{.ssarg={ "DRAM_RDEN",	8, "LOW",	 8,	  0x1F,     0.400e-9,	 UT_ON,	UT_ON,	ss_timing3, "pat_ss_8way.mpa",		0x700,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7754,	"SS_NAND       AdjustPerDUT/16DQ/8WAY/LOW", ss_pDUTcheck,{.ssarg={ "NAND"     ,	8, "LOW",	16,	  0x1F,     0.400e-9,	 UT_ON,	UT_ON,	ss_timing3, "pat_ss_8way.mpa",		0x740,	UT_OFF,      UT_ON,	 UT_ON	}}},
{7755,	"SS_NAND       AdjustPerDUT/ 8DQ/8WAY/LOW", ss_pDUTcheck,{.ssarg={ "NAND"     ,	8, "LOW",	 8,	  0x1F,     0.400e-9,	 UT_ON,	UT_ON,	ss_timing3, "pat_ss_8way.mpa",		0x740,	UT_OFF,      UT_ON,	 UT_ON	}}},





//////////////////////////////////////////////////////////////////////////////// ///////// /////////////// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SSCHK/SSRST CHECK
//////////////////////////////////////////////////////////////////////////////// ///////// /////////////// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//SSCHK SSRST
{7800,	"SS_DRAM SSCHK-PASS/16DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "DRAM",	8, "LOW",	16,	   0x0,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x800,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7801,	"SS_DRAM SSCHK-FAIL/16DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "DRAM",	8, "LOW",	16,	   0x1,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x820,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7802,	"SS_DRAM SSRST/16DQ/8WAY/LOW",				ss_check,	 {.ssarg={ "DRAM",	8, "LOW",	16,	   0x0,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x840,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7803,	"SS_DRAM OVERFLOW/16DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "DRAM",	8, "LOW",	16,	   0x4,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x860,	UT_OFF,      UT_OFF,	 UT_ON	}}},

{7810,	"SS_DRAM SSCHK-PASS/8DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "DRAM",	8, "LOW",	 8,	   0x0,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x800,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7811,	"SS_DRAM SSCHK-FAIL/8DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "DRAM",	8, "LOW",	 8,	   0x1,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x820,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7812,	"SS_DRAM SSRST/8DQ/8WAY/LOW",				ss_check,	 {.ssarg={ "DRAM",	8, "LOW",	 8,	   0x0,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x840,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7813,	"SS_DRAM OVERFLOW/8DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "DRAM",	8, "LOW",	 8,	   0x4,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x860,	UT_OFF,      UT_OFF,	 UT_ON	}}},

{7820,	"SS_DRAM(RDEN) SSCHK-PASS/16DQ/8WAY/LOW",		ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "LOW",	16,	   0x0,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x800,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7821,	"SS_DRAM(RDEN) SSCHK-FAIL/16DQ/8WAY/LOW",		ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "LOW",	16,	   0x1,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x820,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7822,	"SS_DRAM(RDEN) SSRST/16DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "LOW",	16,	   0x0,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x840,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7823,	"SS_DRAM(RDEN) OVERFLOW/16DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "LOW",	16,	   0x4,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x860,	UT_OFF,      UT_OFF,	 UT_ON	}}},

{7830,	"SS_DRAM(RDEN) SSCHK-PASS/8DQ/8WAY/LOW",		ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "LOW",	 8,	   0x0,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x800,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7831,	"SS_DRAM(RDEN) SSCHK-FAIL/8DQ/8WAY/LOW",		ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "LOW",	 8,	   0x1,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x820,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7832,	"SS_DRAM(RDEN) SSRST/8DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "LOW",	 8,	   0x0,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x840,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7833,	"SS_DRAM(RDEN) OVERFLOW/8DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "DRAM_RDEN",	8, "LOW",	 8,	   0x4,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x860,	UT_OFF,      UT_OFF,	 UT_ON	}}},

{7840,	"SS_NAND SSCHK-PASS/16DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "NAND",	8, "LOW",	16,	   0x0,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x900,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7841,	"SS_NAND SSCHK-FAIL/16DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "NAND",	8, "LOW",	16,	   0x1,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x920,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7842,	"SS_NAND SSRST/16DQ/8WAY/LOW",				ss_check,	 {.ssarg={ "NAND",	8, "LOW",	16,	   0x0,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x940,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7843,	"SS_NAND OVERFLOW/16DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "NAND",	8, "LOW",	16,	   0x4,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x960,	UT_OFF,      UT_OFF,	 UT_ON	}}},

{7850,	"SS_NAND SSCHK-PASS/8DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "NAND",	8, "LOW",	 8,	   0x0,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x900,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7851,	"SS_NAND SSCHK-FAIL/8DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "NAND",	8, "LOW",	 8,	   0x1,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x920,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7852,	"SS_NAND SSRST/8DQ/8WAY/LOW",				ss_check,	 {.ssarg={ "NAND",	8, "LOW",	 8,	   0x0,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x940,	UT_OFF,      UT_OFF,	 UT_ON	}}},
{7853,	"SS_NAND OVERFLOW/8DQ/8WAY/LOW",			ss_check,	 {.ssarg={ "NAND",	8, "LOW",	 8,	   0x4,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x960,	UT_OFF,      UT_OFF,	 UT_ON	}}},


//Edge STRB CHECK
//{7890,	"SS_Edge STRB CHECK 1WAY",				ss_check,	 {.ssarg={ "DISABLE",	1, "MID",	16,	   0xF,     100e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x990,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7890,	"SS_Edge STRB CHECK 1WAY",				ss_check,	 {.ssarg={ "DISABLE",	1, "MID",	16,	   0xF,     5e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_1way.mpa",		0x990,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7891,	"SS_Edge STRB CHECK 8WAY",				ss_check,	 {.ssarg={ "DISABLE",	8, "MID",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x990,	UT_OFF,      UT_OFF,	 UT_OFF	}}},



//////////////////////////////////////////////////////////////////////////////// ///////// /////////////// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SHMOO CHECK
//////////////////////////////////////////////////////////////////////////////// ///////// /////////////// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////
//DRAM (No RDEN) SS4  //
////////////////////////

//SHM (PhaseAdjust-VO)
////minimum data
//{7900,	"SS_DRAM SHM(DQSTRB-VO)/16DQ/8WAY/LOW",			ss_SHMcheck,	 {.ssarg={ "DRAM",	8, "LOW",	16,	   0xF,     0.714e-9, 	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7901,	"SS_DRAM SHM(DQSTRB-VO)/16DQ/8WAY/MID",			ss_SHMcheck,	 {.ssarg={ "DRAM",	8, "MID",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7902,	"SS_DRAM SHM(DQSTRB-VO)/16DQ/8WAY/HIGH",		ss_SHMcheck,	 {.ssarg={ "DRAM",	8, "HIGH",	16,	   0xF,     0.714e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x020,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7903,	"SS_DRAM SHM(DQSTRB-VO)/8DQ/8WAY/LOW",			ss_SHMcheck,	 {.ssarg={ "DRAM",	8, "LOW",	 16,	   0xF,     0.714e-9, 	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7904,	"SS_DRAM SHM(DQSTRB-VO)/8DQ/8WAY/MID",			ss_SHMcheck,	 {.ssarg={ "DRAM",	8, "MID",	 16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7905,	"SS_DRAM SHM(DQSTRB-VO)/8DQ/8WAY/HIGH",			ss_SHMcheck,	 {.ssarg={ "DRAM",	8, "HIGH",	 16,	   0xF,     0.714e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x020,	UT_OFF,      UT_OFF,	 UT_OFF	}}},

////18k data        
{7900,	"SS_DRAM SHM(DQSTRB-VO)18k/16DQ/4WAY/LOW",		ss_SHMcheck,	 {.ssarg={ "DRAM",	4, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7901,	"SS_DRAM SHM(DQSTRB-VO)18k/16DQ/4WAY/MID",		ss_SHMcheck,	 {.ssarg={ "DRAM",	4, "MID",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7902,	"SS_DRAM SHM(DQSTRB-VO)18k/16DQ/4WAY/HIGH",		ss_SHMcheck,	 {.ssarg={ "DRAM",	4, "HIGH",	16,	   0xF,     0.714e-9,	UT_OFF, UT_ON,	ss_timing1, "pat_ss_18k_4way_hterm.mpa",0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7903,	"SS_DRAM SHM(DQSTRB-VO)18k/8DQ/4WAY/LOW",		ss_SHMcheck,	 {.ssarg={ "DRAM",	4, "LOW",	 8,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7904,	"SS_DRAM SHM(DQSTRB-VO)18k/8DQ/4WAY/MID",		ss_SHMcheck,	 {.ssarg={ "DRAM",	4, "MID",	 8,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7905,	"SS_DRAM SHM(DQSTRB-VO)18k/8DQ/4WAY/HIGH",		ss_SHMcheck,	 {.ssarg={ "DRAM",	4, "HIGH",	 8,	   0xF,     0.714e-9,	UT_OFF, UT_ON,	ss_timing1, "pat_ss_18k_4way_hterm.mpa",0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},

{7910,	"SS_DRAM SHM(DQSTRB-VO)18k/16DQ/8WAY/LOW",		ss_SHMcheck,	 {.ssarg={ "DRAM",	8, "LOW",	16,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7911,	"SS_DRAM SHM(DQSTRB-VO)18k/16DQ/8WAY/MID",		ss_SHMcheck,	 {.ssarg={ "DRAM",	8, "MID",	16,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7912,	"SS_DRAM SHM(DQSTRB-VO)18k/16DQ/8WAY/HIGH",		ss_SHMcheck,	 {.ssarg={ "DRAM",	8, "HIGH",	16,	   0xF,     0.370e-9,	UT_OFF, UT_ON,	ss_timing1, "pat_ss_18k_8way_hterm.mpa",0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7913,	"SS_DRAM SHM(DQSTRB-VO)18k/8DQ/8WAY/LOW",		ss_SHMcheck,	 {.ssarg={ "DRAM",	8, "LOW",	 8,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7914,	"SS_DRAM SHM(DQSTRB-VO)18k/8DQ/8WAY/MID",		ss_SHMcheck,	 {.ssarg={ "DRAM",	8, "MID",	 8,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7915,	"SS_DRAM SHM(DQSTRB-VO)18k/8DQ/8WAY/HIGH",		ss_SHMcheck,	 {.ssarg={ "DRAM",	8, "HIGH",	 8,	   0xF,     0.370e-9,	UT_OFF, UT_ON,	ss_timing1, "pat_ss_18k_8way_hterm.mpa",0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},


//SHM (DQS Edge-VO)
////minmum data
//{7910,	"SS_DRAM SHM(DQS Edge-VO)/16DQ/8WAY/LOW",		ss_SHMcheck_DQS, {.ssarg={ "DRAM",	8, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x750,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7911,	"SS_DRAM SHM(DQS Edge-VO)/16DQ/8WAY/MID",		ss_SHMcheck_DQS, {.ssarg={ "DRAM",	8, "MID",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x700,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7912,	"SS_DRAM SHM(DQS Edge-VO)/16DQ/8WAY/HIGH",		ss_SHMcheck_DQS, {.ssarg={ "DRAM",	8, "HIGH",	16,	   0xF,     0.714e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x700,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7913,	"SS_DRAM SHM(DQS Edge-VO)/8DQ/8WAY/LOW",		ss_SHMcheck_DQS, {.ssarg={ "DRAM",	8, "LOW",	 16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x750,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7914,	"SS_DRAM SHM(DQS Edge-VO)/8DQ/8WAY/MID",		ss_SHMcheck_DQS, {.ssarg={ "DRAM",	8, "MID",	 16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x700,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7915,	"SS_DRAM SHM(DQS Edge-VO)/8DQ/8WAY/HIGH",		ss_SHMcheck_DQS, {.ssarg={ "DRAM",	8, "HIGH",	 16,	   0xF,     0.714e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x700,	UT_OFF,      UT_OFF,	 UT_OFF	}}},

////18k data
//{7910,	"SS_DRAM SHM(DQS Edge-VO)18k/16DQ/8WAY/LOW",		ss_SHMcheck_DQS, {.ssarg={ "DRAM",	8, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7911,	"SS_DRAM SHM(DQS Edge-VO)18k/16DQ/8WAY/MID",		ss_SHMcheck_DQS, {.ssarg={ "DRAM",	8, "MID",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7912,	"SS_DRAM SHM(DQS Edge-VO)18k/16DQ/8WAY/HIGH",		ss_SHMcheck_DQS, {.ssarg={ "DRAM",	8, "HIGH",	16,	   0xF,     0.714e-9,	UT_OFF, UT_ON,	ss_timing1, "pat_ss_18k_8way_hterm.mpa",0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7913,	"SS_DRAM SHM(DQS Edge-VO)18k/8DQ/8WAY/LOW",		ss_SHMcheck_DQS, {.ssarg={ "DRAM",	8, "LOW",	 8,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7914,	"SS_DRAM SHM(DQS Edge-VO)18k/8DQ/8WAY/MID",		ss_SHMcheck_DQS, {.ssarg={ "DRAM",	8, "MID",	 8,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7915,	"SS_DRAM SHM(DQS Edge-VO)18k/8DQ/8WAY/HIGH",		ss_SHMcheck_DQS, {.ssarg={ "DRAM",	8, "HIGH",	 8,	   0xF,     0.714e-9,	UT_OFF, UT_ON,	ss_timing1, "pat_ss_18k_8way_hterm.mpa",0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},



///////////////////////
//  DRAM (RDEN) SS4  //
///////////////////////

//SHM (PhaseAdjust-VO)
////minimum data
//{7920,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)/16DQ/8WAY/LOW",		ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	8, "LOW",	16,	   0xF,     0.714e-9, 	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7921,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)/16DQ/8WAY/MID",		ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	8, "MID",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7922,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)/16DQ/8WAY/HIGH",		ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	8, "HIGH",	16,	   0xF,     0.714e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x020,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7923,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)/8DQ/8WAY/LOW",		ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	8, "LOW",	 16,	   0xF,     0.714e-9, 	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7924,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)/8DQ/8WAY/MID",		ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	8, "MID",	 16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7925,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)/8DQ/8WAY/HIGH",		ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	8, "HIGH",	 16,	   0xF,     0.714e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x020,	UT_OFF,      UT_OFF,	 UT_OFF	}}},

////18k data        
{7920,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)18k/16DQ/4WAY/LOW",	ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	4, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7921,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)18k/16DQ/4WAY/MID",	ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	4, "MID",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7922,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)18k/16DQ/4WAY/HIGH",	ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	4, "HIGH",	16,	   0xF,     0.714e-9,	UT_OFF, UT_ON,	ss_timing1, "pat_ss_18k_4way_hterm.mpa",0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7923,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)18k/8DQ/4WAY/LOW",		ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	4, "LOW",	 8,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7924,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)18k/8DQ/4WAY/MID",		ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	4, "MID",	 8,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7925,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)18k/8DQ/4WAY/HIGH",	ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	4, "HIGH",	 8,	   0xF,     0.714e-9,	UT_OFF, UT_ON,	ss_timing1, "pat_ss_18k_4way_hterm.mpa",0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},

{7930,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)18k/16DQ/8WAY/LOW",	ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	8, "LOW",	16,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7931,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)18k/16DQ/8WAY/MID",	ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	8, "MID",	16,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7932,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)18k/16DQ/8WAY/HIGH",	ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	8, "HIGH",	16,	   0xF,     0.370e-9,	UT_OFF, UT_ON,	ss_timing1, "pat_ss_18k_8way_hterm.mpa",0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7933,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)18k/8DQ/8WAY/LOW",		ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	8, "LOW",	 8,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7934,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)18k/8DQ/8WAY/MID",		ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	8, "MID",	 8,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7935,	"SS_DRAM(RDEN) SHM(DQSTRB-VO)18k/8DQ/8WAY/HIGH",	ss_SHMcheck,	 {.ssarg={ "DRAM_RDEN",	8, "HIGH",	 8,	   0xF,     0.370e-9,	UT_OFF, UT_ON,	ss_timing1, "pat_ss_18k_8way_hterm.mpa",0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},


//SHM (DQS Edge-VO)
////minmum data
//{7930,	"SS_DRAM(RDEN) SHM(DQS Edge-VO)/16DQ/8WAY/LOW",		ss_SHMcheck_DQS, {.ssarg={ "DRAM_RDEN",	8, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7931,	"SS_DRAM(RDEN) SHM(DQS Edge-VO)/16DQ/8WAY/MID",		ss_SHMcheck_DQS, {.ssarg={ "DRAM_RDEN",	8, "MID",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7932,	"SS_DRAM(RDEN) SHM(DQS Edge-VO)/16DQ/8WAY/HIGH",	ss_SHMcheck_DQS, {.ssarg={ "DRAM_RDEN",	8, "HIGH",	16,	   0xF,     0.714e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x020,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7933,	"SS_DRAM(RDEN) SHM(DQS Edge-VO)/8DQ/8WAY/LOW",		ss_SHMcheck_DQS, {.ssarg={ "DRAM_RDEN",	8, "LOW",	 16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7934,	"SS_DRAM(RDEN) SHM(DQS Edge-VO)/8DQ/8WAY/MID",		ss_SHMcheck_DQS, {.ssarg={ "DRAM_RDEN",	8, "MID",	 16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7935,	"SS_DRAM(RDEN) SHM(DQS Edge-VO)/8DQ/8WAY/HIGH",		ss_SHMcheck_DQS, {.ssarg={ "DRAM_RDEN",	8, "HIGH",	 16,	   0xF,     0.714e-9,	UT_OFF,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x020,	UT_OFF,      UT_OFF,	 UT_OFF	}}},

////18k data
//{7930,	"SS_DRAM(RDEN) SHM(DQS Edge-VO)18k/16DQ/8WAY/LOW",	ss_SHMcheck_DQS, {.ssarg={ "DRAM_RDEN",	8, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7931,	"SS_DRAM(RDEN) SHM(DQS Edge-VO)18k/16DQ/8WAY/MID",	ss_SHMcheck_DQS, {.ssarg={ "DRAM_RDEN",	8, "MID",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7932,	"SS_DRAM(RDEN) SHM(DQS Edge-VO)18k/16DQ/8WAY/HIGH",	ss_SHMcheck_DQS, {.ssarg={ "DRAM_RDEN",	8, "HIGH",	16,	   0xF,     0.714e-9,	UT_OFF, UT_ON,	ss_timing1, "pat_ss_18k_8way_hterm.mpa",0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7933,	"SS_DRAM(RDEN) SHM(DQS Edge-VO)18k/8DQ/8WAY/LOW",	ss_SHMcheck_DQS, {.ssarg={ "DRAM_RDEN",	8, "LOW",	 8,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7934,	"SS_DRAM(RDEN) SHM(DQS Edge-VO)18k/8DQ/8WAY/MID",	ss_SHMcheck_DQS, {.ssarg={ "DRAM_RDEN",	8, "MID",	 8,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7935,	"SS_DRAM(RDEN) SHM(DQS Edge-VO)18k/8DQ/8WAY/HIGH",	ss_SHMcheck_DQS, {.ssarg={ "DRAM_RDEN",	8, "HIGH",	 8,	   0xF,     0.714e-9,	UT_OFF, UT_ON,	ss_timing1, "pat_ss_18k_8way_hterm.mpa",0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},



///////////////////////
//  NAND  SS1        //
///////////////////////

//SHM (PhaseAdjust-VO)

//minimum data
//{7940,	"SS_NAND SHM(DQSTRB-VO)/16DQ/8WAY/LOW",			ss_SHMcheck,	 {.ssarg={ "NAND",	8, "LOW",	16,	   0xF,     0.714e-9, 	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7941,	"SS_NAND SHM(DQSTRB-VO)/16DQ/8WAY/MID",			ss_SHMcheck,	 {.ssarg={ "NAND",	8, "MID",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7942,	"SS_NAND SHM(DQSTRB-VO)/16DQ/8WAY/HIGH",		ss_SHMcheck,	 {.ssarg={ "NAND",	8, "HIGH",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7943,	"SS_NAND SHM(DQSTRB-VO)/8DQ/8WAY/LOW",			ss_SHMcheck,	 {.ssarg={ "NAND",	8, "LOW",	 8,	   0xF,     0.714e-9, 	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7944,	"SS_NAND SHM(DQSTRB-VO)/8DQ/8WAY/MID",			ss_SHMcheck,	 {.ssarg={ "NAND",	8, "MID",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7945,	"SS_NAND SHM(DQSTRB-VO)/8DQ/8WAY/HIGH",			ss_SHMcheck,	 {.ssarg={ "NAND",	8, "HIGH",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_OFF,      UT_OFF,	 UT_OFF	}}},

////18k data        
{7940,	"SS_NAND SHM(DQSTRB-VO)18k/16DQ/4WAY/LOW",		ss_SHMcheck,	 {.ssarg={ "NAND",	4, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7941,	"SS_NAND SHM(DQSTRB-VO)18k/16DQ/4WAY/MID",		ss_SHMcheck,	 {.ssarg={ "NAND",	4, "MID",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7942,	"SS_NAND SHM(DQSTRB-VO)18k/16DQ/4WAY/HIGH",		ss_SHMcheck,	 {.ssarg={ "NAND",	4, "HIGH",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7943,	"SS_NAND SHM(DQSTRB-VO)18k/8DQ/4WAY/LOW",		ss_SHMcheck,	 {.ssarg={ "NAND",	4, "LOW",	 8,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7944,	"SS_NAND SHM(DQSTRB-VO)18k/8DQ/4WAY/MID",		ss_SHMcheck,	 {.ssarg={ "NAND",	4, "MID",	 8,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7945,	"SS_NAND SHM(DQSTRB-VO)18k/8DQ/4WAY/HIGH",		ss_SHMcheck,	 {.ssarg={ "NAND",	4, "HIGH",	 8,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},

{7950,	"SS_NAND SHM(DQSTRB-VO)18k/16DQ/8WAY/LOW",		ss_SHMcheck,	 {.ssarg={ "NAND",	8, "LOW",	16,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7951,	"SS_NAND SHM(DQSTRB-VO)18k/16DQ/8WAY/MID",		ss_SHMcheck,	 {.ssarg={ "NAND",	8, "MID",	16,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7952,	"SS_NAND SHM(DQSTRB-VO)18k/16DQ/8WAY/HIGH",		ss_SHMcheck,	 {.ssarg={ "NAND",	8, "HIGH",	16,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7953,	"SS_NAND SHM(DQSTRB-VO)18k/8DQ/8WAY/LOW",		ss_SHMcheck,	 {.ssarg={ "NAND",	8, "LOW",	 8,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7954,	"SS_NAND SHM(DQSTRB-VO)18k/8DQ/8WAY/MID",		ss_SHMcheck,	 {.ssarg={ "NAND",	8, "MID",	 8,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7955,	"SS_NAND SHM(DQSTRB-VO)18k/8DQ/8WAY/HIGH",		ss_SHMcheck,	 {.ssarg={ "NAND",	8, "HIGH",	 8,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},


//SHM (DQS Edge-VO)

//minmum data
//{7950,	"SS_NAND SHM(DQS Edge-VO)/16DQ/8WAY/LOW",		ss_SHMcheck_DQS, {.ssarg={ "NAND",	8, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7951,	"SS_NAND SHM(DQS Edge-VO)/16DQ/8WAY/MID",		ss_SHMcheck_DQS, {.ssarg={ "NAND",	8, "MID",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7952,	"SS_NAND SHM(DQS Edge-VO)/16DQ/8WAY/HIGH",		ss_SHMcheck_DQS, {.ssarg={ "NAND",	8, "HIGH",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7953,	"SS_NAND SHM(DQS Edge-VO)/8DQ/8WAY/LOW",		ss_SHMcheck_DQS, {.ssarg={ "NAND",	8, "LOW",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7954,	"SS_NAND SHM(DQS Edge-VO)/8DQ/8WAY/MID",		ss_SHMcheck_DQS, {.ssarg={ "NAND",	8, "MID",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7955,	"SS_NAND SHM(DQS Edge-VO)/8DQ/8WAY/HIGH",		ss_SHMcheck_DQS, {.ssarg={ "NAND",	8, "HIGH",	 8,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_OFF,      UT_OFF,	 UT_OFF	}}},

////18k data
//{7950,	"SS_NAND SHM(DQS Edge-VO)18k/16DQ/8WAY/LOW",		ss_SHMcheck_DQS, {.ssarg={ "NAND",	8, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7951,	"SS_NAND SHM(DQS Edge-VO)18k/16DQ/8WAY/MID",		ss_SHMcheck_DQS, {.ssarg={ "NAND",	8, "MID",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7952,	"SS_NAND SHM(DQS Edge-VO)18k/16DQ/8WAY/HIGH",		ss_SHMcheck_DQS, {.ssarg={ "NAND",	8, "HIGH",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7953,	"SS_NAND SHM(DQS Edge-VO)18k/8DQ/8WAY/LOW",		ss_SHMcheck_DQS, {.ssarg={ "NAND",	8, "LOW",	 8,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7954,	"SS_NAND SHM(DQS Edge-VO)18k/8DQ/8WAY/MID",		ss_SHMcheck_DQS, {.ssarg={ "NAND",	8, "MID",	 8,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7955,	"SS_NAND SHM(DQS Edge-VO)18k/8DQ/8WAY/HIGH",		ss_SHMcheck_DQS, {.ssarg={ "NAND",	8, "HIGH",	 8,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way_nand.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},




//////////////////////////////
// SS Disable (Edge STRB)   //
//////////////////////////////

//SHM (PhaseAdjust-VO)
////minimum data
//{7960,	"SS_DISABLE SHM(DQSTRB-VO)/-/8WAY/LOW",			ss_SHMcheck,	 {.ssarg={ "DISABLE",	8, "LOW",	16,	   0xF,     0.714e-9, 	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7961,	"SS_DISABLE SHM(DQSTRB-VO)/-/8WAY/MID",			ss_SHMcheck,	 {.ssarg={ "DISABLE",	8, "MID",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7962,	"SS_DISABLE SHM(DQSTRB-VO)/-/8WAY/HIGH",		ss_SHMcheck,	 {.ssarg={ "DISABLE",	8, "HIGH",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x520,	UT_OFF,      UT_OFF,	 UT_OFF	}}},

////18k data        
{7960,	"SS_DISABLE SHM(DQSTRB-VO)18k/-/4WAY/LOW",		ss_SHMcheck,	 {.ssarg={ "DISABLE",	4, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7961,	"SS_DISABLE SHM(DQSTRB-VO)18k/-/4WAY/MID",		ss_SHMcheck,	 {.ssarg={ "DISABLE",	4, "MID",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7962,	"SS_DISABLE SHM(DQSTRB-VO)18k/-/4WAY/HIGH",		ss_SHMcheck,	 {.ssarg={ "DISABLE",	4, "HIGH",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way_hterm.mpa",0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7963,	"SS_DISABLE SHM(DQSTRB-VO)18k/-/4WAY/LOW",		ss_SHMcheck,	 {.ssarg={ "DISABLE",	4, "LOW",	16,	   0xF,     0.833e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_4way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},

{7970,	"SS_DISABLE SHM(DQSTRB-VO)18k/-/8WAY/LOW",		ss_SHMcheck,	 {.ssarg={ "DISABLE",	8, "LOW",	16,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7971,	"SS_DISABLE SHM(DQSTRB-VO)18k/-/8WAY/MID",		ss_SHMcheck,	 {.ssarg={ "DISABLE",	8, "MID",	16,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
{7972,	"SS_DISABLE SHM(DQSTRB-VO)18k/-/8WAY/HIGH",		ss_SHMcheck,	 {.ssarg={ "DISABLE",	8, "HIGH",	16,	   0xF,     0.370e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way_hterm.mpa",0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},


//SHM (DQS Edge-VO)
////minmum data
//{7970,	"SS_DISABLE SHM(DQS Edge-VO)/-/8WAY/LOW",		ss_SHMcheck_DQS, {.ssarg={ "DISABLE",	8, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7971,	"SS_DISABLE SHM(DQS Edge-VO)/-/8WAY/MID",		ss_SHMcheck_DQS, {.ssarg={ "DISABLE",	8, "MID",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x500,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7972,	"SS_DISABLE SHM(DQS Edge-VO)/-/8WAY/HIGH",		ss_SHMcheck_DQS, {.ssarg={ "DISABLE",	8, "HIGH",	16,	   0xF,     0.714e-9,	 UT_ON,	UT_ON,	ss_timing1, "pat_ss_8way.mpa",		0x520,	UT_OFF,      UT_OFF,	 UT_OFF	}}},

////18k data
//{7970,	"SS_DISABLE SHM(DQS Edge-VO)18k/-/8WAY/LOW",		ss_SHMcheck_DQS, {.ssarg={ "DISABLE",	8, "LOW",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7971,	"SS_DISABLE SHM(DQS Edge-VO)18k/-/8WAY/MID",		ss_SHMcheck_DQS, {.ssarg={ "DISABLE",	8, "MID",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way.mpa",	0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},
//{7972,	"SS_DISABLE SHM(DQS Edge-VO)18k/-/8WAY/HIGH",		ss_SHMcheck_DQS, {.ssarg={ "DISABLE",	8, "HIGH",	16,	   0xF,     0.714e-9,	 UT_ON, UT_ON,	ss_timing1, "pat_ss_18k_8way_hterm.mpa",0x000,	UT_OFF,      UT_OFF,	 UT_OFF	}}},

