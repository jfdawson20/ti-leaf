/* --COPYRIGHT--,BSD
 * Copyright (c) 2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/


// Generated by MSP USB Descriptor Tool: Tue Feb 03 13:27:38 CST 2015

/*-----------------------------------------------------------------------------+
| Include files                                                                |
|-----------------------------------------------------------------------------*/
#include <USB_API/USB_Common/device.h>        // Basic Type declarations
#include <USB_API/USB_Common/defMSP430USB.h>
#include "descriptors.h"
#include <USB_API/USB_Common/usb.h>           //USB-specific Data Structures
#include <USB_API/USB_Common/UsbIsr.h>
#include <string.h>
#include <USB_API/USB_HID_API/UsbHid.h>
#include <USB_API/USB_HID_API/UsbHidReq.h>

/*----------------------------------------------------------------------------+
| External Variables                                                          |
+----------------------------------------------------------------------------*/
extern uint8_t  bFunctionSuspended;
extern __no_init tEDB0 __data16 tEndPoint0DescriptorBlock;
extern __no_init tEDB __data16 tInputEndPointDescriptorBlock[];
extern __no_init tEDB __data16 tOutputEndPointDescriptorBlock[];
extern volatile uint8_t bHostAsksUSBData;
extern volatile uint8_t bTransferInProgress;
extern volatile uint8_t bSecondUartTxDataCounter[];
extern volatile uint8_t* pbSecondUartTxData;
extern uint8_t bStatusAction;
extern uint16_t wUsbEventMask;
int16_t CdcToHostFromBuffer(uint8_t);
int16_t CdcToBufferFromHost(uint8_t);
int16_t CdcIsReceiveInProgress(uint8_t);
int16_t HidToHostFromBuffer(uint8_t);
int16_t HidToBufferFromHost(uint8_t);
int16_t HidIsReceiveInProgress(uint8_t);
extern uint16_t wUsbHidEventMask;
int16_t PHDCToHostFromBuffer(uint8_t);
int16_t PHDCToBufferFromHost(uint8_t);
int16_t PHDCIsReceiveInProgress(uint8_t);
uint16_t USB_determineFreq(void);
/*----------------------------------------------------------------------------+
| General Subroutines                                                         |
+----------------------------------------------------------------------------*/
#if defined(__TI_COMPILER_VERSION__) || (__IAR_SYSTEMS_ICC__) 
#pragma vector=USB_UBM_VECTOR
__interrupt void iUsbInterruptHandler(void)
#elif defined(__GNUC__) && (__MSP430__)
void __attribute__ ((interrupt(USB_UBM_VECTOR))) iUsbInterruptHandler(void)
#endif
{
    uint8_t bWakeUp = FALSE;
//Check if the setup interrupt is pending.
    //We need to check it before other interrupts,
    //to work around that the Setup Int has lower priority then Input Endpoint 0
    if (USBIFG & SETUPIFG)
    {
        bWakeUp = SetupPacketInterruptHandler();  
#ifdef USB10_WORKAROUND
        tEndPoint0DescriptorBlock.bIEPCNFG &= ~EPCNF_UBME; // Clear ME to gate off SETUPIFG clear event
        tEndPoint0DescriptorBlock.bOEPCNFG &= ~EPCNF_UBME; // Clear ME to gate off SETUPIFG clear event
#endif
        USBIFG &= ~SETUPIFG;    // clear the interrupt bit
#ifdef USB10_WORKAROUND
        tEndPoint0DescriptorBlock.bIEPCNFG |= EPCNF_UBME; // Set ME to continue with normal operation
        tEndPoint0DescriptorBlock.bOEPCNFG |= EPCNF_UBME; // Set ME to continue with normal operation
#endif
    }   
    switch (__even_in_range(USBVECINT & 0x3f, USBVECINT_OUTPUT_ENDPOINT7))
    {
    case USBVECINT_NONE:
        break;
    case USBVECINT_PWR_DROP:
      __no_operation();
        break;
    case USBVECINT_PLL_LOCK:
        break;
    case USBVECINT_PLL_SIGNAL:
        break;
    case USBVECINT_PLL_RANGE:
        if (wUsbEventMask & USB_CLOCK_FAULT_EVENT)
        {
            bWakeUp = USB_handleClockEvent();
        }
        break;
    case USBVECINT_PWR_VBUSOn:
        PWRVBUSonHandler();
        if (wUsbEventMask & USB_VBUS_ON_EVENT)
        {
            bWakeUp = USB_handleVbusOnEvent();
        }
        break;
    case USBVECINT_PWR_VBUSOff:
        PWRVBUSoffHandler();
        if (wUsbEventMask & USB_VBUS_OFF_EVENT)
        {
            bWakeUp = USB_handleVbusOffEvent();
        }
        break;
    case USBVECINT_USB_TIMESTAMP:
        break;
    case USBVECINT_INPUT_ENDPOINT0:
        IEP0InterruptHandler();
        break;
    case USBVECINT_OUTPUT_ENDPOINT0:
        OEP0InterruptHandler();
        break;
    case USBVECINT_RSTR:
        USB_reset();
        if (wUsbEventMask & USB_RESET_EVENT)
        {
            bWakeUp = USB_handleResetEvent();
        }
        break;
    case USBVECINT_SUSR:
        USB_suspend();
        if (wUsbEventMask & USB_SUSPENDED_EVENT)
        {
            bWakeUp = USB_handleSuspendEvent();
        }
        break;
    case USBVECINT_RESR:
        USB_resume();
        if (wUsbEventMask & USB_RESUME_EVENT)
        {
            bWakeUp = USB_handleResumeEvent();
        }
        //-- after resume we will wake up! Independ what event handler says.
        bWakeUp = TRUE;
        break;
    case USBVECINT_SETUP_PACKET_RECEIVED:
        // NAK both IEP and OEP enpoints
        tEndPoint0DescriptorBlock.bIEPBCNT = EPBCNT_NAK;
        tEndPoint0DescriptorBlock.bOEPBCNT = EPBCNT_NAK;
        SetupPacketInterruptHandler();
        break;
    case USBVECINT_STPOW_PACKET_RECEIVED:
        break;
	case USBVECINT_INPUT_ENDPOINT1:
        //send saved bytes from buffer...
        bWakeUp = HidToHostFromBuffer(HID0_INTFNUM);
        break;
    case USBVECINT_INPUT_ENDPOINT2:
         break;
    case USBVECINT_INPUT_ENDPOINT3:
        break;
    case USBVECINT_INPUT_ENDPOINT4:
		break;
    case USBVECINT_INPUT_ENDPOINT5:
		break;
    case USBVECINT_INPUT_ENDPOINT6:
		break;
    case USBVECINT_INPUT_ENDPOINT7:
		break;
    case USBVECINT_OUTPUT_ENDPOINT1:
        //call callback function if no receive operation is underway
        if (!HidIsReceiveInProgress(HID0_INTFNUM))
        {
            if (wUsbEventMask & USB_DATA_RECEIVED_EVENT)
            {
                bWakeUp = USBHID_handleDataReceived(HID0_INTFNUM); 
            }
        }
        else
        {
                //complete receive opereation - copy data to user buffer
                bWakeUp = HidToBufferFromHost(HID0_INTFNUM);
        }
	    break;
    case USBVECINT_OUTPUT_ENDPOINT2:
        break;
    case USBVECINT_OUTPUT_ENDPOINT3:
        break;
    case USBVECINT_OUTPUT_ENDPOINT4:
        break;
    case USBVECINT_OUTPUT_ENDPOINT5:
        break;
    case USBVECINT_OUTPUT_ENDPOINT6:
        break;
    case USBVECINT_OUTPUT_ENDPOINT7:
        break;
    default:
        break;
    }

    if (bWakeUp)
    {
        __bic_SR_register_on_exit(LPM3_bits);   // Exit LPM0-3
        __no_operation();  // Required for debugger
    }
}
	


