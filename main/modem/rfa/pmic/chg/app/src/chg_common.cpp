/*! \file 
 *  \n
 *  \brief  chg_common.cpp ---- COMMON DEFINITION
 *  \n
 *  \details This header file contains various definitions that are commonly used 
 *  throughout the charger application
 *  \n
 *  \n &copy; Copyright 2007, 2008, 2009 QUALCOMM Incorporated, All Rights Reserved
 */


/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //source/qcom/qct/modem/rfa/pmic/chg_task/main/latest/app/src/chg_common.cpp#12 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/17/09   hs      Removed chg_general_status.
                   Fixed the bug in chg_get_general_status().
07/30/09   hs      Added support for providing general charging status.
                   Removed chg_get_charging_status()
06/60/09   hs      Integrated the vbatt task interface for the battery alarm
                   status.
06/09/09   hs      Added support for unit test.
06/03/09   hs      Removed chg_auto_charging_use_pulse_charger
04/15/09   hs      Added a secure code for Divided-by-Zero in 
                   chg_get_parameter_level().
04/03/09   hs      Added support for unit tests.
03/26/09   hs      Removed support for software controlled charging.
11/19/08   hs      Modified the code that reads the ADC values for charging current.
06/25/08   hs      Added support for autonomous charging.
06/12/08   hs      Added FEATURE_CHG_TASK.
04/16/08   hs      Included "chg_factory.h"
                   Added definitions for 4 charging UI APIs.
06/13/07   hs      Created.

========================================================================== */
#include "customer.h"                  /* FEATURE definitions    */

#if defined(FEATURE_CHG_TASK) || defined(T_WINNT)

#include "chg_common.h"
#include "charger.h"            /* For chg_get_charging_status()           */
#include "assert.h"             /* For ASSERT()                            */
#ifdef T_WINNT
#error code not present
#endif
#include "msg.h"                /* For MSG_ERROR                           */
#include "chg_evt.h"            /* For class ChargerEventListener          */
#include "chg_system.h"         /* For class SystemSystemEvent             */
#include "chg_factory.h"        /* For class ChargingFactory               */
#include "chg_autocharging.h"    /* For class AutoChargingManager          */
#include "chg_isr.h"
#ifdef __cplusplus
extern "C"
{
#endif /* end __cplusplus */ 

#ifdef T_WINNT
#error code not present
#else
#include "adc.h"                /* For adc_read()                           */
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif /* end __cplusplus */

/*===========================================================================

                            LOCAL VARIABLES

===========================================================================*/
/* Which level of debug information should we print. */
static chg_debug_inf_type      chg_debug_inf    = CHG_DEBUG_INF_NONE;
/*===========================================================================

                            GLOBAL VARIABLES

===========================================================================*/
/*!  Save if NV is set to enable or disable USB charging.         */
/* When it's 0, disable USB charging                              */
/* When it's 1, enable USB charging                               */
chg_cmd_type                   chg_usb_OnOff_nv_item_val  = CHG_CMD_DISABLE;
/*!  Used to save IMAXSEL setting for USB charging.               */
chg_usb_imaxsel_type           chg_usb_imaxsel   = {0,PM_CHG_UCHG_Q_IMAX_INVALID};
/*! What type of USB OTG device we have. */
pm_app_otg_a_dev_type          chg_usb_otg_dev   = PM_APP_OTG_A_DEV_TYPE__INVALID;
/*! \brief Used to hold the system TX information 
 *  \details This variable will be used to hold the system TX information, such as
 *  TX ON status, TX_WAIT voter ID. 
 */
chg_tx_wait_vote_info_type     chg_system_tx_informaton = {CHG_TX_VOTE__INVALID,
                                                         FALSE};
#ifdef FEATURE_VBATT_TASK /* FEATURE_VBATT_TASK */ 
pm_batt_index                  chg_handle_lwr = 0;
pm_batt_index                  chg_handle_upr = 0; 
#endif /* FEATURE_VBATT_TASK */ 

/*===========================================================================

                         LOCAL FUNCTION PROTOTYPES

===========================================================================*/

chg_plvl_rtn_type chg_get_parameter_level(chg_parameter_type parm)
{
  adc_result_type           Adc_Volt;
  chg_plvl_rtn_type         rtnValue = 0;
  adc_error_return_type     adcError = ADC_ERR_FLAG__SUCCESS;  
  adc_logical_channel_type  channel;
  pm_err_flag_type          pmError = PM_ERR_FLAG__SUCCESS;
  int32                     v_cal = 0;
  int32                     v_imon = 0;
  Adc_Volt.mV = 0;

  switch ( parm )
  {
      case CHG_PARAMETER__BATTERY_VOLT:    
          channel =  ADC_VBATT_MV;                                    
          /* Get the Battery Voltage. */
          adcError = adc_read_channel(channel, &Adc_Volt);
          
          #if defined(CHG_DEBUG__OVER_WRITE_PARAMETERS)
#error code not present
          #else
          rtnValue = (chg_plvl_rtn_type)Adc_Volt.mV;
          #endif
          
          break;
       
  case CHG_PARAMETER__WALL_CHARGER_VOLT:
          channel = ADC_VCHG_MV;
          /* Get the Charger Voltage. */
          adcError = adc_read_channel(channel, &Adc_Volt);

          #if defined(CHG_DEBUG__OVER_WRITE_PARAMETERS)
#error code not present
          #else
          rtnValue = (chg_plvl_rtn_type)(Adc_Volt.mV);
          #endif
          
          break;

  case CHG_PARAMETER__USB_CHARGER_VOLT:

          channel =  ADC_USB_VBUS_MV;                                    

          /* Get USB Charger Voltage. */
          //lint --e{655} suppress "bit-wise operation uses (compatible) enum's"
          adcError = adc_read_channel(channel, &Adc_Volt);

          #if defined(CHG_DEBUG__OVER_WRITE_PARAMETERS)
#error code not present
          #else
          rtnValue = (chg_plvl_rtn_type)Adc_Volt.mV;
          #endif
          
          break;

  case CHG_PARAMETER__VPH_PWR_VOLT:
          channel = ADC_ICHG_OUT_MV;
          /* Get the VPH POWER Voltage. */
          adcError = adc_read_channel(channel, &Adc_Volt);
          rtnValue = (chg_plvl_rtn_type)Adc_Volt.mV;          
          break;

  case CHG_PARAMETER__CHARGER_I:
          channel = ADC_ICHG_MV;

        #ifdef T_WINNT
#error code not present
        #else
          /* Set IMON CAL to 12.5V/A */
          pmError |= pm_chg_imon_cal_set(1);
          /* Get the charger current voltage */
          adcError = adc_read_channel(channel, &Adc_Volt);
          v_cal = (chg_plvl_rtn_type)Adc_Volt.mV;

          if(v_cal != 0)
          {
              /* Set IMON CAL to 1.25V/A */
              pmError |= pm_chg_imon_cal_set(0);
              /* Get the charger current voltage */
              adcError = adc_read_channel(channel, &Adc_Volt);
              v_imon = (chg_plvl_rtn_type)Adc_Volt.mV;

              #if defined(CHG_DEBUG__OVER_WRITE_PARAMETERS)
#error code not present
              #else
              rtnValue = (chg_plvl_rtn_type)((1000*v_imon)/v_cal);          
              #endif
#ifdef CUST_EDITION
              rtnValue = (rtnValue == 1000) ? 0 : rtnValue;
#endif			  
          }
          else
          {
              rtnValue = 0;
          }
        #endif /* T_WINNT */
          
          
          break;

  case CHG_PARAMETER__BATTERY_ID:
          channel = ADC_BATT_ID_MV;
          /* Get the Battery ID. */
          adcError = adc_read_channel(channel, &Adc_Volt);
          
          #if defined(CHG_DEBUG__OVER_WRITE_PARAMETERS)
#error code not present
          #else
          rtnValue = (chg_plvl_rtn_type)Adc_Volt.mV;          
          #endif
          
          break;

  case CHG_PARAMETER__BATT_THERM_DEGC:
          channel = ADC_BATT_THERM_DEGC;
          /* Get the battery temperature. */
          adcError = adc_read_channel(channel, &Adc_Volt);
          rtnValue = (chg_plvl_rtn_type)Adc_Volt.degC;   
          break;

  case CHG_PARAMETER__CHG_THERM_DEGC:
          /* Get the charger Q temperature. */
          #ifndef FEATURE_BATTERY_CHARGER_NO_CHG_Q_THERMISTOR
          channel = ADC_CHG_THERM_DEGC;
          #else
          channel = ADC_BATT_THERM_DEGC;
          #endif
          adcError = adc_read_channel(channel, &Adc_Volt);
          rtnValue = (chg_plvl_rtn_type)Adc_Volt.degC;          
          break;

      case CHG_PARAMETER__DUMMY_READ:          
          /* Make sure that the ADC has a least one 
             good reading. */
          /* Get the Battery Voltage. */
          channel = ADC_VBATT_MV;
          adcError =  adc_read_channel(channel, &Adc_Volt);
          /* Get the Charger Voltage. */
          channel = ADC_VCHG_MV;
          adcError = adc_read_channel(channel, &Adc_Volt);
          /* Get the VPH POWER Voltage. */
          channel = ADC_ICHG_OUT_MV;
          adcError = adc_read_channel(channel, &Adc_Volt);
          /* Get the Charger Current. */
          channel = ADC_ICHG_MV;
          adcError = adc_read_channel(channel, &Adc_Volt);
          /* Get the Battery ID. */
          channel = ADC_BATT_ID_MV;
          adcError = adc_read_channel(channel, &Adc_Volt);
          /* Get the battery temperature. */
          channel = ADC_BATT_THERM_DEGC;
          adcError = adc_read_channel(channel, &Adc_Volt);
          /* Get the charger Q temperature. */
          #ifndef FEATURE_BATTERY_CHARGER_NO_CHG_Q_THERMISTOR
          channel = ADC_CHG_THERM_DEGC;
          adcError = adc_read_channel(channel, &Adc_Volt);
          #endif

          /* Return dummy data. */
          rtnValue = (chg_plvl_rtn_type)Adc_Volt.mV;
          break;      

      default:
          MSG_ERROR("CHG: Invalid parameter = %d",parm,0,0);          
          break;
  }

  /* Inform that an ADC error was detected */
  if (adcError != ADC_ERR_FLAG__SUCCESS)
  {
      MSG_ERROR("CHG: ADC ERROR(sig=%d,val=%d,err=%d).", \
                                                   parm, rtnValue, adcError);
  }

  /* Find out if there was an PMIC API error. */
  if (pmError != PM_ERR_FLAG__SUCCESS) 
  {
      MSG_ERROR("PMIC API ERROR(0x%x).",pmError,0,0);
  }

  return rtnValue;
} /* end chg_get_parameter_level */

void chg_tx_wait_vote(chg_cmd_type cmd, chg_tx_wait_voter_type voter)
{

    if(cmd >= CHG_CMD_INVALID)
    {
        ASSERT(false);
    }

    if( voter >= CHG_TX_VOTE__INVALID)
    {
        ASSERT(false);
    }

    /* Update information */
    chg_system_tx_informaton.voter_id = voter;

    void* data = (void*)voter;

    SystemEventGenerator *systemEventGenerator = ChargingFactory::GetSystemEventGenerator();
    systemEventGenerator->TxWaitVote(cmd, data);
}

void chg_usb_charger_switch(chg_cmd_type cmd)
{   
    chg_usb_irq_switch(cmd); 
} /* chg_usb_charger_switch() */

void chg_charging_ftm_switch(chg_cmd_type cmd)
{
    if(cmd >= CHG_CMD_INVALID)
    {
        ASSERT(false);
    }

    SystemEventGenerator *systemEventGenerator = ChargingFactory::GetSystemEventGenerator();
    systemEventGenerator->FtmChargingSwitch(cmd);
} /* chg_charging_ftm_switch() */

void chg_auto_charging_switch(chg_cmd_type cmd)
{
    if(cmd >= CHG_CMD_INVALID)
    {
        ASSERT(false);
    }

    SystemEventGenerator *systemEventGenerator = ChargingFactory::GetSystemEventGenerator();
    systemEventGenerator->AutoChargingSwitch(cmd);
} /* chg_auto_charging_switch() */


chg_debug_inf_type chg_get_debug_state(void)
{
    return chg_debug_inf;
}

void chg_set_debug_state(chg_debug_inf_type cmd)
{
    chg_debug_inf = cmd;
}

boolean chg_is_charging(void)
{
    return ChargingFactory::GetAutoChargingManager()->IsCharging();
}

boolean chg_is_charger_valid(void)
{
    return ChargingFactory::GetAutoChargingManager()->IsChargerValid();
}

boolean chg_is_battery_valid(void)
{
    return ChargingFactory::GetAutoChargingManager()->IsBatteryValid();
}

chg_ui_event_type chg_ui_event_read(void)
{
    return ChargingFactory::GetAutoChargingManager()->GetUiEvent();
}

#ifdef FEATURE_VBATT_TASK 
void chg_vbatt_upr_thr_cb ( void * )
{
    #if defined(FEATURE_CHG_TASK_USE_PULSE_TOPOFF) || defined(FEATURE_CHG_TASK_USE_CV_TOPOFF) || defined(T_WINNT)
    /* Inform the IRQ event generator that battery alarm upper threshold IRQ triggered. */
    IrqEventGenerator *irqEventGenerator = ChargingFactory::GetIrqEventGenerator();
    irqEventGenerator->VbattUpperThresholdCallback();
    #endif
}

void chg_vbatt_lwr_thr_cb ( void * )
{
    #if defined(FEATURE_CHG_TASK_USE_PULSE_TOPOFF) || defined(FEATURE_CHG_TASK_USE_CV_TOPOFF) || defined(T_WINNT)
    /* Inform the IRQ event generator that battery alarm lower threshold IRQ triggered. */
    IrqEventGenerator *irqEventGenerator = ChargingFactory::GetIrqEventGenerator();
    irqEventGenerator->VbattLowerThresholdCallback();
    #endif
}
#endif /* FEATURE_VBATT_TASK */

void chg_get_general_status(chg_general_status_type* status)
{
    ASSERT(NULL != status);

    *status = ChargingFactory::GetAutoChargingManager()->GetGeneralStatus();

    return;
}

#endif /* FEATURE_CHG_TASK || T_WINNT */
