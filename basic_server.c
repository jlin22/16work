#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );
  while(1){
    char msg[BUFFER_SIZE];
    read(from_client, msg, BUFFER_SIZE);
      msg[0] = msg[0] - 32;
    write(to_client, msg, BUFFER_SIZE);
  }
}
