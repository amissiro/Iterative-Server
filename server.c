//Azret Missirov
//29512170
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/select.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>

#define PORT 12170

fd_set active_fd_set, read_fd_set;
int main_socket,my_accept;
char *commands[100];
struct sockaddr_in main_sockaddr;


void tokenizer(char * str)
{

    
    const char sepr[2] = " ";
    char *token = strtok(str, sepr);
    int i=2;
    
    while( token != NULL ){
        commands[i] = token;
        i++;
        token = strtok(NULL, sepr);
    }
    commands[i] = NULL;
}

int create_socket (uint16_t port)
{
    struct sockaddr_in sockaddr;
    int my_socket = socket(PF_INET, SOCK_STREAM, 0);
    
    if (my_socket < 0)
    {
        perror ("Socket Error");
        exit (EXIT_FAILURE);
    }
    
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons (port);
    sockaddr.sin_addr.s_addr = htonl (INADDR_ANY);
    
    if (bind (my_socket, (struct sockaddr *) &sockaddr, sizeof (sockaddr)) < 0)
    {
        perror ("Bind Error");
        exit (EXIT_FAILURE);
    }
    return my_socket;
}




void execute_com(int sock_fd){
    int cpid = fork();
    if (cpid==0){
    dup2(sock_fd, 0);
    dup2(sock_fd, 1);
    dup2(sock_fd, 2);
    int ret = execvp(commands[0], commands);
    }
    else if (cpid<0){
      exit(-1);
    }
    else{
      while(wait(NULL)>0);
    }
}

void clients_handler (){
    int i;
    for (i = 0; i < FD_SETSIZE; ++i){
      if (FD_ISSET (i, &read_fd_set)){
        if (i == main_socket){
         socklen_t size = sizeof (main_sockaddr);
         my_accept= accept (main_socket,(struct sockaddr *) &main_sockaddr,&size);
         FD_SET(my_accept,&active_fd_set);
        }
        else{
         char str[1000];
         read(i,str,1000);
         str[strlen(str)]='\0';
          tokenizer(str);
          execute_com(i);
       }
     }
   }
}

int main (int args, char *argv[]){
    commands[0]="ls";
    commands[1]="-l";
    printf("Server is running....\n");
    main_socket = create_socket (PORT);
    listen (main_socket, 1);

    FD_ZERO (&active_fd_set);
    FD_SET (main_socket, &active_fd_set);
    //signal(SIGPIPE,SIG_IGN);
    while (1)
    {
      read_fd_set = active_fd_set;
      select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL);
      clients_handler();
    }
    
}
