/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 120 */

/* STARTSINGLE_OF_MULTIPLE */

/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/** \file     Can.c / Can_Local.h
 *  \brief    Implementation of the CAN driver
 *  \details  see functional description below
 *
 *********************************************************************************************************************/
/* ***************************************************************************
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| Ht           Heike Honert              Vector Informatik GmbH
| Ml           Patrick Markl             Vector Informatik GmbH
| Bir          Holger Birke              Vector Informatik GmbH
| Rse          Robert Schelkle           Vector Informatik GmbH
| Was          Andreas Weinrauch         Vector Informatik GmbH
| Zam          Artjom Zabirko            Vector Informatik GmbH
| Pl           Georg Pfluegel            Vector Informatik GmbH
| Rli          Roman Linder              Vector Informatik GmbH
| Bns          Benjamin Schuetterle      Vector Informatik GmbH
| Gaz          Carsten Gauglitz          Vector Informatik GmbH
| Yoe          Yacine Ouldboukhitine     Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 2012-01-09  1.00.00  Rse    - ESCAN00056163: Initial version: Hll - Flexcan3 - Imx6 - QCC - High-End - QNX
| 2012-09-20  1.01.00  Rse    - ESCAN00062414: Support workaround for erratum ERR005829
| 2013-01-30  1.02.00  Rse    - ESCAN00065347: Support platform MPC5700
|                             - ESCAN00064665: CANbedded only: CAN messages will not be sent any more
|                             - ESCAN00066667: Support workaround for erratum e5769
|                             - ESCAN00067035: Inconsistent combination of receive handle and receive information (id, dlc, data) is indicated to upper layer
| 2013-05-21  1.03.00  Rse    - ESCAN00067478: Support FlexCAN2 derivatives for RxFifo usage
|                             - ESCAN00067660: Support the feature Mirror Mode
| 2013-07-22  1.04.00  Rse    - ESCAN00069229: Support CAN message retransmit feature for FBL driver
|                             - ESCAN00070121: Support Vybrid with FlexCAN3
| 2013-11-21  1.05.00  Rse    - ESCAN00072129: ASR4 only: change BusOff behavior to ensure recovery time of 128x11 recessive bits
|                             - ESCAN00072322: AR4-328: Predefined Runtime Measurement Points
| 2013-12-09  1.06.00  Rse    - ESCAN00072515: AutoSar only: Can_SetControllerMode(controller, CAN_T_STOP) returns CAN_OK instead of CAN_NOT_OK
|                             - ESCAN00072597: CANbedded only: Retransmit does not work if more than 22 RxFullCAN objects are used
| 2014-01-08  1.07.00  Rse    - ESCAN00072828: CANbedded only: Compiler error: identifier "canCanInterruptCounter" is undefined
|                             - ESCAN00072863: Support Cancel in Hardware with Transmission Abort feature
|                             - ESCAN00072869: Support new interface for Bus Mirroring
| 2014-01-30  1.07.01  Rse    - ESCAN00073299: Parity check only available for Vybrid and MPC5700 derivatives
| 2014-02-06  1.07.02  Rse    - Some minor MISRA improvements
|                      Rse    - ESCAN00073889: CANbedded only: Compiler error: struct has unknown field
| 2014-03-24  1.07.03  Rse    - ESCAN00074424: Indication function is called twice for the reception of one BasicCAN message
| 2014-04-16  1.08.00  Rse    - ESCAN00075110: BusOff notification is called twice for one single BusOff event (FlexCAN2)
|                             - ESCAN00075955: Remove obsolete workaround implementation for e5769
|                             - ESCAN00075964: Delete unnecessary interrupt locks
|                             - ESCAN00075507: IAR Compiler warning: the order of volatile accesses is undefined
| 2014-06-24  1.09.00  Rse    - ESCAN00076588: CAN clock settings are invalid after reinitialization, error frames occur continuously on the bus
|                             - ESCAN00076653: Implement proper mode switch to init (FREEZE) mode in CAN controller initialization process
|                             - ESCAN00076657: MAXMB value is obsolete
|                             - ESCAN00077049: CANbedded only: Support Tx FullCAN Send Delay (External PIA)
|                             - ESCAN00077083: CANbedded only: LowLevel Message is not transmitted
|                             - ESCAN00077485: OS Exception when CAN driver is handled in User Mode
| 2014-08-13  1.10.00  Rse    - ESCAN00077825: Support derivative MPC5748G CUT2
| 2014-11-10  1.10.01  Rse    - ESCAN00079385: Compiler warning: argument of type "volatile uint32 *" is incompatible with parameter of type "volatile uint16 *"
| 2014-11-27  2.00.00  Rse    - ESCAN00078072: Support full functionality for CAN-FD (Mode 2)
|                             - ESCAN00079900: CANbedded only: Extended ID message with dominant SRR-Bit does not receive
|                             - ESCAN00079901: Support ComStackLib tables for ASR403 R11
|                             - ESCAN00079494: Add loop checks for mode switching in CAN Controller initialization process
| 2015-01-21  2.00.01  Rse    - ESCAN00080716: Standard CAN message is sent as CAN-FD message with baudrate switch
| 2015-04-09  2.00.02  Was    - ESCAN00082335: Update to Core 5.00.02, R11 (Vybrid)
| 2015-05-02  2.01.00  Rse    - ESCAN00082800: Support CANbedded compatibility
| 2015-09-02  2.02.00  Zam    - ESCAN00084930: Support Extended CAN RAM Check feature
| 2015-10-14  2.03.00  Pl     - ESCAN00085860: Support S32K with FlexCAN3
| 2015-12-03  3.00.00  Rse    - ESCAN00086974: Support R14 and process 3.0
| 2016-03-17  3.01.00  Rse    - ESCAN00088969: Support Extended RAM check for MSR403
| 2016-05-30  3.01.01  Rse    - ESCAN00090210: Compiler error: parse error near ';'
| 2016-06-20  3.01.02  Rse    - Update HL-ASR 5.04.01 for issue 89754
| 2016-08-03  3.01.03  Rse    - ESCAN00091088: Callback that indicates corrupt CAN Controller is called erroneously
| 2016-08-25  3.02.00  Rse    - ESCAN00091626: Support R14 for Arm32 platforms
|                             - ESCAN00092139: Support ISO CAN-FD
|                             - ESCAN00092218: Support possibility to use a non-CAN-FD baudrate on a CAN-FD channel
|                             - ESCAN00092333: Support asymmetric mailboxes
| 2016-10-26  3.02.01  Rse    - ESCAN00092531: Linker Error: undefined symbol found 'Can_GetCanNumberOfMaxMailboxes'
| 2016-12-12  3.02.02  Rli    - ESCAN00093255: CAN FD FULL support for Little Endian Architectures
| 2017-03-30  3.02.03  Rli    - ESCAN00094552: Compiler error: identifier Controller not declared
|                             - ESCAN00094764: MWCT101xS Support
| 2017-04-21  3.03.00  Rli    - ESCAN00094816: Support of Virtual Addressing
| 2017-09-05  3.03.03  Rli    - ESCAN00096527 Compiler warning: unused argument
| 2017-10-31  5.00.00  Rli    - ESCAN00097302 Support of SafeBSW for FlexCAN3
| 2018-03-08  5.00.01  Bns    - Update HL-ASR 5.07.02 for issue 96367
|                             - ESCAN00098678 Support Extended RAM Check for S32 
| 2018-03-12  5.01.00  Gaz    - ESCAN00098459 Update to Core 6.00.00
| 2018-06-19  5.02.00  Rli    - ESCAN00099727 Support of Virtual Addressing with CAN FD Mode 2
| 2018-08-02  5.03.00  Rli    - STORYC-6186: Support Silent Mode
|                             - ESCAN00100316 IMX8: Messages not received with CAN FD configuration
| 2018-10-19  5.04.00  Yoe    - STORYC-6683: Support SafeBsw for Asymmetric Mailboxes
| 2018-10-31  5.04.01  Yoe    - STORYC-6877: Support SafeBsw for S32k1xx derivatives
| 2018-11-22  5.04.02  Rli    - STORYC-7138: Update code due to Cfg5 bugfix
|************************************************************************** */

#if !defined(CAN_LOCAL_H)
#define  CAN_LOCAL_H

/***************************************************************************/
/* Include                                                                 */
/***************************************************************************/
#include "Can.h"         /* include also all needed types */
/* \trace SPEC-1583 */
#include "SchM_Can.h"

/***************************************************************************/
/* Version Check                                                           */
/***************************************************************************/
/* \trace SPEC-20329 */
/* not the SW version but all file versions that represent the SW version are checked */
#if (CAN_COREVERSION           != 0x0600u) /* \trace SPEC-1699, SPEC-3837 */
# error "Header file are inconsistent!"
#endif
#if (CAN_RELEASE_COREVERSION   != 0x00u)
# error "Header file are inconsistent!"
#endif
#if( DRVCAN_IMXFLEXCAN3ASR_VERSION != 0x0504)
 #error "Source and Header file are inconsistent!"
#endif

#if( DRVCAN_IMXFLEXCAN3ASR_RELEASE_VERSION != 0x02)
 #error "Source and Header file are inconsistent!"
#endif

#if( CAN_GEN_ImxFlexcan3Asr_VERSION != 0x0101)
# error "Generated Data are inconsistent!"
#endif

/***************************************************************************/
/* compatibility defines                                                   */
/***************************************************************************/
#define C_ENABLE_COPY_TX_DATA

#if defined(C_ENABLE_MIXED_ID) || defined(C_ENABLE_EXTENDED_ID)
# define CAN_ID_IDE_MASK            0x80000000UL
# define CAN_ID_FD_MASK             0x40000000UL /* \trace SPEC-50553 */
# define CAN_ID_MASK                0x1FFFFFFFUL
# define CAN_ID_MASK_STD            0x000007FFUL
# define CAN_ID_UNUSED_MASK         0x20000000UL
#else
# define CAN_ID_IDE_MASK            0x0000U
# define CAN_ID_FD_MASK             0x4000U /* \trace SPEC-50553 */
# define CAN_ID_MASK                0x07FFU
# define CAN_ID_MASK_STD            0x07FFU
# define CAN_ID_UNUSED_MASK         0x3800U
#endif
#define kCanAllChannels             ((CanChannelHandle)0xFFU)

#if !defined(C_DRV_INTERNAL) /* COV_CAN_INTERNAL */
# error "Can_Local.h should only be included by Can.c"
#endif
#if defined(kCanNumberOfChannels) /* COV_CAN_COMPATIBILITY */
# undef kCanNumberOfChannels /* may happen for MultiDirverInstance */ /* PRQA S 0841 */ /* MD_Can_0841 */
#endif
/* real amount of controllers in this system (LT and PB) */
#define kCanNumberOfChannels Can_GetControllerMax()
/* if kCanNumberOfChannels used to declare a table/dimension this table has to be generated to be also Link-Time-capable */
/*  -> see ESCAN00028069 controller-amount has to be Link-Time-capable */
#if defined(kCanNumberOfHwChannels) /* COV_CAN_COMPATIBILITY */
# undef kCanNumberOfHwChannels /* may happen for MultiDirverInstance */ /* PRQA S 0841 */ /* MD_Can_0841 */
#endif
/* compatibility to common-can drivers */
/* real amount of controllers in this system (LT and PB) */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COM_STACK_LIB */ /* COV_CAN_MICROSAR_VERSION */
#  define kCanNumberOfHwChannels kCanNumberOfChannels
#else
# if ( CAN_COMMON_CAN == STD_ON )
#  define kCanNumberOfHwChannels CAN_GLOBAL_CONFIG(CanHwChannelMax)
# else
#  define kCanNumberOfHwChannels CAN_GLOBAL_CONFIG(CanControllerMax)
# endif
#endif

#if defined( C_SINGLE_RECEIVE_CHANNEL )
/* have to be done here to avoid declaration of "channel" in Can.h */
# define channel                                ((CanChannelHandle)0)
# define canHwChannel                           ((CanChannelHandle)0)
# define CAN_HL_HW_CHANNEL_STARTINDEX(ch)       ((CanChannelHandle)0)
# define CAN_HL_HW_CHANNEL_STOPINDEX(ch)        ((CanChannelHandle)0)
#else
# define channel                                Controller
#  define canHwChannel                          Controller
#  define CAN_HL_HW_CHANNEL_STARTINDEX(ch)      (ch)
#  define CAN_HL_HW_CHANNEL_STOPINDEX(ch)       (ch)
#endif

#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
# if !defined(CAN_EMULATE_SLEEP) /* COV_CAN_COMPATIBILITY */
#  define CAN_EMULATE_SLEEP STD_ON /* always on for AutoSar4 */
# endif
# if !defined(CAN_TRANSITION_CHECK) /* COV_CAN_COMPATIBILITY */
#  define CAN_TRANSITION_CHECK STD_ON /* default may be deactivated by user configuration */
# endif
#else
# if !defined(CAN_EMULATE_SLEEP) /* COV_CAN_COMPATIBILITY */
#  define CAN_EMULATE_SLEEP STD_OFF
# endif
# if !defined(CAN_TRANSITION_CHECK) /* COV_CAN_COMPATIBILITY */
#  define CAN_TRANSITION_CHECK STD_OFF
# endif
#endif
#if !defined(CAN_REINIT_START) /* COV_CAN_COMPATIBILITY */
# define CAN_REINIT_START STD_OFF
#endif

#if !defined(CAN_OS_TICK2MS) /* COV_CAN_COMPATIBILITY */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
#  error "CAN_OS_TICK2MS() should be defined to OS_TICKS2MS_<counterShortName>() macro from OS"
# endif
# define CAN_OS_TICK2MS(tick) (tick) /* used direct by 401 implementation */
#endif
#if !defined(CAN_OS_COUNTER_ID) /* COV_CAN_COMPATIBILITY */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
#  error "CAN_OS_COUNTER_ID should be defined to 'counterShortName' from OS"
# endif
# define CAN_OS_COUNTER_ID CanTimeoutDurationCounterId /* used direct by 401 implementation */
#endif

#if !defined(CAN_RX_BASICCAN_TYPE) /* compatibility Cfg5 to GENy */ /* COV_CAN_COMPATIBILITY */
# define CAN_RX_BASICCAN_TYPE    RxBasicCANType
# define CAN_RX_FULLCAN_TYPE     RxFullCANType
# define CAN_TX_BASICCAN_TYPE    TxBasicCANType
# define CAN_TX_FULLCAN_TYPE     TxFullCANType
# define CAN_UNUSED_CAN_TYPE     UnusedCANType
#endif
#if !defined(CAN_TX_BASICCAN_MUX_TYPE) /* COV_CAN_COMPATIBILITY */
# define CAN_TX_BASICCAN_MUX_TYPE   TxBasicCANType /* not supported in GENy for now */
#endif

#if !defined(CAN_ID_MASK_IN_GENERIC_CALLOUT) /* COV_CAN_COMPATIBILITY */
# define CAN_ID_MASK_IN_GENERIC_CALLOUT (CAN_ID_IDE_MASK | CAN_ID_FD_MASK | CAN_ID_MASK)
/* May be changed to mask out FD-bit: (CAN_ID_IDE_MASK | CAN_ID_MASK) */
#endif

# if (CAN_MICROSAR_VERSION == CAN_MSR403) /* COV_CAN_COMPATIBILITY */
#  if !defined( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT ) && !defined( C_DISABLE_BUSOFF_RECOVERY_COMPLIANT )
#   define C_ENABLE_BUSOFF_RECOVERY_COMPLIANT
#  endif
# endif
# if defined ( CAN_PROTECTED_MODE ) /* COV_CAN_INTERNAL */
#  if ( CAN_PROTECTED_MODE == STD_ON )
#   define C_ENABLE_USER_MODE_OS
#  endif
# endif

/***************************************************************************/
/* Defines                                                                 */
/***************************************************************************/
/* for variable Can_ActiveSendState */
#define CAN_FREE_OBJ                (uint8)0xFF     /* mark objects as free */
#define kCanBufferFree              CAN_FREE_OBJ    /* compatibility for cancel in HW task */
#define CAN_CANCEL_OBJ              (uint8)0xFE     /* mark object as currently cancelling */
#define kCanBufferCancel            CAN_CANCEL_OBJ  /* compatibility for LL cancel interrupt / task */
#define CAN_CANCEL_OBJ_SW           (uint8)0xFD
#define CAN_SEND_OBJ                (uint8)0x01     /* occupied send object */

#if defined(C_ENABLE_CAN_RAM_CHECK)
/* for variable Can_MailboxState */
# define CAN_ENABLE_OBJ             (uint8)0x00     /* enabled mailbox */
# define CAN_DISABLED_OBJ           (uint8)0x01     /* disabled mailbox */
#endif

/* general return values */
#define kCanFailed                  CAN_NOT_OK
#define kCanOk                      CAN_OK
#define kCanNotSupported            CAN_NOT_SUPPORTED
#define kCanRequested               CAN_REQUESTED

#define kCanTrue                    0x01
#define kCanFalse                   0x00

#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COM_STACK_LIB */ /* COV_CAN_MICROSAR_VERSION */
# define Can_GetControllerMax()                         Can_GetSizeOfControllerData()

# define Can_GetCanControllerDefaultBaudrate(Index)     Can_GetCanControllerDefaultBaudrateOfControllerConfig(Index)
# define Can_GetCanControllerDefaultBaudrateIdx(Index)  Can_GetCanControllerDefaultBaudrateIdxOfControllerConfig(Index)
# if !defined(Can_GetMailboxRxBasicLengthOfControllerConfig) /* If no Object is available ComStackLib do not generate start-stop index */
#  define Can_GetMailboxRxBasicLengthOfControllerConfig(Index) 0
#  define Can_GetMailboxRxBasicStartIdxOfControllerConfig(Index) 0
#  define Can_GetMailboxRxBasicEndIdxOfControllerConfig(Index) 0
# endif
# define Can_GetRxBasicHandleMax(Index)                 Can_GetMailboxRxBasicLengthOfControllerConfig(Index)
# define Can_GetRxBasicHandleStart(Index)               (Can_HwHandleType)Can_GetMailboxRxBasicStartIdxOfControllerConfig(Index)
# define Can_GetRxBasicHandleStop(Index)                (Can_HwHandleType)Can_GetMailboxRxBasicEndIdxOfControllerConfig(Index)
# define Can_GetRxBasicHwStart(Index)                   Can_GetRxBasicHwStartOfControllerConfig(Index)
# define Can_GetRxBasicHwStop(Index)                    Can_GetRxBasicHwStopOfControllerConfig(Index)
# if !defined(Can_GetMailboxRxFullLengthOfControllerConfig)
#  define Can_GetMailboxRxFullLengthOfControllerConfig(Index) 0
#  define Can_GetMailboxRxFullStartIdxOfControllerConfig(Index) 0
#  define Can_GetMailboxRxFullEndIdxOfControllerConfig(Index) 0
# endif
# define Can_GetRxFullHandleMax(Index)                  Can_GetMailboxRxFullLengthOfControllerConfig(Index)
# define Can_GetRxFullHandleStart(Index)                (Can_HwHandleType)Can_GetMailboxRxFullStartIdxOfControllerConfig(Index)
# define Can_GetRxFullHandleStop(Index)                 (Can_HwHandleType)Can_GetMailboxRxFullEndIdxOfControllerConfig(Index)
# define Can_GetRxFullHwStart(Index)                    Can_GetRxFullHwStartOfControllerConfig(Index)
# define Can_GetRxFullHwStop(Index)                     Can_GetRxFullHwStopOfControllerConfig(Index)
# if !defined(Can_GetMailboxTxBasicLengthOfControllerConfig) /* COV_CAN_GENDATA_FAILURE */
#  define Can_GetMailboxTxBasicLengthOfControllerConfig(Index) 0
#  define Can_GetMailboxTxBasicStartIdxOfControllerConfig(Index) 0
#  define Can_GetMailboxTxBasicEndIdxOfControllerConfig(Index) 0
# endif
# define Can_GetTxBasicHandleMax(Index)                 Can_GetMailboxTxBasicLengthOfControllerConfig(Index)
# define Can_GetTxBasicHandleStart(Index)               (Can_HwHandleType)Can_GetMailboxTxBasicStartIdxOfControllerConfig(Index)
# define Can_GetTxBasicHandleStop(Index)                (Can_HwHandleType)Can_GetMailboxTxBasicEndIdxOfControllerConfig(Index)
# define Can_GetTxBasicHwStart(Index)                   Can_GetTxBasicHwStartOfControllerConfig(Index)
# define Can_GetTxBasicHwStop(Index)                    Can_GetTxBasicHwStopOfControllerConfig(Index)
# if !defined(Can_GetMailboxTxFullLengthOfControllerConfig)
#  define Can_GetMailboxTxFullLengthOfControllerConfig(Index) 0
#  define Can_GetMailboxTxFullStartIdxOfControllerConfig(Index) 0
#  define Can_GetMailboxTxFullEndIdxOfControllerConfig(Index) 0
# endif
# define Can_GetTxFullHandleMax(Index)                  Can_GetMailboxTxFullLengthOfControllerConfig(Index)
# define Can_GetTxFullHandleStart(Index)                (Can_HwHandleType)Can_GetMailboxTxFullStartIdxOfControllerConfig(Index)
# define Can_GetTxFullHandleStop(Index)                 (Can_HwHandleType)Can_GetMailboxTxFullEndIdxOfControllerConfig(Index)
# define Can_GetTxFullHwStart(Index)                    Can_GetTxFullHwStartOfControllerConfig(Index)
# define Can_GetTxFullHwStop(Index)                     Can_GetTxFullHwStopOfControllerConfig(Index)
# if !defined(Can_GetMailboxUnusedLengthOfControllerConfig)  /* COV_CAN_GENDATA_FAILURE */
#  define Can_GetMailboxUnusedLengthOfControllerConfig(Index) 0
#  define Can_GetMailboxUnusedStartIdxOfControllerConfig(Index) 0
#  define Can_GetMailboxUnusedEndIdxOfControllerConfig(Index) 0
# endif
# define Can_GetUnusedHandleMax(Index)                  Can_GetMailboxUnusedLengthOfControllerConfig(Index)
# define Can_GetUnusedHandleStart(Index)                (Can_HwHandleType)Can_GetMailboxUnusedStartIdxOfControllerConfig(Index)
# define Can_GetUnusedHandleStop(Index)                 (Can_HwHandleType)Can_GetMailboxUnusedEndIdxOfControllerConfig(Index)
# define Can_GetUnusedHwStart(Index)                    Can_GetUnusedHwStartOfControllerConfig(Index)
# define Can_GetUnusedHwStop(Index)                     Can_GetUnusedHwStopOfControllerConfig(Index)

# define Can_GetDLC_FIFO(Index)                         Can_GetDLC_FIFOOfMailbox(Index)
# define Can_GetHwHandle(Index)                         Can_GetHwHandleOfMailbox(Index)
# define Can_GetIDValue(Index)                          Can_GetIDValueOfMailbox(Index)
# define Can_GetMailboxType(Index)                      Can_GetMailboxTypeOfMailbox(Index)
# define Can_GetMailboxDataLen(Index)                   Can_GetMaxDataLenOfMailbox(Index)
# define Can_GetMailboxFdPadding(Index)                 Can_GetFdPaddingOfMailbox(Index)
# define Can_GetMailboxController(Index)                (CanChannelHandle)Can_GetControllerConfigIdxOfMailbox(Index)

# if defined(CAN_HWOBJINDIVPOLLINGSTART)
#  define Can_GetCanHwObjIndivPolling(ch,Index)          Can_GetHwObjIndivPolling((Can_GetHwObjIndivPollingStart(ch))+(Index))
# else
#  define Can_GetCanHwObjIndivPolling(ch,Index)          Can_GetHwObjIndivPolling((Index))
# endif

# define Can_GetCanToCanIfChannelMapping(Index)          Can_GetCanIfChannelId((Index))

/* VAR */
# define Can_GetLastInitObject(Index)                   Can_GetLastInitObjectOfControllerData(Index)
# define Can_SetLastInitObject(Index,Value)             Can_SetLastInitObjectOfControllerData(Index,Value)
# define Can_GetCanInterruptOldStatus(Index)            Can_GetCanInterruptOldStatusOfControllerData(Index)
# define Can_SetCanInterruptOldStatus(Index,Value)      Can_SetCanInterruptOldStatusOfControllerData(Index,Value)
# define Can_GetCanInterruptCounter(Index)              Can_GetCanInterruptCounterOfControllerData(Index)
# define Can_SetCanInterruptCounter(Index,Value)        Can_SetCanInterruptCounterOfControllerData(Index,Value)
# define Can_IsIsWakeup(Index)                          Can_IsIsWakeupOfControllerData(Index)
# define Can_SetIsWakeup(Index,Value)                   Can_SetIsWakeupOfControllerData(Index,Value)
# define Can_IsIsBusOff(Index)                          Can_IsIsBusOffOfControllerData(Index)
# define Can_SetIsBusOff(Index,Value)                   Can_SetIsBusOffOfControllerData(Index,Value)
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# define Can_GetBusOffCounter(Index)                    Can_GetBusOffCounterOfControllerData(Index)
# define Can_SetBusOffCounter(Index,Value)              Can_SetBusOffCounterOfControllerData(Index,Value)
# define Can_DecBusOffCounter(Index)                    Can_DecBusOffCounterOfControllerData(Index)
#endif
# define Can_GetStatusReq(Index)                        Can_GetStatusReqOfControllerData(Index)
# define Can_SetStatusReq(Index,Value)                  Can_SetStatusReqOfControllerData(Index,Value)
# define Can_GetLogStatus(Index)                        Can_GetLogStatusOfControllerData(Index)
# define Can_SetLogStatus(Index,Value)                  Can_SetLogStatusOfControllerData(Index,Value)
# define Can_GetCanLoopTimeout(ch, Index)               (Can_GetLoopTimeoutOfControllerData(ch))[(Index)]
# define Can_IsIsHardwareCanceled(Index)                Can_IsIsHardwareCanceledOfControllerData(Index)
# define Can_SetIsHardwareCanceled(Index,Value)         Can_SetIsHardwareCanceledOfControllerData(Index,Value)
# define Can_GetMirrorModeState(Index)                  Can_GetMirrorModeStateOfControllerData(Index)
# define Can_SetMirrorModeState(Index,Value)            Can_SetMirrorModeStateOfControllerData(Index,Value)
# define Can_GetSilentModeState(Index)                  Can_GetSilentModeStateOfControllerData(Index)
# define Can_SetSilentModeState(Index,Value)            Can_SetSilentModeStateOfControllerData(Index,Value)

# define Can_GetCanTxBasicDataBuffer(ch,muxTx)          (Can_GetTxBasicDataBuffer(ch))[(muxTx)]

