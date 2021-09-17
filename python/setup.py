import logging
import os
from setuptools import setup
from distutils.file_util import copy_file

from pybind11.setup_helpers import Pybind11Extension, build_ext

import gsl_conf

# Make a copy of README.rst ... required by setup.cfg
t_dir = os.path.dirname(__file__)
par_dir = os.path.normpath(os.path.join(t_dir, os.pardir))
readme_name = "README.rst"
copy_file(
    os.path.join(par_dir, readme_name), os.path.join(t_dir, readme_name), update=True
)

d = gsl_conf.gsl_config()

ext_modules = [
    # Pybind11Extension(
    #    "testbind",
    #    sorted(['src/test_bind.cc', 'src/mytest.cc']),
    #    include_dirs=['.'],
    # ),
    Pybind11Extension(
        "lib",
        sorted(["src/tracy_py.cc"]),
        include_dirs=["../tracy/inc"] + [d["gsl_include"]],
        define_macros=[("_GLIBCXX_DEBUG", 1), ("_GLIBCXX_DEBUG_PEDANTIC", 1)],
        library_dirs=["../tracy/src/.libs"] + [d["gsl_lib_dir"]],
        libraries=["tracy"] + d["gsl_libs"],
    ),
]


setup(cmdclass={"build_ext": build_ext},
      ext_package='tracy',
      ext_modules=ext_modules
)
