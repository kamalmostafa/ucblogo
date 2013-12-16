/*
 * ucblogo OpenLase graphics implementation
 * Copyright 2013 Kamal Mostafa <kamal@whence.com>, GPL-2+
 */

#ifdef WITH_OPENLASE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <libol.h>

#include "openlasegraphics.h"

#include "globals.h"

extern BOOLEAN user_turtle_shown;
extern int drawToPrinter;


// 0: render on each wait or prompt
// 1: render on every motion
int openlase_render_every_motion = 0;

int pw, ph, pc, pm, pv, px, py, bg;
int px = -999999;
int py = -999999;


#define MAXVERTS 60000
struct vertex {
    	int	beginflag;
    	FLONUM	x;
    	FLONUM	y;
} Verts[MAXVERTS];
int nVerts;

int in_object = 0;

FLONUM cur_x, cur_y;


char *LogoPlatformName="OpenLaseGraphics";

void nop()
{
}


static int
openlase_init()
{
    static int initialized = 0;
    if ( initialized )
	return 0;
    initialized = 1;

    // set up OpenLase
    OLRenderParams params;
    memset(&params, 0, sizeof params);
    params.rate = 48000;
    params.on_speed = 1.5/100.0;
    params.off_speed = 4.0/100.0;
    params.start_wait = 16;
    params.start_dwell = 10;			// helps slow turn-on
    params.curve_dwell = 0;
    params.corner_dwell = 16;
    params.curve_angle = cosf(20.0*(M_PI/180.0)); // 20 deg
    params.end_dwell = 10;
    params.end_wait = 15;			// helps slow turn-off
    params.snap = 1/100000.0;
    params.render_flags = RENDER_GRAYSCALE;
    params.render_flags |= RENDER_NOREORDER;
//    params.render_flags |= RENDER_NOREVERSE;
//    params.render_flags |= RENDER_KEEPOBJECTS;	// render does not clear
//    params.flatness = 0.0000001;		// for default font
    if(olInit(2, 30000) < 0) {
	    fprintf(stderr, "OpenLase init failed\n");
	    exit(1);
    }
    olSetRenderParams(&params);

    return 0;
}


static void
olLogoVertex( FLONUM x, FLONUM y )
{
    float olx =  x / (float)OpenLase_scale;
    float oly = -y / (float)OpenLase_scale;
    olVertex(olx, oly, C_WHITE);
}


void
openlase_render()
{
//    fprintf(stderr, "+ %s()   nVerts=%d\n", __FUNCTION__, nVerts);

#if 0
    // not valid -- breaks "cs ht"
    if ( nVerts == 0 && !user_turtle_shown )
	return;
#endif
    openlase_init();

    olLoadIdentity3();
    olLoadIdentity();

    // draw the lines
    if ( nVerts > 0 ) {
	olBegin(OL_LINESTRIP);
	int i;
	for ( i=0; i<nVerts; i++ ) {
	    struct vertex *v = &Verts[i];
	    if ( v->beginflag && i > 0 ) {
		olEnd();
		olBegin(OL_LINESTRIP);
	    }
	    olLogoVertex(v->x, v->y);
	}
	olEnd();
    }

    // draw the turtle
    if ( user_turtle_shown ) {
	olPushMatrix();
	olTranslate(turtle_x/OpenLase_scale, turtle_y/OpenLase_scale);
	float deg = turtle_heading + 180;
	olRotate(deg * M_PI / 180);
	olBegin(OL_LINESTRIP);

#if 1
	FLONUM x = turtle_half_bottom;
	FLONUM y = turtle_half_bottom / 2;
	olLogoVertex(-x, -y);
	olLogoVertex(0, turtle_height);
	olLogoVertex(+x, -y);
	olLogoVertex(-x, -y);
#else
	olLogoVertex(-10, -3);
	olLogoVertex(0, +27);
	olLogoVertex(+10, -3);
	olLogoVertex(-10, -3);
#endif
	olEnd();
	olPopMatrix();
    }

    olRenderFrame(120);
}


void
openlase_prepare_to_draw()
{
    //fprintf(stderr, "+ %s\n", __FUNCTION__);

    // This should happen even earlier, I think . . .
    // Disable ucblogo's XOR-based turtle rendering
    drawToPrinter = 1;
}


void
openlase_done_drawing()
{
    //fprintf(stderr, "+ %s\n", __FUNCTION__);

    if ( openlase_render_every_motion )
	openlase_render();
}


static void
add_vert(FLONUM x, FLONUM y, int beginflag)
{
    //fprintf(stderr, "+ *** VERT (%.3lf, %.3lf) begin=%d\n", x, y, beginflag);

    if ( nVerts == MAXVERTS )
	return;
    Verts[nVerts].beginflag = beginflag;
    Verts[nVerts].x = x;
    Verts[nVerts].y = y;
    nVerts++;
}


void
openlase_move_to( FLONUM x, FLONUM y )
{
    //fprintf(stderr, "+  pv=%3d  %s(%.3lf, %.3lf)\n", pv, __FUNCTION__, x, y);

    if ( cur_x == x && cur_y == y )
	return;

    in_object = 0;

    cur_x = x;
    cur_y = y;
}


void
openlase_line_to( FLONUM x, FLONUM y )
{
    //fprintf(stderr, "+  pv=%3d  %s(%.3lf, %.3lf)\n", pv, __FUNCTION__, x, y);

    if ( pv == -1 )
	return;

    if ( ! in_object ) {
	add_vert(cur_x, cur_y, 1);
	in_object = 1;
    }

    add_vert(x, y, 0);
    cur_x = x;
    cur_y = y;
}


void
openlase_clear()
{
//    fprintf(stderr, "+ %s()\n", __FUNCTION__);
    nVerts = 0;
    in_object = 0;
}


void
openlase_set_pen_vis(int v)
{
    //fprintf(stderr, "+ %s(%d)\n", __FUNCTION__, v);
    pv = v;
}

#endif
