/* *****************************************************************************
	FILE: 			WindowTblPr.h
	
	DESCRIPTION: 	Window table management prototypes

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */

#ifndef _WindowTblPr_
#define _WindowTblPr_

void			initDocList			( void );
void			addToDocList		( DocPtr );
void			removeFromDocList	( DocPtr );
void			menuSelectDoc	( short );
void			fixWindowMenu	( DocPtr );
void			uncheckItems	( MenuHandle );
void			doWindowMenu	( short );
DocPtr			findOpenDoc 	( DocParamsPtr );
Boolean			closeAllDocs 	( void );

#endif
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */