/* *****************************************************************************
	FILE: 			StrRsrcDefs.h
	
	DESCRIPTION: 	Str# Resource definitions

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	6/1/90	-	MacUser Release
	==========================================================

   ***************************************************************************** */

#ifndef _StrRsrcDefs_
#define _StrRsrcDefs_

#define		kNameStrRsrc			16
#define		kNameUntitledStr		1

#define		kMsgStrID			 	64
#define		kMsgPromptStr		  	1

#define		kIOMsgStrID			104		/*  STR# 104, I/O Msg codes  */
#define		kNoErr				0
#define		kOpen				1
#define		kClose				2
#define 	kRead				3
#define 	kWrite				4
#define		kDelete				5
#define		kDirectoryFull		6
#define		kDiskFull			7
#define		kVolumeNotFound		8
#define		kDiskIOErr			9
#define		kBadFilename		10
#define		kEndOfFile			11
#define		kVolumeLocked		12
#define		kFileLocked			13
#define		kFileBusy			14
#define		kFileExists			15
#define		kFileNotFound		16
#define		kExternFSErr		17
#define		kIOMacErr			18

#define		kMemErrStrRsrc			256
#define		kMemErrMsgStr			1
#define		kMemErrUnknownStr		2
#define		kMemErrNoErrStr			3
#define		kMemErrReadOnlyStr		4
#define		kMemErrMemFullStr		5
#define		kMemErrNilHdlStr		6
#define		kMemErrFreeBlkStr		7
#define		kMemErrLockedBlkStr		8

#endif
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */