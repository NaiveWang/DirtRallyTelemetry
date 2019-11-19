/**
  * This a dummy server to feed data like a real Dirt Rally game,
  * so that i do not have to start a real Dirt game which is time consuming
  */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

const short default_port=20777;
char* default_host="0.0.0.0";
const int default_delay=1000;//1000ms

int main(int argc, char **argv)
//input port as the second arg
{
  int i, sock, conn;
  short port;
  char* host;
  int delay;
  float telemetry[64]; //4*64=256
  int broadcastPermission = 1;
  //load port
  //sgetchar();
  if(argc == 4)
  {
    host = argv[1];
    sscanf(argv[2], "%d", &port);
    sscanf(argv[3], "%d", &delay);
  }
  else
  {
    host = default_host;
    port = default_port;
    delay = default_delay;
  }

  printf("host:port==%s:%d broadcast per %dms\n", host, port, delay);
  //initialize Diry Dally fake telemetries
  delay*=1000;

  struct sockaddr_in saddr, baddr;

  setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission,
            sizeof(broadcastPermission));

  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = inet_addr(host);
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
    usleep(delay);
  }

  return 0;
}
