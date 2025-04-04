#ifndef ___TEST_COMMON_H_
#define ___TEST_COMMON_H_

#include "test.h"

// for dct_data()
#define DCT_STORE   (0x10) // Store average DCT data
#define DCT_HISTORY (0x01)   // by UTL_ReadDctPinAllHistoryData()
#define DCT_PINDATA (0x02)   // by UTL_ReadDctPinData()
#define DCT_READ    (0x20) // Read stored data

extern void print_socketinfo();
extern void refresh_pinlist();
extern void testresult_pass4alldut(char *testname);
extern void testresult_fail4alldut(char *testname);
extern void set_reg(RadioButton name, USlider data);
extern void set_ilmode(RadioButton ilmode);
extern void failcapsel_a2();
extern double calc_sum(double nums[], int n);
extern double calc_ave(double nums[], int n);
extern double calc_var(double nums[], int n);
extern double calc_sd(double nums[], int n);
extern DSlider dct_data(UT_DUT dut, UT_PIN pin, int action);
extern void store_dct(char* pinname, int mode);
extern void stat_dct(char *pinlist, DSlider hlimit, DSlider llimit, DSlider *data);
extern void dutpin_to_testerch(UT_DUT dut, int dut_pin, int *tester_channel, int *child);

#endif // ___TEST_COMMON_H_

