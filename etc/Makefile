# File:   Makefile
# Author: M. P. Hayes, UCECE
# Date:   12 Sep 2010
# Descr:  Makefile to create application Makefiles from a template.

# Abandon all hope ye who look in here.
# This Makefile builds all the application Makefiles
# using template Makefiles and a python script makemake.py that parses
# the applications looking for #includes.

APPS = $(filter-out ../apps/README, $(wildcard ../apps/*))

MAKEAPPS = $(addsuffix .apps, $(APPS))
MAKETEST = $(addsuffix .test, $(APPS))
CLEANAPPS = $(addsuffix .cleanapps, $(APPS))
CLEANTEST = $(addsuffix .cleantest, $(APPS))

TESTMAKEFILES = $(addsuffix /Makefile.test, $(APPS))
APPMAKEFILES = $(addsuffix /Makefile, $(APPS))
DOCMAKEFILES = $(addsuffix /doc/Makefile, $(APPS))

all: testmakefiles appmakefiles apps test docs

clean: cleanapps cleantest

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
test: $(MAKETEST)

.PHONY: $(MAKETEST)
$(MAKETEST):
	-@$(MAKE) -f Makefile.test -C $(subst .test,,$@)

# Clean all the applications.
cleanapps: $(CLEANAPPS)

.PHONY: $(CLEANAPPS)
$(CLEANAPPS):
	-@$(MAKE) -C $(subst .cleanapps,,$@) clean

# Clean all the test applications.
cleantest: $(CLEANTEST)

.PHONY: $(CLEANTEST)
$(CLEANTEST):
	-@$(MAKE) -f Makefile.test -C $(subst .cleantest,,$@) clean


