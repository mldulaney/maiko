/* $Id: xwinman.c,v 1.3 2001/12/26 22:17:07 sybalsky Exp $ (C) Copyright Venue, All Rights Reserved
 */

/************************************************************************/
/*									*/
/*	(C) Copyright 1989, 1990, 1990, 1991, 1992, 1993, 1994, 2000 Venue.	*/
/*	    All Rights Reserved.		*/
/*	Manufactured in the United States of America.			*/
/*									*/
/************************************************************************/

#include "version.h"

#include <X11/X.h>         // for Button1, Cursor, ButtonPress, Button2, But...
#include <X11/Xlib.h>      // for XEvent, XMoveResizeWindow, XAnyEvent, XBut...
#include <stdio.h>         // for printf
#include <sys/types.h>     // for u_char
#include "devif.h"         // for (anonymous), MRegion, DefineCursor, OUTER_...
#include "keyeventdefs.h"  // for kb_trans
#include "lispemul.h"      // for PUTBASEBIT68K, FALSE, TRUE, DLword, state
#include "lspglob.h"       // for MiscStats
#include "xdefs.h"         // for XLOCK, XUNLOCK
#include "xlspwindefs.h"   // for DoRing
#include "xscrolldefs.h"   // for JumpScrollHor, JumpScrollVer, Scroll, Scro...
#include "xwinmandefs.h"   // for Set_BitGravity, beep_Xkeyboard, dis...

extern int Mouse_Included;
int Mouse_Included = FALSE;

extern Cursor WaitCursor, DefaultCursor, VertScrollCursor, VertThumbCursor, ScrollUpCursor,
    ScrollDownCursor, HorizScrollCursor, HorizThumbCursor, ScrollLeftCursor, ScrollRightCursor;
extern int noscroll;
extern DspInterface currentdsp;

extern DLword *EmCursorX68K, *EmCursorY68K;
extern DLword *EmMouseX68K, *EmMouseY68K, *EmKbdAd068K, *EmRealUtilin68K;
extern LispPTR *CLastUserActionCell68k;
extern int KBDEventFlg;
extern u_char *SUNLispKeyMap;
#define KEYCODE_OFFSET 7 /* Sun Keycode offset */

/* bits within the EmRealUtilin word */
#define KEYSET_LEFT 8
#define KEYSET_LEFTMIDDLE 9
#define KEYSET_MIDDLE  10
#define KEYSET_RIGHTMIDDLE 11
#define KEYSET_RIGHT 12
/* Mouse buttons */
#define MOUSE_LEFT 13
#define MOUSE_RIGHT 14
#define MOUSE_MIDDLE 15

/* ubound: return (unsigned) value if it is between lower and upper otherwise lower or upper */
static inline unsigned ubound(unsigned lower, unsigned value, unsigned upper)
{
  if (value <= lower)
    return (lower);
  else if (value >= upper)
    return (upper);
  else
    return (value);
}

void Set_BitGravity(XButtonEvent *event, DspInterface dsp, Window window, int grav)
{
  Window OldWindow = 0;

  /* Change Background Pixmap of Gravity Window */
  XLOCK;
  switch (dsp->BitGravity) {
    case NorthWestGravity: OldWindow = dsp->NWGrav; break;
    case NorthEastGravity: OldWindow = dsp->NEGrav; break;
    case SouthWestGravity: OldWindow = dsp->SWGrav; break;
    case SouthEastGravity: OldWindow = dsp->SEGrav; break;
  }

  dsp->BitGravity = grav;

  XSetWindowBackgroundPixmap(event->display, OldWindow, dsp->GravityOffPixmap);
  XClearWindow(event->display, OldWindow);

  XSetWindowBackgroundPixmap(event->display, window, dsp->GravityOnPixmap);
  XClearWindow(event->display, window);
  XUNLOCK(dsp);
} /* end Set_BitGravity */

static void lisp_Xconfigure(DspInterface dsp, int x, int y, unsigned lspWinWidth, unsigned lspWinHeight)
{
  int Col2, Row2, Col3, Row3;
  unsigned int GravSize;

  /* The Visible width and height changes when */
  /* we configure the window. Make them */
  /* stay within bounds. */
  dsp->Visible.width =
      ubound(OUTER_SB_WIDTH(dsp) + 2, lspWinWidth, dsp->Display.width + OUTER_SB_WIDTH(dsp)) -
      OUTER_SB_WIDTH(dsp);
  dsp->Visible.height =
      ubound(OUTER_SB_WIDTH(dsp) + 2, lspWinHeight, dsp->Display.height + OUTER_SB_WIDTH(dsp)) -
      OUTER_SB_WIDTH(dsp);

  GravSize = (dsp->ScrollBarWidth / 2) - (dsp->InternalBorderWidth);
  Col2 = (int)dsp->Visible.width;
  Row2 = (int)dsp->Visible.height;
  Col3 = (int)(dsp->Visible.width + (OUTER_SB_WIDTH(dsp) / 2));
  Row3 = (int)(dsp->Visible.height + (OUTER_SB_WIDTH(dsp) / 2));

  XLOCK;
  XMoveResizeWindow(dsp->display_id, dsp->DisplayWindow, 0, 0, dsp->Visible.width,
                    dsp->Visible.height);
  if (noscroll == 0) {
    /* Scroll bars */
    XMoveResizeWindow(dsp->display_id, dsp->VerScrollBar, Col2, 0 - (int)dsp->InternalBorderWidth, /* y */
                      dsp->ScrollBarWidth,   /* width */
                      dsp->Visible.height); /* height */
    XMoveResizeWindow(dsp->display_id, dsp->HorScrollBar, 0 - (int)dsp->InternalBorderWidth, Row2, /* y */
                      dsp->Visible.width,  /* width */
                      dsp->ScrollBarWidth); /* height */

    /* Scroll buttons */
    XMoveResizeWindow(
                      dsp->display_id, dsp->HorScrollButton,
                      (dsp->Visible.x * (int)dsp->Visible.width) / (int)dsp->Display.width,         /* x */
                      0 - (int)dsp->InternalBorderWidth,                                                /* y */
                      ((dsp->Visible.width * dsp->Visible.width) / dsp->Display.width) + 1, /* width */
                      dsp->ScrollBarWidth);                                                        /* height */
    XMoveResizeWindow(
                      dsp->display_id, dsp->VerScrollButton, 0 - (int)dsp->InternalBorderWidth,             /* x */
                      (dsp->Visible.y * (int)dsp->Visible.height) / (int)dsp->Display.height,           /* y */
                      dsp->ScrollBarWidth,                                                             /* width */
                      ((dsp->Visible.height * dsp->Visible.height) / dsp->Display.height) + 1); /* height */

    /* Gravity windows */
    XMoveResizeWindow(dsp->display_id, dsp->NWGrav, Col2, Row2, GravSize, GravSize);
    XMoveResizeWindow(dsp->display_id, dsp->NEGrav, Col3, Row2, GravSize, GravSize);
    XMoveResizeWindow(dsp->display_id, dsp->SEGrav, Col3, Row3, GravSize, GravSize);
    XMoveResizeWindow(dsp->display_id, dsp->SWGrav, Col2, Row3, GravSize, GravSize);
    Scroll(dsp, dsp->Visible.x, dsp->Visible.y);
  }
  XFlush(dsp->display_id);
  XUNLOCK(dsp);
} /* end lisp_Xconfigure */

void enable_Xkeyboard(DspInterface dsp)
{
  XLOCK;
  XSelectInput(dsp->display_id, dsp->DisplayWindow, dsp->EnableEventMask);
  XFlush(dsp->display_id);
  XUNLOCK(dsp);
}

void disable_Xkeyboard(DspInterface dsp)
{
  XLOCK;
  XSelectInput(dsp->display_id, dsp->DisplayWindow, dsp->DisableEventMask);
  XFlush(dsp->display_id);
  XUNLOCK(dsp);
}

void beep_Xkeyboard(DspInterface dsp)
{
#ifdef TRACE
  printf("TRACE: beep_Xkeyboard()\n");
#endif

  XLOCK;
  XBell(dsp->display_id, (int)50);
  XFlush(dsp->display_id);
  XUNLOCK(dsp);

} /* end beep_Xkeyboard */

