//
//   https://stackoverflow.com/a/48586906/180275
//
//
//  void ShowMessageText(UINT msg) {
//  
//    wchar_t str[1024];
//    wchar_t* win_msgtext = (wchar_t*)WM_to_text(msg);
//    if (win_msgtext)
//    {
//      //printf(L"WndProc: msg = %x (%s)\n", msg, win_msgtext);
//      wsprintf(str, L"WndProc: msg = %x (%s)\n", msg, win_msgtext);
//      OutputDebugString(str);
//    }
//  }

// To list messages used (and generate an 'ignore' list) call:
//   ShowUsedMessages();

char bufToWriteMessageNumbersOfMessagesThatWereNotFound[10];
  
// win_msg.h file ----------
#define SHOW_USED_MESSAGES 1

// wchar_t* WM_to_text(unsigned int msg);
// const char WM_to_text(unsigned int msg);

#ifdef SHOW_USED_MESSAGES
void ShowUsedMessages(void);
#endif


// List here messages to ignore (-1 signifies end of list)
// if -999 occurs at the start of the list, ALL messages except these are ignored (ie. inverts)
//int msgs_to_ignore[] = { -1 };
//
int msgs_to_ignore[] = { // -999
//   0x20, 0x84, 0xA0,
   0x113
// 0x200
};


// 0x0020 - WM_SETCURSOR (45)
// 0x0084 - WM_NCHITTEST (26)
// 0x0113 - WM_TIMER (46)
// 0x0135 - WM_CTLCOLORBTN (8)
// 0x0200 - WM_MOUSEFIRST (26)

typedef struct {
  unsigned int code;
//  wchar_t* text;
    char*    text;
} XMSGITEM;

