#!/bin/bash

PROTO_DIR=~/Documents/Github/Monitor/ServerApp/lib/proto

grpcurl -plaintext --import-path $PROTO_DIR -proto $PROTO_DIR/service.proto -d '{"index": 1}' 0.0.0.0:50051 data.RealtimeService.getId
grpcurl -plaintext --import-path $PROTO_DIR -proto $PROTO_DIR/service.proto -d '{"index": 2}' 0.0.0.0:50051 data.RealtimeService.getId
grpcurl -plaintext --import-path $PROTO_DIR -proto $PROTO_DIR/service.proto 0.0.0.0:50051 data.RealtimeService.sendValue