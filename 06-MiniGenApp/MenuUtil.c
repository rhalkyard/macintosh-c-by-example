/* *****************************************************************************
	FILE: 			MenuUtil.c
	
	DESCRIPTION: 	Menu Utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#include <Devices.h>
#include <Menus.h>

#include "ThinkHelpers.h"

#include "AppGlobals.h"
#include "MenuConstants.h"

#include "AboutBoxPr.h"
#include "DocUtilPr.h"
#include "ShellPr.h"
#include "WindowUtilPr.h"

#include "MenuUtilPr.h"

/* ---------------------  Local Prototypes  -------------------------------- */
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
-------------------------------------------------------------------------------------- */
static void 
doFileMenu (theItem)
	short	theItem;
{
	switch (theItem) 
	{
		case kNewItem:
			doNewDoc ();
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
	SystemEdit (theItem);
}	/* doEditMenu */

/* ----------------------------------------------------------------------------------
	fixMenus -		fixup the applications menus 
	3.30.90kwgm
------------------------------------------------------------------------------------- */
void
fixMenus ()
{
	DocPtr		theDoc;
	
	theDoc = FrontWindow();
	
	if (theDoc)
	{
		DisableItem (gFileMenu, kNewItem);
		EnableItem (gFileMenu, kCloseItem);
		
		if (((WindowPeek) theDoc)->windowKind  >= 1)	/* Generic vindow */
		{
			DisableItem (gEditMenu, kUndoItem);
			DisableItem (gEditMenu, kCutItem);
			DisableItem (gEditMenu, kCopyItem);
			DisableItem (gEditMenu, kPasteItem);
			DisableItem (gEditMenu, kClearItem);
		}
		else
		{
			EnableItem (gEditMenu, kUndoItem);
			EnableItem (gEditMenu, kCutItem);
			EnableItem (gEditMenu, kCopyItem);
			EnableItem (gEditMenu, kPasteItem);
			EnableItem (gEditMenu, kClearItem);
			EnableItem (gFileMenu, 0);
		}
	}
	else
	{
		EnableItem (gFileMenu, kNewItem);
		DisableItem (gFileMenu, kCloseItem);
	}
} /* fixMenus */

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */