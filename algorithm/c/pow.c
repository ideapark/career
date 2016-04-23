long int Pow(long int X, unsigned int N)
{
    if (N == 0)   /* Base case */
        return 1;
    if (N == 1)   /* Base case */
        return X;
    if (IsEven(N))
        return Pow(X * X, N / 2);
    else
        return Pow(X * X, N / 2) * X;
}
