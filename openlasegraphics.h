/*
 * ucblogo OpenLase graphics implementation
 * Copyright 2013 Kamal Mostafa <kamal@whence.com>, GPL-2+
 */

#include "logo.h"


extern void openlase_render(void);


#define OpenLase_scale	500


// FIXME: we're not actually using logo's record buffer
#define GR_SIZE 60000

#define prepare_to_draw openlase_prepare_to_draw()
#define done_drawing openlase_done_drawing()

#define prepare_to_draw_turtle  nop()
#define done_drawing_turtle  nop()

#if 1
#define screen_left	(-OpenLase_scale)
#define screen_right	(+OpenLase_scale)
#define screen_top	(-OpenLase_scale)
#define screen_bottom	(+OpenLase_scale)
#else
#define screen_left	(0)
#define screen_right	(OpenLase_scale*2)
#define screen_top	(0)
#define screen_bottom	(OpenLase_scale*2)
#endif

#define screen_height (1 + screen_bottom - screen_top)
#define screen_width (1 + screen_right - screen_left)

#define screen_x_center (screen_left + (screen_width)/2)
#define screen_y_center (screen_top + (screen_height)/2)

#define turtle_left_max ((screen_left) - (screen_x_center))
#define turtle_right_max ((screen_right) - (screen_x_center))
#define turtle_top_max ((screen_y_center) - (screen_top))
#define turtle_bottom_max ((screen_y_center) - (screen_bottom))

#define screen_x_coord ((screen_x_center) + turtle_x)
#define screen_y_coord ((screen_y_center) - turtle_y)

#define turtle_height 30
#define turtle_half_bottom 10.0
#define turtle_side 33.0

extern void openlase_clear(void);
extern void openlase_set_pen_vis(int v);
extern void openlase_line_to(FLONUM x, FLONUM y);
extern void openlase_move_to(FLONUM x, FLONUM y);


#define clear_screen	openlase_clear()		// IMPLEMENTED
#define line_to		openlase_line_to		// IMPLEMENTED
#define move_to		openlase_move_to		// IMPLEMENTED
#define set_pen_vis	openlase_set_pen_vis		// IMPLEMENTED

#define draw_string(s) nop()
#define set_pen_mode(m) nop()
#define set_pen_color(c) nop()
#define set_pen_width(w) nop()
#define set_pen_height(h) nop()
#define set_pen_x(x) nop()
#define set_pen_y(y) nop()
#define set_back_ground(c) nop()

/* pen_info is a stucture type with fields for the various
   pen characteristics including the location, size, color,
   mode (e.g. XOR or COPY), pattern, visibility (0 = visible) */

typedef struct { int dummy; } pen_info;

#define p_info_x(p) p.dummy
#define p_info_y(p) p.dummy

#define pen_width pw
#define pen_height ph
#define pen_color pc
#define pen_mode pm
#define pen_vis pv
#define pen_x px
#define pen_y py
#define get_node_pen_pattern make_intnode(0)
#define back_ground bg

#define pen_reverse nop()
#define pen_erase nop()
#define pen_down nop()

#define button FALSE
#define mouse_x 0
#define mouse_y 0

#define full_screen nop()
#define split_screen nop()
#define text_screen nop()

#define save_pen(p) nop()
#define restore_pen(p) nop()
#define plain_xor_pen() nop()
#define label(s) nop()
#define tone(p,d) nop()
#define get_pen_pattern(p) nop()
#define set_pen_pattern(p) nop()
#define fmod(x,y) x
#define set_list_pen_pattern(p) nop()

extern int pw, ph, pc, pm, pv, px, py, bg;
extern void nop();

#define logofill nop
#define set_palette nop
#define get_palette nop
#define erase_screen nop
