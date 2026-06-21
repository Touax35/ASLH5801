del ..\..\..\asst9\tst9.rel
del ..\..\..\asst9\tst9.lst
del ..\..\..\asst9\tst9.hlr
del ..\..\..\asst9\tst9.rst
..\exe\asst9.exe -gloacxff ..\..\..\asst9\tst9.asm
..\exe\asxscn.exe -i ..\..\..\asst9\tst9.lst
..\exe\aslink -nxu -g xN=0 -g xNN=0 -g X0=0 -g X1=1 -g X2=2 -g X3=3 -g X4=4 -g X5=5 -g X6=6 -g X7=7 ..\..\..\asst9\tst9.rel
..\exe\asxscn.exe -i ..\..\..\asst9\tst9.rst
del ..\..\..\asst9\tst9.rel
del ..\..\..\asst9\tst9.lst
del ..\..\..\asst9\tst9.hlr
del ..\..\..\asst9\tst9.rst
..\exe\asst9.exe -gloacxff -i ".define GLOBAL" ..\..\..\asst9\tst9.asm
..\exe\aslink -nxu -g xN=0 -g xNN=0 -g X0=0 -g X1=1 -g X2=2 -g X3=3 -g X4=4 -g X5=5 -g X6=6 -g X7=7 ..\..\..\asst9\tst9.rel
..\exe\asxscn.exe -i ..\..\..\asst9\tst9.rst

