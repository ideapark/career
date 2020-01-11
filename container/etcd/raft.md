# Raft

- Time Sequence Required

```text
broadcastTime   <<   electionTimeout   <<    MTBF
 1.ms~10.ms           10.ms~500.ms        1.h~1.Month

broadcastTime = Network Latency + Disk Write
         MTBF = Mean Time Between Failures of Nodes
```
