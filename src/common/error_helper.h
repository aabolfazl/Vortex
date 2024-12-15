#pragma once

#include <errno.h>
#include <string_view>
#include <sys/socket.h>


namespace vortex::common {

inline std::string_view get_socket_error_string(int error_code) {
    switch (error_code) {
    case ECONNRESET:
        return std::string_view{"Connection reset by peer"};
    case ECONNREFUSED:
        return std::string_view{"Connection refused"};
    case ECONNABORTED:
        return std::string_view{"Connection aborted"};
    case ENOTCONN:
        return std::string_view{"Socket not connected"};
    case ETIMEDOUT:
        return std::string_view{"Connection timed out"};

    case ENETDOWN:
        return std::string_view{"Network is down"};
    case ENETUNREACH:
        return std::string_view{"Network unreachable"};
    case ENETRESET:
        return std::string_view{"Network dropped connection on reset"};
    case EHOSTUNREACH:
        return std::string_view{"No route to host"};
    case EHOSTDOWN:
        return std::string_view{"Host is down"};

    case EPIPE:
        return std::string_view{"Broken pipe"};
    case ESHUTDOWN:
        return std::string_view{"Cannot send after socket shutdown"};
    case EBADF:
        return std::string_view{"Bad file descriptor"};
    case ENOTSOCK:
        return std::string_view{"Not a socket"};

    case EADDRINUSE:
        return std::string_view{"Address already in use"};
    case EADDRNOTAVAIL:
        return std::string_view{"Address not available"};
    case EAFNOSUPPORT:
        return std::string_view{"Address family not supported"};

    case EINVAL:
        return std::string_view{"Invalid argument"};
    case EINTR:
        return std::string_view{"Interrupted system call"};
    case EMSGSIZE:
        return std::string_view{"Message too long"};
    case ENOBUFS:
        return std::string_view{"No buffer space available"};
    case ENOMEM:
        return std::string_view{"Out of memory"};
    case EAGAIN:
        return std::string_view{"Resource temporarily unavailable"};

    default:
        return std::string_view{"Unknown socket error"};
    }
}

inline std::string_view get_socket_error(int result) {
    if (result >= 0) {
        return std::string_view{"Not an error"};
    }
    return get_socket_error_string(-result);
}

} // namespace vortex::common
