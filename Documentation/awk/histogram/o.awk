#
# histogram
#     input: numbers between 0 and 100
#     output: histogram of deciles
#

{ x[int($1/10)]++ }

END {
    for (i = 0; i < 10; i++)
        printf(" %2d - %2d: %3d %s\n", 10*i, 10*i+9, x[i], rep(x[i], "."))
    printf("     100: %3d %s\n", x[10], rep(x[10], "."))
}

#
# return string of n s's
#
function rep(n, s, t) {
    while (n-- > 0)
        t = t s
    return t
}