# define Can_GetActiveSendPdu(Index)                    Can_GetPduOfActiveSendObject(Index)
# define Can_SetActiveSendPdu(Index,Value)              Can_SetPduOfActiveSendObject(Index,Value)
# define Can_GetActiveSendState(Index)                  Can_GetStateOfActiveSendObject(Index)
# define Can_SetActiveSendState(Index,Value)            Can_SetStateOfActiveSendObject(Index,Value)
# define Can_GetActiveSendPduInfo(Index)                Can_GetPduInfoOfActiveSendObject(Index)
# define Can_GetActiveSendId(Index)                     (Can_GetPduInfoOfActiveSendObject(Index)).id
# define Can_SetActiveSendId(Index,Value)               (Can_GetPduInfoOfActiveSendObject(Index)).id = (Value)
# define Can_GetActiveSendLength(Index)                 (Can_GetPduInfoOfActiveSendObject(Index)).length
# define Can_SetActiveSendLength(Index,Value)           (Can_GetPduInfoOfActiveSendObject(Index)).length = (Value)
# define Can_GetActiveSendSdu(Index)                    (Can_GetPduInfoOfActiveSendObject(Index)).sdu
# define Can_SetActiveSendSdu(Index,Value)              (Can_GetPduInfoOfActiveSendObject(Index)).sdu = (Value)
# define Can_GetActiveSendSwPduHandle(Index)            (Can_GetPduInfoOfActiveSendObject(Index)).swPduHandle
# define Can_SetActiveSendSwPduHandle(Index,Value)      (Can_GetPduInfoOfActiveSendObject(Index)).swPduHandle = (Value)

#else /* without ComStackLib */

# if defined(CAN_ENABLE_SELECTABLE_PB)
/* \trace SPEC-1727 */
/* Pointer parameter of initialization function used (selectable Post-Build) */
#  define CAN_GLOBAL_CONFIG(x)                          Can_ConfigDataPtr->x      /* PRQA S 3410 */ /* MD_Can_3410 */
#  define CAN_CONTROLLER_CONFIG_INIT                    (Can_ConfigDataPtr->CanControllerConfig_TabPtr)
#  define CAN_CONTROLLER_CONFIG(hwch)                   (Can_ConfigDataPtr->CanControllerConfig_TabPtr[(hwch)])
#  define CAN_MAILBOX                                   (Can_ConfigDataPtr->CanMailbox_TabPtr)
#  define CAN_INIT_OBJ_START_IDX                        (Can_ConfigDataPtr->CanInitObjectStartIndex_TabPtr)
#  define CAN_INIT_OBJ_BAUDRATE                         (Can_ConfigDataPtr->CanInitObjectBaudrate_TabPtr)
#  define CAN_INIT_OBJ_FD_BRS_CONFIG                    (Can_ConfigDataPtr->CanInitObjectFdConfig_TabPtr)
#  define CanHwObjIndivPolling                          (Can_ConfigDataPtr->CanHwObjIndivPolling_TabPtr) /* PRQA S 3436 */ /* MD_Can_3436 */
#  define CAN_PARTIAL_NET                               (Can_ConfigDataPtr->CanPartialNetwork_TabPtr)
/* hardware specific starts here */
#define CanInitObject          (Can_ConfigDataPtr->CanInitObjectPtr)
#define CanInitBasicCan        (Can_ConfigDataPtr->CanInitBasicCanPtr)
#define CanInitBasicCanIndex   (Can_ConfigDataPtr->CanInitBasicCanIndexPtr)
#define CanHwChannelData       (Can_ConfigDataPtr->CanHwChannelDataPtr)
# else
/* \trace SPEC-1728 */
/* Pointer parameter of initialization function not used (no selectable Post-Build or Link-Time configuration) */
#  if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
#   define CAN_GLOBAL_CONFIG(x)                         Can_ConfigDataPtr->x      /* PRQA S 3410 */ /* MD_Can_3410 */
#  else
#   define CAN_GLOBAL_CONFIG(x)                         CanConfig.x               /* PRQA S 3410 */ /* MD_Can_3410 */
#  endif
#  define CAN_CONTROLLER_CONFIG_INIT                    CanControllerConfig
#  define CAN_CONTROLLER_CONFIG(hwch)                   CanControllerConfig[(hwch)]
#  define CAN_MAILBOX                                   CanMailbox
#  define CAN_INIT_OBJ_START_IDX                        CanInitObjectStartIndex
#  define CAN_INIT_OBJ_BAUDRATE                         CanInitObjectBaudrate
#  define CAN_INIT_OBJ_FD_BRS_CONFIG                    CanInitObjectFdConfig
#  define CAN_PARTIAL_NET                               CanPartialNetwork
# endif

/* CONST PB */
# define Can_GetBaseDll_GeneratorVersion()              CAN_GLOBAL_CONFIG(Can_BaseDll_GeneratorVersion)
# define Can_GetPlatformDll_GeneratorVersion()          CAN_GLOBAL_CONFIG(Can_PlatformDll_GeneratorVersion)
# define Can_GetPrecompileCRC()                         CAN_GLOBAL_CONFIG(Can_ePrecompileCRC)
# define Can_GetLinktimeCRC()                           CAN_GLOBAL_CONFIG(Can_eLinktimeCRC)
# define Can_GetIdentitySelected()                      CAN_GLOBAL_CONFIG(IdentitySelected)
# define Can_GetControllerMax()                         CAN_GLOBAL_CONFIG(CanControllerMax)
# define Can_GetHwChannelMax()                          CAN_GLOBAL_CONFIG(CanHwChannelMax)
# define Can_GetMaxRxDataLen()                          CAN_GLOBAL_CONFIG(CanMaxRxDataLen)
# define Can_GetMaxTxDataLen()                          CAN_GLOBAL_CONFIG(CanMaxTxDataLen)
# define Can_GetFinalMagicNumber()                      CAN_GLOBAL_CONFIG(FinalMagicNumber)

# define Can_GetCanControllerDefaultBaudrate(Index)     CAN_CONTROLLER_CONFIG(Index).CanControllerDefaultBaudrate
# define Can_GetCanControllerDefaultBaudrateIdx(Index)  CAN_CONTROLLER_CONFIG(Index).CanControllerDefaultBaudrateIdx
# define Can_GetRxBasicHandleMax(Index)                 CAN_CONTROLLER_CONFIG(Index).RxBasicHandleMax
# define Can_GetRxBasicHandleStart(Index)               CAN_CONTROLLER_CONFIG(Index).RxBasicHandleStart
# define Can_GetRxBasicHandleStop(Index)                CAN_CONTROLLER_CONFIG(Index).RxBasicHandleStop
# define Can_GetRxBasicHwStart(Index)                   CAN_CONTROLLER_CONFIG(Index).RxBasicHwStart
# define Can_GetRxBasicHwStop(Index)                    CAN_CONTROLLER_CONFIG(Index).RxBasicHwStop
# define Can_GetRxFullHandleMax(Index)                  CAN_CONTROLLER_CONFIG(Index).RxFullHandleMax
# define Can_GetRxFullHandleStart(Index)                CAN_CONTROLLER_CONFIG(Index).RxFullHandleStart
# define Can_GetRxFullHandleStop(Index)                 CAN_CONTROLLER_CONFIG(Index).RxFullHandleStop
# define Can_GetRxFullHwStart(Index)                    CAN_CONTROLLER_CONFIG(Index).RxFullHwStart
# define Can_GetRxFullHwStop(Index)                     CAN_CONTROLLER_CONFIG(Index).RxFullHwStop
# define Can_GetTxBasicHandleMax(Index)                 CAN_CONTROLLER_CONFIG(Index).TxBasicHandleMax
# define Can_GetTxBasicHandleStart(Index)               CAN_CONTROLLER_CONFIG(Index).TxBasicHandleStart
# define Can_GetTxBasicHandleStop(Index)                CAN_CONTROLLER_CONFIG(Index).TxBasicHandleStop
# define Can_GetTxBasicHwStart(Index)                   CAN_CONTROLLER_CONFIG(Index).TxBasicHwStart
# define Can_GetTxBasicHwStop(Index)                    CAN_CONTROLLER_CONFIG(Index).TxBasicHwStop
# define Can_GetTxFullHandleMax(Index)                  CAN_CONTROLLER_CONFIG(Index).TxFullHandleMax
# define Can_GetTxFullHandleStart(Index)                CAN_CONTROLLER_CONFIG(Index).TxFullHandleStart
# define Can_GetTxFullHandleStop(Index)                 CAN_CONTROLLER_CONFIG(Index).TxFullHandleStop
# define Can_GetTxFullHwStart(Index)                    CAN_CONTROLLER_CONFIG(Index).TxFullHwStart
# define Can_GetTxFullHwStop(Index)                     CAN_CONTROLLER_CONFIG(Index).TxFullHwStop
# define Can_GetUnusedHandleMax(Index)                  CAN_CONTROLLER_CONFIG(Index).UnusedHandleMax
# define Can_GetUnusedHandleStart(Index)                CAN_CONTROLLER_CONFIG(Index).UnusedHandleStart
# define Can_GetUnusedHandleStop(Index)                 CAN_CONTROLLER_CONFIG(Index).UnusedHandleStop
# define Can_GetUnusedHwStart(Index)                    CAN_CONTROLLER_CONFIG(Index).UnusedHwStart
# define Can_GetUnusedHwStop(Index)                     CAN_CONTROLLER_CONFIG(Index).UnusedHwStop

# define Can_GetDLC_FIFO(Index)                         CAN_MAILBOX[(Index)].DLC_FIFO
# define Can_GetHwHandle(Index)                         CAN_MAILBOX[(Index)].HwHandle
# define Can_GetIDValue(Index)                          CAN_MAILBOX[(Index)].IDValue
# define Can_GetMailboxType(Index)                      CAN_MAILBOX[(Index)].MailboxType
# define Can_GetMailboxDataLen(Index)                   8 /* just for DET check against maximum value - FD-mode2 not supported for GENy */
# define Can_GetMailboxController(Index)                CAN_MAILBOX[(Index)].MsgController

# define Can_GetInitObjectStartIndex(Index)             CAN_INIT_OBJ_START_IDX[(Index)]
# define Can_GetInitObjectBaudrate(Index)               CAN_INIT_OBJ_BAUDRATE[(Index)]
# define Can_GetInitObjectFdBrsConfig(Index)            CAN_INIT_OBJ_FD_BRS_CONFIG[(Index)]

# define Can_GetPartialNetwork(Index)                   CAN_PARTIAL_NET[(Index)] /* only CAN_MSR3 */

# define Can_GetCanHwObjIndivPolling(ch,Index)          CanHwObjIndivPolling[ch][(Index)]

/* CONST */
# define Can_GetWakeupSourceRef(Index)                  CanWakeupSourceRef[(Index)]
# define Can_GetControllerBaudrateConfig(Index)         Can_ControllerBaudrateConfig[(Index)] /* only CAN_MSR40 */
# define Can_GetHwChannelStartIndex(Index)              CanHwChannelStartIndex[(Index)]
# define Can_GetHwChannelToChannel(Index)               CanHwChannelToChannel[(Index)]
# define Can_GetChannelIdentityAssignment(Index)        CanChannelIdentityAssignment[(Index)]
# define Can_GetCanToCanIfChannelMapping(Index)         (Index)
# define Can_GetTxOffsetHwToLog(Index)                  canTxOffsetHwToLog[(Index)]

/* VAR */
# define Can_GetSizeOfRxQueueBuffer()                   kCanRxQueueSize

# define Can_GetActiveSendPdu(Index)                    CanActiveSendPdu[(Index)]
# define Can_SetActiveSendPdu(Index,Value)              CanActiveSendPdu[(Index)] = (Value)
# define Can_GetActiveSendState(Index)                  CanActiveSendState[(Index)]
# define Can_SetActiveSendState(Index,Value)            CanActiveSendState[(Index)] = (Value)
# define Can_GetActiveSendPduInfo(Index)                CanActiveSendId[(Index)]
# define Can_GetActiveSendId(Index)                     CanActiveSendId[(Index)].id
# define Can_SetActiveSendId(Index,Value)               CanActiveSendId[(Index)].id = (Value)
# define Can_GetActiveSendLength(Index)                 CanActiveSendId[(Index)].length
# define Can_SetActiveSendLength(Index,Value)           CanActiveSendId[(Index)].length = (Value)
# define Can_GetActiveSendSdu(Index)                    CanActiveSendId[(Index)].sdu
# define Can_SetActiveSendSdu(Index,Value)              CanActiveSendId[(Index)].sdu = (Value)
# define Can_GetActiveSendSwPduHandle(Index)            CanActiveSendId[(Index)].swPduHandle
# define Can_SetActiveSendSwPduHandle(Index,Value)      CanActiveSendId[(Index)].swPduHandle = (Value)

# define Can_GetLastInitObject(Index)                   lastInitObject[(Index)]
# define Can_SetLastInitObject(Index,Value)             lastInitObject[(Index)] = (Value)
# define Can_GetCanInterruptOldStatus(Index)            canCanInterruptOldStatus[(Index)]
# define Can_SetCanInterruptOldStatus(Index,Value)      canCanInterruptOldStatus[(Index)] = (Value)
# define Can_GetCanInterruptCounter(Index)              canInterruptCounter[(Index)]
# define Can_SetCanInterruptCounter(Index,Value)        canInterruptCounter[(Index)] = (Value)
# define Can_IsIsWakeup(Index)                          (canIsWakeup[(Index)] != FALSE)
# define Can_SetIsWakeup(Index,Value)                   canIsWakeup[(Index)] = (Value)
# define Can_IsIsBusOff(Index)                          (canIsBusOff[(Index)] != FALSE)
# define Can_SetIsBusOff(Index,Value)                   canIsBusOff[(Index)] = (Value)
# define Can_GetStatusReq(Index)                        canStatusReq[(Index)] /* only CAN_MSR4 or RAM_CHECK */
# define Can_SetStatusReq(Index,Value)                  canStatusReq[(Index)] = (Value) /* only CAN_MSR4 or RAM_CHECK */
# define Can_GetLogStatus(Index)                        canStatus[(Index)]
# define Can_SetLogStatus(Index,Value)                  canStatus[(Index)] = (Value)
# define Can_GetCanLoopTimeout(ch, Index)               canLoopTimeout[(ch)][(Index)]
# define Can_IsIsHardwareCanceled(Index)                (canIsHardwareCanceled[(Index)] != FALSE)
# define Can_SetIsHardwareCanceled(Index,Value)         canIsHardwareCanceled[(Index)] = (Value)
# define Can_GetMirrorModeState(Index)                  canMirrorMode[(Index)]             /* GENy will be generated by platforms that support this feature */
# define Can_SetMirrorModeState(Index,Value)            canMirrorMode[(Index)] = (Value)   /* GENy will be generated by platforms that support this feature */
# define Can_GetSilentModeState(Index)                  canSilentMode[(Index)]             /* GENy will be generated by platforms that support this feature */
# define Can_SetSilentModeState(Index,Value)            canSilentMode[(Index)] = (Value)   /* GENy will be generated by platforms that support this feature */
# define Can_GetMailboxState(Index)                     canMailboxState[(Index)] /* only RAM_CHECK */
# define Can_SetMailboxState(Index,Value)               canMailboxState[(Index)] = (Value) /* only RAM_CHECK */

# define Can_GetCanTxBasicDataBuffer(ch,muxTx)          canTxBasicDataBuffer[(ch)][(muxTx)]
# define Can_GetRxQueueInfo()                           (canRxQueueInfo)
# define Can_GetRxQueueBuffer(Index)                    (canRxQueueBuffer[(Index)])
# define Can_IsTimeoutCall(Index)                       (canTimeoutCall[(Index)] != FALSE) /* only CAN_MSR3 */
# define Can_SetTimeoutCall(Index,Value)                canTimeoutCall[(Index)] = (Value)

#endif

#if !defined(CAN_GEN_COM_STACK_LIB) /* != CAN_MSR403 */ /* COV_CAN_COMPATIBILITY */

# define Can_GetBaseAddressOfControllerConfig(Index)                       CanHwChannelData[(Index)].CanBaseAddress
# define Can_GetInterruptMask1OfControllerConfig(Index)                    CanHwChannelData[(Index)].CanInterruptMask1
# define Can_GetInterruptMask2OfControllerConfig(Index)                    CanHwChannelData[(Index)].CanInterruptMask2
# define Can_GetInterruptMask3OfControllerConfig(Index)                    CanHwChannelData[(Index)].CanInterruptMask3
# define Can_GetInterruptMask4OfControllerConfig(Index)                    CanHwChannelData[(Index)].CanInterruptMask4

# define Can_GetRxBasicPollingMask1OfControllerConfig(Index)               CanHwChannelData[(Index)].CanRxBasicPollingMask1
# define Can_GetRxBasicPollingMask2OfControllerConfig(Index)               CanHwChannelData[(Index)].CanRxBasicPollingMask2
# define Can_GetRxBasicPollingMask3OfControllerConfig(Index)               CanHwChannelData[(Index)].CanRxBasicPollingMask3
# define Can_GetRxBasicPollingMask4OfControllerConfig(Index)               CanHwChannelData[(Index)].CanRxBasicPollingMask4

# define Can_GetRxFullPollingMask1OfControllerConfig(Index)                CanHwChannelData[(Index)].CanRxFullPollingMask1
# define Can_GetRxFullPollingMask2OfControllerConfig(Index)                CanHwChannelData[(Index)].CanRxFullPollingMask2
# define Can_GetRxFullPollingMask3OfControllerConfig(Index)                CanHwChannelData[(Index)].CanRxFullPollingMask3
# define Can_GetRxFullPollingMask4OfControllerConfig(Index)                CanHwChannelData[(Index)].CanRxFullPollingMask4

# define Can_GetTxPollingMask1OfControllerConfig(Index)                    CanHwChannelData[(Index)].CanTxPollingMask1
# define Can_GetTxPollingMask2OfControllerConfig(Index)                    CanHwChannelData[(Index)].CanTxPollingMask2
# define Can_GetTxPollingMask3OfControllerConfig(Index)                    CanHwChannelData[(Index)].CanTxPollingMask3
# define Can_GetTxPollingMask4OfControllerConfig(Index)                    CanHwChannelData[(Index)].CanTxPollingMask4


# define Can_GetRFFNOfControllerConfig(Index)                              CanHwChannelData[(Index)].CanRFFN
# define Can_GetReservedMBOfControllerConfig(Index)                        CanHwChannelData[(Index)].CanReservedMB
# define Can_GetNumberOfFullConfigurableFiltersOfControllerConfig(Index)   CanHwChannelData[(Index)].CanNumberOfFullConfigurableFilters
# define Can_GetNumberOfFiltersOfControllerConfig(Index)                   CanHwChannelData[(Index)].CanNumberOfFilters
# define Can_GetGlitchFilterOfControllerConfig(Index)                      CanHwChannelData[(Index)].CanGlitchFilter
# define Can_GetFDMailboxMaxWordLengthOfControllerConfig(Index)            CanHwChannelData[(Index)].CanFdMailboxMaxWordLength
# define Can_GetNumberOfMaxMailboxesOfControllerConfig(Index)              CanHwChannelData[(Index)].CanNumberOfMaxMailboxes

# define Can_GetInitBasicCanIndex(Index)                                   CanInitBasicCanIndex[(Index)]
# define Can_GetInitCodeOfInitBasicCan(Index)                              CanInitBasicCan[(Index)].CanInitCode
# define Can_GetInitMaskOfInitBasicCan(Index)                              CanInitBasicCan[(Index)].CanInitMask

# define Can_GetControl1OfInitObject(Index)                                CanInitObject[(Index)].CanControl1
# define Can_GetCBTOfInitObject(Index)                                     CanInitObject[(Index)].CBT
# define Can_GetTASDOfInitObject(Index)                                    CanInitObject[(Index)].CanTASD

# define Can_GetProtectedAreaId(Index)                                     CanProtectedAreaId[(Index)]

# define Can_GetRxMsgBufferOfControllerData(Index)                         canRxMsgBuffer[(Index)]


# define Can_GetStartModeRequested(Index)           startModeRequested[(Index)]
# define Can_SetStartModeRequested(Index, Value)    startModeRequested[(Index)] = (Value)


#endif

/***************************************************************************/
/* Default switches                                                        */
/* Automatic define settings, depending on user configuration in can_cfg.h */
/***************************************************************************/
/***************************************************************************/
/*  Safe Check for FlexCAN3                                                */
/***************************************************************************/
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
#  if defined (C_ENABLE_WAKEUP_INTERRUPT) || \
      defined (C_ENABLE_GLITCH_FILTER) || \
      defined (V_CPU_IMX) || \
      defined (V_CPU_VYBRID) /* COV_CAN_SAFE_BSW_EXCLUSION_FLEXCAN3 */
#    error "Unsupported Feature activated for SafeBSW"
#  endif
# endif

#define CAN_HL_HW_LAYOUT_TXBASIC_FIRST
#define C_HL_DISABLE_OVERRUN_IN_STATUS

#define C_HL_DISABLE_HW_RANGES_FILTER

#define C_HL_ENABLE_IDTYPE_IN_DLC




#define C_HL_DISABLE_DUMMY_FCT_CALL


#define C_HL_DISABLE_TX_MSG_DESTROYED


#define C_HL_DISABLE_CANCEL_IN_HW_TASK


#define C_HL_DISABLE_HW_EXIT_TRANSMIT 

#if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
# define C_HL_ENABLE_LAST_INIT_OBJ     
#else
# define C_HL_DISABLE_LAST_INIT_OBJ
#endif

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
    defined( C_ENABLE_WAKEUP_INTERRUPT ) /* COV_CAN_INTERRUPT_SUPPORT */
# define C_HL_ENABLE_CAN_IRQ_DISABLE   
#else
# define C_HL_DISABLE_CAN_IRQ_DISABLE   
#endif 

#define C_HL_DISABLE_ADJUST_RXHANDLE


#define C_HL_DISABLE_REJECT_UNWANTED_IDTYPE

#define C_HL_DISABLE_REJECT_REMOTE_FRAME

#define C_HL_DISABLE_REJECT_REMOTE_FRAME_FULLCAN

#define C_HL_DISABLE_COPROCESSOR_SUPPORT



#define C_HL_DISABLE_RETRANSMIT_FCT

#define C_HL_ENABLE_RETRANSMIT_CONF_ISR

#define C_HL_DISABLE_AVOID_REENTRANT_APPLCANCANCELNOTIFICATION

/* Possibility to disable the prototypes of interrupt service routines in the driver header file */

#define C_ENABLE_TX_ACTUAL_MACROS




#if defined ( C_ENABLE_CAN_FD_USED )
# if !defined( C_ENABLE_CLASSIC_MAILBOX_LAYOUT ) && !defined( C_DISABLE_CLASSIC_MAILBOX_LAYOUT ) /* COV_CAN_CLASSIC_MAILBOX_LAYOUT_COMPATABILITY */
#  define C_ENABLE_CLASSIC_MAILBOX_LAYOUT
# endif
#endif

/***************************************************************************/
/* macros                                                                  */
/***************************************************************************/



#define txErrCMask      (vuint32)0x000000FFu
#define rxErrCMask      (vuint32)0x0000FF00u
#define txErrCFastMask  (vuint32)0x00FF0000u
#define rxErrCFastMask  (vuint32)0xFF000000u




/* macros to set DLC and ID in rx-,tx-structures ---------------------------*/
/* MK... macros are used by the generation tool to fill the rx and tx structures */
/* In case the IDE bit is located in the ID registers, this bit has to be handled as must match.
   In general, this is done by setting the IDE bit to 0 in the .._MASK_.. macros.
*/


#if defined( C_ENABLE_EXTENDED_ID ) 
# define MK_STDID0(id)                 ((vuint32)(((vuint32)(id) & (vuint32)0x07FF) << 18))
#else
# define MK_STDID0(id)                 ((vuint16)(((vuint16)(id) & (vuint16)0x07FF) << 2))
#endif


#define MK_EXTID0(id)            ((vuint32)((vuint32)(id) & (vuint32)0x1FFFFFFF))

#define MK_RX_RANGE_MASK_IDSTD0(id)    ((vuint32)MK_STDID0(id))   

#define MK_RX_RANGE_CODE_IDSTD0(id)    ((vuint32)MK_STDID0(id))   

#define MK_RX_RANGE_MASK_IDEXT0(id)    ((vuint32)MK_EXTID0(id))   

#define MK_RX_RANGE_CODE_IDEXT0(id)    ((vuint32)MK_EXTID0(id))   




/* Message Configuration Register:
 * Example C16x:
 * DLC3 DLC2 DLC1 DLC0 Dir Xtd 0 0
 *                      |   |+------------- 0: standard ID; 1: extended ID
 *                      +------------------ 0: receive    ; 1: transmit
*/

#define MK_TX_DLC(dlc)       ((vuint8)((vuint8)(dlc) & (vuint8)0x0F))
#define MK_TX_DLC_EXT(dlc)   ((vuint8)(((vuint8)(dlc) & (vuint8)0x0F) | (vuint8)kCanIdTypeExt))

/* extract  DLC from register format to logical format */
#define XT_TX_DLC(dlc)       ((vuint8)((vuint8)(dlc) & (vuint8)0x0F))


#if defined( C_SINGLE_RECEIVE_CHANNEL )
/* Bus-Off functions */
# if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
#  define CanResetBusOffStart(x)
# else
#  define CanResetBusOffStart(a)       (CanInit(a))
#  define CanResetBusOffEnd(a)
# endif
/* Bus-Sleep functions */
# define CanResetBusSleep(a)     (CanInit(a))

#else
/* Bus-Off functions */
# if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
#  define CanResetBusOffStart(ch,x)
# else
#  define CanResetBusOffStart(ch, a)   (CanInit((ch), (a)))
#  define CanResetBusOffEnd(ch, a)
# endif
/* Bus-Sleep functions */
# define CanResetBusSleep(ch, a)     (CanInit((ch), (a)))
#endif



/* The macros CanRxActualIdRawx() have to provide the register context of the ID registers.
   It is not necessary to mask any bits. These macros are for internal use only and masking
   will be done in can_hls.c
*/
#if defined( C_ENABLE_EXTENDED_ID )
# define CanRxActualIdRaw0(rxStruct)      ((vuint32)(((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->msgID))
#else
# define CanRxActualIdRaw0(rxStruct)      ((vuint16)((((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->msgID) >> 16) & (vuint16)0x1FFF)
#endif /* C_ENABLE_EXTENDED_ID */

/* Macros for CAN message access within ApplCanMsgReceived() or PreCopy() function */
#if defined( C_ENABLE_EXTENDED_ID )
# define CanRxActualIdExtHi(rxStruct)        ((vuint8)((((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->msgID) >> 24) & (vuint8)0x1F)
# define CanRxActualIdExtMidHi(rxStruct)     ((vuint8)((((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->msgID) >> 16) & (vuint8)0xFF)
# define CanRxActualIdExtMidLo(rxStruct)     ((vuint8)((((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->msgID) >> 8) & (vuint8)0xFF)
# define CanRxActualIdExtLo(rxStruct)        ((vuint8)(((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->msgID) & (vuint8)0xFF)
#endif

