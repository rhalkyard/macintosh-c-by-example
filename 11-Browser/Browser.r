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
		{0, 0, 173, 304},
		Picture {
			enabled,
			600
		},
		/* [2] */
		{140, 20, 156, 240},
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

resource 'DITL' (1001, "IO Err") {
	{	/* array DITLarray: 7 elements */
		/* [1] */
		{129, 127, 149, 187},
		Button {
			enabled,
			"OK"
		},
		/* [2] */
		{12, 12, 44, 44},
		Icon {
			disabled,
			2
		},
		/* [3] */
		{125, 123, 153, 191},
		UserItem {
			disabled
		},
		/* [4] */
		{11, 56, 28, 306},
		StaticText {
			disabled,
			"Can't ^0 the file:"
		},
		/* [5] */
		{33, 56, 53, 305},
		StaticText {
			disabled,
			"^1"
		},
		/* [6] */
		{82, 12, 120, 306},
		StaticText {
			disabled,
			"^2 ^3"
		},
		/* [7] */
		{58, 12, 78, 72},
		StaticText {
			disabled,
			"Reason:"
		}
	}
};

resource 'DITL' (65, "Binary GetFile", purgeable) {
	{	/* array DITLarray: 17 elements */
		/* [1] */
		{127, 248, 147, 312},
		Button {
			enabled,
			"Open"
		},
		/* [2] */
		{0, 571, 80, 589},
		Button {
			enabled,
			"Hidden"
		},
		/* [3] */
		{156, 249, 176, 313},
		Button {
			enabled,
			"Cancel"
		},
		/* [4] */
		{94, 219, 114, 338},
		UserItem {
			disabled
		},
		/* [5] */
		{219, 248, 239, 312},
		Button {
			enabled,
			"Eject"
		},
		/* [6] */
		{193, 248, 213, 312},
		Button {
			enabled,
			"Drive"
		},
		/* [7] */
		{94, 18, 240, 214},
		UserItem {
			enabled
		},
		/* [8] */
		{94, 18, 240, 45},
		UserItem {
			disabled
		},
		/* [9] */
		{108, 536, 110, 624},
		UserItem {
			disabled
		},
		/* [10] */
		{0, 532, 101, 628},
		StaticText {
			disabled,
			""
		},
		/* [11] */
		{210, 320, 222, 335},
		UserItem {
			disabled
		},
		/* [12] */
		{0, 0, 66, 332},
		Picture {
			disabled,
			65
		},
		/* [13] */
		{123, 244, 151, 316},
		UserItem {
			disabled
		},
		/* [14] */
		{182, 241, 185, 321},
		UserItem {
			disabled
		},
		/* [15] */
		{253, 19, 271, 133},
		RadioButton {
			enabled,
			"Resource Fork"
		},
		/* [16] */
		{253, 147, 271, 253},
		RadioButton {
			enabled,
			"Data Fork"
		},
		/* [17] */
		{6, 92, 22, 182},
		StaticText {
			disabled,
			"Binary Mode"
		}
	}
};

resource 'DITL' (66, "Text GetFile", purgeable) {
	{	/* array DITLarray: 15 elements */
		/* [1] */
		{127, 248, 147, 312},
		Button {
			enabled,
			"Open"
		},
		/* [2] */
		{0, 571, 80, 589},
		Button {
			enabled,
			"Hidden"
		},
		/* [3] */
		{156, 249, 176, 313},
		Button {
			enabled,
			"Cancel"
		},
		/* [4] */
		{94, 219, 114, 338},
		UserItem {
			disabled
		},
		/* [5] */
		{219, 248, 239, 312},
		Button {
			enabled,
			"Eject"
		},
		/* [6] */
		{193, 248, 213, 312},
		Button {
			enabled,
			"Drive"
		},
		/* [7] */
		{94, 18, 240, 214},
		UserItem {
			enabled
		},
		/* [8] */
		{94, 18, 240, 45},
		UserItem {
			disabled
		},
		/* [9] */
		{108, 536, 110, 624},
		UserItem {
			disabled
		},
		/* [10] */
		{0, 532, 101, 628},
		StaticText {
			disabled,
			""
		},
		/* [11] */
		{210, 320, 222, 335},
		UserItem {
			disabled
		},
		/* [12] */
		{0, 0, 66, 332},
		Picture {
			disabled,
			65
		},
		/* [13] */
		{123, 244, 151, 316},
		UserItem {
			disabled
		},
		/* [14] */
		{182, 241, 185, 321},
		UserItem {
			disabled
		},
		/* [15] */
		{6, 92, 22, 167},
		StaticText {
			disabled,
			"Text Mode"
		}
	}
};

resource 'DLOG' (600, "About") {
	{44, 30, 214, 332},
	dBoxProc,
	invisible,
	noGoAway,
	0x0,
	600,
	""
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

resource 'DLOG' (1001, "IO Err") {
	{40, 40, 200, 360},
	dBoxProc,
	invisible,
	noGoAway,
	0x0,
	1001,
	""
};

resource 'DLOG' (65, "Binary GetFile", purgeable) {
	{32, 46, 312, 388},
	dBoxProc,
	invisible,
	noGoAway,
	0x0,
	65,
	""
};

resource 'DLOG' (66, "Text GetFile", purgeable) {
	{32, 46, 312, 388},
	dBoxProc,
	invisible,
	noGoAway,
	0x0,
	66,
	""
};

resource 'FREF' (600) {
	'APPL',
	0,
	""
};

resource 'ICN#' (600) {
	{	/* array: 2 elements */
		/* [1] */
		$"0FFF F800 0800 0C00 0800 0A00 0800 0900"
		$"0800 0880 0800 0840 0800 0820 0800 0FF0"
		$"0800 0010 081E 0010 086B 8010 08AA 4010"
		$"09AE 6010 0A00 1010 0AEC 7010 0C8A 1810"
		$"0CEC 2810 0CAA 2810 0CEC 2810 0A00 1010"
		$"0ACE 3010 0928 2010 08AE 4010 0863 8010"
		$"081E 0010 080C 0010 080C 0010 080C 0010"
		$"080C 0010 0FFF FFF0 000C 0000 000C",
		/* [2] */
		$"0FFF F800 0FFF FC00 0FFF FE00 0FFF FF00"
		$"0FFF FF80 0FFF FFC0 0FFF FFE0 0FFF FFF0"
		$"0FFF FFF0 0FFF FFF0 0FFF FFF0 0FFF FFF0"
		$"0FFF FFF0 0FFF FFF0 0FFF FFF0 0FFF FFF0"
		$"0FFF FFF0 0FFF FFF0 0FFF FFF0 0FFF FFF0"
		$"0FFF FFF0 0FFF FFF0 0FFF FFF0 0FFF FFF0"
		$"0FFF FFF0 0FFF FFF0 0FFF FFF0 0FFF FFF0"
		$"0FFF FFF0 0FFF FFF0 000C 0000 000C"
	}
};

resource 'BNDL' (600) {
	'Brow',
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

resource 'MENU' (4, "Window") {
	4,
	textMenuProc,
	allEnabled,
	enabled,
	"Window",
	{	/* array: 0 elements */
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
		"Open", noIcon, hierarchicalMenu, "\r", plain,
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
		"About Browser…", noIcon, noKey, noMark, plain,
		/* [2] */
		"-", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (10) {
	10,
	textMenuProc,
	allEnabled,
	enabled,
	"\0x00",
	{	/* array: 2 elements */
		/* [1] */
		"Binary Mode…", noIcon, "B", noMark, plain,
		/* [2] */
		"Text Mode…", noIcon, "T", noMark, plain
	}
};

resource 'STR#' (256, "Mem Error") {
	{	/* array StringArray: 9 elements */
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
		"Block is locked",
		/* [9] */
		"This file exceeds TextEdit's 32000 byte "
		"limit and is therefore too large to read"
		".  Try opening the file in Binary Mode."
	}
};

resource 'STR#' (16, "Names") {
	{	/* array StringArray: 2 elements */
		/* [1] */
		"Untitled",
		/* [2] */
		"%ld K Available Memory"
	}
};

resource 'STR#' (104, "IO Msgs") {
	{	/* array StringArray: 32 elements */
		/* [1] */
		"Open",
		/* [2] */
		"Closing",
		/* [3] */
		"Read",
		/* [4] */
		"Save",
		/* [5] */
		"Delete",
		/* [6] */
		"File directory is full.",
		/* [7] */
		"Disk is full.",
		/* [8] */
		"Volume was not found.",
		/* [9] */
		"Disk I/O error.",
		/* [10] */
		"Bad file name encountered.",
		/* [11] */
		"End of File.",
		/* [12] */
		"Premature End of File during Read.",
		/* [13] */
		"Volume is locked.",
		/* [14] */
		"File is locked.",
		/* [15] */
		"File is busy.",
		/* [16] */
		"File already exists.",
		/* [17] */
		"Out of memory.",
		/* [18] */
		"Bad File Format.",
		/* [19] */
		"File was not found.",
		/* [20] */
		"External File System.",
		/* [21] */
		"Can't Lock File.",
		/* [22] */
		"Can't Unlock File.",
		/* [23] */
		"Can't Set Document Volume Number.",
		/* [24] */
		"Can't Get Temp File Info.",
		/* [25] */
		"Can't Set Temp File Info.",
		/* [26] */
		"Can't Delete Old Named Data File.",
		/* [27] */
		"Can't Move Temporary File to Named File.",
		/* [28] */
		"Data File Was NOT Saved!",
		/* [29] */
		"Internal Macintosh Error: ",
		/* [30] */
		"Cannot initialize because of the followi"
		"ng:",
		/* [31] */
		"Select a file to browse",
		/* [32] */
		"The system can't open another file. Try "
		"closing some documents."
	}
};

resource 'vers' (2) {
	0x2,
	0x0,
	release,
	0x0,
	verUS,
	"2.0",
	""
};

resource 'vers' (1) {
	0x2,
	0x0,
	release,
	0x0,
	verUS,
	"2.0",
	"Browser 2.0 © 1991 Kurt W.G. Matthies"
};

resource 'PICT' (65) {
	1015,
	{178, 128, 244, 460},
	$"1101 A000 8201 000A 0000 0000 02D0 0240"
	$"9800 2A00 B200 8000 F401 D000 B200 8000"
	$"F401 CC00 B200 8000 F401 CC00 0002 D700"
	$"02D7 0002 D700 02D7 0002 D700 02D7 0002"
	$"D700 08FA 0002 5555 50E1 0008 FA00 0255"
	$"5558 E100 02D7 0008 FA00 0260 000C E100"
	$"06F8 0000 01E1 0008 FA00 0260 000D E100"
	$"06F7 0000 40E2 0009 FA00 0360 000C 40E2"
	$"0006 F700 0010 E200 09FA 0003 6000 0C10"
	$"E200 06F7 0000 04E2 0009 FA00 0360 000A"
	$"AAE2 0007 F800 0102 ABE2 0006 FA00 0060"
	$"DF00 06F7 0000 03E2 0006 FA00 0060 DF00"
	$"06F7 0000 03E2 0007 FA00 0160 3FE0 0008"
	$"F900 02FF C003 E200 0D09 0000 3FFF 8000"
	$"0061 FFE0 E100 0E0A 0000 3FFF E000 0003"
	$"FFF0 03E2 000D 0900 003F FFF0 0000 67E9"
	$"F8E1 000E 0A00 003F FFF0 0000 0F86 7C03"
	$"E200 0D09 0000 3E01 F800 000F 003C E100"
	$"0E0A 0000 3E00 F800 001F 4EFE 03E2 000D"
	$"0900 003E 00F8 0000 1E85 9EE1 000E 0A00"
	$"003E 01F8 0000 1FC6 3E03 E200 1814 0000"
	$"3EFF F81F F83D 252F 003F 7DF8 00FC 001F"
	$"FE01 FEEC 0018 1400 003E FFF0 1FF8 3D25"
	$"4F00 FF7D FE03 FC00 7FFE 07FE EC00 1814"
	$"0000 3EFF E03F F83C CE4F 01FF 7DFF 07FC"
	$"00FF FE0F FEEC 0018 1400 003E FFF0 7FF8"
	$"3C00 0F03 FF7D FF87 FC01 FFFE 1FFE EC00"
	$"1814 0000 3E01 F87E 003D EFEF 03F0 7C1F"
	$"8FC0 01F8 3E1F 80EC 0017 1300 003E 00F8"
	$"FC00 3D29 5F07 E07C 0FCF C003 F07E 3FEB"
	$"002A 1300 003E 00F8 F800 3C42 5F07 C07C"
	$"07C7 FF83 E0FC 3EFE 000F 0600 0063 0003"
	$"0318 C0F8 00C0 C019 8C0C FE00 2913 0000"
	$"3E00 F8F8 003C 425F 07C0 7C07 C7FF E3E1"
	$"F83E FE00 0E06 0000 6600 0303 18C1 8C00"
	$"E1C0 198C FD00 2B13 0000 3E01 F8F8 001E"
	$"845E 07E0 FE0F C3FF F3F3 F03E FE00 1207"
	$"C660 6C33 7FC1 9983 0600 E1CF 1FEF 8C70"
	$"F000 2B13 0000 3E03 F0F8 001E 84FE 03F1"
	$"FF1F 80FF F1F8 003E FE00 1207 6660 7833"
	$"7301 BD83 0000 F3D9 998E CCD9 9800 2B0A"
	$"0000 03FF F0F8 001F 003E 83FE FF05 8001"
	$"F9FF FE3E FE00 1206 3660 7033 6300 FF03"
	$"1E00 F3C3 998C CD8D 8000 2B0A 0000 03FF"
	$"E0F8 000F 463C A1FE FF05 0000 F8FF FE3E"
	$"FE00 1206 33C0 7833 6300 FF03 0600 DECF"
	$"998C CDFC F000 2B13 0000 03FF C0F8 000F"
	$"C97C A0FF EFFE 0000 F87F FE3E FE00 1206"
	$"33C0 6C33 6300 6603 0600 DED9 998C CD80"
	$"1800 2B13 0000 03FF 00F8 0007 E9F8 003F"
	$"C7F8 0001 F81F FE3E FE00 1207 6180 6637"
	$"6300 6601 8E00 CCDB 998C CCD9 9800 22FA"
	$"0002 03FF F0FD 0002 0FFF F0FB 0012 07C1"
	$"8063 1F61 C066 18FE 60CC CECE ECCC 70F0"
	$"0012 FA00 0201 FFE0 FD00 020F FFF0 FA00"
	$"0003 F000 11F9 0001 FFC0 FD00 020F FFE0"
	$"FA00 0003 F000 10F9 0000 3FFC 0002 0FFF"
	$"80FA 0000 06F0 0006 F900 001E E000 06F9"
	$"0000 1EE0 0006 F900 001E E000 06F9 0000"
	$"1EE0 0006 F900 001E E000 06F9 0000 1EE0"
	$"0006 F900 001E E000 06F9 0000 1EE0 0006"
	$"F900 001E E000 06F9 0000 0CE0 0002 D700"
	$"02D7 0002 D700 02D7 00A0 0083 FF"
};

resource 'PICT' (600, "About") {
	2587,
	{24, 26, 197, 331},
	$"1101 A000 8201 000A 0000 0000 02D0 0240"
	$"9800 2800 1800 1800 C501 5000 1800 1A00"
	$"C501 4B00 1800 1A00 C501 4B00 0002 D900"
	$"0700 1FDC FF01 C000 0700 1FDC FF01 C000"
	$"0700 1FDC FF01 C000 0700 1FDC FF01 C000"
	$"0700 1FDC FF01 C000 0D00 1FFA FF02 F555"
	$"55E6 FF01 C000 0D00 1FFA FF02 F555 54E6"
	$"FF01 C000 0700 1FDC FF01 C000 0E00 1FFA"
	$"FF03 F3FF FE7F E7FF 01C0 000B 001F F7FF"
	$"00DF E7FF 01C0 000E 001F FAFF 03F3 FFFE"
	$"5FE7 FF01 C000 0B00 1FF7 FF00 F7E7 FF01"
	$"C000 0E00 1FFA FF03 F3FF FE77 E7FF 01C0"
	$"000B 001F F7FF 00FD E7FF 01C0 000E 001F"
	$"FAFF 03F3 FFFE 7DE7 FF01 C000 0B00 1FF6"
	$"FF00 7FE8 FF01 C000 0F00 1FFA FF04 F3FF"
	$"FEAA BFE8 FF01 C000 0C00 1FF7 FF01 AA9F"
	$"E8FF 01C0 000B 001F FAFF 00F3 E4FF 01C0"
	$"000B 001F F6FF 009F E8FF 01C0 000B 001F"
	$"FAFF 00F3 E4FF 01C0 000B 001F F6FF 009F"
	$"E8FF 01C0 000D 001F FAFF 02F3 F81F E6FF"
	$"01C0 000E 001F F9FF 03E0 07FF 9FE8 FF01"
	$"C000 110A 1FFF FFF8 000F FFFF F3C0 03E6"
	$"FF01 C000 1305 1FFF FFF8 0003 FEFF 0380"
	$"01FF 9FE8 FF01 C000 110A 1FFF FFF8 0001"
	$"FFFF F302 C0E6 FF01 C000 130C 1FFF FFF8"
	$"0001 FFFF FE0F 307F 9FE8 FF01 C000 120B"
	$"1FFF FFF8 3FC0 FFFF FE1F F87F E7FF 01C0"
	$"0013 0C1F FFFF F83F E0FF FFFC 1620 3F9F"
	$"E8FF 01C0 0012 0B1F FFFF F83F E0FF FFFC"
	$"2F4C 3FE7 FF01 C000 130C 1FFF FFF8 3FC0"
	$"FFFF FC07 383F 9FE8 FF01 C000 1D16 1FFF"
	$"FFF8 2000 FC00 F85B 5A1F F810 40FF E07F"
	$"FC00 3FC0 3FF2 FF01 C000 1D16 1FFF FFF8"
	$"2001 FC00 F85B 561F E010 403F 807F F000"
	$"3F00 3FF2 FF01 C000 1D16 1FFF FFF8 2003"
	$"F800 F866 361F C010 401F 007F E000 3E00"
	$"3FF2 FF01 C000 1D16 1FFF FFF8 2001 F000"
	$"F87F FE1F 8010 400F 007F C000 3C00 3FF2"
	$"FF01 C000 1C15 1FFF FFF8 3FC0 F03F F842"
	$"021F 81F0 7C0E 07FF C0F8 3C0F F1FF 01C0"
	$"001C 151F FFFF F83F E0E0 7FF8 5AD4 1F03"
	$"F07E 0607 FF81 F038 1FF1 FF01 C000 1C15"
	$"1FFF FFF8 3FE0 E0FF F877 B41F 07F0 7F07"
	$"000F 83E0 783F F1FF 01C0 001C 151F FFFF"
	$"F83F E0E0 FFF8 77B4 1F07 F07F 0700 0383"
	$"C0F8 3FF1 FF01 C000 1C15 1FFF FFF8 3FC0"
	$"E0FF FC2F 743F 03E0 3E07 8001 8181 F83F"
	$"F1FF 01C0 001C 151F FFFF F83F 81E0 FFFC"
	$"2F60 3F81 C01C 0FE0 01C0 FFF8 3FF1 FF01"
	$"C000 1C00 1FFE FF11 8001 E0FF FC1F F82F"
	$"8000 000F FFC0 C000 383F F1FF 01C0 001C"
	$"001F FEFF 1180 03E0 FFFE 1738 6BC0 0000"
	$"1FFF E0E0 0038 3FF1 FF01 C000 1C00 1FFE"
	$"FF11 8007 E0FF FE06 D06B E002 003F FFE0"
	$"F000 383F F1FF 01C0 001C 001F FEFF 1180"
	$"1FE0 FFFF 02C0 FFF8 0700 FFFF C0FC 0038"
	$"3FF1 FF01 C000 1200 1FF9 FF01 8001 FDFF"
	$"02FE 0001 EDFF 01C0 0012 001F F9FF 01C0"
	$"03FD FF02 FE00 01ED FF01 C000 1200 1FF9"
	$"FF01 E007 FDFF 02FE 0003 EDFF 01C0 0012"
	$"001F F9FF 01F8 1FFD FF02 FE00 0FED FF01"
	$"C000 0C00 1FF9 FF01 FC3F E6FF 01C0 000C"
	$"001F F9FF 01FC 3FE6 FF01 C000 0C00 1FF9"
	$"FF01 FC3F E6FF 01C0 000C 001F F9FF 01FC"
	$"3FE6 FF01 C000 0C00 1FF9 FF01 FC3F E6FF"
	$"01C0 000C 001F F9FF 01FC 3FE6 FF01 C000"
	$"0C00 1FF9 FF01 FC3F E6FF 01C0 000C 001F"
	$"F9FF 01FC 3FE6 FF01 C000 0C00 1FF9 FF01"
	$"FC3F E6FF 01C0 000C 001F F9FF 01FE 7FE6"
	$"FF01 C000 0700 1FDC FF01 C000 0700 1FDC"
	$"FF01 C000 0700 1FDC FF01 C000 0700 1FDC"
	$"FF01 C000 0700 1FDC FF01 C000 0B02 1FFF"
	$"FFE0 0003 1FFF C000 0B02 1FFF FFE0 0003"
	$"1FFF C000 0700 1FDC FF01 C000 0700 1FDC"
	$"FF01 C000 0700 1FDC FF01 C000 0700 1FDC"
	$"FF01 C000 0700 1FDC FF01 C000 0700 1FDC"
	$"FF01 C000 0700 1FDC FF01 C000 0700 1FDC"
	$"FF01 C000 0700 1FDC FF01 C000 0700 1FDC"
	$"FF01 C000 0700 1FDC FF01 C000 0700 1FDC"
	$"FF01 C000 0700 1FDC FF01 C000 1F18 1FFF"
	$"FFBF BFEF 7DFF FFF8 3FFF 7BFF FDFE FEFC"
	$"3FF7 DFFB EF7F 7FF4 FF01 C000 1E17 1FFF"
	$"FFBF BFFF 7DFF FFFB DFFF 77FF FDFE FEFB"
	$"DFF3 9FFB EF7F F3FF 01C0 0020 191F FFFF"
	$"BBB4 4E38 F1D3 FBDB BF6F 7688 FEEE FBFF"
	$"F55C 71C7 4E78 F1F5 FF01 C000 2019 1FFF"
	$"FFDB 73EF 7DEE CDF8 3BBF 5F76 7DFF 6DFB"
	$"FFF6 DBBB EF37 776E F5FF 01C0 0020 191F"
	$"FFFF D577 EF7D EEDD FBDB BF3F 76FD FF55"
	$"FB1F F7DC 3BEF 7777 6FF5 FF01 C000 2019"
	$"1FFF FFD5 77EF 7DE0 DDFB DBBF 5F76 FDFF"
	$"55FB DFF7 DBBB EF77 7071 F5FF 01C0 0020"
	$"191F FFFF EEF7 EF7D EFDD FBDB BF6F 76FD"
	$"FFBB FBDF F7DB BBEF 7777 FEF5 FF01 C000"
	$"2019 1FFF FFEE F7EF 7DEE DDFB DBBF 7766"
	$"FDFF BBFB DFF7 DBBB EF77 776E F5FF 01C0"
	$"0020 191F FFFF EEF7 EF9E 71DD F83C 3F7B"
	$"96FE 7FBB DC3B F7DC 3CF3 7778 F1F5 FF01"
	$"C000 0B00 1FF7 FF00 BFE7 FF01 C000 0C00"
	$"1FF8 FF01 FBBF E7FF 01C0 000C 001F F8FF"
	$"01FC 7FE7 FF01 C000 0700 1FDC FF01 C000"
	$"0700 1FDC FF01 C000 0700 1FDC FF01 C000"
	$"0700 1FDC FF01 C000 0700 1FDC FF01 C000"
	$"2603 1FFF FFC3 FEFF 18FB FF7F 7FFF FFDF"
	$"0F0F 9FEF FFFB DFFF EFF7 F7E1 FFBE FFDF"
	$"7BFB FBFF 01C0 0023 031F FFFF BDFC FF15"
	$"7F7F E1FF 9EF6 F76F EFFF FBBF FFEF F7F7"
	$"DEFF 9CFF DF7B FAFF 01C0 0028 211F FFFF"
	$"BFC7 0EED 13C3 4E3F DEFF DEF6 F6F7 E1DD"
	$"FB7B B447 F777 DFFF AAE3 8E3A 73C7 8FFD"
	$"FF01 C000 2821 1FFF FFBF BB76 ECFB BB37"
	$"7FB3 7FDE F6F6 F7EE DDFA FBB3 EFFB 6FDF"
	$"FFB6 DDDF 79BB BB77 FDFF 01C0 0028 211F"
	$"FFFF BFBB 76ED FBBB 777F AF7F DEF6 F6F7"
	$"EEDD F9FB B7EF FAAF D8FF BEE1 DF7B BBBB"
	$"7FFD FF01 C000 2821 1FFF FFBF BB76 EDFB"
	$"BB77 7FAF 7FDF 0706 F7EE DDFA FBB7 EFFA"
	$"AFDE FFBE DDDF 7BBB 838F FDFF 01C0 0028"
	$"211F FFFF BFBB 76ED FBBB 777F B37F DFF7"
	$"F6F7 EEDD FB7B B7EF FDDF DEFF BEDD DF7B"
	$"BBBF F7FD FF01 C000 2821 1FFF FFBD BB76"
	$"EDFB BB77 7FDE FFDF EFEF 6FEE DDFB BB37"
	$"EFFD DFDE FFBE DDDF 7BBB BB77 FDFF 01C0"
	$"0028 211F FFFF C3C7 0F0D FBC3 779F E1FF"
	$"DF1F 1F9F E1E1 FBDC B7F3 FDDE E1DF BEE1"
	$"E79B BBC7 8FFD FF01 C000 1200 1FFD FF03"
	$"7FEF FFFB F8FF 00FD EEFF 01C0 0012 001F"
	$"FDFF 037E EFFF BBF8 FF00 DDEE FF01 C000"
	$"1100 1FFC FF02 1FFF C7F8 FF00 E3EE FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0B02 1FFF FCE0"
	$"0003 7FFF C000 0B02 1FFF FCE0 0003 7FFF"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 0700 1FDC FF01"
	$"C000 0700 1FDC FF01 C000 02D9 00A0 0083"
	$"FF"
};

data 'Brow' (0) {
	$"2F42 726F 7773 6572 2020 436F 7079 7269"            /* /Browser  Copyri */
	$"6768 7420 3139 3931 204B 7572 7420 572E"            /* ght 1991 Kurt W. */
	$"472E 204D 6174 7468 6965 73"                        /* G. Matthies */
};

