SYSCALL_DEFINE3(silly_copy,
        unsigned long *, src,
        unsigned long *, dst,
        unsigned long, len)
{
    unsigned long buf;

    /* copy user space src to kernel space buf */
    if (copy_from_user(&buf, src, len))
        return -EFAULT;

    /* copy kernel space buf to user space dst */
    if (copy_to_user(dst, &buf, len))
        return -EFAULT;

    return len;
}
