#include <stdio.h>
#include <string.h>

#include "parser.h"


int main()
{
  int rc;
  struct parser_t *parser;

  // Create reader
  parser = parser_create("name?");

  // Parse single line
  unsigned char *str = "Hello, \xFF\x5Fworld\xFF\x2E!";
  rc = parser_parseline(parser, str, strlen(str));

  // Dispose reader
  parser_dispose(parser);

  return 0;
}