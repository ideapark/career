#
# Accumulates the population of Asia and Europe in the array pop. The
# END action prints the total populations of these two continents.
#
/Asia/   { pop["Asia"] += $3 }
/Europe/ { pop["Europe"] += $3 }
END {
    print "Asian population is", pop["Asia"], "million."
    print "European population is", pop["Europe"], "million."
}
