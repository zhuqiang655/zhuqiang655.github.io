/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                                   All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/**
 * \addtogroup  Os_Hal_Derivative
 * \{
 *
 * \file
 * \brief  This file contains derivative specific coverage justifications.
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#if !defined (OS_HAL_COVERAGE_IMX8XINT_H)                                                                               /* PRQA S 0883 */ /* MD_Os_0883 */
# define OS_HAL_COVERAGE_IMX8XINT_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */

/* Os module declarations */

/* Os kernel module dependencies */

/* Os hal dependencies */

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/* START_COVERAGE_JUSTIFICATION

Justifications for core:

\ID COV_OS_HALPLATFORMMULTICOREUNSUPPORTED
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XX
  \REASON This coverage token is never reached on a single-core derivative.
          However, the passage is tested on multicore OS.

\ID COV_OS_HALPLATFORMTESTEDASMULTICORE
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XX
  \REASON This coverage token is currently not reached on a single-core derivative.
          This is due to missing tests of very unlikely execution paths in singlecore OS.
          However, the passage is tested on multicore OS, where the execution paths are more likely.

\ID COV_OS_HALPLATFORMNEEDMORETHAN2CORES
  \ACCEPT XX
  \REASON This coverage token is never reached on a single-core derivative.

\ID COV_OS_HALPLATFORMMASTERSTARTALLOWED
  \ACCEPT XX
  \REASON This coverage token is never reached on a single-core derivative.

\ID COV_OS_HALPLATFORMNONAUTOSTARTCORE
  \ACCEPT XX
  \REASON This coverage token is never reached on a single-core derivative.

\ID COV_OS_HALPLATFORMGETSPINLOCK
  \ACCEPT XF
  \REASON Though this code may be reached, it is impossible to have a reliable test with only 1 core to cover this
          branch. Thus this is not covered a single-core derivative. However, the correctness can be proved
          by code review and unit test.

\ID COV_OS_HALPLATFORMCONTEXTDOWHILE
  \ACCEPT XF
  \REASON This macro definition uses a "do while(0)". Thus the "true" branch can never be covered.

\ID COV_OS_HALPLATFORMCONTEXTDOWHILENORETURN
  \ACCEPT XX
  \REASON This macro definition uses a "do while(0)". Since the last statement in the loop body will never return, the
          "while" condition can never be checked. However, because the caller is always executed and there is no
          branches, 100% statement coverage can be ensured.

\ID COV_OS_HALPLATFORMPERIPHERALINTTRIGGERSUPPORTED
  \ACCEPT TX
  \REASON This platform always support peripheral interrupt software trigger.

\ID COV_OS_HALPLATFORMFRTUNSUPPORTED_XX
  \ACCEPT XX
  \REASON Timer type FRT is not available on this derivative. Functionality has been tested on another derivative.

\ID COV_OS_HALPLATFORMPFRTUNSUPPORTED_XX
  \ACCEPT XX
  \REASON Timer type PFRT is not available on this derivative. Functionality has been tested on another derivative.

\ID COV_OS_HALPLATFORMTPUNSUPPORTED_XX
  \ACCEPT XX
  \REASON This derivative does not meet the hardware requirements to support timing protection.
          Functionality has been tested on another derivative.

\ID COV_OS_HALPLATFORMTPUNSUPPORTED_TX
  \ACCEPT TX
  \REASON This derivative does not meet the hardware requirements to support timing protection.
          Functionality has been tested on another derivative.

\ID COV_OS_HALPLATFORMTPUNSUPPORTED_XF
  \ACCEPT XF
  \REASON This derivative does not meet the hardware requirements to support timing protection.
          Functionality has been tested on another derivative.

\ID COV_OS_HALPLATFORMLEVELSUPPORT
  \ACCEPT TX
  \REASON This derivative does support interrupt level switching.


END_COVERAGE_JUSTIFICATION */

#endif /* OS_HAL_COVERAGE_IMX8XINT_H */

/*!
 * \}
 */
/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Coverage_IMX8xInt.h
 **********************************************************************************************************************/
