typedef int semaphore;
semaphore mutex = 1;       /* access to rc */
semaphore db = 1;          /* access to db */
int rc = 0;                /* number of reading processes */

void reader(void)
{
    while (1) {
        down(&mutex);      /* exclude access to rc */
        rc = rc + 1;       /* readers add 1 */

        if (rc == 1)       /* first reader */
            down(&db);

        up(&mutex);        /* recover access to rc */
        read_database();   /* read database */
        down(&mutex);      /* exclude access to rc */
        rc = rc - 1;       /* readers minus 1 */

        if (rc == 0)       /* last reader */
            up(&db);

        use_data_read();   /* non-critical area */
    }
}

void writer(void)
{
    while (1) {
        think_up_data();   /* non-critical area */
        down(&db);         /* exclude access to db */
        write_database();  /* modify data */
        up(&db);           /* recover access to db */
    }
}
