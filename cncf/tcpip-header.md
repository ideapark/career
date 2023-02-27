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
    |  Data Offset  |   Reserved    |CWR|ECE|URG|ACK|PSH|RST|SYN|FIN|                            Window                             |
    +---------------+---------------+---+---+---+---+---+---+---+---+---------------------------------------------------------------+
    |                            Checksum                           |                         Urgent Pointer                        |
    +---------------------------------------------------------------+-----------------------------------+---------------------------+
    |                                              Options                                              |           Padding         |
    +---------------------------------------------------------------------------------------------------+---------------------------+
    |                                                             Data                                                              |
    +-------------------------------------------------------------------------------------------------------------------------------+

## TCP Header Explained

```text
          Source Port: (16 bits)
                  The source port number

     Destination Port: (16 bits)
                  The destination port number

      Sequence Number: (32 bits)
                  The sequence number of the first data octet in this segement
                  (except when the SYN flag is set). If SYN is set, the sequence
                  number is the initial sequence number (ISN) and the first data
                  octet is ISN+1.

Acknowledgment Number: (32 bits)
                  If the ACK control bit is set, this field contains the value of
                  the next sequence number the sender of the segment is expecting
                  to receive. Once a connection is established, this is always sent.

          Data Offset: (4 bits)
                  The number of 32-bit words in the TCP header. This indicates where
                  the data begins. The TCP header (even one including options) is
                  an integer multiple of 32 bits long.

             Reserved: (4 bits)
                  A set of control bits reserved for future use. Must be zero in
                  generated segments and must be ignored in received segments if
                  the corresponding future features are not implemented by the
                  sending or receiving host.

         Control Bits:
                  The control bits are also known as "flags". Assigment is managed
                  by IANA from the "TCP Header Flags" registry.

                  CWR: (1 bit) Congestion Window Reduced
                  ECE: (1 bit) ECN-Echo
                  URG: (1 bit) Urgent pointer field is significant
                  ACK: (1 bit) Acknowledgment field is significant
                  PSH: (1 bit) Push function
                  RST: (1 bit) Reset the connection
                  SYN: (1 bit) Synchronize sequence numbers
                  FIN: (1 bit) No more data from sender

               Window: (16 bits)
                  The number of data octets beginning with the one indicated in the
                  acknowledgment field that the sender of this segment is willing to
                  accept. The value is shifted when the window scaling extension is
                  used.

                  The window size MUST be treated as an unsigned number, or else
                  large window sizes will appear like negative windows and TCP will
                  not work. It is RECOMMENDED that implementations will reserve 32-bit
                  fields for the send and receive window sizes in the connection
                  record and do all window computations with 32 bits.

             Checksum: (16 bits)
                  The checksum field is the 16-bit one's complement of the ones' complement
                  sum of all 16-bit words in the header and text. The checksum computation
                  needs to ensure the 16-bit alignment of the data being summed. If a
                  segment contains an odd number of header and text octets, alignment can
                  be achieved by padding the last octet with zeros on its right to form a
                  16-bit word for checksum purposes. The pad is not transmitted as part of
                  the segment. While computing the checksum, the checksum field itself is
                  replaced with zeros.

       Urgent Pointer: (16 bits)
                  This field communicates the current value of the urgent pointer as a
                  positive offset from the sequence number in this segment. The urgent
                  pointer points to the sequence number of the octet following the urgent
                  data. This field is only to be interpreted in segments with the URG control
                  bit set.

              Options: (DOffset-5)*32
                  Kind  Lengh    Meaning
                  ----------------------------------------
                   0    -        End of Option List Option
                   1    -        No-Operation
                   2    4        Maximum Segment Size

                 Data: (variable length)
                  User data carried by the TCP segment.
```

## Key Connection State Variables

```text
                   1         2          3          4
              ----------|----------|----------|----------
                     SND.UNA    SND.NXT    SND.UNA
                                          +SND.WND

        1 - old sequence numbers that have been acknowledged
        2 - sequence numbers of unacknowledged data
        3 - sequence numbers allowed for new data transmission
        4 - future sequence numbers that are not yet allowed
```

```text
                       1          2          3
                   ----------|----------|----------
                          RCV.NXT    RCV.NXT
                                    +RCV.WND

        1 - old sequence numbers that have been acknowledged
        2 - sequence numbers allowed for new reception
        3 - future sequence numbers that are not yet allowed
```

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

```text
High Order Bits Format                           Class
--------------- -------------------------------  -----
    0            7 bits of net, 24 bits of host    a
    10          14 bits of net, 16 bits of host    b
    110         21 bits of net,  8 bits of host    c
    111         escape to extended addressing mode
```

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
