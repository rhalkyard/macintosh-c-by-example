/* *****************************************************************************
	FILE: 			BrowserConstants.h
	
	DESCRIPTION: 	Browser global constants

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */

#ifndef _BrowserConstants_
#define _BrowserConstants_

#define		NIL					0L
#define		kNulPascalStr		"\p"

/* 
	define MAX and MIN as macros, if not already defined 
	The heavy use of parenthesis allows either x or y to be an expression
*/
#ifndef MIN
#define		MIN(a,b)		((a <= b) ? a : b)
#endif

/* -----------------------  Document attributes  ------------------------------- */
#define	kDocRsrcFork		0x0010		/* resource fork document flag */
#define	kDocDataFork		0x0020		/* data fork document flag */
#define	kDocTypeMask		0x0030
#define	kBinaryMode			0x0001
#define	kTextMode			0x0002
#define	kBrowserModeMask	0x0003

/* macros to test doc type */
#define	ISRSRCDOC(d)	((((DocPtr)d)->type & kDocRsrcFork) ? true : false)
#define	ISDATADOC(d)	((((DocPtr)d)->type & kDocDataFork) ? true : false)
#define	ISTEXTDOC(d)	((((DocPtr)d)->type & kTextMode) ? true : false)
#define	ISBINDOC(d)		((((DocPtr)d)->type & kBinaryMode) ? true : false)


/* ----------------------  Window/Scroll Bar stuff  ----------------------------- */

#define		kScrollBarSize		16
#define		kControlMax			1000
#define		kHScrollTag			1
#define		kVScrollTag			2

#define		kMaxOpenDocs		32


/* --------------------   Dialog Resources  ------------------------------------ */

#define	kSetButtonID			1
#define	kCancelButtonID			2

#define kSetButton				 kSetButtonID
#define	kCancelButton			 kCancelButtonID
#define	kOutlineButton			 3


#define		kBinaryGetFileDLOG			65
#define 	kBRsrcButton				15
#define		kBDataButton				16

#define		kTextGetFileDLOG			66

#define		kGetFileOutline				13		
#define		kGetFileSepLine				14

#define kNotEnufMem				256
#define	kUnknownMach			257

#define kAboutBoxDLOG			600
#define	kAboutMemBox	  		2

#define	kDebugMsgDLOG			1000
#define	kDebugMsgCancel			2
#define	kDebugMsgExit			3
#define	kDebugMsgOKOutline		7

#define	kIOErrDLOG				1001

#endif
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */