from distutils.core import setup, Extension

setup(name='lpcnet', version='1.0', \
ext_modules=[ \
    Extension('lpcnet',
    include_dirs = ['include', 'src'],
    libraries = ['lpcnet'],
    sources = ['lpcnet_python.c'])])
