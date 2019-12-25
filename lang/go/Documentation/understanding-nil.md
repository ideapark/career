# Understanding nil

- what is nil

1. dictionary

```text
`nil` meaning `nothing`
`null` meaning `not any`
`none` meaning `not one`
```

- what is nil in Go

1. predefined not keyword

```go
var nil = errors.New("-\_(-)_/")
```

2. kinds of nil

a. pointers
b. slices
c. maps
d. channels
e. functions
f. interfaces struct(type, value)

3. nil is not nil

```go
var p *Person           // nil of type *Person
var s fmt.Stringer = p  // Stringer(*Person, nil)
fmt.Println(s == nil)   // false
```

```go
func do() error {           // error (*doError, nil)
    var err *doError
    return err              // nil of type *doError
}
func main() {
    err := do()             // error (*doError, nil)
    fmt.Println(err == nil) // false
}
```

```go
func do() *doError {        // nil of type *doError
    return nil
}
func main() {
    err := do()             // nil of type *doError
    fmt.Println(err == nil) // true
}
```

- what does nil mean

```text
bool    --> false          pointers   --> nil  (point to nothing)
numbers --> 0              slices     --> nil  (have no backing array)
string  --> ""             maps       --> nil  (are not initialized)
                           channels   --> nil  (are not initialized)
                           functions  --> nil  (are not initialized)
                           interfaces --> nil  (have no value assigned, not even a nil pointer)
```

- is nil useful

a. pointer

nil receivers are useful

```go
type tree struct {
    v int
    l *tree
    r *tree
}

func (t *tree) Sum() int {
    if t == nil {
        return 0
    }
    return t.v + t.l.Sum() + t.r.Sum()
}

func (t *tree) String() string {
    if t == nil {
        return ""
    }
    return fmt.Sprint(t.l, t.v, t.r)
}

func (t *tree) Find(v int) bool {
    if t == nil {
        return false
    }
    return t.v == v || t.l.Find(v) || t.r.Find(v)
}
```

b. slices

use nil slices, they're often fast enough.

```go
var s []int
for i := 0; i < 10; i++ {
    fmt.Printf("len: %2d, cap: %2d\n", len(s), cap(s))
    s = append(s, i)
}
```

c. maps

use nil maps as read-only empty maps.

```go
func NewGet(url string, headers map[string]string) (*http.Request, error) {
    req, err := http.NewRequest(http.MethodGet, url, nil)
    if err != nil {
        return nil, err
    }
    for k, v := range headers {
        req.Header.Set(k, v)
    }
    return req, nil
}

// with header
NewGet(
    "http://google.com",
    map[string]string{
        "USER_AGENT": "golang/gopher",
    },
)

// no header #1
NewGet("http://google.com", map[string]string{})

// no header #2 (more idiomatic)
NewGet("http://google.com", nil)
```

d. channels

use nil channel to disable a select case.

  read nil channel blocks forever
  write nil channel blocks forever
  close of nil channel panic

```
// bug #1
// if a or b closed, zero value return from channel
func merge(out chan<- int, a, b <-chan int) {
    for {
        select {
        case v := <-a:
            out <- v
        case v := <-b:
            out <- v
        }
    }
}

// bug #2
// panic: goroutine deadlock
func merge(out chan<- int, a, b <-chan int) {
    var aclosed, bclosed bool
    for !aclosed || !bclosed {
        select {
        case v, ok := <-a:
            if !ok { aclosed = true; continue }
            out <- v
        case v, ok := <-b:
            if !ok { bclosed = true; continue }
            out <- v
        }
    }
}

// work
func merge(out chan<- int, a, b <-chan int) {
    for a != nil || b != nil {
        select {
        case v, ok := <-a:
            if !ok { a = nil; continue }
            out <- v
        case v, ok := <-b:
            if !ok { b = nil; continue }
            out <- v
        }
    }
}
```

e. functions

nil funcs as struct fileds

```go
type Foo struct {
    f func() error
}
```

nil funcs for default values

```go
func NewServer(logger func(string, ...interface{})) {
    if logger == nil {
        logger = log.Printf
    }
    logger("initializing %s", os.Getenv("hostname"))
    ...
}
```

f. interfaces

nil interface is used as a signal

```go
if err == nil {
...
}
```

nil values can satisfy interfaces

```go
type Summer interface {
    Sum() int
}

var t *tree
var s Summer = t
fmt.Println(t == nil, s.Sum()) // true 0

type ints []int
func (i ints) Sum() int {
    s := 0
    for _, v := range i {
        s += v
    }
    return s
}
var i []ints
var s Summer = i
fmt.Println(i == nil, s.Sum()) // true 0
```

use nil interfaces to signal default

```go
http.HandleFunc("localhost:8080", nil)
```

```text
pointers     methods can be called on nil receivers
slices       perfectly valid zero values
maps         perfect as read-only values
channels     essential for some concurrency patterns
functions    needed for completeness
interfaces   the most used signal in Go (err != nil)
```
