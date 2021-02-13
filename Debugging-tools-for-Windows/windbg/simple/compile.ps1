


#  $hostDir = (get-item ( where.exe cl.exe ) ).directory.parent.fullname
#  
#  # & $hostDir\x64\cl /Zi /c func.c /Fofunc-cl-64.obj
#  # & $hostDir\x64\cl /Zi /c prog.c /Foprog-cl-64.obj
#  
#  # & $hostDir\x64\cl /Zi func-64.obj prog-cl-64.obj user32.lib /Feprog-cl-64.exe
#    & $hostDir\x64\cl /Zi             prog-cl-64.obj user32.lib /Feprog-cl-64.exe

dev-env # 64

  & cl /nologo /Zi /c func.c /Fofunc-cl-64.obj
  & cl /nologo /Zi /c prog.c /Foprog-cl-64.obj
 
  & cl /nologo /Zi func-cl-64.obj prog-cl-64.obj user32.lib /Feprog-cl-64.exe
# & cl /nologo /Zi             prog-cl-64.obj user32.lib /Feprog-cl-64.exe
