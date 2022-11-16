/* *****************************************************************************
	FILE: 			AppTypes.h
	
	DESCRIPTION: 	Application type definitions

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#ifndef _AppTypes_
#define _AppTypes_

#include "Version.h"

#ifdef V5
#include <Types.h>
#else
#include <MacTypes.h>
#endif

#ifdef V2
#include <WindowMgr.h>
#endif

#define uchar	unsigned char		/* convienient definitions */
#define ushort	unsigned short
#define ulong	unsigned long

typedef struct Doc				/* document data structure */
{
	WindowRecord	window;
	ushort 			type,				/* window type */
					attributes;			/* Document attributes */
	Point			curScroll,			/* current scroll position */
					maxScroll;			/* maximum scroll position */
	short			index;				/* index in open window table */
	short			volRefNum;			/* vol ref num  of open file */
	short			openFileRefNum;		/* file reference num of open file */
	char			fileName [33];		/* filename */
} Doc, *DocPtr;


/* 
	FileParams and DocParams structures are used to open 
	files and associate them with windows
*/

typedef struct FileParams 
{
	short		openFileRefNum,
				volRefNum;
	char		fileName [33];
} FileParams, *FileParamsPtr;

typedef struct DocParams 
{
	ushort		attributes;
	FileParams	fileParams;
} DocParams, *DocParamsPtr;

#endif
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */