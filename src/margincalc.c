/* margincalc.h - Margin Estimation Calculator main source file
 * Copyright (C) 2011 CryptNET, V. Alex Brennen (VAB)
 */

#include "margincalc.h"


int main(int argc,char *argv[])
{
	const char version[] = "1.0.0";
	int strategy = 0;
	int index = 0;
	int rslt = 0;
	int arg = 0;

	/* Options:
	 *		'-i' => Index Margin Requirements
	 *		'-h' => Help
	 *		'-v' => Version
	 */
	if(argc > 1)
	{
		for(arg=1;arg<argc;arg++)
		{
			if(argv[arg][0] == '-')
			{
				if(argv[arg][1] == '-')
				{
					if(strstr(argv[arg],"help") != NULL)
					{
						print_help();

						return 0;
					}
					else if(strstr(argv[arg],"version") != NULL)
					{
						printf("CryptNET Margin Calculator Version %s\n", version);

						return 0;
					}
				}
				else if(argv[arg][1] == 'h')
				{
					print_help();

					return 0;
				}
				else if(argv[arg][1] == 'i')
				{
					index = 1;

					fprintf(stderr, "Index option calculations not yet implemented.\n");

					return -1;
				}
				else if(argv[arg][1] == 'v')
				{
					printf("CryptNET Margin Calculator Version %s\n", version);

					return 0;
				}
				else if(isdigit(argv[arg][0]))
				{
					continue;
				}
				else
				{
					invalid_argument();

					return 0;
				}
			}
		}
	}

	strategy = display_strategies_menu();

	rslt = collect_trade_data(strategy);


	return 0;
}


double calc_short_call_margin_requirement(void)
{

	return 0.0;
}


double calc_short_put_margin_requirement(void)
{

	return 0.0;
}


int collect_trade_data(int strategy)
{
	calc_margin_est(strategy);
	
	return 0;
}


int display_strategies(void)
{
	printf("Select a Strategy\n");
	printf("-----------------\n");
	printf("1. Long Call - 9 Months or Less             20. Short Call Time Spread\n");
	printf("2. Long Call - More Than 9 Months           21. Long Put Time Spread\n");
	printf("3. Short Call                               22. Short Put Time Spread\n");
	printf("4. Long Put - 9 Months or Less              23. Long Call Butterfly\n");
	printf("5. Long Put - More Than 9 Months            24. Short Call Butterfly\n");
	printf("6. Short Put                                25. Long Put Butterfly\n");
	printf("7. Covered Call                             26. Short Put Butterfly\n");
	printf("8. Long Call & Short Underlying Stock       27. Call Back Spread\n");
	printf("9. Long Put & Long Underlying Stock         28. Put Back Spread\n");
	printf("10. Short Put & Short underlying stock      29. Ratio Call Spread\n");
	printf("11. Long Straddle                           30. Ratio Put Spread\n");
	printf("12. Short Straddle                          31. Collar\n");
	printf("13. Long Strangle\n");
	printf("14. Short Strangle\n");
	printf("15. Long Call Spread\n");
	printf("16. Short Call Spread\n");
	printf("17. Long Put Spread\n");
	printf("18. Short Put Spread\n");
	printf("19. Long Call Time Spread\n");


	return 0;
}


int display_strategies_menu(void)
{
	int strategy = 0;
	int rslt = 0;

	rslt = display_strategies();
	if(rslt != 0)
	{
		fprintf(stderr,"Error displaying Strategies.\n");
		fprintf(stderr,"Exiting...\n\n");

		return -1;
	}
	printf("\n");
	printf("Strategy:  ");


	return strategy;
}


int invalid_argument(void)
{
	fprintf(stderr,"margincalc: Invalid arument given.\n\n");
	
	print_help();

	return 0;
}


int print_help(void)
{
	printf("Usage: margincalc\n");
	printf("\t-h\t\tThis Help Text\n");
	printf("\t-i\t\tCalculate Margin Requirements for Index Options\n");
	printf("\t-v\t\tDisplay Version Information\n");
	printf("\t--help\t\tThis Help Text\n");
	printf("\t--version\tDisplay Version Information\n");
	printf("\n");

	return 0;
}

