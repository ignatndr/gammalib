#!/bin/sh
#
# Run all test and example scripts that come with the package
#
# Copyright (C) 2011-2013 Juergen Knoedlseder
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# =====================================================================
base=$PWD


# examples
# ========
echo
echo "=====> examples"
cd examples/python
./models_howto.py
./xml_howto.py
./xml_html_create.py
cd $base


# test
# ====
echo
echo "=====> test"
cd test
./example_model_xml_io.py
./example_radial_models.py
cd $base


# inst/cta/test
# =============
echo
echo "=====> inst/cta/test"
cd inst/cta/test
./test_model.py
./test_gauss.py
./example_binned_ml_fit.py
./example_sim_photons.py
cd $base


# inst/lat/test
# =============
echo
echo "=====> inst/lat/test"
cd inst/lat/test
./test_python.py
cd $base


# inst/mwl/test
# =============
echo
echo "=====> inst/mwl/test"
cd inst/mwl/test
./test_python.py
cd $base


# Signal completion
# =================
echo 
echo "All scripts completed."
