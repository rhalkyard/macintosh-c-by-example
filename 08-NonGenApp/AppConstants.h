/* *****************************************************************************
	FILE: 			AppConstants.h
	
	DESCRIPTION: 	Application global constants

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	5.20.90 - 	July 1990 MacUser Release - scrolling
	4.24.90	-	June 1990 MacUser Release - multiple windows
	3.30.90 - 	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */

#ifndef _AppConstants_
#define _AppConstants_

/* 
	define MAX and MIN as macros, if not already defined 
	The heavy use of parenthesis allows either x or y to be an expression
*/
#ifndef MIN
#define		MIN(a,b)		((a <= b) ? a : b)
#endif

/* ### kwgm 5.17.90 - unused in GenApp */
#if 0
#ifndef MAX
#define		MAX(a,b)		((a >= b) ? a : b)
#endif
#endif
/* ### kwgm 5.17.90 */

/* ----------------------  Window/Scroll Bar stuff  ----------------------------- */

#define		kScrollBarSize		16
#define		kControlMax			1000
#define		kHScrollTag			1
#define		kVScrollTag			2

#define		kMaxOpenDocs		32

/* -----------------------  Document attributes  ------------------------------- */

#define	kDocDirty		0x0001		/* the-doc-has-been-changed flag */

/* ### kwgm 5.17.90 - new stuff to support text and pict documents */
#define	kDocText		0x0010		/* text document flag */
#define	kDocPICT		0x0020		/* picture document flag */
#define	kDocTypeMask	0x0030

/* macros to test doc type */
#define	ISPICTDOC(d)	((((DocPtr)d)->type & kDocPICT) ? true : false)
#define	ISTEXTDOC(d)	((((DocPtr)d)->type & kDocText) ? true : false)
/* ### kwgm 5.17.90 */

#define	ISDIRTY(d)	((((DocPtr)d)->attributes & kDocDirty) ? true : false)

/* --------------------   Dialog Resources  ------------------------------------ */

#define	kSetButtonID			1
#define	kCancelButtonID			2

#define	kSaveChangeDLOG			64
#define	kSaveChangeOK			1
#define	kSaveChangeDont			2
#define	kSaveChangeCancel		4

#define kNotEnufMem				256
#define	kUnknownMach			257

#define kAboutBoxDLOG			600
#define	kAboutMemBox	  		2

#define	kDebugMsgDLOG			1000
#define	kDebugMsgCancel			2
#define	kDebugMsgExit			3
#define	kDebugMsgOKOutline		7


/* -------------------  Other Resources  -------------------------------------- */
/* ### kwgm 5.17.90 */
#define	kDocPictureID		256
#define	kDocTextID			256

#endif
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */