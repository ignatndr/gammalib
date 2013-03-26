/***************************************************************************
 *         GModelSpectralConst.cpp - Spectral constant model class         *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2009-2013 by Juergen Knoedlseder                         *
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
 * @file GModelSpectralConst.cpp
 * @brief Constant spectral model class implementation
 * @author Juergen Knoedlseder
 */

/* __ Includes ___________________________________________________________ */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "GException.hpp"
#include "GTools.hpp"
#include "GModelSpectralConst.hpp"
#include "GModelSpectralRegistry.hpp"

/* __ Constants __________________________________________________________ */

/* __ Globals ____________________________________________________________ */
const GModelSpectralConst    g_spectral_const_seed;
const GModelSpectralRegistry g_spectral_const_registry(&g_spectral_const_seed);

/* __ Method name definitions ____________________________________________ */
#define G_FLUX                "GModelSpectralConst::flux(GEnergy&, GEnergy&)"
#define G_EFLUX              "GModelSpectralConst::eflux(GEnergy&, GEnergy&)"
#define G_MC     "GModelSpectralConst::mc(GEnergy&, GEnergy&, GTime&, GRan&)"
#define G_READ                      "GModelSpectralConst::read(GXmlElement&)"
#define G_WRITE                    "GModelSpectralConst::write(GXmlElement&)"

/* __ Macros _____________________________________________________________ */

/* __ Coding definitions _________________________________________________ */

/* __ Debug definitions __________________________________________________ */


/*==========================================================================
 =                                                                         =
 =                        Constructors/destructors                         =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Void constructor
 ***************************************************************************/
GModelSpectralConst::GModelSpectralConst(void) : GModelSpectral()
{
    // Initialise members
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief XML constructor
 *
 * @param[in] xml XML element.
 *
 * Constructs constant spectral model by extracting information from an XML
 * element. See the read() method for more information about the expected
 * structure of the XML element.
 ***************************************************************************/
GModelSpectralConst::GModelSpectralConst(const GXmlElement& xml) :
                     GModelSpectral()
{
    // Initialise members
    init_members();

    // Read information from XML element
    read(xml);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Value constructor
 *
 * @param[in] norm Normalization factor (ph/cm2/s).
 *
 * Constructs constant spectral model by setting the normalization factor.
 ***************************************************************************/
GModelSpectralConst::GModelSpectralConst(const double& norm) :
                     GModelSpectral()
{
    // Initialise members
    init_members();

    // Set normalization factor
    m_norm.value(norm);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy constructor
 *
 * @param[in] model Spectral constant model.
 ***************************************************************************/
GModelSpectralConst::GModelSpectralConst(const GModelSpectralConst& model) :
                     GModelSpectral(model)
{
    // Initialise members
    init_members();

    // Copy members
    copy_members(model);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Destructor
 ***************************************************************************/
GModelSpectralConst::~GModelSpectralConst(void)
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
 * @param[in] model Constant spectral model.
 * @return Constant spectral model.
 ***************************************************************************/
GModelSpectralConst& GModelSpectralConst::operator=(const GModelSpectralConst& model)
{
    // Execute only if object is not identical
    if (this != &model) {

        // Copy base class members
        this->GModelSpectral::operator=(model);

        // Free members
        free_members();

        // Initialise members
        init_members();

        // Copy members
        copy_members(model);

    } // endif: object was not identical

    // Return
    return *this;
}


/*==========================================================================
 =                                                                         =
 =                              Public methods                             =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Clear constant spectral model
 ***************************************************************************/
void GModelSpectralConst::clear(void)
{
    // Free class members (base and derived classes, derived class first)
    free_members();
    this->GModelSpectral::free_members();

    // Initialise members
    this->GModelSpectral::init_members();
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Clone constant spectral model
 *
 * @return Pointer to deep copy of constant spectral model.
 ***************************************************************************/
GModelSpectralConst* GModelSpectralConst::clone(void) const
{
    // Clone constant spectral model
    return new GModelSpectralConst(*this);
}


/***********************************************************************//**
 * @brief Evaluate model
 *
 * @param[in] srcEng True photon energy.
 * @param[in] srcTime True photon arrival time.
 * @return Model value (ph/cm2/s/MeV).
 *
 * The spectral model is defined by
 *
 * \f[
 *    S_{\rm E}(E | t) = {\tt m\_norm}
 * \f]
 *
 * where
 * \f${\tt m\_norm}\f$ is the normalization constant in units of 
 * ph/cm2/s/MeV.
 ***************************************************************************/
double GModelSpectralConst::eval(const GEnergy& srcEng,
                                 const GTime&   srcTime) const
{
    // Compute function value
    double value = norm();

    // Return
    return value;
}


/***********************************************************************//**
 * @brief Evaluate function and gradients
 *
 * @param[in] srcEng True photon energy.
 * @param[in] srcTime True photon arrival time.
 * @return Model value (ph/cm2/s/MeV).
 *
 * The spectral model is defined by
 *
 * \f[
 *    S_{\rm E}(E | t) = {\tt m\_norm}
 * \f]
 *
 * where
 * \f${\tt m\_norm}\f$ is the normalization constant in units of 
 * ph/cm2/s/MeV.
 *
 * The normalization constant is factorized into a scale factor and a value
 * factor. The partial derivative with respect to the normalization constant
 * value factor is given by
 *
 * \f[
 *    \frac{\delta S_{\rm E}(E | t)}
 *         {\delta {\tt m\_norm.factor\_value()}} =
 *    {\tt m\_norm.scale()}
 * \f]
 ***************************************************************************/
double GModelSpectralConst::eval_gradients(const GEnergy& srcEng,
                                           const GTime&   srcTime)
{
    // Compute function value
    double value = norm();

    // Compute partial derivatives of the parameter values
    double g_norm = (m_norm.isfree()) ? m_norm.scale() : 0.0;

    // Set gradient
    m_norm.factor_gradient(g_norm);

    // Return
    return value;
}


/***********************************************************************//**
 * @brief Returns model photon flux between [emin, emax] (ph/cm2/s)
 *
 * @param[in] emin Minimum photon energy.
 * @param[in] emax Maximum photon energy.
 * @return Photon flux (ph/cm2/s).
 *
 * @exception GException::erange_invalid
 *            Energy range is invalid (emin < emax required).
 *
 * Computes
 *
 * \f[
 *    \int_{E_{\rm min}}^{E_{\rm max}} S_{\rm E}(E | t) dE
 * \f]
 *
 * where
 * - \f$E_{\rm min}\f$ and \f$E_{\rm max}\f$ are the minimum and maximum
 *   energy, respectively, and
 * - \f$S_{\rm E}(E | t)\f$ is the spectral model (ph/cm2/s/MeV).
 * The integration is done analytically.
 *
 * @todo What about returning a zero flux if the energy range is invalid?
 ***************************************************************************/
double GModelSpectralConst::flux(const GEnergy& emin,
                                 const GEnergy& emax) const
{
    // Throw an exception if energy range is invalid
    if (emin >= emax) {
        throw GException::erange_invalid(G_FLUX, emin.MeV(), emax.MeV(),
              "Minimum energy < maximum energy required.");
        
    }

    // Compute flux for a constant model
    double flux = norm() * (emax.MeV() - emin.MeV());

    // Return
    return flux;
}


/***********************************************************************//**
 * @brief Returns model energy flux between [emin, emax] (erg/cm2/s)
 *
 * @param[in] emin Minimum photon energy.
 * @param[in] emax Maximum photon energy.
 * @return Energy flux (erg/cm2/s).
 *
 * @exception GException::erange_invalid
 *            Energy range is invalid (emin < emax required).
 *
 * Computes
 *
 * \f[
 *    \int_{E_{\rm min}}^{E_{\rm max}} S_{\rm E}(E | t) E dE
 * \f]
 *
 * where
 * - \f$E_{\rm min}\f$ and \f$E_{\rm max}\f$ are the minimum and maximum
 *   energy, respectively, and
 * - \f$S_{\rm E}(E | t)\f$ is the spectral model (ph/cm2/s/MeV).
 * The integration is done analytically.
 *
 * @todo What about returning a zero flux if the energy range is invalid?
 ***************************************************************************/
double GModelSpectralConst::eflux(const GEnergy& emin,
                                  const GEnergy& emax) const
{
    // Throw an exception if energy range is invalid
    if (emin >= emax) {
        throw GException::erange_invalid(G_EFLUX, emin.MeV(), emax.MeV(),
              "Minimum energy < maximum energy required.");
    }

    // Compute flux for a constant model
    double flux = norm() * 0.5 * (emax.MeV()*emax.MeV() - 
                                  emin.MeV()*emin.MeV());

    // Convert from MeV/cm2/s to erg/cm2/s
    flux *= MeV2erg;

    // Return
    return flux;
}


/***********************************************************************//**
 * @brief Returns MC energy between [emin, emax]
 *
 * @param[in] emin Minimum photon energy.
 * @param[in] emax Maximum photon energy.
 * @param[in] time True photon arrival time.
 * @param[in,out] ran Random number generator.
 * @return Energy.
 *
 * @exception GException::erange_invalid
 *            Energy range is invalid (emin < emax required).
 *
 * Returns Monte Carlo energy by randomly drawing from a constant between
 * the minimum and maximum photon energy.
 ***************************************************************************/
GEnergy GModelSpectralConst::mc(const GEnergy& emin,
                                const GEnergy& emax,
                                const GTime&   time,
                                GRan&          ran) const
{
    // Throw an exception if energy range is invalid
    if (emin >= emax) {
        throw GException::erange_invalid(G_MC, emin.MeV(), emax.MeV(),
              "Minimum energy < maximum energy required.");
    }

    // Allocate energy
    GEnergy energy;

    // Get uniform value between 0 and 1
    double u = ran.uniform();

    // Map into [emin,emax] range
    energy.MeV((emax.MeV() - emin.MeV()) * u + emin.MeV());

    // Return energy
    return energy;
}


/***********************************************************************//**
 * @brief Read model from XML element
 *
 * @param[in] xml XML element containing power law model information.
 *
 * @exception GException::model_invalid_parnum
 *            Invalid number of model parameters found in XML element.
 * @exception GException::model_invalid_parnames
 *            Invalid model parameter name found in XML element.
 *
 * Reads the spectral information from an XML element having either the
 * format
 *
 *     <spectrum type="ConstantValue">
 *       <parameter name="Value" scale="1" min="0" max="1000" value="1" free="1"/>
 *     </spectrum>
 *
 * or the format
 *
 *     <spectrum type="ConstantValue">
 *       <parameter name="Normalization" scale="1" min="0" max="1000" value="1" free="1"/>
 *     </spectrum>
 ***************************************************************************/
void GModelSpectralConst::read(const GXmlElement& xml)
{
    // Verify that XML element has exactly 1 parameter
    if (xml.elements() != 1 || xml.elements("parameter") != 1) {
        throw GException::model_invalid_parnum(G_READ, xml,
              "Spectral constant requires exactly 1 parameter.");
    }

    // Get parameter element
    const GXmlElement* par = xml.element("parameter", 0);

    // Get value
    if (par->attribute("name") == "Normalization" ||
        par->attribute("name") == "Value") {
        m_norm.read(*par);
    }
    else {
        throw GException::model_invalid_parnames(G_READ, xml,
                          "Spectral constant requires either"
                          " \"Normalization\" or \"Value\" parameter.");
    }

    // Return
    return;
}


/***********************************************************************//**
 * @brief Write model into XML element
 *
 * @param[in] xml XML element into which model information is written.
 *
 * @exception GException::model_invalid_spectral
 *            Existing XML element is not of type "ConstantValue"
 * @exception GException::model_invalid_parnum
 *            Invalid number of model parameters or nodes found in XML element.
 * @exception GException::model_invalid_parnames
 *            Invalid model parameter names found in XML element.
 *
 * Writes the spectral information into an XML element with the format
 *
 *     <spectrum type="ConstantValue">
 *       <parameter name="Value" scale="1" min="0" max="1000" value="1" free="1"/>
 *     </spectrum>
 ***************************************************************************/
void GModelSpectralConst::write(GXmlElement& xml) const
{
    // Set model type
    if (xml.attribute("type") == "") {
        xml.attribute("type", "ConstantValue");
    }

    // Verify model type
    if (xml.attribute("type") != "ConstantValue") {
        throw GException::model_invalid_spectral(G_WRITE, xml.attribute("type"),
              "Spectral model is not of type \"ConstantValue\".");
    }

    // If XML element has 0 nodes then append parameter node. The name
    // of the node is "Value" as this is the Fermi-LAT standard.
    // We thus assure that the XML files will be compatible with
    // Fermi-LAT.
    if (xml.elements() == 0) {
        xml.append(GXmlElement("parameter name=\"Value\""));
    }

    // Verify that XML element has exactly 1 parameter
    if (xml.elements() != 1 || xml.elements("parameter") != 1) {
        throw GException::model_invalid_parnum(G_WRITE, xml,
              "Spectral constant requires exactly 1 parameter.");
    }

    // Get parameter element
    GXmlElement* par = xml.element("parameter", 0);

    // Set parameyter
    if (par->attribute("name") == "Normalization" ||
        par->attribute("name") == "Value") {
        m_norm.write(*par);
    }
    else {
        throw GException::model_invalid_parnames(G_WRITE, xml,
                          "Spectral constant requires either"
                          " \"Normalization\" or \"Value\" parameter.");
    }

    // Return
    return;
}


/***********************************************************************//**
 * @brief Print spectral model information
 *
 * @return String containing spectral model information.
 ***************************************************************************/
std::string GModelSpectralConst::print(void) const
{
    // Initialise result string
    std::string result;

    // Append header
    result.append("=== GModelSpectralConst ===\n");

    // Append model content
    result.append(parformat("Number of parameters")+str(size()));
    for (int i = 0; i < size(); ++i) {
        result.append("\n"+m_pars[i]->print());
    }

    // Return result
    return result;
}


/*==========================================================================
 =                                                                         =
 =                             Private methods                             =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Initialise class members
 ***************************************************************************/
void GModelSpectralConst::init_members(void)
{
    // Initialise constant normalisation
    m_norm.clear();
    m_norm.name("Value");
    m_norm.scale(1.0);
    m_norm.value(1.0);         // default: 1.0
    m_norm.range(0.0, 1000.0); // range:   [0, 1000]
    m_norm.free();
    m_norm.gradient(0.0);
    m_norm.hasgrad(true);

    // Set parameter pointer(s)
    m_pars.clear();
    m_pars.push_back(&m_norm);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy class members
 *
 * @param[in] model Spectral constant model.
 ***************************************************************************/
void GModelSpectralConst::copy_members(const GModelSpectralConst& model)
{
    // Copy members
    m_norm = model.m_norm;

    // Set parameter pointer(s)
    m_pars.clear();
    m_pars.push_back(&m_norm);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Delete class members
 ***************************************************************************/
void GModelSpectralConst::free_members(void)
{
    // Return
    return;
}
