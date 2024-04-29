#
# histogram
#     input: numbers between 0 and 100
#     output: histogram of deciles
#

#
# generate random integers
#
BEGIN {
    for (i = 1; i <= 200; i++)
        print(int(101*rand()))
}
