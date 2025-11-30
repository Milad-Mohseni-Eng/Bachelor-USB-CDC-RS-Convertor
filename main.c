// USB to Serial COnvertor



//_____  I N C L U D E S ___________________________________________________

#include "usbcdc/config.h"
#include "usbcdc/scheduler.h"
#include "usbcdc/wdt_drv.h"
#include "usbcdc/power_drv.h"
#include "usbcdc/usb_drv.h"

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________

int main(void)
{

	Usb_enable_regulator();
	wdt_reset();
	Wdt_clear_flag();
	Wdt_change_enable();
	Wdt_stop();

	Clear_prescaler();
	scheduler();
	return 0;
}

