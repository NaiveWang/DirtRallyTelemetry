/**
 * This c demo receives UDP signal from Dirt game
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void)
{
  int i, sock;
  short port;

  float buff[64];
  struct sockaddr_in host;

  host.sin_family = AF_INET;
  host.sin_addr.s_addr = htonl(INADDR_ANY);
  host.sin_port = htons(20777);

  sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

  bind(sock, &host, sizeof(host));

  while(1)
  {
    i = recvfrom(sock, buff, 256, 0, &host, NULL);

    printf("%f %f %f %f\n", buff[33], buff[7], buff[63], buff[37]);
    //do process here
  }
  close(sock);

  return 0;
}
