#!/bin/bash

PROTO_DIR=~/Documents/Github/Monitor/ServerApp/lib/proto

assert() {
  expected="$1"
  actual="$2"

  if [ "$actual" = "$expected" ]; then
    echo "OK"
  else
    echo "Expected $expected but got $actual"
    exit 1
  fi
}

grpcurl -plaintext --import-path $PROTO_DIR -proto $PROTO_DIR/service.proto 0.0.0.0:50051 list data.RealtimeService

assert 0 $?