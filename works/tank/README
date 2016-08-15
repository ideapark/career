Tank War
========

Copyright (c) Zhou Peng <lockrecv@qq.com>


Game Introduction
-----------------

Tank War one was a classical red-white game, two players both have 4
tanks on the map and 4 lifes to revive. Player can get scores by
kill the other side player (which got 20 points) or eat coins on the
map (1-5 points). Two players fight two legs, 150 rounds each leg.
sum up two legs's scores to define the final winner.

Game Message Exchange Timeline
------------------------------

Player1            Player2           Server
   |                  |                 |
   |                  |   Game start    |
   |    Game start    |<----------------|
   |<-----------------------------------|
   |                  |                 |
   |                  |   Register name |
   |    Register name |---------------->|
   |----------------------------------->|
   |                  |                 |----
   |                  |   Leg start     |   |
   |    Leg start     |<----------------|   |
   |<-----------------------------------|   |
   |                  |                 |---|------------------
   |                  |   Round step    |   |                 |
   |    Round step    |<----------------| Loop LEG_MAX      Loop ROUND_MAX or any player lose
   |<-----------------------------------|   |                 |
   |                  |   Do Roundstep  |   |                 |
   |    Do Roundstep  |---------------->|---|------------------
   |----------------------------------->|   |
   |                  |                 |   |
   |                  |   Leg end       |   |
   |    Leg end       |<----------------|----
   |<-----------------------------------|
   |                  |                 |
   |                  |   Game over     |
   |    Game over     |<----------------|
   |<-----------------------------------|
   |                  |                 |
