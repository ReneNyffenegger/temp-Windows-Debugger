//
//  cl prog.c user32.lib
//

#include <windows.h>

int WinMain(HINSTANCE h0, HINSTANCE h1, LPSTR cmdLine, int show) {

  MessageBox(0, "The number is: 42", "Hello world", 0);

  ExitProcess(42);

}
