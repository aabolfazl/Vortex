[![Build Status](https://github.com/aabolfazl/Vortex/actions/workflows/cmake-single-platform.yml/badge.svg)](https://github.com/aabolfazl/Vortex/actions/workflows/cmake-single-platform.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![CMake](https://img.shields.io/badge/CMake-3.10-blue)](https://cmake.org/)

<img src='https://github.com/aabolfazl/Vortex/assets/33707955/ecf80e50-99de-4ec5-ae4d-47315fe04457' width='500'>

**“What I cannot create. I do not understand.”**
― **Richard Feynman**

# Vortex, Layer 4 Load Balancer using io_uring (under development 🏗️)
This project implements a high-performance Layer 4 load balancer using **modern C++**. The architecture is inspired by **NGINX** and **Envoy proxy**, designed to efficiently handle high volumes of network traffic at the transport layer (TCP/UDP). The load balancer uses a **process-per-core** model and leverages **io_uring** for event-driven I/O management, ensuring low latency and scalable performance.

## Key Features

- **IO_uring**: High-performance I/O operations using io_uring
- **Modern C++**: Written in C++17
- **Process-per-Core**: The load balancer spawns a dedicated process for each CPU core, ensuring maximum parallelism and efficient use of system resources.
- **Event Loop with io_uring**: The core of the load balancer revolves around an **io_uring**-based event loop. This allows the system to efficiently handle I/O operations (e.g., network connections, file descriptors) with minimal system calls and context switches.
- **Layer 4 Protocol Handling**: Focuses on balancing traffic at the transport layer. Currently supports TCP and UDP traffic, with plans to extend protocol support.

## Architecture

- **Worker Processes**: Each CPU core runs a separate worker process, similar to how NGINX operates. This provides better resource utilization and scales well with multi-core systems.
- **Event-Driven Design**: The event loop uses **io_uring** to queue and manage I/O operations asynchronously, significantly reducing the overhead of traditional I/O mechanisms like `epoll` or `select`.
- **Connection Handling**: Each worker process independently manages client connections and handles incoming traffic. The load balancer distributes incoming requests across available backends based on predefined algorithms (e.g., round-robin, least-connections).


## NGINX-Inspired Architecture
![image](https://github.com/user-attachments/assets/72709a58-ef41-4d9c-b3e4-b46e7fbb2ec8)

The architecture of this Layer 4 load balancer takes inspiration from the efficient design principles of NGINX. A key feature of NGINX's architecture is its worker model, which is designed to handle thousands of connections per worker with minimal resource overhead.

### Worker Model
The load balancer does not spawn a new process or thread for every incoming connection in this model. Instead, a shared listening socket is used by all workers to accept new requests. Each worker then runs a highly efficient run-loop, which manages the processing of multiple connections simultaneously within a single process. This approach eliminates the need for explicit connection distribution, as the OS kernel handles the allocation of connections to available workers.

Upon startup, a set of listening sockets is created, and each worker process continuously handles the lifecycle of a connection, including accepting, reading, processing, and writing responses. The model is designed to be asynchronous and non-blocking as much as possible, using modular event notifications and callback functions to handle tasks like I/O operations and connection management.

Non-blocking Event Loop
The core of this architecture is an event loop that uses io_uring for high-performance I/O operations. Like NGINX, the goal is to avoid blocking operations. Workers are designed to remain highly responsive, waiting for network or I/O events to occur before processing them. The event loop processes tasks asynchronously, leveraging callbacks and fine-tuned timers to handle tasks efficiently without stalling.

## future work
- **L7 htto Load Balancing**: Extend the load balancer to support Layer 7 (HTTP) load balancing, including features like URL-based routing, header-based routing, and SSL termination.
- **Dynamic Configuration**: Support dynamic configuration updates without requiring a restart of the load balancer.
- **Monitoring**: Integrate monitoring capabilities to track performance metrics and diagnose issues.
- **Traffic Routing for A/B Testing**: Implement a feature to route a certain percentage of traffic to a new version of the service for A/B testing or canary deployments.

## License

MIT
