%[ 修饰符 ] 修饰符

===

strftime()转换修饰符

转换修饰符        结构成员         输出符号

a                 tm_wday           周几的名称 (简写)

A                 tm_wday           周几的名称 (完整)

b或h              tm_mon            月份的名称 (简写)

B                 tm_mon            月份的名称 (完整)

c                 (全部)            日期和时间

D                 tm_mon、tm_mday、  %m/%d/%y的速写
                  tm_year

d                 tm_mday           该月的第几天，十进制。如果
                                    小于0，则前面放一个空格。值
                                    的范围为1~31

F                 tm_mon、tm_mday、 %Y-%m-%d的速写
                  tm_year

g                 tm_year、tm_wday、ISO 8601 "以周计算的日历" 中年份
                  tm_yday           最后的两个数字。范围为00~99

G                 tm_year、tm_wday、ISO 8601 "以周计算的日历" 中年份
                  tm_yday           的值 (四个数字)

H                 tm_hour           二十四小时制的 "时"，范围为00~23

I                 tm_hour           二十四小时制的 "时"，使用两个数字，范围为01~12

j                 tm_yday           一年中的第几天，使用三个十进制数表示，范围为
                                    001~366

m                 tm_mon            月份，使用两个十进制数表示，范围为00~59

n                 (没有)            换行字符 ('\n')

p                 tm_hour           12小时制中，是AM或PM

r                 tm_hour、tm_min、 十二小时制的时间
                  tm_sec

R                 tm_hour、tm_min   %H:%M的速写

S                 tm_sec            该分钟的第几秒，使用两个十进制数表示，范围为
                                    00~60

t                 (没有)            制表符 ('\t')

T                 tm_hour、tm_min   %H:%M:%S的速写
                  tm_sec

u                 tm_wday           一周的第几天，使用一个十进制数表示，范围为
                                    1~7，其中1表示周一

U                 tm_year、tm_wday  改年的第几周，使用两个十进制数表示，范围为
                  tm_yday           00~53，其中第一周是从一月的第一个周日

V                 tm_year、tm_wday  ISO 8601 "以周几算的日历" 中的第几周，使用
                  tm_yday           两个十进制位数字 (01~53) 表示，第一周从一月
                                    4日当周的星期一开始

w                 tm_wday           一周的第几天，使用一个十进制数表示，范围为
                                    0~6，其中0是星期日

W                 tm_year、tm_wday、一年的第几周，使用两个十进制数表示，范围为
                  tm_yday           00~53，其中第一周是从一月的第一个周一开始计
                                    算的

x                 (全部)            日期

X                 (全部)            时间

y                 tm_year           年份的最后两个数字，范围是00~99

Y                 tm_year           公元年份 (例如: 2005)

z                 tm_isdst          和格林尼治标准时间 (GMT) 的偏差，如果不知道
                                    的话，就是空的 (范围：+0200表示位于GMT东方
                                    两小时)

Z                 tm_isdst          时区的缩写：如果不知道的话，就是空

%                 (没有)            百分比符号 (%)

