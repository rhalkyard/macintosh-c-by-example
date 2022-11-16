/* *****************************************************************************
	FILE: 			DialogUtilPr.h
	
	DESCRIPTION: 	Dialog box Utilities Protoypes
	
	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	5.20.90 - 	July 1990 MacUser Release - scrolling
	4.24.90	-	June 1990 MacUser Release - multiple windows
	3.30.90 - 	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */

#ifndef _DialogUtilPr_
#define _DialogUtilPr_

pascal void			buttonProc 			( DialogPtr, short );
pascal Boolean		DLOGfilterProc1 	( DialogPtr, EventRecord *, short * );

#endif
/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */