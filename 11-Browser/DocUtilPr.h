/* *****************************************************************************
	FILE: 			DocUtilPr.h
	
	DESCRIPTION: 	Document Utilities Prototypes

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */

#ifndef _DocUtilPr_
#define _DocUtilPr_

void			doOpenMenu		( short );
short			doOpenFile		( DocParamsPtr, DocPtr *);
Boolean			doCloseDoc		( WindowPtr );
void			resizeTextDocContents	 ( DocPtr );
#endif
/* ===========================================  EOF  ===========================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */