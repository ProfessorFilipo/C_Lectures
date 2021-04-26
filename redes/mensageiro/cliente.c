// http://www.binarytides.com/winsock-socket-programming-tutorial/
/*
    Create a TCP socket
*/

// código usa funcções obsoletas. utilize esse pragma para compilação no VS2019
#pragma warning(suppress : 4996)

#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc, char* argv[])
{

    char* hostname = "localhost";
    char ip[100];
    struct hostent* he;
    struct in_addr** addr_list;
    int i;

    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char* message, server_reply[2000];
    int recv_size;

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

    if ((he = gethostbyname(hostname)) == NULL)
    {
        //gethostbyname failed
        printf("gethostbyname failed : %d", WSAGetLastError());
        return 1;
    }

    //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
    addr_list = (struct in_addr**) he->h_addr_list;

    for (i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip, inet_ntoa(*addr_list[i]));
    }

    printf("%s resolved to : %s\n", hostname, ip);


    //Create a socket
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    printf("Socket created.\n");


    server.sin_addr.s_addr = inet_addr(ip); //inet_addr("191.6.202.80");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    //Connect to remote server
    if (connect(s, (struct sockaddr*) & server, sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected");

    //Send some data
    message = "GET / HTTP/1.1\r\n\r\n";
    if (send(s, message, strlen(message), 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");

    //Receive a reply from the server
    if ((recv_size = recv(s, server_reply, 2000, 0)) == SOCKET_ERROR)
    {
        puts("recv failed");
    }

    puts("Reply received\n");

    //Add a NULL terminating character to make it a proper string before printing
    server_reply[recv_size] = '\0';
    puts(server_reply);

    return 0;
}
