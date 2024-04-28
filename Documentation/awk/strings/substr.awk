#
# Abbreviate the country names to their first 3 characters. Setting $1
# forces awk to recompute $0 and thus the fields are now separated by
# a blank (the default vaule of OFS), no longer by a tab.
#
{ $1 = substr($1, 1, 3); print }
