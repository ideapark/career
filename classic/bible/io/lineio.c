char *fgets(char *s, int n, FILE *iop)
{
    register int c;
    register char *cs;

    cs = s;
    while (--n > 0 && (c = getc(iop)) != EOF)
        if ((*cs++ = c) == '\n')
            break;
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}

int fputs(char *s, FILE *iop)
{
    int c, cnt;

    cnt = 0;
    while (c = *s++) {
        putc(c, iop);
        cnt++;
    }
    return ferror(iop) ? EOF : cnt;
}

int getline(char *line, int max)
{
    if (fgets(line, max, stdin) == NULL)
        return 0;
    else
        return strlen(line);
}
