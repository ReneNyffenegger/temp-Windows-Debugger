$hostDir = (get-item ( where.exe cl.exe ) ).directory.parent.fullname

& $hostDir\x64\cl /Zi /c func.c /Fofunc-64.obj
& $hostDir\x64\cl /Zi /c prog.c /Foprog-64.obj

& $hostDir\x64\cl /Zi func-64.obj prog-64.obj user32.lib /Feprog-64.exe


