#ifndef ___TEST_ADC_H_
#define ___TEST_ADC_H_
 
void adc_start_pps(TEST_testitem *testarg);
void adc_start_dc(TEST_testitem *testarg);
void adc_start_inhi(TEST_testitem *testarg);
//Asakaze5 not supported: void adc_start_samp(TEST_testitem *testarg);
void adc_start_multi_pps(TEST_testitem *testarg);
void adc_start_multi_dc(TEST_testitem *testarg);
void adc_start_time_pps(TEST_testitem *testarg);
void adc_start_time_dc(TEST_testitem *testarg);

#endif // ___TEST_ADC_H_


