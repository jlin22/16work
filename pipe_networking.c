#include "pipe_networking.h"

/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {

  mkfifo("wkp",0600);
  int up = open("wkp", O_RDONLY, 0600);
  printf("well known pipe created\n");
  char line[HANDSHAKE_BUFFER_SIZE];
  read(up, line, HANDSHAKE_BUFFER_SIZE);
  printf("server received : %s\n", line);
  remove("wkp");

  int down = open(line, O_WRONLY);
  *to_client = down;
  write(down, ACK, strlen(ACK));
  printf("server sent : %s\n", ACK); 
  read(up, line, HANDSHAKE_BUFFER_SIZE);
  printf("server handshake complete\n");
  
  return up;
}


/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int up = open("wkp", O_WRONLY, 0600);
  char line[HANDSHAKE_BUFFER_SIZE];
  sprintf(line, "%d", getpid());
  char pipe[HANDSHAKE_BUFFER_SIZE];
  strcpy(pipe,line);
  mkfifo(line, 0600);
  write(up, line, HANDSHAKE_BUFFER_SIZE);
  int down = open(line, O_RDONLY, 0600);
  read(down, line, HANDSHAKE_BUFFER_SIZE);
  printf("client receive : %s\n",line);
  remove("pipe");
  write(up, ACK, HANDSHAKE_BUFFER_SIZE);
  *to_server = up;
  return down;
}
