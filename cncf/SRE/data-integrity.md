# Data Integrity

```text
User deletes                       Application                                             Application                          Data
data                               deletes data                                            purges data                          gone
|                                  |                                                       |                                    |
+----------------------------------|-------------------------------------------------------|------------------------------------+
|        User-visible trash        |     Not user-visible. Soft-deleted by application     |       Data being destroyed by      |
|                                  |         and/or within storage services.               | application and storage service.   |
+----------------------------------+-------------------------------------------------------+------------------------------------+---->
    Eligible for undeletion             Eligible for undeletion by user support                Can't be undeleted, Restroration
          by users                         and/or application administrators                          requires backups

   Protects against mistakes            Protects against bugs in applications                 Backups protect against this and
          by users                     and mistakes by application service providers               all other scenarios
```