/*----------------------------------------------------------------------------+
| Interrupt Sub-routines                                                      |
+----------------------------------------------------------------------------*/
uint8_t SetupPacketInterruptHandler(void)
{
    uint8_t bTemp;
    uint8_t bWakeUp = FALSE;
    USBCTL |= FRSTE;      // Function Reset Connection Enable - set enable after first setup packet was received
    usbProcessNewSetupPacket:
    // copy the MSB of bmRequestType to DIR bit of USBCTL
    if((tSetupPacket.bmRequestType & USB_REQ_TYPE_INPUT) == USB_REQ_TYPE_INPUT)
    {
        USBCTL |= DIR;
    }
    else
    {
        USBCTL &= ~DIR;
    }
    bStatusAction = STATUS_ACTION_NOTHING;
    // clear out return data buffer
    for(bTemp=0; bTemp<USB_RETURN_DATA_LENGTH; bTemp++)
    {
        abUsbRequestReturnData[bTemp] = 0x00;
    }
    // decode and process the request
    bWakeUp = usbDecodeAndProcessUsbRequest();
    // check if there is another setup packet pending
    // if it is, abandon current one by NAKing both data endpoint 0
    if((USBIFG & STPOWIFG) != 0x00)
    {
        USBIFG &= ~(STPOWIFG | SETUPIFG);
        goto usbProcessNewSetupPacket;
    }
    return bWakeUp;
}

