#include <iostream>
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    while(true){
	printf("ME(Client): ");
        std::string data;
	getline(std::cin, data);
	memset(&buffer, 0, sizeof(buffer));
	strcpy(buffer, data.c_str());
	if(data == "exit"){
        	send(sock, buffer, strlen(buffer), 0 ); 
		break;
	}
        send(sock, buffer, strlen(buffer) , 0 ); 
	memset(&buffer, 0, sizeof(buffer));	
	read(sock, buffer, 1024); 
	printf("SERVER SAYS: %s\n", buffer);
	if(!strcmp(buffer, "exit")){
		std::cout << "SERVER IS OUT" << std::endl;
		break;
	}
    }
    return 0; 
} 
