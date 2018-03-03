# Struct Memory Layout

## struct type

       type Point struct { x, y int }


## Initialized with new

         new(Point)
       +-------------+
       |     *       | *Point
       +------\------+
               \
               +-----|-----+
               |  0  |  0  | Point
               +-----|-----+


## Initialized as a struct literal

       p := Point{10, 20}
         +-----|-----+
         |  0  |  0  | Point
         +-----|-----+

       pp := &Point{10, 20}
         +--------+
         |    *   | *Point
         +-----\--+
                \
                 +-----|-----+
                 |  0  |  0  | Point
                 +-----|-----+


# Memory layout of a struct of structs

    type Rect1 struct { Min, Max Point }
    type Rect2 struct { Min, Max *Point }

        r1 := Rect1{Point{10, 20}, Point{50,60}}
            +----|----|----|----+
            | 10 | 20 | 50 | 60 | Rect1
            +----|----|----|----+

        r2 := Rect2{&Point{10, 20}, &Point{50, 60}}
            +--------|--------+
            |   *    |    *   | Rect2
            +----\---|-------\+
                  \           \
                   +----|----+ +----|----+
                   | 10 | 20 | | 50 | 60 | Point
                   +----|----+ +----|----+
