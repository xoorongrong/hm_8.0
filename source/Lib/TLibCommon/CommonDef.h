/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.  
 *
 * Copyright (c) 2010-2012, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/** \file     CommonDef.h
    \brief    Defines constants, macros and tool parameters
*/

#ifndef __COMMONDEF__
#define __COMMONDEF__

#include <algorithm>

#if _MSC_VER > 1000
// disable "signed and unsigned mismatch"
#pragma warning( disable : 4018 )
// disable bool coercion "performance warning"
#pragma warning( disable : 4800 )
#endif // _MSC_VER > 1000
#include "TypeDef.h"

//! \ingroup TLibCommon
//! \{

// ====================================================================================================================
// Version information
// ====================================================================================================================

#define NV_VERSION        "8.0"                 ///< Current software version

// ====================================================================================================================
// Platform information
// ====================================================================================================================

#ifdef __GNUC__
#define NVM_COMPILEDBY  "[GCC %d.%d.%d]", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__
#ifdef __IA64__
#define NVM_ONARCH    "[on 64-bit] "
#else
#define NVM_ONARCH    "[on 32-bit] "
#endif
#endif

#ifdef __INTEL_COMPILER
#define NVM_COMPILEDBY  "[ICC %d]", __INTEL_COMPILER
#elif  _MSC_VER
#define NVM_COMPILEDBY  "[VS %d]", _MSC_VER
#endif

#ifndef NVM_COMPILEDBY
#define NVM_COMPILEDBY "[Unk-CXX]"
#endif

#ifdef _WIN32
#define NVM_ONOS        "[Windows]"
#elif  __linux
#define NVM_ONOS        "[Linux]"
#elif  __CYGWIN__
#define NVM_ONOS        "[Cygwin]"
#elif __APPLE__
#define NVM_ONOS        "[Mac OS X]"
#else
#define NVM_ONOS "[Unk-OS]"
#endif

#define NVM_BITS          "[%d bit] ", (sizeof(void*) == 8 ? 64 : 32) ///< used for checking 64-bit O/S

#ifndef NULL
#define NULL              0
#endif

// ====================================================================================================================
// Common constants
// ====================================================================================================================

#define _SUMMARY_OUT_               0           ///< print-out PSNR results of all slices to summary.txt
#define _SUMMARY_PIC_               0           ///< print-out PSNR results for each slice type to summary.txt

#define MAX_GOP                     64          ///< max. value of hierarchical GOP size

#define MAX_NUM_REF                 4           ///< max. value of multiple reference frames
#define MAX_NUM_REF_LC              8           ///< max. value of combined reference frames

#define MAX_UINT                    0xFFFFFFFFU ///< max. value of unsigned 32-bit integer
#define MAX_INT                     2147483647  ///< max. value of signed 32-bit integer
#define MAX_INT64                   0x7FFFFFFFFFFFFFFF  ///< max. value of signed 64-bit integer
#define MAX_DOUBLE                  1.7e+308    ///< max. value of double-type value

#define MIN_QP                      0
#define MAX_QP                      51

#define NOT_VALID                   -1

// ====================================================================================================================
// Macro functions
// ====================================================================================================================
extern UInt g_uiIBDI_MAX;

/** clip x, such that 0 <= x <= #g_uiIBDI_MAX */
template <typename T> inline T Clip(T x) { return std::min<T>(T(g_uiIBDI_MAX), std::max<T>( T(0), x)); }

/** clip a, such that minVal <= a <= maxVal */
template <typename T> inline T Clip3( T minVal, T maxVal, T a) { return std::min<T> (std::max<T> (minVal, a) , maxVal); }  ///< general min/max clip

#define DATA_ALIGN                  1                                                                 ///< use 32-bit aligned malloc/free
#if     DATA_ALIGN && _WIN32 && ( _MSC_VER > 1300 )
#define xMalloc( type, len )        _aligned_malloc( sizeof(type)*(len), 32 )
#define xFree( ptr )                _aligned_free  ( ptr )
#else
#define xMalloc( type, len )        malloc   ( sizeof(type)*(len) )
#define xFree( ptr )                free     ( ptr )
#endif

#define FATAL_ERROR_0(MESSAGE, EXITCODE)                      \
{                                                             \
  printf(MESSAGE);                                            \
  exit(EXITCODE);                                             \
}


// ====================================================================================================================
// Coding tool configuration
// ====================================================================================================================

// AMVP: advanced motion vector prediction
#define AMVP_MAX_NUM_CANDS          2           ///< max number of final candidates
#define AMVP_MAX_NUM_CANDS_MEM      3           ///< max number of candidates
// MERGE
#define MRG_MAX_NUM_CANDS           5

// Reference memory management
#define DYN_REF_FREE                0           ///< dynamic free of reference memories