// These from https://wiki.winehq.org/List_Of_Windows_Messages
XMSGITEM xmsglist[] = {
  {    0, "WM_NULL"},
  {    1, "WM_CREATE" },
  {    2, "WM_DESTROY" },
  {    3, "WM_MOVE" },
  {    5, "WM_SIZE" },
  {    6, "WM_ACTIVATE" },
  {    7, "WM_SETFOCUS" },
  {    8, "WM_KILLFOCUS" },
  {   10, "WM_ENABLE" },
  {   11, "WM_SETREDRAW" },
  {   12, "WM_SETTEXT" },
  {   13, "WM_GETTEXT" },
  {   14, "WM_GETTEXTLENGTH" },
  {   15, "WM_PAINT" },
  {   16, "WM_CLOSE" },
  {   17, "WM_QUERYENDSESSION" },
  {   18, "WM_QUIT" },
  {   19, "WM_QUERYOPEN" },
  {   20, "WM_ERASEBKGND" },
  {   21, "WM_SYSCOLORCHANGE" },
  {   22, "WM_ENDSESSION" },
  {   24, "WM_SHOWWINDOW" },
  {   25, "WM_CTLCOLOR" },
  {   26, "WM_WININICHANGE" },
  {   27, "WM_DEVMODECHANGE" },
  {   28, "WM_ACTIVATEAPP" },
  {   29, "WM_FONTCHANGE" },
  {   30, "WM_TIMECHANGE" },
  {   31, "WM_CANCELMODE" },
  {   32, "WM_SETCURSOR" },
  {   33, "WM_MOUSEACTIVATE" },
  {   34, "WM_CHILDACTIVATE" },
  {   35, "WM_QUEUESYNC" },
  {   36, "WM_GETMINMAXINFO" },
  {   38, "WM_PAINTICON" },
  {   39, "WM_ICONERASEBKGND" },
  {   40, "WM_NEXTDLGCTL" },
  {   42, "WM_SPOOLERSTATUS" },
  {   43, "WM_DRAWITEM" },
  {   44, "WM_MEASUREITEM" },
  {   45, "WM_DELETEITEM" },
  {   46, "WM_VKEYTOITEM" },
  {   47, "WM_CHARTOITEM" },
  {   48, "WM_SETFONT" },
  {   49, "WM_GETFONT" },
  {   50, "WM_SETHOTKEY" },
  {   51, "WM_GETHOTKEY" },
  {   55, "WM_QUERYDRAGICON" },
  {   57, "WM_COMPAREITEM" },
  {   61, "WM_GETOBJECT" },
  {   65, "WM_COMPACTING" },
  {   68, "WM_COMMNOTIFY" },
  {   70, "WM_WINDOWPOSCHANGING" },
  {   71, "WM_WINDOWPOSCHANGED" },
  {   72, "WM_POWER" },
  {   73, "WM_COPYGLOBALDATA" },
  {   74, "WM_COPYDATA" },
  {   75, "WM_CANCELJOURNAL" },
  {   78, "WM_NOTIFY" },
  {   80, "WM_INPUTLANGCHANGEREQUEST" },
  {   81, "WM_INPUTLANGCHANGE" },
  {   82, "WM_TCARD" },
  {   83, "WM_HELP" },
  {   84, "WM_USERCHANGED" },
  {   85, "WM_NOTIFYFORMAT" },
  {  123, "WM_CONTEXTMENU" },
  {  124, "WM_STYLECHANGING" },
  {  125, "WM_STYLECHANGED" },
  {  126, "WM_DISPLAYCHANGE" },
  {  127, "WM_GETICON" },
  {  128, "WM_SETICON" },
  {  129, "WM_NCCREATE" },
  {  130, "WM_NCDESTROY" },
  {  131, "WM_NCCALCSIZE" },
  {  132, "WM_NCHITTEST" },
  {  133, "WM_NCPAINT" },
  {  134, "WM_NCACTIVATE" },
  {  135, "WM_GETDLGCODE" },
  {  136, "WM_SYNCPAINT" },
  {  160, "WM_NCMOUSEMOVE" },
  {  161, "WM_NCLBUTTONDOWN" },
  {  162, "WM_NCLBUTTONUP" },
  {  163, "WM_NCLBUTTONDBLCLK" },
  {  164, "WM_NCRBUTTONDOWN" },
  {  165, "WM_NCRBUTTONUP" },
  {  166, "WM_NCRBUTTONDBLCLK" },
  {  167, "WM_NCMBUTTONDOWN" },
  {  168, "WM_NCMBUTTONUP" },
  {  169, "WM_NCMBUTTONDBLCLK" },
  {  171, "WM_NCXBUTTONDOWN" },
  {  172, "WM_NCXBUTTONUP" },
  {  173, "WM_NCXBUTTONDBLCLK" },
  {  176, "EM_GETSEL" },
  {  177, "EM_SETSEL" },
  {  178, "EM_GETRECT" },
  {  179, "EM_SETRECT" },
  {  180, "EM_SETRECTNP" },
  {  181, "EM_SCROLL" },
  {  182, "EM_LINESCROLL" },
  {  183, "EM_SCROLLCARET" },
  {  185, "EM_GETMODIFY" },
  {  187, "EM_SETMODIFY" },
  {  188, "EM_GETLINECOUNT" },
  {  189, "EM_LINEINDEX" },
  {  190, "EM_SETHANDLE" },
  {  191, "EM_GETHANDLE" },
  {  192, "EM_GETTHUMB" },
  {  193, "EM_LINELENGTH" },
  {  194, "EM_REPLACESEL" },
  {  195, "EM_SETFONT" },
  {  196, "EM_GETLINE" },
  {  197, "EM_LIMITTEXT" },
  {  197, "EM_SETLIMITTEXT" },
  {  198, "EM_CANUNDO" },
  {  199, "EM_UNDO" },
  {  200, "EM_FMTLINES" },
  {  201, "EM_LINEFROMCHAR" },
  {  202, "EM_SETWORDBREAK" },
  {  203, "EM_SETTABSTOPS" },
  {  204, "EM_SETPASSWORDCHAR" },
  {  205, "EM_EMPTYUNDOBUFFER" },
  {  206, "EM_GETFIRSTVISIBLELINE" },
  {  207, "EM_SETREADONLY" },
  {  209, "EM_SETWORDBREAKPROC" },
  {  209, "EM_GETWORDBREAKPROC" },
  {  210, "EM_GETPASSWORDCHAR" },
  {  211, "EM_SETMARGINS" },
  {  212, "EM_GETMARGINS" },
  {  213, "EM_GETLIMITTEXT" },
  {  214, "EM_POSFROMCHAR" },
  {  215, "EM_CHARFROMPOS" },
  {  216, "EM_SETIMESTATUS" },
  {  217, "EM_GETIMESTATUS" },
  {  224, "SBM_SETPOS" },
  {  225, "SBM_GETPOS" },
  {  226, "SBM_SETRANGE" },
  {  227, "SBM_GETRANGE" },
  {  228, "SBM_ENABLE_ARROWS" },
  {  230, "SBM_SETRANGEREDRAW" },
  {  233, "SBM_SETSCROLLINFO" },
  {  234, "SBM_GETSCROLLINFO" },
  {  235, "SBM_GETSCROLLBARINFO" },
  {  240, "BM_GETCHECK" },
  {  241, "BM_SETCHECK" },
  {  242, "BM_GETSTATE" },
  {  243, "BM_SETSTATE" },
  {  244, "BM_SETSTYLE" },
  {  245, "BM_CLICK" },
  {  246, "BM_GETIMAGE" },
  {  247, "BM_SETIMAGE" },
  {  248, "BM_SETDONTCLICK" },
  {  255, "WM_INPUT" },
  {  256, "WM_KEYDOWN" },
  {  256, "WM_KEYFIRST" },
  {  257, "WM_KEYUP" },
  {  258, "WM_CHAR" },
  {  259, "WM_DEADCHAR" },
  {  260, "WM_SYSKEYDOWN" },
  {  261, "WM_SYSKEYUP" },
  {  262, "WM_SYSCHAR" },
  {  263, "WM_SYSDEADCHAR" },
  {  264, "WM_KEYLAST" },
  {  265, "WM_UNICHAR" },
  {  265, "WM_WNT_CONVERTREQUESTEX" },
  {  266, "WM_CONVERTREQUEST" },
  {  267, "WM_CONVERTRESULT" },
  {  268, "WM_INTERIM" },
  {  269, "WM_IME_STARTCOMPOSITION" },
  {  270, "WM_IME_ENDCOMPOSITION" },
  {  271, "WM_IME_COMPOSITION" },
  {  271, "WM_IME_KEYLAST" },
  {  272, "WM_INITDIALOG" },
  {  273, "WM_COMMAND" },
  {  274, "WM_SYSCOMMAND" },
  {  275, "WM_TIMER" },
  {  276, "WM_HSCROLL" },
  {  277, "WM_VSCROLL" },
  {  278, "WM_INITMENU" },
  {  279, "WM_INITMENUPOPUP" },
  {  280, "WM_SYSTIMER" },
  {  287, "WM_MENUSELECT" },
  {  288, "WM_MENUCHAR" },
  {  289, "WM_ENTERIDLE" },
  {  290, "WM_MENURBUTTONUP" },
  {  291, "WM_MENUDRAG" },
  {  292, "WM_MENUGETOBJECT" },
  {  293, "WM_UNINITMENUPOPUP" },
  {  294, "WM_MENUCOMMAND" },
  {  295, "WM_CHANGEUISTATE" },
  {  296, "WM_UPDATEUISTATE" },
  {  297, "WM_QUERYUISTATE" },
  {  306, "WM_CTLCOLORMSGBOX" },
  {  307, "WM_CTLCOLOREDIT" },
  {  308, "WM_CTLCOLORLISTBOX" },
  {  309, "WM_CTLCOLORBTN" },
  {  310, "WM_CTLCOLORDLG" },
  {  311, "WM_CTLCOLORSCROLLBAR" },
  {  312, "WM_CTLCOLORSTATIC"    },
  {  512, "WM_MOUSEMOVE"         },                // WM_MOUSEFIRST
  {  513, "WM_LBUTTONDOWN" },
  {  514, "WM_LBUTTONUP" },
  {  515, "WM_LBUTTONDBLCLK" },
  {  516, "WM_RBUTTONDOWN" },
  {  517, "WM_RBUTTONUP" },
  {  518, "WM_RBUTTONDBLCLK" },
  {  519, "WM_MBUTTONDOWN" },
  {  520, "WM_MBUTTONUP" },
  {  521, "WM_MBUTTONDBLCLK" },                   // WM_MOUSELAST
  {  522, "WM_MOUSEWHEEL" },
  {  523, "WM_XBUTTONDOWN" },
  {  524, "WM_XBUTTONUP" },
  {  525, "WM_XBUTTONDBLCLK" },
  {  528, "WM_PARENTNOTIFY" },
  {  529, "WM_ENTERMENULOOP" },
  {  530, "WM_EXITMENULOOP" },
  {  531, "WM_NEXTMENU" },
  {  532, "WM_SIZING" },
  {  533, "WM_CAPTURECHANGED" },
  {  534, "WM_MOVING" },
  {  536, "WM_POWERBROADCAST" },
  {  537, "WM_DEVICECHANGE" },
  {  544, "WM_MDICREATE" },
  {  545, "WM_MDIDESTROY" },
  {  546, "WM_MDIACTIVATE" },
  {  547, "WM_MDIRESTORE" },
  {  548, "WM_MDINEXT" },
  {  549, "WM_MDIMAXIMIZE" },
  {  550, "WM_MDITILE" },
  {  551, "WM_MDICASCADE" },
  {  552, "WM_MDIICONARRANGE" },
  {  553, "WM_MDIGETACTIVE" },
  {  560, "WM_MDISETMENU" },
  {  561, "WM_ENTERSIZEMOVE" },
  {  562, "WM_EXITSIZEMOVE" },
  {  563, "WM_DROPFILES" },
  {  564, "WM_MDIREFRESHMENU" },
  {  640, "WM_IME_REPORT" },
  {  641, "WM_IME_SETCONTEXT" },
  {  642, "WM_IME_NOTIFY" },
  {  643, "WM_IME_CONTROL" },
  {  644, "WM_IME_COMPOSITIONFULL" },
  {  645, "WM_IME_SELECT" },
  {  646, "WM_IME_CHAR" },
  {  648, "WM_IME_REQUEST" },
  {  656, "WM_IMEKEYDOWN" },
  {  656, "WM_IME_KEYDOWN" },
  {  657, "WM_IMEKEYUP" },
  {  657, "WM_IME_KEYUP" },
  {  672, "WM_NCMOUSEHOVER" },
  {  673, "WM_MOUSEHOVER" },
  {  674, "WM_NCMOUSELEAVE" },
  {  675, "WM_MOUSELEAVE" },
  {  768, "WM_CUT" },
  {  769, "WM_COPY" },
  {  770, "WM_PASTE" },
  {  771, "WM_CLEAR" },
  {  772, "WM_UNDO" },
  {  773, "WM_RENDERFORMAT" },
  {  774, "WM_RENDERALLFORMATS" },
  {  775, "WM_DESTROYCLIPBOARD" },
  {  776, "WM_DRAWCLIPBOARD" },
  {  777, "WM_PAINTCLIPBOARD" },
  {  778, "WM_VSCROLLCLIPBOARD" },
  {  779, "WM_SIZECLIPBOARD" },
  {  780, "WM_ASKCBFORMATNAME" },
  {  781, "WM_CHANGECBCHAIN" },
  {  782, "WM_HSCROLLCLIPBOARD" },
  {  783, "WM_QUERYNEWPALETTE" },
  {  784, "WM_PALETTEISCHANGING" },
  {  785, "WM_PALETTECHANGED" },
  {  786, "WM_HOTKEY" },
  {  791, "WM_PRINT" },
  {  792, "WM_PRINTCLIENT" },
  {  793, "WM_APPCOMMAND" },
  {  856, "WM_HANDHELDFIRST" },
  {  863, "WM_HANDHELDLAST" },
  {  864, "WM_AFXFIRST" },
  {  895, "WM_AFXLAST" },
  {  896, "WM_PENWINFIRST" },
  {  897, "WM_RCRESULT" },
  {  898, "WM_HOOKRCRESULT" },
  {  899, "WM_GLOBALRCCHANGE" },
  {  899, "WM_PENMISCINFO" },
  {  900, "WM_SKB" },
  {  901, "WM_HEDITCTL" },
  {  901, "WM_PENCTL" },
  {  902, "WM_PENMISC" },
  {  903, "WM_CTLINIT" },
  {  904, "WM_PENEVENT" },
  {  911, "WM_PENWINLAST" },
  { 1024, "WM_USER" },
};

