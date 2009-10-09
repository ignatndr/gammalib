/***************************************************************************
 *                        GData.cpp  -  Data class                         *
 * ----------------------------------------------------------------------- *
 *  copyright            : (C) 2008 by Jurgen Knodlseder                   *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
/**
 * @file GData.cpp
 * @brief GData class implementation.
 * @author J. Knodlseder
 */

/* __ Includes ___________________________________________________________ */
#include <iostream>
#include "GException.hpp"
#include "GData.hpp"

/* __ Method name definitions ____________________________________________ */
#define G_COPY_MEMBERS      "GData::copy_members(const GData&)"

/* __ Macros _____________________________________________________________ */

/* __ Coding definitions _________________________________________________ */

/* __ Debug definitions __________________________________________________ */


/*==========================================================================
 =                                                                         =
 =                       GData constructors/destructors                    =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Constructor
 ***************************************************************************/
GData::GData()
{
    // Initialise class members for clean destruction
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy constructor
 *
 * @param data GData instance which should be used for construction
 ***************************************************************************/
GData::GData(const GData& data)
{
    // Initialise class members for clean destruction
    init_members();

    // Copy members
    copy_members(data);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Destructor
 ***************************************************************************/
GData::~GData()
{
    // Free members
    free_members();

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                             GData operators                             =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Assignment operator
 *
 * @param[in] data GData instance to be assigned
 ***************************************************************************/
GData& GData::operator= (const GData& data)
{
    // Execute only if object is not identical
    if (this != &data) {

        // Free members
        free_members();

        // Initialise private members for clean destruction
        init_members();

        // Copy members
        copy_members(data);

    } // endif: object was not identical

    // Return this object
    return *this;
}


/*==========================================================================
 =                                                                         =
 =                           GData public methods                          =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Add observation to data
 ***************************************************************************/
void GData::add(GObservation *obs)
{
	// Allocate observation pointers
    GObservation** new_obs = new GObservation*[m_num+1];
	if (new_obs == NULL)
		throw GException::mem_alloc(G_COPY_MEMBERS, m_num+1);

	// Copy over old observation pointers
    if (m_num > 0) {
        for (int i = 0; i < m_num; ++i)
			new_obs[i] = m_obs[i];
	}
	
	// Link in new observation
	new_obs[m_num] = obs;
	obs->link();
	
	// Release old pointer array
	if (m_obs != NULL) delete [] m_obs;
	
	// Attach new pointer array
	m_obs = new_obs;
	
	// Increment number of observations
	m_num++;
	
    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                           GData private methods                         =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Initialise class members
 ***************************************************************************/
void GData::init_members(void)
{
    // Initialise members
    m_num = 0;
	m_obs = NULL;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy class members
 *
 * @param[in] data GData instance from which members should be copied
 *
 * Copy observations from a GData object into the present object by invoking
 * the observation clone method of each observation.
 ***************************************************************************/
void GData::copy_members(const GData& data)
{
    // Copy attributes
    m_num = data.m_num;
	
	// Copy observations
    if (m_num > 0) {
        m_obs = new GObservation*[m_num];
        if (m_obs == NULL)
            throw GException::mem_alloc(G_COPY_MEMBERS, m_num);
        for (int i = 0; i < m_num; ++i) {
			if (data.m_obs[i] != NULL)
				m_obs[i] = (data.m_obs[i])->clone();
			else
				m_obs[i] = NULL;
		}
	}
    
    // Return
    return;
}


/***********************************************************************//**
 * @brief Delete class members
 ***************************************************************************/
void GData::free_members(void)
{
    // Free memory
    if (m_obs != NULL) {
	
		// Release all observations
        for (int i = 0; i < m_num; ++i) {
			if (m_obs[i] != NULL)
				m_obs[i]->release();
		}
		
		// Delete observation pointers
		delete [] m_obs;
	}
	
    // Mark memory as free
	m_num = 0;
	m_obs = NULL;

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                               GData friends                             =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Output operator
 *
 * @param[in] os Output stream into which the data will be dumped
 * @param[in] data Data to be dumped
 ***************************************************************************/
std::ostream& operator<< (std::ostream& os, const GData& data)
{
    // Put header in stream
    os << "=== GData ===" << std::endl;
    os << " Number of observations ....: " << data.m_num << std::endl;

	// Put observations in stream
	for (int i = 0; i < data.m_num; ++i)
		os << *(data.m_obs[i]);

    // Return output stream
    return os;
}


/*==========================================================================
 =                                                                         =
 =                       Other functions used by GData                     =
 =                                                                         =
 ==========================================================================*/
