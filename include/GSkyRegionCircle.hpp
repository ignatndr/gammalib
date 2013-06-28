/***************************************************************************
 *              GSkyRegionCircle.hpp - circular sky region class           *
 * ----------------------------------------------------------------------- *
 * copyright (C) 2013 by Michael Mayer                                     *
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
 * @file GSkyRegionCircle.hpp
 * @brief Abstract sky region base class interface definition
 * @author Michael Mayer
 */

#ifndef GSKYREGIONCIRCLE_HPP
#define GSKYREGIONCIRCLE_HPP

/* __ Includes ___________________________________________________________ */
#include <vector>
#include <string>
#include "GMath.hpp"
#include "GSkyDir.hpp"
#include "GSkyRegion.hpp"


/***********************************************************************//**
 * @class GSkyRegionCircle
 *
 * @brief Abstract interface for the circular sky region class
 *
 * This class provides an implementation for a circular sky region. The sky
 * region is defined by an array of parameters, the meaning of which is
 * specific to the derived class where the region type or shape is defined.
 * The parameters are GModelPar objects for convenience.
 *
 * The class holds several properties such as solid angle subtended by the
 * region and computed through internal method compute_solid().
 *
 * To be clarified:
 * - Do we want a member relating the region to an observation run ?
 * - Constructor and read/write using XML may not be needed if we use DS9
 *   region file format ?
 * - Replace GModelPar by double for the parameters (GModelPar is overkill) ?
 *
 ***************************************************************************/
class GSkyRegionCircle : public GSkyRegion {

public:
    // Constructors and destructors
    GSkyRegionCircle(void);
    GSkyRegionCircle(const GSkyRegionCircle& circle);
    explicit GSkyRegionCircle(const std::string &line);
    GSkyRegionCircle(GSkyDir &centre, const double &radius);
    // GSkyRegionCircle(const double &ra, const double &dec, const double &radius);
    virtual ~GSkyRegionCircle(void);

    // Operators
    GSkyRegionCircle& operator=(const GSkyRegionCircle& region);

    // Implemented methods
    void              clear(void);
    GSkyRegionCircle* clone(void) const;
    GSkyDir           centre(void) const;
    double            radius(void) const;
    void              radius(const double& radius);
    void              centre(const GSkyDir& centre);
    void              centre(const double& ra,const double& dec);
    void              read(const std::string& line);
    std::string       write(void) const;
    bool              contains(const GSkyDir& dir) const;
    bool              contains(const GSkyRegion& reg) const;
    bool              overlaps(const GSkyRegion& reg) const;
    std::string       print(const GChatter& chatter = NORMAL) const;

protected:
    // Protected methods
    void init_members(void);
    void copy_members(const GSkyRegionCircle& region);
    void free_members(void);
    void compute_solid(void);

    // Protected members
    GSkyDir	m_centre;   //!< Centre or reference point of the region
    double 	m_radius;  	//!< Radius of circular the region [deg]
};


/***********************************************************************//**
 * @brief Return region type
 *
 * @return region type
 *
 * Returns the region type.
 ***************************************************************************/
inline
double GSkyRegionCircle::radius(void) const
{
    return (m_radius);
}

/***********************************************************************//**
 * @brief Return region centre
 *
 * @return region centre
 *
 * Returns the region centre.
 ***************************************************************************/
inline
GSkyDir GSkyRegionCircle::centre(void) const
{
    return (m_centre);
}



/***********************************************************************//**
 * @brief Set centre of region
 *
 * @param[in] dir Center of region.
 ***************************************************************************/
inline
void GSkyRegionCircle::centre(const GSkyDir& dir)
{
    // Set centre
    m_centre = dir;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Set centre values
 *
 * @param[in] ra Right ascension value.
 * @param[in] dec declination value.
 ***************************************************************************/
inline
void GSkyRegionCircle::centre(const double& ra, const double& dec)
{
    // Set centre values
    m_centre.radec_deg(ra,dec);

    // Return
    return;
}

#endif /* GSKYREGIONCIRCLE_HPP */

