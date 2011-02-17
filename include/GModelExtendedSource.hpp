/***************************************************************************
 *        GModelExtendedSource.hpp  -  Extended source model class         *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2011 by Jurgen Knodlseder                                *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GModelExtendedSource.hpp
 * @brief Extended source model class interface definition
 * @author J. Knodlseder
 */

#ifndef GMODELEXTENDEDSOURCE_HPP
#define GMODELEXTENDEDSOURCE_HPP

/* __ Includes ___________________________________________________________ */
#include <string>
#include "GModelSky.hpp"
#include "GModelRadial.hpp"
#include "GModelSpectral.hpp"
#include "GXmlElement.hpp"


/***********************************************************************//**
 * @class GModelExtendedSource
 *
 * @brief Point source model class interface defintion
 *
 * This class implements a factorised point source model.
 ***************************************************************************/
class GModelExtendedSource : public GModelSky {

public:
    // Constructors and destructors
    GModelExtendedSource(void);
    explicit GModelExtendedSource(const GXmlElement& xml);
    explicit GModelExtendedSource(const GModelRadial& radial, const GModelSpectral& spectral);
    explicit GModelExtendedSource(const GXmlElement& radial, const GXmlElement& spectral);
    GModelExtendedSource(const GModelExtendedSource& model);
    virtual ~GModelExtendedSource(void);

    // Operators
    virtual GModelExtendedSource& operator= (const GModelExtendedSource& model);

    // Implemented pure virtual methods
    virtual void                  clear(void);
    virtual GModelExtendedSource* clone(void) const;
    virtual std::string           type(void) const { return "ExtendedSource"; }
    virtual void                  read(const GXmlElement& xml);
    virtual void                  write(GXmlElement& xml) const;
    virtual std::string           print(void) const;

    // Other methods
    GModelRadial* radial(void) const;
    GSkyDir       dir(void) const;

protected:
    // Protected methods
    void          init_members(void);
    void          copy_members(const GModelExtendedSource& model);
    void          free_members(void);
    GModelRadial* xml_radial(const GXmlElement& radial) const;
};

#endif /* GMODELEXTENDEDSOURCE_HPP */