/* *****************************************************************************
	FILE: 			Hey.c
	
	DESCRIPTION: 	Hey Mac source file accompanying Chapter 4

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © Kurt W.G. Matthies,  All Rights Reserved.
	
	Revision History:
	==========================================================
	8/20/91	-	Microsoft Press Release
	==========================================================
	

	Installation instructions: 
	--------------------------
	
	This code was developed in THINK C 4.0. You can't open
	the project file with earlier versions of the environment because of 
	the newer format. If you're using THINK C 5.0, the environment will
	automatically convert the project to the new format.
	
	To run this program with other versions you need to:
		1) Create a new project file named HeyMacπ
		2) Add Hey.c and MacTraps to the file. 
		3) Bring the project up to date.

   ***************************************************************************** */
#include <Quickdraw.h>
#define		kHelloString		"\pHey, mac!"

/* ------------------------- Local Prototypes ---------------------------------- */
void			main			( void );
void			initTheMac		( void );
WindowPtr		initWindow		( void );
void			sayHello		( WindowPtr );
void			getMouseDown	( void );

/* -----------------------------------------------------------------------------
	main -	program entry point
-------------------------------------------------------------------------------- */
void
main ()
{
	WindowPtr		theWindow;
	
	initTheMac ();
	
	if (theWindow = initWindow ())
	{
		sayHello (theWindow);
		
		getMouseDown ();
		
		DisposWindow (theWindow);
	}
	
	ExitToShell ();

} /* main */

/* -----------------------------------------------------------------------------
	initTheMac -	initialize the necessary managers for this to be a 
					stand-alone application
-------------------------------------------------------------------------------- */
void
initTheMac ()
{
	InitGraf (&thePort);
	InitWindows();
	InitFonts ();
	InitCursor ();
}
	
/* -----------------------------------------------------------------------------
	initWindow -	initialize a window for this application. Activate the 
					window and return the pointer to the window record. 
					return 0L on fail
-------------------------------------------------------------------------------- */
WindowPtr
initWindow ()
{
	WindowPtr	w;
	Rect		windowRect;
	
	SetRect (&windowRect, 40, 40, 340, 240);
	
	if (w = NewWindow (0L, &windowRect,"\p", true, dBoxProc, (WindowPtr)-1L, false, 0L))
		SetPort (w);

	return (w);
	
} /* initWindow */

/* -----------------------------------------------------------------------------
	sayHello -	print the hello world string in the center of theWindow
-------------------------------------------------------------------------------- */
void
sayHello (theWindow)
	WindowPtr		theWindow;
{
	Rect			windowRect;
	Point			penLoc;
	
	/* get the center of the window */
	windowRect = theWindow->portRect;
	penLoc.h = (windowRect.left + windowRect.right) / 2;
	penLoc.v = (windowRect.top + windowRect.bottom) / 2;
	
	/* offset the pen's horizontal location by half the string width */
	penLoc.h -= StringWidth (kHelloString) / 2;
	
	TextFont (0);
	TextFace (underline);
	TextSize (12);
	
	MoveTo (penLoc.h, penLoc.v);
	DrawString (kHelloString);
	SysBeep (1);
	
	TextFont (1);
	TextFace (0);
	TextSize (9);

	MoveTo (windowRect.left + 20, windowRect.bottom - 20);
	DrawString ("\pClick the mouse button to exit");
	
} /* sayHello */

/* -----------------------------------------------------------------------------
	getMouseDown -	wait for a mouse down event 
-------------------------------------------------------------------------------- */
void
getMouseDown ()
{
	EventRecord		eventRec;
	
	FlushEvents (everyEvent, 0);					/* clear the event queue */
	
	while (!GetNextEvent (mDownMask, &eventRec));	/* idle until a mouse down */
}

/* ===============================  EOF  =======================================
	Copyright © Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */