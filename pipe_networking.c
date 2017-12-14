#include "pipe_networking.h"

/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  //c to s upstream
  //s to c downstream
  //wkp is upstream
  /*char line[256];
  printf("Enter text : ");
  fgets(line, sizeof(line), stdin);*/
  //printf("%s\n",line);
  char * path = "wkp";
  mkfifo(path,0644);
  int up = open(path, O_WRONLY);
  /*write(up, line , sizeof(line));
    close(up);*/
  //to client is downstream
  int down=(&to_client, O_RDONLY);
  /*int value;
  read(down, &value, sizeof(int));
  close(down);*/
  to_client =&down;
  
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
  //private is downstream
  char line[256];
  printf("Enter text : ");
  fgets(line, sizeof(line), stdin);
  //printf("%s\n", line);
  char * path = "private";
  mkfifo(path,0644);
  int down = open(path, O_WRONLY);
  write(down, line, sizeof(int));
  close(down);
  int up=(&to_server, O_RDONLY);
  /*int value;
  read(up, &value, sizeof(int));
  close(up);*/
  to_server = &up;
  return down;
}
