#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "UTSC.h"
#include "test.h"
#include "test_struct.h"
#include "mcitime.h"
#include "exectime.h"

static int exectime_check_body(TEST_testitem *testarg);
static void TimeAnalyzeInit1();

static void TimeAnalyzeInit1(){
  int id;
  for(id=1; id<T_MAX; id++){
    ACCUMULATED_TIME[id] = 0.0;
    CALLS[id] = 0;
  }
  return;
}

static int exectime_check_body(TEST_testitem *testarg){
  int result;
  int i, j;
  double exectime = 0.0;

  TEST_testitem target_test = {0};
  i = 0;
  while(testitem[i].testno!=0){ // search target test
    if(testitem[i].testno==EXECTIMEARG.target_testno){
      target_test = testitem[i];
      break;
    }
    i++;
  }
  if(target_test.testno!=EXECTIMEARG.target_testno){
    printf("EXECTIME: Target test is not found.");
    return;
  }

  printf("EXECTIME TARGET TEST: %s\n", target_test.testname);
  sprintf(target_test.testname, "%s", testarg->testname);
  void (*tfunc)(TEST_testitem *) = target_test.testfunc;

  TimeAnalyzeInit1();
  tfunc(&target_test); // exec target test

  result = 1; //FAIL
  printf("EXECTIME exp=%e limit=+/-%.1f%+/-%e", EXECTIMEARG.exp, EXECTIMEARG.limit_rate*100, EXECTIMEARG.limit_abs);
  printf(" (%e<=t<=%e)\n", EXECTIMEARG.exp*(1.0-EXECTIMEARG.limit_rate)-EXECTIMEARG.limit_abs, EXECTIMEARG.exp*(1.0+EXECTIMEARG.limit_rate)+EXECTIMEARG.limit_abs);

  for(i=0; i<T_MAX; i++){ // pass/fail judge
    if(CALLS[i]>0){
      if(strcmp(MCI_LIST[i], EXECTIMEARG.target_mci)==0){
        result = 0; //PASS

        for(j=0; j<(CALLS[i]<NUM_MAX ? CALLS[i]:NUM_MAX); j++){
          if(EXECTIMEARG.average==UT_ON){
            exectime = ACCUMULATED_TIME[i]/CALLS[i];
            printf("EXECTIME RESULT AVERAGE(%d) %s t=%e", CALLS[i], EXECTIMEARG.target_mci, exectime);
          }
          else{
            exectime = ACCUMULATED_INDIVIDUAL_TIME[i][j];
            printf("EXECTIME RESULT %s(%2d) t=%e", EXECTIMEARG.target_mci, j, exectime);
          }

          printf(" delta=%e %+5.1f%%", exectime-EXECTIMEARG.exp, (exectime-EXECTIMEARG.exp)/EXECTIMEARG.exp*100);
          if((EXECTIMEARG.exp*(1.0-EXECTIMEARG.limit_rate)-EXECTIMEARG.limit_abs<=exectime) && (exectime<=EXECTIMEARG.exp*(1.0+EXECTIMEARG.limit_rate)+EXECTIMEARG.limit_abs)){
            printf("\tPASS\n");
          }
          else{
            printf("\t****RETRY\n");
            result = 1; //FAIL
          }

          if((EXECTIMEARG.average==UT_ON)||(EXECTIMEARG.all!=UT_ON)){
            break;
          }
        }
        break;
      }
    }
  }

  return(result);
}

void exectime_check(TEST_testitem *testarg){
  int i;

  testresult_fail4alldut(testarg->testname);
  for(i=0; i<10; i++){
    if(exectime_check_body(testarg)==0){
      testresult_pass4alldut(testarg->testname);
      break;
    }
  }

  return;
}

