import os
from glob import glob
from sys import platform, argv

_preserve_file_structure = False

is_wsl = os.environ.get("WSLENV", default=None) != None

is_win = platform == "win32" or is_wsl
is_linux = (platform == "linux" or platform == "linux2") and not is_wsl
is_osx = platform == "darwin" and not is_wsl

LIBTOOL="ar -rcs"
RM="rm -rf"

INCLUDES=[]
CFLAGS=["-O3"]

if (is_win):
	CC="x86_64-w64-mingw32-gcc"
	CFLAGS += ["-D WIN32"]
elif (is_linux):
	CC="gcc"
	CFLAGS += ["-D LINUX"]
elif (is_osx):
	CFLAGS += ["-D OSX"]
if (not is_win and not is_linux and not is_osx):
	print("Platform not supported")
	exit(1)

NAME="libft.a"

SRCS_DIR="./srcs"
SRCS_EXT=".c"

OBJS_DIR="./objs"
OBJS_EXT=".o"

SRCS=glob(f'{SRCS_DIR}/**/*{SRCS_EXT}', recursive=True)
if (_preserve_file_structure):
	OBJS=[ o.replace(SRCS_DIR, OBJS_DIR).replace(SRCS_EXT, OBJS_EXT) for o in SRCS ]
else:
	OBJS=[ f'{OBJS_DIR}/{os.path.split(os.path.abspath(o))[1].replace(SRCS_EXT, OBJS_EXT)}' for o in SRCS ]



def all():
	print("Configuration:")
	print(" -> platform:")
	print(f"   {'win32' if (is_win) else 'linux' if (is_linux) else 'osx' if (is_osx) else 'none'}")
	print(" -> compiler:")
	print(f"   {CC}")
	print(" -> flags:")
	print(f"   {CFLAGS}")
	print(" -> compiling:")
	__max_len = max(len(s) for s in SRCS)
	[print(f"   [{s}]{' ' * (__max_len-len(s))} ==> [{o}]") for s, o in zip(SRCS, OBJS) ]


	for src, obj in zip(SRCS, OBJS):
		includes_str = ' '.join([f'-I{inc}' for inc in INCLUDES])
		cflags_str = ' '.join(CFLAGS)

		out_dir = os.path.split(os.path.abspath(obj))[0]
		if (not os.path.exists(out_dir)):
			print(f"Ouput directory '${out_dir}' doesn't exists, creating...")
			os.makedirs(out_dir)

		command = f'{CC} {cflags_str} {includes_str} -c {src} -o {obj}'
		print(command)
		#os.system(command)

	command = f"{LIBTOOL} {' '.join(OBJS)}"
	print(command)
	os.system(command)

def clean():
	command = f"{RM} {OBJS_DIR}/*"
	print(command)
	os.system(command)