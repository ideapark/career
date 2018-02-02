ECF: Exceptional Control Flow

+-----------+-----------------------+----------------+------------------------------+
| Type      | Cause                 | [S]ync/[A]snyc | Return                       |
+-----------+-----------------------+----------------+------------------------------+
| interrupt | IO Device Signal      | A              | Next Instruction             |
| trap      | Raised Purposely      | S              | Next Instruction             |
| fault     | Recoverable Fault     | S              | Possible Current Instruction |
| abort     | Non-Recoverable Fault | S              | No Return                    |
+-----------+-----------------------+----------------+------------------------------+
