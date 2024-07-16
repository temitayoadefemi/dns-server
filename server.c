#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#define PORT 53
#define BUFFER_SIZE 512


void handle_dns_request(int socket_fd) {
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);
    unsigned char buffer[BUFFER_SIZE];

    int received_bytes = recvfrom(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_address, &client_address_len);
    if (received_bytes < 0) {
        perror("Failed to receive data");
        return;
    }

    printf("Received DNS query\n");

    buffer[2] |= 0x80;
    buffer[3] |= 0x80; 

    if (sendto(socket_fd, buffer, received_bytes, 0, (struct sockaddr *)&client_address, client_address_len) < 0) {
        perror("Failed to send response");
    }

    printf("Sent DNS response\n");
}

