#ifndef ___TEST_CRC_H_
#define ___TEST_CRC_H_

extern void crc_pin_ddr4(TEST_testitem *testarg);
extern void crc_pin_gddr5(TEST_testitem *testarg);
extern void crc_pin_ddr5(TEST_testitem *testarg);
extern void ecc_pin_lpddr5(TEST_testitem *testarg);
extern USlider crc_calc_ddr4gddr5(TEST_testitem *testarg, USlider p_data[4]);
extern USlider crc_calc_ddr5(TEST_testitem *testarg, USlider p_data[4]);
extern USlider ecc_calc_lpddr5(TEST_testitem *testarg, USlider p_data[4]);
extern void crc_check(TEST_testitem *testarg);

#endif // ___TEST_CRC_H_

