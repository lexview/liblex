#ifndef _PARSER_H
#define _PARSER_H

struct doc_state_t {
    unsigned char mode;        // DOC_MODE_TEXT, DOC_MODE_COMMAND, DOC_MODE_IMAGE
    unsigned char underline;   // DOC_UNDERLINE_NONE, DOC_UNDERLINE_SINGLE, DOC_UNDERLINE_DOUBLE
    unsigned char font;        // DOC_FONT_0, DOC_FONT_1, DOC_FONT_2, ...

};

#define DOC_MODE_TEXT       0x00
#define DOC_MODE_COMMAND    0x01
#define DOC_MODE_IMAGE      0x02

#define DOC_UNDERLINE_NONE      0x00
#define DOC_UNDERLINE_SINGLE    0x01
#define DOC_UNDERLINE_DOUBLE    0x02

#define DOC_FONT_0          0x00
#define DOC_FONT_1          0x01
#define DOC_FONT_2          0x02
#define DOC_FONT_3          0x03
#define DOC_FONT_4          0x04
#define DOC_FONT_5          0x05
#define DOC_FONT_6          0x06
#define DOC_FONT_7          0x07
#define DOC_FONT_8          0x08
#define DOC_FONT_9          0x09

struct doc_line_t {

};

struct parser_t {
    struct doc_state_t *doc_state;

    unsigned long line_num;

};

#define COMMAND_ESCAPE           0xFF

#define COMMAND_UNDERLINE_START  0x5F
#define COMMAND_UNDERLINE_END    0x2E

#define COMMAND_FONT_0           0x30
#define COMMAND_FONT_1           0x31
#define COMMAND_FONT_2           0x32
#define COMMAND_FONT_3           0x33
#define COMMAND_FONT_4           0x34
#define COMMAND_FONT_5           0x35
#define COMMAND_FONT_6           0x36
#define COMMAND_FONT_7           0x37
#define COMMAND_FONT_8           0x38
#define COMMAND_FONT_9           0x39


struct parser_t *parser_create(char *name);
int parser_parseline(struct parser_t *parser, unsigned char *str, size_t size);
void parser_dispose(struct parser_t *parser);

#endif /* _PARSER_H */
