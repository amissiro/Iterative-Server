//Azret Missirov
//29512170
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int sockfd;
struct sockaddr_in servaddr;
fd_set active_fd_set, read_fd_set;

void sockaddr_handler(char *host){
    bzero(&servaddr,sizeof servaddr);
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(12170);
    inet_pton(AF_INET,host,&(servaddr.sin_addr));
}

void socket_handler(){
    sockfd=socket(AF_INET,SOCK_STREAM,0);
}

void FD_handler(){
    FD_ZERO (&active_fd_set);
    FD_SET (sockfd, &active_fd_set);
    FD_SET (0, &active_fd_set);
    
}

void client_handler(char * sendline){
    int i;
    //char sendline[100];
    char recvline[100000];

    for (i = 0; i < FD_SETSIZE; ++i){
        if (FD_ISSET (i, &read_fd_set))
        {
            if (i == sockfd)
            {
                read(sockfd,recvline,100000);
                recvline[strlen(recvline)]='\0';
                printf("%s",recvline);
            }
            
            else
            {
                //bzero(sendline, 100);
                //bzero(recvline, 100);
               // fgets(sendline,100,stdin);
                write(sockfd,sendline,strlen(sendline)+1);
            }
        }
    }
}

int main(int argc,char *argv[])
{
    sockaddr_handler(argv[1]);
    socket_handler();
    FD_handler();
    
    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
 
    char ARGSSSS[160] = "";
    int k;
    for (k=2; k <argc ; k++) {
        char temp[120] = "";
        sprintf(temp, "%s ",argv[k]);
        strcat(ARGSSSS, temp);
    }
    ARGSSSS[strlen(ARGSSSS)-1] = '\0';
    printf("%s\n",ARGSSSS);
    
   // while(1)
    //{
     read_fd_set = active_fd_set;
        
//     if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0){
//            perror ("select");
//            exit (EXIT_FAILURE);
//     }
        
       client_handler(ARGSSSS);
   // }
}
