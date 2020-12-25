# Guidelines for usage

1. The USE method tells you how happy your machines are, the RED method tells you how happy your users are.
2. USE reports on causes of issues.
3. RED reports on user experience and is more likely to report symptoms of problems.
4. The best practice of alerting is to alert on symptoms rather than causes, so alerting should be done on RED dashboards.

# USE method

USE stands for:

1. Utilization - Percent time the resource is busy, such as node CPU usage
2. Saturation - Amount of work a resource has to do, often queue length or node load
3. Errors - Count of error events

This method is best for hardware resources in infrastructure, such as CPU,
memory, and network devices.

# RED method

RED stands for:

1. Rate - Requests per second
2. Errors - Number of requests that are failing
3. Duration - Amount of time these requests take, distribution of latency measurements

This method is most applicable to services, especially a microservices
environment. For each of your services, instrument the code to expose these
metrics for each component. RED dashboards are good for alerting and SLAs. A
well-designed RED dashboard is a proxy for user experience.

# The Four Golden Signals

According to the Google SRE handbook, if you can only measure four metrics of
your user-facing system, focus on these four.

This method is similar to the RED method, but it includes saturation.

1. Latency - Time taken to serve a request
2. Traffic - How much demand is placed on your system
3. Errors - Rate of requests that are failing
4. Saturation - How “full” your system is
