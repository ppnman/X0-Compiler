#include "../global.h"

/*
 * repeat_stat syntactical analyzer
 */
void repeat_stat ()
{
	int startBreakNum = iterBreakList; /* save the number of break statement to be backfilled before analysing repeat_stat */
	int startContinueNum = iterCtnList; /* save the number of continue statement to be backfilled before analysing repeat_stat */

	if (sym == reptsym)
	{
		readSymbol ();

		if (sym == lbrace)
		{
			readSymbol ();
			int pos = iterCode; /* save the position of statement_list's first code */
			statement_list ();

			/* backfill continue statement */
			for (int i = startContinueNum; i < iterCtnList; i++)
			{
				int pos = continueList[i];
				code[pos].operand1 = iterCode;
			}
			iterCtnList = startContinueNum; /* set the value of iterCtnList to the value
											 * that is before analysing repeat_stat */

			if (sym == rbrace)
			{
				readSymbol ();

				if (sym == untlsym)
				{
					readSymbol ();

					if (sym == lparen)
					{
						readSymbol ();
						expression ();
						gen (jpc, pos, 0, 0);

						if (sym == rparen)
						{
							readSymbol ();

							if (sym == semic)
							{
								readSymbol ();
							}
							else /* the lack of ';' */
							{
								error (10);
							}
						}
						else /* the lack of ')' */
						{
							error (14);
						}
					}
					else /* the lack of '(' */
					{
						error (16);
					}
				}
				else /* the lack of 'while' */
				{
					error (21);
				}
			}
			else /* the lack of '}' */
			{
				error (4);
			}
		}
		else /* the lack of '{' */
		{
			error (5);
		}
	}
	else /* the lack of 'do' */
	{
		error (39);
	}

	/* backfill break statement */
	for (int i = startBreakNum; i < iterBreakList; i++)
	{
		int pos = breakList[i];
		code[pos].operand1 = iterCode;
	}
	iterBreakList = startBreakNum; /* set the value of iterBreakList to the value
								    * that is before analysing repeat_stat */
}