/* *****************************************************************************
	FILE: 			AppTypes.h
	
	DESCRIPTION: 	Application type definitions

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	5.28.90	-	Sept 1990 MacUser Release (Loser)
	==========================================================

   ***************************************************************************** */
#ifndef _AppTypes_
#define _AppTypes_

#define uchar	unsigned char
#define ushort	unsigned short
#define ulong	unsigned long

typedef unsigned char Str16 [17];
typedef unsigned char Str64 [65];

typedef uchar	pBoolean;

typedef struct FileParams {
	short		fileRefNum,
				volRefNum;
	Size		fileSize;
	char		fileName [33];
} FileParams, *FileParamsPtr;

typedef struct DocParams {
	ushort		attributes;
	FileParams	fileParams,
				outputFileParams;
} DocParams, *DocParamsPtr;

#endif
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */