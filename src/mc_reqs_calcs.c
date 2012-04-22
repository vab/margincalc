/* mc_reqs_calc.h - Margin Estimation Calculator margin calculations source file
 * Copyright (C) 2011 CryptNET, V. Alex Brennen (VAB)
 */

#include "mc_reqs_calcs.h"


int calc_margin_est(int strategy)
{
	long shares = 0;
	long contracts = 0;
	double stock_price = 0.00;
	double strike_price = 0.00;
	double option_price = 0.00;
	double margin_requirement = 0.00;
	double margin_maint_requirement = 0.00;
	double out_of_the_money = 0.00;

	/* For complex trades */
	long leg1_contracts = 0;
	double leg1_strike_price = 0.00;
	double leg1_contract_price = 0.00;

	long leg2_contracts = 0;
	double leg2_strike_price = 0.00;
	double leg2_contract_price = 0.00;

	long leg3_contracts = 0;
	double leg3_strike_price = 0.00;
	double leg3_contract_price = 0.00;

	strategy = 29;
	contracts = 10;
	shares = 1000;
	strike_price = 345.00;
	stock_price = 337.51;
	option_price = 1.00;

	/* For complex trades */
	leg1_contracts = 10;
	leg1_strike_price = 335.00;
	leg1_contract_price = 2.25;
	leg2_contracts = 20;
	leg2_strike_price = 345.00;
	leg2_contract_price = .75;
	leg3_contracts = 10;
	leg3_strike_price = 355.00;
	leg3_contract_price = 3.75;

	printf("%d\n\n", strategy);

	if(strategy == D_LONG_CALL) /* OK */
	{
		/* Long Call - 9 Months or Less */
		/* 100% of the call price */
		leg1_contract_price = leg1_contract_price * 100;
		margin_requirement = leg1_contract_price * leg1_contracts;
		margin_maint_requirement = margin_requirement;

		printf("\n\n");
		printf("%.2f margin is required.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_LONG_CALL_LEAP) /* OK */
	{
		/* Long Call - More than 9 Months */
		/* 75% of the cost of the call */
		option_price = option_price * 100;
		margin_requirement = (option_price * contracts) * .75;
		margin_maint_requirement = margin_requirement;

		printf("\n\n");
		printf("%.2f margin is required.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_SHORT_CALL)
	{
		/* Short Call */
		option_price = option_price * 100;
		stock_price = stock_price * 100;
		strike_price = strike_price * 100;

		out_of_the_money = strike_price - stock_price;
		if(out_of_the_money < 0)
		{
			out_of_the_money = 0;
		}	

		margin_requirement = (option_price + ((stock_price * .20) - out_of_the_money)) * contracts;
		margin_maint_requirement = margin_requirement - option_price * contracts;

		printf("\n\n");
		printf("%.2f margin is required.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_LONG_PUT) /* OK */
	{
		/* Long Put - 9 Months or Less */
		/* 100% of Option Price*/
		option_price = option_price * 100;
		margin_requirement = option_price * contracts;
		margin_maint_requirement = margin_requirement;

		printf("\n\n");
		printf("%.2f margin is required.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_LONG_LEAP_PUT) /* OK */
	{
		/* Long Put - 9 Months or More */
		option_price = option_price * 100;
		margin_requirement = (option_price * contracts) * .75;
		margin_maint_requirement = margin_requirement;

		printf("\n\n");
		printf("%.2f margin is required.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_SHORT_PUT)
	{
		/* Short Put */
		option_price = option_price * 100;
		stock_price = stock_price * 100;
		strike_price = strike_price * 100;

		out_of_the_money = strike_price - stock_price;
		if(out_of_the_money < 0)
		{
			out_of_the_money = 0;
		}

		margin_requirement = (option_price + ((stock_price * .20) - out_of_the_money)) * contracts;
		margin_maint_requirement = margin_requirement - option_price * contracts;

		printf("\n\n");
		printf("%.2f margin is required.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_COVERED_CALL)
	{
		/* Covered Call */
		margin_requirement = (stock_price * .50) * shares;
		margin_maint_requirement = margin_requirement;

		printf("\n\n");
		printf("%.2f margin is required.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_LONG_CALL_SHORT_STOCK) /* OK */
	{
		/* Long Call & Short Underlying Stock */
		double net_proceeds = 0.0;

		option_price = option_price * 100;
		
		/* Long Call Options Margin Requirements */
		margin_requirement = option_price * contracts;
		printf("\n\n");
		printf("%.2f margin is required for Long Call Option(s).\n", margin_requirement);

		/* Margin Requirements for Short Stock */
		margin_requirement = (stock_price * shares) * 1.50;
		printf("%.2f is margin requirement for short stock.\n", margin_requirement);

		/* Margin Requirement for Long Call Option(s) and Underlying Short Stock */
		net_proceeds = stock_price * shares;
		margin_maint_requirement = (margin_requirement - net_proceeds) + (option_price * contracts);

		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_LONG_PUT_LONG_STOCK)
	{
		/* Long Put & Long Underlying Stock */
		option_price = option_price * 100;

		/* Long Put Margin Requirements */
		margin_requirement = option_price * contracts;
		printf("\n\n");
		printf("%.2f margin is required for Long Put Option(s).\n", margin_requirement);

		/* Margin Requirements for Long Stock */
		margin_requirement = (stock_price * shares) * .50;
		printf("%.2f is margin requirement for stock.\n", margin_requirement);

		/* Margin Requirement for Long Put Option(s) and Long Underlying Stock */
		margin_maint_requirement = margin_requirement + (option_price * contracts);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_SHORT_PUT_SHORT_STOCK)
	{
		/* Short Put & Short underlying stock */
		double option_proceeds = 0.0;
		double stock_proceeds = 0.0;

		option_price = option_price * 100;
		option_proceeds = option_price * contracts;
		stock_proceeds = stock_price * shares;

		/* Margin Requirements for Short Stock */
		margin_requirement = (stock_price * shares) * 1.50;
		printf("%.2f is margin requirement for short stock.\n", margin_requirement);

		/* Margin Requirements for Short Put and Short Underlying Stock */
		margin_maint_requirement = (margin_requirement - stock_proceeds) - (option_price * contracts);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_LONG_STRADDLE)
	{
		/* Long Straddle */
		double leg1_option_cost = 0.0;
		double leg2_option_cost = 0.0;	


		/* Margin Requirements for Long Call(s) */
		leg1_contract_price = leg1_contract_price * 100;
		leg1_option_cost = leg1_contract_price * contracts; 

		/* Margin Requirements for Long Put(s) */
		leg2_contract_price = leg2_contract_price * 100;
		leg2_option_cost = leg2_contract_price * contracts;

		/* Margin Requirements for Trade */
		margin_maint_requirement = leg1_option_cost + leg2_option_cost;
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_SHORT_STRADDLE)
	{
		/* Short Straddle */
		/* CBOE Requirements:
			* short call(s) or short put(s) requirement, whichever is greater, plus the
				option proceeds of the other side
			* proceeds from sale of entire straddle may be applied to initial margin requirement
			* after position is established, ongoing maintenance margin requirement applies,
				and an increase (or decrease) in the margin required is possible
		*/
		double short_call_margin_req = 0.0;
		double short_call_proceeds = 0.0;
		double short_put_margin_req = 0.0;
		double short_put_proceeds = 0.0;


		/* short call requirement */
		leg1_contract_price = leg1_contract_price * 100;
		stock_price = stock_price * 100;
		leg1_strike_price = leg1_strike_price * 100;

		out_of_the_money = leg1_strike_price - stock_price;
		if(out_of_the_money < 0)
		{
			out_of_the_money = 0;
		}

		short_call_margin_req = (leg1_contract_price + ((stock_price * .20) - out_of_the_money)) * leg1_contracts;
		printf("%.2f is short call  margin requirement.\n", short_call_margin_req);
		short_call_proceeds = leg1_contract_price * leg1_contracts;

		/* short put requirement */
		leg2_contract_price = leg2_contract_price * 100;
		leg2_strike_price = leg2_strike_price * 100;

		out_of_the_money = stock_price - leg2_strike_price;
		if(out_of_the_money < 0)
		{
			out_of_the_money = 0;
		}

		short_put_margin_req = (leg2_contract_price + ((stock_price * .20) - out_of_the_money)) * leg2_contracts;
 		printf("(%.2f + ((%.2f * .20) - %.2f)) * %ld)\n", leg2_contract_price, stock_price, out_of_the_money, leg2_contracts);
		printf("%.2f is short put margin requirement.\n", short_put_margin_req);
		short_put_proceeds = leg2_contract_price * leg2_contracts;

		if(short_call_margin_req >= short_put_margin_req)
		{
			margin_requirement = short_call_margin_req + short_put_proceeds;
		}
		else
		{
			margin_requirement = short_put_margin_req + short_call_proceeds;
		}

		margin_maint_requirement = margin_requirement - (short_call_proceeds + short_put_proceeds);
		printf("%.2f is initial margin requirement.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_LONG_STRANGLE)
	{
		/* Long Strangle */
		/* CBOE Requirements:
			* each call and each put must be paid for in full; cash need
				not be deposited in excess of call(s) and put(s) cost
		*/
		if(leg1_strike_price == leg2_strike_price)
		{
			fprintf(stderr,"Error: Option strike prices cannot be the same.\n");

			return -1;
		}
		leg1_contract_price = leg1_contract_price * 100;
		leg2_contract_price = leg2_contract_price * 100;

		margin_requirement = (leg1_contract_price + leg2_contract_price) * contracts;
		margin_maint_requirement = margin_requirement;
		printf("%.2f is initial margin requirement.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_SHORT_STRANGLE) /* OK */
	{
		/* Short Strangle */
		/* CBOE Requirements:
			* short call(s) or short put(s) requirement, whichever is greater,
				plus the option proceeds of the other side
			* proceeds from sale of entire strangle may be applied to initial
				margin requirement
			* after position is established, ongoing maintenance margin requirement
				applies, and an increase (or decrease) in the margin required is possible
		*/
		double short_put_margin = 0.0;
		double short_call_margin = 0.0;
		
		leg1_contract_price = leg1_contract_price * 100;
		leg2_contract_price = leg2_contract_price * 100;
		stock_price = stock_price * 100;
		leg1_strike_price = leg1_strike_price * 100;
		leg2_strike_price = leg2_strike_price * 100;
		
		if(leg1_contracts != leg2_contracts)
		{
			fprintf(stderr,"The number of call and put contracts must be the same.\n");
			
			return -1;
		}

		if(leg1_strike_price == leg2_strike_price)
		{
			fprintf(stderr,"The contract strike prices must be different.\n");
			
			return -1;
		}
		
		/* TODO: must be same expiration month */

		/* short call margin requirement (3) */
		out_of_the_money = leg1_strike_price - stock_price;
		if(out_of_the_money < 0)
		{
			out_of_the_money = 0;
		}	

		short_call_margin = (leg1_contract_price + ((stock_price * .20) - out_of_the_money)) * leg1_contracts;
		
		/* Short put margin requirement (6) */
		out_of_the_money = stock_price - leg2_strike_price;
		if(out_of_the_money < 0)
		{
			out_of_the_money = 0;
		}	

		short_put_margin = (leg2_contract_price + ((stock_price * .20) - out_of_the_money)) * leg2_contracts;

		
		if(short_call_margin > short_put_margin)
		{
			margin_requirement = short_call_margin + (leg2_contract_price * leg2_contracts);
			printf("%.2f margin is required for short call.\n", margin_requirement);
		}
		else /* short_put margin > short_call_margin */
		{
			margin_requirement = short_put_margin + (leg1_contract_price * leg1_contracts);
			printf("%.2f margin is required for short put.\n", margin_requirement);
		}
		margin_maint_requirement = margin_requirement - ((leg1_contract_price * leg1_contracts) + 
										(leg2_contract_price * leg2_contracts));
		printf("\n\n");
		printf("%.2f margin is required.\n", margin_maint_requirement);
	}
	else if(strategy == D_LONG_CALL_SPREAD)
	{
		/* Long Call Spread */
		/* CBOE Requirements:
			* no margin required on short call(s)
			* long call(s) must be paid for in full
			* proceeds received from sale of short call(s) may be applied to the 
				cost of the long call(s)
			* the short call(s) may expire before the long call(s) and not affect
				margin requirement
		*/
		leg1_contract_price = leg1_contract_price * 100;
		leg2_contract_price = leg2_contract_price * 100;

		margin_requirement = (leg1_contract_price * contracts) - (leg2_contract_price * contracts);
		margin_maint_requirement = margin_requirement;
		printf("%.2f is initial margin requirement.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_SHORT_CALL_SPREAD)
	{
		/* Short Call Spread */
		/* CBOE Requirements:
			* the amount by which the short call aggregate strike price is below
				the long call aggregate strike price (aggregate strike price = number
				of contracts x strike price x $100)
			* long call(s) must be paid for in full
			* proceeds received from sale of short call(s) may be applied to the initial
				margin requirement
			* the short call(s) may expire before the long call(s) and not affect margin
				requirement
		*/
		double long_call_margin_req = 0.0;
		double short_call_margin_req = 0.0;
		
		leg1_contract_price = leg1_contract_price * 100;
		leg2_contract_price = leg2_contract_price * 100;
		
		/* Number of contracts must be the same */
		if(leg1_contracts != leg2_contracts)
		{
			fprintf(stderr,"The number of calls sold must be equal to the number of calls bought.\n");
			
			return -1;
		}
		
		/* Strike price of calls sold must be more than calls bought */
		if((leg1_strike_price < leg2_strike_price) || (leg1_strike_price == leg2_strike_price))
		{
			fprintf(stderr,"The strike price of calls purchased must be greated than the stike");
			fprintf(stderr," price of calls sold.\n");

			return -1;
		}

		/* Leg1: Long Calls that must be paid for in full. */
		long_call_margin_req = leg1_contract_price * leg1_contracts;

		/* Leg2: amount of short call aggregate strike price below long aggregate strike price */
		short_call_margin_req = ((leg1_strike_price * 100 * leg1_contracts) - 
									(leg2_strike_price * 100 * leg2_contracts));

		margin_requirement = long_call_margin_req + short_call_margin_req;
		printf("%.2f is the initial margin requirement.\n",margin_requirement);
		margin_maint_requirement = margin_requirement - (leg2_contract_price * leg2_contracts);
		printf("%.2f is the margin maintenance requirement.\n",margin_maint_requirement);
	}
	else if(strategy == D_LONG_PUT_SPREAD)
	{
		/* Long Put Spread */
		/* CBOE Requirements:
			* no margin required on short put(s)
			* long put(s) must be paid for in full
			* proceeds received from sale of short put(s) may be applied to the cost
				of the long put(s)
			* the short put(s) may expire before the long put(s) and not affect margin
				requirement
		*/
		leg1_contract_price = leg1_contract_price * 100;
		leg2_contract_price = leg2_contract_price * 100;

		margin_requirement = (leg1_contract_price * contracts) - (leg2_contract_price * contracts);
		margin_maint_requirement = margin_requirement;
		printf("%.2f is initial margin requirement.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_SHORT_PUT_SPREAD)
	{
		/* Short Put Spread */
		/* CBOE Requirements:
			* the amount by which the long put aggregate strike price is below the short
				put aggregate strike price (aggregate strike price = number of
				contracts x strike price x $100)
			* long put(s) must be paid for in full
			* proceeds received from sale of short put(s) may be applied to the initial 
				margin requirement
			* the short put(s) may expire before the long put(s) and not affect margin
				requirement
		*/
		double long_put_margin_req = 0.0;
		double short_put_margin_req = 0.0;

		leg1_contract_price = leg1_contract_price * 100;  /* Buy */
		leg2_contract_price = leg2_contract_price * 100;  /* Sell */

		/* Number of contracts must be the same */
		if(leg1_contracts != leg2_contracts)
		{
			fprintf(stderr,"The number of puts sold must be equal to the number of puts bought.\n");

			return -1;
		}
		
		/* Strike price of puts purchased must be less than those of puts sold. */
		if((leg1_strike_price > leg2_strike_price) || (leg1_strike_price == leg2_strike_price))
		{
			fprintf(stderr,"The strike price of the put contracts purchased must be less than the cost of");
			fprintf(stderr,"the put contracts sold.\n");

			return -1;
		}

		/* Leg 1: Long Puts must be paid for in full */
		long_put_margin_req = leg1_contract_price * leg1_contracts;

		/* Leg2: amount of long put aggregate strike price below short aggregate strike price */
		short_put_margin_req = ((leg2_strike_price * 100 * leg2_contracts) - 
									(leg1_strike_price * 100 * leg1_contracts));

		margin_requirement = long_put_margin_req + short_put_margin_req;
		printf("%.2f is the initial margin requirement.\n",margin_requirement);
		margin_maint_requirement = margin_requirement - (leg2_contract_price * leg2_contracts);
		printf("%.2f is the margin maintenance requirement.\n",margin_maint_requirement);
	}
	else if(strategy == D_LONG_CALL_TIME_SPREAD)
	{
		/* Long Call Time Spread */
		/* CBOE Requirements:
			no margin required on short call(s)
			long call(s) must be paid for in full
			proceeds received from sale of short call(s) may be applied to the cost of the long call(s)
			the short call(s) must expire before the long call(s) for margin to be calculated as above
		*/
		double long_call_margin_requirement = 0.0;
		double short_call_margin_requirement = 0.0;

		leg1_contract_price = leg1_contract_price * 100; /* Buy */
		leg2_contract_price = leg2_contract_price * 100; /* Sell */

		/* Number of contracts must be the same */
		if(leg1_contracts != leg2_contracts)
		{
			fprintf(stderr,"The number of calls sold must be equal to the number of calls bought.\n");

			return -1;
		}

		/* Strike price of puts purchased must be less than those of puts sold. */
		if(leg1_strike_price != leg2_strike_price)
		{
			fprintf(stderr,"The strike price of the call contracts must be the same.\n");
			
			return -1;
		}
		
		/* TODO: Leg1 purchased calls must expire later than leg2 sold contracts */

		/* Leg 1: Long calls must be paid for in full */
		long_call_margin_requirement = leg1_contracts * leg1_contract_price;

		/* Leg 2: No margin requirement on short calls */
		short_call_margin_requirement = 0.0;

		margin_requirement = long_call_margin_requirement;
		printf("%.2f is the initial margin requirement.\n",margin_requirement);

		/* Proceeds from short call sale can be used against log call margin requirement */
		margin_maint_requirement = margin_requirement - (leg2_contracts * leg2_contract_price);
		printf("%.2f is the margin maintenance rquirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_SHORT_CALL_TIME_SPREAD)
	{
		/* Short Call Time Spread */
		/* CBOE Requirements:
			* both sides must be treated as separate positions (total of requirements for
				long call(s) and for uncovered short call(s))
			* after position is established, ongoing maintenance margin requirement applies
				to uncovered short call(s) portion, and an increase (or decrease) in 
				the margin required is possible
			* the short call(s) must expire after the long call(s) for margin to be
				calculated as above
		*/
		double long_call_margin_requirement = 0.0;
		double short_call_margin_requirement = 0.0;
		double out_of_the_money = 0.0;


		leg1_contract_price = leg1_contract_price * 100; /* Buy Long calls in near month */
		leg2_contract_price = leg2_contract_price * 100; /* Sell Short calls in far month */
		leg1_strike_price = leg1_strike_price * 100;
		leg2_strike_price = leg2_strike_price * 100;
		stock_price = stock_price * 100;

		/* Number of contracts must be the same */
		if(leg1_contracts != leg2_contracts)
		{
			fprintf(stderr,"The number of calls sold must be equal to the number of calls bought.\n");
			
			return -1;
		}

		/* Strike price of puts purchased must be less than those of puts sold. */
		if(leg1_strike_price != leg2_strike_price)
		{
			fprintf(stderr,"The strike price of the call contracts must be the same.\n");
			
			return -1;
		}

		/* TODO: Short call must expire after the long call */

		/* Leg 1: Long Call Requirements */
		long_call_margin_requirement = (leg1_contract_price * leg1_contracts);

		printf("\n\n");
		printf("%.2f margin is required for long call.\n", long_call_margin_requirement);
		
		/* Leg 2: Short Call Requirement */
		out_of_the_money = leg2_strike_price - stock_price;
		if(out_of_the_money < 0)
		{
			out_of_the_money = 0;
		}	

		short_call_margin_requirement = (leg2_contract_price + ((stock_price * .20) -
											out_of_the_money)) * leg2_contracts;
		margin_maint_requirement = short_call_margin_requirement - leg2_contract_price * leg2_contracts;

		printf("%.2f margin is required for short call.\n", short_call_margin_requirement);
		margin_requirement = long_call_margin_requirement + short_call_margin_requirement;
		printf("%.2f total margin is required.\n", margin_requirement);
		margin_maint_requirement = margin_requirement - (leg2_contract_price * leg2_contracts);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_LONG_PUT_TIME_SPREAD)
	{
		/* Long Put Time Spread */
		/* CBOE Requirements:
			* no margin required on short put(s)
			* long put(s) must be paid for in full
			* proceeds received from sale of short put(s) may be applied to the
				cost of the long put(s)
			* the short put(s) must expire before the long put(s) for margin to
				be calculated as above
		*/
		leg1_contract_price = leg1_contract_price * 100;
		leg2_contract_price = leg2_contract_price * 100;

		/* TODO: Short Put must expire before Log Put */
		margin_requirement = (leg1_contract_price * contracts) - (leg2_contract_price * contracts);
		margin_maint_requirement = margin_requirement;
		printf("%.2f is initial margin requirement.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);

	}
	else if(strategy == D_SHORT_PUT_TIME_SPREAD)
	{
		/* Short Put Time Spread */
		/* CBOE Requirements:
			* both sides must be treated as separate positions (total of requirements
				for long put(s) and for uncovered short put(s))
			* after position is established, ongoing maintenance margin requirement
				applies to uncovered short put(s) portion, and an increase (or
				decrease) in the margin required is possible
			* the short put(s) must expire after the long put(s) for margin to be
				calculated as above
		*/
		double long_put_margin_requirement = 0.0;
		double short_put_margin_requirement = 0.0;


		leg1_contract_price = leg1_contract_price * 100;
		leg2_contract_price = leg2_contract_price * 100;

		/* Number of contracts must be the same */
		if(leg1_contracts != leg2_contracts)
		{
			fprintf(stderr,"The number of puts sold must be equal to the number of puts bought.\n");

			return -1;
		}

		/* Strike price of puts purchased must be less than those of puts sold. */
		if(leg1_strike_price != leg2_strike_price)
		{
			fprintf(stderr,"The strike price of the put contracts must be the same.\n");

			return -1;
		}

		/* TODO: Leg2 short puts must expire after Leg1 log puts */

		/* Leg 1: Long put purchase */
		long_put_margin_requirement = leg1_contract_price * leg1_contracts;

		printf("\n\n");
		printf("%.2f margin is required for long put.\n", long_put_margin_requirement);

		/* Leg 2: Short put sale */
		stock_price = stock_price * 100;
		out_of_the_money = leg2_strike_price - stock_price;
		if(out_of_the_money < 0)
		{
			out_of_the_money = 0;
		}

		short_put_margin_requirement = (leg2_contract_price + ((stock_price * .20) - out_of_the_money)) * leg2_contracts;
		printf("%.2f margin is required for short put.\n", short_put_margin_requirement);
		margin_requirement = short_put_margin_requirement + long_put_margin_requirement;
		margin_maint_requirement = margin_requirement - leg2_contract_price * leg2_contracts;

		printf("%.2f margin is required.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);

	}
	else if(strategy == D_LONG_CALL_BUTTERFLY)
	{
		/* Long Call Butterfly */
		/* CBOE Requirements:
			* total net debit for spread must be paid in full
			* one of the long legs may expire after the short and not affect margin
				requirement
		*/
		double net_debit = 0.0;

		/* TODO: Intervals between strike prices must be the same. */
		leg1_contract_price = leg1_contract_price * 100; /* Buy */
		leg2_contract_price = leg2_contract_price * 100; /* Sell */
		leg3_contract_price = leg3_contract_price * 100; /* Buy */

		if((leg2_contracts != (leg1_contracts * 2)) || (leg2_contracts != (leg3_contracts * 2)))
		{
			fprintf(stderr, "Incorrect option trade contract ratio.\n");

			return -1;
		}

		net_debit = ((leg1_contract_price * leg1_contracts) + (leg3_contract_price * leg3_contracts)) -
				(leg2_contract_price * leg2_contracts);
		if(net_debit < 0.0)
		{
			fprintf(stderr, "The trade must execute at a net debit.\n");

			return -1;
		}
		margin_requirement = net_debit;
		margin_maint_requirement = margin_requirement;
		printf("%.2f is initial margin requirement.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_SHORT_CALL_BUTTERFLY)
	{
		/* Short Call Butterfly */
		/* CBOE Requirements:
			* the amount of the aggregate difference between the two lowest strike
				prices (aggregate difference = number of spreads x difference in
				strike prices x $100)
			* long calls must be paid for in full
			* proceeds received from sale of short option components may be applied
				to the total initial margin requirement
		*/
		double short_call_margin_requirement = 0.0;
		double long_call_margin_requirement = 0.0;
		double net_proceeds = 0.0;


		leg1_contract_price = leg1_contract_price * 100; /* sell */
		leg2_contract_price = leg2_contract_price * 100; /* buy */
		leg3_contract_price = leg3_contract_price * 100; /* sell */
		leg1_strike_price = leg1_strike_price * 100;
		leg2_strike_price = leg2_strike_price * 100;
		leg3_strike_price = leg3_strike_price * 100;

		if( (leg1_contracts != leg3_contracts) || (leg2_contracts != (leg1_contracts * 2)) )
		{
			fprintf(stderr, "Short call Butterfly must be in leg ratio 1:2:1\n");

			return -1;
		}

		if( (leg3_strike_price - leg2_strike_price) != (leg2_strike_price - leg1_strike_price) )
		{
			fprintf(stderr, "The difference between the strike prices must be the same.\n");

			return -1;
		}
		
		if( ( ((leg1_contract_price * leg1_contracts) + (leg3_contract_price * leg3_contracts)) -
				(leg2_contract_price * leg2_contracts)) <= 0)
		{
			fprintf(stderr, "The trade must execute at a net credit.\n");
			
			return -1;
		}
		
		/* TODO: Expiration months must be the same */
		
		/* Long Call Margin Requirements */
		long_call_margin_requirement = leg2_contract_price * leg2_contracts;
		printf("%.2f margin requirement for long call(s).\n",long_call_margin_requirement);

		/* Short Call Margin Requirements */
		short_call_margin_requirement = (leg2_strike_price - leg1_strike_price) * leg1_contracts;
		printf("%.2f margin_requiremnt for short calls.\n",short_call_margin_requirement);

		net_proceeds = (leg1_contract_price * leg1_contracts) + (leg3_contract_price * leg3_contracts);

		margin_requirement = long_call_margin_requirement + short_call_margin_requirement;
		margin_maint_requirement = margin_requirement - net_proceeds;
		printf("%.2f is initial margin requirement.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_LONG_PUT_BUTTERFLY)
	{
		/* Long Put Butterfly */
		/* CBOE Requirements:
			* total net debit for spread must be paid in full
			* one of the long legs may expire after the short and not affect margin
				requirement
		*/
		double net_debit = 0.0;

		leg1_contract_price = leg1_contract_price * 100; /* Buy */
		leg2_contract_price = leg2_contract_price * 100; /* Sell */
		leg3_contract_price = leg3_contract_price * 100; /* Buy */
		
		if((leg2_contracts != (leg1_contracts * 2)) || (leg2_contracts != (leg3_contracts * 2)))
		{
			fprintf(stderr, "Incorrect option trade contract ratio.\n");

			return -1;
		}

		net_debit = ((leg1_contract_price * leg1_contracts) + (leg3_contract_price * leg3_contracts)) -
				(leg2_contract_price * leg2_contracts);
		if(net_debit < 0.0)
		{
			fprintf(stderr, "The trade must execute at a net debit.\n");

			return -1;
		}

		margin_requirement = net_debit;
		margin_maint_requirement = margin_requirement;
		printf("%.2f is initial margin requirement.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);

	}
	else if(strategy == D_SHORT_PUT_BUTTERFLY)
	{
		/* Short Put Butterfly */
		/* CBOE Requirements:
			* the amount of the aggregate difference between the two highest strike
				prices (aggregate difference = number of spreads x difference in
				strike prices x $100)
			* long puts must be paid for in full
			* proceeds received from sale of short option components may be applied
				to the total initial margin requirement
		*/
		double short_put_margin_requirement = 0.0;
		double long_put_margin_requirement = 0.0;
		double net_proceeds = 0.0;


		leg1_contract_price = leg1_contract_price * 100; /* sell */
		leg2_contract_price = leg2_contract_price * 100; /* buy */
		leg3_contract_price = leg3_contract_price * 100; /* sell */
		leg1_strike_price = leg1_strike_price * 100;
		leg2_strike_price = leg2_strike_price * 100;
		leg3_strike_price = leg3_strike_price * 100;

		if( (leg1_contracts != leg3_contracts) || (leg2_contracts != (leg1_contracts * 2)) )
		{
			fprintf(stderr, "Short put Butterfly must be in leg ratio 1:2:1\n");

			return -1;
		}

		if( (leg3_strike_price - leg2_strike_price) != (leg2_strike_price - leg1_strike_price) )
		{
			fprintf(stderr, "The difference between the strike prices must be the same.\n");

			return -1;
		}

		if( ( ((leg1_contract_price * leg1_contracts) + (leg3_contract_price * leg3_contracts)) -
				(leg2_contract_price * leg2_contracts)) <= 0 )
		{
			fprintf(stderr, "The transaction must result in a net credit.\n");

			return -1;
		}

		/* TODO: Expiration months must be the same */

		/* Long puts margin requirements (long puts must be paid for in full */
		long_put_margin_requirement = leg2_contract_price * leg2_contracts;
		printf("%.2f margin requirement for long puts.\n",long_put_margin_requirement);

		/* Short put margin requirements */
		short_put_margin_requirement = (leg3_strike_price - leg2_strike_price) * leg3_contracts;
		printf("%.2f margin_requiremnt for short puts.\n",short_put_margin_requirement);

		net_proceeds = (leg1_contract_price * leg1_contracts) + (leg3_contract_price * leg3_contracts);

		margin_requirement = long_put_margin_requirement + short_put_margin_requirement;
		margin_maint_requirement = margin_requirement - net_proceeds;
		printf("%.2f is initial margin requirement.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_CALL_BACK_SPREAD)
	{
		/* Call Back Spread */
		/* CBOE Requirements:
			* total of requirements for short call spread portion and stand-alone
				long call(s) portion of each back spread
		*/
		long long_call_contracts = 0;
		double long_call_margin_requirement = 0.0;
		double call_spread_margin_requirement = 0.0;
		double short_calls_margin_req = 0.0;
		double long_calls_margin_req = 0.0;

		leg1_contract_price = leg1_contract_price * 100; /* Buy Calls */
		leg2_contract_price = leg2_contract_price * 100; /* Sell Calls */

		if((leg1_contracts < leg2_contracts) || (leg1_contracts == leg2_contracts))
		{
			fprintf(stderr,"The total number of calls bought must be more than ");
			fprintf(stderr,"the total number of calls sold.\n");

			return -1;
		}
		
		if(leg1_contracts <= leg2_contracts)
		{
			fprintf(stderr,"The number of long calls purchased must be greater than number of short ");
			fprintf(stderr,"calls sold.\n");

			return -1;
		}

		/* TODO: Expiration Month Must Be The Same */

		long_call_contracts = leg1_contracts - leg2_contracts;

		/* Short Call Spread Requirements */
		call_spread_margin_requirement = 0.0;

		/* Leg1: Long Calls that must be paid for in full. */
		long_calls_margin_req = leg1_contract_price * leg2_contracts;

		/* Leg2: amount of short call aggregate strike price below long aggregate strike price */
		short_calls_margin_req = ((leg1_strike_price * 100 * leg2_contracts) - 
									(leg2_strike_price * 100 * leg2_contracts));

		call_spread_margin_requirement = (long_calls_margin_req + short_calls_margin_req) - (leg2_contract_price * leg2_contracts);
		printf("%.2f is the initial short call spread margin requirement.\n",call_spread_margin_requirement);
		
		/* Stand Alone Long Call Requirements */
		long_call_margin_requirement = long_call_contracts * leg1_contract_price;
		printf("%.2f margin requirement for long calls.\n",long_call_margin_requirement);
		
		/* Total Margin Requirements */
		margin_requirement = long_call_margin_requirement + call_spread_margin_requirement;
		margin_maint_requirement = margin_requirement;
		printf("%.2f is initial margin requirement.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
		
	}
	else if(strategy == D_PUT_BACK_SPREAD)
	{
		/* Put Back Spread */
		/* CBOE Requirements:
			* total of requirements for short put spread portion and stand-alone
				long put(s) portion of each back spread
		*/
		long naked_contracts = 0;
		double long_put_margin_req = 0.0;
		double short_put_margin_req = 0.0;
		double naked_puts_margin_req = 0.0;
		double put_spread_margin_req = 0.0;

		leg1_contract_price = leg1_contract_price * 100; /* Buy Puts */
		leg2_contract_price = leg2_contract_price * 100; /* Sell Puts */

		if((leg1_contracts < leg2_contracts) || (leg1_contracts == leg2_contracts))
		{
			fprintf(stderr,"Total number of puts bought must be more than puts sold.\n");

			return -1;
		}
		if((leg1_strike_price > leg2_strike_price) || (leg1_strike_price == leg2_strike_price))
		{
			fprintf(stderr,"Strike prike of puts bought must have a strike price less than puts sold.\n");

			return -1;
		}

		naked_contracts = leg1_contracts - leg2_contracts;
		printf("Naked Contracts: %ld\n",naked_contracts);

		/* Log Put Claculations */
		naked_puts_margin_req = leg1_contract_price * naked_contracts;
		printf("%.2f margin is required for long puts.\n", naked_puts_margin_req);

		/* Short Put Spread Calculations */
		/* SHORT PUT SPREAD (18) */

		/* Leg 1: Long Puts must be paid for in full */
		long_put_margin_req = leg1_contract_price * leg2_contracts;

		/* Leg2: amount of long put aggregate strike price below short aggregate strike price */
		short_put_margin_req = ((leg2_strike_price * 100 * leg2_contracts) - 
									(leg1_strike_price * 100 * leg2_contracts));

		put_spread_margin_req = (long_put_margin_req + short_put_margin_req) - (leg2_contracts * leg2_contract_price);
		printf("%.2f is the initial margin requirement for put spread.\n",put_spread_margin_req);

		margin_requirement = naked_puts_margin_req + put_spread_margin_req;
		margin_maint_requirement = margin_requirement;
		printf("\n\n");
		printf("%.2f margin is required for naked puts.\n", margin_requirement);
		printf("%.2f is total margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_RATIO_CALL_SPREAD)
	{
		/* Ratio Call Spread */
		/* CBOE Requirements:
			* total of requirements for long call spread portion and stand-alone
				uncovered short call(s) portion of each ratio spread
			* after position is established, ongoing maintenance margin requirement
				applies to uncovered short call(s) portion, and an increase (or
				decrease) in the margin required is possible
		*/
		long naked_contracts = 0;
		double short_call_margin_req = 0.0;
		double call_spread_margin_req = 0.0;
		
		leg1_contract_price = leg1_contract_price * 100; /* Buy */
		leg2_contract_price = leg2_contract_price * 100; /* Sell */
		leg1_strike_price = leg1_strike_price * 100;
		leg2_strike_price = leg2_strike_price * 100;
		stock_price = stock_price * 100;
		
		if(leg1_strike_price >= leg2_strike_price)
		{
			fprintf(stderr, "The strike price of calls purchased must be less than the ");
			fprintf(stderr, "strike price of calls purchased.\n");
		
			return -1;
		}
		
		if(leg1_contracts >= leg2_contracts)
		{
			fprintf(stderr, "The number of contracts purchased must be less than the number ");
			fprintf(stderr, "the number of contracts sold.\n");
			
			return -1;
		}
		
		/* TODO: Contracts must expire on the same month */

		naked_contracts = leg2_contracts - leg1_contracts;
		printf("Naked Contracts: %ld\n",naked_contracts);
		
		/* Naked Short Call Margin Requirements */
		out_of_the_money = leg2_strike_price - stock_price;
		if(out_of_the_money < 0)
		{
			out_of_the_money = 0;
		}

		short_call_margin_req = ((leg2_contract_price + ((stock_price * .20) - out_of_the_money))
								* naked_contracts ) - (leg2_contract_price * leg1_contracts);

		printf("\n\n");
		printf("%.2f margin is required for naked calls.\n", short_call_margin_req);

		/* Call Spread Margin Requirements */
		call_spread_margin_req = (leg1_contract_price * leg1_contracts) - (leg2_contract_price * leg1_contracts);
		printf("%.2f is initial margin requirement for long call spread.\n", call_spread_margin_req);

		/* Total Ratio Call Spread Margin Requirements */
		margin_requirement = short_call_margin_req + call_spread_margin_req;
		margin_maint_requirement = margin_requirement;
		printf("\n\n");
		printf("%.2f margin is required for naked puts.\n", margin_requirement);
		printf("%.2f is total margin maintenance requirement.\n", margin_maint_requirement);
	}
	else if(strategy == D_RATIO_PUT_SPREAD) /* OK */
	{
		/* Ratio Put Spread */
		/* CBOE Requirements:
			* total of requirements for long put spread portion and stand-alone
				uncovered short put(s) portion of each ratio spread
			* after position is established, ongoing maintenance margin requirement
				applies to uncovered short put(s) portion, and an increase (or
				decrease) in the margin required is possible
		*/
		long naked_puts = 0;
		double margin_requirement_2 = 0.0;
		double margin_maint_requirement_2 = 0.0;

		leg1_contract_price = leg1_contract_price * 100; /* Puts Bought */
		leg2_contract_price = leg2_contract_price * 100; /* Puts Sold */

		if((leg1_contracts > leg2_contracts) || (leg1_contracts == leg2_contracts))
		{
			fprintf(stderr, "Number of puts sold must be greater than number of ");
			fprintf(stderr, "nubmer of puts bought.\n");

			return -1;
		}

		if(leg1_strike_price < leg2_strike_price)
		{
			fprintf(stderr, "The strike price of puts bought must be greater than ");
			fprintf(stderr, "the strike price of puts sold.\n");

			return -1;	
		}
		
		if(leg1_contract_price < leg2_contract_price)
		{
			fprintf(stderr, "The contract price of puts bought must be greater than ");
			fprintf(stderr, "the contract price of puts sold.\n");

			return -1;
		}

		/* Calculate Put Spread Margin Requirement */
		/*   LONG PUT SPREAD (17) */
		margin_requirement = (leg1_contract_price * contracts) - (leg2_contract_price * contracts);
		printf("%.2f is initial margin requirement for put spread.\n", margin_requirement);

		/* Calculate Margin Requirement on Naked Puts */
		/* short put - (6) */
		naked_puts = leg2_contracts - leg1_contracts;

		stock_price = stock_price * 100;
		leg2_strike_price = leg2_strike_price * 100;

		out_of_the_money = stock_price - leg2_strike_price;
		if(out_of_the_money < 0)
		{
			out_of_the_money = 0;
		}

		margin_requirement_2 = ((stock_price * .20) - out_of_the_money) * naked_puts;
		margin_maint_requirement_2 = margin_requirement_2 + margin_requirement;

		printf("%.2f margin is required for naked puts.\n", margin_requirement_2);
		printf("%.2f is total margin maintenance requirement.\n", margin_maint_requirement_2);

	}
	else if(strategy == D_COLLAR) /* OK */
	{
		/* Collar */
		/* CBOE Requirements:
			* no margin required on short call(s)
			* long put(s) must be paid for in full
			* 50% requirement on long stock purchase (in a margin account)
			* proceeds received from sale of call(s) may be applied to the total
				initial margin requirement
			* after position is established, ongoing maintenance margin requirement
				applies, and an increase (or decrease) in the margin required is
				possible
		*/
		leg1_contract_price = leg1_contract_price * 100; /* Long Put */
		leg2_contract_price = leg2_contract_price * 100;

		margin_requirement = ((leg1_contract_price * leg1_contracts) + ((stock_price * shares) * .50));
		margin_maint_requirement = margin_requirement - (leg2_contract_price * leg2_contracts);
		printf("%.2f is initial margin requirement.\n", margin_requirement);
		printf("%.2f is margin maintenance requirement.\n", margin_maint_requirement);
	}
	
	return 0;
}