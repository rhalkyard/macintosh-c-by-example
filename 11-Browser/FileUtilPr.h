/* *****************************************************************************
	FILE: 			FileUtilPr.h
	
	DESCRIPTION: 	File Utility prototypes

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies,  All Rights Reserved.

	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */
#ifndef _FileUtilPr_
#define _FileUtilPr_

#include "BrowserTypes.h"

OSErr		openFile 			( DocParamsPtr );
OSErr		closeDocFile 		( DocPtr );
OSErr		readFile 			( short, uchar *, Size * );

#endif

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies,  All Rights Reserved.
============================================================================================ */