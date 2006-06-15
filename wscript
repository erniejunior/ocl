#! /usr/bin/env python
# encoding: utf-8

import Params

# the following two variables are used by the target "waf dist"
VERSION='0.1.0'
APPNAME='orocos-components'

# the srcdir is mandatory ('/' are converted automatically)
srcdir = '.'
blddir = '_build_'

def build(bld):
	# process subfolders from here
	bld.add_subdirs('reporting taskbrowser hardware/kuka motion_control/naxes') 

def configure(conf):
	conf.checkTool(['g++'])
	#conf.sub_config('reporting')

	# Read the options.
	oroloc = Params.g_options.oropath
	orotgt = Params.g_options.orotarget
	
	if not conf.checkHeader('corelib/CoreLib.hpp', pathlst=[ oroloc+'/include' ]):
		Params.fatal("Orocos headers not found: aborting.")
		exit
	if not conf.checkHeader('os/'+orotgt+'.h', pathlst=[ oroloc+'/include' ]):
		Params.fatal("Headers for target "+orotgt+" not found: aborting.")

	if not conf.checkPkg('orocos-'+orotgt,'OROCOS', '0.23.0', oroloc+'/lib/pkgconfig'):
		Params.fatal("Orocos pkgconf file not found !")
		
	conf.env['LIB_OROCOS'].append( 'orocos-'+orotgt )
	

def set_options(opt):
	opt.add_option('--prefix', type='string', help='installation prefix', dest='prefix')
	opt.add_option('--with-orocos', type='string', help='Orocos installation directory', dest='oropath', default='/usr/local/orocos')
	opt.add_option('--target', type='string', help='Build target (lxrt, xenomai, gnulinux)', dest='orotarget', default='gnulinux')
	#opt.sub_options('src')
