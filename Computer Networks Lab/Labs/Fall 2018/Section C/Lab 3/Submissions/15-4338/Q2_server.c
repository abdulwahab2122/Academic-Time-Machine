/*
        TCP_Server. This Program will will create the Server side for TCP_Socket Programming.
        It will receive the data from the client and then send the same data back to client.
*/

#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr

int main(void)
{
        int socket_desc, client_sock, client_size; 
        struct sockaddr_in server_addr, client_addr;
        char server_message[2000], client_message[2000];

        //Cleaning the Buffers
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Binding IP and Port to socket
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2004);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)
        {
                printf("Bind Failed. Error!!!!!\n");
                return -1;
        }        
        
        printf("Bind Done\n");
        
        //Put the socket into Listening State
        while(1){
        
        if(listen(socket_desc, 1) < 0)
        {
                printf("Listening Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Listening for Incoming Connections.....\n");
        
        //Accept the incoming Connections
        
        client_size = sizeof(client_addr);
        client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);
        
        if (client_sock < 0)
        {
                printf("Accept Failed. Error!!!!!!\n");
                return -1;
        }
        
        printf("Client Connected with IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
        
        //Receive the message from the client
        
        if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
        {
                printf("Receive Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Client sent: %s\n",client_message);
        
        //Send the message back to client
        
        
         int point = 0;
         int vowel = 0;
         int i;
         for(i = 0;i< strlen(client_message);i++){
          if(client_message[i]== 'A' || client_message[i] == 'a'|| client_message[i] == 'E' || client_message[i] == 'e'|| client_message[i] == 'I' || client_message[i] == 'i'|| client_message[i] == 'O' ||client_message[i] == 'o'|| client_message[i] == 'U' || client_message[i] == 'u')  {
              vowel++;
            }
            if((client_message[i]== ' ' || client_message[i]== '.' || client_message==',' || client_message=='\n') && vowel>=1 ){
		     char buffer[i-point + 1];
		     int k = 0;
		     int j;
		       for(j = point;j<i;j++) {
		          buffer[k] = client_message[j];
		          k++;
		       }
		       int l;
		       int s = point;
		       for(l = k-1;l>=point;l--){
		          client_message[s] = buffer[l];
		          s++;
		       }
		       point = i+1;
		       vowel = 0;
            } 
         }
    

        
        strcpy(server_message, client_message);
        
        if (send(client_sock, server_message, strlen(client_message),0)<0)
        {
                printf("Send Failed. Error!!!!!\n");
                return -1;
        }
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        }
              
        //Closing the Socket
        
        close(client_sock);
        close(socket_desc);
        return 0;       
}
