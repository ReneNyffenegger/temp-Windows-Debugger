cl   /nologo /c /W4 /GS- /wd4100 prog.c

link /nologo /nodefaultlib prog.obj /entry:start /subsystem:console user32.lib kernel32.lib gdi32.lib    /out:prog.exe
