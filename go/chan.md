# Go Channel

## close/send/recv

| OPERATION | nil channel | closed channel | not-closed non-nil channel |
|-----------|-------------|----------------|----------------------------|
| close     | panic       | panic          | succeed to close           |
| send to   | block ever  | panic          | block or succeed to send   |
| recv from | block ever  | never block    | block or succeed to recv   |

## Channel Operation

- case A

When a goroutine `Grecv` tries to receive a value from a not-closed non-nil
channel, the goroutine `Grecv` will acquire the lock associated with the channel
firstly, then do the following steps until one condition is satisfied.

  1) If the value buffer queue of the channel is not empty, in which case the
     receiving goroutine queue of the channel must be empty, the goroutine
     `Grecv` will receive (by unshifting) a value from the value buffer queue.
     If the sending goroutine queue of the channel is also not empty, a sending
     goroutine will be unshifted out of the sending goroutine queue and resumed
     to running state again. The value the just unshifted sending goroutine
     trying to send will be pushed into the value buffer queue of the channel.
     The receiving goroutine `Grecv` continues running. For this scenario, the
     channel receive operation is called a non-blocking operation.

  2) Otherwise (the value buffer queue of the channel is empty), if the sending
     goroutine queue of the channel is not empty, in which case the channel must
     be an unbuffered channel, the receiving goroutine `Grecv` will unshift a
     sending goroutine from the sending goroutine queue of the channel and
     receive the value the just unshifted sending goroutine trying to send. The
     just unshifted sending goroutine will get unblocked and resumed to running
     state again. The receiving goroutine `Grecv` continues running. For this
     scenario, the channel receive operation is called a non-blocking operation.

  3) If value buffer queue and the sending goroutine queue of the channel are
     both empty, the goroutine `Grecv` will be pushed into the receiving
     goroutine queue of the channel and enter (and stay in) blocking state. It
     may be resumed to running state when another goroutine sends a value to the
     channel later. For this scenario, the channel receive operation is called a
     blocking operation.

- case B

When a goroutine `Gsend` tries to send a value to a not-closed non-nil channel,
the goroutine `Gsend` will acquire the lock associated with the channel firstly,
then do the following steps until one step condition is satisfied.

  1) If the receiving goroutine queue of the channel is not empty, in which case
     the value buffer queue of the channel must be empty, the sending goroutine
     `Gsend` will unshift a receiving goroutine from the receiving goroutine
     queue of the channel and send the value to the just unshifted receiving
     goroutine. The just unshifted receiving goroutine will get unblocked and
     resumed to running state again. The sending goroutine `Gsend` continues
     running. For this scenario, the channel send operation is called a
     non-blocking operation.

  2) Otherwise (the receiving goroutine queue is empty), if the value buffer
     queue of the channel is not full, in which case the sending goroutine must
     be also empty, the value the sending goroutine `Gsend` trying to send will
     be pushed into the value buffer queue, and the sending goroutine `Gsend`
     continues running. For this scenario, the channel send operation is called
     a non-blocking operation.

  3) If the receiving goroutine queue is empty and the value buffer queue of the
     channel is already full, the sending goroutine `Gsend` will be pushed into
     the sending goroutine queue of the channel and enter (and stay in) blocking
     state. It may be resumed to running state when another goroutine receives a
     value from the channel later. For this scenario, the channel send operation
     is called a blocking operation.

- case C

When a goroutine tries to close a not-closed non-nil channel, once the goroutine
has acquired the lock of the channel, both of the following two steps will be
performed by the following order.

  1) If the receiving goroutine queue of the channel is not empty, in which case
     the value buffer of the channel must be empty, all the goroutines in the
     receiving goroutines queue of the channel will be unshifted one by one,
     each of them will receive a zero value of the element type of the channel
     and be resumed to running state.

  2) If the sending goroutine queue of the channel is not empty, all the
     goroutines in the sending goroutine queue of the channel will be unshifted
     one by one and each of them will produce a panic for sending on a closed
     channel. This is the reason why we should avoid concurrent send and close
     operations on the same channel. In fact, data races happen in concurrent
     send and close operations.

- case D

After a non-nil channel is closed, channel receive operations on the channel
will never block. The values in the value buffer of the channel can still be
received. The accompanying second optional bool return values are still true.
Once all the values in the value buffer are taken out and received, infinite
zero values of the element type of the channel will be received by any of the
following receive operations on the channel. As mentioned above, the optional
second return result of the a channel receive operation is an untyped boolean
value which indicates whether or not the first result (the received value) is
sent before the channel is closed. If the second return result is false, then
the first result (the received value) must be a zero value of the element type
of the channel.

## Close Channel

DON'T CLOSE A CHANNEL FROM THE RECEIVER SIDE AND DON'T CLOSE A CHANNEL IF THE
CHANNEL HAS MULTIPLE CONCURRENT SENDERS.

The universal principle is `DON'T CLOSE (OR SEND VALUES TO) CLOSED CHANNEL.`

## channel (MEMORY COPY) vs mutex (MEMORY SHARE)

* Use locking (mutexes) when:
  * caching information in a shared data structure
  * holding state information, that is context or status of the running application

* Use channels when:
  * communicating asynchronous results
  * distributing units of work
  * passing ownership of data

* Wait Group

Another important synchronisation primitive is sync.WaitGroup. These allow
co-operating goroutines to collectively wait for a threshold event before
proceeding independently again. This is useful typically in two cases.

Firstly, when 'cleaning up', a sync.WaitGroup can be used to ensure that all
goroutines - including the main one - wait before all terminating cleanly.

The second more general case is of a cyclic algorithm that involves a set of
goroutines that all work independently for a while, then all wait on a barrier,
before proceeding independently again. This pattern might be repeated many
times. Data might be exchanged at the barrier event. This strategy is the basis
of Bulk Synchronous Parallelism (BSP).

Channel communication, mutexes and wait-groups are complementary and can be
combined.

## Go runtime implementation

```text
  hchan                 0      1      2
+--------+          +------+------+------+
| buf    |--------->| elem | elem |      |
|--------|          +------+------+------+
| sendx  |
|--------|
| recvx  |     +------------------------------------------------+
|--------|     |    +-----+    +-----+    +-----+    +-----+    |
| sendq  |-----+--->|sudog|<-->|sudog|<-->|sudog|<-->|sudog|<---+
|--------|          +-----+    +-----+    +-----+    +-----+---> nil
| closed |-----+
|--------|     |    +-----+    +-----+    +-----+    +-----+---> nil
| lock   |     +--->|sudog|<-->|sudog|<-->|sudog|<-->|sudog|<-+
|--------|     |    +-----+    +-----+    +-----+    +-----+  |
| ...    |     +----------------------------------------------+
+--------+

  sudog
+------+              .---.
| g    |------------->| G |
|------|              .---.
| next |
|------|
| prev |
|------|
| elem |
|------|
| ...  |
+------+
```
