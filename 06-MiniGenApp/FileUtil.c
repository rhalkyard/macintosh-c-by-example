/* *****************************************************************************
	FILE: 			FileUtil.c
	
	DESCRIPTION: 	File I/O utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	3.3090	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#include "AppConstants.h"

#include "FileUtilPr.h"


/* ------------------------  Local Prototypes  --------------------------------- */

void			closeFile			( short, short );

/* ------------------------------------------------------------------------------------------
	closeDocFile 	-	close the data file associated with a document
	3.30.90kwgm
--------------------------------------------------------------------------------------------*/
short
closeDocFile (theDoc)
	register DocPtr 	theDoc;
{	
	if (!theDoc)
		return;

	closeFile (theDoc->volRefNum, theDoc->openFileRefNum);
	
	theDoc->openFileRefNum = 0;
	theDoc->volRefNum = 0;
	
	return (true);

} /* closeDocFile */

/* -------------------------------------------------------------------------------------
	closeFile	-	close a file specified by fileRef
	3.30.90kwgm
---------------------------------------------------------------------------------------- */
static void
closeFile (volRef, fileRef)
	short		volRef, fileRef;
{
	if (fileRef > 0)
	{
		FSClose (fileRef);
		FlushVol (0L, volRef);
	}
	
} /* closeFile */

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */	

