#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080

int main (int argc, char const *argv[]) {
    
        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        char *hello = "Ola do cliente";
        char *buffer[1024] = {0};
        
        if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
                printf("\n Erro na criacao do socket \n");
                return -1;
        }
     
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
        
        if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
                printf("\n Endereco invalido");
                return -1;
        }
        
        if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
                printf("\n Falha na conexao\n");
                return -1;
        }
        
        send(sock, hello, strlen(hello), 0);
        printf("Cliente: Mensagegem hello enviada\n");
        valread = read(sock, buffer, 1024);
        printf("%s\n", buffer);
        return 0;
}
