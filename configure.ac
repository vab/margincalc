dnl Process this file with autoconf to produce a configure script.
AC_INIT([margincalc], [0.0.1])
AC_CONFIG_SRCDIR([src/margincalc.c])
AM_INIT_AUTOMAKE

dnl Set of available languages.
ALL_LINGUAS="en"

dnl Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

dnl Checks for header files.
AC_HEADER_STDC

AC_SUBST(PKG_CPPFLAGS)
AC_SUBST(PKG_LIBS)
AC_SUBST(PKG_CFLAGS)
AC_SUBST(PKG_FFLAGS)

dnl Force autotools to put the exectuables where the user wants them
if test [ \"NONE\" == \"$prefix\" ]; then
        AC_SUBST(BINDIR, "/usr/bin")
else
        AC_SUBST(BINDIR, "$prefix/bin")
fi

dnl Force autotools to put the man files where the user wants them
if test [ \"NONE\" == \"$prefix\" ]; then
        AC_SUBST(mandir, "/usr/share/man")
else
        AC_SUBST(mandir, "$prefix/share/man")
fi


dnl Files to process
AC_OUTPUT([Makefile src/Makefile doc/Makefile])

