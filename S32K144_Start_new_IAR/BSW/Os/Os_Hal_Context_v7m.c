/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/**
 *  \addtogroup Os_Hal_Context
 *  \{
 *
 *  \file       Os_Hal_Context_v7m.c
 *  \brief      Context switching primitives for ARMv7-M.
 *  \details
 *  Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
                                                                                                                        /* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#define OS_HAL_CONTEXT_V7M_SOURCE

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

# include "Os_Hal_Context_v7m.h"
/***********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define OS_START_SEC_CODE
#include "Os_MemMap_OsCode.h"                                                                                           /* PRQA S 5087 */ /* MD_MSR_19.1 */


/***********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Os_Hal_ContextSwitch()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(OS_HAL_NOINLINE void,  OS_CODE) Os_Hal_ContextSwitch
(
  P2VAR(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Current,
  P2CONST(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Next
)
{
  /* #10 Suspend Current. */
  Os_Hal_ContextSuspend(Current);                                                                                       /* PRQA S 0306 */ /* MD_Os_Hal_0306 */ /* COV_OS_HALPLATFORMCONTEXTDOWHILE */  /* SBSW_OS_HAL_CONTEXTSUSPEND */ /* SBSW_OS_HAL_CONTEXTSUSPEND */ /* SBSW_OS_HAL_CONTEXTSUSPEND */ /* SBSW_OS_HAL_CONTEXTSUSPEND */ /* SBSW_OS_HAL_CONTEXTSUSPEND */ /* SBSW_OS_HAL_CONTEXTSUSPEND */

  /* #20 Resume Next. */
  Os_Hal_ContextResume(Next, &(Current->Sp));                                                                           /* PRQA S 0306, 3203 */ /* MD_Os_Hal_0306, MD_Os_Hal_3203 */ /* COV_OS_HALPLATFORMCONTEXTDOWHILE */
}


/***********************************************************************************************************************
 *  Os_Hal_ContextCall()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(OS_HAL_NOINLINE void,  OS_CODE) Os_Hal_ContextCall
(
  P2VAR(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Current,
  P2VAR(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Next
)
{
  Os_Hal_ContextSwitchInfoType contextSwitchInfo;                                                                       /* PRQA S 3203 */ /* MD_Os_Hal_3203 */
  uint32 fpcaBit;
  uint32 reservedStackSize;

  /* #10 Suspend Current context. */
  Os_Hal_ContextSuspend(Current);                                                                                       /* PRQA S 0306 */ /* MD_Os_Hal_0306 */ /* COV_OS_HALPLATFORMCONTEXTDOWHILE */ /* SBSW_OS_HAL_CONTEXTSUSPEND */ /* SBSW_OS_HAL_CONTEXTSUSPEND */ /* SBSW_OS_HAL_CONTEXTSUSPEND */ /* SBSW_OS_HAL_CONTEXTSUSPEND */ /* SBSW_OS_HAL_CONTEXTSUSPEND */ /* SBSW_OS_HAL_CONTEXTSUSPEND */

  /* #20 Read if Fpu is active. */
  fpcaBit = Os_Hal_ReadControl() & OS_HAL_CONTROL_FPCA_MASK;

  /* #30 Write the corresponding control register preserving FPCA bit. */
  Os_Hal_WriteControl(Next->Control | fpcaBit);

  /* #40 Compute the exception frame size to be subtracted to the current stack pointer. */
  reservedStackSize = OS_HAL_BASIC_FRAME_SIZE +
      ((fpcaBit >> OS_HAL_CONTROL_FPCA_BIT_INDEX) * OS_HAL_EXTENDED_FRAME_ADDITIONAL_SIZE);

  /* #50 Set up the context switch info with the updated stack pointer. */
  Next->ExcFrame.R1 = Os_Hal_ReadStackPointer() - reservedStackSize;                                                    /* SBSW_OS_HAL_PWA_CALLER */

  contextSwitchInfo.NextSprPtr        = (uint32)(&(Next->Sp));                                                          /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  contextSwitchInfo.PermRegsPtr       = (uint32)(Next->PermanentRegisters);                                             /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  contextSwitchInfo.Basepri           = (uint32)(Next->Basepri);
  contextSwitchInfo.SaveSprPtr        = (uint32)(&(Current->Sp));                                                       /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  contextSwitchInfo.MpuStackRegionPtr = (uint32)(&(Current->StackRegionStart));                                         /* PRQA S 0306 */ /* MD_Os_Hal_0306 */

  /* #60 Perform low level context call. */
  Os_Hal_Trigger_Context_SvCall((uint32)(&contextSwitchInfo));                                                          /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
}                                                                                                                       /* PRQA S 6050 */ /* MD_Os_STCAL */


/***********************************************************************************************************************
 *  Os_Hal_ContextCallOnStack()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(OS_HAL_NOINLINE void,  OS_CODE) Os_Hal_ContextCallOnStack
(
  P2VAR(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Current,
  P2CONST(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Next
)
{
  Os_Hal_ContextSwitchInfoType contextSwitchInfo;                                                                       /* PRQA S 3203 */ /* MD_Os_Hal_3203 */

  /* #10 Suspend Current context. */
  Os_Hal_ContextSuspend(Current);                                                                                       /* PRQA S 0306 */ /* MD_Os_Hal_0306 */ /* COV_OS_HALPLATFORMCONTEXTDOWHILE */ /* SBSW_OS_HAL_CONTEXTSUSPEND */ /* SBSW_OS_HAL_CONTEXTSUSPEND */ /* SBSW_OS_HAL_CONTEXTSUSPEND */ /* SBSW_OS_HAL_CONTEXTSUSPEND */ /* SBSW_OS_HAL_CONTEXTSUSPEND */ /* SBSW_OS_HAL_CONTEXTSUSPEND */

  /* #20 Switch to Next with stack switch. */
  Os_Hal_WriteControl(Next->Control | (Os_Hal_ReadControl() & OS_HAL_CONTROL_FPCA_MASK));

  contextSwitchInfo.NextSprPtr        = (uint32)(&(Next->Sp));                                                          /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  contextSwitchInfo.PermRegsPtr       = (uint32)(Next->PermanentRegisters);                                             /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  contextSwitchInfo.Basepri           = (uint32)(Next->Basepri);
  contextSwitchInfo.SaveSprPtr        = (uint32)(&(Current->Sp));                                                       /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  contextSwitchInfo.MpuStackRegionPtr = (uint32)(&(Next->StackRegionStart));                                            /* PRQA S 0306 */ /* MD_Os_Hal_0306 */

  Os_Hal_Trigger_Context_SvCall((uint32)(&contextSwitchInfo));                                                          /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
}


#define OS_STOP_SEC_CODE
#include "Os_MemMap_OsCode.h"                                                                                           /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Context_v7m.c
 **********************************************************************************************************************/
