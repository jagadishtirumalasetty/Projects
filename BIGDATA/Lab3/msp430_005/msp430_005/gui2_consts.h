#ifndef _GUI2_CONSTS_H_
#define _GUI2_CONSTS_H_

//Gadget Constants (gui.dba)
//==========================
//Robert Knight 2006
//Modified by Jack Toole


#define GUI_CONSTANTS 1

//  EVENTS:

#define KEYDOWN           0x100
#define KEYUP             0x101
#define GUI_COMMAND       0x111

#define MOUSE_MOVE        0x200
#define LEFT_DOWN         0x201
#define MOUSE_CLICK       0x202
#define LEFT_UP           0x202
#define DBL_CLICK         0x203

#define RIGHT_DOWN        0x204
#define RIGHT_CLICK       0x205
#define RIGHT_UP          0x205

#define TOOLBAR_CLICK     0x111
#define GADGET_TIMER      0x113
#define HOTKEY            0x312
#define MENU_CLICK        0x401
//  comboboxchange doesn't work for listboxes
#define COMBOBOX_CHANGE   0x403
#define TREEVIEW_CHANGE   0x404
#define TRACKBAR_CHANGE   0x0E0

#define GADGET_MOVE       0x003
#define WINDOW_MAXIMIZE   0x003
#define GADGET_SIZE       0x005
#define LOSEFOCUS         0x008
#define WINDOW_CLOSE      0x010
#define BORDERCLICK       0x0A1
#define GADGET_SIZING     0x214
#define GADGET_MOVING     0x216



//  BORDER STYLES:

#define BORDER_NONE       0
#define BORDER_FLAT       1
#define BORDER_3D         2
#define BORDER_SUNKEN     3



//  ALIGN VALUES:

#define ALIGN_NONE        0
#define ALIGN_ALL         1
#define ALIGN_TOP         2
#define ALIGN_LEFT        3
#define ALIGN_RIGHT       4
#define ALIGN_BOTTOM      5



//  STANDARD TOOLBAR BUTTONS:
//call addStandardButtons immediately after toolbar creation, then call addButton (see gui.dba)

#define TOOLBAR_CUT          0
#define TOOLBAR_COPY         1
#define TOOLBAR_PASTE        2
#define TOOLBAR_UNDO         3
#define TOOLBAR_REDO         4
#define TOOLBAR_DELETE       5
#define TOOLBAR_NEW          6
#define TOOLBAR_OPEN         7
#define TOOLBAR_SAVE         8
#define TOOLBAR_PRINTPREVIEW 9
#define TOOLBAR_PROPERTIES   10
#define TOOLBAR_HELP         11
#define TOOLBAR_FIND         12
#define TOOLBAR_REPLACE      13
#define TOOLBAR_PRINT        14



//  WINDOW STYLES:

//Gives the window a titlebar
#define WINDOW_TITLEBAR      12582912
#define WINDOW_CLOSEBUTTON   524288
#define WINDOW_MAXBUTTON     65536
#define WINDOW_MINBUTTON     131072
#define WINDOW_RESIZEABLE    262144
#define WINDOW_NOBORDER      0x80000000
#define WINDOW_MAXIMIZED     16777216
#define WINDOW_MINIMIZED     536870912
#define WINDOW_DISABLED      134217728

//  EXTRA STYLES:
#define WINDOW_TOOLWINDOW      128

//  STANDARD STYLES:
#define WINDOW_NORMAL        13565952 //WINDOW_TITLEBAR+WINDOW_CLOSEBUTTON+WINDOW_MAXBUTTON+WINDOW_MINBUTTON+WINDOW_RESIZEABLE
#define WINDOW_FIXED         13107200
#define WINDOW_OVR           0



//  LISTVIEW STYLES:

//Big icons with captions underneath, ideal for texture/model browsers etc
#define LISTVIEW_ICON        0
//A table where each item can have additional information (subitems) listed as well
#define LISTVIEW_REPORT      1
//Small icons with captions to their right.
#define LISTVIEW_LIST        3



//  KEYDOWN VALUES:
//  These represent various keyboard key eventData() values from the KEYDOWN event

#define KEY_DELETE        46
#define KEY_ENTER         13
#define KEY_LEFT          37
#define KEY_UP            38
#define KEY_RIGHT         39
#define KEY_MINUS         189
#define KEY_PLUS          187
#define KEY_BACKSLASH     220


//  CSIDL FOLDERID VALUES
//  for use with getSpecialPath(CSIDL)

#define CSIDL_PROGRAMS     0x002
#define CSIDL_MYDOCUMENTS  0x005
#define CSIDL_STARTUP      0x007
#define CSIDL_SENDTO       0x009
#define CSIDL_STARTMENU    0x00B
#define CSIDL_MYMUSIC      0x00D
#define CSIDL_DESKTOP      0x010
#define CSIDL_FONTS        0x014
#define CSIDL_ALLPROGRAMS  0x017
#define CSIDL_USERAPPDATA  0x01A
#define CSIDL_ALLAPPDATA   0x023
#define CSIDL_WINDOWS      0x024
#define CSIDL_SYSTEM       0x025
#define CSIDL_MYPICTURES   0x027
#define CSIDL_PROFILE      0x028

#define TEXT_ALIGN_LEFT    0
#define TEXT_ALIGN_CENTER  1
#define TEXT_ALIGN_RIGHT   2




#endif