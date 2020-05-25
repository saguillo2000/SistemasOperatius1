#include <stdio.h>
#include <string.h>

#define SIZE 100

int main(void)
{
  int len;
  int hh, mm, ss;
  char buffer[SIZE];

  ss = 23;
  mm = 9;
  hh = 0;

  sprintf(buffer, "%02d:%02d:%02d\n", hh, mm, ss);

  len = strlen(buffer);
  write(1, buffer, len);

  return 0;
}
