#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "parser_event.h"


void parse_callback(int event, void *data)
{
    if (event == PARSER_EVENT_CHAR) {
        fprintf(stderr, "event = CHAR, data = %c\n", *((char *)data));
    } else
    if (event == PARSER_EVENT_FONT) {
        fprintf(stderr, "event = FONT, data = %d\n", *((int *)data));
    } else {
        fprintf(stderr, "event = UNKNOWN\n");
    }
}


int main()
{
  int rc;
  struct parser_t *parser;

  // Create reader
  parser = parser_create("parser_1");
  parser_set_callback(parser, parse_callback);

  // Parse single line
  unsigned char *str = "\xFF\x30Hello, \xFF\x5Fworld\xFF\x2E!";
  rc = parser_parseline(parser, str, strlen(str));

  // Dispose reader
  parser_dispose(parser);

  return 0;
}