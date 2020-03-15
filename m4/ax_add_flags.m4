# SYNOPSIS
#
#   AX_ADD_CFLAG(FLAG)
#   AX_ADD_CPPFLAG(FLAG)
#   AX_ADD_LDFLAG(FLAG)
#
# DESCRIPTION
#
#   Adds FLAG to (C|CPP|LD)FLAGS only if it is supported.
#
# LICENSE
#
#   Copyright (c) 2019 Tomas Volf <wolf@wolfsden.cz>
#
#   WTFPL ver. 2

#serial 1

AC_DEFUN([AX_ADD_CFLAG], [
	AX_CHECK_COMPILE_FLAG([$1], [CFLAGS="$CFLAGS $1"])
])
AC_DEFUN([AX_ADD_CPPFLAG], [
	AX_CHECK_PREPRO_FLAG([$1], [CPPFLAGS="$CPPFLAGS $1"])
])
AC_DEFUN([AX_ADD_LDFLAG], [
	AX_CHECK_LINK_FLAG([$1], [LDFLAGS="$LDFLAGS $1"])
])
