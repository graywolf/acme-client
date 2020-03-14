# ===========================================================================
#     https://www.gnu.org/software/autoconf-archive/ax_check_bsd.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_CHECK_BSD([action-if-found[, action-if-not-found]])
#
# DESCRIPTION
#
#   Look for bsd in a number of default spots, or in a user-selected
#   spot (via --with-bsd).  Sets
#
#     BSD_INCLUDES to the include directives required
#     BSD_LIBS to the -l directives required
#     BSD_LDFLAGS to the -L or -R flags required
#
#   and calls ACTION-IF-FOUND or ACTION-IF-NOT-FOUND appropriately
#
#   This macro sets BSD_INCLUDES such that source files should use the
#   bsd/ directory in include directives:
#
#     #include <bsd/bsd.h>
#
# LICENSE
#
#   Copyright (c) 2019 Tomas Volf <wolf@wolfsden.cz>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved. This file is offered as-is, without any
#   warranty.
#
# This script is based on AX_CHECK_OPENSSL, serial 10.

#serial 1

AU_ALIAS([CHECK_BSD], [AX_CHECK_BSD])
AC_DEFUN([AX_CHECK_BSD], [
    found=false
    skip_bsd=false
    case "$host" in
        *-*-aix*|*-*-os400*)
            AC_MSG_CHECKING([AIX libbsd is not fd.o libbsd, skipping])
            # libbsd is *NOT* fd.o libbsd! it's a gigantic footgun instead
            skip_bsd=true
            BSD_LIBS=""
            BSD_INCLUDES=""
            BSD_LDFLAGS=""
            ;;
    esac
    if ! $skip_bsd; then
    AC_ARG_WITH([bsd],
        [AS_HELP_STRING([--with-bsd=DIR],
            [root of the bsd directory])],
        [
            case "$withval" in
            "" | y | ye | yes | n | no)
            AC_MSG_ERROR([Invalid --with-bsd value])
              ;;
            *) bsddirs="$withval"
              ;;
            esac
        ], [
            # if pkg-config is installed and openssl has installed a .pc file,
            # then use that information and don't search bsddirs
            AC_CHECK_TOOL([PKG_CONFIG], [pkg-config])
            if test x"$PKG_CONFIG" != x""; then
                BSD_LDFLAGS=`$PKG_CONFIG libbsd --libs-only-L 2>/dev/null`
                if test $? = 0; then
                    BSD_LIBS=`$PKG_CONFIG libbsd --libs-only-l 2>/dev/null`
                    BSD_INCLUDES=`$PKG_CONFIG libbsd --cflags-only-I 2>/dev/null`
                    found=true
                fi
            fi

            # no such luck; use some default bsddirs
            if ! $found; then
                bsddirs="/usr/local/bsd /usr/lib/bsd /usr/bsd /usr/pkg"
                bsddirs="${bsddirs} /usr/local /usr"
            fi
        ]
        )


    # note that we #include <bsd/foo.h>, so the bsd headers have to be in
    # an 'bsd' subdirectory

    if ! $found; then
        BSD_INCLUDES=
        for bsddir in $bsddirs; do
            AC_MSG_CHECKING([for bsd/bsd.h in $bsddir])
            if test -f "$bsddir/include/bsd/bsd.h"; then
                BSD_INCLUDES="-I$bsddir/include"
                BSD_LDFLAGS="-L$bsddir/lib"
                BSD_LIBS="-lbsd"
                found=true
                AC_MSG_RESULT([yes])
                break
            else
                AC_MSG_RESULT([no])
            fi
        done

        # if the file wasn't found, well, go ahead and try the link anyway -- maybe
        # it will just work!
    fi

    # try the preprocessor and linker with our new flags,
    # being careful not to pollute the global LIBS, LDFLAGS, and CPPFLAGS

    AC_MSG_CHECKING([whether compiling and linking against libbsd works])
    echo "Trying link with BSD_LDFLAGS=$BSD_LDFLAGS;" \
        "BSD_LIBS=$BSD_LIBS; BSD_INCLUDES=$BSD_INCLUDES" >&AS_MESSAGE_LOG_FD

    save_LIBS="$LIBS"
    save_LDFLAGS="$LDFLAGS"
    save_CPPFLAGS="$CPPFLAGS"
    LDFLAGS="$LDFLAGS $BSD_LDFLAGS"
    LIBS="$BSD_LIBS $LIBS"
    CPPFLAGS="$BSD_INCLUDES $CPPFLAGS"
    AC_LINK_IFELSE(
        [AC_LANG_PROGRAM([#include <bsd/stdlib.h>], [strtonum(NULL, 0, 0, NULL)])],
        [
            AC_MSG_RESULT([yes])
            $1
        ], [
            AC_MSG_RESULT([no])
            $2
        ])
    CPPFLAGS="$save_CPPFLAGS"
    LDFLAGS="$save_LDFLAGS"
    LIBS="$save_LIBS"
    fi

    AC_SUBST([BSD_INCLUDES])
    AC_SUBST([BSD_LIBS])
    AC_SUBST([BSD_LDFLAGS])
])
