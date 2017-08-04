Docker Command One Graph
========================

                                            Container
                               +-------------------------------------+
                               |                                     |
     +-----------+             |                     +---------+     |
     |           |             |                   / |         |     |
     | Tar files |             |                  /  | Stopped |     |
     |           |             |                 / / |         |     |
     +-----------+             |          start / /  +---------+     |
   import ||                   |               / / kill              |
          || export/save       |     restart  / /                    |
       +-------+     start     |   +---------+ /                     |
       |       | --------------|>  |         |                       |
       | Image |               |   | Running |                       |
       |       | <-------------|-  |         |                       |
       +-------+     commit    |   +---------+ \                     |
     pull ||                   |              \ \                    |
          || push              |               \ \ pause             |
    +------------+             |                \ \  +--------+      |
    |            |             |         unpause \ \ |        |      |
    |  Registry  |             |                  \  | Paused |      |
    |            |             |                   \ |        |      |
    +------------+             |                     +--------+      |
                               |                                     |
                               +-------------------------------------+

Docker Command Category
=======================

Docker Environment Information:

- info
- version

Container Life Cycle Management:

- create
- exec
- kill
- pause
- restart
- rm
- run
- start
- stop
- unpause

Image Repository Command:

- login
- logout
- pull
- push
- search

Image Management:

- build
- images
- import
- load
- rmi
- save
- tag
- commit

Container Operation:

- attach
- export
- inspect
- port
- ps
- rename
- stats
- top
- wait
- cp
- diff
- update

Container Resource Mgt:

- volume
- network

System Log Information:

- events
- history
- logs
