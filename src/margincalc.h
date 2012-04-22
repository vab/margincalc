/* margincalc.h - Margin Estimation Calculator main header file
 * Copyright (C) 2011 CryptNET, V. Alex Brennen (VAB)
 */
#include "mc_common.h"


/* Data Structures */
struct trade
{
	long	leg1_contracts;
	double	leg1_contract_price;
	double	leg1_strike_price;
	long	leg2_contracts;
	double	leg2_contract_price;
	double  leg2_strike_price;
	long	leg3_contracts;
	double	leg3_contract_price;
	double	leg3_strike_price;

	double stock_price;
};

/* Extern Function Prototypes */
extern int calc_margin_est(int);

/* Function Prototypes */
double calc_short_call_margin_requirement(void);
double calc_short_put_margin_requirement(void);
int collect_trade_data(int);
int display_strategies(void);
int display_strategies_menu(void);
int invalid_argument(void);
int print_help(void);

