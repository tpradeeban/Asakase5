#ifndef ___TEST_JITTER_H_
#define ___TEST_JITTER_H_

extern void jitter_timing(TEST_testitem *testarg, DSlider offset);
extern void jitter_wstrb_timing(TEST_testitem *testarg, DSlider offset);
extern void jitter_ss_tgset(TEST_testitem *testarg);
extern void jitter_sssc_tgset(TEST_testitem *testarg);
extern void jitter_sssc_timing(TEST_testitem *testarg, DSlider offset);
extern void jitter_ss_timing(TEST_testitem *testarg, DSlider offset);
extern void jitter_pincond(TEST_testitem *testarg, RadioButton pdsa, RadioButton pdsb);
extern void jitter_wstrb_pincond(TEST_testitem *testarg, RadioButton pdsa, RadioButton pdsb);
extern void jitter_ss_pincond(TEST_testitem *testarg, RadioButton pdsa, RadioButton pdsb);
extern void jitter_sssc_pincond(TEST_testitem *testarg, RadioButton pdsa, RadioButton pdsb);
extern void jitter_sssc_edge_pincond(TEST_testitem *testarg, RadioButton pdsa, RadioButton pdsb);
extern void jitter_level(TEST_testitem *testarg, DSlider offset);
extern void jitter_pinlist(RadioButton dutpin);
extern void jitter_sssc_pinlist(RadioButton dutpin);
extern void jitter_sssc_edge_pinlist(RadioButton dutpin);
extern void jitter_ss_pinlist(RadioButton dutpin);
extern void jitter_check(TEST_testitem *testarg);
extern void amp_check(TEST_testitem *testarg);
extern void drift_check(TEST_testitem *testarg);

#endif // ___TEST_JITTER_H_

