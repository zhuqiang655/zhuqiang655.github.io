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
 *          File:  SchM_Det.h
 *        Config:  C:/Vector/CBD1800257_D01_S32K1xx/Applications/S32K144_Start_new/S32K144_Start.dpa
 *    BSW Module:  Det
 *  Generated at:  Mon Jun  7 11:19:42 2021
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1800257
 *
 *   Description:  Header of BSW Scheduler for BSW Module <Det> (Contract Phase)
 *********************************************************************************************************************/
#ifndef SCHM_DET_H
# define SCHM_DET_H

# ifdef __cplusplus
extern "C" {
# endif  /* __cplusplus */

# include "SchM_Det_Type.h"

# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

FUNC(void, RTE_CODE) SchM_Enter_Det_DET_EXCLUSIVE_AREA_0(void);
FUNC(void, RTE_CODE) SchM_Exit_Det_DET_EXCLUSIVE_AREA_0(void);

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# ifdef __cplusplus
} /* extern "C" */
# endif  /* __cplusplus */

#endif /* SCHM_DET_H */
