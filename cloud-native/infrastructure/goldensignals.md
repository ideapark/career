Latency

Latency is how long it takes to do something. It is commonly understood as the
elapsed time between a request and its completion. For instance, in a network,
latency is measured as the time it takes to send a packet of data between two
points. An Operator might measure application-specific, internal latencies like
the lag time between actions in a game client and responses in the game engine.

Traffic

Traffic measures how frequently a service is requested. HTTP requests per second
is the standard measurement of web service traffic. Monitoring regimes often
split this measurement between static assets and those that are dynamically
generated. It makes more sense to monitor something like transactions per second
for a database or file server.

Errors

Errors are failed requests, like an HTTP 500-series error. In a web service, you
might have an HTTP success code but see scripting exceptions or other
client-side errors on the successfully delivered page. It may also be an error
to exceed some latency guarantee or performance policy, like a guarantee to
respond to any request within a time limit.

Saturation

Saturation is a gauge of a service’s consumption of a limited resource. These
measurements focus on the most limited resources in a system, typically CPU,
memory, and I/O. There are two key ideas in monitoring saturation. First,
performance gets worse even before a resource is 100% utilized. For instance,
some filesystems perform poorly when more than about 90% full, because the time
it takes to create a file increases as available space decreases. Because of
similar effects in nearly any system, saturation monitors should usually respond
to a high-water mark of less than 100%. Second, measuring saturation can help
you anticipate some problems before they happen. Dividing a file service’s free
space by the rate at which an application writes data lets your Operator
estimate the time remaining until storage is full.
