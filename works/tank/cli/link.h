/*
 * link.h
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef LINK_H
#define LINK_H

/*
 * @brief: connect to server
 * @return: socket file descriptor on success
 *          -1 on failure
 */
int link_connect(const char *server_ip, const char *server_port);

#endif /* LINK_H */
