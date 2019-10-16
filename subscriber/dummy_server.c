/**
  * This a dummy server to feed data like a real Dirt Rally game,
  * so that i do not have to start a real Dirt game which is time consuming
  */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
//input port as the second arg
{
  int i, sock, conn;
  short port;
  float telemetry[64]; //4*64=256
  int broadcastPermission = 1;
  //load port
  //sgetchar();
  sscanf(argv[1], "%d", &port);
  printf("port==%d\n", port);
  //initialize Diry Dally fake telemetries


  struct sockaddr_in saddr, baddr;

  setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission,
            sizeof(broadcastPermission));

  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = inet_addr("0.0.0.0");
  saddr.sin_port = htons(port);

  sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  //bind(sock, &saddr, sizeof(saddr));

  printf("listening\n");
  while(1)
  {
    telemetry[33]=(rand()%11)*1.f;  // gear was set to Reverse
    telemetry[7]=(rand()%200)*1.f;   // volacity 20 mps should be 72kph
    telemetry[63]=1024.f; // max RPM is 1000
    telemetry[37]=(rand()%1024)*1.f;  // current rpm is 700, yield a 70% engine
    printf("sended %f %f %f %f\n", telemetry[33], telemetry[7], telemetry[63], telemetry[37]);
    sendto(sock, telemetry, 256, 0, &saddr, sizeof(saddr));
    usleep(100000);
  }

  return 0;
}
