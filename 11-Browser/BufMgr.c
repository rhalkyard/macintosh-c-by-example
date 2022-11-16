/* *****************************************************************************
	FILE: 			BufMgr.c
	
	DESCRIPTION: 	Browser I/O buffer management routines

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.	
	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */
#include <Files.h>
#include <Memory.h>

#include "BrowserConstants.h"
#include "StrRsrcDefs.h"

#include "FileErrPr.h"
#include "FileUtilPr.h"
#include "MiscUtilPr.h"
#include "BufMgrPr.h"

#define kMaxBufSiz	32000L			/* textEdit max */
#define kBufSize		256L


static Boolean		fillFileBuffer		( DocPtr, Size );

/* ----------------------------------------------------------------------
	initFileBuffer - 	intialize a document's file buffer
	9.20.90kwgm
------------------------------------------------------------------------- */
Boolean
initFileBuffer (theDoc, docParamsPtr)
	DocPtr			theDoc;
	DocParamsPtr	docParamsPtr;
{
	Boolean			result;
	
	result = false;
	theDoc->fileSize = docParamsPtr->fileParams.fileSize;
	theDoc->fileOffset = 0L;
	
	if (docParamsPtr->attributes & kBinaryMode)
	{
		if (theDoc->contentHdl = newClearHdl (kBufSize))
			result = fillFileBuffer (theDoc, kBufSize);
	}
	else
	{
		if (theDoc->fileSize < kMaxBufSiz)	/* limit buf size */
		{
			if (theDoc->contentHdl = newClearHdl (theDoc->fileSize))
			{
				result = fillFileBuffer (theDoc, theDoc->fileSize);
			}
		}
	}			

	return (result);
			
} /* initFileBuffer */

/* ----------------------------------------------------------------------
	prevFileBuffer -	read the previous n * 256 bytes into the buffer
	11.22.90kwgm
------------------------------------------------------------------------- */
void
prevFileBuffer (DocPtr theDoc, long gobble)
{
	
	/* limit the read to the file size */
	if ((theDoc->fileOffset - (gobble * kBufSize)) < 0L)
		theDoc->fileOffset = 0L;
	else
		theDoc->fileOffset -= (gobble * kBufSize);

	fillFileBuffer (theDoc, kBufSize);

} /* prevFileBuffer */

/* ----------------------------------------------------------------------
	nextFileBuffer -	read the next 256 * gobble bytes into the buffer
	11.22.90kwgm
------------------------------------------------------------------------- */
void
nextFileBuffer (DocPtr theDoc, long gobble)
{
	
	/* limit the read to the file size */
	if ((theDoc->fileOffset + (gobble * kBufSize)) > theDoc->fileSize)
		theDoc->fileOffset = (theDoc->fileSize/kBufSize) * kBufSize;
	else
		theDoc->fileOffset += (gobble * kBufSize);

	fillFileBuffer (theDoc, kBufSize);

} /* nextFileBuffer */

/* ----------------------------------------------------------------------
	fillFileBuffer -	fill the file buffer with data
	9.20.90kwgm
------------------------------------------------------------------------- */
static Boolean
fillFileBuffer (theDoc, bufSize)
	DocPtr		theDoc;
	Size		bufSize;
{
	Size		bytesRead;
	OSErr		err;
	Boolean		result;
	
	result = false;

	err = SetFPos (theDoc->openFileRefNum, fsFromStart, theDoc->fileOffset);

	HLock (theDoc->contentHdl);
	bytesRead = bufSize;
	err = readFile (theDoc->openFileRefNum, *theDoc->contentHdl, &bytesRead);
	HUnlock (theDoc->contentHdl);

	if (err == noErr)
		result = true;
	else if (bytesRead != bufSize && err != eofErr)
	{
		doFileCantAlert (theDoc->fileName, kRead, result, kNulPascalStr);
		result = false;
	}

	return (result);
	
} /* fillBuffer */

/* ----------------------------------------------------------------------
	disposeFileBuffer - dispose of a document's file buffer
------------------------------------------------------------------------- */
void
disposeFileBuffer (theDoc)
	DocPtr		theDoc;
{
	disposeHdl (theDoc->contentHdl);
	theDoc->contentHdl = 0L;
} /* disposeFileBuffer */

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */