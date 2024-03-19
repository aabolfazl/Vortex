FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    git \
    openssh-server \
    rsync \
    sudo

RUN useradd -m abolfazl && echo "abolfazl:abolfazl" | chpasswd && adduser abolfazl sudo

RUN mkdir -p /home/abolfazl/.ssh && \
    chmod 700 /home/abolfazl/.ssh && \
    chown abolfazl:abolfazl /home/abolfazl/.ssh

RUN mkdir /var/run/sshd
RUN echo 'root:root' | chpasswd
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config
EXPOSE 22

EXPOSE 8080

CMD ["/usr/sbin/sshd", "-D"]
