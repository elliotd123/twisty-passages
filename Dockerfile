FROM ubuntu:24.04

RUN apt-get update
RUN apt-get install -y \
    build-essential \
    cmake \
    git \
    libsdl2-dev \
    libsdl2-ttf-dev    

ADD . /app
WORKDIR /app
CMD sleep infinity
