/* *****************************************************************************
	FILE: 			WindowUtilPr.h
	
	DESCRIPTION: 	Window utility prototypes

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0	
	==========================================================

   ***************************************************************************** */
#ifndef _WindowUtilPr_
#define _WindowUtilPr_

#include <Controls.h>
#include "BrowserTypes.h"


void		centerWindow		( WindowPtr );
Rect *		getWinRect 			( WindowPtr, Rect * );
Rect *		calcNewWinRect		( Rect * );
void		makeFrameRect		( WindowPtr, Rect * );
void		setFrameClip		( WindowPtr, Rect * );

Rect *		hScrollBarRect		( WindowPtr, Rect * );
Rect *		vScrollBarRect		( WindowPtr, Rect * );
void		invalScrollBars		( WindowPtr, Boolean );
void		drawScrollBars 		( DocPtr, Boolean );

void		doGrowWindow		( WindowPtr, Point );
void		doZoomBox			( WindowPtr, short );
void		clickZoomWindow		( WindowPtr );

void		mouseInScroll		( DocPtr, ControlHandle, short, Point );

#endif
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */