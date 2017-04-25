#!/bin/sh

go test -run=Coverage -coverprofile=c.out runtime
go tool cover -html=c.out
