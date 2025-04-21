//  TNO,   TESTNAME		               , TEST FUNC  ,  ARGUMENTS
                                                                                                     
  { 13000, "MPSEL PC MAX CHECK:              " , mpsel_test1,    {.mpselarg={1, "pmc",     50e-9,    0.5,   0, 0, NULL, ReadPc,  StartAlpg  }} },
  { 13001, "MPSEL FLAG BAR REGISTER CHECK    " , mpsel_test3,    {.mpselarg={1, "fbrc",    50e-9,    0.0,   3, 1, NULL, ReadPc,  StartAlpg  }} },
  { 13002, "MPSEL FLGJ1 CHECK                " , mpsel_flgj1,    {.mpselarg={1, "flgj",    50e-9,    0.5,  10, 2, NULL, ReadPc,  StartAlpg  }} },
  { 13003, "MPSEL FLGS1 CHECK                " , mpsel_test3,    {.mpselarg={1, "flgs",    50e-9,    0.5,  15, 3, NULL, ReadPc,  StartAlpg  }} },
  { 13004, "MPSEL FLGL1 CHECK                " , mpsel_test3,    {.mpselarg={1, "flgl",    50e-9,    0.5,  21, 4, NULL, ReadPc,  StartAlpg  }} },
  { 13005, "MPSEL STISP CHECK                " , mpsel_isp,      {.mpselarg={1, "stisp",   50e-9,    0.5,  26, 5, NULL, ReadIsp, StartAlpg  }} },
  { 13006, "MPSEL IDX   CHECK                " , mpsel_idx,      {.mpselarg={1, "idx",     50e-9,    0.0,  32,-1, NULL, NULL,    NULL       }} },
  { 13007, "MPSEL CFLG  CHECK                " , mpsel_cflg,     {.mpselarg={1, "cflg",    50e-9,    0.0,  35,-1, NULL, NULL,    NULL       }} },
  { 13008, "MPSEL LOOP  CHECK                " , mpsel_loop,     {.mpselarg={1, "loop",    50e-9,    0.0,  53,-1, NULL, NULL,    NULL       }} },
  { 13009, "MPSEL SUBR  CHECK                " , mpsel_subr,     {.mpselarg={1, "subr",    50e-9,    0.0,  63,-1, NULL, NULL,    NULL       }} },
  { 13010, "MPSEL WAIT  CHECK                " , mpsel_wait,     {.mpselarg={1, "wait",    50e-9,    0.0,  80, 6, NULL, NULL,    NULL       }} },
  { 13011, "MPSEL CALM  CHECK                " , mpsel_calm,     {.mpselarg={1, "calm",    2.857e-9, 0.0,  97,-1, NULL, NULL,    NULL       }} },
//  { 13012, "MPSEL MEASFCT CHECK              " , mpsel_measfct,  {.mpselarg={1, "stps",    50e-9,    0.0, 115, 0, NULL, JudgeTime,TmMeasFct }} },
//  { 13013, "MPSEL STARTFCT CHECK             " , mpsel_startfct, {.mpselarg={1, "stps",    50e-9,    0.0, 115, 0, NULL, JudgeTime,TmStartFct}} },


