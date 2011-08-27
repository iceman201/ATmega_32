#!/usr/bin/env python
"""makemake V0.03
Copyright (c) 2010 Michael P. Hayes, UC ECE, NZ

This program tries to make a Makefile from a template.  Given a C file
(or a directory which searched to find a C file containing a main
function) the included header files are recursively searched.  The for
each header file, a search is made for a similarly named C file.  The
header files for each C file are recursively searched and addded to
the list of found header files.  Again, similarly named C files are
searched until all the C files required for the program are found.

Usage: makemake --template template cfile search-dirs
or     makemake --template template directory search-dirs
or     makemake --builddir builddir --objext objext --template template directory search-dirs
or     makemake --builddir builddir --modules --relpath  directory search-dirs
or     makemake --builddir builddir --files --relpath  directory search-dirs

By default makemake will create a rule like foo.o: foo.c bar.h
and this will require a VPATH if the dependencies are another directory.
Alternatively, use the --relpath option to makemake to explicitly add the
relative path to the dependencies.

Note, this will die if there are circular dependencies.   FIXME!
The --modules option also needs fixing.  FIXME!

There are special strings that are replaced in the template file:
 @PROJECT@      Project name
 @VPATH@        List of source directories
 @INCLUDES@     List of include directories each prefixed by -I
 @SRC@          List of source files
 @OBJ@          List of object files
 @CCRULES@      Rules to build object files from C files

"""

# See http://www.amk.ca/python/howto/regex/ for regular expressions in python.
# See also sre.py.
# + one or more, ? 0 or 1, * 0 or more

# http://www.cs.umd.edu/~nspring/software/style-check-readme.html

import sys
import getopt
import re
import os
import subprocess
from os import pathsep
import os.path


def unique (list):

    dict = {}
    for item in list:
        dict[item] = True;

    return dict.keys ()


def file_search (filename, search_path, debug):
    """Given a search path, find file
    """

    file_found = False
    paths = search_path.split (pathsep)
    for path in paths:
        if os.path.exists (os.path.join (path, filename)):
            file_found = True
            break
        
    if file_found:
        return os.path.abspath (os.path.join (path, filename))

    # FIXME, if have :: at end of search path then need to search subdirs.
        
    return None


def hfiles_get (cfile, filedeps, mopts):
 
    deps = filedeps[cfile]
    
    if cfile in deps:
        print >> sys.stderr, 'Circular dependency for', cfile        


    hfilelist = []

    for hfile in filedeps[cfile]:
        if hfile[-2:] == '.h':
            if mopts['relpath']:
                hfile = os.path.relpath (hfile)
            hfilelist.append (hfile)

    for hfile in filedeps[cfile]:
        hfilelist.extend (hfiles_get (hfile, filedeps, mopts))

    return unique (hfilelist)


def cfiles_get (filedeps):

    cfilelist = []
    for target in filedeps:
        if target[-2:] == '.c':
            cfilelist.append (target)

    return unique (cfilelist)


def file_parse (pathname, indent, debug):

    if debug:
        print >> sys.stderr, indent, 'Parsing file', pathname

    file = open (pathname, 'r')
    text = file.read ()
    file.close ()

    prog = re.compile (r'^#include[ ].*["<]([a-zA-Z_.0-9].*)[">]', re.MULTILINE)

    hfilelist = prog.findall (text, 0)    

    if debug:
        print >> sys.stderr, indent, 'Found hfiles', hfilelist, 'in', pathname
    return hfilelist


def  makefile_print (mopts, template, maincfilename, filedeps, 
                     search_list, debug):
    
    basecfilelist = []
    cfilelist = []
    for target in filedeps:
        if target[-2:] == '.c':
            cfilelist.append (target)
            basecfilelist.append (os.path.basename (target))
    basecfilelist.sort ()
    cfilelist.sort ()

    project = os.path.splitext (os.path.basename (maincfilename))
    project = project[0]

    file = open (template, 'r')

    text = file.read ()
    file.close ()

    vpath = ' '.join (search_list)
    includes = '-I' + ' -I'.join (search_list)
    src = ' '.join (basecfilelist)
    obj = src

    if mopts['builddir'] != '':
        objfilelist = [os.path.join (mopts['builddir'], obj1) for obj1 in basecfilelist]
        objfilelist.sort ()
        obj = ' '.join (objfilelist)
        project = os.path.join (mopts['builddir'], project)

    obj = re.sub (r'([a-zA-Z0-9/.-_]*)[.]c', r'\1' + mopts['objext'], obj) 

    text = re.sub (r'@PROJECT@', project, text)
    text = re.sub (r'@VPATH@', vpath, text)
    text = re.sub (r'@INCLUDES@', includes, text)
    text = re.sub (r'@SRC@', src, text)

    text = re.sub (r'@OBJ@', obj, text)

    if re.search (r'@CCRULES@', text) != None:

        search_path = pathsep.join (search_list)

        rules = ''
        for cfile in cfilelist:
            cfilebase = os.path.basename (cfile)

            if mopts['relpath']:
                cfile1 = os.path.relpath (cfile)
            else:
                cfile1 = cfilebase

            if mopts['builddir'] != '':
                rules = rules + os.path.join (mopts['builddir'], '')

            rules = rules + re.sub ('([a-zA-Z0-9/.-_]*)[.]c', r'\1' + mopts['objext'], cfilebase) + ': ' + cfile1
            

            hfilelist = hfiles_get (cfile, filedeps, mopts)
            hfilelist.sort ()

            if debug:
                print >> sys.stderr, 'Need hfiles', hfilelist, 'for', cfile

            for hfile in hfilelist:
                rules = rules + ' ' + hfile

            rules = rules + '\n'
            rules = rules + '\t$(CC) -c $(CFLAGS) $< -o $@\n\n'

        text = re.sub (r'@CCRULES@', rules, text)


    print text


def maincfilename_find (dirname):

    p = subprocess.Popen (['grep -l "main[ ]*(" ' + dirname + '/*.c'],
                          shell = True, stdin = subprocess.PIPE,
                          stdout = subprocess.PIPE,
                          close_fds = True)
    
    (child_stdout, child_stdin) = (p.stdout, p.stdin)
    child_stdin.close ()
    files = child_stdout.read ()
    child_stdout.close ()

    filelist = files.strip ().split (' ')
    if not filelist:
        return None

    # What if there are multiple files with main?  For now, select the
    # first one.
    return filelist[0]


def functions_find (gcc, filepath, functiondeps = {}):

    command = gcc + ' -c ' + filepath + ' -fdump-tree-cfg-raw  > /dev/null'
    # print >> sys.stderr, command
    os.system (command)

    rtlfilename = os.path.abspath (os.path.basename (filepath)) + '.012t.cfg'
    # print >> sys.stderr, rtlfilename

    if not os.path.exists (rtlfilename):
        return

    file = open (rtlfilename, 'r')
    text = file.readlines ()
    file.close ()

    function = None
    for line in text:
        #print >> sys.stderr, line
        #matches = re.findall (r'^(.*)\s[(][)]', line)
        matches = re.findall (r'^;; Function (.*)\s[(]', line)
        if matches:
            function = matches[0]
            functiondeps[function] = []
            # print >> sys.stderr, 'DEF', function
        matches = re.findall (r'.*gimple_call [<]([\w]*)[,]', line)
        if matches:
            # print >> sys.stderr, 'USE', matches[0]
            if function:
                functiondeps[function].append (matches[0])
            else:
                print >> sys.stderr, matches[0], 'used outside function in', filepath

    command = 'rm ' + rtlfilename
    # print >> sys.stderr, command
    # os.system (command)


def files_find (gcc, filepath, search_path, filedeps, moduledeps, indent, debug):

    # filedeps is a cache of all known included files

    if filedeps.has_key (filepath):
        return

    # Find included header files
    includes = file_parse (filepath, indent + '  ', debug)                
    includes2 = []

    for hfile in includes:
        hpath = file_search (hfile, search_path, debug)
        if not hpath:
            continue
        includes2.append (hpath)

    # Guess modules from header files
    modules = []
    for hpath in includes2:    
        cpath = re.sub (r'([a-zA-Z._0-9/.-_].*)[.]h', r'\1.c', hpath);
        if (not os.path.exists (cpath)) or (cpath == filepath):
            continue
        # Have found a module
        modules.append (cpath)

    base, ext = os.path.splitext (os.path.basename (filepath))
    if ext == '.c':
        
        moduledeps[base] = []
        for module in modules:
            modbase, ext = os.path.splitext (os.path.basename (module))
            moduledeps[base].append (modbase)

    filedeps[filepath] = includes2

    # Search recursively each new included file
    for file in includes2:    
        files_find (gcc, file, search_path, filedeps, moduledeps, indent + ' ', debug)

    # Search the modules
    for file in modules:    
        files_find (gcc, file, search_path, filedeps, moduledeps, indent + ' ', debug)


def alldeps_print (depsdir, mopts):

    for target in depsdir.keys ():

        targetbase = os.path.basename (target)
        if targetbase in mopts['exclude']:
            continue

        deps = depsdir[target]
        deps = [dep for dep in deps if os.path.basename (dep) not in mopts['exclude']]
        if mopts['relpath']:
            deps = [os.path.relpath (dep) for dep in deps]

        print os.path.relpath (target) + ': ' + ' '.join (deps) + '\n'


def deps_print (target, depsdir, mopts, record = {}):

    if record.has_key (target):
        return
    if not depsdir.has_key (target):
        return
    
    deps = depsdir[target]
    deps = [dep for dep in deps if os.path.basename (dep) not in mopts['exclude']]
    for dep in deps:
        deps_print (dep, depsdir, mopts, record)

    if mopts['relpath']:
        deps = [os.path.relpath (dep) for dep in deps]

    record[target] = True

    print os.path.relpath (target) + ': ' + ' '.join (deps) + '\n'



class Usage (Exception):
    def __init__(self, msg):
        self.msg = msg


def main(argv = None):
    if argv is None:
        argv = sys.argv
    try:
        try:
            opts, args = getopt.gnu_getopt (argv[1:], "?h", \
                                            ["help", "builddir=", "objext=",
                                             "exeext=",
                                             "relpath", "debug", "template=", 
                                             "files", "modules", "exclude=",
                                             "calls"])
        except getopt.error, msg:
            raise Usage (msg)

        if not opts and not args:
            print __doc__
            sys.exit (0)

        if len (args) < 1:
            print __doc__
            sys.exit (0)

        mopts = {}
        mopts['builddir'] = ''
        mopts['objext'] = '.o'
        mopts['exeext'] = '.out'
        mopts['relpath'] = False
        mopts['template'] = None
        mopts['files'] = False
        mopts['modules'] = False
        mopts['calls'] = False
        mopts['exclude'] = []
        debug = False

        # Process options
        for o, a in opts:
            if o in ("-?", "-h", "--help"):
                print __doc__
                sys.exit (0)
            elif o == "--builddir":
                mopts['builddir'] = a
            elif o == "--objext":
                mopts['objext'] = a
            elif o == "--exeext":
                mopts['exeext'] = a
            elif o == "--relpath":
                mopts['relpath'] = True
            elif o == "--debug":
                debug = True
            elif o == "--template":
                mopts['template'] = a
            elif o == "--files":
                mopts['files'] = True
            elif o == "--modules":
                mopts['modules'] = True
            elif o == "--calls":
                mopts['calls'] = True
            elif o == "--exclude":
                mopts['exclude'] = a.split (' ')
                
        maincfilename = args[0]

        search_list = []
        if len (args) > 1:
            search_list.extend (args[1:len (args)])

        if debug:
            print >> sys.stderr, search_list
        search_path = pathsep.join (search_list)
        if debug:
            print >> sys.stderr, 'template', mopts['template']
            print >> sys.stderr, 'cfile', maincfilename
            print >> sys.stderr, 'search_path', search_path
            print >> sys.stderr, 'CWD = ', os.getcwd()

        if os.path.isdir (maincfilename):
            if debug:
                print >> sys.stderr, 'Searching ' + maincfilename
            maincfilename = maincfilename_find (maincfilename)
            if not maincfilename:
                sys.exit (1)

            if debug:
                print >> sys.stderr, 'Found C file ' + maincfilename

        includes = '-I' + ' -I'.join (search_list)
        cflags = '-mmcu=atmega32u2'
        opts = '-Os'
        gcc = 'avr-gcc' + ' ' + cflags + ' ' + opts + ' ' + includes

        # Search main c file looking for header files included with #include
        # and any header files included by the header files    

        filedeps = {}
        moduledeps = {}
        functiondeps = {}
        files_find (gcc, maincfilename, search_path, filedeps, moduledeps, '', debug)

        cfilelist = cfiles_get (filedeps)
        ofilelist = [cfile[:-2] + mopts['objext'] for cfile in cfilelist]
        outfile = maincfilename[:-2] + mopts['exeext']
        filedeps[outfile] = ofilelist
        for ofile in ofilelist:
            deps = []
            deps.append (ofile[:-2] + '.c')
            filedeps[ofile] = deps

        # print >> sys.stderr, moduledeps
        # print >> sys.stderr, filedeps

        if mopts['calls']:
            for cfile in cfilelist:
                functions_find (gcc, cfile, functiondeps)
            deps_print ('main', functiondeps, mopts)

        if mopts['files']:
            deps_print (outfile, filedeps, mopts)

        if mopts['modules']:
            target, ext = os.path.splitext (os.path.basename (maincfilename))
            deps_print (target, moduledeps, mopts)

        if mopts['template']:
            makefile_print (mopts, mopts['template'], maincfilename, filedeps,
                            search_list, debug)

        return 0


    except Usage, err:
        print >> sys.stderr, err.msg
        print >> sys.stderr, "for help use --help"
        return 2


if __name__ == "__main__":
    sys.exit (main())

