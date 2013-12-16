
/* A dummy graphics implementation for Unix */

#if defined(X_DISPLAY_MISSING) && !defined(WITH_OPENLASE)

int pw, ph, pc, pm, pv, px, py, bg;

#ifndef HAVE_WX
char *LogoPlatformName="Unix-Nographics";

void nop()
{
}
#endif
#endif
