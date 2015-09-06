%[*][ 字段宽度 ][ 长度修饰符 ] 修饰符

===

scanf()转换修饰符的修饰符

修饰符          配套使用的转换修饰符   对应的自变量类型

hh              d、i、o、u、x、X、n    signed char * 或 unsigned char *

h               d、i、o、u、x、X、n    short int * 或 unsigned short int *

l（字母L）      d、i、o、u、x、X、n    long int * 或 unsigned long int *

l（字母L）      c、s、[...]            wint_t *; 利用mbrtowc()进行转换

l（字母L）      a、A、e、E、f、F、g、G double *

ll（两个字母L） d、i、o、u、x、X       long long * 或 unsigned long long *

j               d、i、o、u、x、X、n    intmax_t * 或 uintmax_t *

z               d、i、o、u、x、X、n    size_t * 或 "指向对应的有符号整数类型的指针"

t               d、i、o、u、x、X、n    ptrdiff_t * 或者"指向对应有符号整数"的指针

L               a、A、e、E、f、F、g、G long double *

====

scanf()转换修饰符

转换修饰符        自变量类型            输入符号

d                 signed int *          十进制，带有可选的正负号

i                 signed int *          十进制、八进制或十六进制，带有可选的正负号

u                 unsigned int *        十进制，带有可选的正负号

o                 unsigned int *        八进制，带有可选的正负号

x                 unsigned int *        十六进制，带有可选的正负号，以及前置0x（或0X）

a, e, f, or g     float * 或 double *   浮点数

c                 char * 或 int *       一个字符，如果指定字段宽度大于1，则有多个字符

s                 char *                连续的非空格符

[ 扫描集合 ]      char *                连续的"扫描集合"字符

n                 int *                 不读取输入，反而将"目前为止所读入内容"存储到"此自变量所指向的变量"中

p                 void *                系统对于指针值的表示法，和printf()的转换方式相反

%                 None                  单精度符号(%)，没有存储任何值

