/*
 *  $BJ?@.(B14-19$BG/!JFH!K;:6H5;=QAm9g8&5f=j(B $BCx:n8"=jM-(B
 *  
 *  $BAO:n<T!'?"<G=SIW(B
 *
 *  $BK\%W%m%0%i%`$O!JFH!K;:6H5;=QAm9g8&5f=j$N?&0w$G$"$k?"<G=SIW$,AO:n$7!$(B
 *  $B!JFH!K;:6H5;=QAm9g8&5f=j$,Cx:n8"$r=jM-$9$kHkL)>pJs$G$9!%Cx:n8"=jM-(B
 *  $B<T$K$h$k5v2D$J$7$KK\%W%m%0%i%`$r;HMQ!$J#@=!$2~JQ!$Bh;0<T$X3+<($9$k(B
 *  $BEy$N9T0Y$r6X;_$7$^$9!%(B
 *  
 *  $B$3$N%W%m%0%i%`$K$h$C$F@8$8$k$$$+$J$kB;32$KBP$7$F$b!$Cx:n8"=jM-<T$*(B
 *  $B$h$SAO:n<T$O@UG$$rIi$$$^$;$s!#(B
 *
 *  Copyright 2002-2007.
 *  National Institute of Advanced Industrial Science and Technology (AIST)
 *
 *  Creator: Toshio UESHIBA
 *
 *  [AIST Confidential and all rights reserved.]
 *  This program is confidential. Any using, copying, changing or
 *  giving any information concerning with this program to others
 *  without permission by the copyright holder are strictly prohibited.
 *
 *  [No Warranty.]
 *  The copyright holder or the creator are not responsible for any
 *  damages caused by using this program.
 *
 *  $Id: CanvasPane.cc,v 1.8 2009-03-03 00:59:47 ueshiba Exp $  
 */
#include "TU/v/CanvasPane.h"
#include "vViewport_.h"
#include "vGridbox_.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class CanvasPane							*
************************************************************************/
CanvasPane::CanvasPane(Window& parentWin, u_int devWidth, u_int devHeight)
    :Pane(parentWin),
     _widget(XtVaCreateManagedWidget("TUvCanvasPane",
				     vViewportWidgetClass,  // widget class 
				     parent().widget(),     // parent widget
				     XtNallowHoriz,	TRUE,
				     XtNallowVert,	TRUE,
				     XtNwidth,	(devWidth != 0 ? devWidth :
						 parent().widget().width()),
				     XtNheight,	(devHeight != 0 ? devHeight :
						 parent().widget().height()),
				     XtNuseBottom,	TRUE,
				     XtNuseRight,	TRUE,

				   // Expand/shrink according to the width/
				   // height of Paned.
				     XtNweightx,	1,
				     XtNweighty,	1,
				     Null))
{
    if (window().isFullScreen())
	XtVaSetValues(_widget, XtNborderWidth, 0, Null);
}

CanvasPane::~CanvasPane()
{
}

const Object::Widget&
CanvasPane::widget() const
{
    return _widget;
}

CanvasPane&
CanvasPane::canvasPane()
{
    return *this;
}

void
CanvasPane::initializeGraphics()
{
}

void
CanvasPane::repaintUnderlay()
{
}

void
CanvasPane::repaintOverlay()
{
}

void
CanvasPane::moveDC(int u, int v)
{
    vViewportSetCoordinates(_widget,
			    u - _widget.width()/2, v - _widget.height()/2);
}

}
}
