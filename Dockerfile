FROM alpine

RUN apk add --no-cache \
    ca-certificates \
 && apk add --no-cache --virtual .build-deps \
    binutils-dev \
    cmake \
    g++ \
    gcc \
    git \
    gmp \
    gmp-dev \
    libexecinfo-dev \
    make \
    musl-dev \
    openssl \
    openblas \
    openblas-dev \
    lapack \
 && apk del .build-deps
