//TNO,TESTNAME		, TEST FUNC


#if 1 //CP OK
  { 8000, "BBM FAIL CAPTURE: <A1>DATACAPTURE,ALL FAIL"               	        , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeAllPF, UT_BBM_DATACAPTURE, UT_BBM_READFAIL,0,0}} },
  { 8001, "BBM CP MASK     : <A1>DATAGENERATE,ALL PASS"              	        , bbm_test_3,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeAllPF, UT_BBM_DATAGENERATE,UT_BBM_READFAIL,0,1}} },
  { 8002, "BBM FAIL CAPTURE: <A1>MAXFAIL,    ALL FAIL"               	        , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeAllPF, UT_BBM_MAXFAIL,     UT_BBM_READFAIL,0,0}} },
  { 8003, "BBM CP MASK     : <A1>MAXFAIL,    ALL PASS"              	        , bbm_test_3,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeAllPF, UT_BBM_MAXFAIL,     UT_BBM_READFAIL,0,1}} },
  { 8004, "BBM FAIL CAPTURE: <A1>ORFAIL,     ALL FAIL"               	        , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeAllPF, UT_BBM_ORFAIL,      UT_BBM_READFAIL,0,0}} },
  { 8005, "BBM FAIL CAPTURE: <A2>DATACAPTURE,ALL FAIL"               	        , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeAllPF, UT_BBM_DATACAPTURE, UT_BBM_READFAIL,1,0}} },
  { 8006, "BBM CP MASK     : <A2>DATAGENERATE,ALL PASS"              	        , bbm_test_3,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeAllPF, UT_BBM_DATAGENERATE,UT_BBM_READFAIL,1,1}} },
  { 8007, "BBM FAIL CAPTURE: <A2>MAXFAIL,    ALL FAIL"               	        , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeAllPF, UT_BBM_MAXFAIL,     UT_BBM_READFAIL,1,0}} },
  { 8008, "BBM CP MASK     : <A2>MAXFAIL,    ALL PASS"              	        , bbm_test_3,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeAllPF, UT_BBM_MAXFAIL,     UT_BBM_READFAIL,1,1}} },
  { 8009, "BBM FAIL CAPTURE: <A2>ORFAIL,     ALL FAIL"               	        , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeAllPF, UT_BBM_ORFAIL,      UT_BBM_READFAIL,1,0}} },
#endif

#if 1 //CP OK
  { 8010, "BBM FAIL CAPTURE: <A1>DATACAPTURE,ALL PASS"               	        , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x000, 100e-9, JudgeAllPF, UT_BBM_DATACAPTURE, UT_BBM_READFAIL,0,1}} },
  { 8011, "BBM CP MASK     : <A1>DATAGENERATE,ALL FAIL"              	        , bbm_test_3,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeAllPF, UT_BBM_DATAGENERATE,UT_BBM_READFAIL,0,0}} },
  { 8012, "BBM FAIL CAPTURE: <A1>MAXFAIL,    ALL PASS"               	        , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x000, 100e-9, JudgeAllPF, UT_BBM_MAXFAIL,     UT_BBM_READFAIL,0,1}} },
  { 8013, "BBM CP MASK     : <A1>MAXFAIL,     ALL FAIL"              	        , bbm_test_3,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeAllPF, UT_BBM_MAXFAIL,     UT_BBM_READFAIL,0,0}} },
  { 8014, "BBM FAIL CAPTURE: <A1>ORFAIL,     ALL PASS"               	        , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x000, 100e-9, JudgeAllPF, UT_BBM_ORFAIL,      UT_BBM_READFAIL,0,1}} },
  { 8015, "BBM FAIL CAPTURE: <A2>DATACAPTURE,ALL PASS"               	        , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x000, 100e-9, JudgeAllPF, UT_BBM_DATACAPTURE, UT_BBM_READFAIL,1,1}} },
  { 8016, "BBM CP MASK     : <A2>DATAGENERATE,ALL FAIL"              	        , bbm_test_3,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeAllPF, UT_BBM_DATAGENERATE,UT_BBM_READFAIL,1,0}} },
  { 8017, "BBM FAIL CAPTURE: <A2>MAXFAIL,    ALL PASS"               	        , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x000, 100e-9, JudgeAllPF, UT_BBM_MAXFAIL,     UT_BBM_READFAIL,1,1}} },
  { 8018, "BBM CP MASK     : <A2>MAXFAIL,     ALL FAIL"              	        , bbm_test_3,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeAllPF, UT_BBM_MAXFAIL,     UT_BBM_READFAIL,1,0}} },
  { 8019, "BBM FAIL CAPTURE: <A2>ORFAIL,     ALL PASS"               	        , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x000, 100e-9, JudgeAllPF, UT_BBM_ORFAIL,      UT_BBM_READFAIL,1,1}} },
#endif

#if 1 //CP OK
  { 8020, "BBM FAIL CAPTURE: <A1>DATACAPTURE,PARTIAL FAIL"                      , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x040, 100e-9, JudgeHalfPass, UT_BBM_DATACAPTURE, UT_BBM_READFAIL,0,2}} },
  { 8021, "BBM CP MASK     : <A1>DATAGENERATE,PARTIAL FAIL"          	        , bbm_test_3,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeHalfPass, UT_BBM_DATAGENERATE,UT_BBM_READFAIL,0,0}} },
  { 8022, "BBM FAIL CAPTURE: <A1>MAXFAIL,    PARTIAL FAIL"                      , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x040, 100e-9, JudgeHalfPass, UT_BBM_MAXFAIL,     UT_BBM_READFAIL,0,2}} },
  { 8023, "BBM CP MASK     : <A1>MAXFAIL,    PARTIAL FAIL"           	        , bbm_test_3,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeHalfPass, UT_BBM_MAXFAIL,     UT_BBM_READFAIL,0,0}} },
  { 8024, "BBM FAIL CAPTURE: <A1>ORFAIL,     PARTIAL FAIL"                      , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x040, 100e-9, JudgeHalfPass, UT_BBM_ORFAIL,     UT_BBM_READFAIL,0,0}} },
  { 8025, "BBM FAIL CAPTURE: <A2>DATACAPTURE,PARTIAL FAIL"                      , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x040, 100e-9, JudgeHalfPass, UT_BBM_DATACAPTURE, UT_BBM_READFAIL,1,2}} },
  { 8026, "BBM CP MASK     : <A2>DATAGENERATE,PARTIAL FAIL"          	        , bbm_test_3,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeHalfPass, UT_BBM_DATAGENERATE,UT_BBM_READFAIL,1,0}} },
  { 8027, "BBM FAIL CAPTURE: <A2>MAXFAIL,    PARTIAL FAIL"                      , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x040, 100e-9, JudgeHalfPass, UT_BBM_MAXFAIL,     UT_BBM_READFAIL,1,2}} },
  { 8028, "BBM CP MASK     : <A2>MAXFAIL,    PARTIAL FAIL"           	        , bbm_test_3,{.bbmarg={1, "pat_bbm.mpa",0x020, 100e-9, JudgeHalfPass, UT_BBM_MAXFAIL,     UT_BBM_READFAIL,1,0}} },
  { 8029, "BBM FAIL CAPTURE: <A2>ORFAIL,     PARTIAL FAIL"                      , bbm_test_1,{.bbmarg={1, "pat_bbm.mpa",0x040, 100e-9, JudgeHalfPass, UT_BBM_ORFAIL,     UT_BBM_READFAIL,1,0}} },
#endif

#if 1
  { 8030, "BBM FAIL CAPTURE: <A1>DATACAPTURE,EVEN DUT PARTIAL FAIL"             , bbm_test_9,{.bbmarg={1, "pat_bbm.mpa",0x060, 100e-9, JudgeOddDutPass,UT_BBM_DATACAPTURE,UT_BBM_READFAIL,0,1}} },
  { 8031, "BBM FAIL CAPTURE: <A1>MAXFAIL,    EVEN DUT PARTIAL FAIL"             , bbm_test_9,{.bbmarg={1, "pat_bbm.mpa",0x060, 100e-9, JudgeOddDutPass,UT_BBM_MAXFAIL,    UT_BBM_READFAIL,0,1}} },
  { 8032, "BBM FAIL CAPTURE: <A1>ORFAIL,     EVEN DUT PARTIAL FAIL"             , bbm_test_9,{.bbmarg={1, "pat_bbm.mpa",0x060, 100e-9, JudgeOddDutPass,UT_BBM_ORFAIL,     UT_BBM_READFAIL,0,1}} },
  { 8033, "BBM FAIL CAPTURE: <A2>DATACAPTURE,EVEN DUT PARTIAL FAIL"             , bbm_test_9,{.bbmarg={1, "pat_bbm.mpa",0x060, 100e-9, JudgeOddDutPass,UT_BBM_DATACAPTURE,UT_BBM_READFAIL,1,0}} },
  { 8034, "BBM FAIL CAPTURE: <A2>MAXFAIL,    EVEN DUT PARTIAL FAIL"             , bbm_test_9,{.bbmarg={1, "pat_bbm.mpa",0x060, 100e-9, JudgeOddDutPass,UT_BBM_MAXFAIL,    UT_BBM_READFAIL,1,0}} },
  { 8035, "BBM FAIL CAPTURE: <A2>ORFAIL,     EVEN DUT PARTIAL FAIL"             , bbm_test_9,{.bbmarg={1, "pat_bbm.mpa",0x060, 100e-9, JudgeOddDutPass,UT_BBM_ORFAIL,     UT_BBM_READFAIL,1,0}} },
#endif

#if 1
  { 8036, "BBM DR MASK     : <A1>MAXFAIL,ALL FAIL"                       	, bbm_test_7,{.bbmarg={1, "pat_bbm.mpa",   0x020, 100e-9, JudgeDrMask,  UT_BBM_MAXFAIL,     UT_BBM_READFAIL,0,0}} }, //OK 
  { 8037, "BBM DR MASK     : <A1>MAXFAIL,ALL MASKED"                       	, bbm_test_5,{.bbmarg={1, "pat_bbm.mpa",   0x020, 100e-9, JudgeDrMask2, UT_BBM_MAXFAIL,     UT_BBM_READFAIL,0,1}} }, //OK
  { 8038, "BBM DR MASK     : <A1>MAXFAIL,ALL NON-MASKED"             	        , bbm_test_6,{.bbmarg={1, "pat_bbm.mpa",   0x020, 100e-9, JudgeAllPF,   UT_BBM_MAXFAIL,     UT_BBM_READFAIL,0,0}} }, //OK
  { 8039, "BBM DR MASK     : <A1>MAXFAIL,PARTIAL FAIL"                          , bbm_test_7,{.bbmarg={1, "pat_bbm.mpa",   0x040, 100e-9, JudgeHalfPass,UT_BBM_MAXFAIL,     UT_BBM_READFAIL,0,0}} }, //OK
  { 8040, "BBM DR MASK     : <A1>MAXFAIL,EVEN BLOCKS MASKED"                    , bbm_test_5,{.bbmarg={1, "pat_bbm.mpa",   0x150, 100e-9, JudgeHalfPass,UT_BBM_MAXFAIL,     UT_BBM_READFAIL,0,1}} }, //OK

  { 8041, "BBM DR MASK     : <A2>MAXFAIL,ALL FAIL"                       	, bbm_test_7,{.bbmarg={1, "pat_bbm.mpa",   0x020, 100e-9, JudgeDrMask,  UT_BBM_MAXFAIL,     UT_BBM_READFAIL,1,0}} },
  { 8042, "BBM DR MASK     : <A2>MAXFAIL,ALL MASKED"                       	, bbm_test_5,{.bbmarg={1, "pat_bbm.mpa",   0x020, 100e-9, JudgeDrMask2, UT_BBM_MAXFAIL,     UT_BBM_READFAIL,1,1}} },
  { 8043, "BBM DR MASK     : <A2>MAXFAIL,ALL NON-MASKED"             	        , bbm_test_6,{.bbmarg={1, "pat_bbm.mpa",   0x020, 100e-9, JudgeAllPF,   UT_BBM_MAXFAIL,     UT_BBM_READFAIL,1,0}} },
  { 8044, "BBM DR MASK     : <A2>MAXFAIL,PARTIAL FAIL"                          , bbm_test_7,{.bbmarg={1, "pat_bbm.mpa",   0x040, 100e-9, JudgeHalfPass,UT_BBM_MAXFAIL,     UT_BBM_READFAIL,1,0}} },
  { 8045, "BBM DR MASK     : <A2>MAXFAIL,EVEN BLOCKS MASKED"                    , bbm_test_5,{.bbmarg={1, "pat_bbm.mpa",   0x150, 100e-9, JudgeHalfPass,UT_BBM_MAXFAIL,     UT_BBM_READFAIL,1,1}} },
  
  { 8046, "BBM BAD BLOCK LIMIT=17 :<A1>"        	                        , bbm_test_2,{.bbmarg={1, "pat_bbm.mpa",   0x170, 100e-9, JudgeLmt,     UT_BBM_MAXFAIL,     UT_BBM_READFAIL,0,0}} }, //OK
  { 8047, "BBM BAD BLOCK LIMIT=17 :<A2>"        	                        , bbm_test_2,{.bbmarg={1, "pat_bbm.mpa",   0x170, 100e-9, JudgeLmt,     UT_BBM_MAXFAIL,     UT_BBM_READFAIL,1,0}} }, //OK
#endif

#if 1 //DDR Fail Capture to BBM (Need Debug)
  { 8048, "BBM FAIL CAPTURE: <A1>MAXFAIL,    ALL FAIL(8WAY)"              	, bbm_test_d1,{.bbmarg={8, "pat_bbm_8w.mpa",0x020, 370e-12, JudgeAllPF,    UT_BBM_MAXFAIL,     UT_BBM_READFAIL,0,0}} }, //OK
  { 8049, "BBM FAIL CAPTURE: <A1>MAXFAIL,    ALL PASS(8WAY)"              	, bbm_test_d1,{.bbmarg={8, "pat_bbm_8w.mpa",0x000, 370e-12, JudgeAllPF,    UT_BBM_MAXFAIL,     UT_BBM_READFAIL,0,1}} }, //OK
  { 8050, "BBM FAIL CAPTURE: <A1>MAXFAIL,PARTIAL FAIL(8WAY)"              	, bbm_test_d1,{.bbmarg={8, "pat_bbm_8w.mpa",0x060, 370e-12, JudgeHalfPass, UT_BBM_MAXFAIL,     UT_BBM_READFAIL,0,0}} }, //OK
  { 8051, "BBM FAIL CAPTURE: <A2>MAXFAIL,    ALL FAIL(8WAY)"              	, bbm_test_d1,{.bbmarg={8, "pat_bbm_8w.mpa",0x020, 370e-12, JudgeAllPF,    UT_BBM_MAXFAIL,     UT_BBM_READFAIL,1,0}} }, //OK
  { 8052, "BBM FAIL CAPTURE: <A2>MAXFAIL,    ALL PASS(8WAY)"              	, bbm_test_d1,{.bbmarg={8, "pat_bbm_8w.mpa",0x000, 370e-12, JudgeAllPF,    UT_BBM_MAXFAIL,     UT_BBM_READFAIL,1,1}} }, //OK
  { 8053, "BBM FAIL CAPTURE: <A2>MAXFAIL,PARTIAL FAIL(8WAY)"              	, bbm_test_d1,{.bbmarg={8, "pat_bbm_8w.mpa",0x060, 370e-12, JudgeHalfPass, UT_BBM_MAXFAIL,     UT_BBM_READFAIL,1,0}} }, //OK

#endif


#if 1
  { 8500, "BBM FAIL CAPTURE: <A1>MAXFAIL,W/ECC(OR,SEC1),  PARTIAL FAIL"         , bbm_test_1,{.bbmarg={1, "pat_ecc_1sec.mpa",     0x000, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCORCOUNT(1), 0,1, 1, UT_SIG_C(0),  50}} },
//{ 8025, "BBM CP MASK     : <A1>DATAGENERATE AFTER ECC(OR,SEC1)"    	        , bbm_test_3,{.bbmarg={1, "pat_bbm.mpa",          0x020, 100e-9, JudgeAftrEcc,UT_BBM_DATACAPTURE,UT_BBM_ECCORCOUNT(1), 0,0, 1, 0,            50}} },
  { 8501, "BBM FAIL CAPTURE: <A1>MAXFAIL,W/ECC(OR,SEC2),  PARTIAL FAIL"         , bbm_test_1,{.bbmarg={1, "pat_ecc_2sec.mpa",     0x000, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCORCOUNT(1),   0,1, 2, UT_SIG_C(31), 86}} },
  { 8502, "BBM FAIL CAPTURE: <A1>MAXFAIL,W/ECC(OR,SEC4),  PARTIAL FAIL"         , bbm_test_1,{.bbmarg={1, "pat_ecc_4sec.mpa",     0x000, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCORCOUNT(1),   0,1, 4, UT_SIG_E(0),   8}} },
  { 8503, "BBM FAIL CAPTURE: <A1>MAXFAIL,W/ECC(OR,SEC8),  PARTIAL FAIL"         , bbm_test_1,{.bbmarg={1, "pat_ecc_8sec.mpa",     0x000, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCORCOUNT(1),   0,1, 8, UT_SIG_E(7), 159}} },
  { 8504, "BBM FAIL CAPTURE: <A1>MAXFAIL,W/ECC(OR,SEC16), PARTIAL FAIL"         , bbm_test_1,{.bbmarg={1, "pat_ecc_16sec.mpa",    0x000, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCORCOUNT(1),   0,1,16, UT_SIG_C(10),255}} },
  { 8505, "BBM FAIL CAPTURE: <A1>MAXFAIL,W/ECC(TOTAL,SEC1), PARTIAL FAIL"       , bbm_test_1,{.bbmarg={1, "pat_ecc_1sec.mpa",     0x200, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCTOTALCOUNT(1),0,1, 1, UT_SIG_C(0),  45}} },
  { 8506, "BBM FAIL CAPTURE: <A1>MAXFAIL,W/ECC(TOTAL,SEC2), PARTIAL FAIL"       , bbm_test_1,{.bbmarg={1, "pat_ecc_2sec.mpa",     0x200, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCTOTALCOUNT(1),0,1, 2, UT_SIG_C(31), 42}} },
  { 8507, "BBM FAIL CAPTURE: <A1>MAXFAIL,W/ECC(TOTAL,SEC4), PARTIAL FAIL"       , bbm_test_1,{.bbmarg={1, "pat_ecc_4sec.mpa",     0x200, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCTOTALCOUNT(1),0,1, 4, UT_SIG_E(0), 136}} },
  { 8508, "BBM FAIL CAPTURE: <A1>MAXFAIL,W/ECC(TOTAL,SEC8), PARTIAL FAIL"       , bbm_test_1,{.bbmarg={1, "pat_ecc_8sec.mpa",     0x200, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCTOTALCOUNT(1),0,1, 8, UT_SIG_E(7), 208}} },
  { 8509, "BBM FAIL CAPTURE: <A1>MAXFAIL,W/ECC(TOTAL,SEC16),PARTIAL FAIL"       , bbm_test_1,{.bbmarg={1, "pat_ecc_16sec.mpa",    0x200, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCTOTALCOUNT(1),0,1,16, UT_SIG_C(10),255}} },

  { 8510, "BBM FAIL CAPTURE: <A2>MAXFAIL,W/ECC(OR,SEC1),  PARTIAL FAIL"         , bbm_test_1,{.bbmarg={1, "pat_ecc_1sec.mpa",     0x000, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCORCOUNT(1),   1,1, 1, UT_SIG_C(0),  50}} },
  { 8511, "BBM FAIL CAPTURE: <A2>MAXFAIL,W/ECC(OR,SEC2),  PARTIAL FAIL"         , bbm_test_1,{.bbmarg={1, "pat_ecc_2sec.mpa",     0x000, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCORCOUNT(1),   1,1, 2, UT_SIG_C(31), 86}} },
  { 8512, "BBM FAIL CAPTURE: <A2>MAXFAIL,W/ECC(OR,SEC4),  PARTIAL FAIL"         , bbm_test_1,{.bbmarg={1, "pat_ecc_4sec.mpa",     0x000, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCORCOUNT(1),   1,1, 4, UT_SIG_E(0),   8}} },
  { 8513, "BBM FAIL CAPTURE: <A2>MAXFAIL,W/ECC(OR,SEC8),  PARTIAL FAIL"         , bbm_test_1,{.bbmarg={1, "pat_ecc_8sec.mpa",     0x000, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCORCOUNT(1),   1,1, 8, UT_SIG_E(7), 159}} },
  { 8514, "BBM FAIL CAPTURE: <A2>MAXFAIL,W/ECC(OR,SEC16), PARTIAL FAIL"         , bbm_test_1,{.bbmarg={1, "pat_ecc_16sec.mpa",    0x000, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCORCOUNT(1),   1,1,16, UT_SIG_C(10),255}} },
  { 8515, "BBM FAIL CAPTURE: <A2>MAXFAIL,W/ECC(TOTAL,SEC1), PARTIAL FAIL"       , bbm_test_1,{.bbmarg={1, "pat_ecc_1sec.mpa",     0x200, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCTOTALCOUNT(1),1,1, 1, UT_SIG_C(0),  45}} },
  { 8516, "BBM FAIL CAPTURE: <A2>MAXFAIL,W/ECC(TOTAL,SEC2), PARTIAL FAIL"       , bbm_test_1,{.bbmarg={1, "pat_ecc_2sec.mpa",     0x200, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCTOTALCOUNT(1),1,1, 2, UT_SIG_C(31), 42}} },
  { 8517, "BBM FAIL CAPTURE: <A2>MAXFAIL,W/ECC(TOTAL,SEC4), PARTIAL FAIL"       , bbm_test_1,{.bbmarg={1, "pat_ecc_4sec.mpa",     0x200, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCTOTALCOUNT(1),1,1, 4, UT_SIG_E(0), 136}} },
  { 8518, "BBM FAIL CAPTURE: <A2>MAXFAIL,W/ECC(TOTAL,SEC8), PARTIAL FAIL"       , bbm_test_1,{.bbmarg={1, "pat_ecc_8sec.mpa",     0x200, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCTOTALCOUNT(1),1,1, 8, UT_SIG_E(7), 208}} },
  { 8519, "BBM FAIL CAPTURE: <A2>MAXFAIL,W/ECC(TOTAL,SEC16),PARTIAL FAIL"       , bbm_test_1,{.bbmarg={1, "pat_ecc_16sec.mpa",    0x200, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCTOTALCOUNT(1),1,1,16, UT_SIG_C(10),255}} },

