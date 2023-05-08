#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define MAX_BUF_SIZE 256

int main(int argc, char *argv[])
{
    //Kiem tra dau vao
    if(argc != 4)
    {
        printf("Moi nhap theo dung mau ./tcp_server <Port><File chua cau chao> <File ghi nd gui tu client>\n");
        exit(1);
    }

    //Tao socket
    int server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( server == -1)
    {
        perror("Ko tao duoc socket!\n");
        exit(1);
    }

    //Thiet lap thong tin dia chi cho socket
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

    //Gan dia chi cho socket
    if(bind(server, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind() failed!\n");
        exit(1);
    }

    //Doi ket noi tu client
    if(listen(server, 10)== -1)
    {
        perror("Loi\n");
        exit(1);
    }

    while (1)
    {
        printf("Waiting a new client.....\n");

        //Chap nhan ket noi tu client
        struct sockaddr_in client_addr;
        int client = accept(server, (struct sockaddr*)&client_addr, sizeof(client_addr));
        if(client == -1)
        {
            perror("Ket noi that bai!\n");
            exit(1);
        }
        
        printf("ket noi thanh cong!\n");

    }
    


}