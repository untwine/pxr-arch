# -*- coding: utf-8 -*-

"""Arch documentation build configuration file."""

import os
import re
import pathlib

# -- General ------------------------------------------------------------------

# Extensions.
extensions = ["lowdown"]

if os.environ.get("READTHEDOCS"):
    import doxygen
    doxygen.create_cmake_config()
    doxygen.build()

    html_extra_path = ["./api"]

# The suffix of source filenames.
source_suffix = ".rst"

# The master toctree document.
master_doc = "index"

# General information about the project.
project = u"Arch"
copyright = u"2022, Pixar, modified by Jeremy Retailleau"

# Version
pattern = r"project\(.* VERSION ([\d\\.]+)"
root = pathlib.Path(__file__).parent.resolve()
config = (root.parent.parent / "CMakeLists.txt").read_text(encoding="utf-8")

version = re.search(pattern, config, re.DOTALL).group(1)
release = version

# -- HTML output --------------------------------------------------------------

html_theme = "sphinx_rtd_theme"

# If True, copy source rst files to output for reference.
html_copy_source = True
