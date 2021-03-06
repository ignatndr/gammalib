/***************************************************************************
 *             GCTAResponseTable.hpp - CTA response table class            *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2012-2013 by Juergen Knoedlseder                         *
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
 * @file GCTAResponseTable.hpp
 * @brief CTA response table class definition
 * @author Juergen Knoedlseder
 */

#ifndef GCTARESPONSETABLE_HPP
#define GCTARESPONSETABLE_HPP

/* __ Includes ___________________________________________________________ */
#include <string>
#include <vector>
#include "GBase.hpp"
#include "GNodeArray.hpp"
#include "GFitsTable.hpp"


/***********************************************************************//**
 * @class GCTAResponseTable
 *
 * @brief Interface for the CTA response table class
 *
 * A response table contains response parameters in multi-dimensional vector
 * column format. Each dimension is described by axes columns. 
 ***************************************************************************/
class GCTAResponseTable : public GBase {

public:
    // Constructors and destructors
    GCTAResponseTable(void);
    GCTAResponseTable(const GCTAResponseTable& table);
    GCTAResponseTable(const GFitsTable* hdu);
    virtual ~GCTAResponseTable(void);

    // Operators
    GCTAResponseTable&  operator= (const GCTAResponseTable & table);
    std::vector<double> operator()(const double& arg) const;
    std::vector<double> operator()(const double& arg1, const double& arg2) const;
    double              operator()(const int& index, const double& arg) const;
    double              operator()(const int& index, const double& arg1,
                                   const double& arg2) const;

    // Methods
    void               clear(void);
    GCTAResponseTable* clone(void) const;
    int                size(void) const;
    int                elements(void) const;
    int                axes(void) const;
    int                axis(const int& index) const;
    double             axis_lo(const int& index, const int& bin) const;
    double             axis_hi(const int& index, const int& bin) const;
    void               axis_linear(const int& index);
    void               axis_log10(const int& index);
    void               axis_radians(const int& index);
    void               scale(const int& index, const double& scale);
    void               read(const GFitsTable* hdu);
    void               write(GFitsTable* hdu) const;
    std::string        print(const GChatter& chatter = NORMAL) const;

private:
    // Methods
    void init_members(void);
    void copy_members(const GCTAResponseTable& table);
    void free_members(void);
    void read_colnames(const GFitsTable* hdu);
    void read_axes(const GFitsTable* hdu);
    void read_pars(const GFitsTable* hdu);
    void update(const double& arg) const;
    void update(const double& arg1, const double& arg2) const;

    // Table information
    int                               m_naxes;       //!< Number of axes
    int                               m_npars;       //!< Number of parameters
    int                               m_nelements;   //!< Number of elements per parameter
    std::vector<std::string>          m_colname_lo;  //!< Column names for lower boundaries
    std::vector<std::string>          m_colname_hi;  //!< Column names for upper boundaries
    std::vector<std::string>          m_colname_par; //!< Column names for parameters
    std::vector<std::vector<double> > m_axis_lo;     //!< Axes lower boundaries
    std::vector<std::vector<double> > m_axis_hi;     //!< Axes upper boundaries
    std::vector<GNodeArray>           m_axis_nodes;  //!< Axes node arrays
    std::vector<std::vector<double> > m_pars;        //!< Parameters

    // Response table computation cache for 1D access
    mutable int    m_inx_left;                       //!< Index of left node
    mutable int    m_inx_right;                      //!< Index of right node
    mutable double m_wgt_left;                       //!< Weight of left node
    mutable double m_wgt_right;                      //!< Weight of right node

    // Response table computation cache for 2D access
    mutable int    m_inx1;                           //!< Index of upper left node
    mutable int    m_inx2;                           //!< Index of lower left node
    mutable int    m_inx3;                           //!< Index of upper right node
    mutable int    m_inx4;                           //!< Index of lower right node
    mutable double m_wgt1;                           //!< Weight of upper left node
    mutable double m_wgt2;                           //!< Weight of lower left node
    mutable double m_wgt3;                           //!< Weight of upper right node
    mutable double m_wgt4;                           //!< Weight of lower right node
};

#endif /* GCTARESPONSETABLE_HPP */
