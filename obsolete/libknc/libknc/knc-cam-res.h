#ifndef __KNC_CAM_H__
#define __KNC_CAM_H__

typedef enum {
	KNC_CAM_OK					= 0x0000,
	KNC_CAM_ERR_FOCUS				= 0x0101,
	KNC_CAM_ERR_IRIS				= 0x0102,
	KNC_CAM_ERR_STROBE				= 0x0201,
	KNC_CAM_ERR_EEPROM				= 0x0203,
	KNC_CAM_ERR_INTERNAL_1				= 0x0205,
	KNC_CAM_ERR_INTERNAL_2				= 0x0206,
	KNC_CAM_ERR_NO_CARD				= 0x0301,
	KNC_CAM_ERR_CARD_NOT_SUPPORTED			= 0x0311,
	KNC_CAM_ERR_CARD_REMOVED			= 0x0321,
	KNC_CAM_ERR_INVALID_IMAGE_NUMBER		= 0x0340,
	KNC_CAM_ERR_CARD_CANNOT_BE_WRITTEN		= 0x0341,
	KNC_CAM_ERR_CARD_WRITE_PROTECTED		= 0x0381,
	KNC_CAM_ERR_NO_SPACE_LEFT_ON_CARD		= 0x0382,
	KNC_CAM_ERR_IMAGE_PROTECTED			= 0x0390,
	KNC_CAM_ERR_LIGHT_TOO_DARK			= 0x0401,
	KNC_CAM_ERR_AUTOFOCUS				= 0x0402,
	KNC_CAM_ERR_SYSTEM				= 0x0501,
	KNC_CAM_ERR_ILLEGAL_PARAMETER			= 0x0800,
	KNC_CAM_ERR_CMD_CANNOT_BE_CANCELLED		= 0x0801,
	KNC_CAM_ERR_INVALID_SIZE_OF_IMAGE_ID		= 0x0810,
	KNC_CAM_ERR_LOCALIZATION_DATA_TOO_LONG		= 0x0b00,
	KNC_CAM_ERR_LOCALIZATION_DATA_CORRUPT		= 0x0bff,
	KNC_CAM_ERR_UNSUPPORTED_CMD			= 0x0c01,
	KNC_CAM_ERR_OTHER_CMD_EXECUTING			= 0x0c02,
	KNC_CAM_ERR_CMD_ORDER_ERROR			= 0x0c03,
	KNC_CAM_ERR_UNKNOWN_ERROR			= 0xffff
} KncCamRes;

const char *knc_cam_res_name (KncCamRes);

#endif
