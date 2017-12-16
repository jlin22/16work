#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  while(1){
    char msg[BUFFER_SIZE];
    printf("enter text in lowercase: ");
    fgets(msg, BUFFER_SIZE, stdin);
    //printf("%s", msg);
    write(to_server, msg, BUFFER_SIZE);
    read(from_server, msg, BUFFER_SIZE);
    printf("recieve new text : %s \n", msg);
  }
}
