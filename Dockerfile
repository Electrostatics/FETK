FROM ubuntu:20.04 as fetk_base

SHELL ["/bin/bash", "-c"]

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
        build-essential \
        cmake \
        gfortran \
        git \
        libarpack2-dev \
        liblapack-dev \
        libf2c2-dev \
        libopenblas-dev \
        libsuitesparse-dev \
        && \
    mkdir /src

##################################

FROM fetk_base

ARG CREATE_PACKAGE=FALSE
ENV CREATE_PACKAGE=${CREATE_PACKAGE}

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
    cmake -DCREATE_PACKAGE=${CREATE_PACKAGE} .. && \
    make install && \
    if [ "${CREATE_PACKAGE,,}" = true ]; then cpack; fi
