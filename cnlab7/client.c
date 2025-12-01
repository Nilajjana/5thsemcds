#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024
#define TIMEOUT 2 // seconds

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(server_addr);
    int seq = 0;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set timeout for receiving ACK
    struct timeval tv;
    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    // Server address configuration
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    while (1)
    {
        char message[BUFFER_SIZE];
        printf("Enter message (or 'exit' to quit): ");
        fgets(message, BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = '\0';

        if (strcmp(message, "exit") == 0)
            break;

        sprintf(buffer, "%d %s", seq, message);
        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&server_addr, addr_len);

        printf("Sent packet (seq=%d): %s\n", seq, message);

        // Wait for ACK
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                         (struct sockaddr *)&server_addr, &addr_len);

        if (n < 0)
        {
            printf("Timeout. Resending packet...\n");
            continue; // retransmit same packet
        }

        buffer[n] = '\0';
        int ack;
        sscanf(buffer, "ACK %d", &ack);

        if (ack == seq)
        {
            printf("Received ACK %d\n", ack);
            seq = 1 - seq; // toggle sequence number
        }
        else
        {
            printf("Incorrect ACK. Resend again\n");
        }
    }

    close(sockfd);
    return 0;
}