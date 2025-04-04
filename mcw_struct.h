#ifndef ___TEST_MCW_STRUCT_H_
#define ___TEST_MCW_STRUCT_H_
#include "test.h"

#define MCWARG testarg->mcwarg

typedef struct{
    int sta_max;            // Max Station number
    int blk_max;            // Max Block number
	int bit_max;            // Max Bit number
    CheckButton aps_onoff;  // Enables or disables to target all physical station
    RadioButton mcw_mode;   // Type of the DUT auxiliary signal
}TEST_mcwarg;

#endif //___TEST_MCW_STRUCT_H_