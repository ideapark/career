# iptables vs ipvs

- Flush route rule

| #.Service | #.Iptables | Deplay - add 1 iptables | Deplay - add 1 ipvs rule |
| ---       | ---        | ---                     | ---                      |
| 1         | 8          | 50us                    | 30us                     |
| 5000      | 40000      | 11min                   | 50us                     |
| 20000     | 160000     | 5hour                   | 70us                     |

- Throughoutput and Deplay

| Mode     | Concurrency | Throughoutput | Avg Delay |
| ---      | ---         | ---           | ---       |
| iptables | 500         | 23353/s       | 30.11ms   |
| ipvs     | 500         | 31094/s       | 30.06ms   |
| iptables | 1000        | 28492/s       | 125.22ms  |
| ipvs     | 1000        | 31361/s       | 30.16ms   |

- Resource

| Resource | #.Service | ipvs   | iptables |
| ---      | ---       | ---    | ---      |
| memory   | 1000      | 386Mb  | 1.1Gb    |
|          | 5000      | N/A    | 1.9Gb    |
|          | 10000     | 542Mb  | 2.3Gb    |
|          | 15000     | N/A    | OOM      |
|          | 50000     | 1272Mb | OOM      |
| ---      | ---       | ---    | ---      |
| cpu      | 1000      | 0%     | N/A      |
|          | 5000      | 0%     | 50%~85%  |
|          | 10000     | 0%     | 50%~100% |
|          | 15000     | 0%     | N/A      |
|          | 50000     | 0%     | N/A      |
