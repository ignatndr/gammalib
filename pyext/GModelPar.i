/***************************************************************************
 *           GModelPar.i  -  Model parameter class Python interface        *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2009-2011 by Jurgen Knodlseder                           *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GModelPar.i
 * @brief Model parameter class Python interface
 * @author J. Knodlseder
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GModelPar.hpp"
#include "GTools.hpp"
%}


/***********************************************************************//**
 * @class GModelPar
 *
 * @brief Model parameter class
 ***************************************************************************/
class GModelPar {
public:
    // Constructors and destructors
    GModelPar(void);
    GModelPar(const GModelPar& par);
    virtual ~GModelPar(void);

    // Methods
    void        clear(void);
    GModelPar*  clone(void) const;
    std::string name(void) const;
    std::string unit(void) const;
    double      real_value(void) const;
    double      real_error(void) const;
    double      real_gradient(void) const;
    double      real_min(void) const;
    double      real_max(void) const;
    double      value(void) const;
    double      error(void) const;
    double      gradient(void) const;
    double      min(void) const;
    double      max(void) const;
    double      scale(void) const;
    bool        isfree(void) const;
    bool        hasmin(void) const;
    bool        hasmax(void) const;
    bool        hasgrad(void) const;
    void        name(const std::string& name);
    void        unit(const std::string& unit);
    void        real_value(const double& value);
    void        real_error(const double& error);
    void        value(const double& value);
    void        error(const double& error);
    void        gradient(const double& gradient);
    void        min(const double& min);
    void        max(const double& max);
    void        scale(const double& scale);
    void        range(const double& min, const double& max);
    void        remove_min(void);
    void        remove_max(void);
    void        remove_range(void);
    void        free(void);
    void        fix(void);
    void        hasgrad(const bool& grad);
    void        read(const GXmlElement& xml);
    void        write(GXmlElement& xml) const;
};


/***********************************************************************//**
 * @brief GModelPar class extension
 ***************************************************************************/
%extend GModelPar {
    char *__str__() {
        return tochar(self->print());
    }
    GModelPar copy() {
        return (*self);
    }
};
