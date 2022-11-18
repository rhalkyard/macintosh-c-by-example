/* *****************************************************************************
	FILE: 			DisplayPr.h
	
	DESCRIPTION: 	Display Routines Prototype file

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#ifndef _DisplayPr_
#define _DisplayPr_

#include "AppTypes.h"

void		makeFrameRect		( WindowPtr, Rect * );
void		setFrameClip		( WindowPtr, Rect * );

void		drawDocContents		( DocPtr );

#endif
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */
