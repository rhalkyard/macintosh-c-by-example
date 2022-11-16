/* *****************************************************************************
	FILE: 			DialogUtilPr.h
	
	DESCRIPTION: 	Dialog box Utilities Protoypes
	
	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	5.28.90	- Sept 1990 MacUser Release (Loser)
	==========================================================

   ***************************************************************************** */

#ifndef _DialogUtilPr_
#define _DialogUtilPr_

Point				dialogTopLeft		( short );
void				doNumAlert			( short );

pascal void			buttonProc			( DialogPtr, short );
pascal void			sepLineProc			( DialogPtr, short );

pascal Boolean		DLOGfilterProc1 	( DialogPtr, EventRecord *, short * );

#endif
/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */