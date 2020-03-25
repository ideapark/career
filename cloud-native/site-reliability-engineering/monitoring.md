# Monitoring

## Why Monitor?

- Analyzing long-term trends

How big is my database and how fast is it growing? How quickly is my
daily-active user count growing?

- Comparing over time or experiment groups

Are queries faster with Acme Bucket of Bytes 2.72 versus Ajax DB 3.14? How much
better is my memcache hit rate with an extra node? Is my site slower than it was
last week?

- Alerting

Something is broken, and somebody needs to fix it right now! Or, something might
break soon, so somebody should look soon.

- Building dashboards

Dashboards should answer basic questions about your service, and normally
include some form of the four golden signals (discussed in The Four Golden
Signals).

- Conducting ad hoc retrospective analysis (i.e., debugging)

Our latency just shot up; what else happened around the same time?

## Paging a human only when necessory

Monitoring is one of the primary means by which service owners keep track of a
system’s health and availability. As such, monitoring strategy should be
constructed thoughtfully. A classic and common approach to monitoring is to
watch for a specific value or condition, and then to trigger an email alert when
that value is exceeded or that condition occurs. However, this type of email
alerting is not an effective solution: a system that requires a human to read an
email and decide whether or not some type of action needs to be taken in
response is fundamentally flawed. Monitoring should never require a human to
interpret any part of the alerting domain. Instead, software should do the
interpreting, and humans should be notified only when they need to take action.

There are three kinds of valid monitoring output:

- Alerts

Signify that a human needs to take action immediately in response to something
that is either happening or about to happen, in order to improve the situation.

- Tickets

Signify that a human needs to take action, but not immediately. The system
cannot automatically handle the situation, but if a human takes action in a few
days, no damage will result.

- Logging

No one needs to look at this information, but it is recorded for diagnostic or
forensic purposes. The expectation is that no one reads logs unless something
else prompts them to do so.

## The Four Golden Signals

- Latency

The time it takes to service a request. It’s important to distinguish between
the latency of successful requests and the latency of failed requests. For
example, an HTTP 500 error triggered due to loss of connection to a database or
other critical backend might be served very quickly; however, as an HTTP 500
error indicates a failed request, factoring 500s into your overall latency might
result in misleading calculations. On the other hand, a slow error is even worse
than a fast error! Therefore, it’s important to track error latency, as opposed
to just filtering out errors.

- Traffic

A measure of how much demand is being placed on your system, measured in a
high-level system-specific metric. For a web service, this measurement is
usually HTTP requests per second, perhaps broken out by the nature of the
requests (e.g., static versus dynamic content). For an audio streaming system,
this measurement might focus on network I/O rate or concurrent sessions. For a
key-value storage system, this measurement might be transactions and retrievals
per second.

- Errors

The rate of requests that fail, either explicitly (e.g., HTTP 500s), implicitly
(for example, an HTTP 200 success response, but coupled with the wrong content),
or by policy (for example, "If you committed to one-second response times, any
request over one second is an error"). Where protocol response codes are
insufficient to express all failure conditions, secondary (internal) protocols
may be necessary to track partial failure modes. Monitoring these cases can be
drastically different: catching HTTP 500s at your load balancer can do a decent
job of catching all completely failed requests, while only end-to-end system
tests can detect that you’re serving the wrong content.

- Saturation

How "full" your service is. A measure of your system fraction, emphasizing the
resources that are most constrained (e.g., in a memory-constrained system, show
memory; in an I/O-constrained system, show I/O). Note that many systems degrade
in performance before they achieve 100% utilization, so having a utilization
target is essential.

In complex systems, saturation can be supplemented with higher-level load
measurement: can your service properly handle double the traffic, handle only
10% more traffic, or handle even less traffic than it currently receives? For
very simple services that have no parameters that alter the complexity of the
request (e.g., "Give me a nonce" or "I need a globally unique monotonic
integer") that rarely change configuration, a static value from a load test
might be adequate. As discussed in the previous paragraph, however, most
services need to use indirect signals like CPU utilization or network bandwidth
that have a known upper bound. Latency increases are often a leading indicator
of saturation. Measuring your 99th percentile response time over some small
window (e.g., one minute) can give a very early signal of saturation.

Finally, saturation is also concerned with predictions of impending saturation,
such as "It looks like your database will fill its hard drive in 4 hours."
