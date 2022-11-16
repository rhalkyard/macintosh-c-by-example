/* *****************************************************************************
	FILE: 			AppConstants.h
	
	DESCRIPTION: 	Application global constants

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	4.24.90	-	June 1990 MacUser Release - multiple windows
	3.30.90 - 	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */

#ifndef _AppConstants_
#define _AppConstants_

/* ### 4.24.90kwgm - added for multiGeneric */
/* 
	define MAX and MIN as macros, if not already defined 
	The heavy use of parenthesis allows either x or y to be an expression
*/
#ifndef MIN
#define	MIN(x,y)	(((x) > (y)) ? (y) : (x))
#endif

#ifndef MAX
#define MAX(x,y)	(((x) < (y)) ? (y) : (x))
#endif
/* ### 4.24.90kwgm - added for multiGeneric */

/* ----------------------  Window/Scroll Bar stuff  ----------------------------- */

#define		kScrollBarSize		16

/* ### 4.24.90kwgm - added for multiGeneric */
#define		kControlMax			1000
#define		kHScrollTag			1
#define		kVScrollTag			2

#define		kMaxOpenDocs		32
/* ### 4.24.90kwgm - added for multiGeneric */

/* ### 4.24.90kwgm - added for multiGeneric */
/* -----------------------  Document attributes  ------------------------------- */

#define	kDocDirty	0x0001		/* the-doc-has-been-changed flag */
/* a macro to test this bit in the doc */
#define	ISDIRTY(d)	((((DocPtr)d)->attributes & kDocDirty) ? true : false)
/* ### 4.24.90kwgm - added for multiGeneric */


/* ### 4.24.90kwgm - STR# resources in multiGeneric defined in StrRsrcDefs.h */
#if 0
/* --------------------   String Resources  ------------------------------------ */
#define		kNameStrRsrc		100
#define		kHelloStrID			1
#define		kWindowTitleStrID	2
#define		kAboutBoxMsgStr		3
#endif
/* ### 4.24.90kwgm - multiGeneric ∂ */

/* --------------------   Dialog Resources  ------------------------------------ */

#define	kSetButtonID			1		/* used in all dialogs: button 1 is OK */
#define	kCancelButtonID			2		/* button 2 is Cancel */

#define	kSaveChangeDLOG			64		/* save changes on closing dialog */
#define	kSaveChangeOK			1
#define	kSaveChangeDont			2
#define	kSaveChangeCancel		4


#define kNotEnufMem				256		/* alert IDs */
#define	kUnknownMach			257

#define kAboutBoxDLOG			600
#define	kAboutMemBox	  		2

#define	kDebugMsgDLOG			1000	/* a general message dialog used for error reporting */
#define	kDebugMsgCancel			2		/* in MiscUtil.c: pDebugStr() */
#define	kDebugMsgExit			3
#define	kDebugMsgOKOutline		7

#endif

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */