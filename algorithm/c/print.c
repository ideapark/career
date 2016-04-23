extern int PrintDigit(int i);

/* Print nonnegative N */
void PrintOut(unsigned int N)
{
    if (N >= 10)
        PrintOut(N / 10);
    PrintDigit(N % 10);
}
