/***************************************************************************
 *       GFitsTableDoubleCol.cpp  - FITS table double column class         *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2010 by Jurgen Knodlseder                                *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/* __ Includes ___________________________________________________________ */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <iostream>
#include "GException.hpp"
#include "GTools.hpp"
#include "GFitsCfitsio.hpp"
#include "GFitsTableDoubleCol.hpp"

/* __ Method name definitions ____________________________________________ */

/* __ Macros _____________________________________________________________ */

/* __ Coding definitions _________________________________________________ */

/* __ Debug definitions __________________________________________________ */


/*==========================================================================
 =                                                                         =
 =                         Constructors/destructors                        =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Constructor
 ***************************************************************************/
GFitsTableDoubleCol::GFitsTableDoubleCol(void) : GFitsTableCol()
{
    // Initialise class members for clean destruction
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Constructor
 *
 * @param[in] name Name of column.
 * @param[in] length Length of column.
 * @param[in] size Vector size of column.
 ***************************************************************************/
GFitsTableDoubleCol::GFitsTableDoubleCol(const std::string& name,
                                         const int&         length,
                                         const int&         size)
                                       : GFitsTableCol(name, length, size, 2)
{
    // Initialise class members for clean destruction
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy constructor
 *
 * @param[in] column Column from which class instance should be built.
 ***************************************************************************/
GFitsTableDoubleCol::GFitsTableDoubleCol(const GFitsTableDoubleCol& column)
                                                      : GFitsTableCol(column)
{
    // Initialise class members for clean destruction
    init_members();

    // Copy members
    copy_members(column);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Destructor
 ***************************************************************************/
GFitsTableDoubleCol::~GFitsTableDoubleCol(void)
{
    // Free members
    free_members();

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                                Operators                                =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Assignment operator
 *
 * @param[in] column Column which should be assigned
 ***************************************************************************/
GFitsTableDoubleCol& GFitsTableDoubleCol::operator= (const GFitsTableDoubleCol& column)
{
    // Execute only if object is not identical
    if (this != &column) {

        // Copy base class members
        this->GFitsTableCol::operator=(column);

        // Free members
        free_members();

        // Initialise private members for clean destruction
        init_members();

        // Copy members
        copy_members(column);

    } // endif: object was not identical

    // Return this object
    return *this;
}


/***********************************************************************//**
 * @brief Column data access operator
 *
 * @param[in] row Row of column to access.
 * @param[in] inx Vector index in column row to access
 *
 * Provides access to data in a column.
 ***************************************************************************/
double& GFitsTableDoubleCol::operator() (const int& row, const int& inx)
{
    // If data are not available then load them now
    if (m_data == NULL) fetch_data();

    // Return data bin
    return m_data[offset(row, inx)];
}


/***********************************************************************//**
 * @brief Column data access operator (const variant)
 *
 * @param[in] row Row of column to access.
 * @param[in] inx Vector index in column row to access
 *
 * Provides access to data in a column.
 ***************************************************************************/
const double& GFitsTableDoubleCol::operator() (const int& row, const int& inx) const
{
    // If data are not available then load them now
    if (m_data == NULL) ((GFitsTableDoubleCol*)this)->fetch_data();

    // Return data bin
    return m_data[offset(row, inx)];
}


/*==========================================================================
 =                                                                         =
 =                               Public methods                            =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Get string value
 *
 * @param[in] row Table row.
 * @param[in] inx Table column vector index.
 *
 * Returns value of specified row and vector index as string.
 ***************************************************************************/
std::string GFitsTableDoubleCol::string(const int& row, const int& inx)
{
    // If data are not available then load them now
    if (m_data == NULL) fetch_data();

    // Convert double into string
    std::ostringstream s_value;
    s_value << m_data[offset(row,inx)];

    // Return value
    return s_value.str();
}


/***********************************************************************//**
 * @brief Get double precision value
 *
 * @param[in] row Table row.
 * @param[in] inx Table column vector index.
 *
 * Returns value of specified row and vector index as double precision.
 ***************************************************************************/
double GFitsTableDoubleCol::real(const int& row, const int& inx)
{
    // If data are not available then load them now
    if (m_data == NULL) fetch_data();

    // Convert double into double
    double value = (double)m_data[offset(row,inx)];

    // Return value
    return value;
}


/***********************************************************************//**
 * @brief Get integer value
 *
 * @param[in] row Table row.
 * @param[in] inx Table column vector index.
 *
 * Returns value of specified row and vector index as integer.
 ***************************************************************************/
int GFitsTableDoubleCol::integer(const int& row, const int& inx)
{
    // If data are not available then load them now
    if (m_data == NULL) fetch_data();

    // Convert double into int
    int value = (int)m_data[offset(row,inx)];

    // Return value
    return value;
}


/***********************************************************************//**
 * @brief Set NULL value
 *
 * @param[in] value Pointer on NULL value
 *
 * Allows the specification of the FITS table NULL value. If value=NULL the
 * data will not be screened for NULL values.
 *
 * @todo To correctly reflect the NULL value in the data, the column should
 * be reloaded. However, the column may have been changed, so in principle
 * saving is needed. However, we may not want to store the data, hence saving
 * is also not desired. We thus have to develop a method to update the
 * column information for a new NULL value in place ...
 ***************************************************************************/
void GFitsTableDoubleCol::nullval(const double* value)
{
    // Allocate nul value
    alloc_nulval(value);

    // Update column
//    if (m_data != NULL) {
//        save();
//        load();
//    }

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                             Private methods                             =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Initialise class members
 ***************************************************************************/
void GFitsTableDoubleCol::init_members(void)
{
    // Initialise members
    m_type   = __TDOUBLE;
    m_data   = NULL;
    m_nulval = NULL;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy class members
 *
 * @param[in] column Column for which members should be copied.
 *
 * Sets the content of the vector column by copying from another column.
 * If the code is compiled with the small memory option, and if the source
 * column has not yet been loaded, then we only load the column temporarily
 * for copying purposes and release it again once copying is finished.
 ***************************************************************************/
void GFitsTableDoubleCol::copy_members(const GFitsTableDoubleCol& column)
{
    // Fetch column data if not yet fetched. The casting circumvents the
    // const correctness
    bool not_loaded = (column.m_data == NULL);
    if (not_loaded) ((GFitsTableDoubleCol*)(&column))->fetch_data();

    // Copy attributes
    m_type = column.m_type;
    m_size = column.m_size;

    // Copy column data
    if (column.m_data != NULL && m_size > 0) {
        alloc_data();
        for (int i = 0; i < m_size; ++i)
            m_data[i] = column.m_data[i];
    }

    // Copy NULL value
    alloc_nulval(column.m_nulval);

    // Small memory option: release column if it was fetch above
    #if defined(G_SMALL_MEMORY)
    if (not_loaded) ((GFitsTableDoubleCol*)(&column))->release_data();
    #endif

    // Return
    return;
}


/***********************************************************************//**
 * @brief Delete class members
 ***************************************************************************/
void GFitsTableDoubleCol::free_members(void)
{
    // Free memory
    if (m_data   != NULL) delete [] m_data;
    if (m_nulval != NULL) delete m_nulval;

    // Mark memory as freed
    m_data   = NULL;
    m_nulval = NULL;

    // Reset load flag
    m_size = 0;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Clone column
 ***************************************************************************/
GFitsTableDoubleCol* GFitsTableDoubleCol::clone(void) const
{
    return new GFitsTableDoubleCol(*this);
}


/***********************************************************************//**
 * @brief Returns format string of ASCII table
 ***************************************************************************/
std::string GFitsTableDoubleCol::ascii_format(void) const
{
    // Initialize format string
    std::string format;

    // Set type code
    format.append("F");

    // Set width
    format.append(str(m_width));

    // Return format
    return format;
}


/***********************************************************************//**
 * @brief Returns format string of binary table
 ***************************************************************************/
std::string GFitsTableDoubleCol::binary_format(void) const
{
    // Initialize format string
    std::string format;

    // Set number of elements
    format.append(str(m_number));

    // Set type code
    format.append("D");

    // Return format
    return format;
}


/***********************************************************************//**
 * @brief Allocates column data
 ***************************************************************************/
void GFitsTableDoubleCol::alloc_data(void)
{
    // Free any existing memory
    if (m_data != NULL) delete [] m_data;

    // Mark pointer as free
    m_data = NULL;

    // Allocate new data
    if (m_size > 0)
        m_data = new double[m_size];

    // Return
    return;
}


/***********************************************************************//**
 * @brief Release column data
 ***************************************************************************/
void GFitsTableDoubleCol::release_data(void)
{
    // Free any existing memory
    if (m_data != NULL) delete [] m_data;

    // Mark pointer as free and reset loaded vector size
    m_data = NULL;
    m_size = 0;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Allocates null value
 ***************************************************************************/
void GFitsTableDoubleCol::alloc_nulval(const double* value)
{
    // Free any existing memory
    if (m_nulval != NULL) delete m_nulval;

    // Mark pointer as free
    m_nulval = NULL;

    // If we have valid value, allocate and set nul value
    if (value != NULL) {
        m_nulval  = new double;
        *m_nulval = *value;
    }

    // Return
    return;
}


/***********************************************************************//**
 * @brief Initialise column data
 ***************************************************************************/
void GFitsTableDoubleCol::init_data(void)
{
    // Initialise data if they exist
    if (m_data != NULL) {
        for (int i = 0; i < m_size; ++i)
            m_data[i] = 0.0;
    }

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                                Friends                                  =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Output operator
 *
 * @param[in] os Output stream
 * @param[in] column Column to put in output stream
 ***************************************************************************/
std::ostream& operator<< (std::ostream& os, const GFitsTableDoubleCol& column)
{
    // Dump column in output stream
    column.dump_column(os, column.m_data);

    // Return output stream
    return os;
}