/* *****************************************************************************
	FILE: 			DocUtil.c
	
	DESCRIPTION: 	Document Utilities 

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#include "AppGlobals.h"

#include "FileUtilPr.h"
#include "MiscUtilPr.h"
#include "WindowUtilPr.h"
#include "DocUtilPr.h"


/* ------------------------  Local Prototypes  --------------------------------- */
DocPtr			createNewDoc		( DocParamsPtr );
DocPtr			allocDoc			( void );

/* -----------------------------------------------------------------------------
	doNewDoc -		open a new window
	3.30.90kwgm
-------------------------------------------------------------------------------- */
Boolean
doNewDoc ()
{
	DocParams			docParams;
	DocPtr				theDoc;
	Boolean				result;
	
	result = false;
	
	/* 	
		The DocParams data structure is used to tell the creation function
		how to create the document and what file if any to associate
		with the window
	*/
	docParams.attributes = 0;
	docParams.fileParams.fileName [0] = 0;
	docParams.fileParams.openFileRefNum = 0;
	docParams.fileParams.volRefNum = 0;

	if (theDoc = createNewDoc (&docParams))
		result = true;

	return (result);

} /* doNewDoc */

/* -----------------------------------------------------------------------------
	doCloseDoc -	close the top document.
	3.30.90kwgm
-------------------------------------------------------------------------------- */
Boolean
doCloseDoc (theDoc)
	WindowPtr			theDoc;
{
	ControlHandle		control;
	Boolean				result;
	WindowPtr			topWin;

    result = false;

	if (!theDoc)		/* nothing to close */
	    return (result);
    
	if (((WindowPeek) theDoc)->windowKind  < 1)    /* desk accessory */
 		CloseDeskAcc (((WindowPeek) theDoc)->windowKind);
 	/* close the file, then dispose of the window stuff */
 	else if ((result = closeDocFile ((DocPtr)theDoc)) != kSaveChangeCancel)
 	{
 		/* dispose each control associated with the window */
      	while (control = ((WindowPeek)theDoc)->controlList)
      		DisposeControl (control);
		
		/* Have the Window Manager close the window */
		CloseWindow ((WindowPtr) theDoc);

		/* because we allocated the storage for the document, dispose the pointer */
		DisposPtr (theDoc);
		result = true;
	}
	else
		result = false;		/* the user canceled the close */

	return (result);
	
} /* doCloseDoc */

/*-------------------------------------------------------------------------
	createNewDoc -	create a new document window
	3.30.90kwgm
--------------------------------------------------------------------------*/
static DocPtr 
createNewDoc (params)
	DocParamsPtr		params;
{
	register DocPtr		theDoc;
	Str255				title;

	if (!(theDoc = allocDoc ()))	/* create the document on the heap */
		return (0L);
				
	GetIndString (title, kNameStrRsrc, kWindowTitleStrID);
	
	/* create the associated window */
	if (theDoc = NewWindow ((WindowPtr)theDoc, &gWindowRect, title, false, rDocProc, (WindowPtr)-1L, true, 0L))
	{
		ShowWindow (theDoc);
		SelectWindow (theDoc);
		SetPort (theDoc);
	}

	return (theDoc);
	
} /* createNewDoc */

/* -----------------------------------------------------------
	allocDoc -		allocate the document's data structs
	3.30.90kwgm
--------------------------------------------------------------  */
static DocPtr
allocDoc ()
{
	DocPtr		newDoc;
		
	return (newDoc = newClearPtr ((Size)sizeof (Doc)));
		
} /* allocDoc */

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */