/* *****************************************************************************
	FILE: 			WindowUtilPr.h
	
	DESCRIPTION: 	Window utility prototypes

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	4.24.90	-	June 1990 MacUser Release - multiple windows
	3.30.90 - 	May 1990 MacUser Release	
	==========================================================

   ***************************************************************************** */

#ifndef _WindowUtilPr_
#define _WindowUtilPr_

#include <Controls.h>

#if V2
#include <ControlMgr.h>
#endif

#include "AppTypes.h"

#define kPage	1
#define	kLine	2

void		centerWindow		( WindowPtr );
Rect *		getWinRect 			( WindowPtr, Rect * );
Rect *		calcNewWinRect		( WindowPtr, Rect * );

Rect *		hScrollBarRect		( WindowPtr, Rect * );
Rect *		vScrollBarRect		( WindowPtr, Rect * );
void		invalScrollBars		( WindowPtr, Boolean );
void		drawScrollBars 		( DocPtr, Boolean );


void		doGrowWindow		( WindowPtr, Point );
void 		mouseScroll 		( WindowPtr, ControlHandle, short, Point );
void		doZoomBox			( WindowPtr, short );
void		clickZoomWindow		( WindowPtr );

Rect *		makeFrameRect		( WindowPtr, Rect * );
void		setFrameClip		( WindowPtr, Rect * );

#endif
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */