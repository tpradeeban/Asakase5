//TNO,TESTNAME                     , TEST FUNC                          mpat                , pc_addr, hlimit, llimit, exp
{ 600, "Pattern_Burst_wait OUT2"   , pattern_burst_wait , {.burstarg={ "pat_burst.mpa"      , 0x490, 0    , 0    , 0}}},
{ 610, "Pattern_Burst_sti OUT2"    , pattern_burst_sti  , {.burstarg={ "pat_burst.mpa"      , 0x500, 0    , 0    , 0}}},
{ 620, "Pattern_Burst_stisp OUT2"  , pattern_burst_stisp, {.burstarg={ "pat_burst.mpa"      , 0x510, 0    , 0    , 0}}},

{ 630, "Pattern_Burst_wait OUT"    , pattern_burst_wait , {.burstarg={ "pat_burst.mpa"      , 0x520, 0    , 0    , 0}}},
{ 640, "Pattern_Burst_sti OUT"     , pattern_burst_sti  , {.burstarg={ "pat_burst.mpa"      , 0x530, 0    , 0    , 0}}},
{ 650, "Pattern_Burst_stisp OUT"   , pattern_burst_stisp, {.burstarg={ "pat_burst.mpa"      , 0x540, 0    , 0    , 0}}},

{ 660, "Pattern_Burst_inh default" , pattern_burst_inh  , {.burstarg={ "pat_burst_inout.mpa", 0x000,  6.12,  5.88, 0}}},
{ 661, "Pattern_Burst_inh OUT"     , pattern_burst_inh  , {.burstarg={ "pat_burst_inout.mpa", 0x010, -4.90, -5.10, 0}}},
{ 662, "Pattern_Burst_inh OUT2"    , pattern_burst_inh  , {.burstarg={ "pat_burst_inout.mpa", 0x020, -4.90, -5.10, 0}}},

{ 665, "Pattern_Burst_inhh default", pattern_burst_inhh , {.burstarg={ "pat_burst_inout.mpa", 0x100, 10.28,  9.72, 0}}},
{ 666, "Pattern_Burst_inhh OUT"    , pattern_burst_inhh , {.burstarg={ "pat_burst_inout.mpa", 0x050, 29.70, 28.30, 0}}},
{ 667, "Pattern_Burst_inhh OUT2"   , pattern_burst_inhh , {.burstarg={ "pat_burst_inout.mpa", 0x060, 29.70, 28.30, 0}}},

{ 670, "Pattern_Burst_vt default"  , pattern_burst_vt   , {.burstarg={ "pat_burst_inout.mpa", 0x000,  2.04,  1.96, 0}}},
{ 671, "Pattern_Burst_vt OUT"      , pattern_burst_vt   , {.burstarg={ "pat_burst_inout.mpa", 0x110, -0.98, -1.02, 0}}},
{ 672, "Pattern_Burst_vt OUT2"     , pattern_burst_vt   , {.burstarg={ "pat_burst_inout.mpa", 0x120, -0.98, -1.02, 0}}},

{ 680, "Pattern_Burst_vio default" , pattern_burst_inout, {.burstarg={ "pat_burst_inout.mpa", 0x200, 0    , 0    , 0x0}}},
{ 681, "Pattern_Burst_vih OUT"     , pattern_burst_inout, {.burstarg={ "pat_burst_inout.mpa", 0x210, 0    , 0    , 0x1}}},
{ 682, "Pattern_Burst_vih OUT2"    , pattern_burst_inout, {.burstarg={ "pat_burst_inout.mpa", 0x220, 0    , 0    , 0x1}}},
{ 683, "Pattern_Burst_vil OUT"     , pattern_burst_inout, {.burstarg={ "pat_burst_inout.mpa", 0x230, 0    , 0    , 0x2}}},
{ 684, "Pattern_Burst_vil OUT2"    , pattern_burst_inout, {.burstarg={ "pat_burst_inout.mpa", 0x240, 0    , 0    , 0x2}}},

{ 691, "Pattern_Burst_voh OUT"     , pattern_burst_inout, {.burstarg={ "pat_burst_inout.mpa", 0x310, 0    , 0    , 0x1}}},
{ 692, "Pattern_Burst_voh OUT2"    , pattern_burst_inout, {.burstarg={ "pat_burst_inout.mpa", 0x320, 0    , 0    , 0x1}}},
{ 693, "Pattern_Burst_vol OUT"     , pattern_burst_inout, {.burstarg={ "pat_burst_inout.mpa", 0x330, 0    , 0    , 0x2}}},
{ 694, "Pattern_Burst_vol OUT2"    , pattern_burst_inout, {.burstarg={ "pat_burst_inout.mpa", 0x340, 0    , 0    , 0x2}}},

{ 695, "Pattern_Burst_max OUT"     , pattern_burst_inout, {.burstarg={ "pat_burst_inout.mpa", 0x410, 0    , 0    , 0x3}}},
{ 696, "Pattern_Burst_max OUT2"    , pattern_burst_inout, {.burstarg={ "pat_burst_inout.mpa", 0x420, 0    , 0    , 0x3}}},

