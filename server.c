#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void die(const char *m) {
  perror(m);
  exit(1);
}

int main(int argc, char const *argv[]) {
  int fd, v;
  ssize_t s;
  struct sockaddr_in sa_in;

  fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd == -1)
    die("socket() return -1");

  v = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &v, sizeof(v)) == -1)
    die("setsockopt() return -1");

  sa_in.sin_family = AF_INET;
  sa_in.sin_port = htons(3000);
  sa_in.sin_addr.s_addr = inet_addr("172.17.255.255");

  s = sendto(fd, "hello world", 13, 0, (struct sockaddr *)&sa_in,
             sizeof(sa_in));

  close(fd);
  return 0;
}
