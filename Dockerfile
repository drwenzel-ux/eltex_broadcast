FROM alpine:latest

RUN apk update && apk add bash alpine-sdk net-tools
RUN mkdir -p /root/node

WORKDIR /root/node

COPY ./node .

CMD make client && ./client && make clean
