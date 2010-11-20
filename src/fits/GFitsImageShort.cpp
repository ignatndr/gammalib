/***************************************************************************
 *          GFitsImageShort.cpp  - FITS unsigned short image class         *
 * ----------------------------------------------------------------------- *
 *  copyright : (C) 2010 by Jurgen Knodlseder                              *
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
#include "GFitsCfitsio.hpp"
#include "GFitsImageShort.hpp"

/* __ Method name definitions ____________________________________________ */

/* __ Macros _____________________________________________________________ */
#define G_BITPIX 16                 //!< Defines the number of bits per pixel

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
GFitsImageShort::GFitsImageShort(void) : GFitsImage()
{
    // Initialise class members for clean destruction
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief 1D image constructor
 *
 * @param[in] nx Number of pixels.
 * @param[in] pixels Optional pointer to image pixel array
 *
 * Construct 1D instance by specifying the number of pixels in the image.
 ***************************************************************************/
GFitsImageShort::GFitsImageShort(int nx, const short* pixels) :
                 GFitsImage(G_BITPIX, nx)
{
    // Initialise class members for clean destruction
    init_members();

    // Construct data
    construct_data(pixels);

    // Return
    return;
}


/***********************************************************************//**
 * @brief 2D image constructor
 *
 * @param[in] nx Number of pixels in first dimension.
 * @param[in] ny Number of pixels in second dimension.
 * @param[in] pixels Optional pointer to image pixel array
 *
 * Construct 2D image by specifying the number of pixels in each dimension.
 ***************************************************************************/
GFitsImageShort::GFitsImageShort(int nx, int ny, const short* pixels) :
                 GFitsImage(G_BITPIX, nx, ny)
{
    // Initialise class members for clean destruction
    init_members();

    // Construct data
    construct_data(pixels);

    // Return
    return;
}


/***********************************************************************//**
 * @brief 3D image constructor
 *
 * @param[in] nx Number of pixels in first dimension.
 * @param[in] ny Number of pixels in second dimension.
 * @param[in] nz Number of pixels in third dimension.
 * @param[in] pixels Optional pointer to image pixel array
 *
 * Construct 3D image by specifying the number of pixels in each dimension.
 ***************************************************************************/
GFitsImageShort::GFitsImageShort(int nx, int ny, int nz,
                                 const short* pixels) :
                 GFitsImage(G_BITPIX, nx, ny, nz)
{
    // Initialise class members for clean destruction
    init_members();

    // Construct data
    construct_data(pixels);

    // Return
    return;
}


/***********************************************************************//**
 * @brief 4D image constructor
 *
 * @param[in] nx Number of pixels in first dimension.
 * @param[in] ny Number of pixels in second dimension.
 * @param[in] nz Number of pixels in third dimension.
 * @param[in] nt Number of pixels in forth dimension.
 * @param[in] pixels Optional pointer to image pixel array
 *
 * Construct 4D image by specifying the number of pixels in each dimension.
 ***************************************************************************/
GFitsImageShort::GFitsImageShort(int nx, int ny, int nz, int nt,
                                 const short* pixels) :
                 GFitsImage(G_BITPIX, nx, ny, nz, nt)
{
    // Initialise class members for clean destruction
    init_members();

    // Construct data
    construct_data(pixels);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Pixel array constructor
 *
 * @param[in] naxis Image dimension (0,1,2,3,4).
 * @param[in] naxes Number of pixels in each dimension.
 * @param[in] pixels Optional pointer to image pixel array
 *
 * Construct instance of GFitsImageShort by specifying the image dimension and
 * the number of pixels in each dimension. Note that this constructor does
 * not allocate any memory for the actual image.
 ***************************************************************************/
GFitsImageShort::GFitsImageShort(int naxis, const int* naxes, const short* pixels) :
                 GFitsImage(G_BITPIX, naxis, naxes)
{
    // Initialise class members for clean destruction
    init_members();

    // If there are pixels then allocate array
    if (m_num_pixels > 0) {

        // Allocate data
        alloc_data();

        // If no pixel array has been specified then simply initialise data
        if (pixels == NULL)
            init_data();

        // ... otherwise copy pixels
        else {
            for (int i = 0; i < m_num_pixels; ++i)
                m_pixels[i] = pixels[i];
        }

    } // endif: there are pixels in image

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy constructor
 *
 * @param[in] image FITS image.
 ***************************************************************************/
GFitsImageShort::GFitsImageShort(const GFitsImageShort& image) :
                 GFitsImage(image)
{
    // Initialise class members for clean destruction
    init_members();

    // Copy members
    copy_members(image);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Destructor
 ***************************************************************************/
GFitsImageShort::~GFitsImageShort(void)
{
    // Free members
    free_members();

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                               Operators                                 =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Assignment operator
 *
 * @param[in] image FITS image.
 ***************************************************************************/
GFitsImageShort& GFitsImageShort::operator= (const GFitsImageShort& image)
{
    // Execute only if object is not identical
    if (this != &image) {

        // Copy base class members
        this->GFitsImage::operator=(image);

        // Free members
        free_members();

        // Initialise private members for clean destruction
        init_members();

        // Copy members
        copy_members(image);

    } // endif: object was not identical

    // Return this object
    return *this;
}


/***********************************************************************//**
 * @brief Image pixel access operator
 *
 * @param[in] ix Pixel index (starting from 0).
 *
 * Provides access to an image pixel. No range checking is performed.
 * Use the at(ix) method if range checking is required.
 ***************************************************************************/
short& GFitsImageShort::operator() (const int& ix)
{
    // If image pixels are not available then fetch them now
    if (m_pixels == NULL) fetch_data();

    // Return image pixel
    return m_pixels[ix];
}


/***********************************************************************//**
 * @brief 2D image pixel access operator
 *
 * @param[in] ix Pixel index in first dimension (starting from 0).
 * @param[in] iy Pixel index in second dimension (starting from 0).
 *
 * Provides access to a pixel of a 2D image. No range checking or image
 * dimension verification is performed. Use the at(ix,iy) method if range
 * checking and image dimension verification is required.
 ***************************************************************************/
short& GFitsImageShort::operator() (const int& ix, const int& iy)
{
    // If image pixels are not available then allocate them now
    if (m_pixels == NULL) fetch_data();

    // Calculate pixel offset
    int offset = ix + iy * m_naxes[0];

    // Return image pixel
    return m_pixels[offset];
}


/***********************************************************************//**
 * @brief 3D image pixel access operator
 *
 * @param[in] ix Pixel index in first dimension (starting from 0).
 * @param[in] iy Pixel index in second dimension (starting from 0).
 * @param[in] iz Pixel index in third dimension (starting from 0).
 *
 * Provides access to a pixel of a 3D image. No range checking or image
 * dimension verification is performed. Use the at(ix,iy) method if range
 * checking and image dimension verification is required.
 ***************************************************************************/
short& GFitsImageShort::operator() (const int& ix, const int& iy,
                                              const int& iz)
{
    // If image pixels are not available then allocate them now
    if (m_pixels == NULL) fetch_data();

    // Calculate pixel offset
    int offset = ix + m_naxes[0] * (iy + iz * m_naxes[1]);

    // Return image pixel
    return m_pixels[offset];
}


/***********************************************************************//**
 * @brief 4D image pixel access operator
 *
 * @param[in] ix Pixel index in first dimension (starting from 0).
 * @param[in] iy Pixel index in second dimension (starting from 0).
 * @param[in] iz Pixel index in third dimension (starting from 0).
 * @param[in] it Pixel index in forth dimension (starting from 0).
 *
 * Provides access to a pixel of a 4D image. No range checking or image
 * dimension verification is performed. Use the at(ix,iy) method if range
 * checking and image dimension verification is required.
 ***************************************************************************/
short& GFitsImageShort::operator() (const int& ix, const int& iy,
                                    const int& iz, const int& it)
{
    // If image pixels are not available then allocate them now
    if (m_pixels == NULL) fetch_data();

    // Calculate pixel offset
    int offset = ix + m_naxes[0] * (iy + m_naxes[1] * (iz + it *  m_naxes[2]));

    // Return image pixel
    return m_pixels[offset];
}


/***********************************************************************//**
 * @brief Image pixel access operator (const variant)
 *
 * @param[in] ix Pixel index (starting from 0).
 *
 * Provides access to an image pixel. No range checking is performed.
 * Use the at(ix) method if range checking is required.
 ***************************************************************************/
const short& GFitsImageShort::operator() (const int& ix) const
{
    // If image pixels are not available then fetch them now
    if (m_pixels == NULL) ((GFitsImageShort*)this)->fetch_data();

    // Return image pixel
    return m_pixels[ix];
}


/***********************************************************************//**
 * @brief 2D image pixel access operator (const variant)
 *
 * @param[in] ix Pixel index in first dimension (starting from 0).
 * @param[in] iy Pixel index in second dimension (starting from 0).
 *
 * Provides access to a pixel of a 2D image. No range checking or image
 * dimension verification is performed. Use the at(ix,iy) method if range
 * checking and image dimension verification is required.
 ***************************************************************************/
const short& GFitsImageShort::operator() (const int& ix, const int& iy) const
{
    // If image pixels are not available then allocate them now
    if (m_pixels == NULL) ((GFitsImageShort*)this)->fetch_data();

    // Calculate pixel offset
    int offset = ix + iy * m_naxes[0];

    // Return image pixel
    return m_pixels[offset];
}


/***********************************************************************//**
 * @brief 3D image pixel access operator (const variant)
 *
 * @param[in] ix Pixel index in first dimension (starting from 0).
 * @param[in] iy Pixel index in second dimension (starting from 0).
 * @param[in] iz Pixel index in third dimension (starting from 0).
 *
 * Provides access to a pixel of a 3D image. No range checking or image
 * dimension verification is performed. Use the at(ix,iy) method if range
 * checking and image dimension verification is required.
 ***************************************************************************/
const short& GFitsImageShort::operator() (const int& ix, const int& iy,
                                          const int& iz) const
{
    // If image pixels are not available then allocate them now
    if (m_pixels == NULL) ((GFitsImageShort*)this)->fetch_data();

    // Calculate pixel offset
    int offset = ix + m_naxes[0] * (iy + iz * m_naxes[1]);

    // Return image pixel
    return m_pixels[offset];
}


/***********************************************************************//**
 * @brief 4D image pixel access operator (const variant)
 *
 * @param[in] ix Pixel index in first dimension (starting from 0).
 * @param[in] iy Pixel index in second dimension (starting from 0).
 * @param[in] iz Pixel index in third dimension (starting from 0).
 * @param[in] it Pixel index in forth dimension (starting from 0).
 *
 * Provides access to a pixel of a 4D image. No range checking or image
 * dimension verification is performed. Use the at(ix,iy) method if range
 * checking and image dimension verification is required.
 ***************************************************************************/
const short& GFitsImageShort::operator() (const int& ix, const int& iy,
                                          const int& iz, const int& it) const
{
    // If image pixels are not available then allocate them now
    if (m_pixels == NULL) ((GFitsImageShort*)this)->fetch_data();

    // Calculate pixel offset
    int offset = ix + m_naxes[0] * (iy + m_naxes[1] * (iz + it *  m_naxes[2]));

    // Return image pixel
    return m_pixels[offset];
}


/*==========================================================================
 =                                                                         =
 =                             Public methods                              =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Image pixel access operator
 *
 * @param[in] ix Pixel index (starting from 0).
 *
 * Provides access to a pixel of an image including range checking. Note that
 * this method does not necessarily restrict do 1D images but generally
 * applies to all image dimensions.
 ***************************************************************************/
short& GFitsImageShort::at(const int& ix)
{
    // If image pixels are not available then allocate them now
    if (m_pixels == NULL) fetch_data();

    // Return image pixel
    return (m_pixels[offset(ix)]);
}


/***********************************************************************//**
 * @brief 2D image pixel access operator
 *
 * @param[in] ix Pixel index in first dimension (starting from 0).
 * @param[in] iy Pixel index in second dimension (starting from 0).
 *
 * Provides access to a pixel of an image including range checking.
 ***************************************************************************/
short& GFitsImageShort::at(const int& ix, const int& iy)
{
    // If image pixels are not available then allocate them now
    if (m_pixels == NULL) fetch_data();

    // Return image pixel
    return (m_pixels[offset(ix,iy)]);
}


/***********************************************************************//**
 * @brief 3D image pixel access operator
 *
 * @param[in] ix Pixel index in first dimension (starting from 0).
 * @param[in] iy Pixel index in second dimension (starting from 0).
 * @param[in] iz Pixel index in third dimension (starting from 0).
 *
 * Provides access to a pixel of an image including range checking.
 ***************************************************************************/
short& GFitsImageShort::at(const int& ix, const int& iy, const int& iz)
{
    // If image pixels are not available then allocate them now
    if (m_pixels == NULL) fetch_data();

    // Return image pixel
    return (m_pixels[offset(ix,iy,iz)]);
}


/***********************************************************************//**
 * @brief 4D image pixel access operator
 *
 * @param[in] ix Pixel index in first dimension (starting from 0).
 * @param[in] iy Pixel index in second dimension (starting from 0).
 * @param[in] iz Pixel index in third dimension (starting from 0).
 * @param[in] it Pixel index in forth dimension (starting from 0).
 *
 * Provides access to a pixel of an image including range checking.
 ***************************************************************************/
short& GFitsImageShort::at(const int& ix, const int& iy, const int& iz,
                           const int& it)
{
    // If image pixels are not available then allocate them now
    if (m_pixels == NULL) fetch_data();

    // Return image pixel
    return (m_pixels[offset(ix,iy,iz,it)]);
}


/***********************************************************************//**
 * @brief Image pixel access operator (const variant)
 *
 * @param[in] ix Pixel index (starting from 0).
 *
 * Provides access to a pixel of an image including range checking.
 ***************************************************************************/
const short& GFitsImageShort::at(const int& ix) const
{
    // If image pixels are not available then allocate them now
    if (m_pixels == NULL) ((GFitsImageShort*)this)->fetch_data();

    // Return image pixel
    return (m_pixels[offset(ix)]);
}


/***********************************************************************//**
 * @brief 2D image pixel access operator (const variant)
 *
 * @param[in] ix Pixel index in first dimension (starting from 0).
 * @param[in] iy Pixel index in second dimension (starting from 0).
 *
 * Provides access to a pixel of an image including range checking.
 ***************************************************************************/
const short& GFitsImageShort::at(const int& ix, const int& iy) const
{
    // If image pixels are not available then allocate them now
    if (m_pixels == NULL) ((GFitsImageShort*)this)->fetch_data();

    // Return image pixel
    return (m_pixels[offset(ix,iy)]);
}


/***********************************************************************//**
 * @brief 3D image pixel access operator (const variant)
 *
 * @param[in] ix Pixel index in first dimension (starting from 0).
 * @param[in] iy Pixel index in second dimension (starting from 0).
 * @param[in] iz Pixel index in third dimension (starting from 0).
 *
 * Provides access to a pixel of an image including range checking.
 ***************************************************************************/
const short& GFitsImageShort::at(const int& ix, const int& iy,
                                 const int& iz) const
{
    // If image pixels are not available then allocate them now
    if (m_pixels == NULL) ((GFitsImageShort*)this)->fetch_data();

    // Return image pixel
    return (m_pixels[offset(ix,iy,iz)]);
}


/***********************************************************************//**
 * @brief 4D image pixel access operator (const variant)
 *
 * @param[in] ix Pixel index in first dimension (starting from 0).
 * @param[in] iy Pixel index in second dimension (starting from 0).
 * @param[in] iz Pixel index in third dimension (starting from 0).
 * @param[in] it Pixel index in forth dimension (starting from 0).
 *
 * Provides access to a pixel of an image including range checking.
 ***************************************************************************/
const short& GFitsImageShort::at(const int& ix, const int& iy,
                                 const int& iz, const int& it) const
{
    // If image pixels are not available then allocate them now
    if (m_pixels == NULL) ((GFitsImageShort*)this)->fetch_data();

    // Return image pixel
    return (m_pixels[offset(ix,iy,iz,it)]);
}


/***********************************************************************//**
 * @brief Return value of image pixel
 *
 * @param[in] ix Pixel index (starting from 0).
 *
 * Returns the value of an image pixel as double precision floating point
 * value. This method performs range checking.
 ***************************************************************************/
double GFitsImageShort::pixel(const int& ix) const
{
    // Return pixel value
    return (double(this->at(ix)));
}


/***********************************************************************//**
 * @brief Return value of image pixel (2D version)
 *
 * @param[in] ix Pixel index in first dimension (starting from 0).
 * @param[in] iy Pixel index in second dimension (starting from 0).
 *
 * Returns the value of an image pixel as double precision floating point
 * value. This method performs range checking.
 ***************************************************************************/
double GFitsImageShort::pixel(const int& ix, const int& iy) const
{
    // Return pixel value
    return (double(this->at(ix,iy)));
}


/***********************************************************************//**
 * @brief Return value of image pixel (3D version)
 *
 * @param[in] ix Pixel index in first dimension (starting from 0).
 * @param[in] iy Pixel index in second dimension (starting from 0).
 * @param[in] iz Pixel index in third dimension (starting from 0).
 *
 * Returns the value of an image pixel as double precision floating point
 * value. This method performs range checking.
 ***************************************************************************/
double GFitsImageShort::pixel(const int& ix, const int& iy, const int& iz) const
{
    // Return pixel value
    return (double(this->at(ix,iy,iz)));
}


/***********************************************************************//**
 * @brief Return value of image pixel (4D version)
 *
 * @param[in] ix Pixel index in first dimension (starting from 0).
 * @param[in] iy Pixel index in second dimension (starting from 0).
 * @param[in] iz Pixel index in third dimension (starting from 0).
 * @param[in] it Pixel index in forth dimension (starting from 0).
 *
 * Returns the value of an image pixel as double precision floating point
 * value. This method performs range checking.
 ***************************************************************************/
double GFitsImageShort::pixel(const int& ix, const int& iy, const int& iz,
                              const int& it) const
{
    // Return pixel value
    return (double(this->at(ix,iy,iz,it)));
}


/***********************************************************************//**
 * @brief Return pointer to image pixel
 ***************************************************************************/
void* GFitsImageShort::pixels(void)
{
    // If image pixels are not available then allocate them now
    if (m_pixels == NULL) fetch_data();

    // Return
    return m_pixels;
}


/***********************************************************************//**
 * @brief Clone FITS image
 *
 * Cloning provides a copy of the FITS file. Cloning is used to allocate
 * derived classes into a base class pointer.
 ***************************************************************************/
GFitsImageShort* GFitsImageShort::clone(void) const
{
    // Clone this image
    return new GFitsImageShort(*this);
}


/*==========================================================================
 =                                                                         =
 =                             Private methods                             =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Initialise class members
 ***************************************************************************/
void GFitsImageShort::init_members(void)
{
    // Initialise members
    m_bitpix = G_BITPIX;
    m_pixels = NULL;
    m_nulval = NULL;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy class members
 *
 * @param image FITS image to copy
 *
 * Copy class members. If the pixel array is linked the pointer to the array
 * is copied. Otherwise a copy of the image pixels will be created.
 ***************************************************************************/
void GFitsImageShort::copy_members(const GFitsImageShort& image)
{
    // Fetch column data if not yet fetched. The casting circumvents the
    // const correctness
    bool not_loaded = (image.m_pixels == NULL);
    if (not_loaded) ((GFitsImageShort*)(&image))->fetch_data();

    // Copy pixels
    if (m_num_pixels > 0 && image.m_pixels != NULL) {
        m_pixels = new short[m_num_pixels];
        for (int i = 0; i < m_num_pixels; ++i)
            m_pixels[i] = image.m_pixels[i];
    }

    // Copy NULL value
    alloc_nulval(image.m_nulval);

    // Small memory option: release column if it was fetch above
    #if defined(G_SMALL_MEMORY)
    if (not_loaded) ((GFitsImageShort*)(&image))->release_data();
    #endif

    // Return
    return;
}


/***********************************************************************//**
 * @brief Delete class members
 ***************************************************************************/
void GFitsImageShort::free_members(void)
{
    // Free memory
    if (m_pixels != NULL) delete [] m_pixels;
    if (m_nulval != NULL) delete m_nulval;

    // Mark memory as free
    m_pixels = NULL;
    m_nulval = NULL;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Allocate data
 ***************************************************************************/
void GFitsImageShort::alloc_data(void)
{
    // Release any existing data
    release_data();

    // Allocate new data
    if (m_num_pixels > 0)
        m_pixels = new short[m_num_pixels];

    // Return
    return;
}


/***********************************************************************//**
 * @brief Initialise data
 ***************************************************************************/
void GFitsImageShort::init_data(void)
{
    // Initialise data if they exist
    if (m_pixels != NULL) {
        for (int i = 0; i < m_num_pixels; ++i)
            m_pixels[i] = 0;
    }

    // Return
    return;
}


/***********************************************************************//**
 * @brief Release data
 ***************************************************************************/
void GFitsImageShort::release_data(void)
{
    // Free any existing memory
    if (m_pixels != NULL) delete [] m_pixels;

    // Mark pointer as free
    m_pixels = NULL;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Construct data from array
 *
 * @param[in] pixels Optional pointer to pixel array.
 *
 * Initialise pixel data from an optional pixel array. If the pointer is
 * NULL the image is simply initialised. This method supports all
 * constructors.
 ***************************************************************************/
void GFitsImageShort::construct_data(const short* pixels)
{
    // If there are pixels then allocate array
    if (m_num_pixels > 0) {

        // Allocate data
        alloc_data();

        // If no pixel array has been specified then simply initialise data
        if (pixels == NULL)
            init_data();

        // ... otherwise copy pixels
        else {
            for (int i = 0; i < m_num_pixels; ++i)
                m_pixels[i] = pixels[i];
        }

    } // endif: there are pixels in image

    // Return
    return;
}


/***********************************************************************//**
 * @brief Allocates nul value
 ***************************************************************************/
void GFitsImageShort::alloc_nulval(const void* value)
{
    // Free any existing memory
    if (m_nulval != NULL) delete m_nulval;

    // Mark pointer as free
    m_nulval = NULL;

    // If we have valid value, allocate and set nul value
    if (value != NULL) {
        m_nulval  = new short;
        *m_nulval = *((short*)value);
    }

    // Return
    return;
}


/***********************************************************************//**
 * @brief Return image type
 ***************************************************************************/
int GFitsImageShort::type(void) const
{
    // Return type
    return __TSHORT;
}


/*==========================================================================
 =                                                                         =
 =                                 Friends                                 =
 =                                                                         =
 ==========================================================================*/