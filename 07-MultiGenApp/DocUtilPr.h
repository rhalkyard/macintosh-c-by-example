/* *****************************************************************************
	FILE: 			DocUtilPr.h
	
	DESCRIPTION: 	Document Utilities Prototypes

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	4.24.90	-	June 1990 MacUser Release - multiple windows
	3.30.90 - 	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */

#ifndef _DocUtilPr_
#define _DocUtilPr_

#ifdef V5
#include <Windows.h>
#else
#include <WindowMgr.h>
#endif

Boolean		doNewDoc	( void );
Boolean		doCloseDoc	( WindowPtr );
Boolean		closeAllDocs ( void );

#endif
/* ===========================================  EOF  ===========================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */