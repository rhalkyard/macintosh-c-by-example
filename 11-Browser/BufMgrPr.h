/* *****************************************************************************
	FILE: 			BufMgrPr.h
	
	DESCRIPTION: 	Browser I/O buffer management prototypes

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */

#ifndef _BufMgrPr_
#define _BufMgrPr_

#include "BrowserTypes.h"

Boolean		initFileBuffer		( DocPtr, DocParamsPtr );
void		prevFileBuffer		( DocPtr, long );
void		nextFileBuffer 		( DocPtr, long );
void		disposeFileBuffer	( DocPtr );                                            

#endif
/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */