#!/usr/bin/env bash
set -xeu

[ -f acctproc.c ]
[ -f chngproc.c ]
[ -f fileproc.c ]

export CVS_RSH=ssh

# Initial checkout done using:
#   cvs -d anoncvs@anoncvs.ca.openbsd.org:/cvs/src/usr.sbin/acme-client checkout -P .

set +u
. /usr/lib/git-core/git-sh-setup
require_clean_work_tree "update from openbsd tree"
set -u

git checkout openbsd

cvs up -PAd

if [ -n "$(git status -z --porcelain | egrep -zv '^?? CVS/Entries$')" ]; then
	echo "Some changes present, commiting."
	git add .
	git commit -m "Update from openbsd ($(date -u '+%Y-%m-%d %H:%M:%S') UTC)"
else
	echo "No new changes detected"
	git checkout -- CVS/Entries
fi
