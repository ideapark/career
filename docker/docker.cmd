Docker Command One Graph
========================

     +-----------+                                   +---------+
     |           |                                 / |         |
     | Tar files |                                /  | Stopped |
     |           |                               / / |         |
     +-----------+                        start / /  +---------+
   import ||                                   / / kill
          || export/save             restart  / /
       +-------+     start         +---------+ /
       |       | --------------->  |         |
       | Image |                   | Running |
       |       | <---------------  |         |
       +-------+     stop          +---------+ \
     pull ||                                  \ \
          || push                              \ \ pause
    +------------+                              \ \  +--------+
    |            |                       unpause \ \ |        |
    |  Registry  |                                \  | Paused |
    |            |                                 \ |        |
    +------------+                                   +--------+
