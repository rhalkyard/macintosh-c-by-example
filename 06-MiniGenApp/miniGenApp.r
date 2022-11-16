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

resource 'DITL' (64, "Save Change") {
	{	/* array DITLarray: 6 elements */
		/* [1] */
		{14, 190, 34, 250},
		Button {
			enabled,
			"Save"
		},
		/* [2] */
		{45, 190, 65, 250},
		Button {
			enabled,
			"Don't"
		},
		/* [3] */
		{10, 186, 38, 254},
		UserItem {
			disabled
		},
		/* [4] */
		{76, 190, 96, 250},
		Button {
			enabled,
			"Cancel"
		},
		/* [5] */
		{10, 57, 96, 171},
		StaticText {
			disabled,
			"Save Changes to ^0?"
		},
		/* [6] */
		{10, 11, 42, 43},
		Icon {
			enabled,
			2
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
	{44, 30, 209, 329},
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

resource 'DLOG' (64, "Save Change") {
	{40, 40, 152, 304},
	dBoxProc,
	invisible,
	noGoAway,
	0x0,
	64,
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
		"About miniGeneric", noIcon, noKey, noMark, plain,
		/* [2] */
		"-", noIcon, noKey, noMark, plain
	}
};

data 'GNAP' (0, "Signature") {
	$"2B6D 696E 6947 656E 7269 6320 4170 7020"            /* +miniGenric App  */
	$"A920 3139 3930 204B 7572 7420 572E 472E"            /*  1990 Kurt W.G. */
	$"204D 6174 7468 6965 73"                             /*  Matthies */
};

resource 'STR#' (100) {
	{	/* array StringArray: 3 elements */
		/* [1] */
		"Hey Mac! ",
		/* [2] */
		"Kurt's mini-Generic App",
		/* [3] */
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
	0x1,
	verUS,
	"1.1",
	"mini Generic - Version 1.1\n 1990 Kurt W"
	".G. Matthies"
};

resource 'PICT' (600, "About box") {
	2576,
	{206, 26, 372, 326},
	$"1101 A000 8201 000A 0000 0000 02D0 0240"
	$"9800 2600 CE00 1801 7401 4800 CE00 1A01"
	$"7401 4600 CE00 1A01 7401 4600 0002 DB00"
	$"0600 1FDD FF00 F806 001F DDFF 00F8 0600"
	$"1FDD FF00 F806 001F DDFF 00F8 0600 1FDD"
	$"FF00 F806 001F DDFF 00F8 0600 1FDD FF00"
	$"F806 001F DDFF 00F8 0600 1FDD FF00 F806"
	$"001F DDFF 00F8 0600 1FDD FF00 F806 001F"
	$"DDFF 00F8 0600 1FDD FF00 F806 001F DDFF"
	$"00F8 0600 1FDD FF00 F806 001F DDFF 00F8"
	$"0600 1FDD FF00 F806 001F DDFF 00F8 0600"
	$"1FDD FF00 F806 001F DDFF 00F8 0600 1FDD"
	$"FF00 F806 001F DDFF 00F8 0600 1FDD FF00"
	$"F806 001F DDFF 00F8 0600 1FDD FF00 F806"
	$"001F DDFF 00F8 0600 1FDD FF00 F806 001F"
	$"DDFF 00F8 0600 1FDD FF00 F806 001F DDFF"
	$"00F8 0600 1FDD FF00 F806 001F DDFF 00F8"
	$"1D17 1FFF FC30 F000 181E 0180 00C0 07FE"
	$"01F8 C3FF F83F C007 E003 F4FF 00F8 1D17"
	$"1FFF F810 F000 181E 0180 00C0 01FE 01E0"
	$"43FF F83F C001 E000 F4FF 00F8 1E18 1FFF"
	$"F010 F000 181E 0180 00C0 00FE 01C0 43FF"
	$"F83F C000 E000 7FF5 FF00 F81E 181F FFF0"
	$"00F0 0018 1E01 8000 C000 FE01 C003 FFF8"
	$"3FC0 00E0 007F F5FF 00F8 1E18 1FFF E000"
	$"F000 180E 0180 00C0 007E 0180 03FF F83F"
	$"C000 6000 3FF5 FF00 F81E 181F FFE0 00F0"
	$"0018 0E01 8000 C000 7E01 8003 FFF8 3FC0"
	$"0060 003F F5FF 00F8 1E18 1FFF E000 F000"
	$"180E 0180 00C0 007E 0180 03FF F01F C000"
	$"6000 3FF5 FF00 F81E 181F FFE0 00F0 0018"
	$"0E01 8000 C000 7E01 8003 FFF0 1FC0 0060"
	$"003F F5FF 00F8 1E18 1FFF E000 F000 1806"
	$"0180 00C0 007E 0180 03FF F01F C000 6000"
	$"3FF5 FF00 F81E 091F FFE0 E0FC 3E18 0601"
	$"E1FE F00B 7E01 8383 FFF0 1FF0 F078 783F"
	$"F5FF 00F8 1E18 1FFF E1F0 FC3E 1E07 87E1"
	$"F0F0 F87F 8787 C3FF F01F F0F8 787C 3FF5"
	$"FF00 F81E 181F FFE1 F0FC 3E1E 0787 E1F0"
	$"F0F8 7F87 87C3 FFF0 1FF0 F878 7C3F F5FF"
	$"00F8 1E18 1FFF E1F0 FC3E 1E03 87E1 F0F0"
	$"F87F 8787 C3FF F01F F0F8 787C 3FF5 FF00"
	$"F81E 181F FFE1 F0FC 3E1E 0387 E1F0 F0F8"
	$"7F87 87C3 FFE0 0FF0 F878 7C3F F5FF 00F8"
	$"1E18 1FFF E1F0 FC3E 1E03 87E1 F0F0 F87F"
	$"8787 C3FF E00F F0F8 787C 3FF5 FF00 F81E"
	$"181F FFE1 F0FC 3E1E 0387 E1F0 F0F8 7F87"
	$"87C3 FFE0 0FF0 F878 7C3F F5FF 00F8 1E18"
	$"1FFF E1FF FC3F FE01 87E1 FFF0 F87F 8787"
	$"FFFF E00F F0F8 787C 3FF5 FF00 F81E 181F"
	$"FFE1 FFFC 3FFE 0187 E1FF F0F8 7F87 87FF"
	$"FFE1 0FF0 F878 7C3F F5FF 00F8 1E18 1FFF"
	$"E1FF FC3F FE01 87E1 FFF0 F87F 8787 FFFF"
	$"E10F F0F8 787C 3FF5 FF00 F81E 181F FFE1"
	$"FFFC 007E 0187 E003 F0F0 FF87 87FF FFE1"
	$"07F0 F878 7C3F F5FF 00F8 1E18 1FFF E1C0"
	$"3C00 7E00 87E0 03F0 00FF 8787 FFFF C107"
	$"F0F0 7878 3FF5 FF00 F81E 181F FFE1 C03C"
	$"007E 0087 E003 F003 FF87 87FF FFC1 07F0"
	$"0078 003F F5FF 00F8 1E18 1FFF E1C0 3C00"
	$"7E10 87E0 03F0 01FF 8787 FFFF C387 F000"
	$"F800 7FF5 FF00 F81E 181F FFE1 C03C 007E"
	$"1007 E003 F001 FF87 87FF FFC3 87F0 00F8"
	$"007F F5FF 00F8 1D17 1FFF E1C0 3C3F FE10"
	$"07E1 FFF0 00FF 8787 FFFF C387 F001 F800"
	$"F4FF 00F8 1D17 1FFF E1F0 FC3F FE18 07E1"
	$"FFF0 E0FF 8787 FFFF C387 F007 F803 F4FF"
	$"00F8 1D17 1FFF E1F0 FC3F FE18 07E1 FFF0"
	$"F0FF 8787 FFFF C387 F0FF F87F F4FF 00F8"
	$"1D17 1FFF E1F0 FC3F FE18 07E1 FFF0 F0FF"
	$"8787 FFFF C007 F0FF F87F F4FF 00F8 1D09"
	$"1FFF E1F0 FC3E 1E18 07E1 FEF0 0AFF 8787"
	$"C3FF 8003 F0FF F87F F4FF 00F8 1D09 1FFF"
	$"E1F0 FC3E 1E1C 07E1 FEF0 0AFF 8787 C3FF"
	$"8003 F0FF F87F F4FF 00F8 1D09 1FFF E1F0"
	$"FC3E 1E1C 07E1 FEF0 0AFF 8787 C3FF 8003"
	$"F0FF F87F F4FF 00F8 1D09 1FFF E1F0 FC3E"
	$"1E1C 07E1 FEF0 0AFF 8787 C3FF 87C3 F0FF"
	$"F87F F4FF 00F8 1D09 1FFF E1F0 FC3E 1E1C"
	$"07E1 FEF0 0AE7 8787 C3FF 87C3 F0FF F87F"
	$"F4FF 00F8 1D09 1FFF E1F0 FC3E 1E1E 07E1"
	$"FEF0 0AE7 8787 C3FF 87C3 F0FF F87F F4FF"
	$"00F8 1D09 1FFF E1F0 FC3E 1E1E 07E1 FEF0"
	$"0AE7 8787 C3FF 87C3 F0FF F87F F4FF 00F8"
	$"1D09 1FFF E0E0 FC3E 1E1E 07E1 FEF0 0A47"
	$"8783 83FF 87C3 F0FF F87F F4FF 00F8 1D17"
	$"1FFF E000 F000 1806 0780 00C0 3006 0180"
	$"03FE 0100 C03F E01F F4FF 00F8 1D17 1FFF"
	$"E000 F000 1807 0780 00C0 3006 0180 03FE"
	$"0100 C03F E01F F4FF 00F8 1D17 1FFF E000"
	$"F000 1807 0780 00C0 3006 0180 03FE 0100"
	$"C03F E01F F4FF 00F8 1D17 1FFF E000 F000"
	$"1807 0780 00C0 3006 0180 03FE 0100 C03F"
	$"E01F F4FF 00F8 1D17 1FFF E000 F000 1807"
	$"0780 00C0 3006 0180 03FE 0100 C03F E01F"
	$"F4FF 00F8 1D17 1FFF F000 F000 1807 8780"
	$"00C0 3006 01C0 07FE 0100 C03F E01F F4FF"
	$"00F8 1D17 1FFF F008 F000 1807 8780 00C0"
	$"380E 01C0 07FE 0100 C03F E01F F4FF 00F8"
	$"1D17 1FFF F808 F000 1807 8780 00C0 380E"
	$"01E0 0FFE 0100 C03F E01F F4FF 00F8 1D17"
	$"1FFF FE18 F000 1807 8780 00C0 3C1E 01F8"
	$"3FFE 0100 C03F E01F F4FF 00F8 0600 1FDD"
	$"FF00 F806 001F DDFF 00F8 0600 1FDD FF00"
	$"F806 001F DDFF 00F8 0600 1FDD FF00 F806"
	$"001F DDFF 00F8 0600 1FDD FF00 F806 001F"
	$"DDFF 00F8 0600 1FDD FF00 F806 001F DDFF"
	$"00F8 0600 1FDD FF00 F806 001F DDFF 00F8"
	$"0600 1FDD FF00 F806 001F DDFF 00F8 0600"
	$"1FDD FF00 F825 031F FFF8 7FFE FF18 CFFC"
	$"FE7F C3FF 3E1E 1E1F FCE7 FFFC FE66 7F0F"
	$"FEFF 7FF3 CE7E 7FFC FF00 F823 031F FFF3"
	$"BFFD FF16 FCFE 7FBD FE3C CCCC CFFC CFFF"
	$"FCFE 667E 77FE 7E7F F3CE 7FFB FF00 F826"
	$"201F FFF3 F870 7332 4E0C 1C3F 66FF 3CCC"
	$"CCCF FC9E 6648 7E66 7E7F FE3C 70E1 860E"
	$"70F1 FDFF 00F8 251D 1FFF F3F3 3333 31CC"
	$"CCCE 7F5A FF3C CCCC CFFC 3E66 3CFE 667E"
	$"7FFE 186E 73CE FE66 FDFF 00F8 2603 1FFF"
	$"F3F3 FE33 19CC CCCE 7F5E FF3C CCCC CFFC"
	$"7E66 7CFE 667E 47FE 8270 73CE 6666 63FD"
	$"FF00 F826 031F FFF3 F3FE 3319 CCCC CE7F"
	$"5AFF 3E0E 0CCF FC3E 667C FE66 7E67 FEC6"
	$"6673 CE66 6071 FDFF 00F8 2603 1FFF F3F3"
	$"FE33 19CC CCCE 7F66 FF3F CFCC CFFC 9E66"
	$"7CFE 667E 67FE EE66 73CE 6667 F8FD FF00"
	$"F826 031F FFF3 B3FE 3319 CCCC CE7F BDFF"
	$"3F9F 9CCF FCCE 667C FE66 E666 7EFE 6673"
	$"CE66 676C FDFF 00F8 260C 1FFF F878 7078"
	$"33CE 0CCF 3FC3 FFFE 3E10 1FFC E706 7E7E"
	$"01E7 0E7E FE70 79E6 6670 F1FD FF00 F80E"
	$"001F FEFF 04F3 FF3F FFCF E5FF 00F8 0E00"
	$"1FFE FF04 F3F7 3FFD CFE5 FF00 F80D 001F"
	$"FDFF 03F8 7FFE 1FE5 FF00 F806 001F DDFF"
	$"00F8 0600 1FDD FF00 F806 001F DDFF 00F8"
	$"0600 1FDD FF00 F806 001F DDFF 00F8 0600"
	$"1FDD FF00 F806 001F DDFF 00F8 0600 1FDD"
	$"FF00 F806 001F DDFF 00F8 0600 1FDD FF00"
	$"F806 001F DDFF 00F8 0600 1FDD FF00 F806"
	$"001F DDFF 00F8 0600 1FDD FF00 F806 001F"
	$"DDFF 00F8 0600 1FDD FF00 F806 001F DDFF"
	$"00F8 0600 1FDD FF00 F806 001F DDFF 00F8"
	$"0600 1FDD FF00 F806 001F DDFF 00F8 0600"
	$"1FDD FF00 F806 001F DDFF 00F8 0600 1FDD"
	$"FF00 F806 001F DDFF 00F8 0600 1FDD FF00"
	$"F806 001F DDFF 00F8 0600 1FDD FF00 F806"
	$"001F DDFF 00F8 0600 1FDD FF00 F806 001F"
	$"DDFF 00F8 0600 1FDD FF00 F806 001F DDFF"
	$"00F8 0600 1FDD FF00 F806 001F DDFF 00F8"
	$"0600 1FDD FF00 F806 001F DDFF 00F8 0600"
	$"1FDD FF00 F806 001F DDFF 00F8 0600 1FDD"
	$"FF00 F806 001F DDFF 00F8 0600 1FDD FF00"
	$"F806 001F DDFF 00F8 0600 1FDD FF00 F806"
	$"001F DDFF 00F8 0600 1FDD FF00 F806 001F"
	$"DDFF 00F8 0600 1FDD FF00 F806 001F DDFF"
	$"00F8 0600 1FDD FF00 F806 001F DDFF 00F8"
	$"0600 1FDD FF00 F806 001F DDFF 00F8 0600"
	$"1FDD FF00 F806 001F DDFF 00F8 0600 1FDD"
	$"FF00 F806 001F DDFF 00F8 0600 1FDD FF00"
	$"F806 001F DDFF 00F8 0600 1FDD FF00 F802"
	$"DB00 A000 83FF"
};

