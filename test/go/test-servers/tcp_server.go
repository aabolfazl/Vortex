package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"time"
)

func handleConnection(conn net.Conn) {
	defer conn.Close()

	clientAddr := conn.RemoteAddr().String()
	log.Printf("New TCP connection from %s at %s", clientAddr, time.Now().Format(time.RFC3339))

	scanner := bufio.NewScanner(conn)
	for scanner.Scan() {
		message := scanner.Text()
		log.Printf("Received from %s: %s", clientAddr, message)

		// Echo the message back to the client
		_, err := conn.Write([]byte(fmt.Sprintf("Echo: %s\n", message)))
		if err != nil {
			log.Printf("Failed to send response to %s: %v", clientAddr, err)
			return
		}
	}

	if err := scanner.Err(); err != nil {
		log.Printf("Error reading from connection %s: %v", clientAddr, err)
	}

	log.Printf("Connection from %s closed at %s", clientAddr, time.Now().Format(time.RFC3339))
}

func startTCPServer(port int) {
	log.Printf("Starting TCP server on port %d", port)
	listener, err := net.Listen("tcp", fmt.Sprintf(":%d", port))
	if err != nil {
		log.Fatalf("Failed to start TCP server on port %d: %v", port, err)
	}
	defer listener.Close()

	log.Printf("TCP server listening on port %d", port)

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Printf("Failed to accept connection on port %d: %v", port, err)
			continue
		}

		go handleConnection(conn) // Handle each connection concurrently
	}
}

func main() {
	fmt.Println("Starting 10 TCP servers...")
	basePort := 8080
	numServers := 10

	// Start multiple servers
	for i := 0; i < numServers; i++ {
		port := basePort + i
		go startTCPServer(port)
	}

	// Block main goroutine to keep servers running
	select {}
}
