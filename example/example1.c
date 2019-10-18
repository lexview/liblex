
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "liblex.h"


#define ROW_SIZE 512


void parse_callback( struct parser_event *pe, void *userdata )
{
    if ( pe->event == EVENT_RUNE )
    {
        fprintf( stdout, "debug: event = RUNE, data = %c\n", pe->rune );
    }
    else if ( pe->event == EVENT_FONT )
    {
        fprintf( stdout, "debug: event = FONT, data = %d\n", pe->font_id );
    }
    else if ( pe->event == EVENT_ERROR )
    {
        fprintf( stdout, "debug: event = ERROR\n" );
    }
    else
    {
        fprintf( stdout, "debug: event = UNKNOWN\n" );
    }
}

int parse(struct parser *p, int fd)
{
    uint8_t mem[ROW_SIZE];
    ssize_t size;
    int err;

    bool running = true;
    while ( running )
    {

        /* Read */
        size = read( fd, mem, ROW_SIZE );

        if ( size > 0 )
        {
            /* Parse */
            err = parser_parse( p, mem, size );
            if ( err != 0 )
            {
                fprintf(stderr, "error: Unable to parsing row\n");
                return err;
            }
        }
        else if ( size == 0 )
        {
            /* No more - EOF */
            return 0;
        }
        else if ( size == -1 )
        {
            /* Some error when reading */
            fprintf(stderr, "error: Unable to read bytes\n");
            return 1;
        }

    }

    return 0;
}

int parse_file(struct parser *p, char *filename)
{
    int err;
    int fd;

    /* Open stream */
    fd = open( filename, O_RDONLY );
    if ( fd == -1 )
    {
        fprintf( stderr, "error: Unable to open stream\n" );
        return 1;
    }

    /* Main process */
    err = parse( p, fd );
    if ( err != 0 )
    {
        (void)close( fd );
        fprintf(stderr, "error: Unable parse Lexicon document\n");
        return 1;
    }

    /* Close stream */
    (void)close( fd );

    return 0;
}

int main(int argc, char *argv[])
{
    int err;
    struct parser *p;
    struct parser_event pe;


    /* Check parameters */
    if ( argc != 2 )
    {
        fprintf(stdout, "Usage: parser [lexicon-file]\n");
        exit(1);
    }

    /* Create new parser */
    err = parser_create( &p );
    if ( err != 0 ) {
        fprintf(stderr, "error: Unable to create Lexicon parser\n");
        exit(1);
    }

    /* Set callback */
    err = parser_set_callback( p, parse_callback, NULL );
    if ( err != 0 )
    {
        fprintf(stderr, "error: Unable to set Lexicon parser callback\n");
        exit(1);
    }

    /* Parse file */
    err = parse_file( p, argv[1] );
    if ( err != 0 )
    {
        fprintf(stderr, "error: Unable to parse Lexicon docuemnt\n");
        exit(1);
    }

    /* Release parser */
    parser_dispose( p );

    return 0;
}
