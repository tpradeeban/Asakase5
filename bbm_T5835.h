#ifndef ___TEST_BBM_H_
#define ___TEST_BBM_H_

extern void bbm_init  (void);
extern void bbm_write (TEST_testitem *testarg);
extern void bbm_test_1(TEST_testitem *testarg);
extern void bbm_test_2(TEST_testitem *testarg);
extern void bbm_test_3(TEST_testitem *testarg);
extern void bbm_test_4(TEST_testitem *testarg);
extern void bbm_test_9(TEST_testitem *testarg);
extern void bbm_test_5(TEST_testitem *testarg);
extern void bbm_test_7(TEST_testitem *testarg);
extern void bbm_test_6(TEST_testitem *testarg);
extern void bbm_test_d1(TEST_testitem *testarg);
extern void bbm_test_d2(TEST_testitem *testarg);

extern void JudgeAllPF(TEST_bbmarg bbmarg);
extern void JudgeHalfPass(TEST_bbmarg bbmarg);
extern void JudgeEcc(TEST_bbmarg bbmarg);
extern void JudgeAftrEcc(TEST_bbmarg bbmarg);
extern void JudgeOddDutPass(TEST_bbmarg bbmarg);
extern void NoJudge(TEST_bbmarg bbmarg);
extern void JudgeDrMask(TEST_bbmarg bbmarg);
extern void JudgeDrMask2(TEST_bbmarg bbmarg);
void JudgeLmt(TEST_bbmarg bbmarg);

#endif // ___TEST_BBM_H_

