#include <windows.h>
#include <stdio.h>
#include <tchar.h>




int dispatchDebugEvent(const DEBUG_EVENT* debugEvent) {
    printf("dispatchDebugEvent\n");
    switch (debugEvent->dwDebugEventCode) {
    case CREATE_PROCESS_DEBUG_EVENT:
        // TBD
        break;

    case CREATE_THREAD_DEBUG_EVENT:
        // TBD
        break;

    case EXCEPTION_DEBUG_EVENT:
        // TBD
        break;

    case EXIT_PROCESS_DEBUG_EVENT:
        // TBD
        break;

    case EXIT_THREAD_DEBUG_EVENT:
        // TBD
        break;

    case LOAD_DLL_DEBUG_EVENT:
        // TBD
        break;

    case UNLOAD_DLL_DEBUG_EVENT:
        // TBD
        break;

    case OUTPUT_DEBUG_STRING_EVENT:
        // TBD
        break;

    case RIP_EVENT:
        // TBD
        break;

    default:
        printf("Unknown debug event.\n");
        return 0;
        break;
    }
    return 1;
}
      


void debug_loop() {

  DEBUG_EVENT debugEvent;
	

  while (WaitForDebugEvent(&debugEvent, INFINITE)) {
      DWORD debuggeeprocessID = debugEvent.dwProcessId;
      DWORD debuggeethreadID = debugEvent.dwThreadId;
      if (dispatchDebugEvent(&debugEvent)) {
          ContinueDebugEvent(debuggeeprocessID, debuggeethreadID, DBG_CONTINUE);
      }
      else {
          break;
      }
  }

}
int _tmain() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

//  SECURITY_ATTRIBUTES saPrc;
//  SECURITY_ATTRIBUTES saThr;

//  ZeroMemory(&saPrc, sizeof(saPrc));
//  ZeroMemory(&saThr, sizeof(saThr));
//  saPrc.nLength = sizeof(saPrc);
//  saThr.nLength = sizeof(saThr);

    printf("sizeof SECURITY_ATTRIBUTES: %d\n", sizeof(SECURITY_ATTRIBUTES));

    printf("sizeof si = %d\n", sizeof(si));
    printf("sizeof pi = %d\n", sizeof(pi));


    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );


    // Start the child process. 
    if( !CreateProcess(
       "C:\\Program Files\\Microsoft Office\\Office14\\EXCEL.EXE",             // Moudle
       NULL, // "C:\\Program Files\\Microsoft Office\\Office14\\EXCEL.EXE",             // Command line
       NULL,//&saPrc,                  // Process handle not inheritable
       NULL,//&saThr,                  // Thread handle not inheritable
        FALSE,                  // Set handle inheritance to FALSE
        DEBUG_ONLY_THIS_PROCESS | CREATE_NEW_CONSOLE,
        NULL,                   // Use parent's environment block
        NULL,                   // Use parent's starting directory 
        &si,                    // Pointer to STARTUPINFO structure
        &pi )                   // Pointer to PROCESS_INFORMATION structure
    ) 
    {
        printf( "CreateProcess failed (%d).\n", GetLastError() );
        return (0);
    }
    printf("xxx\n");

    debug_loop();

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );

    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}
