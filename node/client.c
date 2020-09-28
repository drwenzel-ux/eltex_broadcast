#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void die(const char *m) {
  perror(m);
  exit(1);
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

  r = recvfrom(fd, buf, 13, 0, (struct sockaddr *)&addr, &size);
  printf("%s\n", buf);

  close(fd);
  return 0;
}
