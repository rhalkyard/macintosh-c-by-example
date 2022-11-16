/* *****************************************************************************
	FILE: 			BrowserTypes.h
	
	DESCRIPTION: 	Browser type definitions

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */
#ifndef _BrowserTypes_
#define _BrowserTypes_
#include <TextEdit.h>
#include <Windows.h>

#include "Version.h"

#ifdef V5
#include <Types.h>
#else
#include <MacTypes.h>
#endif

/* these defines save you from typing 'unsigned' all the time */
#define uchar	unsigned char
#define ushort	unsigned short
#define ulong	unsigned long

/*
	some convienient string sizes to add to Str255 
	Be carefull that you don't overrun the end of objects of these types
*/
typedef unsigned char Str16 [17];		/* for very small strings */
typedef unsigned char Str64 [65];		/* moderate size strings */

/* 
	File Params and Doc Params are parameter blocks used in the creation of a new document
*/
/* the file params uniquely identify a file */
typedef struct FileParams {
	short		openFileRefNum,		/* open file reference number */
				volRefNum;			/* volume reference number */
	Size		fileSize;
	char		fileName [33];		/* file name */
} FileParams, *FileParamsPtr;

typedef struct DocParams {
	ushort		attributes;			/* general purpose flags */
	FileParams	fileParams;			/* file data */
} DocParams, *DocParamsPtr;

/* 
	The main collection of data is a document 
*/
typedef struct Doc {
	/* window data structure */
	WindowRecord	theWindow;
	
	/* document management information */
	ushort 			type,				/* document type */
					attributes;			/* document attributes */
	short			index;				/* index in open window table */
					
	/* display management information */
	Point			curScroll,			/* current scroll position */
					maxScroll,			/* maximum scroll position */
					docExtent,			/* pixel size of displayed contents */
					scrollVal;			/* scrollSize factor */
					
	short			textFont,
					textSize;
	Style			textFace;
	
	/* file linkages */
	short			volRefNum;			/* vol reference # of open file (vol and folder) */
	short			openFileRefNum;		/* file reference num of open file */
	char			fileName [33];		/* filename */
	
	long			fileSize,
					fileOffset;
	
	/* contents */
	Handle			contentHdl;			/* data associated with this document */
	TEHandle		textHdl;
	
} Doc, *DocPtr;

/* --------------------------  Window (View) Menu  document list  --------------- */
typedef struct DocInfo {
	DocPtr			theDoc;
	short			menuItem,
					slotNumber;
} DocInfo, *DocInfoPtr, **DocInfoHdl;
	
typedef struct DocList {
	short			count;
	DocInfo			docInfo [1];
} DocList, *DocListPtr, **DocListHdl;


#endif
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies All Rights Reserved.
================================================================================ */