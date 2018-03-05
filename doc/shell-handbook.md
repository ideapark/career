# SHELL

## File type

    d:    directory        l:    symbolic link
    s:    socket file      b:    block file
    c:    character file   p:    named pipe
    -:    regular file

## Regular expression (RE)

    ^    match start of line
    $    match end of line
    *    match zero or more characters
    []   match one of characters
    \    escape character
    .    match any single character
    {n}      match exactly n times
    {n,}     match at least n times
    {n,m}    match n-m times

## Characters RE

    [:alnum:]    alphabetical character and digits [a-zA-Z0-9]
    [:alpha:]    alphabetical character [a-zA-Z]
    [:digit:]    digits [0-9]
    [:blank:]    whitespace or tab
    [:cntrl:]    any control character
    [:graph:]    any visible character
    [:lower:]    lowercase character [a-z]
    [:upper:]    uppercase character [A-Z]
    [:print:]    non-control character
    [:punct:]    punctuation character
    [:space:]    whitespace
    [:xdigit:]   hexidecimal digits [0-9a-fA-F]

## Shell quote

    ""    double quote, expand shell variable
    ''    single quote, no expand
    ``    backquote, set output to variable
    \     backslash, escape shell special character like &, *, +, ^, $, `, ", |, ?

## Condition test

    file test:
        -d    test is directory
        -f    test is regular
        -L    test is symbolic link
        -r    test is readable
        -w    test is writable
        -x    test is executable
        -s    test is not empty

    string test:
        test "string"
        test "string1" op "string2"
        [ op "string" ]
        [ "string1" op "string2" ]
        op: = equal to, != not equal to, -z empty, -n non-empty

    number test:
        "number1" op "number2"
        [ "number1" op "number2" ]
        op: -eq, -ne, -gt, -lt, -ge, -le, -a and

## Command execute priority

    &&      the after executes only the before succeed
    ||      the after executes only the before failed
    (),{}   command group execute in the same shell

## Shell debug

    set -n    read command, not execute
    set -v    echo the read line
    set -x    echo command and args

## Here document

    echo <<EOF
    Hello, nice to meet you,
    How do you do!
    Fine, Thank you.
    EOF

## Shell builtin variable

    $#    shell script args number
    $*    script args string list
    $$    running shell pid
    $!    the last process pid running background
    $@    shell args list
    $-    options used
    $?    exit status

## awk

    awk -F":" '{print "username: "$1"\t\tuid: "$3}' /etc/passwd

    script:

        BEGIN {x=0}
        /^$/ {x=x+1}
        END {print "I found " x " blank lines."}

## sed

    sed -e 'd' /etc/services                   # delete all line
    sed -e '1,10d' /etc/service                # delete 1-10 line (both included)
    sed -e '/^#/d' /etc/service                # delete all comment line
    sed -n -e '/^#/p' /etc/service             # print all comment line
    sed -n -e '/BEGIN/,/END/p' /etc/service    # print lines between BEGIN and END
    sed -e 's/tcp/TCP/' /etc/service           # replace each line *first* tcp -> TCP
    sed -e 's/tcp/TCP/g' /etc/service          # replace each line all tcp -> TCP
    sed -e '1,10s/tcp/TCP/g' /etc/service      # replace 1-10 line all tcp -> TCP
    sed -e 's/<[^>]*>//g' some.html            # remove html tags (NOTE: /<[^>]*>/ matches shortest)

## shortcuts

    [CTRL-A] Moves the cursor to the start of the line.
    [CTRL-E] Moves the cursor to the end of the line.
    [CTRL-R] Searches in reverse through the history.
    [CTRL-K] Deletes everything from the cursor to the end of the line.
    [CTRL-U] Deletes everything from the cursor to the start of the line.
    [CTRL-S] Pauses output from a program that is writing to the screen.
    [CTRL-Q] Restarts output after a pause by [CTRL-S]
    [CTRL-D] Used to signal end-of-input for some programs (like cat and mail)
             and return you to shell prompt. If you type [CTRL-D] at a shell
             prompt, it may also log you out of the UNIX system.