// Explicit temporal layer QP offset
#define MAX_TLAYER                  8           ///< max number of temporal layer
#define HB_LAMBDA_FOR_LDC           1           ///< use of B-style lambda for non-key pictures in low-delay mode

// Fast estimation of generalized B in low-delay mode
#define GPB_SIMPLE                  1           ///< Simple GPB mode
#if     GPB_SIMPLE
#define GPB_SIMPLE_UNI              1           ///< Simple mode for uni-direction
#endif

// Fast ME using smoother MV assumption
#define FASTME_SMOOTHER_MV          1           ///< reduce ME time using faster option

// Adaptive search range depending on POC difference
#define ADAPT_SR_SCALE              1           ///< division factor for adaptive search range

#define CLIP_TO_709_RANGE           0

// IBDI range restriction for skipping clip
#define IBDI_NOCLIP_RANGE           0           ///< restrict max. value after IBDI to skip clip

// Early-skip threshold (encoder)
#define EARLY_SKIP_THRES            1.50        ///< if RD < thres*avg[BestSkipRD]

#define MAX_NUM_REF_PICS 16

#define MAX_CHROMA_FORMAT_IDC      3

enum NalUnitType
{
  NAL_UNIT_UNSPECIFIED_0 = 0,
  NAL_UNIT_CODED_SLICE,           // 1
  NAL_UNIT_CODED_SLICE_TFD,       // 2
  NAL_UNIT_CODED_SLICE_TLA,       // 3
  NAL_UNIT_CODED_SLICE_CRA,       // 4
  NAL_UNIT_CODED_SLICE_CRANT,     // 5
  NAL_UNIT_CODED_SLICE_BLA,       // 6
  NAL_UNIT_CODED_SLICE_BLANT,     // 7
  NAL_UNIT_CODED_SLICE_IDR,       // 8
  NAL_UNIT_RESERVED_9,
  NAL_UNIT_RESERVED_10,
  NAL_UNIT_RESERVED_11,
  NAL_UNIT_RESERVED_12,
  NAL_UNIT_RESERVED_13,
  NAL_UNIT_RESERVED_14,
  NAL_UNIT_RESERVED_15,
  NAL_UNIT_RESERVED_16,
  NAL_UNIT_RESERVED_17,
  NAL_UNIT_RESERVED_18,
  NAL_UNIT_RESERVED_19,
  NAL_UNIT_RESERVED_20,
  NAL_UNIT_RESERVED_21,
  NAL_UNIT_RESERVED_22,
  NAL_UNIT_RESERVED_23,
  NAL_UNIT_RESERVED_24,
  NAL_UNIT_VPS,                   // 25
  NAL_UNIT_SPS,                   // 26
  NAL_UNIT_PPS,                   // 27
#if REMOVE_APS
  NAL_UNIT_RESERVED_28,
#else
  NAL_UNIT_APS,                   // 28
#endif
  NAL_UNIT_ACCESS_UNIT_DELIMITER, // 29
  NAL_UNIT_FILLER_DATA,           // 30
  NAL_UNIT_SEI,                   // 31
  NAL_UNIT_RESERVED_32,
  NAL_UNIT_RESERVED_33,
  NAL_UNIT_RESERVED_34,
  NAL_UNIT_RESERVED_35,
  NAL_UNIT_RESERVED_36,
  NAL_UNIT_RESERVED_37,
  NAL_UNIT_RESERVED_38,
  NAL_UNIT_RESERVED_39,
  NAL_UNIT_RESERVED_40,
  NAL_UNIT_RESERVED_41,
  NAL_UNIT_RESERVED_42,
  NAL_UNIT_RESERVED_43,
  NAL_UNIT_RESERVED_44,
  NAL_UNIT_RESERVED_45,
  NAL_UNIT_RESERVED_46,
  NAL_UNIT_RESERVED_47,
  NAL_UNIT_UNSPECIFIED_48,
  NAL_UNIT_UNSPECIFIED_49,
  NAL_UNIT_UNSPECIFIED_50,
  NAL_UNIT_UNSPECIFIED_51,
  NAL_UNIT_UNSPECIFIED_52,
  NAL_UNIT_UNSPECIFIED_53,
  NAL_UNIT_UNSPECIFIED_54,
  NAL_UNIT_UNSPECIFIED_55,
  NAL_UNIT_UNSPECIFIED_56,
  NAL_UNIT_UNSPECIFIED_57,
  NAL_UNIT_UNSPECIFIED_58,
  NAL_UNIT_UNSPECIFIED_59,
  NAL_UNIT_UNSPECIFIED_60,
  NAL_UNIT_UNSPECIFIED_61,
  NAL_UNIT_UNSPECIFIED_62,
  NAL_UNIT_UNSPECIFIED_63,
  NAL_UNIT_INVALID,
};

//! \}

#endif // end of #ifndef  __COMMONDEF__

