AM_CFLAGS = \
	-D_GNU_SOURCE=1 \
	-Wall \
	-Werror \
	-Wextra \
	-Wmissing-declarations \
	-Wmissing-prototypes \
	-Wpointer-arith \
	-Wshadow \
	-Wsign-compare \
	-Wstrict-prototypes \
	-Wundef \
	-Wunused \
	@BSD_INCLUDES@ \
	@OPENSSL_INCLUDES@
AM_LDFLAGS = \
	@BSD_LDFLAGS@ \
	@OPENSSL_LDFLAGS@


bin_PROGRAMS = acme-client

acme_client_SOURCES = \
	acctproc.c \
	base64.c \
	certproc.c \
	chngproc.c \
	compat.c \
	compat.h \
	dbg.c \
	dnsproc.c \
	extern.h \
	fileproc.c \
	http.c \
	http.h \
	jsmn.c \
	jsmn.h \
	json.c \
	key.c \
	key.h \
	keyproc.c \
	main.c \
	netproc.c \
	parse.h \
	parse.y \
	revokeproc.c \
	util.c
acme_client_LDADD = \
	@BSD_LIBS@ \
	@OPENSSL_LIBS@

dist_man_MANS = \
	acme-client.1 \
	acme-client.conf.5

# vim: noet ts=8 sts=8 sw=8:
