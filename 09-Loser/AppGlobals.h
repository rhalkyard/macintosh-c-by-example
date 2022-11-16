/* *****************************************************************************
	FILE: 			AppGlobals.h
	
	DESCRIPTION: 	Application global variables declaration and definitions

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	5.28.90	-	Sept 1990 MacUser Release (Loser)
	==========================================================

   ***************************************************************************** */
#ifndef _AppGlobals_
#define	_AppGlobals_


#ifdef _Main_Module_
#define SCOPE /*GLOBAL*/
#else
#define SCOPE extern
#endif
	
#include "AppTypes.h"


SCOPE		Boolean				gDevel;				/* development flag */							
SCOPE		Rect				gScreenRect;		/* the main device screen rect */

#undef _main_module

#endif
/* ==================================  EOF  ====================================
 		Copryright © 1990 Kurt W.G. Matthies,  All Rights Reserved
   ============================================================================= */