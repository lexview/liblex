
#include <stdio.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "liblex.h"


#define ROW_SIZE 512


void parse_callback( struct parser_event *pe, void *userdata )
{
    switch ( pe->event ) {

        case EVENT_RUNE:
            fprintf( stdout, "debug: event = RUNE, data = %c\n", pe->rune );
            break;

        case EVENT_FONT:
            fprintf( stdout, "debug: event = FONT, data = %d\n", pe->font_id );
            break;

        case EVENT_ERROR:
            fprintf( stdout, "debug: event = ERROR\n" );
            break;

        default:
            fprintf( stdout, "debug: event = UNKNOWN\n" );
    }
}


int main()
{
    int err = 0;
    struct parser *p;
    struct parser_event pe;
    int fd;
    uint8_t row[ROW_SIZE];
    ssize_t size;

    /* Create new parser */
    err = parser_create( &p );
    if ( err ) {
        fprintf( stderr, "error: Unable to create parser\n" );
        goto out;
    }

    fd = open("example.lex", O_RDONLY);
    if ( fd == -1 ) {
        fprintf( stderr, "error: Unable to open stream\n" );
        goto out;
    }

    err = parser_set_callback( p, parse_callback, NULL );
    if ( err ) {
        fprintf( stderr, "error: Unable to setup callback\n" );
        goto out;
    }

    for ( ;; ) {

        /* Read */
        size = read( fd, row, ROW_SIZE );
        if ( size == 0 ) {
            goto out;
        }
        if ( size == -1 ) { /* Some error when reading */
            fprintf( stderr, "error: Unable to read bytes\n" );
            goto out;
        }

        /* Parse */
        err = parser_parse( p, row, size );
        if ( err ) {
            fprintf(stderr, "error: Unable to parsing row\n");
            goto out;
        }

    }

  out:

    /* Close stream */
    if ( fd != -1 ) {
        close( fd );
    }

    /* Dispose reader */
    parser_dispose( p );

    return err;
}
