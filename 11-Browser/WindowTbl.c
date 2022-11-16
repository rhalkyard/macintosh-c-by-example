/* *****************************************************************************
	FILE: 			WindowTbl.c
	
	DESCRIPTION: 	Window table and menu utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, and MacUser, All Rights Reserved.

	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */
#include <stdio.h>
#include <string.h>

#include "BrowserGlobals.h"

#include "DocUtilPr.h"
#include "MiscUtilPr.h"
#include "WindowTblPr.h"

/* -------------------------- Global Prototypes  ---------------------------- */

#define	kSubstChar		0x255

static ushort	sWindowKeyTbl;		/* defines which slots are taken (for cmd 1-9) */

static DocListHdl	sDocListHdl;		/* the table of open window refs */

/* ------------------------  Local Prototypes  --------------------------------- */

short		 	buildMenuItemStr 	( DocPtr, StringPtr, short );

/* -----------------------------------------------------------------------------------
	doWindowMenu - 	window menu item routing function.
	6.20.90kwgm
-------------------------------------------------------------------------------------- */
void 
doWindowMenu (theItem)
	short		theItem;
{
	DocPtr		theDoc;
	
	if ((*sDocListHdl)->count > 0)
	{
		theDoc = (*sDocListHdl)->docInfo [theItem - 1].theDoc;

		if (theDoc != FrontWindow ())
			SelectWindow (theDoc);			
	}
	
} /* doWindowMenu */
/* ---------------------------------------------------------------------------------
	findOpenDoc -	if an open document with this name and vol ref num is found,
	4/26/89			return the docPtr
	11.20.90		revised for Browser
------------------------------------------------------------------------------------ */
DocPtr
findOpenDoc (DocParamsPtr docParamsPtr)
{
	register short	index, count;
	DocPtr			aDoc;
	StringPtr		fileName;
	short			volRefNum;

	/* search open files for this file name and volRefNum */
	count = (*sDocListHdl)->count;
	index = 0;
	while (count--)
	{	
		aDoc = (*sDocListHdl)->docInfo [index++].theDoc;
		if (EqualString (docParamsPtr->fileParams.fileName, aDoc->fileName, 0, 0) && 
			docParamsPtr->fileParams.volRefNum == aDoc->volRefNum &&
			((docParamsPtr->attributes & aDoc->type) & kDocTypeMask) &&
			(docParamsPtr->attributes & aDoc->type & kBrowserModeMask) )
			return (aDoc);
	}
	
	return (0L);
	
} /* findOpenDoc */

/* -----------------------------------------------------------------------------
	closeAllDocs -	close all open documents. present user with choice 
	6.20.90kwgm		to save/cancel. Return false if user cancels at any time.
-------------------------------------------------------------------------------- */
Boolean
closeAllDocs ()
{
	DocPtr				theDoc;
	register short		count;
	Boolean				result;
	
	result = true;
	
	count = (*sDocListHdl)->count;
	while ((count--) > 0)
		if (theDoc = (*sDocListHdl)->docInfo [count].theDoc)	
			doCloseDoc (theDoc);
		
	return (result);
	
} /* closeAllDocs */

/* ----------------------------------------------------------------------------
	uncheckItems -	uncheck all the items in a menu
	6.20.90kwgm
-------------------------------------------------------------------------------- */
void
uncheckItems (theMenu)
	MenuHandle		theMenu;
{
	register short	i, count;
	
	count = CountMItems (theMenu);
	for (i = 1 ; i <= count ; i++)
		CheckItem (theMenu, i, false);
}

/* -------------------------------------------------------------------------------
	removeFromDocList - 	Given a docPtr, remove its window from
	6.20.90kwgm				the view menu and related structure
---------------------------------------------------------------------------------*/
void
removeFromDocList (theDoc)
	DocPtr				theDoc;
{
	register short			i, index, listCount, xFerCount;
	ushort					bitMask;
	Size					newHdlSize;
	DocInfo					docInfo;
	DocInfoPtr				docInfoPtr;
	
	index = theDoc->index;
	docInfo = (*sDocListHdl)->docInfo [index];

	DelMenuItem (gWindowMenu, docInfo.menuItem);
	
	if (docInfo.slotNumber <= 9)		/* clear the window entry's slot number */
	{
		bitMask = 0x0001 << (docInfo.slotNumber-1);
		
		sWindowKeyTbl &= ~bitMask;
	}
	
	(*sDocListHdl)->docInfo [index].theDoc = 0L;

	/* compact the open document list */
	
	listCount = --(*sDocListHdl)->count;	/* one less open window */
	xFerCount = listCount - index;		/* of all items above the deleted one */
	if (xFerCount)
	{
		docInfoPtr = &((*sDocListHdl)->docInfo [index]);
		BlockMove (docInfoPtr+1, docInfoPtr, sizeof (DocInfo) * xFerCount);
		/* we used BlockMove to shift all list elements at once, but each element's 
			data needs updating, since its menu item number changed */
		for ( ; index < listCount ; index++)
		{
			(*sDocListHdl)->docInfo [index].menuItem--;
			theDoc = (*sDocListHdl)->docInfo [index].theDoc;
			theDoc->index = index;
		}
	}
	
	/* now fit the memory to the size of the list */
	newHdlSize = sizeof (DocList) + (listCount - 1) * sizeof (DocInfo);
	if (resizeHdl (sDocListHdl, newHdlSize))
		return;
		
} /* removeFromDocList */

/* --------------------------------------------------------------------------------
	addToDocList -	Given a DocPtr, add its window to the view menu and
	6.20.90kwgm		the related structure
----------------------------------------------------------------------------------*/
void
addToDocList (theDoc)
	register DocPtr		theDoc;
{
	register short		bit, index;
	register ushort		bitMask;
	short				nMenuItems, slotNumber;
	Size				newHdlSize;
	DocInfo				docInfo;
	Str64 				menuItemStr;
	
	/* find next available slot in Window Key table */
	bitMask = 0x0001;
	for (bit = 1 ; bit <= 9 ; bit++)
	{
		if (!(bitMask & sWindowKeyTbl))		/* found free */
		{
			sWindowKeyTbl |= bitMask;		/* set occupied */
			break;
		}
		bitMask <<= 1;		/* shift to next bit */
	}
	
	nMenuItems = buildMenuItemStr (theDoc, menuItemStr, bit);

	InsMenuItem (gWindowMenu, menuItemStr, nMenuItems);

	if (!sDocListHdl)
		initDocList ();

	index = (*sDocListHdl)->count++;

	newHdlSize = sizeof (DocList) + index * sizeof (DocInfo);
	if (resizeHdl (sDocListHdl, newHdlSize))
		return;
	
	docInfo.slotNumber = bit <= 9 ? bit : 10;		/* docTable */
	docInfo.theDoc = theDoc;
	docInfo.menuItem = nMenuItems;

	EnableItem (gWindowMenu, docInfo.menuItem);

	theDoc->index = index;
	(*sDocListHdl)->docInfo [index] = docInfo;
		
} /* addToDocList */

/* ------------------------------------------------------------------------
	initDocList -	initialize the document list
	6.20.90kwgm
--------------------------------------------------------------------------- */
void 
initDocList ()
{
	sDocListHdl = newClearHdl ((Size) sizeof (short));			
} /* initDocList */

/* -------------------------------------------------------------------
	menuSelectDoc	-	select a document from Window Menu selection
	6.20.90kwgm
----------------------------------------------------------------------  */
void
menuSelectDoc (theItem)
	short		theItem;
{
	WindowPtr	topWindow, theDoc;
	
	topWindow = FrontWindow ();
	
	if ((*sDocListHdl)->count > 0)
	{
		theDoc = (*sDocListHdl)->docInfo [theItem - 1].theDoc;
	
		if (theDoc != topWindow)
			SelectWindow (theDoc);
	}
	
} /* menuSelectDoc */

/* ---------------------------------------------------------------------
	fixWindowMenu -	check the window item for the current top window
	6.20.90kwgm
------------------------------------------------------------------------ */
void
fixWindowMenu (theDoc)
	DocPtr 		theDoc;
{
	DocInfo		docInfo;
	
	if (theDoc)
	{		
		uncheckItems (gWindowMenu);
		docInfo = (*sDocListHdl)->docInfo [theDoc->index];
		CheckItem (gWindowMenu, docInfo.menuItem, true);
	}
}

/* --------------------------------------------------------------------------------
	buildMenuItemStr -	add a cmd-number to the window title for the view menu item
	6.20.90kwgm			return number of menu items;	
----------------------------------------------------------------------------------- */
static short
buildMenuItemStr (theDoc, menuItemStr, slotNumber)
	DocPtr			theDoc;
	StringPtr		menuItemStr;
	short			slotNumber;
{
	register short	nMenuItems, count;
	register Ptr	strPtr;
	Str16 			slotStr;
	
	BlockMove (theDoc->fileName, menuItemStr, (long)(theDoc->fileName[0] + 1));

	count = menuItemStr [0];
	
	strPtr = &menuItemStr [1];

	while (count--)	
	{
		switch (*strPtr)	/* strip any special Menu Manager chars from string */
		{
			case '/':
			case '(':
			case '<':
			case ';':
			case '^':
			case '!':
				*strPtr = kSubstChar;
				break;
		}
		
		strPtr++;
	}

	if (slotNumber <= 9)				/* add a cmd - menu number to menu item */
	{		
		PtoCstr (menuItemStr);
		sprintf (slotStr, "/%d", slotNumber);
		strcat (menuItemStr, slotStr);
		CtoPstr (menuItemStr);
	}
	
	return (CountMItems (gWindowMenu) + 1);
	
} /* buildMenuItemStr */

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, and MacUser, All Rights Reserved.
============================================================================================ */