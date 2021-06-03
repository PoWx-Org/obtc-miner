#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit, atoi, malloc, free */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */
#define MAXLEN 1000
#define LEN 64
void error(const char *msg) { perror(msg); exit(0); }


char* pack_array(unsigned long int Array[64], char* dest){
    strncat(dest, "[", 2);
    for(int i=0; i<LEN-1; i++){
        char string[20];
        sprintf ( string, "%lu,", Array[i]);
        strncat(dest, string, 20);
    }
    char string[20];
    sprintf ( string, "%lu]", Array[LEN-1]);
    strncat(dest, string, 20);
}

char* pack_matrix(unsigned long int Matrix[64][64], char* dest){
    strncat(dest, "[", 2);
    for(int i=0; i<LEN-1; i++){
        char array_str[1000]="";
        pack_array(Matrix[i], array_str);
        strncat(dest, array_str, 1000);
        strncat(dest, ",", 2);
    }
    char array_str[1000]="";
    pack_array(Matrix[LEN-1], array_str);
    strncat(dest, array_str, 1000);
    strncat(dest, "]", 2);
}

void convertStrtoArr(char* str, unsigned long* arr)
{
    // get length of string str
    int str_length = strlen(str);
  
    // create an array with size as string
    // length and initialize with 0
  
    int j = 0, i, sum = 0;
  
    // Traverse the string
    for (i = 0; str[i] != '\0'; i++) {
        // if str[i] is ', ' then split
        if ((str[i] == ',') || (str[i] == '[') || (str[i] == ']') )
            continue;
         if ( (str[i] == ' ')  ){
            // Increment j to point to next
            // array location
            j++;
        }
        else {
  
            // subtract str[i] by 48 to convert it to int
            // Generate number by multiplying 10 and adding
            // (int)(str[i])

            arr[j] = arr[j] * 10 + (str[i] - 48);
        }
    }
}

void slice_str(const char * str, char * buffer)
{

    int index_start = strchr(str, '[') - str;
    int index_end = strchr(str, ']') - str;
    size_t j = 0;
    for ( size_t i = index_start; i <= index_end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}

void matr_uli_64x64_arr_uli_64_multiply(unsigned long int Matrix[64][64], unsigned long int Array[64], unsigned long int* result)
{
    char matrix_str[64000]="";
    pack_matrix(Matrix, matrix_str);
    char array_str[1000]="";
    pack_array(Array, array_str);

    char params[64000];
    sprintf(params, "{\"matr\":%s,\"vector\":%s}", matrix_str, array_str);
    char *args[7] = {"", "localhost", "5000", "POST", "/send_matr", params, "Content-Type: application/json"};
    int argcount=7;
    int i;
    /* first where are we going to send it? */
    int portno = atoi(args[2])>0?atoi(args[2]):80;
    char *host = strlen(args[1])>0?args[1]:"localhost";

    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total, message_size;
    char *message, response[4096];

    if (argcount < 5) { puts("Parameters: <host> <port> <method> <path> [<data> [<headers>]]"); exit(0); }

    /* How big is the message? */
    message_size=0;
    if(!strcmp(args[3],"GET"))
    {
        message_size+=strlen("%s %s%s%s HTTP/1.0\r\n");        /* method         */
        message_size+=strlen(args[3]);                         /* path           */
        message_size+=strlen(args[4]);                         /* headers        */
        if(argcount>5)
            message_size+=strlen(args[5]);                     /* query string   */
        for(i=6;i<argcount;i++)                                    /* headers        */
            message_size+=strlen(args[i])+strlen("\r\n");
        message_size+=strlen("\r\n");                          /* blank line     */
    }
    else
    {
        message_size+=strlen("%s %s HTTP/1.0\r\n");
        message_size+=strlen(args[3]);                         /* method         */
        message_size+=strlen(args[4]);                         /* path           */
        for(i=6;i<argcount;i++)                                    /* headers        */
            message_size+=strlen(args[i])+strlen("\r\n");
        if(argcount>5)
            message_size+=strlen("Content-Length: %d\r\n")+10; /* content length */
        message_size+=strlen("\r\n");                          /* blank line     */
        if(argcount>5)
            message_size+=strlen(args[5]);                     /* body           */
    }

    /* allocate space for the message */
    message=malloc(message_size);

    /* fill in the parameters */
    if(!strcmp(args[3],"GET"))
    {
        if(argcount>5)
            sprintf(message,"%s %s%s%s HTTP/1.0\r\n",
                strlen(args[3])>0?args[3]:"POST",               /* method         */
                strlen(args[4])>0?args[4]:"/",                 /* path           */
                strlen(args[5])>0?"?":"",                      /* ?              */
                strlen(args[5])>0?args[5]:"");                 /* query string   */
        else
            sprintf(message,"%s %s HTTP/1.0\r\n",
                strlen(args[3])>0?args[3]:"GET",               /* method         */
                strlen(args[4])>0?args[4]:"/");                /* path           */
        for(i=6;i<argcount;i++)                                    /* headers        */
            {strcat(message,args[i]);strcat(message,"\r\n");}
        strcat(message,"\r\n");                                /* blank line     */
    }
    else
    {
        sprintf(message,"%s %s HTTP/1.0\r\n",
            strlen(args[3])>0?args[3]:"POST",                  /* method         */
            strlen(args[4])>0?args[4]:"/");                    /* path           */
        for(i=6;i<argcount;i++)                                    /* headers        */
            {strcat(message,args[i]);strcat(message,"\r\n");}
        if(argcount>5)
            sprintf(message+strlen(message),"Content-Length: %ld\r\n",strlen(args[5]));
        strcat(message,"\r\n");                                /* blank line     */
        if(argcount>5)
            strcat(message,args[5]);                           /* body           */
    }

    /* What are we going to send? */
    //printf("Request:\n%s\n",message);

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    /* lookup the ip address */
    server = gethostbyname(host);
    if (server == NULL) error("ERROR, no such host");

    /* fill in the structure */
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

    /* connect the socket */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    /* send the request */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);

    /* receive the response */
    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd,response+received,total-received);
        if (bytes < 0)
            error("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received+=bytes;
    } while (received < total);

    if (received == total)
        error("ERROR storing complete response from socket");

    /* close the socket */
    close(sockfd);

    /* process response */
    //printf("Response:\n%s\n",response);
    char resp_massive[1000];
    slice_str(response, resp_massive);
    convertStrtoArr(resp_massive, result);


    free(message);
}
