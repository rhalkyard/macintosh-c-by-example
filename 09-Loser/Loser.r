#define ALRT_RezTemplateVersion 0
#define DLOG_RezTemplateVersion 0

#include "Types.r"

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

resource 'DITL' (65, "Loser GetFile", purgeable) {
	{	/* array DITLarray: 16 elements */
		/* [1] */
		{127, 248, 147, 312},
		Button {
			enabled,
			"Lose"
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
		{253, 221, 265, 236},
		UserItem {
			disabled
		},
		/* [12] */
		{0, 0, 66, 341},
		Picture {
			disabled,
			65
		},
		/* [13] */
		{251, 25, 271, 113},
		RadioButton {
			enabled,
			"Lose File"
		},
		/* [14] */
		{123, 244, 151, 316},
		UserItem {
			disabled
		},
		/* [15] */
		{182, 241, 185, 321},
		UserItem {
			disabled
		},
		/* [16] */
		{251, 126, 271, 214},
		RadioButton {
			enabled,
			"Find File"
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

resource 'DITL' (100, "Message") {
	{	/* array DITLarray: 4 elements */
		/* [1] */
		{92, 19, 112, 79},
		Button {
			enabled,
			"OK"
		},
		/* [2] */
		{15, 17, 47, 49},
		Icon {
			enabled,
			1
		},
		/* [3] */
		{88, 15, 116, 83},
		UserItem {
			disabled
		},
		/* [4] */
		{14, 98, 119, 306},
		StaticText {
			enabled,
			"^0"
		}
	}
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

resource 'DLOG' (65, "Loser GetFile", purgeable) {
	{32, 46, 312, 388},
	dBoxProc,
	invisible,
	noGoAway,
	0x0,
	65,
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

resource 'DLOG' (100, "Message") {
	{58, 44, 188, 364},
	dBoxProc,
	invisible,
	noGoAway,
	0x0,
	100,
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
		$"0000 0000 0000 0000 0000 0000 0000 FE00"
		$"0000 8300 0000 8280 0000 8240 0000 83E0"
		$"00FC 8020 0102 8020 0201 8020 1C00 FFF8"
		$"1000 8028 1000 0008 1000 8028 1000 0008"
		$"1000 8028 1000 0008 1000 AAA8 1000 0008"
		$"1000 0008 1000 0008 1000 0008 1000 0008"
		$"1000 0008 1FFF FFF8",
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
	'Lose',
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

resource 'STR#' (104, "IO Msgs") {
	{	/* array StringArray: 18 elements */
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
		"Premature End of File during Read.",
		/* [12] */
		"Volume is locked.",
		/* [13] */
		"File is locked.",
		/* [14] */
		"File is busy.",
		/* [15] */
		"File already exists.",
		/* [16] */
		"File was not found.",
		/* [17] */
		"External File System.",
		/* [18] */
		"Macintosh File System Error:"
	}
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

resource 'STR#' (64, "Messages") {
	{	/* array StringArray: 1 elements */
		/* [1] */
		"Select File"
	}
};

resource 'vers' (2) {
	0x1,
	0x0,
	0x8,
	0x1,
	verUS,
	"1.0",
	"MacUser's Power Programming"
};

resource 'vers' (1) {
	0x1,
	0x0,
	0x8,
	0x1,
	verUS,
	"1.0",
	"Loser - Version 1.0\n© 1990 Code of the W"
	"est, Inc."
};

resource 'PICT' (65, "Loser Logo", purgeable) {
	2616,
	{0, 0, 66, 341},
	$"1101 A000 82A0 008E 0100 0A00 0000 0002"
	$"D002 4098 002C 0000 0000 0042 0158 0000"
	$"0000 0042 0155 0000 0000 0042 0155 0001"
	$"21F3 001D 8800 0008 8000 0088 0000 0880"
	$"0000 8800 0008 8000 0088 0000 0880 0000"
	$"8800 21F3 0003 2000 0002 FE00 0320 0000"
	$"02FE 0003 2000 0002 FE00 0320 0000 02FE"
	$"0001 2000 21F3 001D 8800 0008 8000 0088"
	$"0000 0880 0000 8800 0008 8000 0088 0000"
	$"0880 0000 8800 21F3 0003 2000 0002 FE00"
	$"0320 0000 02FE 0003 2000 0002 FE00 0320"
	$"0000 02FE 0001 2000 12F3 000A 8800 0008"
	$"8000 0088 0000 08EF 8800 0013 F300 0320"
	$"0000 02FE 0003 2000 0002 F022 0120 0012"
	$"F300 0A88 0000 0880 0000 8800 0008 EF88"
	$"0000 19FA 0002 1555 54FD 0003 2000 0002"
	$"FE00 0320 0000 02F0 2201 2000 18FA 0002"
	$"1555 56FD 000A 8800 0008 8000 0088 0000"
	$"08EF 8800 0021 F300 0320 0000 02FE 0003"
	$"2000 0002 FE00 0320 0000 02FE 0003 2000"
	$"0002 FE00 0120 0027 FA00 0218 0003 FD00"
	$"1D88 0000 0880 0000 8800 0008 8000 0088"
	$"0000 0880 0000 8800 0008 8000 0088 0025"
	$"F700 0040 FE00 0320 0000 02FE 0003 2000"
	$"0002 FE00 0320 0000 02FE 0003 2000 0002"
	$"FE00 0120 002C FE00 0701 FFF8 0018 0003"
	$"40FE 001D 8800 0008 8000 0088 0000 0880"
	$"0000 8800 0008 8000 0088 0000 0880 6000"
	$"8800 2BFE 0002 01FF F8FD 0000 10FE 0003"
	$"2000 0002 FE00 0320 0000 02FE 000F 2000"
	$"0003 C038 0021 E1C0 0200 6000 2000 2CFE"
	$"0007 0600 0600 1800 0310 FE00 1D88 0000"
	$"0880 0000 8800 0008 8000 0088 0000 08E0"
	$"7000 88C0 8008 8020 0088 002B FE00 0206"
	$"0006 FD00 0004 FE00 0320 0000 02FE 0003"
	$"2000 0002 FE00 0F20 0000 02E0 7000 20C0"
	$"8002 0020 0020 002C FE00 0718 0001 8018"
	$"0003 04FE 001D 8800 0008 8000 0088 0000"
	$"0880 0000 8800 0008 B0B0 0088 C080 0880"
	$"4000 8800 2CFE 0003 1800 0180 FE00 0001"
	$"FE00 0320 0000 02FE 0003 2000 0002 FE00"
	$"0F20 0000 02B0 B1E0 F0C0 8F0E 170F 0020"
	$"002C FE00 2818 0001 8018 0002 AA80 0000"
	$"8800 0008 8000 0088 0000 0880 0000 8800"
	$"0008 9933 3198 C099 99BB 1980 8800 2CFE"
	$"000E 6000 0040 0000 02AA C000 0020 0000"
	$"02FE 0003 2000 0002 FE00 0F20 0000 0299"
	$"3233 38C0 9CB3 981C 8020 0029 FE00 0460"
	$"0000 4018 FB00 1D88 0000 0880 0000 8800"
	$"0008 8000 0088 0000 089A 3073 88C0 8E3F"
	$"980E 0088 002D 1100 0001 E000 007F E7FF"
	$"FFC0 C000 0020 0000 02FE 0003 2000 0002"
	$"FE00 0F20 0000 028E 31B3 20C0 8732 1807"
	$"0020 002D 0600 0001 E000 007F FEFF 00C0"
	$"FE00 1D88 0000 0880 0000 8800 0008 8000"
	$"0088 0000 088E 3333 88E1 93B8 9813 8088"
	$"0029 0200 0006 FA00 0720 C000 0020 0000"
	$"02FE 0003 2000 0002 FE00 0F20 0000 0284"
	$"3375 B873 199F 1819 8020 002C 0200 0006"
	$"FD00 0318 0000 20FE 001D 8800 0008 8000"
	$"0088 0000 0880 0000 8800 0009 C479 98F8"
	$"3E0F 0EBC 0F00 8800 2902 0000 06FA 0007"
	$"60C0 0000 2000 0002 FE00 0320 0000 02FE"
	$"0003 2000 0002 FE00 0320 0000 02FE 0001"
	$"2000 2C02 0000 06FD 0003 1800 0060 FE00"
	$"1D88 0000 0880 0000 8800 0008 8000 0088"
	$"0000 0880 0000 8800 0008 8000 0088 0029"
	$"0200 0006 FA00 0760 C000 0020 0000 02FE"
	$"0003 2000 0002 FE00 0320 0000 02FE 0003"
	$"2000 0002 FE00 0120 002C 0200 0006 FD00"
	$"0318 0000 60FE 001D 8800 0008 8000 0088"
	$"0000 0880 0000 8800 0008 8000 0088 0000"
	$"0880 0000 8800 2902 0000 06FA 0007 60C0"
	$"0000 2000 0002 FE00 0A20 0000 0200 0F80"
	$"2000 0002 FE00 0320 79E0 02FE 0001 2000"
	$"2C02 0000 06FD 0003 1800 0060 FE00 1D88"
	$"0000 0880 0000 8800 0008 803F 8088 0000"
	$"0880 0000 8879 E008 8000 0088 0029 0200"
	$"0006 FA00 0760 C000 0020 0000 02FE 000A"
	$"2000 0002 007F 8020 0000 02FE 0003 2001"
	$"E002 FE00 0120 002C 0200 0006 FD00 0318"
	$"0000 60FE 001D 8800 0008 8000 0088 0000"
	$"0880 7F80 8800 0008 8000 0088 01E0 0880"
	$"0000 8800 2902 0000 06FA 0007 60C0 0000"
	$"2000 0002 FE00 1620 0000 0200 F800 23FF"
	$"80FF 9E07 80FE 79FF E7C1 F000 2000 2D0A"
	$"0000 0601 E000 0018 0000 60FE 001D 8800"
	$"0008 8000 0088 0000 0880 F000 8FFF 83FF"
	$"9E07 83FE 79FF EBE1 FC00 8800 2B04 0000"
	$"0600 C0FC 0007 60C0 0000 2000 0002 FE00"
	$"1620 0000 0200 F000 3FFF 87FF 9E07 87FE"
	$"79FF E3E1 FE00 2000 2B04 0000 0600 C0FC"
	$"0000 60FE 001D 8800 0008 8000 0088 0000"
	$"0880 F800 BFFF 8FFF 9E07 8FFE 79FF E9F1"
	$"FF00 8800 2B04 0000 0600 C0FC 0007 60C0"
	$"0000 2000 0002 FE00 1620 0000 0200 7FE0"
	$"3E07 8F82 1E07 8FA0 79E0 03F0 1F00 2000"
	$"2D0A 0000 0600 C00F 0787 C730 60FE 001D"
	$"8800 0008 8000 0088 0000 0880 7FF8 FC0F"
	$"9F08 9E07 9F88 79E0 08F8 0F80 8800 2D11"
	$"0000 0600 C031 98CC 6370 60C0 0000 2000"
	$"0002 FE00 1620 0000 0200 3FFC 781F 1E02"
	$"1E07 9E20 79E0 02F8 0780 2000 2D0A 0000"
	$"0600 C020 D808 3380 60FE 001D 8800 0008"
	$"8000 0088 0000 0880 0FFE F83E 1E08 9E07"
	$"9E88 79E0 08FC 0780 8800 2D11 0000 0600"
	$"C060 DC18 3300 60C0 0000 2000 0002 FE00"
	$"1620 0000 0200 003E 7C7C 1F02 1F07 9E20"
	$"79F0 027C 0F80 2000 2D0A 0000 0600 C060"
	$"CF9F F300 60FE 001D 8800 0008 8000 0088"
	$"0000 0880 001F BE00 0F88 8F87 9E88 78F8"
	$"08BE 1F00 8800 2D11 0000 0600 C060 C1D8"
	$"0300 60C0 0000 2000 0002 FE00 1620 0000"
	$"0200 000F 3FFF 8FFF 8FFF 9E20 78FF E23E"
	$"3F00 2000 2D0A 0000 0600 C160 80DC 0300"
	$"60FE 001D 8800 0008 8000 0088 0000 0880"
	$"000F 9FFF 87FF 87FF 9E88 787F E89F 7E00"
	$"8800 2D11 0000 0600 C131 98CE 130A AAC0"
	$"0000 2000 0002 FE00 1620 0000 0200 001F"
	$"2FFF 83FF 83FF 9E20 783F E21F FC00 2000"
	$"2D2B 0000 0601 FF1E 0F07 E78A AAC0 0000"
	$"8800 0008 8000 0088 0000 0880 003E 8BFF"
	$"80FF 80FF 9E88 780F E88F F800 8800 2902"
	$"0000 06FA 0000 60FE 0003 2000 0002 FE00"
	$"0A20 0000 0200 FFFE 2000 0002 FE00 0820"
	$"0000 020F F000 2000 2902 0000 06FA 0000"
	$"60FE 001D 8800 0008 8000 0088 0000 0880"
	$"FFFC 8800 0008 8000 0088 0000 0887 E000"
	$"8800 2902 0000 06FA 0000 60FE 0003 2000"
	$"0002 FE00 0A20 0000 0200 FFF8 2000 0002"
	$"FE00 0820 0000 020F C000 2000 2902 0000"
	$"06FA 0000 60FE 001D 8800 0008 8000 0088"
	$"0000 0880 FFE0 8800 0008 8000 0088 0000"
	$"089F 8000 8800 2902 0000 06FA 0000 60FE"
	$"0003 2000 0002 FE00 0320 0000 02FE 0003"
	$"2000 0002 FE00 0820 0000 023F 0000 2000"
	$"2902 0000 06FA 0000 60FE 001D 8800 0008"
	$"8000 0088 0000 0880 0000 8800 0008 8000"
	$"0088 0000 08FE 0000 8800 2902 0000 06FA"
	$"0000 60FE 0003 2000 0002 FE00 0320 0000"
	$"02FE 0003 2000 0002 FE00 0320 0000 02FE"
	$"0001 2000 2902 0000 06FA 0000 60FE 001D"
	$"8800 0008 8000 0088 0000 0880 0000 8800"
	$"0008 8000 0088 0000 0880 0000 8800 2902"
	$"0000 06FA 0000 60FE 0003 2000 0002 FE00"
	$"0320 0000 02FE 0003 2000 0002 FE00 0320"
	$"0000 02FE 0001 2000 1A02 0000 07FA FF00"
	$"E0FE 000A 8800 0008 8000 0088 0000 08EF"
	$"8800 001B 0200 0007 FAFF 00E0 FE00 0320"
	$"0000 02FE 0003 2000 0002 F022 0120 0012"
	$"F300 0A88 0000 0880 0000 8800 0008 EF88"
	$"0000 13F3 0003 2000 0002 FE00 0320 0000"
	$"02F0 2201 2000 12F3 000A 8800 0008 8000"
	$"0088 0000 08EF 8800 0021 F300 0320 0000"
	$"02FE 0003 2000 0002 FE00 0320 0000 02FE"
	$"0003 2000 0002 FE00 0120 0021 F300 1D88"
	$"0000 0880 0000 8800 0008 8000 0088 0000"
	$"0880 0000 8800 0008 8000 0088 0021 F300"
	$"0320 0000 02FE 0003 2000 0002 FE00 0320"
	$"0000 02FE 0003 2000 0002 FE00 0120 0021"
	$"F300 1D88 0000 0880 0000 8800 0008 8000"
	$"0088 0000 0880 0000 8800 0008 8000 0088"
	$"0005 D7FF 01F8 00A0 008F A000 83FF"
};

data 'Lose' (0) {
	$"2D4C 6F73 6572 2C20 436F 7079 7269 6768"            /* -Loser, Copyrigh */
	$"7420 3139 3930 2C20 436F 6465 206F 6620"            /* t 1990, Code of  */
	$"7468 6520 5765 7374 2C20 496E 632E"                 /* the West, Inc. */
};

