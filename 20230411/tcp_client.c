#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define MAX_BUF_SIZE 256

int main(int argc, char *argv[])
{
    //Kiem tra dau vao
    if(argc != 3)
    {
        printf("Moi nhap dung theo mau : ./tcp_client <IP-address-server> < Port>\n");
        exit(1);
    }

    //Thiet lap thong tin dia chi cho socket
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    //Tao socket
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(client == -1)
    {
        perror("Khong tao duoc socket!\n");
        exit(1);
    }
    //Ket noi den server
    if(connect(client, (struct sockaddr*)&server_addr, sizeof(server_addr)))
    {
        perror("Khong ket noi duoc voi servre!\n");
        exit(1);
    }

    printf("Ket noi thanh cong den %s<IP-address> %s <Port>\n", argv[1], argv[2]);


    //Nhan du lieu tu ban phim
    char buf[MAX_BUF_SIZE];
    memset(buf, 0, MAX_BUF_SIZE);

    while (1)
    {
        //Nhan du lieu tu ban phim
        printf("Moi nhap du lieu: ");
        fgets(buf, MAX_BUF_SIZE, stdin);

        //Gui tin nhan den server
        if(send(client, buf, strlen(buf), 0) == -1)
        {
            perror("Gui tin nhan that bai!\n");
            exit(1);
        }

        //Kiem tra co nhap lenh thoat khong
        if(strcmp(buf, "exit\n") == 0)
        {
            exit(1);
        }
    }
    close(client);

}