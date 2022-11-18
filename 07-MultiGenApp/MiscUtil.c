/* *****************************************************************************
	FILE: 			MiscUtil.c
	
	DESCRIPTION: 	Useful utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	4.24.90 -	June 1990 MacUser Release - Multiple window support
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#include "Version.h"

#include <Dialogs.h>
#include <Sound.h>
#include <TextUtils.h>

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
#include <Pascal.h>
#include <Proto.h>
#endif

#include "AppGlobals.h"
#include "StrRsrcDefs.h"

#include "DialogUtilPr.h"
#include "WindowUtilPr.h"

#include "MiscUtilPr.h"

/* -------------------------------------------------------------------------
	newClearPtr - 	allocate a zeroed, non-relocatable memory object of size 
	3.30.90kwgm		bytes and return its pointer
---------------------------------------------------------------------------- */
Ptr
newClearPtr (size)
	Size			size;
{
	Ptr				thePtr;
	Size			freeMem;
	OSErr			err;
	Str64			s;
	
	thePtr = 0L;
	if (size >= 0L)		/* a common sense test for negative size */
	{
		freeMem = MaxBlock ();		/* check the largest block avail */
	
		if (size < freeMem)		/* if request is less than largest block */
		{
			thePtr = NewPtrClear(size);
	
			if (err = MemError() || thePtr == nil)	/* test for success */
			{
				if (gDevel)
				{
					memErrorStr (s, err);
					pDebugStr (s);			/* report error */
				}
		
				thePtr = 0L;	/* clear out the ptr on memory error */
			}
		}
	}
	else
	{
		if (gDevel)
			pDebugStr ("\pnewClearPtr: negative size");
	}
	
	return (thePtr);
		
} /* newClearPtr */

/* ### 4.24.90 kwgm - new routine for multiGeneric */
/*---------------------------------------------------------------------------
	newClearHdl - 	allocate a zeroed, relocatable memory object of size 
	4.24.90kwgm		bytes and return the handle to it
----------------------------------------------------------------------------*/
Handle
newClearHdl (size)
	Size			size;
{
	Handle			theHandle;
	Size			freeMem;
	OSErr			err;
	Str64			s;
	
	theHandle = 0L;
	if (size >= 0L)
	{
		freeMem = FreeMem ();	/* check free space */
			if (size < freeMem)		/* if less than free space */
			{
			theHandle = NewHandleClear(size);

			if (err = MemError() || theHandle == nil)	/* test for success */
			{
				if (gDevel)
				{
					memErrorStr (s, err);
					pDebugStr (s);
				}
		
				theHandle = 0L;	/* clear out the handle on memory error */
			}
		}
	}
	else
	{
		if (gDevel)
			pDebugStr ("\pnewClearHdl: negative size");
	}
	
	return (theHandle);
		
} /* newClearHdl */

/* ---------------------------------------------------------------------------------
	resizeHdl -		resize a relocatable block of memory
	4.24.90kwgm
------------------------------------------------------------------------------------ */
OSErr
resizeHdl (aHandle, newSize)
	Handle		aHandle;
	Size		newSize;
{
	OSErr		err;
	Size		free, size;
	Str64		s;
	
	if (newSize < 0L)
	{
		if (gDevel)
			pDebugStr ("\presizeHdl: requested handle size is negative");
			
		return (nilHandleErr);
	}

	if (aHandle)
	{
		/* odd address handles are not allowed (yet!) */
		if ((long)aHandle & 0x00000001L)
		{
			if (gDevel)
				pDebugStr ("\presizeHdl: Handle has odd address");

			return (nilHandleErr);
		}

		/* is this handle a real handle?? 
			GetHandleSize returns 0 if it isn't
		*/
		size = GetHandleSize (aHandle);
		if (!size)
		{
			/* if MemError then we have a bad handle */
			if (err = MemError ())
			{
				if (gDevel)
				{
					memErrorStr (s, err);
					pDebugStr (s);
				}
				return (err);
			}
		}
	
		/* change the size */
		SetHandleSize (aHandle, newSize);

		/* check error in SetHandleSize */
		if (err = MemError())
		{
			memErrorStr (s, err);
			pDebugStr (s);
			return (err);
		}
	}
	else
	{
		pDebugStr ("\presizeHdl: attempt to resize null Handle");
		return (nilHandleErr);
	}
		
	return (noErr);
			
} /* resizeHdl */
/* ### 4.24.90 kwgm - new routine for multiGeneric */

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
	GrafPtr				savePort;
	ControlHandle		itemHdl;
	DialogPtr 			theDialog;
	
	SysBeep (1);			/* beep the bell */
	GetPort (&savePort);	/* save graphic environment */

	/* get the dialog for the message */
	if (!(theDialog = GetNewDialog (kDebugMsgDLOG, 0L, (WindowPtr)-1L)))
		return (false);
	
	/* hilite the default button */
	GetDItem (theDialog, kDebugMsgOKOutline, &type, (Handle *) &itemHdl, &box);
	SetDItem (theDialog, kDebugMsgOKOutline, type, (Handle) buttonProc, &box);

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

/* ### 4.24.90 kwgm - new routine for multiGeneric */
/* ----------------------------------------------------------------------------
	memErrorStr -	passed a memory error id, create a string with the error
	4.24.90kwgm
------------------------------------------------------------------------------- */
StringPtr
memErrorStr (theString, errorID)
	StringPtr		theString;
	OSErr			errorID;
{
	Str64			errorStr, hdrStr;
	short			strID;
	
	strID = 0;
	switch (errorID)		/* get the string resource id for this error */
	{
		case memROZErr:
			strID = kMemErrReadOnlyStr;
			break;
			
		case memFullErr:
			strID = kMemErrMemFullStr;
			break;
			
		case nilHandleErr:
			strID = kMemErrNilHdlStr;
			break;
			
		case memWZErr:
			strID = kMemErrFreeBlkStr;
			break;
			
		case memPurErr:
		case memLockedErr:
			strID = kMemErrLockedBlkStr;
			break;
		
		case noErr:
			strID = kMemErrNoErrStr;
			break;
			
		default:
			strID = kMemErrUnknownStr;
			break;
	}
		
	/* get the strings from the resource file */
	GetIndString (errorStr, kMemErrStrRsrc, strID);
	GetIndString (hdrStr, kMemErrStrRsrc, kMemErrMsgStr);

	/* create the error string */
	PtoCstr (hdrStr);
	PtoCstr (errorStr);
	sprintf (theString,"%s %d => %s", hdrStr, errorID, errorStr);
	CtoPstr (theString);
	
	return (theString);
	
} /* memErrorStr */
/* ### 4.24.90 kwgm - new routine for multiGeneric */

/* ### 4.24.90 kwgm - new routine for multiGeneric */
/* -------------------------------------------------------------------------------------------
	getDblClick -	check for mouse double-click
	4.24.90kwgm
--------------------------------------------------------------------------------------------- */
Boolean
getDblClick (e)
	register EventRecord 	*e;
{	
	EventRecord 			eRec;
	register long			ticks, dblTime;
	
#define kBounds		5		/* in pixels */

	/* wait for mouse up event within dbl time range */
	dblTime = (GetDblTime() >> 1);	/* tighten up double time */
	do {
		
		ticks = TickCount ();
		
	} while (StillDown () && (ticks - e->when < dblTime));

	/* mouse down before timeout and within kBounds range of last mouse pt is a dblClick */
	do {
		ticks = TickCount ();
		if (GetNextEvent (mDownMask,&eRec))	
		{
			/* check to see if in same rect */
			if ((eRec.where.h <= e->where.h + kBounds) || (eRec.where.h >= e->where.h - kBounds) &&
				(eRec.where.v <= e->where.v + kBounds) || (eRec.where.v >= e->where.v - kBounds))
				return (true);
		}
	} while ((ticks - e->when < dblTime));

	return (false);
	
} /* getDblClick */
/* ### 4.24.90 kwgm - new routine for multiGeneric */

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */