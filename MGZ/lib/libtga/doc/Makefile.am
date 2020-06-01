# Most of this Makefile.am was taken from Documentation/DocBook/Makefile
# from the Linux kernel tree

EXTRA_DIST=api.sgml

pdf: api.sgml
	@(which db2pdf > /dev/null 2>&1) || \
	 (echo "*** You need to install DocBook stylesheets ***"; \
	  exit 1)
	db2pdf $<

ps: api.sgml
	@(which db2ps > /dev/null 2>&1) || \
	 (echo "*** You need to install DocBook stylesheets ***"; \
	  exit 1)
	db2ps $<

html: api.sgml
	@(which db2html > /dev/null 2>&1) || \
	 (echo "*** You need to install DocBook stylesheets ***"; \
	  exit 1)
	db2html $<

clean:
	rm -rf api.ps api.pdf api