// 1003 messages
#define NUM_XMSGS (sizeof(xmsglist) / sizeof(XMSGITEM))
int ignore_msg[NUM_XMSGS];
static int xmsgs_initialized = 0;

#ifdef SHOW_USED_MESSAGES
int used_freq[NUM_XMSGS];
#endif

//-------------------------------------------------
// returns -1 if not found
int msgid_to_index(unsigned int msg) {

  static unsigned int first, cur, last; //138nS
  //register unsigned int first,cur,last;   //173nS

  // Use bchop to find message code
  first = 0;
  last = NUM_XMSGS;

  while (1) {
    cur = (first + last) / 2;

    if (msg < xmsglist[cur].code) {

      if (cur == last)
        return (-1);          // not found
      else
        last = cur;
    }
    else {
      if (msg == xmsglist[cur].code) { // found
        return (cur);
      }

      if (cur == first)
        return (-1);          // not found
      else
        first = cur;
    }
  }
}

//-------------------------------------------------
#define MAX_XMIGNORES (sizeof(msgs_to_ignore) / sizeof(int))

void initialise_xmsgs(void) {
  int msg,index;
  int invert = 0;

  if (msgs_to_ignore[0] == -999) invert = 1;

  for (int i = 0; i < NUM_XMSGS; i++) {
    ignore_msg[i] = invert; 
#ifdef SHOW_USED_MESSAGES
    used_freq[i] = 0;
#endif
  }

  for (int i = 0; i < MAX_XMIGNORES; i++)
  {
    msg = msgs_to_ignore[i];
    if (msg == -1) break;

    index = msgid_to_index(msg);
    if (index != -1) {
      if (index < NUM_XMSGS)
      {
        ignore_msg[index] = invert ^ 1;
      }
      else
      {
        index = NUM_XMSGS;
      }
    }
  }
  xmsgs_initialized = 1;
}

//-------------------------------------------------
const char* WM_to_text(unsigned int msg) {

   int index;

  // Setup ignore list on first call
  if (!xmsgs_initialized) {
    initialise_xmsgs();
  }

  index = msgid_to_index(msg);
  if (index == -1) {
     wsprintfA(bufToWriteMessageNumbersOfMessagesThatWereNotFound, "%d", msg);
//   return "-1";
     return bufToWriteMessageNumbersOfMessagesThatWereNotFound;
  }


  //not found - bad msg id

#ifdef SHOW_USED_MESSAGES
  used_freq[index]++;
#endif

  if (ignore_msg[index]) {
     return "ignored.";
//   return NULL;
  }
  return xmsglist[index].text;
}

//-------------------------------------------------
#ifdef SHOW_USED_MESSAGES
void ShowUsedMessages() {

  char str[1024];
  char* p = str;
  int count = 0;
  int lastmsg;

// Find last message - to exclude ',' at end
   for (int i = 0; i < NUM_XMSGS; i++) {
      if (used_freq[i]) lastmsg = i;
   }
  
  // Pass 1 - output table for inclusion
//OutputDebugString("\nint msgs_to_ignore[] = {\n");

  for (int i = 0; i < NUM_XMSGS; i++) {

    if (used_freq[i]) {

      p += wsprintfA(p, "0x%X", xmsglist[i].code);
      count++;

      if (i == lastmsg)
        count = 8;
      else
        *p++ = ',';

      if (count >= 8)
      {
        *p++ = '\n';
        *p++ = '\0';
        OutputDebugString(str);
        p = str;
        count = 0;
      }
    }
  }
  OutputDebugString("};\n");

  // Pass 2 - add message text and frequencies
  for (int i = 0; i < NUM_XMSGS; i++)
  {
    if (used_freq[i])
    {
      wsprintfA(str, "// 0x%04X - %s (%d)\n", xmsglist[i].code, xmsglist[i].text, used_freq[i]);
      OutputDebugString(str);
    }
  }
}
#endif
