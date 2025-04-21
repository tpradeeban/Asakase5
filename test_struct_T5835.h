#ifndef ___TEST_STRUCT_H_
#define ___TEST_STRUCT_H_

#include "common.h"
#include "mcitime.h"
extern int FK[17];

#define TEST_END {0, "", NULL, {{0}}}
#define STR_MAX (4096)
#define MAXDUTCNT (288)
#define MAXCLDCNT (2)
#define MAXBLKCNT (8)
#define MAXBLKIOCNT (18)
#define MAXIOPINNO (466)
#define MAXPINNO (478)
#define MAXDCTCNT (4095)

//Add struct.h here
#include "drcp_struct.h"
#include "hvlvdr_struct.h"
#include "msdc_struct.h"
#include "pinppsbump_struct.h"
#include "msdc_struct.h"
#include "burst_struct.h"
#include "dbm_struct.h"
#include "fcm_struct.h"
#include "ubm_struct.h"
#include "pg_struct.h"
#include "frun_struct.h"
#include "jitter_struct.h"
#include "mcw_struct.h"
#include "sourcesync_struct.h"
#include "bbm_struct.h"
#include "fcsm_struct.h"
#include "pscram_struct.h"
#include "flash_struct.h"
#include "timetraining_struct.h"
#include "smh_drvln_mvm_struct.h"
#include "crc_struct.h"
#include "exectime_struct.h"
#include "mpselect_struct.h"
#include "multich_struct.h"
#include "multipg_struct.h"
#include "pdfc_struct.h"
#include "fbgsync_struct.h"

enum test_flag{
  TEST_EXEC,
  TEST_SKIP
};

enum skip_reason{
  TEST_SKIP_NULL=0,
  TEST_SKIP_MB_LOCK=1,
  TEST_SKIP_MB_FREE=2,
  TEST_SKIP_DIAGPB_LOCK=3,
  TEST_SKIP_DIAGPB_FREE=4,
  TEST_SKIP_SOCKET=5,
  TEST_SKIP_FM_CONFIG=6
};

typedef struct{
  int testno;
  char testname[STR_MAX];
  void (*testfunc);
  union{
    //Add struct member here
    TEST_drcparg drcparg;
    TEST_hvarg hvarg;
    TEST_pinppsbumparg pinppsbumparg;
    TEST_msdcarg msdcarg;
    TEST_dbmarg dbmarg;
    TEST_fcmarg fcmarg;
    TEST_ubmarg ubmarg;
    TEST_pgarg pgarg;
    TEST_burstarg burstarg;
    TEST_frunarg frunarg;
    TEST_jitterarg jitterarg;
    TEST_mcwarg mcwarg;
    TEST_ssarg ssarg;
    TEST_bbmarg bbmarg;
    TEST_fcsmarg fcsmarg;
    TEST_pscramarg pscramarg;
    TEST_flasharg flasharg;
    TEST_ttrarg ttrarg;
    TEST_crcarg crcarg;
    TEST_exectimearg exectimearg;
    TEST_wavearg wavearg;
    TEST_mpselarg mpselarg;
    TEST_multicharg multicharg;
    TEST_multipgarg multipgarg;
    TEST_pdfcarg pdfcarg;
    TEST_fbgarg fbgarg;
  };
  enum test_flag testflag; //for test_main.c internal use
  enum skip_reason skipreason;
}TEST_testitem;

typedef struct{
  RadioButton dut_iopin_count;
  RadioButton dutblock_count;
  RadioButton dutblock_iopin_count[MAXBLKCNT];
  RadioButton dutblock_iopin[MAXBLKCNT][MAXBLKIOCNT];
  char *dutblock_iopinlist[MAXBLKCNT];
  char *all_iopinlist;
  RadioButton dut_child[MAXDUTCNT+1];
  int testeriopin[MAXDUTCNT+1][MAXIOPINNO+1];
}TEST_socketinfo;

extern TEST_socketinfo SOCKET;

#endif // ___TEST_STRUCT_H_

