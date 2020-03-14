AC_PREREQ([2.69])

AC_INIT([acme-client], [0.2.7], [wolf@wolfsden.cz])

AC_CONFIG_SRCDIR([main.c])
AC_CONFIG_SRCDIR([acctproc.c])
AC_CONFIG_SRCDIR([fileproc.c])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADERS([config.h])

AC_CANONICAL_SYSTEM
AC_CANONICAL_HOST

AM_INIT_AUTOMAKE([-Wall -Werror foreign dist-xz])

AC_PROG_CC
AC_PROG_CC_STDC
if test "$ac_cv_prog_cc_stdc" == "no"; then
	AC_MSG_ERROR([C compiler does not support std mode.])
fi
AC_PROG_CPP
AC_PROG_CPP_WERROR
AC_PROG_YACC

AC_CONFIG_MACRO_DIRS([m4])

AX_CHECK_OPENSSL([], [AC_MSG_ERROR([Openssl not found.])])

AC_FUNC_FORK
AC_CHECK_FUNCS([pledge unveil])
AC_REPLACE_FUNCS([err errx warn warnx vwarnx asprintf vasprintf strlcat strtonum reallocarray recallocarray])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
