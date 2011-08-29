# File:   Makefile
# Author: M. P. Hayes, UCECE
# Date:   12 Sep 2010
# Descr:  Makefile to create application Makefiles from a template.

# Abandon all hope ye who look in here.
# This Makefile builds all the application Makefiles
# using template Makefiles and a python script makemake.py that parses
# the applications looking for #includes.

APPDIRS = $(filter-out ../apps/README, $(wildcard ../apps/*))
TESTDIRS = $(APPDIRS)
DOCDIRS = $(addsuffix /doc, $(APPDIRS))

TESTMAKEFILES = $(addsuffix /Makefile.test, $(APPDIRS))
APPMAKEFILES = $(addsuffix /Makefile, $(TESTDIRS))
DOCMAKEFILES = $(addsuffix /Makefile, $(DOCDIRS))

MAKEAPPS = $(addsuffix .apps, $(APPDIRS))
MAKETESTS = $(addsuffix .tests, $(TESTDIRS))
MAKEDOCS = $(addsuffix .docs, $(DOCDIRS))

CLEANAPPS = $(addsuffix .cleanapps, $(APPDIRS))
CLEANTESTS = $(addsuffix .cleantests, $(TESTDIRS))
CLEANDOCS = $(addsuffix .cleandocs, $(APPDIRS))

all: testmakefiles appmakefiles docmakefiles apps tests docs

clean: cleanapps cleantests cleandocs

docmakefiles: $(DOCMAKEFILES)

testmakefiles: $(TESTMAKEFILES)

appmakefiles: $(APPMAKEFILES)

docs: $(DOCMAKEFILES)

../%/doc/Makefile: Makefile.doc.template Makefile makemake.py
	mkdir -p $(dir $@)
	(cd $(dir $@)/..; ../../etc/makemake.py --relpath --template ../../etc/Makefile.doc.template . . ../../utils ../../fonts ../../drivers ../../drivers/avr > doc/Makefile)

../%/Makefile.test: Makefile.test.template Makefile
	(cd $(dir $@);	../../etc/makemake.py --cc="gcc" --cflags="" --relpath --objext=-test.o --template ../../etc/Makefile.test.template . . ../../utils ../../drivers ../../drivers/test > Makefile.test)

../%/Makefile: Makefile.template Makefile makemake.py
	(cd $(dir $@);	../../etc/makemake.py --cc="avr-gcc" --cflags="-Os -mmcu=atmega32u2" --relpath --template ../../etc/Makefile.template . . ../../utils ../../fonts ../../drivers ../../drivers/avr > Makefile)



# Compile all the applications.
apps: $(MAKEAPPS)

.PHONY: $(MAKEAPPS)
$(MAKEAPPS):
	-@$(MAKE) -C $(subst .apps,,$@)

# Compile all the test applications.
tests: $(MAKETESTS)

.PHONY: $(MAKETESTS)
$(MAKETESTS):
	-@$(MAKE) -f Makefile.test -C $(subst .tests,,$@)

# Make all the docs.
docs: $(MAKEDOCS)

.PHONY: $(MAKEDOCS)
$(MAKEDOCS):
	-@$(MAKE) -C $(subst .docs,,$@)

# Clean all the applications.
cleanapps: $(CLEANAPPS)

.PHONY: $(CLEANAPPS)
$(CLEANAPPS):
	-@$(MAKE) -C $(subst .cleanapps,,$@) clean

# Clean all the test applications.
cleantests: $(CLEANTESTS)

.PHONY: $(CLEANTESTS)
$(CLEANTESTS):
	-@$(MAKE) -f Makefile.test -C $(subst .cleantests,,$@) clean

# Clean all the docs.
cleandocs: $(CLEANDOCS)

.PHONY: $(CLEANDOCS)
$(CLEANDOCS):
	-@$(MAKE) -C $(subst .cleandocs,,$@) clean


