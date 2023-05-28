#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <termios.h>
#include <termios.h>
#include <fcntl.h>
 //include<iostream>
#include<stdio.h>                // printf
#include<string.h>                // strlen
//<string>                // string
#include<sys/socket.h>            // socket
#include<arpa/inet.h>            // inet_addr
#include<netdb.h>                // hostenta
#include <unistd.h>
//include<iostream>
#include<sys/socket.h>            // socket
#include<arpa/inet.h>            // inet_addr

struct sockaddr_in server;

   int port = 80;

/*telnet*/
#define IAC 255
#define CMD 0xff
#define DONT 0xfe
#define DO 0xfd
#define WONT 0xfc
#define WILL 0xfb
#define SB 0xfa
#define GA 0xf9
#define EL 0xf8
#define EC 0xf7
#define AYT 0xf6
#define AO 0xf5
#define IP 0xf4
#define BREAK 0xf3
#define SYNCH 0xf2
#define NOP 0xf1
#define SE 0xf0
#define EOR     0xef
#define ABORT 0xee
#define SUSP 0xed
#define xEOF 0xec
/*ftp*/
#define PRELIM 1
#define COMPLETE 2
#define CONTINUE 3
#define TRANSIENT 4
#define ERROR 5
#define RRQ 01
#define WRQ 02
#define DATA 03
#define ACK 04
#define REC_ESC '\377'
#define REC_EOR '\001'
#define REC_EOF '\002'
#define BLK_EOR 0x80
#define BLK_EOF 0x40
#define BLK_ERRORS 0x20
#define BLK_RESTART 0x10 
/* SSH*/
#define SSH_CMD_IAC   255
#define SSH_CMD_CMD   0xff
#define SSH_CMD_DONT  0xfe
#define SSH_CMD_DO    0xfd
#define SSH_CMD_WONT  0xfc
#define SSH_CMD_WILL  0xfb
#define SSH_CMD_SB    0xfa
#define SSH_CMD_GA    0xf9
#define SSH_CMD_EL    0xf8
#define SSH_CMD_EC    0xf7
#define SSH_CMD_AYT   0xf6
#define SSH_CMD_AO    0xf5
#define SSH_CMD_IP    0xf4
#define SSH_CMD_BREAK 0xf3
#define SSH_CMD_SYNCH 0xf2
#define SSH_CMD_NOP   0xf1
#define SSH_CMD_SE    0xf0
#define SSH_CMD_EOR   0xef
#define SSH_CMD_ABORT 0xee
#define SSH_CMD_SUSP  0xed
#define SSH_CMD_EOF   0xec

char *message = {"OPTIONS / HTTP/1.1\r\nHost: exemple.com\r\n\r\n"};

 int nready;
 int maxfd;
  
 int sock;
char buffer[1024];
char head[50]="HEAD / HTTP/1.1\r\n\r\nHost:gov.ua\r\n\r\n";
char option[25]="OPTIONS / HTTP/1.1\r\n";
char xd;
    int bytes_received;
//int numBytesRecv=1;

#define BUFLEN 20
int len;

 unsigned char buf[BUFLEN + 1];

static struct termios tin;

int help(){
printf("-h help\r\n");
printf("-p post\r\n");
printf("-t telnet\r\n");
printf("-<3 heartbled\r\n");
return 0;
}
/*
int hostname_to_ip(char * hostname , char* ip)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
        
    if ( (he = gethostbyname( hostname ) ) == NULL)
    {
        // get the host info
        herror("gethostbyname");
        return 1;
    }

    addr_list = (struct in_addr **) he->h_addr_list;
    
    for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;
    }
    
    return 1;
}

*/


int hostname_to_ip(int argc, char *argv) {
    if (argc < 2) {
        fprintf(stderr, "Hostname not provided\n");
        return 0;
    }

    char *hostname = argv;
   
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
        
    if ( (he = gethostbyname( hostname ) ) == NULL)
    {
        // get the host info
        herror("gethostbyname");
        return 1;
    }

    addr_list = (struct in_addr **) he->h_addr_list;
    
    for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(argv, inet_ntoa(*addr_list[i]) );
        return 0;
    }
    
    return 1;
}

int telnet (int argc, char*argv[]){
char *hostname;
    char ip[100];

   hostname = argv[2];

hostname_to_ip(argc , ip);

sock = socket(AF_INET, SOCK_STREAM, 0);

server.sin_family = AF_INET;
    
          
       server.sin_addr.s_addr = inet_addr(ip);   
    

   
        port = atoi(argv[3]);
    
           printf("%s resolved to %s" , hostname , ip);
 server.sin_port = htons(port);
     connect(sock, (struct sockaddr *)&server, sizeof(server));        
             struct timeval ts;
    ts.tv_sec = 1; // 1 second
    ts.tv_usec = 0;
    ssize_t numBytesRecv = 0;
      char replyMessage[5500];
         char *replyMessage2[5200];

//sprintf(buffer,head,"host:",argv[1]);
sprintf(buffer, "GET /start.php HTTP/1.1\r\nHost: www.gov.ua\r\n\r\n");

    //(sprintf)(buffer, "HEAD / HTTP/1.1\r\nHost: %s\r\n\r\n", ip); //

//snprintf(buffer, sizeof(buffer), "HEAD / HTTP/1.1\r\nHost: %s \r\n\r\n", ip);

 FILE *fp;
  if ((fp=fopen("test2.html", "w"))==NULL) {
    printf ("can't open file to write\n");
    exit(1); };
  ///  ########################    ///
    
    printf("port is: %d\n", port);
    printf("host ip is %s\n", argv[2]);
    printf("enter the , exemple:/index.aspx\n");

      while(1){
            fd_set fds;
  /* Set up polling. */
 FD_ZERO(&fds);
        if (sock != 0)
            FD_SET(sock, &fds);
        FD_SET(0, &fds);

        // wait for data
        int nready = select(sock + 1, &fds, (fd_set *) 0, (fd_set *) 0, &ts);
        if (nready < 0) {
            perror("select. Error");
            return 1;
        }
        else if (nready == 0) {
            ts.tv_sec = 1; // 1 second
            ts.tv_usec = 0;
        }
        else if (sock != 0 && FD_ISSET(sock, &fds)) {
            // start by reading a single byte
            int rv;
            if ((rv = recv(sock , buf , 1 , 0)) < 0){
      
                return 1;}
            else if (rv == 0) {
        
                printf("Connection closed by the remote end\n\r");
                return 0;
            }

            if (buf[0] == CMD) {
                // read 2 more bytes
                len = recv(sock , buf + 1 , 2 , 0);
            
                if (len  < 0){
    
                    return 1;}
                else if (len == 0) {
          
                    printf("Connection closed by the remote end\n\r");
                    return 0;
                }
                //negotiate(sock, buf, 3);
            }
            else {
                len = 1;
                buf[len] = '\0';
                printf("%s", buf);
                   fprintf(fp,"%s", buf);
                fflush(0);
           //     tcflush(sock, 0);
      
            }
        }
        
        else if (FD_ISSET(0, &fds)) {
            buf[0] = getc(stdin); //fgets(buf, 1, stdin);
            if (send(sock, buf, 1, 0) < 0)
                return 1;
            if (buf[0] == '\n') // with the terminal in raw mode we need to force a LF
                putchar('\r');
        }
    
 } 
    
     
  
    printf("save in test2.html file\n");
       fclose (fp);   
     }



int menu(int argc, char *argv[]) {
    if (argc <1) {
        printf("Usage: %s host port\n", argv[0]);
        return 1;
    }

    char *option = argv[1];

    switch (option[0]) {
        case '-':
            switch (option[1]) {
                case 'h':
                    printf("Help\n");
                    help();
                    break;
                case 'p':
                    printf("post\n");
                    //post();
                    break;
                case 'g':
                    printf("ip\n");
                    break;
                case 't':
                    printf("Telnet\n");

        telnet(argc, argv);

                    break;
                default:
                 printf("Invalidoption\n");
                    break;
            }
            break;
        default:
            printf("Invalid option\n");
            break;
    }
    return 0;
}
int main(int argc, char *argv[])
{ 
menu(argc,argv);
return 0;
}
