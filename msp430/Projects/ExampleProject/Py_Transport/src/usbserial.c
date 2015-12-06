#include "usbserial.h"


// Global flags set by events
volatile uint8_t bCDCDataReceived_event = FALSE;  // Flag set by event handler to 
                                               // indicate data has been 
                                               // received into USB buffer


/*  
 * ======== UNMI_ISR ========
 */
#if defined(__TI_COMPILER_VERSION__) || (__IAR_SYSTEMS_ICC__)
#pragma vector = UNMI_VECTOR
__interrupt void UNMI_ISR (void)
#elif defined(__GNUC__) && (__MSP430__)
void __attribute__ ((interrupt(UNMI_VECTOR))) UNMI_ISR (void)
#else
#error Compiler not found!
#endif
{
    switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG ))
    {
        case SYSUNIV_NONE:
            __no_operation();
            break;
        case SYSUNIV_NMIIFG:
            __no_operation();
            break;
        case SYSUNIV_OFIFG:
            UCS_clearFaultFlag(UCS_XT2OFFG);
            UCS_clearFaultFlag(UCS_DCOFFG);
            SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
            break;
        case SYSUNIV_ACCVIFG:
            __no_operation();
            break;
        case SYSUNIV_BUSIFG:
            // If the CPU accesses USB memory while the USB module is
            // suspended, a "bus error" can occur.  This generates an NMI.  If
            // USB is automatically disconnecting in your software, set a
            // breakpoint here and see if execution hits it.  See the
            // Programmer's Guide for more information.
            SYSBERRIV = 0; // clear bus error flag
            USB_disable(); // Disable
    }
}


uint16_t checkUSB(char * buf)
{
	uint8_t ReceiveError = 0, SendError = 0;
        uint16_t count;
        // Check the USB state and directly main loop accordingly
        switch (USB_getConnectionState())
        {
            // This case is executed while your device is enumerated on the
            // USB host
            case ST_ENUM_ACTIVE:
                if (bCDCDataReceived_event){
                
                    // Clear flag early -- just in case execution breaks
                    // below because of an error
                    bCDCDataReceived_event = FALSE;

                    count = USBCDC_receiveDataInBuffer((uint8_t*)buf,
                        BUFFER_SIZE,
                        CDC0_INTFNUM);

                    // Count has the number of bytes received into dataBuffer
                    // Echo back to the host.
                    if (USBCDC_sendDataInBackground((uint8_t*)buf,
                            count, CDC0_INTFNUM, 1)){
                        // Exit if something went wrong.
                        SendError = 0x01;
                        break;
                    }
                }
                break;
            default:;
        }

        if (ReceiveError || SendError){
            // TO DO: User can place code here to handle error
        }
}

uint16_t SendBuffer(char *buf,uint16_t length )
{
	uint8_t ReceiveError = 0, SendError = 0;
        uint16_t count;
        // Check the USB state and directly main loop accordingly
        switch (USB_getConnectionState())
        {
            // This case is executed while your device is enumerated on the
            // USB host
            case ST_ENUM_ACTIVE:
            	if (USBCDC_sendDataAndWaitTillDone((uint8_t*)buf, length, CDC0_INTFNUM, 1))
		{
                        SendError = 0x01;
                        break;
                }
                break;
            default:;
        }

        if (ReceiveError || SendError){
            // TO DO: User can place code here to handle error
        }

	return 0;
}

uint16_t ReceiveBuffer(char *buf)
{
	uint8_t ReceiveError = 0, SendError = 0;
        uint16_t count = 0;
        // Check the USB state and directly main loop accordingly
        switch (USB_getConnectionState())
        {
            case ST_ENUM_ACTIVE:
                if (bCDCDataReceived_event){
                
                    // Clear flag early -- just in case execution breaks
                    // below because of an error
                    bCDCDataReceived_event = FALSE;

                    count = USBCDC_receiveDataInBuffer((uint8_t*)buf,
                        64,
                        CDC0_INTFNUM);

                }
                break;
            default:;
        }

        if (ReceiveError || SendError){
            // TO DO: User can place code here to handle error
        }
	
	return count;
}
