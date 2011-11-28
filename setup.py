from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

SOURCEMOD_PATH = '/Users/they4kman/programming/sourcemod-central'

ext = Extension(
    "cpp_smjit",                 # name of extension
    [ "cpp_smjit.pyx", 'cpp_smjit_iface.cpp' ],     # filename of our Cython source
    language="c++",              # this causes Cython to create C++ source
    include_dirs=[SOURCEMOD_PATH + '/public', SOURCEMOD_PATH + '/public/sourcepawn', SOURCEMOD_PATH + '/sourcepawn/jit' ],          # usual stuff
    libraries=[  ],             # ditto
    extra_link_args=[ 'sourcepawn.jit.x86.dylib' ],       # if needed
    cmdclass = { 'build_ext': build_ext }
    )

setup(
    cmdclass = { 'build_ext': build_ext },
    ext_modules = [ext]
)