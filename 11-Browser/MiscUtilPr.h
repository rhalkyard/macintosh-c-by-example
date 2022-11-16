/* *****************************************************************************
	FILE: 			MiscUtilPr.h
	
	DESCRIPTION: 	Useful utilities Prototypes

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */

#ifndef _MiscUtilPr_
#define _MiscUtilPr_

Handle		newClearHdl		( Size );
Ptr			newClearPtr		( Size );
OSErr		resizeHdl		( Handle, Size );
OSErr		disposeHdl		( Handle );

StringPtr	memErrorStr		( StringPtr, OSErr);
Boolean		getDblClick		( EventRecord *e );

Boolean		pDebugStr 		( StringPtr );
StringPtr	pStrCat			( StringPtr, StringPtr );

#endif
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */
