#include <windows.h>

#include "WM_to_text.h"

//
//   https://devblogs.microsoft.com/oldnewthing/20041025-00/?p=37483:
//
//      The pseudovariable __ImageBase represents the DOS header of the module,
//      which happens to be what a Win32 module begins with.
//      In other words, it’s the base address of the module.
//      And the module base address is the same as its HINSTANCE.
//
HINSTANCE __ImageBase;

HANDLE   stdOut;
unsigned int indent = 0;

void print(const char* text, unsigned int len) {

   DWORD charsWritten;

   for (unsigned int i=0; i< indent*2; i++) {
      WriteConsoleA(stdOut, " ", 1, &charsWritten, NULL);
   }
   WriteConsoleA(stdOut, text, len, &charsWritten, NULL);
   WriteConsoleA(stdOut, "\n",   1, &charsWritten, NULL);

}



typedef union {

   LPARAM value;
   struct {
      unsigned repeat_count       : 16;
      unsigned scan_code          :  8;
      unsigned extended_key       :  1;
      unsigned reserved           :  4;
      unsigned context_code       :  1; // Always 0 for WM_KEYDOWN
      unsigned previous_key_state :  1;
      unsigned transition_state   :  1; // Always 0 for WM_KEYDOWN
   } keydown_keyup_char; // WM_KEYDOWN, WM_KEYUP, WM_CHAR

} lparam;

typedef union {
  WPARAM value;
  struct {
    WPARAM virtual_key_code;
  } keydown_keyup; // WM_KEYDOWN, WM_KEYUP (But not WM_CHAR!)
  struct {
    WPARAM character_code;
  } char_; // WM_CHAR
  

} wparam;

typedef struct {
  HWND   hwnd;
  UINT   message;
  wparam wParam;
//WPARAM wParam;
//LPARAM lParam;
  lparam lParam;
  DWORD  time;
  POINT  pt;
  DWORD  lPrivate;
} win_msg;


LRESULT CALLBACK WndProc (
    HWND   hWnd,
    UINT   msg,
//  WPARAM wParam,
    wparam wParam,
//  LPARAM lParam
    lparam lParam
    ) {

  indent ++;


  char buf[200];
  int len;

  if (msg == WM_CHAR) {

     len = wsprintfA(buf, "win proc, %s: scan code: %d, character code code: %d, repeat count: %d",
        WM_to_text(msg),
        lParam.keydown_keyup_char.scan_code,
        wParam.char_.character_code,
        lParam.keydown_keyup_char.repeat_count
      );

     print(buf, len);
  }
  else {
     len = wsprintfA(buf, "win proc, %s (%d, %d)", WM_to_text(msg), wParam.value, lParam.value);
     print(buf, len);
  }



//len = wsprintfA(buf, "sizeof(WPARAM) = %d", sizeof(WPARAM));
//print(buf, len);
//len = wsprintfA(buf, "sizeof(LPARAM) = %d", sizeof(LPARAM));
//print(buf, len);
  switch (msg) {
    case WM_PAINT: {

      PAINTSTRUCT ps;
      HDC hDC = BeginPaint(hWnd, &ps);
      TextOutA(hDC, 10, 10, "Hello world", 11);
      EndPaint(hWnd, &ps);
    }
    break;

    case WM_DESTROY:
      PostQuitMessage(0);
    break;

    default:
      indent --;
      return DefWindowProc( hWnd, msg, wParam.value, lParam.value);
  } 
  indent --;
  return 0;
}

ULONG __stdcall start(void* PEB) {


   stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   print("started", 8);


// HINSTANCE   __ImageBase = GetModuleHandleA(NULL);
   WNDCLASSEXA wce;

   wce.cbSize        = sizeof(wce);
   wce.style         = CS_VREDRAW | CS_HREDRAW; 
   wce.lpfnWndProc   = (WNDPROC) WndProc; 
   wce.cbClsExtra    = 0; 
   wce.cbWndExtra    = 0; 
   wce.hInstance     = __ImageBase;
   wce.hIcon         = LoadIcon  ((HINSTANCE) NULL, IDI_APPLICATION); 
   wce.hCursor       = LoadCursor((HINSTANCE) NULL, IDC_ARROW      ); 
   wce.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); 
   wce.lpszMenuName  = 0;
   wce.lpszClassName = "tq84WinClass", // "ADPWinClass",
   wce.hIconSm       = 0;
 
   if (!RegisterClassEx(&wce)) return 0; 
   
   HWND hWnd = CreateWindowExA(
      0,                   // Ex Styles
      wce.lpszClassName,   // className,
     "Title",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT,       // x
      CW_USEDEFAULT,       // y
      CW_USEDEFAULT,       // Height
      CW_USEDEFAULT,       // Width
      NULL,                // Parent Window
      NULL,                // Menu, or windows id if child
      __ImageBase,         //
      NULL                 // Pointer to window specific data
   );

   ShowWindow(hWnd, SW_SHOWDEFAULT);

   win_msg msg;
// MSG msg;
   int r;

   while ((r = GetMessageA((LPMSG) &msg, NULL, 0, 0 )) != 0) { 
     indent ++;

     char buf[200];
     int len;

     if (msg.message == WM_KEYDOWN || msg.message == WM_KEYUP) {
        len = wsprintfA(buf, "%s: scan code: %d, virtual key code: %d, repeat count: %d",
            WM_to_text(msg.message),
            msg.lParam.keydown_keyup_char.scan_code,
            msg.wParam.keydown_keyup.virtual_key_code,
            msg.lParam.keydown_keyup_char.repeat_count);
        print(buf, len);
     }
     else if (msg.message == WM_CHAR) {
        len = wsprintfA(buf, "%s: scan code: %d, character code: %d, repeat count: %d",
            WM_to_text(msg.message),
            msg.lParam.keydown_keyup_char.scan_code,
            msg.wParam.char_.character_code,
            msg.lParam.keydown_keyup_char.repeat_count);
        print(buf, len);
     }
     else {
         len = wsprintfA(buf, "got message %s (%d, %d)", WM_to_text(msg.message), msg.wParam, msg.lParam);
         print(buf, len);
      }

     if (r == -1) {

       print("r == -1, exiting", 16);
       return 1;// Error!
     }
     else {
       indent++;
       print("TranslateMessage", 16);
       TranslateMessage((LPMSG) &msg); 
       print("DispatchMessage" , 15);
       DispatchMessage ((LPMSG) &msg); 
       indent--;
     }
     indent --;
   } 

   // The application's return value
   return 0; // msg.wParam;

}
