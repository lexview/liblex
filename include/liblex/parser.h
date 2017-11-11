#ifndef PARSER_H__
#define PARSER_H__

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


typedef void (* parser_cb)( struct parser_event *pe, void *userdata);

struct parser {

    uint8_t mode;        /* Parser state: DOC_MODE_TEXT, DOC_MODE_COMMAND, DOC_MODE_IMAGE                  */
    uint8_t underline;   /* Underline mark: DOC_UNDERLINE_NONE, DOC_UNDERLINE_SINGLE, DOC_UNDERLINE_DOUBLE */
    uint8_t font_id;     /* Selected font: DOC_FONT_0, DOC_FONT_1, DOC_FONT_2, ...                         */

    parser_cb cb;
    void *userdata;

};

#define RUNE_ESCAPE                0xFF
#define RUNE_COMMAND_ESCAPE        0xFF

#define RUNE_COMMAND_UNDERLINE_START  0x5F
#define RUNE_COMMAND_UNDERLINE_END    0x2E

#define RUNE_COMMAND_FONT_0           0x30
#define RUNE_COMMAND_FONT_1           0x31
#define RUNE_COMMAND_FONT_2           0x32
#define RUNE_COMMAND_FONT_3           0x33
#define RUNE_COMMAND_FONT_4           0x34
#define RUNE_COMMAND_FONT_5           0x35
#define RUNE_COMMAND_FONT_6           0x36
#define RUNE_COMMAND_FONT_7           0x37
#define RUNE_COMMAND_FONT_8           0x38
#define RUNE_COMMAND_FONT_9           0x39


int parser_create( struct parser **pp );
int parser_parse( struct parser *p, uint8_t *str, size_t size );
int parser_set_callback(struct parser *p, parser_cb cb, void *userdata);
int parser_dispose(struct parser *p);

#endif /* PARSER_H__ */
