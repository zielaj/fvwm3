## Process this file with automake to create Makefile.in

program_transform_name =

moduledir = @FVWM_MODULEDIR@

module_PROGRAMS = FvwmShell

FvwmShell_SOURCES = FvwmShell.c
FvwmShell_DEPENDENCIES = $(top_builddir)/libs/libfvwm3.a

man_MANS = 

# Use X_EXTRA_LIBS to get socket(), etc.
LDADD = -L$(top_builddir)/libs -lfvwm3 $(readline_LIBS) $(X_EXTRA_LIBS)

# FIXME:
# Despite not using X functions explicitly, the code includes
# fvwmlib.h, which *does* include X headers and xpm.h!
AM_CPPFLAGS = -I$(top_srcdir) $(readline_CFLAGS) $(xpm_CFLAGS) $(X_CFLAGS)
