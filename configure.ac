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
AC_REPLACE_FUNCS([
	asprintf
	err
	errx
	reallocarray
	recallocarray
	strlcat
	strtonum
	vasprintf
	vwarnx
	warn
	warnx
])

AX_ADD_CFLAG([-D_GNU_SOURCE=1])
AX_ADD_CFLAG([-Wall])
AX_ADD_CFLAG([-Wextra])
AX_ADD_CFLAG([-Wformat])
AX_ADD_CFLAG([-Wmissing-declarations])
AX_ADD_CFLAG([-Wmissing-prototypes])
AX_ADD_CFLAG([-Wpointer-arith])
AX_ADD_CFLAG([-Wshadow])
AX_ADD_CFLAG([-Wsign-compare])
AX_ADD_CFLAG([-Wstrict-prototypes])
AX_ADD_CFLAG([-Wundef])
AX_ADD_CFLAG([-Wunused])
AX_ADD_CFLAG([-Wvla])

# Handle -flto in platform specific manner
case "$host" in
*solaris*)
	# flto seems broken on solaris, so do not use it:
	# https://github.com/graywolf/acme-client-portable/pull/5#issuecomment-599510762
	;;
*)
	AX_ADD_CFLAG([-flto])
	AX_ADD_LDFLAG([-flto])
	;;
esac

# Platform specific CPPFLAGS
case "$host" in
*aix*|*os400*)
	# malloc is different, workaround
	CPPFLAGS="$CPPFLAGS -D_LINUX_SOURCE_COMPAT"
	;;
esac

AC_ARG_ENABLE(
	devel,
	[  --enable-devel   Enable development compilation flags],
	[AM_CONDITIONAL(DEVEL_MODE, test 0 -eq 0)],
	[AM_CONDITIONAL(DEVEL_MODE, test 0 -ne 0)],
)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
