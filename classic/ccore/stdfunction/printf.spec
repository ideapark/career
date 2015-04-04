%[ 标记 ][ 字段宽度 ][. 精确度 ][ 长度修饰符 ] 修饰符

标记（flags）:
 
 +   在正数前面放一个加号
 
 ' ' 在正数前面放一个加号（不可以搭配 + 使用）
 
 -   将输出对齐到字段左边
 
 0   将输出前面补上0，一直到数值输出的左边为止（不可以搭配使用-）
     对整数来说，如果指定精确度，则忽略之
 
 #   使用另类的转换规则，如下所示

     A、a、E、e、F、f、G、g
        用小数点为浮点数做标识，尽管小数点后面没有数字也一样

     G、g
        不要把后面的0截断
     
     X、x、o
        前置0X或0x，以格式化非0的十六进制整数；前置0，以格式化八进制整数

===

printf()转换修饰符的修饰符

修饰符          转换修饰符             对应的自变量类型

hh              d、i、o、u、x、X       signed char或unsigned char

hh              n                      singed char *

h               d、i、o、u、x、X       short int 或 unsigned short int

h               n                      short int *

l（字母L）      d、i、o、u、x、X       long int 或 unsigned long int

l（字母L）      c                      wint_t

l（字母L）      n                      long int *

l（字母L）      s                      wchar_t *

l（字母L）      a、A、e、E、f、F、g、G （允许使用修饰符，但没有作用）

ll（两个字母L） d、i、o、u、x、X       long long 或 unsigned long long 

ll（两个字母L） n                      long long *

j               d、i、o、u、x、X       intmax_t 或 uintmax_t

j               n                      intmax_t *

z               d、i、o、u、x、X       size_t 或对应的有符号整数类型

z               n                      size_t * 或者 "指向有符号整数类型"的指针

t               d、i、o、u、x、X       ptrdiff_t 或者对应的无符号整数类型

t               n                      ptrdiff_t * 或者"指向对应有符号整数"的指针

L               a、A、e、E、f、F、g、G long double

===

printf()转换修饰符

转换修饰符        自变量类型                输出符号

d、i              int                       十进制

u                 unsigned int              十进制

o                 unsigned int              八进制

x、X              unsigned int              十六进制

f、F              float 或 double           十进制浮点数

e、E              float 或 double           指数计数法

g、G              float 或 double           十进制浮点数或浮点数符号

a、A              float 或 double           十六进制指数计数法

c                 char 或 int               单一字符

s                 char *                    指针自变量所指向的字符串内容

n                 int *                     没有输出，printf()会将"目前为
                                            止的输出字符"存储到"此自变量所
                                            指向"的变量中

p                 任何指针类型              指针值(用十六进制计数法表示)

%                 没有                      百分比符号(%)

===

定义在stdint.h中的转换修饰符宏

类型                意义                      printf()转换修饰符

intN_t              宽度为N位的整数类型       PRIdN、PRIiN

uintN_t                                       PRIoN、PRIuN、PRIxN、PRIXN

int_leastN_t        宽度至少为N位的整数类型   PRIdLEASTN、PRIiLEASTN

uint_leastN_t                                 PRIoLEASTN、PRIuLEASTN、
                                              PRIxLEASTN、PRIXLEASTN

int_fastN_t         宽度至少N位               PRIdFASTN、PRIiFASTN

uint_fastN_t        处理速度最快的整数类型    PRIoFASTN、PRIuFASTN、
                                              PRIxFASTN、PRIXFASTN

intmax_t            最宽的整数类型            PRIdMAX、PRIiMAX

uintmax_t                                     PRIoMAX、PRIuMAX、PRIxMAX、PRIXMAX

intptr_t            足以存储指针值的整数类型  PRIdPTR、PRIiPTR

uintptr_t                                     PRIoPTR、PRIuPTR、PRIxPTR、PRIXPTR
