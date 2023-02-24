# TCP (Transmission Control Protocol) Header

                                           10                                      20                                      30      32
    +---------------------------------------+---------------------------------------+---------------------------------------+-------+
    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | 1 |
    +---------------------------------------+-----------------------+---------------+---------------------------------------+-------+
    |                             Source Port                       |                     Destination Port                          |
    +---------------------------------------------------------------+---------------------------------------------------------------+
    |                                                      Sequence Number                                                          |
    +-------------------------------------------------------------------------------------------------------------------------------+
    |                                                    Acknowledgment Number                                                      |
    +---------------+---------------+---+---+---+---+---+---+---+---+---------------------------------------------------------------+
    |  Data Offset  |   Reserved    |cwr|ece|urg|ack|psh|rst|syn|fin|                            Window                             |
    +---------------+---------------+---+---+---+---+---+---+---+---+---------------------------------------------------------------+
    |                            Checksum                           |                         Urgent Pointer                        |
    +---------------------------------------------------------------+-----------------------------------+---------------------------+
    |                                              Options                                              |           Padding         |
    +---------------------------------------------------------------------------------------------------+---------------------------+
    |                                                             Data                                                              |
    +-------------------------------------------------------------------------------------------------------------------------------+

## TCP Connection Status (RFC 9293)

    LISTEN       - represents waiting for a connection request from any remote TCP peer and port.
    SYN-SENT     - represents waiting for a matching connection request after having sent a connection request.
    SYN-RECEIVED - represents waiting for a confirming connection request acknowledgment after having both received and sent a connection request.
    ESTABLISHED  - represents an open connection, data received can be delivered to the user. The normal state for the data transfer phase of the connection.
    FIN-WAIT-1   - represents waiting for a connection termination request from the remote TCP peer, or an acknowledgment of the connection termination request previously sent.
    FIN-WAIT-2   - represents waiting for a connection termination request from the remote TCP peer.
    CLOSE-WAIT   - represents waiting for a connection termination request from the local user.
    CLOSING      - represents waiting for a connection termination request acknowledgment from the remote TCP peer.
    LAST-ACK     - represents waiting for an acknowledgment of the connection termination request previously sent to the remote TCP peer (this termination request sent to the remote TCP peer already included an acknowledgment of the termination request sent from the remote TCP peer).
    TIME-WAIT    - represents waiting for enough time to pass to be sure the remote TCP peer received the acknowledgment of its connection termination request, and to avoid new connections being impacted by delayed segments from previous connections.
    CLOSED       - represents no connection state at all.

# UDP (User Datagram Protocol) Header

                                           10                                      20                                      30      32
    +---------------------------------------+---------------------------------------+---------------------------------------+-------+
    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | 1 |
    +---------------------------------------+-----------------------+---------------+---------------------------------------+-------+
    |                              Source Port                      |                   Destination Port                            |
    +---------------------------------------------------------------+---------------------------------------------------------------+
    |                                Length                         |                       Checksum                                |
    +---------------------------------------------------------------+---------------------------------------------------------------+
    |                                                             Data                                                              |
    +-------------------------------------------------------------------------------------------------------------------------------+


# IP (Internet Protocol) Headers

                                           10                                      20                                      30      32
    +---------------------------------------+---------------------------------------+---------------------------------------+-------+
    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | 1 |
    +---------------+-------+-------+-------+-----------------------+---------------+---------------------------------------+-------+
    |    Version    |    IHL        |        TOS/DSCP/ECN           |                            Total Length                       |
    +---------------+---------------+-------------------------------+-----------+---------------------------------------------------+
    |                      Identification                           |    Flags  |                  Fragment Offset                  |
    +-------------------------------+-------------------------------+-----------+---------------------------------------------------+
    |         Time To Live          |            Protocol           |                         Header Checksum                       |
    +-------------------------------+-------------------------------+---------------------------------------------------------------+
    |                                                      Source Address                                                           |
    +-------------------------------------------------------------------------------------------------------------------------------+
    |                                                   Destination Address                                                         |
    +---------------------------------------------------------------------------------------------------+---------------------------+
    |                                                         Options                                   |          Padding          |
    +---------------------------------------------------------------------------------------------------+---------------------------+


# ICMP (Internet Control Message Protocol) Basic Headers

                                           10                                      20                                      30      32
    +---------------------------------------+---------------------------------------+---------------------------------------+-------+
    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | 1 |
    +---------------+---------------+-------+-----------------------+---------------+---------------------------------------+-------+
    |    Version    |    IHL        |        TOS/DSCP/ECN           |                            Total Length                       |
    +---------------+---------------+-------------------------------+-----------+---------------------------------------------------+
    |                      Identification                           |    Flags  |                  Fragment Offset                  |
    +-------------------------------+-------------------------------+-----------+---------------------------------------------------+
    |         Time to Live          |            Protocol           |                         Header Checksum                       |
    +---------------------------------------------------------------+---------------------------------------------------------------+
    |                                                      Source Address                                                           |
    +-------------------------------------------------------------------------------------------------------------------------------+
    |                                                   Destination Address                                                         |
    +-------------------------------+-------------------------------+---------------------------------------------------------------+
    |              Type             |             Code              |                           Checksum                            |
    +-------------------------------+-------------------------------+---------------------------------------------------------------+
