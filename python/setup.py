# # from distutils.core import setup
# # from distutils.extension import Extension
# # from Cython.Distutils import build_ext
# from setuptools import setup, Extension
# from Cython.Build import cythonize
#
# module = cythonize([Extension(
#     'pyctrl',
#     sources=[
#         'pyctrl.pyx',
#     ],
#     libraries=['pyctrl', 'symengine'],
#     library_dirs=['/usr/local/lib'],
#     include_dirs=['/usr/local/include'],
#     language='c++',
# )], include_path=['/usr/local/lib/python3.6/site-packages/symengine/lib'])
#
# wrapper = Extension(
#     'py_wrapper',
#     sources=[
#         'py_wrapper.cc',
#     ],
#     libraries=['symengine'],
#     library_dirs=['/usr/local/lib'],
#     include_dirs=['/usr/local/include'],
#     language='c++',
# )
#
# setup(
#     name='pyctrl',
#     version='0.1.0',
#     # packages=['pyctrl'],
#     # package_dir={'pyctrl': '.'},
#     # package_data={'pyctrl': ['pyctrl.so']},
#     # include_package_data=True,
#     ext_modules = [module, wrapper],
#     # cmdclass = {'build_ext': build_ext},
# )

import os
from setuptools import setup, Extension

# Check if the USE_SETUPTOOLS environment variable is set.
use_cython = True
use_setuptools = os.getenv('USE_SETUPTOOLS')

if use_setuptools is not None:
    if use_setuptools.lower() == 'true':
        use_cython = False

# Load Cython.
if use_cython:
    try:
        from Cython.Build import cythonize
    except ImportError:
        use_cython = False

if not use_cython:
    # If the USE_SETUPTOOLS flag is set, or if Cython is not installed, install
    # the library using setuptools as a Python/C extension.
    modules = [
        Extension(
            'pyctrl',
            sources=['py_wrapper.cc'],
            include_dirs=['/usr/local/include'],
        )
    ]
else:
    modules = cythonize([
            Extension(
                'pyctrl',
                sources=['pyctrl.pyx', '../models/state_space.cc'],
                # sources=['state_space.cc'],
                include_dirs=[
                    '/usr/local/include',
                    '/usr/local/lib/python3.6/site-packages/symengine/lib',
                ],
                libraries=['symengine'],
                library_dirs=[
                    '/usr/local/lib',
                    '/usr/local/lib/libctrl',
                ],
                extra_compile_args=['-std=c++11'],
                language='c++',
            )
        ],
        include_path=['/usr/local/lib/python3.6/site-packages/symengine/lib'],
    )

long_description = '''
The Symbolic Controls Toolbox is a C++ symbolic library for working with control systems licensed under the MIT general license.
See https://github.com/ajthor/symbolic-controls-toolbox for more information.
'''

setup(
    name='pyctrl',
    version='0.1.0',
    description='Python library for control systems.',
    long_description=long_description,
    author='Adam Thorpe',
    license='MIT',
    url='https://github.com/ajthor/symbolic-controls-toolbox',
    keywords='control-systems hybrid nonlinear mdp',
    zip_safe=False,
    ext_modules=modules,
)
