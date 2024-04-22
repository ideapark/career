#
# The Structure of an AWK Program
#
#   pattern { action }
#   pattern { action }
#   ... ...
#

#
# These are actions with no pattern, since patterns and actions are
# both optional, actions are enclosed in braces to distinguish them
# from patterns.
#
{ print }      # print by itself prints the current input line
{ print $0 }   # does the same as above, since $0 is the whole line
{ print $1 }   # print the first column/field

#
# print the name and pay (rate times hours) for everyone who worked
# more than zero hours.
#
$3 > 0 { print $1, $2 * $3 }

#
# print the names of those employees who did not work.
#
$3 == 0 { print $1 }

#
# AWK Built-in Variable
#
# NF: counts the number of fields
# NR: counts the number of lines
#
{ print NF, $NF }
{ print NR, $0  }
