/* mc_common.h - Margin Estimation Calculator common header file
 * Copyright (C) 2011 CryptNET, V. Alex Brennen (VAB)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define D_LONG_CALL					1
#define D_LONG_CALL_LEAP			2
#define D_SHORT_CALL				3
#define D_LONG_PUT					4
#define D_LONG_LEAP_PUT				5
#define D_SHORT_PUT					6
#define D_COVERED_CALL				7
#define D_LONG_CALL_SHORT_STOCK		8
#define D_LONG_PUT_LONG_STOCK		9
#define D_SHORT_PUT_SHORT_STOCK		10
#define D_LONG_STRADDLE				11
#define D_SHORT_STRADDLE			12
#define D_LONG_STRANGLE				13
#define D_SHORT_STRANGLE			14
#define D_LONG_CALL_SPREAD			15
#define D_SHORT_CALL_SPREAD			16
#define D_LONG_PUT_SPREAD			17
#define D_SHORT_PUT_SPREAD			18
#define D_LONG_CALL_TIME_SPREAD		19
#define D_SHORT_CALL_TIME_SPREAD	20
#define D_LONG_PUT_TIME_SPREAD		21
#define D_SHORT_PUT_TIME_SPREAD		22
#define D_LONG_CALL_BUTTERFLY		23
#define D_SHORT_CALL_BUTTERFLY		24
#define D_LONG_PUT_BUTTERFLY		25
#define D_SHORT_PUT_BUTTERFLY		26
#define D_CALL_BACK_SPREAD			27
#define D_PUT_BACK_SPREAD			28
#define D_RATIO_CALL_SPREAD			29
#define D_RATIO_PUT_SPREAD			30
#define D_COLLAR					31
