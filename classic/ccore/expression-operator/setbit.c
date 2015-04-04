// name:
//       setBit: set m's position bit to 1
// 
// return:
//         mask
unsigned int setBit(unsigned int mask, unsigned int p)
{
    if (p >= CHART_BIT * sizeof(int))
        return mask;
    else
        return mask | (1 << p);
}