#if defined( C_ENABLE_EXTENDED_ID ) 
# define XT_ID(id)         ((vuint16)(((vuint32)(id) & (vuint32)0x1FFC0000) >> 18))
#else
# define XT_ID(id)         ((vuint16)(((vuint16)(id) & 0x1FFC) >> 2))
#endif
#define XT_EXTID(id)       ((vuint32)((vuint32)(id) & (vuint32)0x1FFFFFFF))

#define CanRxActualExtId(rxStruct)        (XT_EXTID(CanRxActualIdRaw0(rxStruct)))
#define CanRxActualStdId(rxStruct)        (XT_ID(CanRxActualIdRaw0(rxStruct)))

#define CanRxActualData(rxStruct,i)       ((vuint8)((rxStruct)->pChipData[(i)]))
#define CanRxActualDLC(rxStruct)          ((vuint8)(((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->control) & (vuint8)0x0F)
#define CanRxActualIdType(rxStruct)       ((vuint8)(((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->control) & (vuint8)kCanIdTypeExt)
#define CanRxActualFdType(rxStruct)       ((vuint8)((((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->control) >> 8) & (vuint8)kCanFdTypeFd)

/* Macros for CAN message access within GenericConfirmation() function */

#if defined( C_ENABLE_EXTENDED_ID )
# define CanTxActualIdRaw0(txStruct)      ((vuint32)(((tCanMsgObjPtr)((txStruct)->pChipMsgObj))->msgID))
#else
# define CanTxActualIdRaw0(txStruct)      ((vuint16)((((tCanMsgObjPtr)((txStruct)->pChipMsgObj))->msgID) >> 16) & (vuint16)0x1FFF)
#endif /* C_ENABLE_EXTENDED_ID */

#define CanTxActualStdId(txStruct)        (XT_ID(CanTxActualIdRaw0(txStruct)))
#define CanTxActualExtId(txStruct)        (XT_EXTID(CanTxActualIdRaw0(txStruct)))
#define CanTxActualFdType(txStruct)       ((vuint8)((((tCanMsgObjPtr)((txStruct)->pChipMsgObj))->control) >> 8) & (vuint8)kCanFdTypeFd)
#define CanTxActualDLC(txStruct)          ((vuint8)(((tCanMsgObjPtr)((txStruct)->pChipMsgObj))->control) & (vuint8)0x0F)
#define CanTxActualIdType(txStruct)       ((vuint8)(((tCanMsgObjPtr)((txStruct)->pChipMsgObj))->control) & (vuint8)kCanIdTypeExt)
#define CanTxActualData(rxStruct,i)       ((vuint8)((txStruct)->pChipData[(i)]))

/* Macros for CAN message access within PreTransmit() function */

#if defined( C_ENABLE_EXTENDED_ID )
# define CanTxWriteActId(txStruct,id)       (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->msgID) = MK_STDID0(id); \
                                            (vuint8)(((tCanMsgObjPtr)((txStruct).pChipMsgObj))->control) &= (vuint8)0x0F

# define CanTxWriteActExtId(txStruct,id)    (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->msgID) = MK_EXTID0(id); \
                                            (vuint8)(((tCanMsgObjPtr)((txStruct).pChipMsgObj))->control) |= (vuint8)kCanIdTypeExt
#else
# define CanTxWriteActId(txStruct,id)       (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->msgID) = ((((tCanMsgObjPtr)((txStruct).pChipMsgObj))->msgID) & 0x0000FFFF) | ((vuint32)MK_STDID0(id) << 16); \
                                            (vuint8)(((tCanMsgObjPtr)((txStruct).pChipMsgObj))->control) &= (vuint8)0x0F
#endif
#define CanTxWriteActDLC(txStruct,dlc)      (vunin8)(((tCanMsgObjPtr)((txStruct).pChipMsgObj))->control) &= (vuint8)kCanIdTypeExt; \
                                            (vunin8)(((tCanMsgObjPtr)((txStruct).pChipMsgObj))->control) |= ((vuint8)(dlc) & (vuint8)0x0F)


/* macros for buffer access */
#define StartRxReadSync()          (VStdSuspendAllInterrupts())
#define EndRxReadSync()            (VStdResumeAllInterrupts())

#define StartRxWriteSync()         (VStdSuspendAllInterrupts())
#define EndRxWriteSync()           (VStdResumeAllInterrupts())

#define StartTxReadSync()
#define EndTxReadSync()

#define StartTxWriteSync()         (VStdSuspendAllInterrupts())
#define EndTxWriteSync()           (VStdResumeAllInterrupts())

#define StartRxWriteCANSync() 
#define EndRxWriteCANSync()   

#define StartRxReadCANSync()  
#define EndRxReadCANSync()    

#define StartRxFullCANReadSync(Obj)  (VStdSuspendAllInterrupts())
#define EndRxFullCANReadSync(Obj)    (VStdResumeAllInterrupts())

#define StartRxFullCANWriteSync(obj) (VStdSuspendAllInterrupts())
#define EndRxFullCANWriteSync(obj)   (VStdResumeAllInterrupts())

/* macros for flag access */
#define CanStartFlagWriteSync()    (VStdSuspendAllInterrupts())
#define CanEndFlagWriteSync()      (VStdResumeAllInterrupts())

/* macros to copy data bytes to unint32 */
# define CanCopyDataBytes2Uint32(dst, src) \
            (dst)[0] = ((((vuint32)((src)[0])) << 24) & (vuint32)0xFF000000u) | \
                       ((((vuint32)((src)[1])) << 16) & (vuint32)0x00FF0000u) | \
                       ((((vuint32)((src)[2])) << 8) & (vuint32)0x0000FF00u) | \
                       (((vuint32)((src)[3])) & (vuint32)0x000000FFu); \
            (dst)[1] = ((((vuint32)((src)[4])) << 24) & (vuint32)0xFF000000u) | \
                       ((((vuint32)((src)[5])) << 16) & (vuint32)0x00FF0000u) | \
                       ((((vuint32)((src)[6])) << 8) & (vuint32)0x0000FF00u) | \
                       (((vuint32)((src)[7])) & (vuint32)0x000000FFu);

# define CanCopyFDDataBytes2Uint32(dst, src) \
            (dst) = ((((vuint32)((src)[0])) << 24) & (vuint32)0xFF000000u) | \
                    ((((vuint32)((src)[1])) << 16) & (vuint32)0x00FF0000u) | \
                    ((((vuint32)((src)[2])) << 8) & (vuint32)0x0000FF00u) | \
                    (((vuint32)((src)[3])) & (vuint32)0x000000FFu);

# define CanAdd1FDByte2Uint32(dst, src) \
            (dst) =  (((dst) << 8)); \
            (dst) |= (((vuint32)((src))) & (vuint32)0x000000FFu);

# define CanCopyFDPadding2Uint32(dst, src) \
            (dst) = ((((vuint32)((src))) << 24) & (vuint32)0xFF000000u) | \
                    ((((vuint32)((src))) << 16) & (vuint32)0x00FF0000u) | \
                    ((((vuint32)((src))) << 8) & (vuint32)0x0000FF00u) | \
                    (((vuint32)((src))) & (vuint32)0x000000FFu);


#define CAN_HL_MIN(x,y) (((x)>(y)) ? (y) : (x)) /* COV_CAN_GENDATA_FAILURE */
#define CAN_HL_MAX(x,y) (((x)<(y)) ? (y) : (x)) /* COV_CAN_GENDATA_FAILURE */

/***************************************************************************************************/
/* Macros for dummy statements */
#if !defined(CAN_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
# if defined(V_ENABLE_USE_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
#  define CAN_DUMMY_STATEMENT(x) (x) = (x)
# else
#  define CAN_DUMMY_STATEMENT(x)
# endif
#endif
#if !defined(CAN_DUMMY_STATEMENT_CONST) /* COV_CAN_COMPATIBILITY */
# if defined(V_ENABLE_USE_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
#  define CAN_DUMMY_STATEMENT_CONST(x) (void)(x)
# else
#  define CAN_DUMMY_STATEMENT_CONST(x)
# endif
#endif

/***************************************************************************************************/
/* Macros for DET and assertions */
#if (CAN_DEV_ERROR_REPORT == STD_ON) /* \trace SPEC-1404, SPEC-1696, SPEC-3803, SPEC-3849 */
/* \trace SPEC-1725, SPEC-1403, SPEC-1568, SPEC-3781, SPEC-3819 */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
#  define Can_CallDetReportError(api, err) ((void) Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, (api), (err)))
# else
#  define Can_CallDetReportError(api, err) (Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, (api), (err)))
# endif
# define assertHardware(a, b, c)  if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define assertInternal(a, b, c)  if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define assertUser(a, b, c)      if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define assertGen(a, b, c)       if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define C_ENABLE_HARDWARE_CHECK
# define C_ENABLE_INTERNAL_CHECK
# define C_ENABLE_USER_CHECK
# define C_ENABLE_GEN_CHECK
#else
# define Can_CallDetReportError(api, err)
# define assertHardware(a, b, c)
# define assertInternal(a, b, c)
# define assertUser(a, b, c)
# define assertGen(a, b, c)
#endif
#if (CAN_DEV_ERROR_DETECT == STD_ON) 
# define CAN_IS_NO_ERROR(errorId) if ((errorId) == CAN_E_NO_ERROR)
#else
# define CAN_IS_NO_ERROR(errorId)
#endif

/***************************************************************************************************/
/* Macros for Critical Area abstraction */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
# define Can_EnterCritical(area)     SchM_Enter_Can_##area() /* PRQA S 0342 */ /* MD_Can_0342 */
# define Can_LeaveCritical(area)     SchM_Exit_Can_##area() /* PRQA S 0342*/ /* MD_Can_0342 */
#else
# define Can_EnterCritical(area)     SchM_Enter_Can(area) /* do not use double brackets here ESCAN00060494 */
# define Can_LeaveCritical(area)     SchM_Exit_Can(area)
#endif

#define CanDeclareGlobalInterruptOldStatus
/* CAN_EXCLUSIVE_AREA_0 called only by LL code */
#define CanSingleGlobalInterruptDisable()     Can_EnterCritical(CAN_EXCLUSIVE_AREA_0)
#define CanSingleGlobalInterruptRestore()     Can_LeaveCritical(CAN_EXCLUSIVE_AREA_0)
#define CanGlobalInterruptDisable()           Can_EnterCritical(CAN_EXCLUSIVE_AREA_0)
#define CanGlobalInterruptRestore()           Can_LeaveCritical(CAN_EXCLUSIVE_AREA_0)
#define CanNestedGlobalInterruptDisable()     Can_EnterCritical(CAN_EXCLUSIVE_AREA_0)
#define CanNestedGlobalInterruptRestore()     Can_LeaveCritical(CAN_EXCLUSIVE_AREA_0)

/* For LL: parameter has to be 'channel' not CAN_CHANNEL_PARA_ONLY */
# define CAN_CAN_INTERRUPT_RESTORE(ch)  Can_EnableControllerInterrupts((uint8)(ch))
# define CAN_CAN_INTERRUPT_DISABLE(ch)  Can_DisableControllerInterrupts((uint8)(ch))

/***************************************************************************************************/
/* Macros for LL-HLL compatibility */

