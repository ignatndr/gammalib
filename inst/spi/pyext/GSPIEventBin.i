/***************************************************************************
 *                  GSPIEventBin.i  -  SPI event bin class                 *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2013 by Juergen Knoedlseder                              *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GSPIEventBin.hpp
 * @brief SPI event bin class interface definition
 * @author Juergen Knoedlseder
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GSPIEventBin.hpp"
%}


/***********************************************************************//**
 * @class GSPIEventBin
 *
 * @brief SPI event bin class
 ***************************************************************************/
class GSPIEventBin : public GEventBin {
public:
    // Constructors and destructors
    GSPIEventBin(void);
    GSPIEventBin(const GSPIEventBin& bin);
    virtual ~GSPIEventBin(void);

    // Implemented pure virtual base class methods
    virtual void               clear(void);
    virtual GSPIEventBin*      clone(void) const;
    virtual double             size(void) const;
    virtual const GSPIInstDir& dir(void) const;
    virtual const GEnergy&     energy(void) const;
    virtual const GTime&       time(void) const;
    virtual double             counts(void) const;
    virtual double             error(void) const;
    virtual void               counts(const double& counts);
};


/***********************************************************************//**
 * @brief GSPIEventBin class extension
 ***************************************************************************/
%extend GSPIEventBin {
    GSPIEventBin copy() {
        return (*self);
    }
};