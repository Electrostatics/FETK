FROM ubuntu:20.04 as fetk_base

SHELL ["/bin/bash", "-c"]

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
        build-essential \
        cmake \
        git \
        libarpack2-dev \
        liblapack-dev \
        libf2c2-dev \
        libopenblas-serial-dev \
        libsuitesparse-dev \
        libsuperlu-dev \
        && \
    mkdir /src

##################################

FROM fetk_base

ARG CREATE_PACKAGE=FALSE
ARG FETK_STATIC_BUILD=ON
ARG MAKEJOBS="-j"

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
    cmake \
        -DCREATE_PACKAGE:BOOL=${CREATE_PACKAGE} \
        -DFETK_STATIC_BUILD:BOOL=${FETK_STATIC_BUILD} \
        .. && \
    make ${MAKEJOBS} install && \
    if [ "${CREATE_PACKAGE,,}" = true ]; then cpack; fi
