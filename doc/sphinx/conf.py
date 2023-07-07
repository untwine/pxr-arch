# -*- coding: utf-8 -*-

"""Arch documentation build configuration file."""

import pathlib

# -- General ------------------------------------------------------------------

extensions = ["sphinxcontrib.doxylink", "lowdown"]
templates_path = ["_templates"]
source_suffix = ".rst"
master_doc = "index"

project = "Arch"
copyright = "2023, Pixar, modified by Jeremy Retailleau"

version = "@CMAKE_PROJECT_VERSION@"
release = version

build_path = pathlib.Path("@CMAKE_CURRENT_BINARY_DIR@/doc")
doxylink = {"arch-cpp": ((build_path / "arch.tag").as_posix(), "./doxygen")}
add_function_parentheses = True

# -- HTML output --------------------------------------------------------------

html_theme = "sphinx_rtd_theme"
html_favicon = "favicon.ico"
