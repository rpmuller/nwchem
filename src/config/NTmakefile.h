##############################################################################
#
# include makefile for nmake under Windows NT
#
##############################################################################

#
#	$Id: NTmakefile.h,v 1.3 2000-07-27 15:50:25 bjohnson Exp $
#

#
# If NWCHEM_TOP_WIN32 is set, take it.  Otherwise, if NWCHEM_TOP is set,
# use that.  One of the two must be set, however.
#
!IFNDEF NWCHEM_TOP_WIN32
!IFDEF NWCHEM_TOP
NWCHEM_TOP_WIN32 = $(NWCHEM_TOP)
!ELSE
!MESSAGE You must define NWCHEM_TOP in your environment to be the path
!MESSAGE of the top level nwchem directory in DOS format ... e.g.
!MESSAGE     NWCHEM_TOP="D:\PNNL\nwchem"
!MESSAGE
!ERROR NWCHEM_TOP not set.
!ENDIF
!ENDIF

TOPDIR = $(NWCHEM_TOP_WIN32)
SRCDIR = $(TOPDIR)\src
LIBDIR = $(TOPDIR)\lib\win32
# !!! This is called LIB_DISTRIB in prev NT makefiles
# !!! Also, one can override LIB_DISTRIB if desired this way
# !!! Should LIB_DISTRIB just be changed to LIBDIR?
LIB_DISTRIB = $(LIBDIR)
#BINDIR = $(TOPDIR)\bin\win32
INCDIR = $(TOPDIR)\src\include
CNFDIR = $(TOPDIR)\src\config
OBJDIR = .\obj

!IFNDEF SCRATCH_DEF_DIR
SCRATCH_DEF_DIR = "'.'"
!ENDIF
!IFNDEF PERM_DEF_DIR
PERM_DEF_DIR = "'.'"
!ENDIF

GLOB_DEFINES =-DWIN32 -DUSE_FCD
DEFINES = $(GLOB_DEFINES) $(LIB_DEFINES)
GLOB_INCLUDES= -I"$(SRCDIR)\include" -I"$(SRCDIR)\tools\include"
INCLUDES = $(GLOB_INCLUDES) $(LIB_INCLUDES)

#AR = link.exe -lib -nologo
AR = lib -nologo
ARFLAGS = /out:$(LIBRARY_PATH)

CC = cl -nologo
#COPT =   -Zi
COPT =   -Z7
#COPT =  -G5 -O2
CFLAGS = -W3 $(COPT) $(DEFINES) $(INCLUDES) -Fo"$(OBJDIR)/" -c

FC = fl32 -nologo
#FOPT = -Zi
FOPT = -G5 -Ox
#FFLAGS = $(FOPT) -Fo"$(OBJDIR)/" -c

#FFLAGS=/check:all /debug:full /nooptimize /extend_source:132 $(INCLUDES) $(DEFINES) /traceback /warn:argument_checking /warn:nofileopt /warn:nouncalled /pdbfile:"$(OBJDIR)/" /object:"$(OBJDIR)/" /fpp:"/c /m" /nodefine /nokeep -c

FFLAGS=/check:none /Z7 /nooptimize /extend_source:132 $(INCLUDES) $(DEFINES) /traceback /warn:argument_checking /warn:nofileopt /warn:nouncalled /object:"$(OBJDIR)/" /fpp:"/c /m" /nodefine /nokeep -c

#CPP   = $(CC) -EP
#CPPFLAGS = $(INCLUDES) $(DEFINES)

.SUFFIXES:
.SUFFIXES:      .obj .s .F .c

.c{$(OBJDIR)}.obj:
	$(CC) $(CFLAGS) $<

!IF 0
.F{$(OBJDIR)}.obj:
	$(CPP) $(CPPFLAGS) $< > $*.for
	$(FC) $(FFLAGS) $*.for
	@del $*.for
!ELSE
.F{$(OBJDIR)}.obj:
	$(FC) $(FFLAGS) $<
!ENDIF

#.F.for:
#        $(CPP) $(CPPFLAGS) $< > $*.for
