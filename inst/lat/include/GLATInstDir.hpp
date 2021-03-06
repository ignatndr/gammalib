/***************************************************************************
 *             GLATInstDir.hpp - LAT instrument direction class            *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2010-2013 by Juergen Knoedlseder                         *
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
 * @file GLATInstDir.hpp
 * @brief GLATInstDir class definition.
 * @author Juergen Knoedlseder
 */

#ifndef GLATINSTDIR_HPP
#define GLATINSTDIR_HPP

/* __ Includes ___________________________________________________________ */
#include <string>
#include "GInstDir.hpp"
#include "GSkyDir.hpp"


/***********************************************************************//**
 * @class GLATInstDir
 *
 * @brief Interface for the LAT instrument direction class.
 *
 * The LAT instrument direction is an encapsulation of a sky direction
 * as LAT is an imaging device.
 ***************************************************************************/
class GLATInstDir : public GInstDir {

public:
    // Constructors and destructors
    GLATInstDir(void);
    explicit GLATInstDir(const GSkyDir& dir);
    GLATInstDir(const GLATInstDir& dir);
    virtual ~GLATInstDir(void);

    // Operators
    GLATInstDir& operator= (const GLATInstDir& dir);

    // Implemented pure virtual base class methods
    void         clear(void);
    GLATInstDir* clone(void) const;
    std::string  print(const GChatter& chatter = NORMAL) const;

    // Methods
    void         skydir(const GSkyDir& dir) { m_dir=dir; }
    void         radec(const double& ra, const double& dec) { m_dir.radec(ra,dec); }
    void         radec_deg(const double& ra, const double& dec) { m_dir.radec_deg(ra,dec); }
    void         lb(const double& l, const double& b) { m_dir.lb(l,b); }
    void         lb_deg(const double& l, const double& b) { m_dir.lb_deg(l,b); }
    GSkyDir      skydir(void) const { return m_dir; }
    double       l(void) const { return m_dir.l(); }
    double       l_deg(void) const { return m_dir.l_deg(); }
    double       b(void) const { return m_dir.b(); }
    double       b_deg(void) const { return m_dir.b_deg(); }
    double       ra(void) const { return m_dir.ra(); }
    double       ra_deg(void) const { return m_dir.ra_deg(); }
    double       dec(void) const { return m_dir.dec(); }
    double       dec_deg(void) const { return m_dir.dec_deg(); }
    double       dist(const GSkyDir& dir) const { return m_dir.dist(dir); }
    double       dist_deg(const GSkyDir& dir) const { return m_dir.dist_deg(dir); }
    double       dist(const GLATInstDir& dir) const;
    double       dist_deg(const GLATInstDir& dir) const;

protected:
    // Protected methods
    void init_members(void);
    void copy_members(const GLATInstDir& dir);
    void free_members(void);
    
    // Data members
    GSkyDir m_dir;  //!< Observed incident direction of event
};

#endif /* GLATINSTDIR_HPP */