/************************************************************************/
/*									*/
/*		    p r o c e s s _ X e v e n t s			*/
/*									*/
/*  Take X key/mouse events and turn them into Lisp events		*/
/*									*/
/************************************************************************/

extern int Current_Hot_X, Current_Hot_Y; /* Cursor hotspot */

void process_Xevents(DspInterface dsp)
{
  XEvent report;

  while (XPending(dsp->display_id)) {
    XNextEvent(dsp->display_id, &report);
    if (report.xany.window == dsp->DisplayWindow) /* Try the most important window first. */
      switch (report.type) {
        case MotionNotify:
          *CLastUserActionCell68k = MiscStats->secondstmp;
          *EmCursorX68K = (*((DLword *)EmMouseX68K)) =
              (short)((report.xmotion.x + dsp->Visible.x) & 0xFFFF) - Current_Hot_X;
          *EmCursorY68K = (*((DLword *)EmMouseY68K)) =
              (short)((report.xmotion.y + dsp->Visible.y) & 0xFFFF) - Current_Hot_Y;
          break;
        case KeyPress:
          kb_trans(SUNLispKeyMap[(report.xkey.keycode) - KEYCODE_OFFSET], FALSE);
          DoRing();
          if ((KBDEventFlg += 1) > 0) Irq_Stk_End = Irq_Stk_Check = 0;
          break;
        case KeyRelease:
          kb_trans(SUNLispKeyMap[(report.xkey.keycode) - KEYCODE_OFFSET], TRUE);
          DoRing();
          if ((KBDEventFlg += 1) > 0) Irq_Stk_End = Irq_Stk_Check = 0;
          break;
        case ButtonPress:
          switch (report.xbutton.button) {
            case Button1: PUTBASEBIT68K(EmRealUtilin68K, MOUSE_LEFT, FALSE); break;
            case Button2: PUTBASEBIT68K(EmRealUtilin68K, MOUSE_MIDDLE, FALSE); break;
            case Button3: PUTBASEBIT68K(EmRealUtilin68K, MOUSE_RIGHT, FALSE); break;
            case Button4: PUTBASEBIT68K(EmRealUtilin68K, KEYSET_LEFT, FALSE); break;
            case Button5: PUTBASEBIT68K(EmRealUtilin68K, KEYSET_LEFTMIDDLE, FALSE); break;
            case Button5 + 1: PUTBASEBIT68K(EmRealUtilin68K, KEYSET_RIGHT, FALSE); break;
            case Button5 + 2: PUTBASEBIT68K(EmRealUtilin68K, KEYSET_RIGHTMIDDLE, FALSE); break;
            default: break;
          }
          DoRing();
          if ((KBDEventFlg += 1) > 0) Irq_Stk_End = Irq_Stk_Check = 0;
          break;
        case ButtonRelease:
          switch (report.xbutton.button) {
            case Button1: PUTBASEBIT68K(EmRealUtilin68K, MOUSE_LEFT, TRUE); break;
            case Button2: PUTBASEBIT68K(EmRealUtilin68K, MOUSE_MIDDLE, TRUE); break;
            case Button3: PUTBASEBIT68K(EmRealUtilin68K, MOUSE_RIGHT, TRUE); break;
            case Button4: PUTBASEBIT68K(EmRealUtilin68K, KEYSET_LEFT, TRUE); break;
            case Button5: PUTBASEBIT68K(EmRealUtilin68K, KEYSET_LEFTMIDDLE, TRUE); break;
            case Button5 + 1: PUTBASEBIT68K(EmRealUtilin68K, KEYSET_RIGHT, TRUE); break;
            case Button5 + 2: PUTBASEBIT68K(EmRealUtilin68K, KEYSET_RIGHTMIDDLE, TRUE); break;
            default: break;
          }
          DoRing();
          if ((KBDEventFlg += 1) > 0) Irq_Stk_End = Irq_Stk_Check = 0;
          break;
        case EnterNotify: Mouse_Included = TRUE; break;
        case LeaveNotify: Mouse_Included = FALSE; break;
        case Expose:
          (dsp->bitblt_to_screen)(dsp, 0, report.xexpose.x + dsp->Visible.x,
                                  report.xexpose.y + dsp->Visible.y, report.xexpose.width,
                                  report.xexpose.height);
          break;
        default: break;
      }
    else if (report.xany.window == dsp->LispWindow)
      switch (report.xany.type) {
        case ConfigureNotify:
          lisp_Xconfigure(dsp, report.xconfigure.x, report.xconfigure.y, (unsigned)report.xconfigure.width,
                          (unsigned)report.xconfigure.height);
          break;
        case EnterNotify: enable_Xkeyboard(currentdsp); break;
        case LeaveNotify: break;
        case MapNotify:
          /* Turn the blitting to the screen on */
          break;
        case UnmapNotify:
          /* Turn the blitting to the screen off */
          break;
        default: break;
      }
    else if (noscroll) continue;
    else if (report.xany.window == dsp->HorScrollBar)
      switch (report.type) {
        case ButtonPress:
          switch (report.xbutton.button) {
            case Button1:
              DefineCursor(dsp, dsp->HorScrollBar, &ScrollLeftCursor);
              ScrollLeft(dsp);
              break;
            case Button2:
              DefineCursor(dsp, dsp->HorScrollBar, &HorizThumbCursor);
              break;
            case Button3:
              DefineCursor(dsp, dsp->HorScrollBar, &ScrollRightCursor);
              ScrollRight(dsp);
              break;
            default: break;
          } /* end switch */
          break;
        case ButtonRelease:
          switch (report.xbutton.button) {
            case Button1:
              DefineCursor(dsp, report.xany.window, &HorizScrollCursor);
              break;
            case Button2:
              JumpScrollHor(dsp, report.xbutton.x);
              DefineCursor(dsp, report.xany.window, &HorizScrollCursor);
              break;
            case Button3:
              DefineCursor(dsp, report.xany.window, &HorizScrollCursor);
              break;
            default: break;
          } /* end switch */
	  break;
        default: break;
      }
    else if (report.xany.window == dsp->VerScrollBar)
      switch (report.type) {
        case ButtonPress:
          switch (report.xbutton.button) {
            case Button1:
              DefineCursor(dsp, report.xany.window, &ScrollUpCursor);
              ScrollUp(dsp);
              break;
            case Button2:
              DefineCursor(dsp, report.xany.window, &VertThumbCursor);
              break;
            case Button3:
              DefineCursor(dsp, report.xany.window, &ScrollDownCursor);
              ScrollDown(dsp);
              break;
            default: break;
          } /* end switch */
          break;
        case ButtonRelease:
          switch (report.xbutton.button) {
            case Button1:
              DefineCursor(dsp, report.xany.window, &VertScrollCursor);
              break;
            case Button3:
              DefineCursor(dsp, report.xany.window, &VertScrollCursor);
              break;
            case Button2:
              JumpScrollVer(dsp, report.xbutton.y);
              DefineCursor(dsp, report.xany.window, &VertScrollCursor);
              break;
            default: break;
          } /* end switch */
          break;
        default: break;
      }
    else if ((report.xany.window == dsp->NEGrav) && (report.xany.type == ButtonPress) &&
             ((report.xbutton.button & 0xFF) == Button1))
      Set_BitGravity(&report.xbutton, dsp, dsp->NEGrav, NorthEastGravity);
    else if ((report.xany.window == dsp->SEGrav) && (report.xany.type == ButtonPress) &&
             ((report.xbutton.button & 0xFF) == Button1))
      Set_BitGravity(&report.xbutton, dsp, dsp->SEGrav, SouthEastGravity);
    else if ((report.xany.window == dsp->SWGrav) && (report.xany.type == ButtonPress) &&
             ((report.xbutton.button & 0xFF) == Button1))
      Set_BitGravity(&report.xbutton, dsp, dsp->SWGrav, SouthWestGravity);
    else if ((report.xany.window == dsp->NWGrav) && (report.xany.type == ButtonPress) &&
             ((report.xbutton.button & 0xFF) == Button1))
      Set_BitGravity(&report.xbutton, dsp, dsp->NWGrav, NorthWestGravity);
    XFlush(dsp->display_id);
  } /* end while */
} /* end process_Xevents */
