%define D_RESET 00h
%define D_STATUS 01h
%define D_READ 02h
%define D_WRITE 03h
%define D_VERIFY 04h
%define D_FORMATT 05h
%define D_FORMATTBS 06h
%define D_FORMFROM 07h
%define D_READPARAMS 08h
%define D_READTYPE 15h
%define D_PARKHEADS 19h

%define HD_INIT 09h
%define HD_LONGREAD 0ah
%define HD_LONGWRITE 0bh
%define HD_MOVEHEAD 0ch
%define HD_RESET 0dh
%define HD_ISREADY 10h
%define HS_RECALIBRATE 11h
%define HD_DIAG 14h

%define PS_READTEST 0eh
%define PS_WRITETEST 0fh
%define PS_RAMTEST 12h
%define PS_DRVTEST 13h

%define FD_TESTMCH 16h
%define FD_SETMTF1 17h
%define FD_SETMTF2 18h

%define EXT_TESTEXT 41h
%define EXT_READ 42h
%define EXT_WRITE 43h
%define EXT_VERIFY 44h
%define EXT_TLOCK 45h
%define EXT_EJECT 46h
%define EXT_MOVEHEAD 47h
%define EXT_READPARAMS 48h
%define EXT_TESTMCH 49h

;#####################################

%define TYPE_FD1 00h
%define TYPE_FD2 01h
%define TYPE_HD1 80h
%define TYPE_HD2 81h
%define TYPE_CD e0h