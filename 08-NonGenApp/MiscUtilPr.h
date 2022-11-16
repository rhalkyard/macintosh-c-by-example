/* *****************************************************************************
	FILE: 			MiscUtilPr.h
	
	DESCRIPTION: 	Useful utilities Prototypes

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	5.20.90	-	July 1990 MacUser Release
	4.24.90	-	June 1990 MacUser Release
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */

#ifndef _MiscUtilPr_
#define _MiscUtilPr_

Handle		newClearHdl		( Size );
Ptr			newClearPtr		( Size );
OSErr		resizeHdl		( Handle, Size );

StringPtr	memErrorStr		( StringPtr, OSErr);
Boolean		pDebugStr 		( StringPtr );

Boolean		getDblClick		( EventRecord * );

#endif
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */
