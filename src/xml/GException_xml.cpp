/***************************************************************************
 *               GException_xml.cpp  -  XML exception handlers             *
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
#include "GException.hpp"
#include "GTools.hpp"


/***********************************************************************//**
 * @brief XML syntax error
 *
 * @param[in] origin Method that throws the error.
 * @param[in] segment XML segment for which syntax error was encountered.
 * @param[in] message Optional error message.
 ***************************************************************************/
GException::xml_syntax_error::xml_syntax_error(std::string origin,
                                               std::string segment,
                                               std::string message)
{
    // Set origin and message
    m_origin  = origin;
    m_message = "XML syntax error ("+message+") occured in "+segment;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Invalid XML attribute value
 *
 * @param[in] origin Method that throws the error.
 * @param[in] value XML attribute value.
 ***************************************************************************/
GException::xml_attribute_value::xml_attribute_value(std::string origin,
                                                     std::string value)
{
    // Set origin and message
    m_origin  = origin;
    m_message = "Invalid XML attribute value: "+value;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Invalid XML node type
 *
 * @param[in] origin Method that throws the error.
 * @param[in] type XML node type.
 * @param[in] message Optional error message.
 ***************************************************************************/
GException::xml_bad_node_type::xml_bad_node_type(std::string origin,
                                                 std::string type,
                                                 std::string message)
{
    // Set origin and message
    m_origin  = origin;
    m_message = "Invalid XML node type ("+type+"). "+message;

    // Return
    return;
}


/***********************************************************************//**
 * @brief XML element name not found
 *
 * @param[in] origin Method that throws the error.
 * @param[in] name XML element name.
 * @param[in] message Optional error message.
 ***************************************************************************/
GException::xml_name_not_found::xml_name_not_found(std::string origin,
                                                   std::string name,
                                                   std::string message)
{
    // Set origin and message
    m_origin  = origin;
    m_message = "XML element name \""+name+"\" not found. "+message;

    // Return
    return;
}
