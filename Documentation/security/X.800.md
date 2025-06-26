# Security Services (X.800)

## AUTHENTICATION

The assurance that the communicating entity is the one that it claims
to be.

### Peer Entity Authentication

Used in association with a logical connection to provide confidence in
the identity of the entities connected.

### Data-Origin Authentication

In a connectionless transfer, provides assurance that the source of
received data is as claimed.

## ACCESS CONTROL

The prevention of unauthorized use of a resource (i.e., this service
controls who can have access to a resource, under what conditions
access can occur, and what those accessing the resource are allowed to
do).

## DATA CONFIDENTIALITY

The protection of data from unauthorized disclosure.

### Connection Confidentiality

The protection of all user data on a connection.

### Connectionless Confidentiality

The protection of all user data in a single data block

### Selective-Field Confidentiality

The confidentiality of selected fields within the user data on a
connection or in a single data block.

### Traffic-Flow Confidentiality

The protection of the information that might be derived from
observation of traffic flows.

## DATA INTEGRITY

The assurance that data received are exactly as sent by an authorized
entity (i.e., contain no modification, insertion, deletion, or
replay).

### Connection Integrity with Recovery

Provides for the integrity of all user data on a connection and
detects any modification, insertion, deletion, or replay of any data
within an entire data sequence, with recovery attempted.

### Connection Integrity without Recovery

As above, but provides only detection without recovery.

### Selective-Field Connection Integrity

Provides for the integrity of selected fields within the user data of
a data block transferred over a connection and takes the form of
determination of whether the selected fields have been modified,
inserted, deleted, or replayed.

### Connectionless Integrity

Provides for the integrity of a single connectionless data block and
may take the form of detection of data modification. Additionally, a
limited form of replay detection may be provided.

### Selective-Field Connectionless Integrity

Provides for the integrity of selected fields within a single
connectionless data block; takes the form of determination of whether
the selected fields have been modified.

## NONREPUDIATION

Provides protection against denial by one of the entities involved in
a communication of having participated in all or part of the
communication.

### Nonrepudiation, Origin

Proof that the message was sent by the specified party.

### Nonrepudiation, Destination

Proof that the message was received by the specified party
