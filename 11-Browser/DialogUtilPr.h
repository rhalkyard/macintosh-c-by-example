/* *****************************************************************************
	FILE: 			DialogUtilPr.h
	
	DESCRIPTION: 	Dialog box Utilities Protoypes
	
	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */

#ifndef _DialogUtilPr_
#define _DialogUtilPr_

pascal void			buttonProc 			( DialogPtr, short );
pascal void			sepLineProc			( DialogPtr, short );
pascal Boolean		DLOGfilterProc1 	( DialogPtr, EventRecord *, short * );
Point				dialogTopLeft		( short );

#endif
/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */