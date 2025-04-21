#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include "test.h"
#include "test_struct.h"
#include "msdc.h"

static void pinlist();
//void msdc_mltpl_org();
static void level_setting( int channel, double high, double low);
static void mvm_setting();
static int  read_dct();

#define DEBUG  0         // 0:Not Debug Mode/1:Debug Mode/2:Option

#define DUTMAX 8
#define PINMAX 4

#if 0
int msdc_main(int argc, char *argv)
{

  char *socname;
  int  soc=0;
  int  std_pin;
  socname = UTL_ReadSocketProgramName();
//char *p = strstr(socname,"socket1");
  if(strstr(socname,"socket1")!=NULL){printf("\nSocket Pro: %s\n",strstr(socname,"socket1"));soc=1;}
  if(strstr(socname,"socket2")!=NULL){printf("\nSocket Pro: %s\n",strstr(socname,"socket2"));soc=2;}
//if(strstr(socname,"socket3")!=NULL){printf("\nSocket Pro: %s\n",strstr(socname,"socket3"));soc=3;}
  

  pinlist();
  TestHandle testh = UTL_GetTestHandle();
  if(soc==1){UTL_SetTestAction(testh, msdcsepa1  ); UTL_Test(testh, "TNO097 MSDCSEPA1 Check ");}
  if(soc==1){UTL_SetTestAction(testh, msdcsepa2  ); UTL_Test(testh, "TNO098 MSDCSEPA2 Check ");}
  if(soc==2){
             UTL_SetTestAction(testh, msdc_mltpl ); 
             std_pin=33; 
             UTL_SetTestArg(testh,&std_pin);
             UTL_Test(testh, "TNO099 MSDCSEPA+ Check(P33) ");
  }
  if(soc==2){
             UTL_SetTestAction(testh, msdc_mltpl ); 
             std_pin=34; 
             UTL_SetTestArg(testh,&std_pin);
             UTL_Test(testh, "TNO099 MSDCSEPA+ Check(P34) ");
  }





return 0;
}
#endif

static void pinlist()
{
        int i,soc;
    	UTL_CreatePinList	("TPIN");
    	UTL_SetPinType		("TPIN",UT_PINTYPE_PIN);
        for(i=1;i<=4;i++){
             UTL_AddPinNumber	("TPIN", i   );
        }
        

}
static void level_setting(int channel , double high, double low){
        ViHandle vi_h = UTL_GetViHandle();
        UTL_SetViHigh           (vi_h , high );     
        UTL_SetViLow            (vi_h , low  );     
        UTL_SetViHvDr           (vi_h , UT_OFF);
        UTL_SendVi              (vi_h , channel);
        UTL_DeleteHandle(vi_h);
       
}
static void mvm_setting()
{
  DcHandle Dc_H = UTL_GetDcHandle();
  //UTL_SetDcMode      (Dc_H, UT_DCT_MVM );
  //UTL_SetDcMrange    (Dc_H, 0.0, -7.0);
  UTL_SetDcMode      (Dc_H, UT_DCT_VSIM);
  UTL_SetDcMrange    (Dc_H, 5e-6, -5e-6);
  UTL_SetDcSrange    (Dc_H, 7.0, -7.0);
  UTL_SetDcSource    (Dc_H, 7.0);
  UTL_SetDcLimitHigh (Dc_H, 0.0, UT_OFF);
  UTL_SetDcLimitLow  (Dc_H, 0.0, UT_OFF);
  UTL_SetDcMeasCnt   (Dc_H, 1);
  UTL_SendDc         (Dc_H, 1);
  UTL_DeleteHandle   (Dc_H);
}

static int  read_dct(){
// Read Dct 
        RadioButton sepam;
        sepam=UTL_ReadDctSepaDrCtrlMode();  

        DutCursor dutc; 
        UT_DUT dut;
        PinCursor pinc; 
        UT_PIN pin;
        DSlider dcdata[DUTMAX][PINMAX];
        DctReadPinHandle drph= UTL_GetDctReadPinHandle();
        dutc = UTL_GetDutCursor(UT_DDUT);  
        while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
             if(DEBUG==1){printf("dut:%d\n",dut);fflush(stdout);}
             UTL_SetDctReadPinDut(drph,dut);
             pinc = UTL_GetPinCursor("TPIN");  
             while((pin=UTL_NextPin(pinc))!=UT_NOMORE){
                  UTL_SetDctReadPinNumber(drph,pin);
                  dcdata[dut-1][pin-1]=UTL_ReadDctPinData(drph);
                  if(DEBUG==1){printf("dcdata[%d][%d]:%f\n",dut,pin,dcdata[dut-1][pin-1]*1e9);fflush(stdout);}
             }
        }

// Pass/Fail Judge        
        int result=0;
        int i,j;
        for(i=0;i<DUTMAX;i++){
             for(j=0;j<PINMAX;j++){
                  if(i%2==0){
                       if(DEBUG==1){printf("dcdata[%d][%d]=%f:dcdata[%d][%d]=%f\n",i,j,dcdata[i][j]*1e9,i+1,j,dcdata[i+1][j]*1e9);fflush(stdout);}
                       if(sepam==UT_DCT_SIMUL){
                            if(DEBUG==1){printf("***Entry UT_DCT_SIMUL\n");fflush(stdout);}
                            if(dcdata[i][j]!=dcdata[i+1][j]){
                                 result = result | 0x1 << i;
                                 printf("FAIL****,Dut:%d,Pin:%d\n",i+1,j+1);fflush(stdout);
                            }
                       }else if(sepam==UT_DCT_SEPA){
                            if(DEBUG==1){printf("***Entry UT_DCT_SEPA\n");fflush(stdout);}
                            if(dcdata[i][j]==dcdata[i+1][j]){
                                 result = result | 0x1 << i;
                                 //printf("FAIL****,Dut:%d,Pin:%d\n",i+1,j+1);fflush(stdout);
                            }
                       }else{UTL_Stop();}
                  }
             }
        }

        UTL_DeleteHandle(drph);

        return result;
}


void msdcsepa1(TEST_testitem *testarg)
{
  pinlist();

        int res=0;

        PinHandle Pin_H = UTL_GetPinHandle();
        UTL_SetPinOpen   (Pin_H, UT_ON);
        UTL_SendPin      (Pin_H, "TPIN");
        UTL_DeleteHandle (Pin_H);

        UTL_SetDctSepaDrCtrlMode(UT_DCT_SIMUL);
        mvm_setting();
        
        DctHandle dcth = UTL_GetDctHandle();

        UTL_SetDctPinList(dcth,"TPIN");
        UTL_MeasDct      (dcth);

        res=read_dct();

//display result
        DutCursor dutc;
        UT_DUT   dut=0;
        dutc=UTL_GetDutCursor(UT_CDUT);

        printf("\nTEST NAME : %-32s", UTL_ReadTestName());fflush(stdout);
        if(res==0){
	    testresult_pass4alldut(testarg->testname);
	    printf("***PASS\n");fflush(stdout);
	}
        else{
	    testresult_fail4alldut(testarg->testname);
            if(res!=0){
                 printf("FAIL***\n");
                 while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
                      if(res >> dut-1 & 0x01 ==0x01){printf(" DUT:%d",dut);fflush(stdout);} 
                 }
            }
        }
//display result


        UTL_DeleteHandle(dcth);

}

void msdcsepa2(TEST_testitem *testarg)
{
  pinlist();

        PinHandle Pin_H = UTL_GetPinHandle();
        UTL_SetPinOpen   (Pin_H, UT_ON);
        UTL_SendPin      (Pin_H, "TPIN");
        UTL_DeleteHandle (Pin_H);

        SamplingRateHandle samh = UTL_GetSamplingRateHandle();
        UTL_SetSamplingRate(samh, 5e-6);
        UTL_SendSamplingRate(samh);
        UTL_DeleteHandle(samh);

        UTL_SetDctSepaDrCtrlMode(UT_DCT_SEPA);
        mvm_setting();

        DctHandle dcth = UTL_GetDctHandle();
        UTL_SetDctPinList(dcth,"TPIN");

	int i;
	int pf;
	int res = 0xff;
	for(i=0; i<100; i++){
          UTL_MeasDct(dcth);
          pf = read_dct();
	  printf("i=%d 0x%02x\n", i, pf); fflush(stdout);
          res&=pf;
	  if(res==0) break;
	  UTL_WaitTime(1.0);
	}
        UTL_DeleteHandle(dcth);

        if(DEBUG==1){printf("result:%x\n",res);fflush(stdout);}

//display result
        DutCursor dutc;
        UT_DUT   dut=0;
        dutc=UTL_GetDutCursor(UT_CDUT);

        printf("\nTEST NAME : %-32s", UTL_ReadTestName());fflush(stdout);
        if(res==0){
	    testresult_pass4alldut(testarg->testname);
	    printf("***PASS\n");fflush(stdout);
	}
        else{
	    testresult_fail4alldut(testarg->testname);
            if(res!=0){
                 printf("FAIL***\n");
                 while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
                      if(res >> dut-1 & 0x01 ==0x01){printf(" DUT:%d",dut);fflush(stdout);} 
                 }
            }
        }
}

//void msdc_mltpl_org()
//{
//
//        PinHandle Pin_H = UTL_GetPinHandle();
//        UTL_SetPinOpen   (Pin_H, UT_ON);
//        UTL_SendPin      (Pin_H, "TPIN");
//        UTL_DeleteHandle (Pin_H);
//
//
//
//
//////
//       
//       RadioButton gnum,gmax;
//       PinCursor pinc;
//       DutCursor dutc;
//       int std_pin=1;
//       UT_PIN pin;
//       UT_DUT dut;
//       ExclusionHandle hex = UTL_GetExclusionHandle();
//       pinc=UTL_GetPinCursor("TPIN");
////     while((pin=UTL_NextPin(pinc))!=UT_NOMORE){
//
//       gmax=UTL_GetDctDutGroupMaxNumber(std_pin); 
//   printf("gmax : %d\n",gmax);fflush(stdout);
//       for(gnum=0; gnum<=gmax; gnum++)
//       {
////             UTL_SetExclusionIgnoreWet  (hex,UT_OFF);                          
//               dutc=UTL_GetDctDutGroupCursor(pin, gnum  );  // RTE.
//               dutc=UTL_GetDctDutGroupCursor( 2 , gnum  );  // RTE.
//               while((dut=UTL_NextDut(dutc))!=UT_NOMORE)
//               {
//printf("DUT: %d\n",dut);fflush(stdout);
//getchar();
//printf("***AAAAAA\n");fflush(stdout);
//
//                    UTL_ClearExclusionDut      (hex);                      
//                    UTL_AddExclusionDut        (hex,dut);                  
//                    UTL_SetExclusionSetOrReset (hex,UT_OFF);               
//                    UTL_SetExclusionMask       (hex,UT_OFF);               
//                    UTL_SendExclusion          (hex);                       
//  
//                    UTL_OnPowerSeq             ();                    
//
//                    DctHandle dcth = UTL_GetDctHandle();
////                  UTL_SetDctSepaDrCtrlMode(UT_DCT_SEPA );
//                    vsim_setting();
//                    
//
//                    UTL_SetDctPinList(dcth,"TPIN");
//                    UTL_MeasDct      (dcth);
//
//                    UTL_OffPowerSeq             ();                      
//  
//                    UTL_SetExclusionSetOrReset (hex,UT_ON);             
//                    UTL_SetExclusionMask       (hex,UT_ON);              
//                    UTL_SendExclusion          (hex);                     
//
//               }
//        }
////    }
///////
//printf("******AAAAAAAAAAAAAAAAAAAA\n");
//getchar();
//        DctHandle dcth = UTL_GetDctHandle();
//        UTL_SetDctSepaDrCtrlMode(UT_DCT_SEPA );
//        vsim_setting();
//        
//
//        UTL_SetDctPinList(dcth,"TPIN");
//        UTL_MeasDct      (dcth);
//
//        UTL_DeleteHandle(dcth);
//
//
//}

void msdc_mltpl(TEST_testitem *testarg)
{
  pinlist();

        PinHandle Pin_H = UTL_GetPinHandle();
        UTL_SetPinOpen   (Pin_H, UT_ON);
        UTL_SendPin      (Pin_H, "TPIN");
        UTL_DeleteHandle (Pin_H);



        if(DEBUG==1)printf("*****stdpin:%d\n",MSDCARG.std_pin);fflush(stdout);

////

        RadioButton gnum,gmax;
        PinCursor pinc;
        DutCursor dutc;
        USlider dutbit;
        int size;
        dutbit = 0x0;
        size = sizeof(dutbit*4);
        UT_PIN pin;
        UT_DUT dut;

        UTL_SetDctSepaDrCtrlMode(UT_DCT_SEPA  );
        ExclusionHandle hex = UTL_GetExclusionHandle();
        pinc=UTL_GetPinCursor("TPIN");

        gmax=UTL_GetDctDutGroupMaxNumber(MSDCARG.std_pin);
        if(DEBUG==1)printf("*****gmax : %d\n",gmax);fflush(stdout);
        for(gnum=0; gnum<=gmax; gnum++)
        {
               dutc=UTL_GetDctDutGroupCursor(MSDCARG.std_pin, gnum  );
               while((dut=UTL_NextDut(dutc))!=UT_NOMORE)
               {
                    dutbit=dutbit | 0x1 << (dut-1);
                    if(DEBUG==1)printf("dutbit: %4x\n",dutbit);fflush(stdout);
                    if(DEBUG==1)printf("gnum: %d\n",gnum);fflush(stdout);
                    if(DEBUG==1)printf("DUT: %d\n",dut);fflush(stdout);
               }

               UTL_SetResetExclusionByDutBit (&dutbit,size,UT_OFF,UT_OFF);
               UTL_OnPowerSeq             ();

               DctHandle dcth = UTL_GetDctHandle();
               UTL_SetDctSepaDrCtrlMode(UT_DCT_SEPA  );
               mvm_setting();
               UTL_SetDctPinList(dcth,"TPIN");
               UTL_MeasDct      (dcth);
               UTL_OffPowerSeq             ();

               UTL_SetExclusionSetOrReset (hex,UT_ON);
               UTL_SetExclusionMask       (hex,UT_ON);
               UTL_SendExclusion          (hex);
               dutbit=0x0;

        }
        if(DEBUG==1)printf("gmax:%d\n",gmax);fflush(stdout);
        printf("\nTEST NAME : %-32s", UTL_ReadTestName());fflush(stdout);
        if(MSDCARG.std_pin==1){
           if(gmax==0){printf("***PASS\n");fflush(stdout);
           }else{printf("FAIL***");}
        }
        if(MSDCARG.std_pin==2){
           if(gmax==2){printf("***PASS\n");fflush(stdout);
           }else{printf("FAIL***");}
        }

}

