/***************************************************************************
 *                          ctalib - SWIG file                             *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2010-2011 by Jurgen Knodlseder                           *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 * Usage:                                                                  *
 * swig -c++ -python -Wall ctalib.i                                        *
 ***************************************************************************/
%module ctalib

/* __ CTA ________________________________________________________________ */
%include "GCTAObservation.i"
%include "GCTAEventCube.i"
%include "GCTAEventList.i"
%include "GCTAEventBin.i"
%include "GCTAEventAtom.i"
%include "GCTAPointing.i"
%include "GCTAResponse.i"
%include "GCTAInstDir.i"
%include "GCTARoi.i"
%include "GCTAModelRadial.i"
%include "GCTAModelRadialRegistry.i"
%include "GCTAModelRadialGauss.i"
%include "GCTAModelRadialAcceptance.i"



