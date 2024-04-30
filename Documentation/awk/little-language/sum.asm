        #
        # print sum of input numbers (terminated by zero)
        #
        ld zero # initialize sum to zero
        st sum

loop    get       # read a number
        jz  done  # no more input if number is zero
        add sum   # add in accumulated sum
        st  sum   # store new vaule back in sum
        j   loop

done    ld sum # print sum
        put
        halt

zero	const	0
sum	const