/***************************************************************************************************/
/* Macros for ProtectedMode / PeripheralAccess */
# if defined ( C_ENABLE_USER_MODE_OS )
#  define CAN_WRITE_PROTECTED_REG8(area, regPtr, val)         osWritePeripheral8((area), (vuint32)(regPtr), (val))
#  define CAN_WRITE_PROTECTED_REG16(area, regPtr, val)        osWritePeripheral16((area), (vuint32)(regPtr), (val))
#  define CAN_WRITE_PROTECTED_REG32(area, regPtr, val)        osWritePeripheral32((area), (vuint32)(regPtr), (val))
#  define CAN_WRITE_PROTECTED_REG8_RESET(area, regPtr, bits)  osModifyPeripheral8((area), (vuint32)(regPtr), (vuint8)~(bits), (vuint8)0x00u)
#  define CAN_WRITE_PROTECTED_REG16_RESET(area, regPtr, bits) osModifyPeripheral16((area), (vuint32)(regPtr), (vuint16)~(bits), (vuint16)0x0000u)
#  define CAN_WRITE_PROTECTED_REG32_RESET(area, regPtr, bits) osModifyPeripheral32((area), (vuint32)(regPtr), (vuint32)~(bits), (vuint32)0x00000000UL)
#  define CAN_WRITE_PROTECTED_REG8_SET(area, regPtr, bits)    osModifyPeripheral8((area), (vuint32)(regPtr), (vuint8)0xFFu, (bits))
#  define CAN_WRITE_PROTECTED_REG16_SET(area, regPtr, bits)   osModifyPeripheral16((area), (vuint32)(regPtr), (vuint16)0xFFFFu, (bits))
#  define CAN_WRITE_PROTECTED_REG32_SET(area, regPtr, bits)   osModifyPeripheral32((area), (vuint32)(regPtr), (vuint32)0xFFFFFFFFUL, (bits))
#  define CAN_READ_PROTECTED_REG8(area, regPtr)               osReadPeripheral8((area), (vuint32)(regPtr))
#  define CAN_READ_PROTECTED_REG16(area, regPtr)              osReadPeripheral16((area), (vuint32)(regPtr))
#  define CAN_READ_PROTECTED_REG32(area, regPtr)              osReadPeripheral32((area), (vuint32)(regPtr))
# endif
# if defined ( C_ENABLE_USER_MODE_APPL )
#  define CAN_WRITE_PROTECTED_REG8(area, regPtr, val)         ApplCanWriteProtectedRegister8((regPtr), (vuint8)0xFFu, (val))
#  define CAN_WRITE_PROTECTED_REG16(area, regPtr, val)        ApplCanWriteProtectedRegister16((regPtr), (vuint16)0xFFFFu, (val))
#  define CAN_WRITE_PROTECTED_REG32(area, regPtr, val)        ApplCanWriteProtectedRegister32((regPtr), (vuint32)0xFFFFFFFFUL, (val))
#  define CAN_WRITE_PROTECTED_REG8_RESET(area, regPtr, bits)  ApplCanWriteProtectedRegister8((regPtr), (bits), (vuint8)0x00u)
#  define CAN_WRITE_PROTECTED_REG16_RESET(area, regPtr, bits) ApplCanWriteProtectedRegister16((regPtr), (bits), (vuint16)0x0000u)
#  define CAN_WRITE_PROTECTED_REG32_RESET(area, regPtr, bits) ApplCanWriteProtectedRegister32((regPtr), (bits), (vuint32)0x00000000UL)
#  define CAN_WRITE_PROTECTED_REG8_SET(area, regPtr, bits)    ApplCanWriteProtectedRegister8((regPtr), (bits), (bits))
#  define CAN_WRITE_PROTECTED_REG16_SET(area, regPtr, bits)   ApplCanWriteProtectedRegister16((regPtr), (bits), (bits))
#  define CAN_WRITE_PROTECTED_REG32_SET(area, regPtr, bits)   ApplCanWriteProtectedRegister32((regPtr), (bits), (bits))
#  define CAN_READ_PROTECTED_REG8(area, regPtr)               ApplCanReadProtectedRegister8((regPtr))
#  define CAN_READ_PROTECTED_REG16(area, regPtr)              ApplCanReadProtectedRegister16((regPtr))
#  define CAN_READ_PROTECTED_REG32(area, regPtr)              ApplCanReadProtectedRegister32((regPtr))
# endif
# if !defined(C_ENABLE_USER_MODE_OS) && !defined(C_ENABLE_USER_MODE_APPL)
#  define CAN_WRITE_PROTECTED_REG8(area, regPtr, val)         *(regPtr) = (val)
#  define CAN_WRITE_PROTECTED_REG16(area, regPtr, val)        *(regPtr) = (val)
#  define CAN_WRITE_PROTECTED_REG32(area, regPtr, val)        *(regPtr) = (val)
#  define CAN_WRITE_PROTECTED_REG8_RESET(area, regPtr, bits)  *(regPtr) &= (vuint8)~(bits)
#  define CAN_WRITE_PROTECTED_REG16_RESET(area, regPtr, bits) *(regPtr) &= (vuint16)~(bits)
#  define CAN_WRITE_PROTECTED_REG32_RESET(area, regPtr, bits) *(regPtr) &= (vuint32)~(bits)
#  define CAN_WRITE_PROTECTED_REG8_SET(area, regPtr, bits)    *(regPtr) |= (bits)
#  define CAN_WRITE_PROTECTED_REG16_SET(area, regPtr, bits)   *(regPtr) |= (bits)
#  define CAN_WRITE_PROTECTED_REG32_SET(area, regPtr, bits)   *(regPtr) |= (bits)
#  define CAN_READ_PROTECTED_REG8(area, regPtr)               *(regPtr)
#  define CAN_READ_PROTECTED_REG16(area, regPtr)              *(regPtr)
#  define CAN_READ_PROTECTED_REG32(area, regPtr)              *(regPtr)
# endif

/***************************************************************************/
/* error codes                                                             */
/***************************************************************************/
/* error numbers for User Assertions 0x20-0x3f - hardware depended */

/* error numbers for Generation tool Assertions 0x60-0x7f - hardware depended */
#define kErrorMaskExtIdConfig             ((vuint8)0x60)
/* error numbers for Hardware Assertions 0xa0-0xbf - hardware depended */

/* error numbers for Internal Assertions 0xe0-0xff - hardware depended */
#define kCanInvalidHwObjHandle                  ((vuint8)0xE0)

/***************************************************************************/
/* Special switches need by CAN driver                                     */
/***************************************************************************/

/***************************************************************************/
/* Defines / data types / structures / unions                              */
/***************************************************************************/
/* Define CAN Chip hardware; segment must be located in locator file    */
/* register layout of the can chip                                      */
/* Structure describing CAN receive buffer. */

typedef struct sCanRxInfoStruct
{
  CanChipMsgPtr  pChipMsgObj;
  CanChipDataPtr pChipData;
  Can_IdType localId;
  Can_HwHandleType localHrh;
  uint8 localDlc;
  /* LL specific part */
} tCanRxInfoStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanRxInfoStruct, VAR_NOINIT) CanRxInfoPtrType;

#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
typedef struct sCanTxInfoStruct
{
  CanChipDataPtr pChipData;
  /* LL specific part */
  CanChipMsgPtr   pChipMsgObj;
} tCanTxInfoStruct;
#endif

typedef struct sCanInitInfoStruct
{
  CAN_CHANNEL_CANTYPE_LOCAL
  CanInitHandle  initObject;
  uint8 isMbCorrupt;
  uint8 isChCorrupt;
  /* LL specific part */
} tCanInitInfoStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanInitInfoStruct, VAR_NOINIT) CanInitInfoPtrType;
#define CAN_HL_INFO_INIT_PTR(member)(initInfo->member) /* PRQA S 3410 */ /* MD_Can_3410 */
#define CAN_HL_INFO_INIT(member)    (initInfo.member)  /* PRQA S 3410 */ /* MD_Can_3410 */

typedef struct sCanRxBasicInfoStruct
{
  tCanRxInfoStruct rxInfo;
  CanObjectHandle rxObjHandle;
  CAN_CHANNEL_CANTYPE_LOCAL
  /* LL specific part */
  #if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  # if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanDeclareGlobalInterruptOldStatus
  # endif
  #endif
  tFlexCANPtr pFlexCANLocal; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
} tCanRxBasicInfoStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanRxBasicInfoStruct, VAR_NOINIT) CanRxBasicInfoPtrType;
#define CAN_HL_INFO_RXBASIC_PTR(member) ((*rxBasicInfo).member) /* PRQA S 3410 */ /* MD_Can_3410 */
#define CAN_HL_INFO_RXBASIC(member)     (rxBasicInfo.member)  /* PRQA S 3410 */ /* MD_Can_3410 */

typedef struct sCanRxFullInfoStruct
{
  tCanRxInfoStruct rxInfo;
  CanObjectHandle rxObjHandle;
  CAN_CHANNEL_CANTYPE_LOCAL
  /* LL specific part */
  #if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanDeclareGlobalInterruptOldStatus
  #endif
} tCanRxFullInfoStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanRxFullInfoStruct, VAR_NOINIT) CanRxFullInfoPtrType;
#define CAN_HL_INFO_RXFULL_PTR(member) ((*rxFullInfo).member) /* PRQA S 3410 */ /* MD_Can_3410 */
#define CAN_HL_INFO_RXFULL(member)     (rxFullInfo.member)  /* PRQA S 3410 */ /* MD_Can_3410 */

V_DEF_P2VAR_TYPE(V_NONE, CanObjectHandle, VAR_NOINIT) CanHlObjectHandlePtrType;
    
/***************************************************************************/
/* module global variable declaration                                      */
/***************************************************************************/

/***************************************************************************/
/* External Declarations                                                   */
/***************************************************************************/
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED  /*---------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED  /*----------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***************************************************************************/
/* local function prototypes (only internal usage)                         */
/***************************************************************************/
#define CAN_START_SEC_STATIC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanResetBusOffEnd()
 ***********************************************************************************************************/
/*! \brief         Finish busoff
 *  \details       Set state to busoff
 *  \param[in]     canHwChannel              CAN HW controller
 *  \param[in]     initObject                Index of the initialization structure to be initialized
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_BUSOFF_RECOVERY_COMPLIANT
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanResetBusOffEnd(CAN_CHANNEL_CANTYPE_FIRST uint8 initObject);
/* CODE CATEGORY 4 END */
# endif

# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
  /* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  Can_CheckMaxHwMailboxHandle()
 ***********************************************************************************************************/
/*! \brief         Check for maximum value of HW mailbox handle
 *  \details       If canHwChannel is greater or equal to number of available mailboxes throw a DET
 *  \param[in]     hwChannel           hardware channel of the corresponding CAN Controller
 *  \param[in]     hwObjHandle         Handle to hardware object
 *  \return        errorid     0: no error, else error
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_SAFE_BSW == STD_ON
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) Can_CheckMaxHwMailboxHandle(CanChannelHandle hwChannel, Can_HwHandleType hwObjHandle);
/* CODE CATEGORY 4 END */
# endif

# if defined ( V_CPU_S32 ) /* COV_CAN_FLEXCAN3_ARM32_DERIVATIVE */
#  if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
#   if defined ( C_ENABLE_CAN_FD_FULL )
#    if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
  /* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  Can_CheckMaxHwFDMailboxHandle()
 ***********************************************************************************************************/
/*! \brief         Check for maximum value of HW FD mailbox handle
 *  \details       If hwObjHandle is greater or equal to number of available mailboxes throw a DET
 *  \param[in]     canHwChannel        hardware channel of the corresponding CAN Controller
 *  \param[in]     hwObjHandle         Handle to hardware object
 *  \return        errorid     0: no error, else errorr
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_FD_FULL && C_ENABLE_CAN_RXTX_INTERRUPT
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) Can_CheckMaxHwFDMailboxHandle(CAN_HW_CHANNEL_CANTYPE_FIRST Can_HwHandleType hwObjHandle);
/* CODE CATEGORY 4 END */
#    endif
#   endif
#  endif
# endif

# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
#  if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
      defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
      defined( C_ENABLE_CAN_WAKEUP_INTERRUPT ) /* COV_CAN_INTERRUPT_SUPPORT */
  /* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  Can_CheckSizeOfHwChannelData()
 ***********************************************************************************************************/
/*! \brief         Check size of HwChannelData
 *  \details       If canHwChannel is greater or equal to the size of HwChannelData throw a DET
 *  \param[in]     hwChannel   hardware channel of the corresponding CAN Controller
 *  \return        errorid     0: no error, else error
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT || C_ENABLE_CAN_BUSOFF_INTERRUPT || C_ENABLE_CAN_WAKEUP_INTERRUPT
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) Can_CheckSizeOfHwChannelData(CanChannelHandle hwChannel);
/* CODE CATEGORY 4 END */
#  endif
# endif

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
    defined( C_ENABLE_CAN_WAKEUP_INTERRUPT ) /* COV_CAN_INTERRUPT_SUPPORT */
/* CODE CATEGORY 2 START */
/************************************************************************************************************
 *  CanLL_CanInterruptDisable()
 ***********************************************************************************************************/
/*! \brief         disable CAN interrupt
 *  \details       saves the current status (enable or disable) of all 
 *                 CAN interrupts to localInterruptOldFlagPtr
 *                 and disables all CAN interrupts  (RX, TX, error, wakeup).
 *  \param[in]     canHwChannel              CAN HW controller
 *  \param[out]    localInterruptOldFlagPtr  get old interrupt state to be restored
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptDisable(CanChannelHandle canHwCh, tCanIntOldPtr localInterruptOldFlagPtr);

/************************************************************************************************************
 *  CanLL_CanInterruptRestore()
 **********************************************************************************************************/
/*! \brief         enable CAN interrupt
 *  \details       restores all CAN interrupts (RX, TX, error, wakeup).
 *  \param[in]     canHwChannel              CAN HW controller
 *  \param[in]     localInterruptOldFlag     old interrupt state to be restored
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptRestore(CanChannelHandle canHwCh, tCanLLCanIntOld localInterruptOldFlag);
/* CODE CATEGORY 2 END */
#endif
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_SetFlexCANToInitMode()
 ***********************************************************************************************************/
/*! \brief         Set FlexCAN Controller to INIT mode.
 *  \details       Sets the FlexCAN Controller from any mode to INIT mode.
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \param[in]     initObj       Selected INIT object that is used for initialization.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_SetFlexCANToInitMode(CAN_HW_CHANNEL_CANTYPE_FIRST CanInitHandle initObj);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_ExecuteSoftReset()
 ***********************************************************************************************************/
/*! \brief         Perform FlexCAN soft-reset
 *  \details       Triggers the FlexCAN Controller to perform internal soft-reset.
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ExecuteSoftReset(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_HandleBusOff()
 ***********************************************************************************************************/
/*! \brief         Handle BusOff recovery
 *  \details       Call CanInit and set BusOff flag to FALSE if BusOff recovery was successful
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \pre           Interrupts are disabled.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_BUSOFF_RECOVERY_COMPLIANT
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_HandleBusOff(CAN_CHANNEL_CANTYPE_ONLY);

/************************************************************************************************************
 *  CanLL_HandleStartProcess()
 ***********************************************************************************************************/
/*! \brief         Handle START process
 *  \details       Call CanInit and set BusOff flag to FALSE if BusOff recovery was successful
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \return        kCanOk (CAN_OK)          transition to START was finished successfully
 *  \return        kCanFailes (CAN_NOT_OK)  transition to START was not yet finished successfully
 *  \pre           Interrupts are disabled.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_BUSOFF_RECOVERY_COMPLIANT
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanLL_HandleStartProcess(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif

#if defined( C_ENABLE_CAN_RAM_CHECK )
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_IsMailboxCorrupt()
 ***********************************************************************************************************/
/*! \brief         RAM check
 *  \details       check the current mailbox at index hwObjHandle by write and read back patterns.
 *  \param[in]     Controller          CAN controller
 *  \param[in]     hwObjHandle         Handle to hardware object
 *  \return        kCanTrue:    Mailbox is corrupt
 *  \return        kCanFalse:   Mailbox is not corrupt  
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RAM_CHECK
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_IsMailboxCorrupt(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle hwObjHandle);
/* CODE CATEGORY 4 END */
# if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_InitBeginIsRegisterCorrupt()
 ***********************************************************************************************************/
/*! \brief         RAM check
 *  \details       check the channel register at the beginning of the initialization by write and read back patterns.
 *  \param[in]     Controller          CAN controller
 *  \return        kCanTrue:    Channel is corrupt
 *  \return        kCanFalse:   Channel is not corrupt  
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBeginIsRegisterCorrupt(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */

/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_CheckClockSource()
 ***********************************************************************************************************/
/*! \brief         Check the CAN[CTRL1].CLKSRC bit
 *  \details       check the CAN[CTRL1].CLKSRC bit by write and read back patterns.
 *  \param[in]     Controller   CAN controller
 *  \return        kCanTrue:    CAN[CTRL1].CLKSRC bit is corrupt
 *  \return        kCanFalse:   CAN[CTRL1].CLKSRC bit is not corrupt  
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_CheckClockSource(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif
#endif
#if defined ( V_CPU_S32 ) /* COV_CAN_FLEXCAN3_ARM32_DERIVATIVE */
# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanLL_ComputeMailboxInterrupt()
 ***********************************************************************************************************/
/*! \brief         Computes Mailbox interrupt.
 *  \details       Determines the index of the Mailbox that notified an interrupt and call
 *                 CanLL_ComputeInterruptType.
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \param[in]     iFlags        Interrupt Flags that should be used for computation.
 *  \param[in]     iMask         Interrupt Mask that determines which iFlags are considered in interrupt context.
 *  \param[in]     startIndex    Index of first Mailbox that is part of the corresponding iFlags/iMask values.
 *  \pre           -
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANTYPE_FIRST vuint32 iFlags, vuint32 iMask, CanObjectHandle startIndex);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanLL_ComputeInterruptType()
 ***********************************************************************************************************/
/*! \brief         Computes the communication type of the notified Mailbox interrupt (Tx/Rx FullCAN/BasicCAN).
 *  \details       Determines which communication event occurred and calls internal notification function.
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \param[in]     index         Index of the Mailbox that notified an interrupt.
 *  \pre           -
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ComputeInterruptType(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle index);
/* CODE CATEGORY 1 END */
# endif
#endif

/************************************************************************************************************
 *  CanInit()
 ***********************************************************************************************************/
/*! \brief         Wrapper for Can_InitController()
 *  \details       Initialization of controller specific CAN hardware. \n
 *                 The CAN driver registers and variables are initialized. \n
 *                 The CAN controller is fully initialized and left back within the state "STOP mode", ready to change to "Running Mode".
 *                 Called from LowLevel driver code while bus off handling or in case of mode transition that requires a reinitialization.
 *  \param[in]     Controller    CAN controller. \n
 *                               (only if not using "Optimize for one controller")
 *  \param[in]     initObject    Index of the initialization structure to be initialized (specifies the baud rate to be used.)
 *  \pre           initObject has to be valid
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanInit(CAN_CHANNEL_CANTYPE_FIRST uint8 initObject);
/************************************************************************************************************
 *  Can_CleanUpSendState()
 ***********************************************************************************************************/
/*! \brief         Clean up send state
 *  \details       Reset active send state (semaphore blocking TX while send).
 *                 Called by Can_SetControllerMode(), Can_Mainfunction_Mode() (Can_InitController() do same but without this call).
 *  \param[in]     Controller    CAN controller \n
 *                               (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) Can_CleanUpSendState(CAN_CHANNEL_CANTYPE_ONLY);

#if (defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) ) || defined(C_ENABLE_HW_LOOP_TIMER) /* always used for sync mode */ /* COV_CAN_MICROSAR_VERSION */
# if (CAN_HW_LOOP_SUPPORT_API == STD_OFF)
/************************************************************************************************************
 *  ApplCanTimerLoop()
 ***********************************************************************************************************/
/*! \brief         Time out monitoring
 *  \details       Service function to check (against generated maximum loop value) whether a hardware loop shall be continued or broken.
 *  \param[in]     Controller  CAN controller on which the hardware observation takes place. \n
 *                             (only if not using "Optimize for one controller")
 *  \param[in]     source      Source for the hardware observation.
 *  \return        CAN_NOT_OK  when loop shall be broken (observation stops) \n
 *                             CAN_NOT_OK should only be used in case of a time out occurs due to a hardware issue. \n
 *                             After this an appropriate error handling is needed (see chapter Hardware Loop Check / Time out Monitoring).
 *  \return        CAN_OK      when loop shall be continued (observation continues)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         Please refer to chapter "Hardware Loop Check".
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) ApplCanTimerLoop(CAN_CHANNEL_CANTYPE_FIRST uint8 source);
# endif
#endif

/************************************************************************************************************
 *  CanHL_StartTransition()
 ***********************************************************************************************************/
/*! \brief         Request START
 *  \details       Handle START transition and wait ASR3:synchronous, ASR4:asynchronous-short time and notify to upper layer.
 *                 Called by Can_SetControllerMode().
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \return        CAN_NOT_OK    transition rejected
 *  \return        CAN_OK        transition finished successful or is ongoing asynchronous
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_StartTransition(CAN_CHANNEL_CANTYPE_ONLY);

/************************************************************************************************************
 *  CanHL_StopTransition()
 ***********************************************************************************************************/
/*! \brief         Request STOP
 *  \details       Handle STOP transition and wait ASR3:synchronous, ASR4:asynchronous-short time and notify to upper layer.
 *                 Called by Can_SetControllerMode().
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \return        CAN_NOT_OK    transition rejected
 *  \return        CAN_OK        transition finished successful or is ongoing asynchronous
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_StopTransition(CAN_CHANNEL_CANTYPE_ONLY);

/************************************************************************************************************
 *  CanHL_WakeupTransition()
 ***********************************************************************************************************/
/*! \brief         Request WAKEUP
 *  \details       Handle WAKEUP transition and wait ASR3:synchronous, ASR4:asynchronous-short time and notify to upper layer.
 *                 Called by Can_SetControllerMode().
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \return        CAN_NOT_OK    transition rejected
 *  \return        CAN_OK        transition finished successful or is ongoing asynchronous
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_WakeupTransition(CAN_CHANNEL_CANTYPE_ONLY);

#if defined(C_ENABLE_CAN_RAM_CHECK)
/************************************************************************************************************
 *  CanHL_DoRamCheck()
 ***********************************************************************************************************/
/*! \brief         RAM check
 *  \details       Start RAM check by set request and start Can_InitController doing the check.
 *                 Called by CanHL_WakeupTransition(), Wakeup Processing, Can_RamCheckExecution().
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_DoRamCheck(CAN_CHANNEL_CANTYPE_ONLY);
#endif

/************************************************************************************************************
 *  CanHL_SleepTransition()
 ***********************************************************************************************************/
/*! \brief         Request SLEEP
 *  \details       Handle SLEEP transition and wait ASR3:synchronous, ASR4:asynchronous-short time and notify to upper layer.
 *                 Called by Can_SetControllerMode().
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \return        CAN_NOT_OK    transition rejected
 *  \return        CAN_OK        transition finished successful or is ongoing asynchronous
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_SleepTransition(CAN_CHANNEL_CANTYPE_ONLY);

#if defined(C_ENABLE_CANCEL_IN_HW)
/************************************************************************************************************
 *  CanHL_IsHigherCanIdPrio()
 ***********************************************************************************************************/
/*! \brief         check CAN ID priority
 *  \details       compare two CAN IDs and check if first one is of higher priority.
 *  \param[in]     CanId1        first CAN ID for compare
 *  \param[in]     CanId2        second CAN ID for compare
 *  \return        CAN_OK        first CAN ID has higher priority
 *  \return        CAN_NOT_OK    first CAN ID has no higher priority
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_IsHigherCanIdPrio(Can_IdType CanId1, Can_IdType CanId2);
#endif

#if defined(C_ENABLE_CANCEL_IN_HW) && defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
/************************************************************************************************************
 *  CanHL_SortlogTxObjHandlePrioList()
 ***********************************************************************************************************/
/*! \brief         Sort TX handle
 *  \details       Sort transmit hardware priority list to check witch hardware object should be cancelled first 
 *                 (not all objects ready to cancel e.g. already cancelled) so low priority ID is first in list.
 *                 Called by Can_Write().
 *  \param[out]    logTxObjHandlePrioList      Array[3] in case of MultiplexedTx which contain the logical handle index
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_SortlogTxObjHandlePrioList(CanHlObjectHandlePtrType logTxObjHandlePrioList);
#endif

/************************************************************************************************************
 *  CanHL_WritePrepare()
 ***********************************************************************************************************/
/*! \brief         TX preparation
 *  \details       Search for BasicCAN object handle to transmit (Multiplexed TX) and backup data for cancel TX object if necessary
 *                 Called by Can_Write().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     Hth              hardware transmit handle from (CanMailboxId)
 *  \param[in]     PduInfo          PDU info include ID, DLC, data, PDU
 *  \return        logTxObjHandle   logical transmit handle to be send
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, CanObjectHandle, STATIC_CODE) CanHL_WritePrepare(CAN_CHANNEL_CANTYPE_FIRST Can_HwHandleType Hth, Can_PduInfoPtrType PduInfo);

#if defined(C_ENABLE_CANCEL_IN_HW)
/************************************************************************************************************
 *  CanHL_WritePrepareCancelTx()
 ***********************************************************************************************************/
/*! \brief         TX cancellation
 *  \details       Cancel the BasicCAN TX object
 *                 Called by CanHL_WritePrepare().
 *  \param[in]     Controller              CAN controller. \n
 *                                         (only if not using "Optimize for one controller")
 *  \param[in]     logTxObjHandle          logical transmit handle to be send
 *  \param[in]     muxTx                   multiplexed TX index (or 0 for none)
 *  \param[in]     muxTx_max               multiplexed TX max size (1 or 3)
 *  \param[in]     logTxObjHandlePrioList  logTxObjHandle list
 *  \param[in]     PduInfo                 PDU info include ID, DLC, data, PDU
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_WritePrepareCancelTx(CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle logTxObjHandle, uint8_least muxTx, uint8_least muxTx_max, CanHlObjectHandlePtrType logTxObjHandlePrioList, Can_PduInfoPtrType PduInfo);
#endif

/************************************************************************************************************
 *  CanHL_WriteStart()
 ***********************************************************************************************************/
/*! \brief         TX start
 *  \details       Write ID, DLC and Data to FullCAN or BasicCAN object and set transmit request
 *                 Called by Can_Write().
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     Hth             hardware transmit handle from (CanMailboxId)
 *  \param[in]     logTxObjHandle  logical TX object handle
 *  \param[in]     PduInfo         PDU info include ID, DLC, data, PDU
 *  \return        CAN_NOT_OK      transmission failed.
 *  \return        CAN_OK          transmission successful.
 *  \return        CAN_BUSY        transition object busy - repeat it.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_WriteStart(CAN_CHANNEL_CANTYPE_FIRST Can_HwHandleType Hth, CanObjectHandle logTxObjHandle, Can_PduInfoPtrType PduInfo);

#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
/************************************************************************************************************
 *  CanHL_StartProcessed()
 ***********************************************************************************************************/
/*! \brief         Check START
 *  \details       Transition finished and notify to upper layer.
 *                 Called by Can_MainFunction_Mode().
 *  \param[in]     Controller      CAN controller. (Controller must be in valid range). \n
 *                                 (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_StartProcessed(CAN_CHANNEL_CANTYPE_ONLY);

/************************************************************************************************************
 *  CanHL_StopProcessed()
 ***********************************************************************************************************/
/*! \brief         Check STOP
 *  \details       Transition finished and notify to upper layer.
 *                 Called by Can_MainFunction_Mode().
 *  \param[in]     Controller      CAN controller. (Controller must be in valid range). \n
 *                                 (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_StopProcessed(CAN_CHANNEL_CANTYPE_ONLY);


#endif /* CAN_ENABLE_MICROSAR_VERSION_MSR40X */

/************************************************************************************************************
 *  CanHL_GetTxHwToLogHandle()
 ***********************************************************************************************************/
/*! \brief         Convert Handle
 *  \details       Hardware to logical Handle conversion.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     hwTxObjHandle   Handle to hardware mailbox
 *  \return        logical handle for the given hardware mailbox
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, CanObjectHandle, STATIC_CODE) CanHL_GetTxHwToLogHandle(CAN_CHANNEL_CANTYPE_FIRST Can_HwHandleType hwTxObjHandle);

/************************************************************************************************************
 *  CanHL_GetTxLogToHwHandle()
 ***********************************************************************************************************/
/*! \brief         Convert Handle
 *  \details       Logical to hardware Handle conversion.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     logTxObjHandle  Logical handle of TX mailbox
 *  \return        hardware mailbox for the given logical handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_HwHandleType, STATIC_CODE) CanHL_GetTxLogToHwHandle(CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle logTxObjHandle);

#if defined(C_ENABLE_CAN_RAM_CHECK)
/************************************************************************************************************
 *  CanHL_RamCheckMailboxNotification()
 ***********************************************************************************************************/
/*! \brief         RAM check
 *  \details       Notify upper layer in case of an HW issue and deactivate controller.
 *                 Called by Can_InitController().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     hwObjHandle      Handle to hardware object
 *  \param[in]     htrh             Hrh or Hth of the hardware object
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANTYPE_FIRST Can_HwHandleType hwObjHandle, Can_HwHandleType htrh);
#endif


/************************************************************************************************************
 *  CanHL_SetValue16()
 ***********************************************************************************************************/
