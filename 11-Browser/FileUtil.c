/* *****************************************************************************
	FILE: 			FileUtil.c
	
	DESCRIPTION: 	File I/O utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */
#include "BrowserConstants.h"
#include "StrRsrcDefs.h"

#include "FileErrPr.h"
#include "MiscUtilPr.h"

#include "FileUtilPr.h"

/* --------------------------------------------------------------------------------------
	openFile	-	open a file, get file size, seek to beginning, 
	6.20.90kwgm		return file reference number
----------------------------------------------------------------------------------------- */
OSErr
openFile (DocParamsPtr docParams)
{
	OSErr				err;
	long				fSize;
	short				vRefNum;
	Str64				volName;
	FileParamsPtr		fileParams;
	
	fileParams = &docParams->fileParams;
	
	if (err = SetVol (0L, fileParams->volRefNum))	/* set vol to passed value */
	{
		doFileCantAlert (fileParams->fileName, kOpen, err, kNulPascalStr);
		return (err);
	}
	
	/* open the file */
	if (docParams->attributes & kDocDataFork)
	{
		if (err = FSOpen (fileParams->fileName, fileParams->volRefNum, &fileParams->openFileRefNum))
		{
			doFileCantAlert (fileParams->fileName, kOpen, err, kNulPascalStr);
			return (err);
		}
	}
	else
	{
		if (err = OpenRF (fileParams->fileName, fileParams->volRefNum, &fileParams->openFileRefNum))
		{
			doFileCantAlert (fileParams->fileName, kOpen, err, kNulPascalStr);
			return (err);
		}
	}

	/* get the file size */
	if (err = GetEOF (fileParams->openFileRefNum, &fileParams->fileSize))
	{
		doFileCantAlert (fileParams->fileName, kOpen, err, kNulPascalStr);
		FSClose (fileParams->openFileRefNum);
		return (err);
	}

	/* set the 'mark' to the beginning of the file */
	if (err = SetFPos (fileParams->openFileRefNum, fsFromStart, 0L))
	{
		doFileCantAlert (fileParams->fileName, kOpen, err, kNulPascalStr);
		FSClose (fileParams->openFileRefNum);
		return (err);
	}

	return (noErr);
	
} /* openFile */

/* -------------------------------------------------------------------------------------
	closeDocFile	-	close the file associated with a document
	9.20.90kwgm
---------------------------------------------------------------------------------------- */
OSErr
closeDocFile (theDoc)
	DocPtr			theDoc;
{
	OSErr			err;
	
	err = noErr;
	
	if (theDoc->openFileRefNum > 0)
	{
		if ((err = FSClose (theDoc->openFileRefNum)) == noErr)
		{
			theDoc->openFileRefNum = 0;
			err = FlushVol (0L, theDoc->volRefNum);
		}
	}

	return (err);

} /* closeFile */

/* ----------------------------------------------------------------------
	readFile -	read len bytes into buffer from an open file
	6.20.90kwgm
------------------------------------------------------------------------- */
OSErr
readFile (openFileRefNum, buffer, len)
	short	openFileRefNum;
	uchar 	*buffer;
	Size	*len;
{
	OSErr	err;

	return (err = FSRead (openFileRefNum, len, buffer));
}


/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */	

