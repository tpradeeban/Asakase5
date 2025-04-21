#ifndef ___TEST_FBGSYNC_H_
#define ___TEST_FBGSYNC_H_

void common_pg                 (TEST_testitem *testarg);
void outsync                   (TEST_testitem *testarg);
void outsync_8grp              (TEST_testitem *testarg);
void outsync_wave              (TEST_testitem *testarg);
void outsync_multi             (TEST_testitem *testarg);
void outsync_rej_1             (TEST_testitem *testarg);
void outsync_rej_3             (TEST_testitem *testarg);
void outsync_match             (TEST_testitem *testarg);
void outsync_sel               (TEST_testitem *testarg);

void meas_fct_per_group        (TEST_fbgarg fbgarg);
void meas_fct_per_group_mpatsel(TEST_fbgarg fbgarg);
void shmoo                     (TEST_fbgarg fbgarg);
void shmoo_range               (TEST_fbgarg fbgarg);
void shmoo_range_mpatsel       (TEST_fbgarg fbgarg);
void match_shmoo_check_teibai  (TEST_fbgarg fbgarg);
void shmoo_check_teibai        (TEST_fbgarg fbgarg);
void shmoo_check               (TEST_fbgarg fbgarg);
void shmoo_check_reject        (TEST_fbgarg fbgarg);
void shmoo_check_allpass       (TEST_fbgarg fbgarg);
void shmoo_check_allfail       (TEST_fbgarg fbgarg);
void expPASS                   (TEST_fbgarg fbgarg);
void expFAIL                   (TEST_fbgarg fbgarg);
void regcheck                  (TEST_fbgarg fbgarg);
void expPASS_regcheck          (TEST_fbgarg fbgarg);
void expFAIL_regcheck          (TEST_fbgarg fbgarg);
void shmoo_range_1pg           (TEST_fbgarg fbgarg);
void shmoo_range_CALM          (TEST_fbgarg fbgarg);
void shmoo_range_DBM           (TEST_fbgarg fbgarg);

#define PINMAX 16
#define	BITMAX	16
#define	DUTMAX	256
#define	SECTOR_MAX	1024
#define	PAGE_MAX	64
#define FBGMAX	8

extern int grp8[FBGMAX];
extern int grp2[FBGMAX];
extern int grp2b[FBGMAX];

extern DSlider FBGrate[25];
extern DSlider FBGrate2[25];
extern DSlider FBGrate3[25];
extern DSlider FBGrate0[25];
extern DSlider FBGrateT[25];
extern DSlider FBGrateM[25];

extern  char*pat2[FBGMAX];
extern	char*pat1[FBGMAX];
extern	char*pat8[FBGMAX];
extern	int   pc1[FBGMAX];
extern	int   pc000[FBGMAX];
extern	int   pc100[FBGMAX];
extern	int   pc200[FBGMAX];
extern	int   pc240[FBGMAX];
extern	int   pc300[FBGMAX];
extern	int   pc340[FBGMAX];
extern	int   pc380[FBGMAX];
extern	int   pc3C0[FBGMAX];
extern	int   pc400[FBGMAX];
extern	int   pc440[FBGMAX];
extern	int   pc480[FBGMAX];
extern	int   pc500[FBGMAX];
extern	int   pc550[FBGMAX];
extern	int   pc600[FBGMAX];
extern	int   pc700[FBGMAX];
extern	int   pc800[FBGMAX];
extern	int   pc900[FBGMAX];
extern	int   pcA00[FBGMAX];

extern	int   pc10[FBGMAX];
extern	int   pc20[FBGMAX];
extern	int   pc30[FBGMAX];
extern	int   pc40[FBGMAX];
extern	int   pc50[FBGMAX];
extern	int   pc60[FBGMAX];
extern	int   pc70[FBGMAX];
extern	int   pc80[FBGMAX];
extern	int   pc90[FBGMAX];
extern	int   pcA0[FBGMAX];
extern	int   pcB0[FBGMAX];
extern	int   pcC0[FBGMAX];
extern	int   pcD0[FBGMAX];

extern	char*adj0[FBGMAX];
extern	char*pat0[FBGMAX];
extern	char*patI[FBGMAX];
extern	char*pat3[FBGMAX];
extern	char*patH[FBGMAX];
extern	char*patM[FBGMAX];
extern	char*null[FBGMAX];
extern	int   pc0[FBGMAX];

#endif // ___TEST_FBGSYNC_H_
