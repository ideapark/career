/*
 * name:
 *         average: calc average of float array
 * param: 
 *         float array, array length
 * return: 
 *         double, average value
 */
double average(const float *array, int length)
{
    double sum = 0.0;
    const float *end = array + length; // next to last element

    if (length <= 0)
        return 0.0;
    for (const float *p = array; p < end; ++p)
        sum += *p;
    return sum/length;
}
