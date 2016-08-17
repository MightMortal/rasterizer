#! /usr/bin/env python
# encoding: utf-8

import os
from fnmatch import fnmatch

top = '.'
out = 'bin'

APPNAME = 'rasterizer'
VERSION = '0.3'

sources_pattern = "*.c"

def get_source_list():
	result = ''
	for path, subdirs, files in os.walk('.'):
	    for name in files:
	        if fnmatch(name, sources_pattern):
	            result = result + ' ' + os.path.join(path, name)
	return result

def options(opt):
	opt.load('compiler_c')

def configure(conf):
	print('→ configuring the project in ' + conf.path.abspath())
	conf.env.append_value('CFLAGS', ['-g', '-O3', '-da']) # Configure flags for compiler
	conf.find_program('gcc', var = 'CC', mandatory = True)
	conf.load('compiler_c')

def build(bld):
	bld.program(
			source 		= get_source_list(),
			target 		= APPNAME + '_' + VERSION,
			lib 		= [],
			includes 	= ". .. include"
		)
