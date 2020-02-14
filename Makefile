all: debuggee.exe debugger.exe

debuggee.exe: debuggee.c
	gcc $< -o $@

debugger.exe: debugger.c
	gcc $< -o $@
