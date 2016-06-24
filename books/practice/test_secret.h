/*
 * 测试技巧:
 *
 *  1. 临时减小数组初始值
 *
 *  2. 让散列表返回某个常数，是所有元素都跑到同一个散列桶里
 *
 *  3. 自定义存储分配函数，构造内存分配失败场景(testmalloc)
 *
 */

/* testmalloc: return NULL after 10 calls */
void* testmalloc(size_t n)
{
    static int count = 0;

    if (++count > 10)
        return NULL;
    else
        return malloc(n);
}