//{ 8520, "BBM FAIL CAPTURE: <A1>MAXFAIL,W/ECC(OR,SEC16),PARTIAL FAIL(9IO)"     , bbm_test_1,{.bbmarg={1, "pat_ecc_16sec_9io.mpa",0x000, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCTOTALCOUNT(1),0,1,16, UT_SIG_C(0),249}} },
//{ 8521, "BBM FAIL CAPTURE: <A2>MAXFAIL,W/ECC(OR,SEC16),PARTIAL FAIL(9IO)"     , bbm_test_1,{.bbmarg={1, "pat_ecc_16sec_9io.mpa",0x000, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCTOTALCOUNT(1),1,1,16, UT_SIG_C(0),249}} },
//{ 8522, "BBM FAIL CAPTURE: <A1>MAXFAIL,W/ECC(TOTAL,SEC16),PARTIAL FAIL(9IO)"  , bbm_test_1,{.bbmarg={1, "pat_ecc_16sec_9io.mpa",0x200, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCTOTALCOUNT(1),0,1,16, UT_SIG_C(0),249}} },
//{ 8523, "BBM FAIL CAPTURE: <A2>MAXFAIL,W/ECC(TOTAL,SEC16),PARTIAL FAIL(9IO)"  , bbm_test_1,{.bbmarg={1, "pat_ecc_16sec_9io.mpa",0x200, 100e-9, JudgeEcc,    UT_BBM_DATACAPTURE,UT_BBM_ECCTOTALCOUNT(1),1,1,16, UT_SIG_C(0),249}} },
#endif

  { 8524, "BBM FAIL CAPTURE: <A1>MAXFAIL,W/ECC(OR,   SEC16,8WAY),PARTIAL FAIL"  , bbm_test_d2,{.bbmarg={8, "pat_ecc_8w.mpa",       0x040, 370e-12, JudgeEcc,      UT_BBM_MAXFAIL, UT_BBM_ECCORCOUNT(1),   0,1,16, UT_SIG_C(10),155}} },
  { 8525, "BBM FAIL CAPTURE: <A1>MAXFAIL,W/ECC(TOTAL,SEC16,8WAY),PARTIAL FAIL"  , bbm_test_d2,{.bbmarg={8, "pat_ecc_8w.mpa",       0x000, 370e-12, JudgeEcc,      UT_BBM_MAXFAIL, UT_BBM_ECCTOTALCOUNT(1),0,1,16, UT_SIG_C(10),256}} },
  { 8526, "BBM FAIL CAPTURE: <A2>MAXFAIL,W/ECC(OR,   SEC16,8WAY),PARTIAL FAIL"  , bbm_test_d2,{.bbmarg={8, "pat_ecc_8w.mpa",       0x040, 370e-12, JudgeEcc,      UT_BBM_MAXFAIL, UT_BBM_ECCORCOUNT(1),   1,1,16, UT_SIG_C(10),155}} },
  { 8527, "BBM FAIL CAPTURE: <A2>MAXFAIL,W/ECC(TOTAL,SEC16,8WAY),PARTIAL FAIL"  , bbm_test_d2,{.bbmarg={8, "pat_ecc_8w.mpa",       0x000, 370e-12, JudgeEcc,      UT_BBM_MAXFAIL, UT_BBM_ECCTOTALCOUNT(1),1,1,16, UT_SIG_C(10),256}} },

  { 8528, "BBM FAIL CAPTURE: <A1>ECC COUNTER CLEAR(1)"                          , bbm_test_1,{.bbmarg={1, "pat_ecc_nc.mpa",0x000, 100e-9,  JudgeEcc,      UT_BBM_DATACAPTURE, UT_BBM_ECCTOTALCOUNT(1),0,1,16, UT_SIG_C(10),  1}} },
  { 8529, "BBM FAIL CAPTURE: <A1>ECC COUNTER CLEAR(2)"                          , bbm_test_1,{.bbmarg={1, "pat_ecc_nc.mpa",0x050, 100e-9,  JudgeEcc,      UT_BBM_DATACAPTURE, UT_BBM_ECCTOTALCOUNT(1),0,1,16, UT_SIG_C(10),  1}} },





