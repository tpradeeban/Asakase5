#ifndef ___TEST_MPSEL_H_
#define ___TEST_MPSEL_H_

extern void mpsel_test1  (TEST_testitem *testarg);
extern void mpsel_test2  (TEST_testitem *testarg);
extern void mpsel_test3  (TEST_testitem *testarg);
extern void mpsel_idx    (TEST_testitem *testarg);
extern void mpsel_isp    (TEST_testitem *testarg);
extern void mpsel_cflg   (TEST_testitem *testarg);
extern void mpsel_loop   (TEST_testitem *testarg);
extern void mpsel_subr   (TEST_testitem *testarg);
extern void mpsel_wait   (TEST_testitem *testarg);
extern void mpsel_calm   (TEST_testitem *testarg);
extern void mpsel_debug  (TEST_testitem *testarg);
extern void mpsel_flgj1  (TEST_testitem *testarg);
extern void mpsel_measfct(TEST_testitem *testarg);
extern void mpsel_startfct(TEST_testitem *testarg);

extern void StartAlpg();
extern void ReadPc(int exp_p, int i);
extern void ReadIsp(int exp_p, int i);
extern void JudgeTime(int fcttype, int dummy);

extern void TmStartFct();
extern void TmMeasFct();
#endif // ___TEST_MPSEL_H_

