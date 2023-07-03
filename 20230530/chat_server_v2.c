#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(9000);

    int server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(server < 0)
    {
        perror("socket() failed!\n");
        return 1;
    }

    if(bind(server, (struct sockaddr*)&server_addr, sizeof(server_addr) < 0))
    {
        perror("bind() failed!\n");
        return 1;
    }

    if(listen(server, 10)< 0)
    {
        perror("listen() failed!\n");
        return 1;
    }

    printf("Waiting a new client....\n");

    fd_set fdread, fdtest;
    FD_ZERO(&fdread);
    FD_SET(server, &fdread);

    char buf[256]; 
    int users[64];//Mang socket client da dang nhap
    char *user_id[64];//Mang luu tru id cua client da dang nhap
    int num_users = 0;//so luong client da dang nhap

    while (1)
    {
        fdtest = fdread;

        int ret = select(FD_SETSIZE, &fdtest, NULL, NULL, NULL);

        if(ret < 0)
        {
            perror("select() failed!\n");
            break;
        }

        for(int i = 0; i< FD_SETSIZE; i++)
        {
            if(FD_ISSET(i, &fdtest))
            {
                if (i == server)
                {
                    //chap nhan ket noi
                    int client = accept(server, NULL, NULL);
                    if(client < FD_SETSIZE)
                    {
                        printf("New client connected: %d\n", client);
                        FD_SET(client, &fdread);
                    }
                    else
                    {
                        printf("Too many connetions\n");
                        close(client);
                    }
                }
                else
                {

                    //Nhan du lieu
                    int ret = recv(i, buf, sizeof(buf), 0);
                    if(ret <= 0)
                    {
                        printf("client %d disconnected.\n", i);
                        close(i);
                        FD_CLR(i, &fdread);
                    }
                    else
                    {
                        buf[ret] =0;
                        printf("Recieved from %d: %s", i, buf);

                        //Kiem tra trang thai dang nhap cua client
                        int client = i;

                        int j =0;
                        for(; j< num_users; j++)
                        {
                            if (users[i] == client)
                            {
                                break;
                            }
                            
                        }
                    }
                    
                }
                
                
                
            }
        }
    }
    

}