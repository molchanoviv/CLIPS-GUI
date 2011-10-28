#define MANAGER_BUTTON  0
#define BUTTON_BOX      1
#define MENU_BUTTON     2
#define DIALOG_WIN      3
#define FACTS_WIN       4
#define INSTANCES_WIN   5
#define GLOBALS_WIN     6
#define AGENDA_WIN      7
#define FOCUS_WIN       8
#define PULLDOWN_MENUS  9
#define MANAGERS        10
#define CONFIRMATION    11
#define FILE_WIN        12
#define WATCH_OPTIONS   13
#define WATCH_OPTION_BUTTONS 14

#define FOREGROUND      0
#define BACKGROUND      1
#define BORDER          2
#define NOT_AVAILABLE   3

static String items[] = {
"aliceblue",
"antiquewhite",
"aquamarine1",
"aquamarine2",
"aquamarine3",
"aquamarine4",
"azure1",
"azure2",
"azure3",
"azure4",
"beige",
"bisque1",
"bisque2",
"bisque3",
"bisque4",
"black",
"blanchedalmond",
"blueviolet",
"blue1",
"blue2",
"blue3",
"blue4",
"brown",
"brown1",
"brown2",
"brown3",
"brown4",
"burlywood",
"burlywood1",
"burlywood2",
"burlywood3",
"burlywood4",
"cadetblue",
"chartreuse1",
"chartreuse2",
"chartreuse3",
"chartreuse4",
"chocolate",
"chocolate1",
"chocolate2",
"chocolate3",
"chocolate4",
"coral",
"coral1",
"coral2",
"coral3",
"coral4",
"cornflowerblue",
"cornsilk1",
"cornsilk2",
"cornsilk3",
"cornsilk4",
"cyan1",
"cyan2",
"cyan3",
"cyan4",
"darkgoldenrod",
"darkgreen",
"darkkhaki",
"darkolivegreen",
"darkorange",
"darkorchid",
"darksalmon",
"darkseagreen",
"darkslateblue",
"darkslategray",
"darkturquoise",
"darkviolet",
"firebrick",
"firebrick1",
"firebrick2",
"firebrick3",
"firebrick4",
"floralwhite",
"forestgreen",
"gainsboro",
"ghostwhite",
"gold1",
"gold2",
"gold3",
"gold4",
"goldenrod",
"goldenrod1",
"goldenrod2",
"goldenrod3",
"goldenrod4",
"gray",
"gray1",
"gray2",
"gray3",
"gray4",
"gray5",
"gray6",
"gray7",
"gray8",
"gray9",
"gray10",
"gray11",
"gray12",
"gray13",
"gray14",
"gray15",
"gray16",
"gray17",
"gray18",
"gray19",
"gray20",
"gray21",
"gray22",
"gray23",
"gray24",
"gray25",
"gray26",
"gray27",
"gray28",
"gray29",
"gray30",
"gray31",
"gray32",
"gray33",
"gray34",
"gray35",
"gray36",
"gray37",
"gray38",
"gray39",
"gray40",
"gray41",
"gray42",
"gray43",
"gray44",
"gray45",
"gray46",
"gray47",
"gray48",
"gray49",
"gray50",
"gray51",
"gray52",
"gray53",
"gray54",
"gray55",
"gray56",
"gray57",
"gray58",
"gray59",
"gray60",
"gray61",
"gray62",
"gray63",
"gray64",
"gray65",
"gray66",
"gray67",
"gray68",
"gray69",
"gray70",
"gray71",
"gray72",
"gray73",
"gray74",
"gray75",
"gray76",
"gray77",
"gray78",
"gray79",
"gray80",
"gray81",
"gray82",
"gray83",
"gray84",
"gray85",
"gray86",
"gray87",
"gray88",
"gray89",
"gray90",
"gray91",
"gray92",
"gray93",
"gray94",
"gray95",
"gray96",
"gray97",
"gray98",
"gray99",
"greenyellow",
"green1",
"green2",
"green3",
"green4",
"honeydew1",
"honeydew2",
"honeydew3",
"honeydew4",
"hotpink",
"indianred",
"ivory1",
"ivory2",
"ivory3",
"ivory4",
"khaki",
"khaki1",
"khaki2",
"khaki3",
"khaki4",
"lavender",
"lawngreen",
"lightblue",
"lightcoral",
"lightgoldenrod",
"lightgoldenrodyellow",
"lightgray",
"lightpink",
"lightseagreen",
"lightskyblue",
"lightslateblue",
"lightslategray",
"lightsteelblue",
"lightyellow",
"limegreen",
"linen",
"magenta1",
"magenta2",
"magenta3",
"magenta4",
"maroon",
"maroon1",
"maroon2",
"maroon3",
"maroon4",
"mediumorchid",
"mediumpurple",
"mediumseagreen",
"mediumslateblue",
"mediumspringgreen",
"mediumturquoise",
"mediumvioletred",
"midnightblue",
"mintcream",
"mistyrose",
"moccasin",
"navy",
"oldlace",
"olivedrab",
"orangered",
"orange1",
"orange2",
"orange3",
"orange4",
"orchid",
"orchid1",
"orchid2",
"orchid3",
"orchid4",
"palegoldenrod",
"palegreen",
"paleturquoise",
"palevioletred",
"papayawhip",
"pink",
"pink1",
"pink2",
"pink3",
"pink4",
"plum",
"plum1",
"plum2",
"plum3",
"plum4",
"powderblue",
"purple",
"purple1",
"purple2",
"purple3",
"purple4",
"red1",
"red2",
"red3",
"red4",
"rosybrown",
"royalblue",
"salmon",
"salmon1",
"salmon2",
"salmon3",
"salmon4",
"sandybrown",
"seashell1",
"seashell2",
"seashell3",
"seashell4",
"sienna",
"sienna1",
"sienna2",
"sienna3",
"sienna4",
"skyblue",
"slateblue",
"slategray",
"snow1",
"snow2",
"snow3",
"snow4",
"steelblue",
"tan",
"tan1",
"tan2",
"tan3",
"tan4",
"thistle",
"thistle1",
"thistle2",
"thistle3",
"thistle4",
"tomato1",
"tomato2",
"tomato3",
"tomato4",
"turquoise",
"turquoise1",
"turquoise2",
"turquoise3",
"turquoise4",
"violet",
"violetred",
"wheat",
"wheat1",
"wheat2",
"wheat3",
"wheat4",
"white",
"yellow1",
"yellow2",
"yellow3",
"yellow4",
NULL};
