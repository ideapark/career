# Ingress

Kubernetes service out of cluster access point, such as URL, LoadBalance, SSL
termination, HTTP routing.

   Internet
      |
  ----------
  [Services]


   Internet
       |
   [Ingress]
  ---|---|---
  [Services]


## Multi-Service Ingress.

foo.bar.com -> 178.91.123.132 -> /foo  svc1:80
                                 /bar  svc2:80

## Virtual Host Ingress

foo.bar.com --+                +--> foo.bar.com  svc1:80
              | 178.91.123.132 |
bar.foo.com --+                +--> bar.foo.com  svc2:80

## TLS Ingress

Terminate TLS from Secret certificate (tls.crt & tls.key)
