#pragma once

#ifndef _HID_TRANSPORT_H_
#define _HID_TRANSPORT_H_

#include "DataTransport.hpp"
#include "hidapi/hidapi.h"

class HIDTransport : public DataTransport {
	// Inherited via DataTransport
	int Start() override;
	void Stop() override;
	bool IsConnected() override;
	int ReadPacket(uint8_t* buffer, size_t length) override;

private:
	hid_device* hHID;
	bool HIDInit = false;
	bool HIDConnected = false;
};

#endif
