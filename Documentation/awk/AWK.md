# Builtin Variables

```text
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
```

# Expressions

```text
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
```

# Builtin Arithmetic Functions

```text
==========================================================================================
   FUNCTION        |                        VAULE RETURNED
-------------------+----------------------------------------------------------------------
    atan2(y,x)     | arctangent of y/x in the range -π to π
    cos(x)         | consine of x, with x in radians
    exp(x)         | exponential function of x, e^x
    int(x)         | integer part of x; truncated towards 0 when x > 0
    log(x)         | natural (base e) logrithm of x
    rand()         | random number r, where 0 <= r < 1
    sin(x)         | sine of x, with x in radians
    sqrt(x)        | square root of x
    srand(x)       | x is new seed for rand()
-------------------+----------------------------------------------------------------------
```

# Builtin String Functions

```text
=====================================================================================================================================
        FUNCTION           |                        DESCRIPTION
---------------------------+---------------------------------------------------------------------------------------------------------
    gsub(r,s)              | substitute s for r globally in $0, return number of substitutions made
    gsub(r,s,t)            | substitute s for r globally in string t, return number of substitute made
    index(s,t)             | return first position of string t in s, or 0 if t is not present
    length(s)              | return number of characters in s
    match(s,r)             | test whether s contains a substring matched by r, return index or 0; sets RSTART and RLENGTH
    split(s,a)             | split s into array a on FS, return number of fields
    split(s,a,fs)          | split s into array a on field separator fs, return number of fields
    sprintf(fmt,expr-list) | return expr-list formatted according to format string fmt
    sub(r,s)               | substitute s for the leftmost longest substring of $0 matched by r; return number of substitutions made
    sub(r,s,t)             | substitute s for the leftmost longest substring of t matched by r; return number of substitutions made
    substr(s,p)            | return suffix of s starting at position p
    substr(s,p,n)          | return substring of s of length n starting at position p
---------------------------+---------------------------------------------------------------------------------------------------------
```

# Expression Operators

```text
==================================================================================================================
       OPERATION      |      OPERATORS      |    EXAMPLE     |     MEANING OF EXAMPLE
----------------------+---------------------+----------------+----------------------------------------------------
 assignment           | = += -= *= /= %= ^= |    x *= 2      | x = x * 2
 conditional          | ?:                  |    x ? y : z   | if x is true then y else z
 logical OR           | ||                  |    x || y      | 1 if x or y are true, 0 otherwise
 logical AND          | &&                  |    x && y      | 1 if x and y are true, 0 otherwise
 array membership     | in                  |    i in a      | 1 if a[i] exists, 0 otherwise
 matching             | ~ !~                |    $1 ~ /x/    | 1 if the first field contains an x, 0 otherwise
 relatioinal          | < <= == != >= >     |    x == y      | 1 if x is equal to y, 0 otherwise
 concatenation        |                     |    "a" "bc"    | "abc"; there is no explicit concatenation operator
 add,substract        | + -                 |    x + y       | sum of x and y
 multiply,divide,mod  | * / %               |    x % y       | remainder of x divided by y
 unary plus and minus | + -                 |    -x          | negated vault of x
 logical NOT          | !                   |    !$1         | 1 if $1 is zero or null, 0 otherwise
 exponentiation       | ^                   |    x ^ y       | multiply x for y times
 increment,decrement  | ++ --               |    ++x, x++    | add 1 to x
 field                | $                   |    $i+1        | vaule of i-th field, plus 1
 grouping             | ()                  |    ($i)++      | add 1 to value of i-th field
----------------------+---------------------+----------------+----------------------------------------------------
```

# Control-Flow Statements

```text
========================================================================
{ stmts }
    statement grouping

if (expr) smt
    if expr is true, execute smt

if (expr) stmt1 else stmt2
    if expr is true, execute stmt1, otherwise execute stmt2

while (expr) stmt
    if expr is true, execute stmt, then repeat

for (expr1; expr2; expr3) stmt
    equivalent to expr1; while (expr2) { stmt; expr3; }

for (var in array) stmt
    execute stmt with var set to each subscript in array in turn

do stmt while (expr)
    execute stmt; if expr is true; repeat

break
    immediately leave innermost enclosing while, for or do

continue
    start next iteration of innermost enclosing while, for or do

next
    start next iteration of main input loop

exit
exit expr
    go immediately to the END action; if within the END action, exit
    program entirely. return expr as program status.
------------------------------------------------------------------------
```

# Output Statements

```text
========================================================================
print
    print $0 on standard output

print expr, expr, ...
    print expr's, separated by OFS, terminated ORS

print expr, expr, ... >filename
    print on file filename instead of standard output

print expr, expr, ... >>filename
    append to file filename instead of overwriting previous contents

print expr, expr, ... | command
    print to standard input of command

printf(format, expr, expr, ...)
printf(format, expr, expr, ...) >filename
printf(format, expr, expr, ...) >>filename
printf(format, expr, expr, ...) | command
    printf statements are like print but the first argument specifies
    output format

close(filename), close(command)
    break connection between print and filename or command

system(command)
    execute command; value is status return of command
```

# Printf Format-Control Characters

```text
==========================================================================================
  CHARACTER  |   PRINT EXPRESSION AS
-------------+----------------------------------------------------------------------------
      c      | ASCII character
      d      | decimal integer
      e      | [-]d.ddddddE[+-]dd
      f      | [-]ddd.dddddd
      g      | e or f conversion, whichever is shorter, with nonsignificant zeros suppressed
      o      | unsigned octal number
      s      | string
      x      | unsigned hexadecimal number
      %      | print a %; no argument is consumed
-------------+----------------------------------------------------------------------------
```

# Examples of Printf Specifications

```text
==========================================================================================
         fmt            |           $1          |     printf(fmt, $1)
------------------------+-----------------------+-----------------------------------------
       %c               | 97                    | a
       %d               | 97.5                  | 97
       %5d              | 97.5                  |    97
       %e               | 97.5                  | 9.750000e+01
       %f               | 97.5                  | 97.500000
       %7.2f            | 97.5                  |    97.50
       %g               | 97.5                  | 97.5
       %.6g             | 97.5                  | 97.5
       %o               | 97                    | 141
       %06o             | 97                    | 000141
       %x               | 97                    | 61
       [%s]             | January               | [January]
       [%10s]           | January               | [    January]
       [%-10s]          | January               | [January    ]
       [%.3s]           | January               | [Jan]
       [%10.3s]         | January               | [        Jan]
       [%-10.3s]        | January               | [Jan        ]
       %%               | January               | %
------------------------+-----------------------+-----------------------------------------
```
