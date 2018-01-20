/*
 * link.h
 *
 * Copyright (c) Zhou Peng <p@ctriple.cn>
 */

#ifndef LINK_H
#define LINK_H

/*
 * open listening on port
 */
int link_open(const char *port);

/*
 * stop listening
 */
void link_close(void);

/*
 * accept client connection
 */
int link_accept(void);

#endif /* LINK_H */
