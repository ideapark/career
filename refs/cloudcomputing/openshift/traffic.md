# Getting Traffic into a Cluster

The recommendation, in order or preference, is:

- If you have HTTP/HTTPS, use a router.
- If you have a TLS-encrypted protocol other than HTTPS (for example, TLS with
  the SNI header), use a router.
- Otherwise, use a Load Balancer, and External IP, or a NodePort.

| Method                                                         | Purpose                                                                                                                 |
| ---                                                            | ---                                                                                                                     |
| Use a router                                                   | Allows access to HTTP/HTTPS traffic and TLS-encrypted protocols other than HTTPS (for example, TLS with the SNI header) |
| Automatically Assign a Public IP Using a Load Balancer Service | Allows traffic to non-standard ports through an IP address assigned from a pool.                                        |
| Manually assign an external IP to a service                    | Allows traffic to non-standard ports through a specific IP address.                                                     |
| Configure a NodePort                                           | Expose a service on all nodes in the cluster.                                                                           |
