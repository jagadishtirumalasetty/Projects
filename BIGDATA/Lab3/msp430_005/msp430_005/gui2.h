#ifndef _GUI2_H_
#define _GUI2_H_

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "gui2_consts.h"

class CGadget;
typedef CGadget* handle;
typedef char* str;

void message_int(str title, int msg);

extern "C"
{
	void startBlue(); /* Sencond stage of BlueGUI setup */
	void processEvents(); /* You must call this during your loop for each gadget! */

	void setGadgetDefaults(bool visible);
	void setGadgetColor(handle gadget, DWORD background, DWORD text);

	int questionMessage(str msg, str title);
	void warningMessage(str msg);
	void message(const char * title, const char * msg);

	void setWindowIcon(handle gadget, char* fileName);

	void attachGadget(handle target, int tabPage, handle attach);
	void detachGadget(handle target, int tabPage, handle detach);

	void enableXPStyles(CGadget* gadget, int xpStyles);

 handle				createButton(int x, int y, int width, int height, char* caption,bool flat,handle parent);
 handle				createPanel(int x, int y, int width, int height, handle parent);
 handle				createFrame(int x, int y, int width, int height, char* caption,handle parent);
 handle				createEdit(int x, int y, int width, int height, int settings,handle parent);
 handle				createLabel(int x, int y, int width, int height, char* caption, handle parent);
 handle				createTransparentLabel(int x, int y, int width, int height, char* caption, handle parent);
 handle				createCanvas(int x, int y, int width, int height, handle parent);
 handle				createCheckbox(int x, int y, int width, int height, char* caption, handle parent);
 handle				createRadiobutton(int x, int y, int width, int height, char* caption, handle parent);
 handle				createListbox(int x, int y, int width, int height, handle parent);
 handle				createListview(int x, int y, int width, int height, handle parent);
 handle				createCombobox(int x, int y, int width, int height, handle parent);
 handle				createTabs(int x, int y, int width, int height, int style, handle parent);
 handle				createUpDown_noBuddy(int x, int y, int width, int height, handle parent);
 handle				createUpDown_buddy(int x, int y, int width, int height, handle buddy, int style, handle parent);
 handle				createScrollbar(int x, int y, int width, int height, int style, handle parent);
 handle				createTrackbar(int x, int y, int width, int height, int vertical, handle parent);
 handle				createTreeview(int x, int y, int width, int height, handle parent);
 handle				createToolbar(handle parent);
 handle				createStatusbar(handle parent);
 handle				createWindow(int x, int y, int width, int height, 
								 char* caption, int styles, int extraStyles, int createTopMost, handle parent);
 handle				createGadgetFromWindow(HWND existingWindow);
 handle				copyGadget(handle existingGadget);

//Image List
 handle	createImageList(int width, int height);
 void					addImageListItem(handle imageList, char* fileName);
 void					addImageListItem_FromMem(handle imageList, int imageIndex);

//Menu
 handle			createMenu(handle parent);
 handle			createPopupMenu();
 handle			createSubMenu(handle parent, int item);
 void					addMenuItem(handle menu, char* caption, int returnValue);
 void					addMenuSplitter(handle menu);
 void					setMenuItemChecked(handle menu, int item, int boolChecked);
 void					setMenuItemEnabled(handle menu, int item, int boolEnabled);
 int					getMenuItemChecked(handle menu, int item);
 int					getMenuItemEnabled(handle menu, int item);
 DWORD				getMenuItemText(DWORD oldString, handle menu, int item);
 int					getMenuItemCount(handle menu);
 int					showPopupMenu(handle menu);
 void					setMenuItemRadio(handle menu, int firstGroupItem, int lastGroupItem, int selectItem);
   
//Events
 void					getEvent_wait(int waitEvent);
 void					getEvent();
 void					getEventStack();
 handle				eventSource();
 DWORD				eventType();
 DWORD				eventData();
 DWORD				eventDataEx();
 handle				gadgetClicked();

//General Gadget Functions
 void					moveGadget(handle gadget, int x, int y);
 void					resizeGadget(handle gadget, int width, int height);
 void					setGadget(handle gadget, int x, int y,int width, int height);
 void					paintGadget(handle gadget);
 void					doGadgetAlign(handle gadget);
 void					setGadgetAlign(handle gadget, int align);
 void					setGadgetTextAlign(handle gadget,DWORD textAlignment);
 void					setGadgetVisible(handle gadget, int flag);
 void					setGadgetVisible_center(handle gadget, int visible, BOOL centerInParent);
 void					bringToFront(handle gadget);
 void					setGadgetEnabled(handle gadget, DWORD flag);
 void					setGadgetParent(handle gadget, handle parent);


 handle				getParentGadget(handle gadget);


 void					deleteGadget(handle gadget);
 int					deleteGadget_returnNull(handle gadget);

 int					gadgetX(handle gadget);
 int					gadgetY(handle gadget);
 int					gadgetX_relative(handle gadget, handle relativeTo);
 int					gadgetY_relative(handle gadget, handle relativeTo);
 int					gadgetWidth(handle gadget);
 int					gadgetHeight(handle gadget);
  int					gadgetClientWidth(handle gadget);
 int					gadgetClientHeight(handle gadget);
 void					setGadgetText(handle gadget, const char* text);
 DWORD				getGadgetText(DWORD oldString, handle gadget);
 int					getGadgetVisible(handle gadget);
 HWND					gadgetHandle(handle gadget);
 DWORD				getGadgetEnabled(handle gadget);

//Helper Functions
 handle				gadgetUnderMouse();
 HWND					mainWindow();
 HWND					desktopWindow();
 HWND					windowHandle(handle gadget);
 handle				activeGadget();
 int					mousePosX(handle gadget);
 int					mousePosY(handle gadget);
 int					mousePosX_noGadget();
 int					mousePosY_noGadget();
 void					createHotKey(int hotKeyId, int requireAlt, int requireShift, int requireCtrl, int keyCode);
 void					deleteHotKey(int hotKeyId);
 int					getTextWidth(handle font, char* text);
 int					getTextHeight(handle font, char* text);

//Special Functions

//Panel Gadgets
	 void		setPanelBorderStyle(handle gadget,int borderStyle);
	 void		setPanelImage(handle gadget, char* imageFileName);
	 void		setPanelImageFromMem(handle gadget, int imageIndex);

//Button Gadgets
	 void		setButtonImage(handle gadget, char* imageFileName);
	 void		setButtonImageFromMem(handle gadget, int imageIndex);

//Edit Gadgets
	 void		setReadOnly(handle gadget, bool readOnly);
	 void		setSelStart(handle gadget, int selStart);
	 void		setSelLen(handle gadget, int selLength);

	 int		getReadOnly(handle gadget);
	 int		getSelStart(handle gadget);
	 int		getSelLen(handle gadget);

//Checkbox Gadgets
	 void		setChecked(handle gadget, bool checked);
	 int		getChecked(handle gadget);

//Listbox/Combobox Gadgets
	 void		addItem(handle gadget, const char* caption);
	 void		addItem_index(handle gadget, const char* caption, int index);
	 void		removeItem(handle gadget, int index);
	 void		changeItem(handle gadget, int index, char* newCaption);
	 void		selectItem(handle gadget, int index);
	 int		selectedItem(handle gadget);
	 DWORD	itemText(DWORD oldString, handle gadget, int index);
	 DWORD	itemCount(handle gadget);

//Tab Gadgets
	 void		addTab(handle gadget, char* caption);
	 void		addTab_index(handle gadget, char* caption, int index);
	 void		removeTab(handle gadget, int index);
	 void		changeTab(handle gadget, int index, char* newCaption);
	 int		selectedTab(handle gadget);
	 DWORD	tabCaption(DWORD oldString, handle gadget, int index);
	 int		tabCount(handle gadget);

//Statusbar Gadgets
	 void		addStatusPanel(handle gadget, int width);
	 void		setStatusText(handle gadget, int panelIndex, char* caption);
	 void		removeStatusPanel(handle gadget, int index);
	 int		statusPanelCount(handle gadget);
	 DWORD	getStatusText(DWORD oldString, handle gadget, int index);

//Scrollbar Gadgets
	 void		setScrollbarRange(handle gadget, int min, int max);
	 void		setScrollbarPosition(handle gadget, int position);
	 int		getScrollbarPosition(handle gadget);
	 int		getScrollbarMin(handle gadget);
	 int		getScrollbarMax(handle gadget);
	 void		setScrollbarThumbSize(handle gadget, int size);
	 int		getScrollbarThumbSize(handle gadget);

//UpDown Gadgets
	 void		setUpDownRange(handle gadget, int min, int max);
	 void		setUpDownPosition(handle gadget, int position);

	 int		getUpDownPosition(handle gadget);
	 int		getUpDownMin(handle gadget);
	 int		getUpDownMax(handle gadget);

//Toolbar Gadgets
	 void		addToolbarButton_image(handle gadget, char* fileName, int makeCheckButton);
	 void		addToolbarButton_index(handle gadget, int index, int makeCheckButton);
	 void		addStandardToolbarButtons(handle gadget);
	 void		removeToolbarButton(handle gadget, int index); //Not done
	 void		addToolbarSplitter(handle gadget);

	 int		getToolbarItem(handle gadget);

//Trackbar Gadgets
	 void		setTrackbarRange(handle gadget, int min, int max);
	 void		setTrackbarPosition(handle gadget, int position);
	 void		setTrackbarTickFrequency(handle gadget, int frequency);
	 int		getTrackbarMin(handle gadget);
	 int		getTrackbarMax(handle gadget);
	 int		getTrackbarPosition(handle gadget);

//Canvas Gadgets
	 void		drawText(handle gadget, int x, int y, char* text);
	 void		drawLine(handle gadget, int x1, int y1, int x2, int y2);
	 void		drawRect(handle gadget, int x1, int y1, int x2, int y2);
	 void		drawEllipse(handle gadget, int x1, int y1, int x2, int y2);
	 void		drawPoint(handle gadget, int x, int y, DWORD color);

//Listview gadgets
	 void		addListViewItem(handle gadget, char* caption, int image);
	 void		setListViewImageList(handle gadget, handle images);
	 void		setListViewImageList_withIndex(handle gadget, handle images, int listIndex);
	 void		addListViewColumn(handle gadget, char* caption, int width);
	 int		getListViewItemCount(handle gadget);
	 void		setListViewStyle(handle gadget, int style);
	 void		setListViewItemText(handle gadget, int index, int subItemIndex, char* caption);
	 void		selectListViewItem(handle gadget, int index);
	 int		selectedListViewItem(handle gadget);
	 void		removeListViewItem(handle gadget, int index);

//Treeview gadgets
	 handle	addTreeViewItem(handle gadget, handle parent, int image, char* caption);
	 handle	addTreeViewItem_index(handle gadget, handle parent, int image, char* caption, handle insertAfter);
	 void			setTreeViewImageList(handle gadget, handle imageList, int index);
	 void			removeTreeViewItem(handle gadget, handle item);
	 handle	selectedTreeViewItem(handle gadget);
	 void			selectTreeViewItem(handle gadget, handle item);
	 void			setTreeViewItemText(handle gadget, handle item, char* text);

	 //Fonts
	 handle createFont(const char* name, int size, int bold, int italic, int underline);
	 void deleteFont(handle font);
	 void applyFont(handle gadget, handle font);
}



inline void message_int(str title, int msg)
{
	char buffer[16];
	sprintf_s(buffer,"%d",msg);
	message(title, buffer);
}


#define messagef(title, format, ...)                     \
	do {                                                 \
		char __messagef_buffer[256];                     \
		sprintf_s(__messagef_buffer,format,__VA_ARGS__); \
		message(title, __messagef_buffer);               \
	} while (0)


#endif