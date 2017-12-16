#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );
  while(1){
    char msg[BUFFER_SIZE];
    read(from_client, msg, 256);
    int i;
    /*for (i=0; i<strlen(msg)-1;i++){
      msg[i] = msg[i] - 32;
      }*/
    write(to_client, msg, BUFFER_SIZE);
  }
}
