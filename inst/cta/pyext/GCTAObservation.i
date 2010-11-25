/***************************************************************************
 *       GCTAObservation.i  -  CTA Observation class SWIG interface        *
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
/**
 * @file GCTAObservation.i
 * @brief GCTAObservation class SWIG interface.
 * @author J. Knodlseder
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GCTAObservation.hpp"
%}


/***********************************************************************//**
 * @class GCTAObservation
 *
 * @brief Interface class for CTA observations.
 ***************************************************************************/
class GCTAObservation : public GObservation {
public:
    // Constructors and destructors
    GCTAObservation(void);
    GCTAObservation(const GCTAObservation& obs);
    virtual ~GCTAObservation(void);

    // Implement pure virtual methods
    GCTAObservation* clone(void) const;
    void             response(const std::string& irfname, std::string caldb = "");
    GResponse*       response(const GTime& time) const;
    GPointing*       pointing(const GTime& time) const;
    std::string      instrument(void) const;

    // Other methods
    void load_unbinned(const std::string& filename);
    void load_binned(const std::string& filename);
};


/***********************************************************************//**
 * @brief GCTAObservation class extension
 ***************************************************************************/
%extend GCTAObservation {
    char *__str__() {
        static char str_buffer[10001];
        std::ostringstream buffer;
        buffer << *self;
        std::string str = buffer.str();
        strncpy(str_buffer, (char*)str.c_str(), 10001);
        str_buffer[10000] = '\0';
        return str_buffer;
    }
    GCTAObservation copy() {
        return (*self);
    }
};
