
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "liblex.h"


int parser_create( struct parser **pp )
{
    struct parser *p = NULL;
    int err = 0;

    p = (struct parser *)malloc(sizeof(struct parser));
    if ( !p ) {
        err = ENOMEM;
        goto out;
    }

    p->cb = NULL;
    p->userdata = NULL;

  out:

    if ( err ) {
        parser_dispose( p );
    } else {
        *pp = p;
    }

    return err;
}


int parser_set_callback(struct parser *p, parser_cb cb, void *userdata)
{
    int err = 0;

    if ( !p ) {
        err = EINVAL;
        goto out;
    }

    p->cb = cb;
    p->userdata = userdata;

  out:

    return err;
}


static void process_process_text( struct parser *p, uint8_t rune )
{
    struct parser_event pe;

    if ( rune == RUNE_ESCAPE ) {
        p->mode = DOC_MODE_COMMAND;
    } else {
        if ( p->cb ) {

            pe.event = EVENT_RUNE;
            pe.rune = rune;

            p->cb( &pe, p->userdata );
        }
    }
}


struct font_map {
    uint8_t rune;
    uint8_t font_id;
};


static struct font_map font_map[] = {
    { RUNE_COMMAND_FONT_0, DOC_FONT_0 },
    { RUNE_COMMAND_FONT_1, DOC_FONT_1 },
    { RUNE_COMMAND_FONT_2, DOC_FONT_2 },
    { RUNE_COMMAND_FONT_3, DOC_FONT_3 },
    { RUNE_COMMAND_FONT_4, DOC_FONT_4 },
    { RUNE_COMMAND_FONT_5, DOC_FONT_5 },
    { RUNE_COMMAND_FONT_6, DOC_FONT_6 },
    { RUNE_COMMAND_FONT_7, DOC_FONT_7 },
    { RUNE_COMMAND_FONT_8, DOC_FONT_8 },
    { RUNE_COMMAND_FONT_9, DOC_FONT_9 },

    { 0, 0 }
};


static void process_process_command( struct parser *p, uint8_t rune )
{
    struct parser_event pe;

    switch ( rune ) {

        case RUNE_COMMAND_ESCAPE:
            p->mode = DOC_MODE_TEXT;

            pe.event = EVENT_RUNE;
            pe.rune = rune;

            if ( p->cb ) {
                p->cb( &pe, p->userdata );
            }

            break;

        case RUNE_COMMAND_UNDERLINE_START:
            p->underline = DOC_UNDERLINE_SINGLE;
            p->mode = DOC_MODE_TEXT;
            break;

        case RUNE_COMMAND_UNDERLINE_END:
            p->underline = DOC_UNDERLINE_NONE;
            p->mode = DOC_MODE_TEXT;
            break;

        case RUNE_COMMAND_FONT_0:
        case RUNE_COMMAND_FONT_1:
        case RUNE_COMMAND_FONT_2:
        case RUNE_COMMAND_FONT_3:
        case RUNE_COMMAND_FONT_4:
        case RUNE_COMMAND_FONT_5:
        case RUNE_COMMAND_FONT_6:
        case RUNE_COMMAND_FONT_7:
        case RUNE_COMMAND_FONT_8:
        case RUNE_COMMAND_FONT_9:

            for (int i=0; i < sizeof(font_map) ; ++i) {
                struct font_map *fm = &font_map[i];
                if ( rune == fm->rune ) {
                    p->font_id = fm->font_id;
                }
            }

            p->mode = DOC_MODE_TEXT;

            if ( p->cb ) {
                pe.event = EVENT_FONT;
                pe.font_id = p->font_id;

                p->cb( &pe, p->userdata );
            }

            break;

        default:

            if ( p->cb ) {
                pe.event = EVENT_ERROR;

                p->cb( &pe, p->userdata );
            }

            break;
    }
}


/**
 * Parse line
 *
 * parseline(self, str, size)
 *
 * @return code
 */
int parser_parse(struct parser *p, uint8_t *str, size_t size)
{
    int err = 0;
    uint8_t rune;
    int i;

    for(i=0; i < size; ++i) {
        rune = (uint8_t)str[i];

        switch ( p->mode ) {

            case DOC_MODE_TEXT:
                process_process_text( p, rune );
                break;

            case DOC_MODE_COMMAND:
                process_process_command( p, rune );
                break;

        }
    }

    return 0;
}



int parser_dispose( struct parser *p )
{
    int err = 0;

    if ( !p ) {
        err = EINVAL;
        goto out;
    }

    free( p );

  out:

    return err;
}
