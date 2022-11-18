/* *****************************************************************************
	FILE: 			MenuUtil.c
	
	DESCRIPTION: 	Menu Utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	5.20.90 - 	July 1990 MacUser Release
					- support for Doc type menu
	4.24.90 -	June 1990 MacUser Release: No Changes
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#include <Devices.h>
#include <Menus.h>
#include <Windows.h>

#include "ThinkHelpers.h"

#include "AppGlobals.h"
#include "MenuConstants.h"

#include "AboutBoxPr.h"
#include "DocUtilPr.h"
#include "ShellPr.h"
#include "WindowUtilPr.h"

#include "MenuUtilPr.h"

/* ------------------------------------------------------------------------ */
static void			doAppleMenu			( short );
static void			doFileMenu			( short );
static void			doEditMenu			( short );


/* -----------------------------------------------------------------------------
	doMenu -		determine what item in which menu was selected.
	3.30.9090kwgm	route control to the action function
-------------------------------------------------------------------------------*/
void 
doMenu (menuResult)
	long  		menuResult;
{
	short 		menuID, itemNumber;

	menuID = HiWord (menuResult);		/* which menu */
	itemNumber = LoWord (menuResult);	/* what item */
	
	switch (menuID) 
	{
		case kAppleMenuID:
			doAppleMenu (itemNumber);
			break;
			
		case kFileMenuID:
		case kDocTypeMenuID:
			doFileMenu (itemNumber);
			break;
			
		case kEditMenuID:
			doEditMenu (itemNumber);
			break;
	}
		
	HiliteMenu (0);

}	/* doMenu */

/* -----------------------------------------------------------------------------------
	doFileMenu -	file menu item routing function
	3.30.90kwgm
	5.20.90kwgm		modified for text/pict doc support
-------------------------------------------------------------------------------------- */
static void 
doFileMenu (theItem)
	short	theItem;
{
	switch (theItem) 
	{
/* ### kwgm 5.17.90 - support text and pict doc */
		case kTextDocItem:
		case kPictDocItem:
			doNewDoc ((theItem == kPictDocItem) ? kDocPICT : kDocText);
			break;
			
		case kCloseItem:
			doCloseDoc (FrontWindow ());
			break;
			
		case kQuitItem:
			cleanExit (true);
			break;
	}
	
} /* doFileMenu */

/* -----------------------------------------------------------------------------------
	doAppleMenu -	apple menu item routing function
	3.30.90kwgm
-------------------------------------------------------------------------------------- */
static void 
doAppleMenu (theItem)
	short		theItem;
{
	Str255		itemName;
	
	if (theItem == 1)
		 doAboutBox ();
	else
	{	/* desk accesories get called here */
		GetItem (GetMHandle (kAppleMenuID), theItem, itemName);
		OpenDeskAcc (itemName);
	}
	
} /* doAppleMenu */

/* -----------------------------------------------------------------------------------
	doEditMenu - 	edit menu item routing function.
	3.30.90kwgm		Supplied for desk accessory compatibility
-------------------------------------------------------------------------------------- */
static void 
doEditMenu (theItem)
	short	theItem;
{
	SystemEdit (theItem);		/* for desk accessories */
} /* doEditMenu */

/* ----------------------------------------------------------------------------------
	fixMenus -		fixup the application's menus 
	3.30.90kwgm
	5.20.90kwgm		support for text/pict window
------------------------------------------------------------------------------------- */
void
fixMenus ()
{
	DocPtr		theDoc;
	
	if (theDoc = (DocPtr) FrontWindow())		/* if there's an open document */
	{
		EnableItem (gFileMenu, kCloseItem);		/* enable the close item */
		
		if (((WindowPeek) theDoc)->windowKind  >= 1)	/* generic's window */
		{
			DisableItem (gEditMenu, kUndoItem);		/* generic doesn't use the edit menu */
			DisableItem (gEditMenu, kCutItem);		/* so it disables the items */
			DisableItem (gEditMenu, kCopyItem);
			DisableItem (gEditMenu, kPasteItem);
			DisableItem (gEditMenu, kClearItem);
			
/* ### kwgm 6.20.90 */
			if (gNumOpenDocs >= 2)
			{
				DisableItem (gDocTypeMenu, kPictDocItem);
				DisableItem (gDocTypeMenu, kTextDocItem);
			}
			else if (ISPICTDOC(theDoc))
#if 0
			if (ISPICTDOC(theDoc))
#endif
/* ### kwgm 6.20.90 */
			{
				DisableItem (gDocTypeMenu, kPictDocItem);
				EnableItem (gDocTypeMenu, kTextDocItem);
			}
			else
			{
				DisableItem (gDocTypeMenu, kTextDocItem);
				EnableItem (gDocTypeMenu, kPictDocItem);
			}
/* ### kwgm 5.17.90 */
		}
		else
		{
			EnableItem (gEditMenu, kUndoItem);		/* DAs can use the edit menu */
			EnableItem (gEditMenu, kCutItem);
			EnableItem (gEditMenu, kCopyItem);
			EnableItem (gEditMenu, kPasteItem);
			EnableItem (gEditMenu, kClearItem);
			EnableItem (gFileMenu, 0);
/* ### kwgm 5.17.90 - new menus */
			DisableItem (gDocTypeMenu, kTextDocItem);
			DisableItem (gDocTypeMenu, kPictDocItem);
/* ### kwgm 5.17.90 */
		}
	}
	else
	{
		EnableItem (gFileMenu, kNewItem);
/* ### kwgm 5.17.90 - new menus */
		EnableItem (gDocTypeMenu, kPictDocItem);
		EnableItem (gDocTypeMenu, kTextDocItem);
/* ### kwgm 5.17.90  */
		DisableItem (gFileMenu, kCloseItem);		/* no open windows, so no need to close */
	}
	
} /* fixMenus */

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */