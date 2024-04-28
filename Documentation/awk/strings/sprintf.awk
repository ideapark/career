#
# Pretty print each input line with first field as 10-character
# stirng, and second field as at least 6-character long decimal
# number.
#
{ x = sprintf("%10s %6d", $1, $2); print x; }
