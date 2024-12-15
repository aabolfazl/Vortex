FROM golang:1.21-alpine

WORKDIR /app
COPY tcp_server.go .

RUN go build -o tcpserver tcp_server.go

CMD ["./tcpserver"]