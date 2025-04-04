//TNO    TESTNAME                 TEST FUNC     (TEST_flasharg) ILMODE  Pattern                      	Flash Mode  Hold Mode  FLIMIT IDX8   UCM Condition TEST Condition
{ 7200 , "MATCH  DUT          " , flash_test , { .flasharg={    2 ,     "pat_ff_match_01_2way.mpa" , 	"MAXFAIL" , "MATCH"  , 100 ,  30-2 , 1 , 1}}},
{ 7201 , "MATCH  Hold clear   " , flash_test , { .flasharg={    2 ,     "pat_ff_match_02_2way.mpa" , 	"MAXFAIL" , "MATCH"  , 100 ,  30-2 , 1 , 2}}},
{ 7202 , "MATCH  Counter limit" , flash_test , { .flasharg={    2 ,     "pat_ff_match_02_2way.mpa" , 	"MAXFAIL" , "MATCH"  ,  40 ,  50-2 , 2 , 3}}},
{ 7203 , "MATCH  Counter clear" , flash_test , { .flasharg={    2 ,     "pat_ff_match_04_2way.mpa" , 	"MAXFAIL" , "MATCH"  ,  40 ,  50-2 , 2 , 4}}},

{ 7204 , "MATCH2 DUT          " , flash_test , { .flasharg={    2 ,     "pat_ff_match_01_2way.mpa" , 	"MAXFAIL" , "MATCH2" , 100 ,  30-2 , 1 , 5}}},
{ 7205 , "MATCH2 Hold clear   " , flash_test , { .flasharg={    2 ,     "pat_ff_match_02_2way.mpa" , 	"MAXFAIL" , "MATCH2" , 100 ,  30-2 , 1 , 6}}},
{ 7206 , "MATCH2 Counter limit" , flash_test , { .flasharg={    2 ,     "pat_ff_match_02_2way.mpa" , 	"MAXFAIL" , "MATCH2" ,  40 ,  50-2 , 2 , 7}}},
{ 7207 , "MATCH2 Counter clear" , flash_test , { .flasharg={    2 ,     "pat_ff_match_04_2way.mpa" , 	"MAXFAIL" , "MATCH2" ,  40 ,  50-2 , 2 , 8}}},

//RTE after FS1.03_beta1.4 untill bug fix.
//http://exia.mei9.advantest.co.jp/cgi-bin/fswiki/wiki.cgi?page=BugTrack%2DFS%2F4196
{ 7208 , "STACK  DUT          " , flash_test , { .flasharg={    2 ,     "pat_ff_stack_01_2way.mpa" , 	"MAXFAIL" , "STACK"  , 100 ,  50-2 , 3 , 9}}},
{ 7209 , "STACK  Hold clear   " , flash_test , { .flasharg={    2 ,     "pat_ff_stack_02_2way.mpa" , 	"MAXFAIL" , "STACK"  , 100 ,  50-2 , 3 , 10}}},
{ 7210 , "STACK  Counter limit" , flash_test , { .flasharg={    2 ,     "pat_ff_stack_03_2way.mpa" , 	"MAXFAIL" , "STACK"  ,  40 ,  50-2 , 4 , 11}}},
{ 7211 , "STACK  Counter clear" , flash_test , { .flasharg={    2 ,     "pat_ff_stack_04_2way.mpa" , 	"MAXFAIL" , "STACK"  ,  40 ,  50-2 , 4 , 12}}},

{ 7212 , "STACK2 DUT          " , flash_test , { .flasharg={    2 ,     "pat_ff_stack_01_2way.mpa" , 	"MAXFAIL" , "STACK2" , 100 ,  50-2 , 3 , 13}}},
{ 7213 , "STACK2 Hold clear   " , flash_test , { .flasharg={    2 ,     "pat_ff_stack_02_2way.mpa" , 	"MAXFAIL" , "STACK2" , 100 ,  50-2 , 3 , 14}}},
{ 7214 , "STACK2 Counter limit" , flash_test , { .flasharg={    2 ,     "pat_ff_stack_03_2way.mpa" , 	"MAXFAIL" , "STACK2" ,  40 ,  50-2 , 4 , 15}}},
{ 7215 , "STACK2 Counter clear" , flash_test , { .flasharg={    2 ,     "pat_ff_stack_04_2way.mpa" , 	"MAXFAIL" , "STACK2" ,  40 ,  50-2 , 4 , 16}}},

{ 7216 , "STACK  DUT          " , flash_test , { .flasharg={    4 ,     "pat_ff_stack_01_4way.mpa" , 	"MAXFAIL" , "STACK"  , 100 ,  50-2 , 3 , 9}}},
{ 7217 , "STACK  Hold clear   " , flash_test , { .flasharg={    4 ,     "pat_ff_stack_02_4way.mpa" , 	"MAXFAIL" , "STACK"  , 100 ,  50-2 , 3 , 10}}},
{ 7218 , "STACK  Counter limit" , flash_test , { .flasharg={    4 ,     "pat_ff_stack_03_4way.mpa" , 	"MAXFAIL" , "STACK"  ,  40 ,  50-2 , 4 , 11}}},
{ 7219 , "STACK  Counter clear" , flash_test , { .flasharg={    4 ,     "pat_ff_stack_04_4way.mpa" , 	"MAXFAIL" , "STACK"  ,  40 ,  50-2 , 4 , 12}}},

{ 7220 , "STACK2 DUT          " , flash_test , { .flasharg={    4 ,     "pat_ff_stack_01_4way.mpa" , 	"MAXFAIL" , "STACK2" , 100 ,  50-2 , 3 , 13}}},
{ 7221 , "STACK2 Hold clear   " , flash_test , { .flasharg={    4 ,     "pat_ff_stack_02_4way.mpa" , 	"MAXFAIL" , "STACK2" , 100 ,  50-2 , 3 , 14}}},
{ 7222 , "STACK2 Counter limit" , flash_test , { .flasharg={    4 ,     "pat_ff_stack_03_4way.mpa" , 	"MAXFAIL" , "STACK2" ,  40 ,  50-2 , 4 , 15}}},
{ 7223 , "STACK2 Counter clear" , flash_test , { .flasharg={    4 ,     "pat_ff_stack_04_4way.mpa" , 	"MAXFAIL" , "STACK2" ,  40 ,  50-2 , 4 , 16}}},

{ 7224 , "STACK  DUT          " , flash_test , { .flasharg={    8 ,     "pat_ff_stack_01_8way.mpa" , 	"MAXFAIL" , "STACK"  , 100 ,  50-2 , 3 , 9}}},
{ 7225 , "STACK  Hold clear   " , flash_test , { .flasharg={    8 ,     "pat_ff_stack_02_8way.mpa" , 	"MAXFAIL" , "STACK"  , 100 ,  50-2 , 3 , 10}}},
{ 7226 , "STACK  Counter limit" , flash_test , { .flasharg={    8 ,     "pat_ff_stack_03_8way.mpa" , 	"MAXFAIL" , "STACK"  ,  40 ,  50-2 , 4 , 11}}},
{ 7227 , "STACK  Counter clear" , flash_test , { .flasharg={    8 ,     "pat_ff_stack_04_8way.mpa" , 	"MAXFAIL" , "STACK"  ,  40 ,  50-2 , 4 , 12}}},

{ 7228 , "STACK2 DUT          " , flash_test , { .flasharg={    8 ,     "pat_ff_stack_01_8way.mpa" , 	"MAXFAIL" , "STACK2" , 100 ,  50-2 , 3 , 13}}},
{ 7229 , "STACK2 Hold clear   " , flash_test , { .flasharg={    8 ,     "pat_ff_stack_02_8way.mpa" , 	"MAXFAIL" , "STACK2" , 100 ,  50-2 , 3 , 14}}},
{ 7230 , "STACK2 Counter limit" , flash_test , { .flasharg={    8 ,     "pat_ff_stack_03_8way.mpa" , 	"MAXFAIL" , "STACK2" ,  40 ,  50-2 , 4 , 15}}},
{ 7231 , "STACK2 Counter clear" , flash_test , { .flasharg={    8 ,     "pat_ff_stack_04_8way.mpa" , 	"MAXFAIL" , "STACK2" ,  40 ,  50-2 , 4 , 16}}},

{ 7232 , "Flash FM store 1Way " , flash_test , { .flasharg={    1 ,     "pat_ff_match_FMstr_1way.mpa",	"MAXFAIL" , "MATCH"  , 100 ,    99 , 5 , 64}}},
{ 7233 , "Flash FM store 8Way " , flash_test , { .flasharg={    8 ,     "pat_ff_match_FMstr_8way.mpa",	"MAXFAIL" , "MATCH"  , 100 ,    99 , 5 , 64}}},

