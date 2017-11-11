#ifndef PARSER_EVENT_H__
#define PARSER_EVENT_H__


#define EVENT_RUNE             0x01
#define EVENT_FONT             0x02
#define EVENT_UNDERLINE_START  0x03
#define EVENT_UNDERLINE_END    0x04
#define EVENT_ERROR            0xFF

struct parser_event {
    uint8_t event;
    uint8_t rune;
    uint8_t font_id;
};


#endif /* PARSER_EVENT_H__ */