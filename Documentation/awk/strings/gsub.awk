#
# Replace all occurrences of "USA" by "United States"; In such cases,
# when $0 changes, the fields and NF change too.
#
{ print "LINE:"NR":"; print NF; gsub(/USA/, "United States"); print NF; }
