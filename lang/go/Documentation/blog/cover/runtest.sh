#!/bin/sh

# package test coverage
go test -cover

# coverage profile
go test -coverprofile=coverage.out
go tool cover -func=coverage.out
go tool cover -html=coverage.out
