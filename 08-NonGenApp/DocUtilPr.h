/* *****************************************************************************
	FILE: 			DocUtilPr.h
	
	DESCRIPTION: 	Document Utilities Prototypes

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

#ifndef _DocUtilPr_
#define _DocUtilPr_

Boolean			doNewDoc		( short );
Boolean			doCloseDoc		( WindowPtr );
Boolean			closeAllDocs 	( void );

/* ### kwgm 5.20.90 */
void			resizeDocContents	 (DocPtr);
/* ### kwgm 5.20.90 */

#endif
/* ===========================================  EOF  ===========================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */