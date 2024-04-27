#
# Regular expression built up from strings concatenation.
#
BEGIN {
    sign     = "[+-]?"
    decimal  = "[0-9]+[.]?[0-9]*"
    fraction = "[.][0-9]+"
    exponent = "([eE]" sign "[0-9]+)?"
    number   = "^" sign "(" decimal "|" fraction ")" exponent "$"
}

# print line if the second field looks like a number
$2 ~ number
