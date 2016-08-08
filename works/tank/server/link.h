/*
 * link.h
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef LINK_H
#define LINK_H

int link_open(const char *port);
void link_close(void);
int link_accept(void);

#endif /* LINK_H */
