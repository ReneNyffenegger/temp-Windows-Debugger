#include <windows.h>
#include <stdio.h>
#include <tchar.h>


#define case_printf(c) case c: printf("Exc: " #c "\n"); break;


int dispatchDebugEvent(const DEBUG_EVENT* debugEvent) {

//  printf("ev: %5d %5d ", debugEvent->dwProcessId, debugEvent->dwThreadId);

    switch (debugEvent->dwDebugEventCode) {

    case CREATE_PROCESS_DEBUG_EVENT:
        printf("CREATE_PROCESS_DEBUG_EVENT\n");
        break;

    case CREATE_THREAD_DEBUG_EVENT:
        printf("CREATE_THREAD_DEBUG_EVENT\n");
        break;

    case EXCEPTION_DEBUG_EVENT:
//      printf("EXCEPTION_DEBUG_EVENT\n");

//      printf("   %d ", debugEvent->u.Exception.dwFirstChance);

        switch (debugEvent->u.Exception.ExceptionRecord.ExceptionCode) {

          case EXCEPTION_ACCESS_VIOLATION: break;

//        case_printf(EXCEPTION_ACCESS_VIOLATION)
          case_printf(EXCEPTION_ARRAY_BOUNDS_EXCEEDED)
          case_printf(EXCEPTION_BREAKPOINT)
          case_printf(EXCEPTION_DATATYPE_MISALIGNMENT)
          case_printf(EXCEPTION_FLT_DENORMAL_OPERAND)
          case_printf(EXCEPTION_FLT_DIVIDE_BY_ZERO)
          case_printf(EXCEPTION_FLT_INEXACT_RESULT)
          case_printf(EXCEPTION_FLT_INVALID_OPERATION)
          case_printf(EXCEPTION_FLT_OVERFLOW)
          case_printf(EXCEPTION_FLT_STACK_CHECK)
          case_printf(EXCEPTION_FLT_UNDERFLOW)
          case_printf(EXCEPTION_ILLEGAL_INSTRUCTION)
          case_printf(EXCEPTION_IN_PAGE_ERROR)
          case_printf(EXCEPTION_INT_DIVIDE_BY_ZERO)
          case_printf(EXCEPTION_INT_OVERFLOW)
          case_printf(EXCEPTION_INVALID_DISPOSITION)
          case_printf(EXCEPTION_NONCONTINUABLE_EXCEPTION)
          case_printf(EXCEPTION_PRIV_INSTRUCTION)
          case_printf(EXCEPTION_SINGLE_STEP)
          case_printf(EXCEPTION_STACK_OVERFLOW)

          default: "?";

        }
        break;


    case EXIT_PROCESS_DEBUG_EVENT:
        printf("EXIT_PROCESS_DEBUG_EVENT\n");
        break;

    case EXIT_THREAD_DEBUG_EVENT:
        printf("EXIT_THREAD_DEBUG_EVENT\n");
        break;

    case LOAD_DLL_DEBUG_EVENT:
        printf("LOAD_DLL_DEBUG_EVENT\n");
        break;

    case UNLOAD_DLL_DEBUG_EVENT:
        printf("UNLOAD_DLL_DEBUG_EVENT\n");
        break;

    case OUTPUT_DEBUG_STRING_EVENT:
        printf("OUTPUT_DEBUG_STRING_EVENT\n");
        break;

    case RIP_EVENT:
        printf("RIP_EVENT\n");
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
      DWORD debuggeethreadID  = debugEvent.dwThreadId;

      if (dispatchDebugEvent(&debugEvent)) {
          if (!ContinueDebugEvent(debuggeeprocessID, debuggeethreadID, DBG_CONTINUE)) {
            printf("ContinueDebugEvent returned false!\n");
            exit(-1);
          }
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

//  printf("sizeof SECURITY_ATTRIBUTES: %d\n", sizeof(SECURITY_ATTRIBUTES));

//  printf("sizeof si = %d\n", sizeof(si));
//  printf("sizeof pi = %d\n", sizeof(pi));


    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );


    // Start the child process.
    if( !CreateProcess(
       "C:\\Program Files\\Microsoft Office\\Office14\\EXCEL.EXE",             // Module
        NULL,                                                                  // Command line
        NULL,                                       //&saPrc,                  // Process handle not inheritable
        NULL,                                       //&saThr,                  // Thread handle not inheritable
        FALSE,                                                                 // Set handle inheritance to FALSE
        DEBUG_ONLY_THIS_PROCESS | CREATE_NEW_CONSOLE,
        NULL,                                                                  // Use parent's environment block
        NULL,                                                                  // Use parent's starting directory
        &si,                                                                   // Pointer to STARTUPINFO structure
        &pi )                                                                  // Pointer to PROCESS_INFORMATION structure
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
