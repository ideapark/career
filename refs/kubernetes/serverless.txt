# Serverless

+-----------+                         <--+
| Functions |                            |
+-----------+                            |
+-------------------+                    | Serverless = BaaS + FaaS
| Apps              |                    |
+-------------------+                 <--+
+--------------------------+          <--+
| Containers               |             |
+--------------------------+             | Infrastructure
+---------------------------------+      |
| Virtual Machines                |      |
+---------------------------------+   <--+
+----------------------------------------+
| Bare Metal                             |
+----------------------------------------+

BaaS (Backend as a Service): Auth0, AWS RDS
FaaS (Functions as a Service): AWS Lambda, Google Functions
