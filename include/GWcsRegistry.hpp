/***************************************************************************
 *      GWcsRegistry.hpp - World Coordinate Projection registry class      *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2011-2013 by Juergen Knoedlseder                         *
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
 * @file GWcsRegistry.hpp
 * @brief World Coordinate Projection registry class interface definition
 * @author Juergen Knoedlseder
 */

#ifndef GWCSREGISTRY_HPP
#define GWCSREGISTRY_HPP

/* __ Includes ___________________________________________________________ */
#include <string>
#include "GRegistry.hpp"
#include "GWcslib.hpp"


/***********************************************************************//**
 * @class GWcsRegistry
 *
 * @brief Interface definition for the WCS registry class
 *
 * The registry class allows the registration of WCS projections that are not
 * necessarily compiled into the GammaLib. It uses the static members
 * m_number, m_codes, m_names, and m_prjs which are allocated globally to keep
 * track of projections that are available throughout all linked libraries. To
 * register a projection it is sufficient to add
 *
 *     const GWcsXXX      g_wcs_XXX_seed;
 *     const GWcsRegistry g_wcs_XXX_registry(&g_wcs_XXX_seed);
 *
 * at the top of the .cpp file of the projection. Here, XXX is a unique
 * code that describes the projection.
 ***************************************************************************/
class GWcsRegistry : public GRegistry {

public:
    // Constructors and destructors
    GWcsRegistry(void);
    GWcsRegistry(const GWcs* prj);
    GWcsRegistry(const GWcsRegistry& registry);
    virtual ~GWcsRegistry(void);

    // Operators
    GWcsRegistry& operator= (const GWcsRegistry& registry);

    // Methods
    int         size(void) const { return m_number; }
    GWcs*       alloc(const std::string& code) const;
    std::string code(const int& index) const;
    std::string name(const int& index) const;
    std::string list(void) const;
    std::string print(const GChatter& chatter = NORMAL) const;

protected:
    // Protected methods
    void init_members(void);
    void copy_members(const GWcsRegistry& registry);
    void free_members(void);

private:
    // Pricate members
    static int          m_number;   //!< Number of projections in registry
    static std::string* m_codes;    //!< Projection codes
    static std::string* m_names;    //!< Projection names
    static const GWcs** m_prjs;     //!< Pointer to seed projections
};

#endif /* GWCSREGISTRY_HPP */
