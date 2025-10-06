#include <stdio.h>

void instrLogger(const char *opName, const char *useName) {
  printf("%s <- %s\n", opName, useName);
}