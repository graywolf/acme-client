AC_PREREQ([2.69])

AC_INIT([acme-client], [0.2.6], [wolf@wolfsden.cz])

AC_CONFIG_SRCDIR([main.c])
AC_CONFIG_SRCDIR([acctproc.c])
AC_CONFIG_SRCDIR([fileproc.c])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADERS([config.h])

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
AX_CHECK_BSD([], [AC_MSG_ERROR([Libbsd not found.])])

AC_FUNC_FORK
AC_CHECK_FUNCS([pledge unveil])
AC_REPLACE_FUNCS([reallocarray recallocarray])

# Compiling with libbsd can cause this error on some systems:
# #warning usage of non-standard #include <sys/cdefs.h> is deprecated [-Werror=cpp]
# if so, compile with -Wno-cpp to make it pass
AC_MSG_CHECKING([whether including bsd/stdlib.h is without warnings])
save_CPPFLAGS="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS -Werror=cpp -Werror"
AC_COMPILE_IFELSE(
	[AC_LANG_SOURCE(
		[[
			#include <stdlib.h>
			#include <bsd/stdlib.h>
		]]
	)],
	[AC_MSG_RESULT([yes])],
	[
		AC_MSG_RESULT([no])
		save_CPPFLAGS="$save_CPPFLAGS -Wno-cpp"
	]
)
CPPFLAGS="$save_CPPFLAGS"

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
