#!python3

import os
import sys
import subprocess
from glob import glob
import argparse

_makefile_dir = os.path.dirname(os.path.abspath(__file__))
_current_dir = os.getcwd()
if _current_dir != _makefile_dir:
    os.chdir(_makefile_dir)

def _execute(*exe_args):
	print(' '.join(exe_args))
	try:
		process = subprocess.Popen(exe_args, shell=False)
	except FileNotFoundError:
		print(f"Error: '{exe_args[0]}' doesn't exist. Double check args sent to subprocess.Popen.")
		exit(1)
	process.communicate()
	if (process.returncode != 0):
		print(f"Error: {exe_args[0]} exited with code {process.returncode}.")
		exit(1)

def _get_platform():
	is_wsl = os.environ.get("WSLENV", default=None) != None

	is_win = sys.platform == "win32" or is_wsl
	is_linux = (sys.platform == "linux" or sys.platform == "linux2") and not is_wsl
	is_osx = sys.platform == "darwin" and not is_wsl
	return "win32" if (is_win) else "linux" if (is_linux) else "osx" if (is_osx) else None

def _filter_files(srcs, objs):
	srcs_out = []
	objs_out = []
	for s, o in zip(srcs, objs):
		try:
			s_mtime = os.stat(s).st_mtime
		except FileNotFoundError as e:
			print(f"Error: couldn't stat '{e.filename}': not found !")
			continue

		try:
			o_mtime = os.stat(o).st_mtime
		except:
			srcs_out.append(s)
			objs_out.append(o)
			continue

		if (s_mtime > o_mtime):
			srcs_out.append(s)
			objs_out.append(o)
	return srcs_out, objs_out

def _rebuild_lib_needed(name, objs):
	try:
		mtime_lib = os.stat(name).st_mtime
	except FileNotFoundError as e:
		return True
	
	_objs_mtime = []
	for o in objs:
		try:
			_objs_mtime.append(os.stat(o).st_mtime)
		except FileNotFoundError:
			continue
	if (mtime_lib < max(_objs_mtime)):
		return True
	else:
		return False


parser = argparse.ArgumentParser(description='Custom makefile')

flag_group = parser.add_mutually_exclusive_group()
flag_group.add_argument('-re', action='store_true', help='Rebuild everything')
flag_group.add_argument('-clean', action='store_true', help='Cleanup')
flag_group.add_argument('-fclean', action='store_true', help='Full cleanup')

parser.add_argument('-d', '--debug', action='store_true', help='Stores debug info')
parser.add_argument('-t', '--target', metavar='TARGET', type=str, choices=['win32', 'linux', 'osx'], help='Specify the target platform. Build for current architecture if not specified.')
parser.add_argument('-D', metavar='DEFINE', type=str, action='append', help='Defines')

args = parser.parse_args()



LIBTOOL=["ar", "-rcs"]
RM=["rm", "-rf"]

INCLUDES=["-I./srcs"]
LIBRARIES_PATH=[]
LIBRARIES=[]
CFLAGS=["-O3"]

if (args.debug):
	CFLAGS += ["-g"]

if (args.target):
	platform = args.target
else:
	platform = _get_platform()

if (platform == "win32"):
	CC="x86_64-w64-mingw32-gcc"
	CFLAGS += ["-D FT_WIN32"]
elif (platform == "linux"):
	CC="gcc"
	CFLAGS += ["-D FT_LINUX"]
elif (platform == "osx"):
	CFLAGS += ["-D FT_OSX"]
else:
	print("Platform not supported")
	exit(1)

if (args.D):
	CFLAGS += [f"-D {define}" for define in args.D]

NAME="libft.a"
NAME_PLATFORM=f"libft_{platform.lower().removeprefix('ft_')}.a"

SRCS_DIR="./srcs"
SRCS_EXT=".c"

OBJS_DIR="./objs"
OBJS_EXT=".o"

SRCS=glob(f'{SRCS_DIR}/**/*{SRCS_EXT}', recursive=True)
OBJS=[ f'{OBJS_DIR}/{os.path.split(os.path.abspath(o))[1].removesuffix(SRCS_EXT).__add__(f"_{platform}{OBJS_EXT}")}' for o in SRCS ]

def name():
	if (not _rebuild_lib_needed(NAME_PLATFORM, OBJS)):
		print(f"Nothing to do for {NAME_PLATFORM}")
		return
	_execute(*LIBTOOL, NAME_PLATFORM, *OBJS)
	_execute("cp", NAME_PLATFORM, NAME)

def all():

	srcs, objs = _filter_files(SRCS, OBJS)
	if (len(srcs) == 0 or len(objs) == 0):
		print(f"Nothing to do for all")
		name()
		return

	for src, obj in zip(srcs, objs):
		out_dir = os.path.split(os.path.abspath(obj))[0]
		if (not os.path.exists(out_dir)):
			print(f"Ouput directory '${out_dir}' doesn't exists, creating...")
			os.makedirs(out_dir)
		_execute(CC, *CFLAGS, *INCLUDES, *LIBRARIES_PATH, '-c', src,'-o', obj, *LIBRARIES)
	name()

def clean():
	files = glob(OBJS_DIR + "/*")
	for f in files:
		_execute(*RM, f)

def fclean():
	clean()
	_execute(*RM, NAME_PLATFORM)
	_execute(*RM, NAME)

def re():
	fclean()
	all()


target = all
if args.re:
    target = re
elif args.clean:
    target = clean
elif args.fclean:
    target = fclean
target()
