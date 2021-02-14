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


LRESULT CALLBACK WndProc (
    HWND   hWnd,
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam ) {

  indent ++;
  print("called back", 11);
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
      return DefWindowProc( hWnd, msg, wParam, lParam);
  } 
  indent --;
  return 0;
}

ULONG __stdcall start(void* PEB) {


   stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   print("started\n", 9);


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

   MSG msg;
   int r;

   while ((r = GetMessageA(&msg, NULL, 0, 0 )) != 0) { 
     indent ++;

     char buf[200];
     int len = wsprintfA(buf, "got message %s (%d, %d)", WM_to_text(msg.message), msg.wParam, msg.lParam);
     print(buf, len);

     if (r == -1) {

       print("r == -1, exiting", 16);
       return 1;// Error!
     }
     else {
       TranslateMessage(&msg); 
       DispatchMessage (&msg); 
     }
     indent --;
   } 

   // The application's return value
   return 0; // msg.wParam;

}
