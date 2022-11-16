/* *****************************************************************************
	FILE: 			WindowUtilPr.h
	
	DESCRIPTION: 	Window utility prototypes

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */

#ifndef _WindowUtilPr_
#define _WindowUtilPr_

#include "Version.h"

#ifdef V5
#include <Controls.h>
#include <Types.h>
#include <Windows.h>
#else
#include <ControlMgr.h>
#include <MacTypes.h>
#include <WindowMgr.h>
#endif
void			centerWindow	( WindowPtr );
Rect *			getWinRect		( WindowPtr, Rect * );

#endif
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */