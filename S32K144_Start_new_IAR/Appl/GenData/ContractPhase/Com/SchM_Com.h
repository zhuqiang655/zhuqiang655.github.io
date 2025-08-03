/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_Com.h
 *        Config:  C:/Vector/CBD1800257_D01_S32K1xx/Applications/S32K144_Start_new/S32K144_Start.dpa
 *    BSW Module:  Com
 *  Generated at:  Mon Jun  7 11:19:41 2021
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1800257
 *
 *   Description:  Header of BSW Scheduler for BSW Module <Com> (Contract Phase)
 *********************************************************************************************************************/
#ifndef SCHM_COM_H
# define SCHM_COM_H

# ifdef __cplusplus
extern "C" {
# endif  /* __cplusplus */

# include "SchM_Com_Type.h"

# define COM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

FUNC(void, COM_CODE) Com_MainFunctionRx(void); /* PRQA S 3451 */ /* MD_Rte_3451 */
FUNC(void, COM_CODE) Com_MainFunctionTx(void); /* PRQA S 3451 */ /* MD_Rte_3451 */

# define COM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

FUNC(void, RTE_CODE) SchM_Enter_Com_COM_EXCLUSIVE_AREA_BOTH(void);
FUNC(void, RTE_CODE) SchM_Exit_Com_COM_EXCLUSIVE_AREA_BOTH(void);
FUNC(void, RTE_CODE) SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX(void);
FUNC(void, RTE_CODE) SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX(void);
FUNC(void, RTE_CODE) SchM_Enter_Com_COM_EXCLUSIVE_AREA_TX(void);
FUNC(void, RTE_CODE) SchM_Exit_Com_COM_EXCLUSIVE_AREA_TX(void);

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# ifdef __cplusplus
} /* extern "C" */
# endif  /* __cplusplus */

#endif /* SCHM_COM_H */

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_3451:  MISRA rule: 8.8
     Reason:     Schedulable entities are declared by the RTE and also by the BSW modules.
     Risk:       No functional risk.
     Prevention: Not required.

*/
