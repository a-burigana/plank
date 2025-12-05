ARG VERSION=24.04
FROM ubuntu:$VERSION

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y make cmake gdb
RUN apt-get update && apt-get install -y libboost-all-dev
RUN apt-get update && apt-get install -y git wget curl

ARG GCC_VERSION=14
ENV GCC_VERSION=$GCC_VERSION
ENV CC=gcc-$GCC_VERSION
ENV CXX=g++-$GCC_VERSION

RUN apt-get update && apt-get install -y gcc-$GCC_VERSION g++-$GCC_VERSION
RUN apt-get update && apt-get install -y valgrind

ENTRYPOINT ["/usr/bin/env", "--"]
