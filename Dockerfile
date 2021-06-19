FROM ubuntu:20.04 as fetk_base

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
        build-essential \
        cmake && \
    mkdir /src

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
        libarpack2-dev \
        libblas-dev \
        liblapack-dev \
        libsuperlu-dev \
        libf2c2-dev \
        libsuitesparse-dev

COPY cmake /src/cmake
COPY gamer /src/gamer
COPY maloc /src/maloc
COPY mc /src/mc
COPY punc /src/punc
COPY CMakeLists.txt /src/CMakeLists.txt
COPY VERSION /src/VERSION

RUN cd /src && \
    export CC=gcc && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make install
