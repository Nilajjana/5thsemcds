#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);
    int expected_seq = 0;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Server address configuration
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1)
    {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                         (struct sockaddr *)&client_addr, &addr_len);
        buffer[n] = '\0';

        int seq;
        char message[BUFFER_SIZE];
        sscanf(buffer, "%d %s", &seq, message);

        printf("Received packet (seq=%d): %s\n", seq, message);

        if (seq == expected_seq)
        {
            printf("Packet in order. Sending ACK %d\n", expected_seq);
            sprintf(buffer, "ACK %d", expected_seq);
            sendto(sockfd, buffer, strlen(buffer), 0,
                   (struct sockaddr *)&client_addr, addr_len);
            expected_seq = 1 - expected_seq; // Toggle sequence number
        }
        else
        {
            printf("Duplicate packet. Resending ACK %d\n", 1 - expected_seq);
            sprintf(buffer, "ACK %d", 1 - expected_seq);
            sendto(sockfd, buffer, strlen(buffer), 0,
                   (struct sockaddr *)&client_addr, addr_len);
        }
    }

    close(sockfd);
    return 0;
}