# Builtin Variables

==========================================================================================
   VARIABLE     |                     MEANING                     |         DEFAULT
----------------+-------------------------------------------------+-----------------------
	 ARGC       | number of command-line arguments                |       -
	 ARGV       | array of command-line arguments                 |       -
	 FILENAME   | name of current input file                      |       -
	 FNR        | record number in current file                   |       -
	 FS         | controls the input field separator              |       SPC
	 NF         | number of fields in current record              |       -
	 NR         | number of records read so far                   |       -
	 OFMT       | output format for numbers                       |       "%.6g"
	 OFS        | output field separator                          |       SPC
	 ORS        | output record separator                         |       RET
	 RLENGTH    | length of string matched by match function      |       -
	 RS         | controls the input record separator             |       RET
	 RSTART     | start of string matched by match function       |       -
	 SUBSEP     | subscript separator                             |       "\034"
----------------+-------------------------------------------------+-----------------------

  SPC: " "
  RET: "\n"

# Expressions

==========================================================================================
1. The primary expressions are:
	numeric and string constants, variables, fields, function calls, array elements.

2. These operators combine expressions:
	assignment operators = += -= *= /= %= ^=
	conditional expression operator ?:
	logical operators || (OR), && (AND), ! (NOT)
	matching operators ~ and !~
	relational operators < <= == != > >=
	concatenation (no explicit operator)
	arithmetic operators + - * / % ^
	unary + and -
	increment and decrement operators ++ and -- (prefix and postfix)
	parentheses for grouping
------------------------------------------------------------------------------------------
