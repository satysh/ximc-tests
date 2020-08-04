#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ximc.h>

int main (int argc, char* argv[])
{
/*
	Variables declaration.
	device_t, status_t, engine_settings_t, status_calb and calibration_t are types provided by the libximc library.
*/
	device_t device;
	result_t result;
	int names_count;
	char device_name[256];
	const int probe_flags = ENUMERATE_PROBE;
	const char* enumerate_hints = "";
	char ximc_version_str[32];
	device_enumeration_t devenum;

// unused variables
	(void)argc;
	(void)argv;

	printf( "This is a ximc test program.\n" );
//	ximc_version returns library version string.
	ximc_version( ximc_version_str );
	printf( "libximc version %s\n", ximc_version_str );

//	Device enumeration function. Returns an opaque pointer to device enumeration data.
	devenum = enumerate_devices( probe_flags, enumerate_hints );

//	Gets device count from device enumeration data
	names_count = get_device_count( devenum );

//	Terminate if there are no connected devices
	if (names_count <= 0)
	{
		printf( "No devices found\n" );
	//	Free memory used by device enumeration data
		free_enumerate_devices( devenum );
		return 1;
	}
    
    int device_index=0; // You can change device here

//	Copy found device name into a string
	strcpy( device_name, get_device_name( devenum, device_index ) );
//	Free memory used by device enumeration data
	free_enumerate_devices( devenum );

	printf( "Opening device...");
//	Open device by device name
	device = open_device( device_name );
	printf( "done.\n" );

//  Get device info 
    device_information_t device_information;
    memset((void*)&device_information, 0, sizeof(device_information));
    get_device_information(device, &device_information); 
    printf("Производитель: %s\n", device_information.Manufacturer);
    printf("Идентификатор производителя: %s\n", device_information.ManufacturerId);
    printf("Описание продукта: %s\n", device_information.ProductDescription);
    printf("Основной номер версии железа: %d\n", device_information.Major);
    printf("Второстепенный номер версии железа: %d\n", device_information.Minor);
    printf("Номер правок этой версии железа: %d\n", device_information.Release);

	printf( "Closing device..." );
//	Close specified device
	close_device( &device );
	printf( "done.\n" );

	return 0;
}
