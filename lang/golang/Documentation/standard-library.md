---
title: Go Stdlib
author: Zhou Peng <p@ctriple.cn>
description: The Go Programming Language Standard Library
---

| Library           | Description                                                                                                                   |
|-------------------|-------------------------------------------------------------------------------------------------------------------------------|
| unsafe            | contains commands to step out of the Go type-safety, not needed in normal programs; can be useful when interfacing with C/C++ |
| os                | gives us a platform-independent interface to operating-system functionality; its design is Unix-like                          |
| os/exec           | gives you the possibility to run external OS commands and programs                                                            |
| syscall           | is the low-level, external package, which provides a primitive interface to the underlying system calls                       |
| archive/{tar,zip} | functionality for (de)compressing files                                                                                       |
| fmt               | contains functionality for formatted input-output                                                                             |
| io                | provides basic input-output functionality, mostly as a wrapper around os-functions                                            |
| bufio             | wraps around io to give buffered input-output functionality                                                                   |
| path/filepath     | routines for manipulating filename paths targeted at the OS used                                                              |
| flag              | functionality to work with command-line arguments                                                                             |
| strings           | for working with strings                                                                                                      |
| strconv           | converting strings to basic data types                                                                                        |
| unicode           | special functions for Unicode characters                                                                                      |
| regexp            | provides pattern-search functionality in complex strings                                                                      |
| bytes             | contains functions for the manipulation of byte slices                                                                        |
| index/suffixarray | for very fast searching in strings                                                                                            |
| math              | basic mathematical constants and functions                                                                                    |
| math/cmath        | manipulations with complex numbers                                                                                            |
| math/rand         | contains pseudo-random number generators                                                                                      |
| sort              | functionality for sorting arrays and user-defined collections                                                                 |
| math/big          | multiprecision arithmetic for working with arbitrarily large integers and rational numbers                                    |
| container/list    | to work with doubly linked lists                                                                                              |
| container/ring    | to work with circular lists                                                                                                   |
| time              | basic functionality for working with times and dates                                                                          |
| log               | functionality for logging information in a running program                                                                    |
| encoding/json     | implements the functions for reading/decoding as well as writing/encoding data in JSON format                                 |
| encoding/xml      | simple XML 1.0 parser                                                                                                         |
| text/template     | to make data-driven templates which can generate textual output mixed with data, like HTML                                    |
| net               | basic functions for working with network-data                                                                                 |
| http              | functionality for parsing HTTP requests/replies, provides an extensible HTTP server and a basic client                        |
| html              | parser for HTML5                                                                                                              |
| runtime           | operations for interacting with the Go-runtime, such as the garbage collection and goroutines                                 |
| reflect           | implements runtime introspection, allowing a program to manipulate variables with arbitrary types                             |
| exp               | contains 'experimental' packages, that is new packages being build                                                            |
