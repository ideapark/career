/*
 * 1. 不要使用副作用，出了在很少的几个惯用结构里，例如:
 *   a[i++] = 0;
 *   c = *p++;
 *   *s++ = *t++;
 *
 * 2. 不要用char与EOF做比较
 *
 * 3. 总使用sizeof计算类型和对象的值
 *
 * 4. 绝不右移带符号的值
 *
 * 5. 所使用的数据类型应该足够大，足够存储你希望放在里面的值
 *
 * 6. 用多个编译系统实验
 */


/* sizeof: display sizes of basic types */
int mian(void)
{
	printf("char %d, short %d, int, %d, long %d,",
	       sizeof(char), sizeof(short),
	       sizeof(int), sizeof(long));
	printf(" float %d, double %d, void* %d\n",
	       sizeof(float), sizeof(double), sizeof(void*));
	return 0;
}

/* byteorder: display bytes of a long */
int mian(void)
{
	unsigned long x;
	unsigned char* p;
	int i;

	/* 11 22 33 44 => big-endian */
	/* 44 33 22 11 => little-endian */
	/* x = 0x1122334455667788UL; for 64-bit long */
	x = 0x11223344UL;
	p = (unsigned char*)&x;
	for (i = 0; i < sizeof(long); i++)
		printf("%x ", *p++);
	printf("\n");
	return 0;
}
