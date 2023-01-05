#include "HomeKitAccessory.h"
#include <Arduino.h>

using namespace std::placeholders;

// TODO: Remove
static float currentTemperature;

static int identify(hap_acc_t *ha)
{
	// TODO: Find out what this is.
	return HAP_SUCCESS;
}

static int read(hap_char_t *hc, hap_status_t *status_code, void *serv_priv, void *read_priv)
{
	auto characteristic = hap_char_get_type_uuid(hc);
	if (!strcmp(characteristic, HAP_CHAR_UUID_CURRENT_TEMPERATURE))
	{
		auto cur_val = hap_char_get_val(hc);

		// TODO: Do we need that? because the characteristic is updated in SetTemperature.
		hap_val_t new_val = {
			.f = currentTemperature,
		};
		hap_char_update_val(hc, &new_val);
		*status_code = HAP_STATUS_SUCCESS;
	}

	return HAP_SUCCESS;
}

hap_serv_t *HomeKitAccessory::create_temperature_service()
{
	hap_serv_t *service = hap_serv_temperature_sensor_create(0);
	auto sensorName = hap_char_name_create("Capteur de température");
	hap_serv_add_char(service, sensorName);

	hap_serv_set_read_cb(service, read);

	return service;
}

hap_acc_t *HomeKitAccessory::create_accessory()
{
	hap_acc_cfg_t cfg = {
		.name = "Temperature sensor",
		.model = "DS18B20",
		.manufacturer = "Loïc Morvan",
		.serial_num = "112233445566",
		.fw_rev = "0.0.1",
		.hw_rev = NULL,
		.pv = "1.1.0",
		.cid = HAP_CID_SENSOR,
		.identify_routine = identify,
	};

	auto accessory = hap_acc_create(&cfg);

	/* Add a dummy Product Data */
	uint8_t product_data[] = {'E', 'S', 'P', '3', '2', 'K', 'I', 'T'};
	hap_acc_add_product_data(accessory, product_data, sizeof(product_data));

	service = create_temperature_service();
	hap_acc_add_serv(accessory, service);

	return accessory;
}

HomeKitAccessory::HomeKitAccessory()
{
	hap_cfg_t hap_cfg;
	hap_get_config(&hap_cfg);
	hap_cfg.unique_param = UNIQUE_NONE;
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
	currentTemperature = value;

	auto hc = hap_serv_get_char_by_uuid(service, HAP_CHAR_UUID_CURRENT_TEMPERATURE);
	hap_val_t new_val = {
		.f = currentTemperature,
	};
	hap_char_update_val(hc, &new_val);
}
