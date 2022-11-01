#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
 
void des_cl(int c) {
  // deservirea clientului
  uint16_t a, b, suma, text;
  recv(c, &a, sizeof(a), MSG_WAITALL);
  recv(c, &b, sizeof(b), MSG_WAITALL);
  a = ntohs(a);
  b = ntohs(b);
  suma = 12;
  suma = htons(suma);
  send(c, &suma, sizeof(suma), 0);
  close(c);
}
 
int main() {
  int s;
  struct sockaddr_in server, client;
  int c, l;
  char text[] = "start joc", str2[] = "start joc";

  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  
  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }
 
  listen(s, 5);
  
  l = sizeof(client);
  memset(&client, 0, sizeof(client));

  while (1) {
    c = accept(s, (struct sockaddr *) &client, &l);
    printf("S-a conectat un client. Scrie start joc\n");
    if (fork() == 0) { // fiu
      printf("Astept sa dai start joc.\n");
      scanf("%c", text);
      //send(c, text, strlen(text), 0);
      if(strcmp(text,str2) == 0){
        des_cl(c);
      }
      return 0;
    }
  }
}