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
 && mkdir -p "/tmp/symengine" \
 && git clone https://github.com/symengine/symengine /tmp/symengine \
 && (cd /tmp/symengine && cmake .) \
 && (cd /tmp/symengine && make && make install) \
 && apk del .build-deps
