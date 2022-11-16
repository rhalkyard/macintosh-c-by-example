#define ALRT_RezTemplateVersion 0
#define DLOG_RezTemplateVersion 0

#include "Types.r"

resource 'ALRT' (256, "No RAM") {
	{46, 56, 134, 392},
	256,
	{	/* array: 4 elements */
		/* [1] */
		OK, invisible, silent,
		/* [2] */
		OK, invisible, silent,
		/* [3] */
		OK, invisible, silent,
		/* [4] */
		Cancel, visible, sound2
	}
};

resource 'ALRT' (257, "Unknown Mach") {
	{46, 56, 134, 392},
	257,
	{	/* array: 4 elements */
		/* [1] */
		OK, invisible, silent,
		/* [2] */
		OK, invisible, silent,
		/* [3] */
		OK, invisible, silent,
		/* [4] */
		Cancel, visible, sound2
	}
};

resource 'DITL' (256, "No RAM") {
	{	/* array DITLarray: 2 elements */
		/* [1] */
		{12, 101, 78, 320},
		StaticText {
			disabled,
			"Sorry,  but this application can't find "
			"enough available RAM to load in the curr"
			"ent machine configuration."
		},
		/* [2] */
		{57, 20, 77, 80},
		Button {
			enabled,
			"Finder"
		}
	}
};

resource 'DITL' (600, "About") {
	{	/* array DITLarray: 2 elements */
		/* [1] */
		{0, 0, 166, 300},
		Picture {
			enabled,
			600
		},
		/* [2] */
		{140, 16, 156, 240},
		UserItem {
			disabled
		}
	}
};

resource 'DITL' (1000, "pError") {
	{	/* array DITLarray: 9 elements */
		/* [1] */
		{133, 48, 153, 119},
		Button {
			enabled,
			"Continue"
		},
		/* [2] */
		{132, 148, 153, 274},
		Button {
			enabled,
			"Cancel Operation"
		},
		/* [3] */
		{132, 297, 153, 389},
		Button {
			enabled,
			"Exit to Shell"
		},
		/* [4] */
		{41, 39, 61, 375},
		StaticText {
			disabled,
			"^0"
		},
		/* [5] */
		{73, 39, 113, 376},
		StaticText {
			disabled,
			"^1"
		},
		/* [6] */
		{10, 117, 29, 275},
		StaticText {
			disabled,
			"Internal Error Advisory"
		},
		/* [7] */
		{129, 44, 157, 122},
		UserItem {
			disabled
		},
		/* [8] */
		{128, 144, 157, 277},
		UserItem {
			disabled
		},
		/* [9] */
		{128, 293, 157, 393},
		UserItem {
			disabled
		}
	}
};

resource 'DITL' (257, "Unknown Mach") {
	{	/* array DITLarray: 2 elements */
		/* [1] */
		{14, 98, 77, 332},
		StaticText {
			disabled,
			"The application cannot determine the mac"
			"hine type or the operating system versio"
			"n and must exit."
		},
		/* [2] */
		{56, 26, 76, 86},
		Button {
			enabled,
			"Finder"
		}
	}
};

resource 'DLOG' (600, "About") {
	{44, 30, 210, 330},
	dBoxProc,
	invisible,
	noGoAway,
	0x0,
	600,
	"About Generic"
};

resource 'DLOG' (1000, "pError") {
	{80, 114, 254, 536},
	dBoxProc,
	invisible,
	noGoAway,
	0x0,
	1000,
	""
};

resource 'FREF' (600) {
	'APPL',
	0,
	""
};

resource 'ICN#' (128) {
	{	/* array: 2 elements */
		/* [1] */
		$"FFFF FFFF 8000 0001 8000 0001 8000 0001"
		$"83FF FFC1 8200 0061 8200 0061 8200 0061"
		$"823F FC61 823F FC61 8230 07E1 8230 03E1"
		$"8230 0001 8230 0001 8230 0001 8230 1FC1"
		$"8230 1061 8230 1061 8230 1C61 8230 0461"
		$"8230 0461 823F FC61 8200 0061 8200 0061"
		$"8200 0061 83FF FFE1 81FF FFE1 8000 0001"
		$"8000 0001 8000 0001 8000 0001 FFFF FFFF",
		/* [2] */
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	}
};

resource 'BNDL' (600) {
	'GNAP',
	0,
	{	/* array TypeArray: 2 elements */
		/* [1] */
		'ICN#',
		{	/* array IDArray: 1 elements */
			/* [1] */
			0, 600
		},
		/* [2] */
		'FREF',
		{	/* array IDArray: 1 elements */
			/* [1] */
			0, 600
		}
	}
};

resource 'MENU' (3, "Edit") {
	3,
	textMenuProc,
	0x7FFFFFFD,
	enabled,
	"Edit",
	{	/* array: 6 elements */
		/* [1] */
		"Undo", noIcon, "Z", noMark, plain,
		/* [2] */
		"-", noIcon, noKey, noMark, plain,
		/* [3] */
		"Cut", noIcon, "X", noMark, plain,
		/* [4] */
		"Copy", noIcon, "C", noMark, plain,
		/* [5] */
		"Paste", noIcon, "V", noMark, plain,
		/* [6] */
		"Clear", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (2, "File") {
	2,
	textMenuProc,
	0x7FFFFFF5,
	enabled,
	"File",
	{	/* array: 5 elements */
		/* [1] */
		"New...", noIcon, "N", noMark, plain,
		/* [2] */
		"-", noIcon, noKey, noMark, plain,
		/* [3] */
		"Close", noIcon, "W", noMark, plain,
		/* [4] */
		"-", noIcon, noKey, noMark, plain,
		/* [5] */
		"Quit", noIcon, "Q", noMark, plain
	}
};

resource 'MENU' (1, "Apple") {
	1,
	textMenuProc,
	0x7FFFFFFD,
	enabled,
	apple,
	{	/* array: 2 elements */
		/* [1] */
		"About GenericÔøΩ", noIcon, noKey, noMark, plain,
		/* [2] */
		"-", noIcon, noKey, noMark, plain
	}
};

data 'GNAP' (0, "Signature") {
	$"2347 656E 7269 6320 4170 7020 A920 3139"            /* #Genric App ÔøΩ 19 */
	$"3930 204B 7572 7420 572E 472E 204D 6174"            /* 90 Kurt W.G. Mat */
	$"7468 6965 73"                                       /* thies */
};

resource 'STR#' (256, "Mem Error") {
	{	/* array StringArray: 8 elements */
		/* [1] */
		"The Memory Manager Has Reported an Error"
		": ",
		/* [2] */
		"Unknown Error ID: ",
		/* [3] */
		"No Error!",
		/* [4] */
		"Block is read-only",
		/* [5] */
		"Out of room in heap zone",
		/* [6] */
		"Block has a NIL master pointer",
		/* [7] */
		"Block has not been allocated",
		/* [8] */
		"Block is locked"
	}
};

resource 'STR#' (100, "Names") {
	{	/* array StringArray: 2 elements */
		/* [1] */
		"Untitled",
		/* [2] */
		"%ld K Available Memory"
	}
};

resource 'vers' (2) {
	0x1,
	0x10,
	release,
	0x1,
	verUS,
	"1.1",
	""
};

resource 'vers' (1) {
	0x1,
	0x10,
	release,
	0x2,
	verUS,
	"1.1",
	"multiGeneric App - Version 1.1 ÔøΩ 1990 Ku"
	"rt W.G. Matthies"
};

resource 'PICT' (600, "About") {
	2604,
	{128, 139, 294, 439},
	$"1101 A000 8201 000A 0000 0000 02D0 0240"
	$"9800 2600 8000 8801 2601 B800 8000 8B01"
	$"2601 B700 8000 8B01 2601 B700 0002 DB00"
	$"0600 0FDD FF00 FC06 000F DDFF 00FC 0600"
	$"0FDD FF00 FC06 000F DDFF 00FC 0600 0FDD"
	$"FF00 FC06 000F DDFF 00FC 0600 0FDD FF00"
	$"FC06 000F DDFF 00FC 0600 0FDD FF00 FC06"
	$"000F DDFF 00FC 0600 0FDD FF00 FC06 000F"
	$"DDFF 00FC 0600 0FDD FF00 FC06 000F DDFF"
	$"00FC 0600 0FDD FF00 FC06 000F DDFF 00FC"
	$"0600 0FDD FF00 FC06 000F DDFF 00FC 0600"
	$"0FDD FF00 FC06 000F DDFF 00FC 0600 0FDD"
	$"FF00 FC06 000F DDFF 00FC 0600 0FDD FF00"
	$"FC06 000F DDFF 00FC 0600 0FDD FF00 FC06"
	$"000F DDFF 00FC 0600 0FDD FF00 FC06 000F"
	$"DDFF 00FC 0600 0FDD FF00 FC06 000F DDFF"
	$"00FC 0600 0FDD FF00 FC06 000F DDFF 00FC"
	$"0600 0FDD FF00 FC06 000F DDFF 00FC 0600"
	$"0FDD FF00 FC06 000F DDFF 00FC 0600 0FDD"
	$"FF00 FC06 000F DDFF 00FC 0600 0FDD FF00"
	$"FC06 000F DDFF 00FC 0600 0FDD FF00 FC1D"
	$"170F FFFE 1878 000C 0F00 C000 6003 FF00"
	$"FC61 FFFC 1FE0 03F0 01F4 FF00 FC1E 180F"
	$"FFFC 0878 000C 0F00 C000 6000 FF00 F021"
	$"FFFC 1FE0 00F0 007F F5FF 00FC 1E18 0FFF"
	$"F808 7800 0C0F 00C0 0060 007F 00E0 21FF"
	$"FC1F E000 7000 3FF5 FF00 FC1E 180F FFF8"
	$"0078 000C 0F00 C000 6000 7F00 E001 FFFC"
	$"1FE0 0070 003F F5FF 00FC 1E18 0FFF F000"
	$"7800 0C07 00C0 0060 003F 00C0 01FF FC1F"
	$"E000 3000 1FF5 FF00 FC1E 180F FFF0 0078"
	$"000C 0700 C000 6000 3F00 C001 FFFC 1FE0"
	$"0030 001F F5FF 00FC 1E18 0FFF F000 7800"
	$"0C07 00C0 0060 003F 00C0 01FF F80F E000"
	$"3000 1FF5 FF00 FC1E 180F FFF0 0078 000C"
	$"0700 C000 6000 3F00 C001 FFF8 0FE0 0030"
	$"001F F5FF 00FC 1E18 0FFF F000 7800 0C03"
	$"00C0 0060 003F 00C0 01FF F80F E000 3000"
	$"1FF5 FF00 FC1E 180F FFF0 707E 1F0C 0300"
	$"F0F8 7878 3F00 C1C1 FFF8 0FF8 783C 3C1F"
	$"F5FF 00FC 1E18 0FFF F0F8 7E1F 0F03 C3F0"
	$"F878 7C3F C3C3 E1FF F80F F87C 3C3E 1FF5"
	$"FF00 FC1E 180F FFF0 F87E 1F0F 03C3 F0F8"
	$"787C 3FC3 C3E1 FFF8 0FF8 7C3C 3E1F F5FF"
	$"00FC 1E18 0FFF F0F8 7E1F 0F01 C3F0 F878"
	$"7C3F C3C3 E1FF F80F F87C 3C3E 1FF5 FF00"
	$"FC1E 180F FFF0 F87E 1F0F 01C3 F0F8 787C"
	$"3FC3 C3E1 FFF0 07F8 7C3C 3E1F F5FF 00FC"
	$"1E18 0FFF F0F8 7E1F 0F01 C3F0 F878 7C3F"
	$"C3C3 E1FF F007 F87C 3C3E 1FF5 FF00 FC1E"
	$"180F FFF0 F87E 1F0F 01C3 F0F8 787C 3FC3"
	$"C3E1 FFF0 07F8 7C3C 3E1F F5FF 00FC 1E18"
	$"0FFF F0FF FE1F FF00 C3F0 FFF8 7C3F C3C3"
	$"FFFF F007 F87C 3C3E 1FF5 FF00 FC1E 180F"
	$"FFF0 FFFE 1FFF 00C3 F0FF F87C 3FC3 C3FF"
	$"FFF0 87F8 7C3C 3E1F F5FF 00FC 1E18 0FFF"
	$"F0FF FE1F FF00 C3F0 FFF8 7C3F C3C3 FFFF"
	$"F087 F87C 3C3E 1FF5 FF00 FC1E 180F FFF0"
	$"FFFE 003F 00C3 F001 F878 7FC3 C3FF FFF0"
	$"83F8 7C3C 3E1F F5FF 00FC 1E18 0FFF F0E0"
	$"1E00 3F00 43F0 01F8 007F C3C3 FFFF E083"
	$"F878 3C3C 1FF5 FF00 FC1E 180F FFF0 E01E"
	$"003F 0043 F001 F801 FFC3 C3FF FFE0 83F8"
	$"003C 001F F5FF 00FC 1E18 0FFF F0E0 1E00"
	$"3F08 43F0 01F8 00FF C3C3 FFFF E1C3 F800"
	$"7C00 3FF5 FF00 FC1E 180F FFF0 E01E 003F"
	$"0803 F001 F800 FFC3 C3FF FFE1 C3F8 007C"
	$"003F F5FF 00FC 1E18 0FFF F0E0 1E1F FF08"
	$"03F0 FFF8 007F C3C3 FFFF E1C3 F800 FC00"
	$"7FF5 FF00 FC1D 170F FFF0 F87E 1FFF 0C03"
	$"F0FF F870 7FC3 C3FF FFE1 C3F8 03FC 01F4"
	$"FF00 FC1D 170F FFF0 F87E 1FFF 0C03 F0FF"
	$"F878 7FC3 C3FF FFE1 C3F8 7FFC 3FF4 FF00"
	$"FC1D 170F FFF0 F87E 1FFF 0C03 F0FF F878"
	$"7FC3 C3FF FFE0 03F8 7FFC 3FF4 FF00 FC1D"
	$"170F FFF0 F87E 1F0F 0C03 F0F8 7878 7FC3"
	$"C3E1 FFC0 01F8 7FFC 3FF4 FF00 FC1D 170F"
	$"FFF0 F87E 1F0F 0E03 F0F8 7878 7FC3 C3E1"
	$"FFC0 01F8 7FFC 3FF4 FF00 FC1D 170F FFF0"
	$"F87E 1F0F 0E03 F0F8 7878 7FC3 C3E1 FFC0"
	$"01F8 7FFC 3FF4 FF00 FC1D 170F FFF0 F87E"
	$"1F0F 0E03 F0F8 7878 7FC3 C3E1 FFC3 E1F8"
	$"7FFC 3FF4 FF00 FC1D 170F FFF0 F87E 1F0F"
	$"0E03 F0F8 7878 73C3 C3E1 FFC3 E1F8 7FFC"
	$"3FF4 FF00 FC1D 170F FFF0 F87E 1F0F 0F03"
	$"F0F8 7878 73C3 C3E1 FFC3 E1F8 7FFC 3FF4"
	$"FF00 FC1D 170F FFF0 F87E 1F0F 0F03 F0F8"
	$"7878 73C3 C3E1 FFC3 E1F8 7FFC 3FF4 FF00"
	$"FC1D 170F FFF0 707E 1F0F 0F03 F0F8 7878"
	$"23C3 C1C1 FFC3 E1F8 7FFC 3FF4 FF00 FC1D"
	$"170F FFF0 0078 000C 0303 C000 6018 0300"
	$"C001 FF00 8060 1FF0 0FF4 FF00 FC1D 170F"
	$"FFF0 0078 000C 0383 C000 6018 0300 C001"
	$"FF00 8060 1FF0 0FF4 FF00 FC1D 170F FFF0"
	$"0078 000C 0383 C000 6018 0300 C001 FF00"
	$"8060 1FF0 0FF4 FF00 FC1D 170F FFF0 0078"
	$"000C 0383 C000 6018 0300 C001 FF00 8060"
	$"1FF0 0FF4 FF00 FC1D 170F FFF0 0078 000C"
	$"0383 C000 6018 0300 C001 FF00 8060 1FF0"
	$"0FF4 FF00 FC1D 170F FFF8 0078 000C 03C3"
	$"C000 6018 0300 E003 FF00 8060 1FF0 0FF4"
	$"FF00 FC1D 170F FFF8 0478 000C 03C3 C000"
	$"601C 0700 E003 FF00 8060 1FF0 0FF4 FF00"
	$"FC1D 170F FFFC 0478 000C 03C3 C000 601C"
	$"0700 F007 FF00 8060 1FF0 0FF4 FF00 FC1D"
	$"170F FFFF 0C78 000C 03C3 C000 601E 0F00"
	$"FC1F FF00 8060 1FF0 0FF4 FF00 FC06 000F"
	$"DDFF 00FC 0600 0FDD FF00 FC06 000F DDFF"
	$"00FC 0600 0FDD FF00 FC06 000F DDFF 00FC"
	$"0600 0FDD FF00 FC06 000F DDFF 00FC 0600"
	$"0FDD FF00 FC06 000F DDFF 00FC 0600 0FDD"
	$"FF00 FC06 000F DDFF 00FC 0600 0FDD FF00"
	$"FC06 000F DDFF 00FC 0600 0FDD FF00 FC06"
	$"000F DDFF 00FC 2703 0FFF FC3F FEFF 06E7"
	$"FE7F 3FE1 FF9F FE0F 10E7 FFFE 73FF FE7F"
	$"333F 87FF 7FBF F9E7 3F3F FEFF 00FC 2503"
	$"0FFF F9DF FDFF 18FE 7F3F DEFF 1E66 6667"
	$"E7FF FE67 FFFE 7F33 3F3B FF3F 3FF9 E73F"
	$"FDFF 00FC 2725 0FFF F9FC 3839 9927 060E"
	$"1FB3 7F9E 6666 67E0 E67E 4F33 243F 333F"
	$"3FFF 1E38 70C3 0738 78FF FFFC 271F 0FFF"
	$"F9F9 9999 98E6 6667 3FAD 7F9E 6666 67E6"
	$"667E 1F33 1E7F 333F 3FFF 0C37 39E7 FE33"
	$"027F FFFC 2703 0FFF F9F9 FE99 1EE6 6667"
	$"3FAF 7F9E 6666 67E6 667E 3F33 3E7F 333F"
	$"23FF 4138 39E7 3333 31FF FFFC 2703 0FFF"
	$"F9F9 FE99 1EE6 6667 3FAD 7F9F 0706 67E6"
	$"667E 1F33 3E7F 333F 33FF 6333 39E7 3330"
	$"38FF FFFC 2703 0FFF F9F9 FE99 1EE6 6667"
	$"3FB3 7F9F E7E6 67E6 667E 4F33 3E7F 333F"
	$"33FF 7733 39E7 3333 FC7F FFFC 2703 0FFF"
	$"F9D9 FE99 1EE6 6667 3FDE FF9F CFCE 67E6"
	$"667E 6733 3E7F 3373 333F 7F33 39E7 3333"
	$"B67F FFFC 2725 0FFF FC3C 383C 19E7 0667"
	$"9FE1 FF9F 1F1F 0FE0 F07E 7383 3F3F 00F3"
	$"873F 7F38 3CF3 3338 78FF FFFC 1300 0FFE"
	$"FF04 F9FF 9FFF E7F8 FF01 FE7F F0FF 00FC"
	$"1300 0FFE FF04 F9FB 9FFE E7F8 FF01 EE7F"
	$"F0FF 00FC 1100 0FFD FF03 FC3F FF0F F8FF"
	$"00F0 EFFF 00FC 0600 0FDD FF00 FC06 000F"
	$"DDFF 00FC 0600 0FDD FF00 FC06 000F DDFF"
	$"00FC 0600 0FDD FF00 FC06 000F DDFF 00FC"
	$"0600 0FDD FF00 FC06 000F DDFF 00FC 0600"
	$"0FDD FF00 FC06 000F DDFF 00FC 0600 0FDD"
	$"FF00 FC06 000F DDFF 00FC 0600 0FDD FF00"
	$"FC06 000F DDFF 00FC 0600 0FDD FF00 FC06"
	$"000F DDFF 00FC 0600 0FDD FF00 FC06 000F"
	$"DDFF 00FC 0600 0FDD FF00 FC06 000F DDFF"
	$"00FC 0600 0FDD FF00 FC06 000F DDFF 00FC"
	$"0600 0FDD FF00 FC06 000F DDFF 00FC 0600"
	$"0FDD FF00 FC06 000F DDFF 00FC 0600 0FDD"
	$"FF00 FC06 000F DDFF 00FC 0600 0FDD FF00"
	$"FC06 000F DDFF 00FC 0600 0FDD FF00 FC06"
	$"000F DDFF 00FC 0600 0FDD FF00 FC06 000F"
	$"DDFF 00FC 0600 0FDD FF00 FC06 000F DDFF"
	$"00FC 0600 0FDD FF00 FC06 000F DDFF 00FC"
	$"0600 0FDD FF00 FC06 000F DDFF 00FC 0600"
	$"0FDD FF00 FC06 000F DDFF 00FC 0600 0FDD"
	$"FF00 FC06 000F DDFF 00FC 0600 0FDD FF00"
	$"FC06 000F DDFF 00FC 0600 0FDD FF00 FC06"
	$"000F DDFF 00FC 0600 0FDD FF00 FC06 000F"
	$"DDFF 00FC 0600 0FDD FF00 FC02 DB00 A000"
	$"83FF"
};

