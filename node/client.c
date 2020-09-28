#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void die(const char *m) {
  perror(m);
  exit(1);
}

void socket_print(int fd) {
  struct sockaddr_in sa;
  socklen_t size = sizeof(sa);
  char inet_addr[INET_ADDRSTRLEN];

  if (getsockname(fd, (struct sockaddr *)&sa, &size) == -1)
    die("getsockname failed");

  inet_ntop(AF_INET, &sa.sin_addr.s_addr, inet_addr, size);
  printf("%s:%d\n", inet_addr, htons(sa.sin_port));
}

int main(int argc, char const *argv[]) {
  int fd;
  char buf[16];
  struct sockaddr_in addr;
  socklen_t size;
  ssize_t r;

  fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd == -1)
    die("socket() return -1");

  addr.sin_family = AF_INET;
  addr.sin_port = htons(3000);
  addr.sin_addr.s_addr = inet_addr("172.17.255.255");

  size = sizeof(struct sockaddr_in);
  if (bind(fd, (struct sockaddr *)&addr, size) == -1)
    die("bind failed");

  socket_print(fd);

  r = recvfrom(fd, buf, 13, 0, (struct sockaddr *)&addr, &size);
  printf("%s\n", buf);

  close(fd);
  return 0;
}
