set(VORTEX_EVENT_MODULE
    event/io_uring_core_impl.cpp
    event/io_uring_core_impl.h
)

set(VORTEX_CONFIG
    core/config/types.h
    core/config/config_manager.cpp
    core/config/config_manager.h
    core/config/parser_interface.h
    core/config/yaml_parser.cpp
    core/config/yaml_parser.h
)

set(VORTEX_COMMON
    common/traits.h
    common/address.h
    common/address.cpp
    common/sys_calls_impl.cpp
    common/sys_calls_impl.h
    common/platform.h
    common/error_helper.h
)

set(VORTEX_BALANCER
    core/balancer/cluster_manager_impl.h
    core/balancer/cluster_manager_impl.cpp
    core/balancer/cluster_impl.h
    core/balancer/cluster_impl.cpp
    core/balancer/backend_impl.h
    core/balancer/backend_impl.cpp
)


set(VORTEX_TCP_CONNECTION_POOL
    core/net/connection_factory_impl.h
    core/net/connection_factory_impl.cpp
    core/net/tcp_conn_pool_impl.h
    core/net/tcp_conn_pool_impl.cpp
    core/net/client_connection_impl.h
    core/net/client_connection_impl.cpp
)


set(VORTEX_LISTENER
    core/listener/listener_manager.h
)

set(VORTEX_CORE
    core/service_node_impl.h
    core/service_node_impl.cpp
    core/components_factory_impl.h
    core/components_factory_impl.cpp
    core/logger/logger.h
    core/io/socket_io_handle_impl.cpp
    core/io/socket_io_handle_impl.h
    core/io/io_uring_dispacher_impl.cpp
    core/io/io_uring_dispacher_impl.h
)

add_library(vortex STATIC
    ${VORTEX_EVENT_MODULE}
    ${VORTEX_CONFIG}
    ${VORTEX_COMMON}
    ${VORTEX_CORE}
    ${VORTEX_TCP_CONNECTION_POOL}
    ${VORTEX_LISTENER}
    ${VORTEX_BALANCER}
)

target_include_directories(vortex
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${URING_INCLUDE_DIRS}
)

target_link_libraries(vortex
    PUBLIC
        fmt::fmt
        yaml-cpp
    PRIVATE
        ${URING_LIBRARIES}
)