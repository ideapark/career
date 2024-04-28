#
# number "": concatenate a null string to number to coerce it to a
#            string
#
# string + 0: add zero to string to coerce it to a number
#
BEGIN {
    print "1E2"+0, "12E"+0, "E12"+0, "1X2Y3"+0

    print 1E2 "", 12E-2 "", E12 "", 1.23456789 ""
}

