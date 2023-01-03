#include "HomeKitAccessory.h"
#include <Arduino.h>

static int identify(hap_acc_t *ha)
{
	return HAP_SUCCESS;
}

static int read(hap_char_t *hc, hap_status_t *status_code, void *serv_priv, void *read_priv)
{
	return HAP_SUCCESS;
}

static int write(hap_write_data_t write_data[], int count, void *serv_priv, void *write_priv)
{
	return HAP_SUCCESS;
}

hap_serv_t *HomeKitAccessory::create_temperature_service()
{
	/* Create the Temperature Service. Include the "name" since this is a user visible service  */
	hap_serv_t *service = hap_serv_temperature_sensor_create(0);
	this->temperatureCharacteristic = hap_char_name_create("Temperature");
	hap_serv_add_char(service, temperatureCharacteristic);

	hap_serv_set_write_cb(service, write);
	hap_serv_set_read_cb(service, read);

	return service;
}

hap_acc_t *HomeKitAccessory::create_accessory()
{
	hap_acc_cfg_t cfg = {
		.name = "Temperature sensor",
		.model = "DS18B20",
		.manufacturer = "Loic Morvan",
		.serial_num = "112233445566",
		.fw_rev = "0.0.1",
		.hw_rev = NULL,
		.pv = "1.1.0",
		.cid = HAP_CID_SENSOR,
		.identify_routine = identify,
	};

	hap_acc_t *accessory = hap_acc_create(&cfg);

	/* Add a dummy Product Data */
	uint8_t product_data[] = {'E', 'S', 'P', '3', '2', 'K', 'I', 'T'};
	hap_acc_add_product_data(accessory, product_data, sizeof(product_data));

	hap_serv_t *service = create_temperature_service();
	hap_acc_add_serv(accessory, service);

	return accessory;
}

HomeKitAccessory::HomeKitAccessory()
{
	hap_cfg_t hap_cfg;
	hap_get_config(&hap_cfg);
	hap_cfg.unique_param = UNIQUE_NAME;
	hap_set_config(&hap_cfg);

	hap_init(HAP_TRANSPORT_WIFI);

	auto accessory = create_accessory();
	hap_add_accessory(accessory);

	Serial.write("Accessory is paired with num controllers: ");
	Serial.println(hap_get_paired_controller_count());

	hap_set_setup_code("111-22-333");
	hap_set_setup_id("TEMP");

	hap_start();
}

void HomeKitAccessory::SetTemperature(const float &value)
{
	hap_val_t val = {
		.f = value,
	};

	hap_char_update_val(temperatureCharacteristic, &val);
}
