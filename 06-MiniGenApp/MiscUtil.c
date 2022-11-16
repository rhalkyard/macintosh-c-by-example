/* *****************************************************************************
	FILE: 			MiscUtil.c
	
	DESCRIPTION: 	Useful utilities for memory allocation and other duties

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#include "Version.h"

#include <Dialogs.h>
#include <Sound.h>

#include "ThinkHelpers.h"

#ifdef V5
#include <stdio.h>
#endif

#ifdef V4
#include <stdio.h>
#endif

#ifdef V3
#include <Proto.h>
#endif

#ifdef V2
#include <asm.h>
#include <MemoryMgr.h>
#include <Pascal.h>
#include <Proto.h>
#endif

#include "AppGlobals.h"

#include "DialogUtilPr.h"
#include "WindowUtilPr.h"

#include "MiscUtilPr.h"

/*---------------------------------------------------------------------------
	newClearPtr - 	allocate a zeroed, non-relocatable memory object of size 
	3.30.90kwgm		bytes and return its pointer
----------------------------------------------------------------------------*/
Ptr
newClearPtr (size)
	Size			size;
{
	Ptr				thePtr;
	Size			freeMem;
	OSErr			err;
	char			s [64];
	
	if (size < 0L)
	{
		if (gDevel)
			pDebugStr ("\pnewClearPtr: negative size");
			
		return (0L);
	}

	freeMem = MaxBlock ();	/* get the size of the largest block in the heap */

	thePtr = 0L;
	if (size < freeMem)		/* if we want less than the largest block */
	{
		thePtr = NewPtrClear(size);

		if (err = MemError())	/* test for success */
		{
			if (gDevel)
			{
				sprintf (s,"newClearPtr: mem error %d", err);
				CtoPstr (s);
				pDebugStr (s);
			}
	
			thePtr = 0L;	/* clear out the ptr on memory error */
		}
	}
	
	return (thePtr);
		
} /* newClearPtr */

/* ------------------------------------------------------------------------------------
	pDebugStr  -	provide sensible interface for error messages and allow a user the
	3.30.90kwgm		choice of actions
--------------------------------------------------------------------------------------- */
Boolean
pDebugStr  (string)
	StringPtr			string;
{
	unsigned short		flags;
	short				theItem, type;
	Rect				box;
	DialogPtr 			theDialog;
	GrafPtr				savePort;
	ControlHandle		itemHdl;
	
	SysBeep (1);			/* beep the bell */
	GetPort (&savePort);	/* save graphic environment */

	/* get the dialog for the message */
	if (!(theDialog = GetNewDialog (kDebugMsgDLOG, 0L, (WindowPtr)-1L)))
		return (false);
	
	/* hilite the default button */
	GetDItem (theDialog, kDebugMsgOKOutline, &type, &itemHdl, &box);
	SetDItem (theDialog, kDebugMsgOKOutline, type, buttonProc, &box);

	ParamText (0L, string, 0L, 0L);		/* set up to write the error string */

	centerWindow (theDialog);
	ShowHide (theDialog, true);
	
	/* display the dialog, wait for button */
	ModalDialog (DLOGfilterProc1, &theItem);
	
	DisposDialog (theDialog);		/* restore environment */
	SetPort (savePort);

	/* switch on user choice */
	if (theItem == kDebugMsgExit)
		ExitToShell();
	else if (theItem == kDebugMsgCancel)
		return (false);
	else
		return (true);
	
} /* pDebugStr */

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */