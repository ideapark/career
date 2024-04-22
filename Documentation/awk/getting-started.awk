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

#
# Formatted printing
#
{ printf("%-8s: $%-.2f\n", $1, $2 * $3) }

#
# Two special patterns
#
#  BEGIN : matches before the first line of the first input file
#  END   : matches after the last line of the last file
#
BEGIN {
    print "Name    RATE      HOURS";
    print "------------------------"
}
{ print }
END {
    print "------------------------"
}

#
# Counting, Sum, Averages
#

# awk variable initialized with vaule 0.
$3 > 15 { emp = emp + 1 }
END { print emp, "employees worked more than 15 hours." }

# average
{ pay = pay + $2 * $3 }
END {
    print NR, "employees"
    print "total pay is", pay
    print "average pay is", pay/NR
}

#
# Finds the employee who is paid the most per hour.
#
$2 > maxrate { maxrate = $2; maxemp = $1 }
END {
    print "highest hourly rate:", maxrate, "for", maxemp
}

#
# String concatenation
#
{ names = names $1 " " }
END {
    print names
}

#
# Print the last input line.
#
{ last = $0 }
END {
    print last
}

#
# AWK built-in functions
#
{ print $1, length($1) }

#
# Control-Flow Statements
#
$2 > 6 { n = n + 1; pay = pay + $2 * $3 }
END {
    if (n > 0)
	print n, "employees, totoal pay is", pay, "average pay is", pay/n
    else
	print "no employees are paid more than $6/hour"
}

#
# Reverse input lines
#
{ line[NR] = $0 }
END {
    i = NR
    while (i > 0) {
	print line[i]
	i = i -1
    }
}
END {
    for (i = NR; i > 0; i--) {
	print line[i]
    }
}
