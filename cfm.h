#ifndef ___TEST_CFM_H_
#define ___TEST_CFM_H_

extern void fcm_config_cfm(TEST_testitem *testarg);
extern void cfm_read_check_ckbd(TEST_testitem *testarg);
extern void cfm_read_check_ckbd_bar(TEST_testitem *testarg);
extern void cfm_read_check_allfail(TEST_testitem *testarg);
extern void cfm_read_check_allpass(TEST_testitem *testarg);
extern void cfm_preset_all0_check(TEST_testitem *testarg);
extern void cfm_preset_all1_check(TEST_testitem *testarg);
extern void cfm_count_check(TEST_testitem *testarg);
extern void cfm_read_check_perdut(TEST_testitem *testarg);
extern void cfm_count_check_perdut(TEST_testitem *testarg);

#endif // ___TEST_CFM_H_

