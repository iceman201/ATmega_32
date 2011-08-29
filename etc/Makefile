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

APPFILEDEPS = $(addsuffix /file_dependencies.pdf, $(APPS))
APPMODULEDEPS = $(addsuffix /module_dependencies.pdf, $(APPS))
APPMAKEFILEDEPS = $(addsuffix /makefile_dependencies.pdf, $(APPS))
APPBUILDDEPS = $(addsuffix /build_dependencies.pdf, $(APPS))
APPCALLGRAPHS = $(addsuffix /callgraph.pdf, $(APPS))

all: testmakefiles appmakefiles apps test appfiledeps appmoduledeps appmakefiledeps appbuilddeps appcallgraphs

clean: cleanapps cleantest

testmakefiles: $(TESTMAKEFILES)

appmakefiles: $(APPMAKEFILES)

../%/Makefile.test: Makefile.test.template Makefile
	(cd $(dir $@);	../../etc/makemake.py --cc="gcc" --cflags="" --relpath --objext=-test.o --template ../../etc/Makefile.test.template . . ../../utils ../../drivers ../../drivers/test > Makefile.test)


../%/Makefile: Makefile.template Makefile makemake.py
	(cd $(dir $@);	../../etc/makemake.py --cc="avr-gcc" --cflags="-Os -mmcu=atmega32u2" --relpath --template ../../etc/Makefile.template . . ../../utils ../../fonts ../../drivers ../../drivers/avr > Makefile)


appfiledeps: $(APPFILEDEPS)
appmoduledeps: $(APPMODULEDEPS)
appmakefiledeps: $(APPMAKEFILEDEPS)
appbuilddeps: $(APPBUILDDEPS)
appcallgraphs: $(APPCALLGRAPHS)

../%/file_dependencies.pdf: ../%/files.d 
	./graphdeps.py $< --out $@

../%/module_dependencies.pdf: ../%/modules.d 
	./graphdeps.py $< --modules --out $@

../%/makefile_dependencies.pdf: ../%/Makefile
	./graphdeps.py $< --out $@

../%/build_dependencies.pdf: ../%/Makefile
	./graphdeps.py $< --out $@ --showops

../%/callgraph.pdf: ../%/callgraph.d 
	(cd $(dir $@);	../../etc/graphdeps.py --calls --modules $(notdir $<) --out $(notdir $@))

../%/files.d: ../%/Makefile
	(cd $(dir $@);	../../etc/makemake.py --relpath --files . . ../../drivers ../../drivers/avr ../../utils --exclude system.h > files.d)


../%/modules.d: ../%/Makefile
	(cd $(dir $@);	../../etc/makemake.py --relpath --modules . . ../../drivers ../../drivers/avr ../../utils --exclude system > modules.d)

../%/callgraph.d: ../%/Makefile
	(cd $(dir $@);	../../etc/makemake.py --cc="avr-gcc" --cflags="-Os -mmcu=atmega32u2" --relpath --calls . . ../../drivers ../../drivers/avr ../../utils --exclude system > callgraph.d)


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