//----------------------------------------------------------------------------
void PWRVBUSoffHandler(void)
{
   uint16_t MCLKFreq = USB_determineFreq();
   uint16_t DelayConstant_250us = ((MCLKFreq >> 6) + (MCLKFreq >> 7) + (MCLKFreq >> 9));
   volatile uint16_t i, j;

    //wait 1 ms till enable USB 
    for(j = 0; j < 4; j++)
    {
        for (i = 0; i < (DelayConstant_250us); i++){
            _NOP();
        }
   }
    if (!(USBPWRCTL & USBBGVBV))
    {
        USBKEYPID   =    0x9628;        // set KEY and PID to 0x9628 -> access to configuration registers enabled
        bEnumerationStatus = 0x00;      // device is not enumerated
        bFunctionSuspended = FALSE;     // device is not suspended
        USBCNF     =    0;              // disable USB module
        USBPLLCTL  &=  ~UPLLEN;         // disable PLL
        USBPWRCTL &= ~(VBOFFIE + VBOFFIFG + SLDOEN);          // disable interrupt VBUSoff
        USBKEYPID   =    0x9600;        // access to configuration registers disabled
    }
}

//----------------------------------------------------------------------------
void PWRVBUSonHandler(void)
{
   uint16_t MCLKFreq = USB_determineFreq();
   uint16_t DelayConstant_250us = ((MCLKFreq >> 6) + (MCLKFreq >> 7) + (MCLKFreq >> 9));
   volatile uint16_t i, j;

    //wait 1 ms till enable USB 
    for(j = 0; j < 4; j++)
    {
        for (i = 0; i < (DelayConstant_250us); i++){
            _NOP();
        }
   }
    if (USBPWRCTL & USBBGVBV)                //Checking for USB Bandgap and VBUS valid before modifying USBPWRCTL
    {
        USBKEYPID =  0x9628;                // set KEY and PID to 0x9628 -> access to configuration registers enabled
        USBPWRCTL |= VBOFFIE;               // enable interrupt VBUSoff
        USBPWRCTL &= ~ (VBONIFG + VBOFFIFG);             // clean int flag (bouncing)
        USBKEYPID =  0x9600;                // access to configuration registers disabled
    }
}

//----------------------------------------------------------------------------
void IEP0InterruptHandler(void)
{
    USBCTL |= FRSTE;                              // Function Reset Connection Enable
    tEndPoint0DescriptorBlock.bOEPBCNT = 0x00;     
    if(bStatusAction == STATUS_ACTION_DATA_IN)
    {
        usbSendNextPacketOnIEP0();
    }
    else
    {
        tEndPoint0DescriptorBlock.bIEPCNFG |= EPCNF_STALL; // no more data
    }
}

//----------------------------------------------------------------------------
uint8_t OEP0InterruptHandler(void)
{
    uint8_t bWakeUp = FALSE;
    USBCTL |= FRSTE;                              // Function Reset Connection Enable
    tEndPoint0DescriptorBlock.bIEPBCNT = 0x00;    
    if(bStatusAction == STATUS_ACTION_DATA_OUT)
    {
        usbReceiveNextPacketOnOEP0();
        if(bStatusAction == STATUS_ACTION_NOTHING)
        {
#           ifdef _CDC_
                if(tSetupPacket.bRequest == USB_CDC_SET_LINE_CODING)
                {
                    bWakeUp = Handler_SetLineCoding();
                }
#          endif
#ifdef _HID_
                if (tSetupPacket.bRequest == USB_REQ_SET_REPORT) {
                    bWakeUp = USBHID_handleEP0SetReportDataAvailable(tSetupPacket.wIndex);
                }
#endif
          }
    }
    else
    {
        tEndPoint0DescriptorBlock.bOEPCNFG |= EPCNF_STALL; // no more data
    }
    return (bWakeUp);
}



/*----------------------------------------------------------------------------+
| End of source file                                                          |
+----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/	
	
//Released_Version_5_00_01
