#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include "test.h"
#include "test_main.h"
#include "test_struct.h"
#include "test_testitem.h"
#include "UTSC.h"
#include "UTHN.h"

//#define PRINT_TEST_SOCKET

int FK[17] = {0};
TEST_socketinfo SOCKET;

static int kbhit(void){
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch!=EOF){
    ungetc(ch, stdin);
    return(1);
  }

  return(0);
}

static int ReadFK(int *array){ 
  char svname[STR_MAX];
  char *rdata, label[STR_MAX], *value;
  UTSC_size_t size;
  UTSC_Pf pfdesc;
  UT_LKstream lks, lobj;
  int stn, st, ival = UT_OFF;
  int fknum;
  
  pfdesc = NULL;
  lks = NULL;
  
  if((st=UTSC_Pf_Open(&pfdesc, NULL))!=0){
    printf("%s:%d %d\n", __FILE__, __LINE__, st);
    goto END;
  }
  
  stn = UTL_ReadStationNumber();
  sprintf(svname, "UTPFV_SystemValue_FK%d", stn);
  if((st=UTSC_Pf_ReadData(pfdesc, svname, (void *)&rdata, &size))!=0) {
    printf("%s:%d %d\n", __FILE__, __LINE__, st);
    goto END;
  }
  if((st=UTHN_LKstream_Construct(&lks, rdata))!=UTHN_LKSTREAM_OK) {
    printf("%s:%d %d\n", __FILE__, __LINE__, st);
    goto END;
  }
  for(fknum=1; fknum<=16; fknum++){
    snprintf(label, sizeof(label), "FK%d", fknum);
    if((st=UTHN_LKstream_FindLabel(lks, label, &lobj))!=UTHN_LKSTREAM_OK){
      printf("%s:%d %d\n", __FILE__, __LINE__, st);
      goto END;
    }
    if((st=UTHN_LKstream_FindKey(lobj, "switch", &value))!=UTHN_LKSTREAM_OK){
      printf("%s:%d %d\n", __FILE__, __LINE__, st);
      goto END;
    }
    if(strcmp(value, "on")==0)
      array[fknum] = UT_ON;
    else
      array[fknum] = UT_OFF;
  }

END:
  if(lks){
    if((st=UTHN_LKstream_Destruct(lks))!=UTHN_LKSTREAM_OK){
      printf("%s:%d %d\n", __FILE__, __LINE__, st);
    }
  }
  if(pfdesc){
    if((st=UTSC_Pf_Close(pfdesc))!=0) {
      printf("%s:%d %d\n", __FILE__, __LINE__, st);
    }      
  }

  return ival;
}

static void cui_menu(char *itemfile){
  char str[STR_MAX] = {0};
  char *strp;
  long testno = 0;
  char items[STR_MAX] = {0};
  int i = 0;
  FILE *fp;

  printf("=== ITEM SELECTION MENU ===\n");
  while(1){
    printf("[<TESTNO>=ADD, C=CLEAR ALL, P=PRINT ALL ITEMS, Q=QUIT&EXEC] > "); fflush(stdout);
    scanf("%s", str);

    testno = strtol(str, &strp, 10);
    if(testno!=0){
      testno = 0;
      if(strlen(items)==0){
        sprintf(items, "%s", str);
      }
      else{
        sprintf(items, "%s, %s", items, str);
      }
      printf("  Add %s\n", str);
      printf("  Selected items: %s\n", items);
    }
    else if(str[0]=='C'){
      items[0] = 0;
      printf("  Clear selected items.\n");
    }
    else if(str[0]=='P'){
      i = 0;
      while(testitem[i].testno!=0){
        printf("%s\n", testitem[i].testname);
        i++;
      }
    }
    else if(str[0]=='Q'){
      fp = fopen(itemfile, "w");
      if(fp==NULL){
        printf("File open error.\n");
        exit(1);
      }

      fprintf(fp, "%s\n", items);
      fclose(fp);
      break;
    }
  }

  return;
}

static void get_testmode(int argc, char *argv[], char *itemfile){
  remove(ITEM_FILE);

  if((argc==3)&&(strncmp("-f", argv[1], 2)==0)){
    sprintf(itemfile, "%s", argv[2]);
    printf("FILE mode: Test items loaded from \"%s\"\n", itemfile);
  } 
  else{
    sprintf(itemfile, "%s", ITEM_FILE);
    struct stat st;
    printf("MANUAL mode: Hit enter key to enter the menu.\n"); fflush(stdout);
    while(kbhit()==0){
      if(stat(itemfile, &st)==0){
        break; // For replica sites
      }
    }
    if(stat(itemfile, &st)!=0){
      cui_menu(itemfile); // Only for primary site
    }
  }

  return;
}

static void testno2testflag(long testno_min, long testno_max){
  int i = 0;
  while(testitem[i].testno!=0){
    if((testno_min<=testitem[i].testno)&&(testitem[i].testno<=testno_max)){
      testitem[i].testflag = TEST_EXEC;
    }
    i++;
  }

  return;
}

static void itemfile2testflag(char *itemfile){
  int i = 0;
  while(testitem[i].testno!=0){
    testitem[i].testflag = TEST_SKIP;
    i++;
  }

  FILE *fp;
  fp = fopen(itemfile, "r");
  if(fp==NULL){
    printf("File open error.\n");
    exit(1);
  }

  char str[STR_MAX] = {0};
  char *strp;
  char *str2;
  long testno_min = 0;
  long testno_max = 0;
  printf("  Execute: ");
  while(fscanf(fp, "%[^,]%*[,]", str)!=EOF){
    if(testno_min!=0){
      printf(", ");
    }
    testno_min = strtol(str, &strp, 10);

    str2 = strchr(strp, (int)'-');
    if(str2==NULL){
      testno_max = testno_min;
      printf("%d", testno_min);
    }
    else{
      str2++;
      testno_max = strtol(str2, NULL, 10);
      printf("%d-%d", testno_min, testno_max);
    }
    testno2testflag(testno_min, testno_max);
  }
  printf("\n");

  fclose(fp);

  return;
}

static void parse_socket(){
  int *dutpin, pcnt, pidx;
  int vtc_pin, vtc_stn;
  int pbpin_number, pbpin_child;
  RadioButton testerblock;
  DutCursor dutc;
  UT_DUT dut;

  int block[8];
  for(testerblock=0; testerblock<MAXBLKCNT; testerblock++){
    SOCKET.dutblock_iopin_count[testerblock] = 0;
    block[testerblock] = -1;
    for(pidx=0; pidx<MAXBLKIOCNT; pidx++){
      SOCKET.dutblock_iopin[testerblock][pidx] = 0;
    }
  }

  UTSOCK_Info_GetDutPinList(UT_SOCKET_PINTYPE_IO, &dutpin, &pcnt);

  dutc = UTL_GetDutCursor(UT_DDUT);
  dut = UTL_NextDut(dutc);
  UTL_DeleteCursor(dutc);
  SOCKET.dutblock_count = 0;
  SOCKET.dut_iopin_count = 0;
  for(pidx=0; pidx<pcnt; pidx++){
    UTVTC_SocketConversion_DutPin_ToVtcPin(UT_SOCKET_PINTYPE_IO, dutpin[pidx]-1, &vtc_pin);
    UTVTC_SocketConversion_VtcPin_ToPbPin (dut-1, vtc_pin, &vtc_stn, &pbpin_number, &pbpin_child);

    if(pbpin_number%64>18){
      continue;
    }
    testerblock = pbpin_number/64;

    if(block[testerblock]<0){
      block[testerblock] = SOCKET.dutblock_count++;
    }
    SOCKET.dutblock_iopin[block[testerblock]][SOCKET.dutblock_iopin_count[block[testerblock]]++] = dutpin[pidx];
    SOCKET.dut_iopin_count++;
  }

  for(dut=0; dut<=MAXDUTCNT; dut++){
    for(pidx=0; pidx<=MAXIOPINNO; pidx++){
      SOCKET.testeriopin[dut][pidx] = -1;
    }
  }
  dutc = UTL_GetDutCursor(UT_DDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    for(pidx=0; pidx<pcnt; pidx++){
      UTVTC_SocketConversion_DutPin_ToVtcPin(UT_SOCKET_PINTYPE_IO, dutpin[pidx]-1, &vtc_pin);
      UTVTC_SocketConversion_VtcPin_ToPbPin (dut-1, vtc_pin, &vtc_stn, &pbpin_number, &pbpin_child);
      if(pbpin_number%64>18){
        continue;
      }
      SOCKET.testeriopin[dut][dutpin[pidx]] = pbpin_number+1;
    }
  }
  UTL_DeleteCursor(dutc);

  dutc = UTL_GetDutCursor(UT_DDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    UTVTC_SocketConversion_DutPin_ToVtcPin(UT_SOCKET_PINTYPE_IO, dutpin[0]-1, &vtc_pin);
    UTVTC_SocketConversion_VtcPin_ToPbPin (dut-1, vtc_pin, &vtc_stn, &pbpin_number, &pbpin_child);
    SOCKET.dut_child[dut] = (pbpin_child&0x3)-1; //A1=0, A2=1
  }
  UTL_DeleteCursor(dutc);

  refresh_pinlist();

  return;
}

int main(int argc, char *argv[]){
  UTL_InitTest(argc, argv);
  char *TEST_SKIP_MSG[] = {
    "",
    "MB Lock",
    "MB Free",
    "DiagPB Lock",
    "DiagPB Free",
    "Socket",
    "FM Config"
  };
  int i = 0;
  ReadFK(FK);
  char *strenv;

  printf("\n\n\n");
  printf("****************************************************************************************************\n");
  if((strenv=getenv("ATFSTMODEL"))!= NULL){
    printf("ATFSTMODEL\t: %s\n", strenv);
  }
  if((strenv=getenv("ATFSREV"))!= NULL){
    printf("ATFSREV\t\t: %s\n", strenv);
  }
  if((strenv=getenv("ATFSMTT"))!= NULL){
    printf("ATFSMTT\t\t: %s\n", strenv);
  }
  if((strenv=getenv("ATFSDIAG"))!= NULL){
    printf("ATFSDIAG\t: %s\n", strenv);
  }
  printf("\nSOCKET\t\t: %s\n", UTL_ReadSocketProgramName());
  parse_socket();
  print_socketinfo();

  printf("****************************************************************************************************\n");
  printf("Arguments\n");
  printf("test_main\t\t: MANUAL mode - Select test items using CUI menu.\n");
  printf("test_main -f <itemfile>\t: FILE mode - Test items load from itemfile.\n");
  printf("\n");
  printf("Function Key Setting\n");
  printf("FK[ 2]: Print MCI time (Average)\n");
  printf("FK[ 3]: Print MCI time (Individual)\n");
  printf("FK[ 4]: Print skipped test items.\n");
  printf("****************************************************************************************************\n");
  printf("\n");

  char testno_testname[STR_MAX] = {0};
  char itemfile[STR_MAX] = {0};

  i = 0;
  while(testitem[i].testno!=0){
    sprintf(testno_testname, "%5d %s", testitem[i].testno, testitem[i].testname);
    sprintf(testitem[i].testname, "%s", testno_testname);
    i++;
  }
  get_testmode(argc, argv, itemfile);
  itemfile2testflag(itemfile);

  TestHandle testh;
  time_t timer;
  RadioButton result, itemresult, finalresult;
  DutCursor dutc;
  UT_DUT dut;
 
  testh = UTL_GetTestHandle();
  time(&timer);
  printf("\n----------------------------------------------------------------------------------------------------\n");
  printf("\nTEST PROGRAM START AT : %s\n", ctime(&timer));

  int skip = 0;
  i = 0;
  while(testitem[i].testno!=0){
    if(testitem[i].testflag==TEST_SKIP){
      if(FK[4]){
        printf("\n%-86s", testitem[i].testname);
        printf("tSKIP\n"); fflush(stdout);
      }
      i++;
      continue;
    }

#ifndef PRINT_TEST_SOCKET
    set_ilmode(2);
    set_ilmode(1); //reset ilmode

    //Avoid 3ms overhead on every MeasFct for PPS-less system.
    PowerSeqHandle psh = UTL_GetPowerSeqHandle();
    UTL_AddPowerSeqAll(psh, 1);
    UTL_SetPowerSeqWaitTime(psh, 1, 0.0);
    UTL_SendPowerSeq(psh);
    UTL_DeleteHandle(psh);

    parse_socket();
    testitem[i].skipreason = TEST_SKIP_NULL;
    UTL_SetTestArg   (testh, &testitem[i]);
    UTL_SetTestAction(testh,  testitem[i].testfunc);
    UTL_Test         (testh,  testitem[i].testname);

    printf("\n%-86s", testitem[i].testname);
    if(testitem[i].skipreason==TEST_SKIP_NULL){
      dutc = UTL_GetDutCursor(UT_DDUT);
      itemresult = UT_RES_PASSED;
      while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
        result = UTL_ReadTestResult(dut, testitem[i].testname, UT_RES_ALL);

        if(result==UT_RES_FAILED){
        //if(result!=UT_RES_PASSED){
          itemresult = UT_RES_FAILED;
        }
      }
      UTL_DeleteCursor(dutc);
      if(itemresult==UT_RES_PASSED){
        printf("tPASS     ");
      }
      else{
        printf("*****tFAIL");
      }
      printf(" .%s\n", strrchr(UTL_ReadSocketProgramName(), '/'));
    }
    else{
      printf("tSKIP(%s)\n", TEST_SKIP_MSG[testitem[i].skipreason]);
      skip++;
    }
    fflush(stdout);
#else
    printf("%s, %s\n", testitem[i].testname, UTL_ReadSocketProgramName());
#endif

    i++;
  }

  time(&timer);
  printf("\nTEST PROGRAM END   AT : %s", ctime(&timer));
  UTL_DeleteHandle(testh);

  dutc = UTL_GetDutCursor(UT_DDUT);
  finalresult = UT_RES_PASSED;
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    result = UTL_ReadFinalResult(dut, UT_RES_ALL);
    if(result==UT_RES_FAILED){
    //if(result!=UT_RES_PASSED){
      finalresult = UT_RES_FAILED;
    }
  }
  UTL_DeleteCursor(dutc);

  printf("\n%86s", "tRESULT");
  if(finalresult==UT_RES_PASSED && skip==0){
    printf("_PASS\n");
  }
  else{
    printf("******FAIL\n");
  }

  printf("\n----------------------------------------------------------------------------------------------------\n");

  return 0;
}

