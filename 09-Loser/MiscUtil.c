/* *****************************************************************************
	FILE: 			MiscUtil.c
	
	DESCRIPTION: 	Useful utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	5.28.90	-	Sept 1990 MacUser Release (Loser)
	==========================================================

   ***************************************************************************** */
#include "AppConstants.h"
#include "AppGlobals.h"
#include "StrRsrcDefs.h"

#include "DialogUtilPr.h"
#include "WindowUtilPr.h"

#include "MiscUtilPr.h"

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

/* ---------------------------------------------------------------------------
	pStrCat - a Pascal string to Pascal string cat function. Cats ps2 to ps1
----------------------------------------------------------------------------- */
StringPtr
pStrCat (ps1, ps2)
	register uchar *ps1, *ps2;
{
	register short len1, len2, len3;
	register uchar *ps3;
	
	ps3 = ps1;
	
	len1 = (unsigned)*ps1++;
	len2 = (unsigned)*ps2++;
	len3 = len1 + len2;
	
	while (len1--)
		ps1++;
		
	while (len2--)
		*ps1++ = *ps2++;
	
	*ps3 = (char)len3;
	
	return (ps3);

} /* pStrCat */

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */