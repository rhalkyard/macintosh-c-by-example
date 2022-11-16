/* *****************************************************************************
	FILE: 			MenuUtil.c
	
	DESCRIPTION: 	Menu Utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */
#include "BrowserGlobals.h"
#include "MenuConstants.h"

#include "AboutBoxPr.h"
#include "DocUtilPr.h"
#include "BrowserPr.h"
#include "WindowTblPr.h"
#include "WindowUtilPr.h"

#include "MenuUtilPr.h"

/* ------------------------------------------------------------------------ */
void			doAppleMenu			( short );
void			doFileMenu			( short );
void			doEditMenu			( short );


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
			doFileMenu (itemNumber);
			break;
			
		case kOpenMenuID:
			doOpenMenu (itemNumber);
			break;
			
		case kEditMenuID:
			doEditMenu (itemNumber);
			break;
			
		case kWindowMenuID:
			doWindowMenu (itemNumber);
			break;
	}
		
	HiliteMenu (0);

}	/* doMenu */

/* -----------------------------------------------------------------------------------
	doFileMenu -	file menu item routing function
	6.20.90kwgm
-------------------------------------------------------------------------------------- */
static void 
doFileMenu (theItem)
	short	theItem;
{
	switch (theItem) 
	{
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
	
	if (theDoc = FrontWindow())		/* if there's an open document */
	{
		EnableItem (gFileMenu, kCloseItem);		/* enable the close item */
		
		if (((WindowPeek) theDoc)->windowKind  >= 1)	/* generic's window */
		{
			EnableItem (gFileMenu, kOpenItem);
			DisableItem (gEditMenu, kUndoItem);		/* generic doesn't use the edit menu */
			DisableItem (gEditMenu, kCutItem);		/* so it disables the items */
			DisableItem (gEditMenu, kCopyItem);
			DisableItem (gEditMenu, kPasteItem);
			DisableItem (gEditMenu, kClearItem);
			
		}
		else
		{
			EnableItem (gEditMenu, kUndoItem);		/* DAs can use the edit menu */
			EnableItem (gEditMenu, kCutItem);
			EnableItem (gEditMenu, kCopyItem);
			EnableItem (gEditMenu, kPasteItem);
			EnableItem (gEditMenu, kClearItem);
			EnableItem (gFileMenu, 0);
			DisableItem (gFileMenu, kOpenItem);
		}
		
		fixWindowMenu (theDoc);
	}
	else
	{
		EnableItem (gFileMenu, kOpenItem);
		DisableItem (gFileMenu, kCloseItem);		/* no open windows, so no need to close */
	}
	
} /* fixMenus */

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies All Rights Reserved.
================================================================================ */