/******************************************************************************
** File:  cfe_psp_support.c
**
**
**      Copyright (c) 2004-2006, United States government as represented by the
**      administrator of the National Aeronautics Space Administration.
**      All rights reserved. This software(cFE) was created at NASA Goddard
**      Space Flight Center pursuant to government contracts.
**
**      This software may be used only pursuant to a United States government
**      sponsored project and the United States government may not be charged
**      for use thereof.
**
**

** Purpose:
**   This file contains glue routines between the cFE and the OS Board Support Package ( BSP ).
**   The functions here allow the cFE to interface functions that are board and OS specific
**   and usually dont fit well in the OS abstraction layer.
**
** History:
**  $ Log: cfe_psp_support.c $
**
******************************************************************************/

/*
**  Include Files
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/*
** cFE includes
*/
#include "common_types.h"
#include "osapi.h"
#include "cfe_es.h"            /* For reset types */
#include "cfe_platform_cfg.h"  /* for processor ID */
#include "cfe_mission_cfg.h"   /* for spacecraft ID */

/*
** Types and prototypes for this module
*/
#include "cfe_psp.h"
#include "cfe_psp_private.h"

/*
** External Variables
*/
extern CFE_PSP_GlobalData_t CFE_PSP_GlobalData;


/******************************************************************************
**  Function:  CFE_PSP_Restart()
**
**  Purpose:
**    Provides a common interface to the processor reset.
**
**  Arguments:
**    reset_type  : Type of reset.
**
**  Return:
**    (none)
*/

void CFE_PSP_Restart(uint32 reset_type)
{

   if ( reset_type == CFE_ES_POWERON_RESET )
   {
       OS_printf("CFE_PSP: Exiting cFE with POWERON Reset status.\n");
       OS_printf("CFE_PSP: Start the cFE Core with the PO parameter to complete the Power On Reset\n");
       OS_printf("CFE_PSP: When the Power On Reset is completed, the Shared Memroy segments will be CLEARED\n");
       exit(CFE_ES_POWERON_RESET);
   }
   else
   {
       OS_printf("CFE_PSP: Exiting cFE with PROCESSOR Reset status.\n");
       OS_printf("CFE_PSP: Shared Memory segments have been PRESERVED.\n");
       OS_printf("CFE_PSP: Restart the cFE with the PR parameter to complete the Processor Reset.\n");
       exit(CFE_ES_PROCESSOR_RESET);
   }

}

/******************************************************************************
**  Function:  CFE_PSP_Panic()
**
**  Purpose:
**    Provides a common interface to abort the cFE startup process and return
**    back to the OS.
**
**  Arguments:
**    ErrorCode  : Reason for Exiting.
**
**  Return:
**    (none)
*/

void CFE_PSP_Panic(int32 ErrorCode)
{
   OS_printf("CFE_PSP_Panic Called with error code = 0x%08X. Exiting.\n",(unsigned int)ErrorCode);
   OS_printf("The cFE could not start.\n");
   exit(-1);
}


/******************************************************************************
**  Function:  CFE_PSP_FlushCaches)
**
**  Purpose:
**    Provides a common interface to flush the processor caches. This routine
**    is in the BSP because it is sometimes implemented in hardware and
**    sometimes taken care of by the RTOS.
**
**  Arguments:
**
**  Return:
**    (none)
*/
void CFE_PSP_FlushCaches(uint32 type, uint32 address, uint32 size)
{
   printf("CFE_PSP_FlushCaches called -- Currently no Linux/OSX/Cygwin implementation\n");
}

/*
** Name: CFE_PSP_GetProcessorId
**
** Purpose:
**         return the processor ID.
**
**
** Parameters:
**
** Global Inputs: None
**
** Global Outputs: None
**
**
**
** Return Values: Processor ID
*/
uint32 CFE_PSP_GetProcessorId    (void)
{
    return(CFE_PSP_GlobalData.CFE_PSP_CpuId);
}


/*
** Name: CFE_PSP_GetSpacecraftId
**
** Purpose:
**         return the spacecraft ID.
**
** Parameters:
**
** Global Inputs: None
**
** Global Outputs: None
**
**
** Return Values: Spacecraft ID
*/
uint32 CFE_PSP_GetSpacecraftId   (void)
{
   return(CFE_PSP_GlobalData.CFE_PSP_SpacecraftId);
}
