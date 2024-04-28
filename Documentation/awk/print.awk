#
# OFS: output field separator, default to single blank
# ORS: output record separator, default to single newline
#
BEGIN {
        OFSOLD = OFS;
        ORSOLD = ORS;
}

{ OFS = ":";    ORS = "\n\n"; print $1, $2; }
{ OFS = OFSOLD; ORS = ORSOLD; print $1, $2; }