/*! \brief         Write value and do RamCheck
 *  \details       Write the value of the hardware mailbox or controller register and read back for RamCheck. 
 *                 Notify upper layer in case of an HW issue and deactivate controller.
 *                 Called by Can_InitController().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     regPtr           valid pointer to Register to be written.
 *  \param[in]     value            value to be written.
 *  \param[in]     readMask         mask to check the read back value.
 *  \return        kCanTrue         RamCheck failed.
 *  \return        kCanFalse        RamCheck passed.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_SetValue16(CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr16 regPtr, uint16 value, uint16 readMask);

/************************************************************************************************************
 *  CanHL_SetValue32()
 ***********************************************************************************************************/
/*! \brief         Write value and do RamCheck
 *  \details       Write the value of the hardware mailbox or controller register and read back for RamCheck. 
 *                 Notify upper layer in case of an HW issue and deactivate controller.
 *                 Called by Can_InitController().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     regPtr           valid pointer to Register to be written.
 *  \param[in]     value            value to be written.
 *  \param[in]     readMask         mask to check the read back value.
 *  \return        kCanTrue         RamCheck failed.
 *  \return        kCanFalse        RamCheck passed.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_SetValue32(CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr32 regPtr, uint32 value, uint32 readMask);


/************************************************************************************************************
 *  CanHL_SetOsValue16()
 ***********************************************************************************************************/
/*! \brief         Write value via OS and do RamCheck
 *  \details       Write the value of the hardware mailbox or controller register and read back for RamCheck. 
 *                 Notify upper layer in case of an HW issue and deactivate controller.
 *                 Called by Can_InitController().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     area             Memory area to be written.
 *  \param[in]     regPtr           valid pointer to Register to be written.
 *  \param[in]     value            Value to be written.
 *  \param[in]     readMask         Mask to check the read back value.
 *  \return        kCanTrue         RamCheck failed.
 *  \return        kCanFalse        RamCheck passed.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_SetOsValue16(CAN_CHANNEL_CANTYPE_FIRST uint16 area, CanChipMsgPtr16 regPtr, uint16 value, uint16 readMask);


/************************************************************************************************************
 *  CanHL_InitBegin()
 ***********************************************************************************************************/
/*! \brief         Start Initialization
 *  \details       LL implementation see token CanLL_InitBegin description.
 *                 Called by Can_InitController().
 *  \param[in]     initInfo          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitBegin(CanInitInfoPtrType initInfo);

#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_InitTxFullCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize TX FullCAN
 *  \details       LL implementation see token CanLL_InitTxObj description.
 *                 Called by Can_InitController().
 *  \param[in]     initInfo          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitTxFullCAN(CanInitInfoPtrType initInfo);
#endif

/************************************************************************************************************
 *  CanHL_InitTxBasicCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize TX BasicCAN
 *  \details       LL implementation see token CanLL_InitTxObj description.
 *                 Called by Can_InitController().
 *  \param[in]     initInfo          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitTxBasicCAN(CanInitInfoPtrType initInfo);


#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_InitRxFullCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize RX FullCAN
 *  \details       LL implementation see token CanLL_InitFullCANObj description.
 *                 Called by Can_InitController().
 *  \param[in]     initInfo          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitRxFullCAN(CanInitInfoPtrType initInfo);
#endif

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_InitRxBasicCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize RX BasicCAN
 *  \details       LL implementation see token CanLL_InitBasicCANObj description.
 *                 Called by Can_InitController().
 *  \param[in]     initInfo          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitRxBasicCAN(CanInitInfoPtrType initInfo);
#endif

/************************************************************************************************************
 *  CanHL_InitEnd_InitMode()
 ***********************************************************************************************************/
/*! \brief         End Initialization
 *  \details       LL implementation see token CanLL_InitEnd_InitMode description.
 *                 Called by Can_InitController().
 *  \param[in]     initInfo          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitEnd_InitMode(CanInitInfoPtrType initInfo);

/************************************************************************************************************
 *  CanHL_InitEnd_StopMode()
 ***********************************************************************************************************/
/*! \brief         Transition to STOP
 *  \details       LL implementation see token CanLL_InitEnd_StopMode description.
 *                 Called by Can_InitController().
 *  \param[in]     initInfo          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitEnd_StopMode(CanInitInfoPtrType initInfo);

/************************************************************************************************************
 *  CanHL_StopReinit()
 ***********************************************************************************************************/
/*! \brief         Reinitialization after STOP
 *  \details       LL implementation see token CanLL_StopReinit description.
 *                 Called by Can_InitController().
 *  \param[in]     Controller    CAN controller.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_StopReinit(CAN_HW_CHANNEL_CANTYPE_ONLY);

/************************************************************************************************************
 *  CanHL_InitPowerOn()
 ***********************************************************************************************************/
/*! \brief         Power on initialization
 *  \details       LL implementation see token CanLL_InitPowerOn description.
 *                 Called by Can_InitController().
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_InitPowerOn(void);

/************************************************************************************************************
 *  CanHL_InitPowerOnChannelSpecific()
 ***********************************************************************************************************/
/*! \brief         Power on channel initialization
 *  \details       LL implementation see token CanLL_InitPowerOnChannelSpecific description.
 *                 Called by Can_Init().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_InitPowerOnChannelSpecific(CAN_CHANNEL_CANTYPE_ONLY);

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_RxBasicMsgReceivedBegin()
 ***********************************************************************************************************/
/*! \brief         RX BasicCAN start
 *  \details       RX BasicCAN handling start.
 *                 Called by CanBasicCanMsgReceived().
 *  \param[in]     rxBasicInfo          include controller and all LL specific settings.
 *  \return        CAN_NOT_OK      reception failed.
 *  \return        CAN_OK          reception successful.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_RxBasicMsgReceivedBegin(CanRxBasicInfoPtrType rxBasicInfo);

/************************************************************************************************************
 *  CanHL_RxBasicMsgReceivedSearch()
 ***********************************************************************************************************/
/*! \brief         RX BasicCAN search
 *  \details       RX BasicCAN search logical HRH from hardware hwRxHandle.
 *                 Called by CanBasicCanMsgReceived().
 *  \param[out]    rxBasicInfo          include Hrh, controller and all LL specific settings.
 *  \return        CAN_NOT_OK      reception failed.
 *  \return        CAN_OK          reception successful.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_RxBasicMsgReceivedSearch(CanRxBasicInfoPtrType rxBasicInfo);

/************************************************************************************************************
 *  CanHL_RxBasicMsgReceivedEnd()
 ***********************************************************************************************************/
/*! \brief         RX BasicCAN end
 *  \details       RX BasicCAN handling end.
 *                 Called by CanBasicCanMsgReceived().
 *  \param[in]     rxBasicInfo          include controller and all LL specific settings.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxBasicMsgReceivedEnd(CanRxBasicInfoPtrType rxBasicInfo);

# if defined(C_ENABLE_RX_BASICCAN_POLLING) /* COV_CAN_RX_BASICCAN_POLLING */
/************************************************************************************************************
 *  CanHL_RxBasicMsgReceivePolling()
 ***********************************************************************************************************/
/*! \brief         RX BasicCAN polling
 *  \details       RX BasicCAN polling handling.
 *                 Called by Can_MainFunctionRead().
 *  \param[in]     Controller    CAN controller.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxBasicMsgReceivePolling(CAN_HW_CHANNEL_CANTYPE_ONLY);
# endif
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_RxFullMsgReceivedBegin()
 ***********************************************************************************************************/
/*! \brief         RX FullCAN start
 *  \details       RX FullCAN handling start.
 *                 Called by CanFullCanMsgReceived().
 *  \param[in]     rxFullInfo          include controller and all LL specific settings.
 *  \return        CAN_NOT_OK      reception failed.
 *  \return        CAN_OK          reception successful.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_RxFullMsgReceivedBegin(CanRxFullInfoPtrType rxFullInfo);

/************************************************************************************************************
 *  CanHL_RxFullMsgReceivedSearch()
 ***********************************************************************************************************/
/*! \brief         RX FullCAN search
 *  \details       RX FullCAN search logical HRH from hardware hwTxHandle.
 *                 Called by CanFullCanMsgReceived().
 *  \param[out]    rxFullInfo          include HRH, controller and all LL specific settings.
 *  \return        CAN_NOT_OK      reception failed.
 *  \return        CAN_OK          reception successful.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_RxFullMsgReceivedSearch(CanRxFullInfoPtrType rxFullInfo);

/************************************************************************************************************
 *  CanHL_RxFullMsgReceivedEnd()
 ***********************************************************************************************************/
/*! \brief         RX FullCAN end
 *  \details       RX FullCAN handling end.
 *                 Called by CanFullCanMsgReceived().
 *  \param[in]     rxFullInfo          include controller and all LL specific settings.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxFullMsgReceivedEnd(CanRxFullInfoPtrType rxFullInfo);

# if defined(C_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
/************************************************************************************************************
 *  CanHL_RxFullMsgReceivePolling()
 ***********************************************************************************************************/
/*! \brief         RX FullCAN polling
 *  \details       RX FullCAN polling handling.
 *                 Called by Can_MainFunctionRead().
 *  \param[in]     Controller    CAN controller.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxFullMsgReceivePolling(CAN_HW_CHANNEL_CANTYPE_ONLY);
# endif
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_RxMsgReceivedNotification()
 ***********************************************************************************************************/
/*! \brief         RX notification
 *  \details       RX queue and notification handling for BasicCAN and FullCAN reception.
 *                 Called by CanBasicCanMsgReceived(),CanFullCanMsgReceived().
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxInfo          include controller and all LL specific settings.
 *  \return        errorId         error identifier reporting to DET
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_RxMsgReceivedNotification(CAN_CHANNEL_CANTYPE_FIRST CanRxInfoPtrType rxInfo);
#endif

#if defined(C_ENABLE_RX_QUEUE)
/************************************************************************************************************
 *  CanHL_RxQueueExecution()
 ***********************************************************************************************************/
/*! \brief         RX queue
 *  \details       RX queue execution and notification.
 *                 Called by Can_MainFunction_Read().
 *  \return        errorId         error identifier reporting to DET
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_RxQueueExecution(void);
#endif

/************************************************************************************************************
 *  CanHL_TxConfirmation()
 ***********************************************************************************************************/
/*! \brief         TX Confirmation handling
 *  \details       Called for a transmit or cancel event. Finish transmission by free send mailbox and call confirmation. \n
 *                 Called for FullCAN and BasicCAN handling.
 *  \param[in]     Controller    CAN controller. \n
 *                               (only if not using "Optimize for one controller")
 *  \param[in]     txObjHandle   transmit hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_TxConfirmation(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle);

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/************************************************************************************************************
 *  CanBasicCanMsgReceived()
 ***********************************************************************************************************/
/*! \brief         Handle reception
 *  \details       Receive BasicCAN data and call indication function.
 *  \param[in]     Controller    CAN controller. \n
 *                               (only if not using "Optimize for one controller")
 *  \param[in]     rxObjHandle   received hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle);
#endif

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
/************************************************************************************************************
 *  CanFullCanMsgReceived()
 ***********************************************************************************************************/
/*! \brief         Handle reception
 *  \details       Receive FullCAN data and call indication function.
 *  \param[in]     Controller    CAN controller. \n
 *                               (only if not using "Optimize for one controller")
 *  \param[in]     rxObjHandle   received hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanFullCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle);
#endif

/************************************************************************************************************
 *  CanHL_ErrorHandling()
 ***********************************************************************************************************/
/*! \brief         BUSOFF handling
 *  \details       Handler for bus off situation.
 *  \param[in]     Controller    CAN controller. \n
 *                               (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_ErrorHandling(CAN_HW_CHANNEL_CANTYPE_ONLY);


#if defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING TX */
/************************************************************************************************************
 *  CanHL_TxTaskConfPendingHandling()
 ***********************************************************************************************************/
/*! \brief         Tx task confirmation
 *  \details       Tx task handle the pending mailboxes.
 *                 Called by Can_MainFunction_Write().
 *  \param[in]     Controller    CAN controller. \n
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_TxTaskConfPendingHandling(CAN_HW_CHANNEL_CANTYPE_ONLY);
#endif

#if defined(C_ENABLE_CANCEL_TX_IN_HW) 
#endif

#define CAN_STOP_SEC_STATIC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define CAN_START_SEC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
/************************************************************************************************************
 *  Can_InitController()
 ***********************************************************************************************************/
/*! \brief         Initialization of controller specific CAN hardware.
 *  \details       The CAN driver registers and variables are initialized. \n
 *                 The CAN controller is fully initialized and left back within the state "STOP Mode", ready to change to "Running Mode".
 *  \param[in]     Controller            CAN controller
 *  \param[in]     ControllerConfigPtr   Pointer to the configuration data structure.
 *  \pre           Disabled Interrupts.
 *  \pre           Can_Init() has to be called.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         Has to be called during the start up sequence before CAN communication takes place. \n
 *                 Must not be called while in "SLEEP Mode".
***********************************************************************************************************/
V_DEF_FUNC(V_NONE, void, CODE) Can_InitController( uint8 Controller, Can_ControllerConfigPtrType ControllerConfigPtr );
#endif

#define CAN_STOP_SEC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* CAN_LOCAL_H */

/* End of channel */



/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 120 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 120 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 120 */

/************   Organi, Version 3.9.2 Vector-Informatik GmbH  ************/
