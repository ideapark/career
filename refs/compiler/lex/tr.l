%{
/*
 * Selects only lines that end of
 * begin with the letter 'a'.
 * Deletes everything else.
 */
#include <stdio.h>
%}
ends_with_a .*a\n
begins_with_a a.*\n
%%
{ends_with_a} ECHO;
{begins_with_a} ECHO;
.*\n ;
%%
int main()
{
	yylex();
	return 0;
}
