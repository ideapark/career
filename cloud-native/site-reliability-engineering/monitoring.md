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
