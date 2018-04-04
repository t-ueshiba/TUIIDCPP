/*
 *  平成14-19年（独）産業技術総合研究所 著作権所有
 *  
 *  創作者：植芝俊夫
 *
 *  本プログラムは（独）産業技術総合研究所の職員である植芝俊夫が創作し，
 *  （独）産業技術総合研究所が著作権を所有する秘密情報です．著作権所有
 *  者による許可なしに本プログラムを使用，複製，改変，第三者へ開示する
 *  等の行為を禁止します．
 *  
 *  このプログラムによって生じるいかなる損害に対しても，著作権所有者お
 *  よび創作者は責任を負いません。
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
 *  $Id$  
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
CanvasPane::CanvasPane(Window& parentWin, size_t devWidth, size_t devHeight)
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
				     nullptr))
{
    if (window().isFullScreen())
	XtVaSetValues(_widget, XtNborderWidth, 0, nullptr);
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
