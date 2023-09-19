#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX 1000

int main() {
    int clientDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    char buffer[MAX], message[MAX];
    struct sockaddr_in cliaddr, serverAddress;
    socklen_t serverLength = sizeof(serverAddress);

    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(9976);

    bind(clientDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    while (1) {
        printf("\nCOMMAND FOR EXECUTION ... ");
        fgets(buffer, sizeof(buffer), stdin);
        sendto(clientDescriptor, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddress, serverLength);
        printf("\nData Sent !");
        recvfrom(clientDescriptor, message, sizeof(message), 0, (struct sockaddr *)&serverAddress, &serverLength);
        printf("UDP SERVER : %s\n", message);
    }
    return 0;
}

