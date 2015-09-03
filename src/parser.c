#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"


void parser_debug(int event, void *data) {
}


struct parser_t *
parser_create(char *name) {
    struct parser_t *parser;
    struct doc_state_t *doc_state;

    parser = (struct parser_t *)malloc(sizeof(struct parser_t));
    if (parser != NULL) {
        doc_state = (struct doc_state_t *)malloc(sizeof(struct doc_state_t));
        if (doc_state != NULL) {
            // Initialize DOC_STATE struct
            doc_state->mode = DOC_MODE_TEXT;
            doc_state->underline = DOC_UNDERLINE_NONE;
            doc_state->font = DOC_FONT_0;

            parser->doc_state = doc_state;
        }    

        parser->cb = parser_debug;
        parser->line_num = 0;
    }

    return parser;
}

void
parser_dispose(struct parser_t *parser) {
    if (parser != NULL) {
        if (parser->doc_state != NULL) {
            free(parser->doc_state);
        }
        free(parser);
    }
}


void parser_set_callback(struct parser_t *parser, parser_cb_t cb) {
    parser->cb = cb;
}

/**
 * Parse line
 *
 * parseline(self, str, size)
 *
 * @return code
 */
int parser_parseline(struct parser_t *parser, unsigned char *str, size_t size)
{
    struct doc_state_t *doc_state = parser->doc_state;

    unsigned char ch;
    int i;
                        
    // Starting parse
    for(i=0; i < size; ++i) {
        ch = str[i];  // ch = (unsigned char)*(str + i);

        if (doc_state->mode == DOC_MODE_TEXT) {
            if (ch == COMMAND_ESCAPE) {
                doc_state->mode = DOC_MODE_COMMAND;
            } else {
                //
                parser->cb(1, (void *)&ch);
            }
        } else
        if (doc_state->mode == DOC_MODE_COMMAND) {
            if (ch == COMMAND_UNDERLINE_START) {
                doc_state->underline = DOC_UNDERLINE_SINGLE;
                doc_state->mode = DOC_MODE_TEXT;
            } else
            if (ch == COMMAND_UNDERLINE_END) {
                doc_state->underline = DOC_UNDERLINE_NONE;
                doc_state->mode = DOC_MODE_TEXT;
            } else
            if (ch == COMMAND_FONT_0) {
                doc_state->font = DOC_FONT_0;
                doc_state->mode = DOC_MODE_TEXT;
                //
                parser->cb(2, (void *)&doc_state->font);
            } else
            if (ch == COMMAND_FONT_1) {
                doc_state->font = DOC_FONT_1;
                doc_state->mode = DOC_MODE_TEXT;
                //
                parser->cb(2, (void *)&doc_state->font);
            } else
            if (ch == COMMAND_FONT_2) {
                doc_state->font = DOC_FONT_2;
                doc_state->mode = DOC_MODE_TEXT;
                //
                parser->cb(2, (void *)&doc_state->font);
            } else
            if (ch == COMMAND_FONT_3) {
                doc_state->font = DOC_FONT_3;
                doc_state->mode = DOC_MODE_TEXT;
                //
                parser->cb(2, (void *)&doc_state->font);
            } else
            if (ch == COMMAND_FONT_4) {
                doc_state->font = DOC_FONT_4;
                doc_state->mode = DOC_MODE_TEXT;
                //
                parser->cb(2, (void *)&doc_state->font);
            } else
            if (ch == COMMAND_FONT_5) {
                doc_state->font = DOC_FONT_5;
                doc_state->mode = DOC_MODE_TEXT;
                //
                parser->cb(2, (void *)&doc_state->font);
            } else
            if (ch == COMMAND_FONT_6) {
                doc_state->font = DOC_FONT_6;
                doc_state->mode = DOC_MODE_TEXT;
                //
                parser->cb(2, (void *)&doc_state->font);
            } else
            if (ch == COMMAND_FONT_7) {
                doc_state->font = DOC_FONT_7;
                doc_state->mode = DOC_MODE_TEXT;
                //
                parser->cb(2, (void *)&doc_state->font);
            } else
            if (ch == COMMAND_FONT_8) {
                doc_state->font = DOC_FONT_8;
                doc_state->mode = DOC_MODE_TEXT;
                //
                parser->cb(2, (void *)&doc_state->font);
            } else
            if (ch == COMMAND_FONT_9) {
                doc_state->font = DOC_FONT_9;
                doc_state->mode = DOC_MODE_TEXT;
                //
                parser->cb(2, (void *)&doc_state->font);
            } else
            if (ch == COMMAND_ESCAPE) {
                fprintf(stdout, "char: %c", ch);
                doc_state->mode = DOC_MODE_TEXT;
                //
                parser->cb(1, (void *)&ch);
            } else {
                fprintf(stderr, "error: unknown command.");
            }
        } else {
            fprintf(stderr, "error: unknown document state.");
        }
    }

    return 0;
}
