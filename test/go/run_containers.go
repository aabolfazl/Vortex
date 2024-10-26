package main

import (
	"fmt"
	"os"
	"os/exec"
)

func main() {
	networkName := "my_net"
	subnet := "172.20.0.0/16"

	cleanup := exec.Command("docker", "rm", "-f", "$(docker ps -aq --filter name=server_)")
	if err := cleanup.Run(); err != nil {
		fmt.Println("Failed to cleanup:", err)
		return
	}

	networkCleanup := exec.Command("docker", "network", "rm", networkName)
	if err := networkCleanup.Run(); err != nil {
		fmt.Println("Failed to networkCleanup:", err)
		return
	}

	fmt.Println("Creating Docker network...")
	createNetwork := exec.Command("docker", "network", "create",
		"--driver", "bridge",
		"--opt", "com.docker.network.bridge.name=br-mynet0",
		"--subnet="+subnet,
		networkName)
	createNetwork.Stdout = os.Stdout
	createNetwork.Stderr = os.Stderr
	if err := createNetwork.Run(); err != nil {
		fmt.Println("Failed to create network:", err)
		return
	}

	for i := 1; i <= 10; i++ {
		ip := fmt.Sprintf("172.20.0.%d", i+10)
		containerName := fmt.Sprintf("server_%d", i)
		hostPort := fmt.Sprintf("%d", 8080+i-1)
		fmt.Printf("Starting container %s with IP %s on host port %s\n", containerName, ip, hostPort)

		cmd := exec.Command("docker", "run", "-d",
			"--name", containerName,
			"--net", networkName,
			"--ip", ip,
			"-p", hostPort+":8080",
			"--network-alias", containerName,
			"-e", "PORT=8080",
			"go_test_server")
		cmd.Stdout = os.Stdout
		cmd.Stderr = os.Stderr

		if err := cmd.Run(); err != nil {
			fmt.Printf("Failed to start container %s: %s\n", containerName, err)
		}
	}
	fmt.Println("All containers started.")
}
