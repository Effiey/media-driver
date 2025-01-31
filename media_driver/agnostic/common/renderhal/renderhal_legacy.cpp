/*
* Copyright (c) 2022, Intel Corporation
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*/
//!
//! \file     renderhal_legacy.cpp
//! \brief    Render Engine state heap manager for VP and CM
//! \details  Platform/OS Independent Render Engine state heap management interfaces
//!

#include "renderhal_legacy.h"

//!
//! \brief    Init Interface
//! \details  Initializes RenderHal Interface structure, responsible for HW
//!           abstraction of HW Rendering Engine for CM(MDF) and VP.
//! \param    PRENDERHAL_INTERFACE_LEGACY pRenderHal
//!           [in] Pointer to RenderHal Interface Structure
//! \param    MhwCpInterface** ppCpInterface
//!           [in/out] Pointer of pointer to MHW CP Interface Structure, which 
//!           is created during renderhal initialization
//! \param    PMOS_INTERFACE pOsInterface
//!           [in] Pointer to OS Interface Structure
//! \return   MOS_STATUS
//!           MOS_STATUS_UNKNOWN : Invalid parameters
//!
MOS_STATUS RenderHal_InitInterface_Legacy(
    PRENDERHAL_INTERFACE_LEGACY pRenderHal,
    MhwCpInterface              **ppCpInterface,
    PMOS_INTERFACE              pOsInterface)
{
    //---------------------------------------
    MHW_RENDERHAL_CHK_NULL_RETURN(pRenderHal);
    MHW_RENDERHAL_CHK_NULL_RETURN(ppCpInterface);
    MHW_RENDERHAL_CHK_NULL_RETURN(pOsInterface);
    //---------------------------------------
    MHW_RENDERHAL_CHK_STATUS_RETURN(RenderHal_InitInterface(pRenderHal, ppCpInterface, pOsInterface));

    // ISA ASM Debug support functions
    pRenderHal->pfnLoadDebugKernel            = RenderHal_LoadDebugKernel;
    pRenderHal->pfnLoadSipKernel              = RenderHal_LoadSipKernel;
    pRenderHal->pfnSendSipStateCmd            = RenderHal_SendSipStateCmd;
    // Tracker tag
    pRenderHal->pfnSetupPrologParams          = RenderHal_SetupPrologParams;
    // Special functions
    RenderHal_InitInterfaceEx_Legacy(pRenderHal);

    return MOS_STATUS_SUCCESS;
}

