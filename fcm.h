#ifndef ___TEST_FCM_H_
#define ___TEST_FCM_H_
#define FMBLKBIT (32) // fm bit block size = 32bit

extern void set_result(UT_DUT dut, int result);
extern CheckButton is_captured(TEST_testitem *testarg, UT_DUT dut);
extern void fcm_check(TEST_testitem *testarg);
extern void fcm_pin_std(TEST_testitem *testarg);
extern void fcm_pin_pfc(TEST_testitem *testarg);
extern void fcm_pin_fcsm(TEST_testitem *testarg);
extern void fcm_config_std(TEST_testitem *testarg);
extern void fcm_config_std_or_cfm(TEST_testitem *testarg);
extern void fcm_reg_std(TEST_testitem *testarg);
extern void fcm_reg_fifo(TEST_testitem *testarg);
extern void fcm_reg_burst(TEST_testitem *testarg);
extern void fcm_config_pfc(TEST_testitem *testarg);
extern void fcm_config_pfc2(TEST_testitem *testarg);
extern void fcm_read_check_ckbd(TEST_testitem *testarg);
extern void fcm_read_check_ckbd_bar(TEST_testitem *testarg);
extern void fcm_read_check_allfail(TEST_testitem *testarg);
extern void fcm_read_check_allpass(TEST_testitem *testarg);
extern void fcm_preset_all0_check(TEST_testitem *testarg);
extern void fcm_preset_all1_check(TEST_testitem *testarg);
extern void fcm_preset_inuse0_check(TEST_testitem *testarg);
extern void fcm_preset_inuse1_check(TEST_testitem *testarg);
extern void fcm_count_check(TEST_testitem *testarg);
extern void fcm_delay_check(TEST_testitem *testarg);
extern void fcm_search_check(TEST_testitem *testarg);
extern void fcm_pfc_check(TEST_testitem *testarg);
extern void fcm_pfc_no_clear_check(TEST_testitem *testarg);
extern void fcm_pfc_div_check(TEST_testitem *testarg);
extern void fcm_pfc_time_check(TEST_testitem *testarg);
extern void fcm_preset_time_check(TEST_testitem *testarg);
extern void fcm_fcsm_set(TEST_testitem *testarg);
extern void fcm_fcsm_check(TEST_testitem *testarg);
extern void fcm_fcsm_multimeas_check(TEST_testitem *testarg);
extern void fcm_perdut_set(TEST_testitem *testarg);
extern void fcm_read_check_perdut(TEST_testitem *testarg);
extern void fcm_count_check_perdut(TEST_testitem *testarg);
extern void fcm_pfc_check_perdut(TEST_testitem *testarg);

#endif // ___TEST_FCM_H_

