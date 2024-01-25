FROM ubuntu:23.04

RUN apt-get update
RUN apt-get install -y g++

RUN apt-get install -y libjsoncpp-dev
RUN apt-get install -y libboost-dev
RUN apt-get install -y wget
RUN wget https://github.com/CrowCpp/Crow/releases/download/v1.0%2B5/crow-v1.0+5.deb
RUN apt install -y ./crow-v1.0+h.deb

COPY . /app

WORKDIR /app

RUN rm -rf /var/lib/apt/lists/*
RUN rm -rf /root/.cache

WORKDIR /app

CMD ["./run.sh", "app"]