#include "dataHandler.h"

CdataHandler::CdataHandler(DataTransport& transport)
	: dataTransport(transport)
{
}

/**
	 Reads Transport data and separates the incoming data packet into HMD, controller or tracker data.
*/
void CdataHandler::ReadTransportData()
{
	HMDQuaternionPacket* DataHMDQuat = (HMDQuaternionPacket*)packet_buffer;
	HMDRAWPacket* DataHMDRAW = (HMDRAWPacket*)packet_buffer;
	ControllerPacket* DataCtrl = (ControllerPacket*)packet_buffer;
	DriverLog("[DataTransport] Data transport Thread created, Status: %d", dataTransport.IsConnected());
	while (dataTransport.IsConnected()) {
		if (dataTransport.ReadPacket(packet_buffer, 64) > 0) {
			switch (packet_buffer[1])
			{
			case 1:		//HMD quaternion packet
				HMDData.TrackingData.RawRotation.W = DataHMDQuat->HMDQuatW;
				HMDData.TrackingData.RawRotation.X = DataHMDQuat->HMDQuatX;
				HMDData.TrackingData.RawRotation.Y = DataHMDQuat->HMDQuatY;
				HMDData.TrackingData.RawRotation.Z = DataHMDQuat->HMDQuatZ;

				HMDData.Data = DataHMDQuat->HMDData;

				TrackerWaistData.Rotation.W = (float)(DataHMDQuat->tracker1_QuatW) / 32767.f;
				TrackerWaistData.Rotation.X = (float)(DataHMDQuat->tracker1_QuatX) / 32767.f;
				TrackerWaistData.Rotation.Y = (float)(DataHMDQuat->tracker1_QuatY) / 32767.f;
				TrackerWaistData.Rotation.Z = (float)(DataHMDQuat->tracker1_QuatZ) / 32767.f;
				TrackerWaistData.vBat = (float)(DataHMDQuat->tracker1_vBat) / 255.f;

				TrackerLeftData.Rotation.W = (float)(DataHMDQuat->tracker2_QuatW) / 32767.f;
				TrackerLeftData.Rotation.X = (float)(DataHMDQuat->tracker2_QuatX) / 32767.f;
				TrackerLeftData.Rotation.Y = (float)(DataHMDQuat->tracker2_QuatY) / 32767.f;
				TrackerLeftData.Rotation.Z = (float)(DataHMDQuat->tracker2_QuatZ) / 32767.f;
				TrackerLeftData.vBat = (float)(DataHMDQuat->tracker2_vBat) / 255.f;

				TrackerRightData.Rotation.W = (float)(DataHMDQuat->tracker3_QuatW) / 32767.f;
				TrackerRightData.Rotation.X = (float)(DataHMDQuat->tracker3_QuatX) / 32767.f;
				TrackerRightData.Rotation.Y = (float)(DataHMDQuat->tracker3_QuatY) / 32767.f;
				TrackerRightData.Rotation.Z = (float)(DataHMDQuat->tracker3_QuatZ) / 32767.f;
				TrackerRightData.vBat = (float)(DataHMDQuat->tracker3_vBat) / 255.f;
				break;

			case 2:		//Controller quaternion packet
				RightCtrlData.TrackingData.RawRotation.W = (float)(DataCtrl->Ctrl1_QuatW) / 32767.f;
				RightCtrlData.TrackingData.RawRotation.X = (float)(DataCtrl->Ctrl1_QuatX) / 32767.f;
				RightCtrlData.TrackingData.RawRotation.Y = (float)(DataCtrl->Ctrl1_QuatY) / 32767.f;
				RightCtrlData.TrackingData.RawRotation.Z = (float)(DataCtrl->Ctrl1_QuatZ) / 32767.f;

				RightCtrlData.TrackingData.Accel.X = (float)(DataCtrl->Ctrl1_AccelX) / 2048.f;
				RightCtrlData.TrackingData.Accel.Y = (float)(DataCtrl->Ctrl1_AccelY) / 2048.f;
				RightCtrlData.TrackingData.Accel.Z = (float)(DataCtrl->Ctrl1_AccelZ) / 2048.f;

				
				RightCtrlData.Data = DataCtrl->Ctrl1_Data;
				RightCtrlData.Buttons = DataCtrl->Ctrl1_Buttons;

				RightCtrlData.Trigger = (float)(DataCtrl->Ctrl1_Trigger) / 255.f;
				RightCtrlData.JoyAxisX = (float)(DataCtrl->Ctrl1_axisX) / 127.f;
				RightCtrlData.JoyAxisY = (float)(DataCtrl->Ctrl1_axisY) / 127.f;
				RightCtrlData.TrackpY = (float)(DataCtrl->Ctrl1_trackY) / 127.f;
				RightCtrlData.vBat = (float)(DataCtrl->Ctrl1_vBat) / 255.f;
				RightCtrlData.FingThumb = (float)(DataCtrl->Ctrl1_THUMB) / 255.f;
				RightCtrlData.FingIndex = (float)(DataCtrl->Ctrl1_INDEX) / 255.f;
				RightCtrlData.FingMiddl = (float)(DataCtrl->Ctrl1_MIDDLE) / 255.f;
				RightCtrlData.FingRing = (float)(DataCtrl->Ctrl1_RING) / 255.f;
				RightCtrlData.FingPinky = (float)(DataCtrl->Ctrl1_PINKY) / 255.f;
				RightCtrlData.GripStrength = (float)(DataCtrl->Ctrl1_AnalogGrip) / 255.f;
				

				LeftCtrlData.TrackingData.RawRotation.W = (float)(DataCtrl->Ctrl2_QuatW) / 32767.f;
				LeftCtrlData.TrackingData.RawRotation.X = (float)(DataCtrl->Ctrl2_QuatX) / 32767.f;
				LeftCtrlData.TrackingData.RawRotation.Y = (float)(DataCtrl->Ctrl2_QuatY) / 32767.f;
				LeftCtrlData.TrackingData.RawRotation.Z = (float)(DataCtrl->Ctrl2_QuatZ) / 32767.f;
				
				LeftCtrlData.TrackingData.Accel.X = (float)(DataCtrl->Ctrl2_AccelX) / 2048.f;
				LeftCtrlData.TrackingData.Accel.Y = (float)(DataCtrl->Ctrl2_AccelY) / 2048.f;
				LeftCtrlData.TrackingData.Accel.Z = (float)(DataCtrl->Ctrl2_AccelZ) / 2048.f;
				

				LeftCtrlData.Data = DataCtrl->Ctrl2_Data;
				LeftCtrlData.Buttons = DataCtrl->Ctrl2_Buttons;

				LeftCtrlData.Trigger = (float)(DataCtrl->Ctrl2_Trigger) / 255.f;
				LeftCtrlData.JoyAxisX = (float)(DataCtrl->Ctrl2_axisX) / 127.f;
				LeftCtrlData.JoyAxisY = (float)(DataCtrl->Ctrl2_axisY) / 127.f;
				LeftCtrlData.TrackpY = (float)(DataCtrl->Ctrl2_trackY) / 127.f;
				LeftCtrlData.vBat = (float)(DataCtrl->Ctrl2_vBat) / 255.f;
				LeftCtrlData.FingThumb = (float)(DataCtrl->Ctrl2_THUMB) / 255.f;
				LeftCtrlData.FingIndex = (float)(DataCtrl->Ctrl2_INDEX) / 255.f;
				LeftCtrlData.FingMiddl = (float)(DataCtrl->Ctrl2_MIDDLE) / 255.f;
				LeftCtrlData.FingRing = (float)(DataCtrl->Ctrl2_RING) / 255.f;
				LeftCtrlData.FingPinky = (float)(DataCtrl->Ctrl2_PINKY) / 255.f;
				LeftCtrlData.GripStrength = (float)(DataCtrl->Ctrl2_AnalogGrip) / 255.f;

				receivedControllerData = true;

				if (CtrlAccelEnable) {
					UpdateIMUPosition(RightCtrlData.TrackingData, CtrlRightKalman);
					UpdateIMUPosition(LeftCtrlData.TrackingData, CtrlLeftKalman);
				}
				break;

			case 3:		//hmd IMU packet
				if (!orientationFilterInit) {		//init filter
					HMDfilter.begin();
					HMDfilter.setBeta(2.f);

					if (readsFromInit < 2000) {
						readsFromInit++;
					}
					if (readsFromInit >= 2000) {
						orientationFilterInit = true;
						ResetPos(true, true);
					}
				}			

				if (readsFromInit >= 2000) {
					float Av = Vector3::Magnitude(HMDData.TrackingData.AngularVelocity);
					if (Av > 10.f) Av = 10.f;
					HMDfilter.setBeta(Av * (maxFilterBeta - minFilterBeta) / 10 + minFilterBeta);
				}

				HMDData.TrackingData.Accel.X = (float)(DataHMDRAW->AccX) / 2048;
				HMDData.TrackingData.Accel.Y = (float)(DataHMDRAW->AccY) / 2048;
				HMDData.TrackingData.Accel.Z = (float)(DataHMDRAW->AccZ) / 2048;

				HMDData.TrackingData.AngularAccel.X = (float)(DataHMDRAW->GyroY) / 16;
				HMDData.TrackingData.AngularAccel.Y = (float)(DataHMDRAW->GyroX) / 16;
				HMDData.TrackingData.AngularAccel.Z = (float)(DataHMDRAW->GyroZ) / 16;

				//get data and scale it properly. Then update the filter.
				HMDfilter.update((float)(DataHMDRAW->GyroX / 16), (float)(DataHMDRAW->GyroY / 16), (float)(DataHMDRAW->GyroZ / 16), 
					(float)(DataHMDRAW->AccX) / 2048, (float)(DataHMDRAW->AccY) / 2048, (float)(DataHMDRAW->AccZ) / 2048,
					(float)(DataHMDRAW->MagX / 5), (float)(DataHMDRAW->MagY / 5), (float)(DataHMDRAW->MagZ / 5));

				//Apply rotation to the HMD
				HMDData.TrackingData.RawRotation = HMDfilter.getQuat();

				if (HMDAccelEnable) {
					UpdateIMUPosition(HMDData.TrackingData, HMDKalman);
				}

				HMDData.Data = DataHMDRAW->HMDData;

				TrackerWaistData.Rotation.W = (float)(DataHMDRAW->tracker1_QuatW) / 32767;
				TrackerWaistData.Rotation.X = (float)(DataHMDRAW->tracker1_QuatX) / 32767;
				TrackerWaistData.Rotation.Y = (float)(DataHMDRAW->tracker1_QuatY) / 32767;
				TrackerWaistData.Rotation.Z = (float)(DataHMDRAW->tracker1_QuatZ) / 32767;
				TrackerWaistData.vBat = (float)(DataHMDRAW->tracker1_vBat) / 255;

				TrackerLeftData.Rotation.W = (float)(DataHMDRAW->tracker2_QuatW) / 32767;
				TrackerLeftData.Rotation.X = (float)(DataHMDRAW->tracker2_QuatX) / 32767;
				TrackerLeftData.Rotation.Y = (float)(DataHMDRAW->tracker2_QuatY) / 32767;
				TrackerLeftData.Rotation.Z = (float)(DataHMDRAW->tracker2_QuatZ) / 32767;
				TrackerLeftData.vBat = (float)(DataHMDRAW->tracker2_vBat) / 255;

				TrackerRightData.Rotation.W = (float)(DataHMDRAW->tracker3_QuatW) / 32767;
				TrackerRightData.Rotation.X = (float)(DataHMDRAW->tracker3_QuatX) / 32767;
				TrackerRightData.Rotation.Y = (float)(DataHMDRAW->tracker3_QuatY) / 32767;
				TrackerRightData.Rotation.Z = (float)(DataHMDRAW->tracker3_QuatZ) / 32767;
				TrackerRightData.vBat = (float)(DataHMDRAW->tracker3_vBat) / 255;
				break;
			}
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));	//max USB HID update rate is 1000hz.
	}
	DriverLog("[DataTransport] Stopping to poll HID data");
}

/**
	 Grabs Final HMD data...
*/
DriverPose_t CdataHandler::GetHMDPose()
{
	DriverPose_t pose = { 0 };

	pose.qWorldFromDriverRotation = HmdQuaternion_t{ 1, 0, 0, 0 };
	pose.qDriverFromHeadRotation = HmdQuaternion_t{ 1, 0, 0, 0 };
	pose.shouldApplyHeadModel = true;
	pose.poseTimeOffset = 0;
	pose.willDriftInYaw = false;

	if (dataTransport.IsConnected()) {
		pose.result = TrackingResult_Running_OK;
		pose.poseIsValid = true;
		pose.deviceIsConnected = true;
		// if accelerometer position is enabled, update on IMU data, else update on camera data.
		if (HMDAccelEnable) {
			HMDKalman.updateIMU();
		}
		else {
			HMDKalman.update();
		}

		HMDData.TrackingData.Position = HMDKalman.getEstimation();

		SetOffsetQuat(HMDData.TrackingData);
		//swap components Z and Y because steamvr's coordinate system is stupid, then do the inverse.
		Quaternion HMDPosQuat = Quaternion::Inverse(Quaternion(HMDData.TrackingData.OutputRotation.X, HMDData.TrackingData.OutputRotation.Z, HMDData.TrackingData.OutputRotation.Y, HMDData.TrackingData.OutputRotation.W));

		if (PSMConnected) {	//PSM POSITION
			Vector3 pos = HMDData.TrackingData.Position + (HMDPosQuat * HMDData.TrackingData.PositionOffset);
			pose.vecPosition[0] = pos.X;
			pose.vecPosition[1] = pos.Z;
			pose.vecPosition[2] = pos.Y;

			//Velocity
			pose.vecVelocity[0] = HMDData.TrackingData.Velocity.X;
			pose.vecVelocity[1] = HMDData.TrackingData.Velocity.Z;
			pose.vecVelocity[2] = HMDData.TrackingData.Velocity.Y;
		}
		else {
			Vector3 pos = Vector3(0, 0, 0.4) + HMDData.TrackingData.PositionOffset;
			pose.vecPosition[0] = pos.X;
			pose.vecPosition[1] = pos.Z;
			pose.vecPosition[2] = pos.Y;
		}

		//Angular acceleration
		pose.vecAngularAcceleration[0] = HMDData.TrackingData.AngularAccel.X;
		pose.vecAngularAcceleration[1] = HMDData.TrackingData.AngularAccel.Z;
		pose.vecAngularAcceleration[2] = HMDData.TrackingData.AngularAccel.Y;

		pose.vecAngularVelocity[0] = HMDData.TrackingData.AngularVelocity.X;
		pose.vecAngularVelocity[1] = HMDData.TrackingData.AngularVelocity.Z;
		pose.vecAngularVelocity[2] = HMDData.TrackingData.AngularVelocity.Y;
	
		pose.qRotation = HmdQuaternion_t{ HMDData.TrackingData.OutputRotation.W,HMDData.TrackingData.OutputRotation.X ,HMDData.TrackingData.OutputRotation.Y ,HMDData.TrackingData.OutputRotation.Z };
	}
	else {
		pose.poseIsValid = false;
		pose.result = TrackingResult_Uninitialized;
		pose.deviceIsConnected = false;
	}

	if ((GetAsyncKeyState(VK_F11) & 0x8000))
	{
		DriverLog("[Debug] current filter beta:%lf", HMDfilter.getBeta());
	}
	if ((GetAsyncKeyState(VK_F10) & 0x8000))
	{
		DriverLog("[Debug] Right controller Accel: Ax:%f Ay:%f Az:%f  Vx:%fm/s Vy:%fm/s Vz:%fm/s", RightCtrlData.TrackingData.Accel.X, RightCtrlData.TrackingData.Accel.Y, RightCtrlData.TrackingData.Accel.Z, RightCtrlData.TrackingData.Velocity.X, RightCtrlData.TrackingData.Velocity.Y, RightCtrlData.TrackingData.Velocity.Z);
		DriverLog("[Debug] Left controller Accel: Ax:%f Ay:%f Az:%f  Vx:%fm/s Vy:%fm/s Vz:%fm/s", LeftCtrlData.TrackingData.Accel.X, LeftCtrlData.TrackingData.Accel.Y, LeftCtrlData.TrackingData.Accel.Z, LeftCtrlData.TrackingData.Velocity.X, LeftCtrlData.TrackingData.Velocity.Y, LeftCtrlData.TrackingData.Velocity.Z);
		DriverLog("[Debug] HMD Accel: Ax:%f Ay:%f Az:%f HMD Velocity: Vx:%fm/s Vy:%fm/s Vz:%fm/s", HMDData.TrackingData.Accel.X, HMDData.TrackingData.Accel.Y, HMDData.TrackingData.Accel.Z, HMDData.TrackingData.Velocity.X, HMDData.TrackingData.Velocity.Y, HMDData.TrackingData.Velocity.Z);
	}
	if ((GetAsyncKeyState(VK_F9) & 0x8000)) {
		ResetPos(true, true);
	}
	if ((GetAsyncKeyState(VK_F8) & 0x8000))
	{
		SetCentering(false);
	}
	if ((GetAsyncKeyState(VK_F7) & 0x8000))
	{
		SetCentering(true);
	}
	return pose;
}

/**
	 Grabs Final Controller data...
*/
DriverPose_t CdataHandler::GetControllersPose(int ControllerIndex)
{
	DriverPose_t pose = { 0 };

	if (dataTransport.IsConnected()) {

		if (receivedControllerData) {
			pose.poseIsValid = true;
			pose.deviceIsConnected = true;
			pose.poseTimeOffset = ((float)psmsMillisecondPeriod * 2) / 1000;	//keep things smooth, time offset in milliseconds is psms camera rate.
		}																		//thanks okawo!
		else {	
			pose.poseIsValid = false;
			pose.deviceIsConnected = false;
			pose.result = TrackingResult_Uninitialized;
			return pose;
		}

		pose.qWorldFromDriverRotation = HmdQuaternion_t{ 1, 0, 0, 0 };
		pose.qDriverFromHeadRotation = HmdQuaternion_t{ 1, 0, 0, 0 };

		if (ControllerIndex == 1) {

			if (RightCtrlData.TrackingData.isTracked) {
				pose.result = TrackingResult_Running_OK;
			}
			else{
				pose.result = TrackingResult_Running_OutOfRange;
			}

			// if accelerometer position is enabled, update on IMU data, else update on camera data.
			if (CtrlAccelEnable) {
				CtrlRightKalman.updateIMU();
			}
			else {
				CtrlRightKalman.update();
			}

			SetOffsetQuat(RightCtrlData.TrackingData);

			//swap components Z and Y because steamvr's coordinate system is stupid, then do the inverse.
			Quaternion CtrlPosQuat = Quaternion::Inverse(Quaternion(RightCtrlData.TrackingData.OutputRotation.X,
																	RightCtrlData.TrackingData.OutputRotation.Z,
																	RightCtrlData.TrackingData.OutputRotation.Y,
																	RightCtrlData.TrackingData.OutputRotation.W));

			RightCtrlData.TrackingData.Position = CtrlRightKalman.getEstimation();

			if (PSMConnected) {		//PSM POSITION
				// Apply position offset
				RightCtrlData.TrackingData.Position = RightCtrlData.TrackingData.Position + (CtrlPosQuat * RightCtrlData.TrackingData.PositionOffset);
			}
			else {
				// Apply position offset
				RightCtrlData.TrackingData.Position = Vector3(0.1, -0.3, 0.2) + RightCtrlData.TrackingData.PositionOffset;
			}

			pose.vecPosition[0] = RightCtrlData.TrackingData.Position.X;
			pose.vecPosition[1] = RightCtrlData.TrackingData.Position.Z;
			pose.vecPosition[2] = RightCtrlData.TrackingData.Position.Y;

			//Velocity
			pose.vecVelocity[0] = RightCtrlData.TrackingData.Velocity.X;
			pose.vecVelocity[1] = RightCtrlData.TrackingData.Velocity.Z;
			pose.vecVelocity[2] = RightCtrlData.TrackingData.Velocity.Y;

			//Rotation first controller
			//check if controller rotation is initialized and valid.
			if (isnan(RightCtrlData.TrackingData.OutputRotation.W) || isnan(RightCtrlData.TrackingData.OutputRotation.X) || isnan(RightCtrlData.TrackingData.OutputRotation.Y) || isnan(RightCtrlData.TrackingData.OutputRotation.Z)) {
				pose.poseIsValid = false;
				pose.result = TrackingResult_Uninitialized;
				pose.deviceIsConnected = false;
				pose.qRotation = HmdQuaternion_t{ 1, 0, 0, 0 };
			}
			else {
				pose.qRotation = HmdQuaternion_t{ RightCtrlData.TrackingData.OutputRotation.W, RightCtrlData.TrackingData.OutputRotation.X, RightCtrlData.TrackingData.OutputRotation.Y, RightCtrlData.TrackingData.OutputRotation.Z };
			}
		}
		else{

			if (LeftCtrlData.TrackingData.isTracked) {
				pose.result = TrackingResult_Running_OK;
			}
			else {
				pose.result = TrackingResult_Running_OutOfRange;
			}

			// if accelerometer position is enabled, update on IMU data, else update on camera data.
			if (CtrlAccelEnable) {
				CtrlLeftKalman.updateIMU();
			}
			else {
				CtrlLeftKalman.update();
			}

			SetOffsetQuat(LeftCtrlData.TrackingData);

			//swap components Z and Y because steamvr's coordinate system is stupid, then do the inverse.
			Quaternion CtrlPosQuat = Quaternion::Inverse(Quaternion(LeftCtrlData.TrackingData.OutputRotation.X,
																	LeftCtrlData.TrackingData.OutputRotation.Z,
																	LeftCtrlData.TrackingData.OutputRotation.Y,
																	LeftCtrlData.TrackingData.OutputRotation.W));

			LeftCtrlData.TrackingData.Position = CtrlLeftKalman.getEstimation();

			if (PSMConnected) {		//PSM POSITION
				// Apply position offset
				LeftCtrlData.TrackingData.Position = LeftCtrlData.TrackingData.Position + (CtrlPosQuat * LeftCtrlData.TrackingData.PositionOffset);
			}
			else {
				// Apply position offset
				LeftCtrlData.TrackingData.Position = Vector3(-0.1, -0.3, 0.2) + LeftCtrlData.TrackingData.PositionOffset;
			}

			pose.vecPosition[0] = LeftCtrlData.TrackingData.Position.X;
			pose.vecPosition[1] = LeftCtrlData.TrackingData.Position.Z;
			pose.vecPosition[2] = LeftCtrlData.TrackingData.Position.Y;

			//Velocity
			pose.vecVelocity[0] = LeftCtrlData.TrackingData.Velocity.X;
			pose.vecVelocity[1] = LeftCtrlData.TrackingData.Velocity.Z;
			pose.vecVelocity[2] = LeftCtrlData.TrackingData.Velocity.Y;
			
			//Rotation second controller
			//check if controller rotation is initialized and valid.
			if (isnan(LeftCtrlData.TrackingData.OutputRotation.W) || isnan(LeftCtrlData.TrackingData.OutputRotation.X) || isnan(LeftCtrlData.TrackingData.OutputRotation.Y) || isnan(LeftCtrlData.TrackingData.OutputRotation.Z)) {
				pose.poseIsValid = false;
				pose.result = TrackingResult_Uninitialized;
				pose.deviceIsConnected = false;
				pose.qRotation = HmdQuaternion_t{ 1, 0, 0, 0 };
			}
			else
			{
				pose.qRotation = HmdQuaternion_t{ LeftCtrlData.TrackingData.OutputRotation.W, LeftCtrlData.TrackingData.OutputRotation.X, LeftCtrlData.TrackingData.OutputRotation.Y, LeftCtrlData.TrackingData.OutputRotation.Z };
			}
		}
		return pose;
	}
	return pose;
}

void CdataHandler::GetControllerData(TController* RightController, TController* LeftController) {
	RightController->Buttons = RightCtrlData.Buttons;
	RightController->Trigger = RightCtrlData.Trigger;
	RightController->JoyAxisX = RightCtrlData.JoyAxisX;
	RightController->JoyAxisY = RightCtrlData.JoyAxisY;
	RightController->TrackpY = RightCtrlData.TrackpY;
	RightController->vBat = RightCtrlData.vBat;

	RightController->FingThumb = RightCtrlData.FingThumb;
	RightController->FingIndex = RightCtrlData.FingIndex;
	RightController->FingMiddl = RightCtrlData.FingMiddl;
	RightController->FingRing = RightCtrlData.FingRing;
	RightController->FingPinky = RightCtrlData.FingPinky;

	LeftController->Buttons = LeftCtrlData.Buttons;
	LeftController->Trigger = LeftCtrlData.Trigger;
	LeftController->JoyAxisX = LeftCtrlData.JoyAxisX;
	LeftController->JoyAxisY = LeftCtrlData.JoyAxisY;
	LeftController->TrackpY = LeftCtrlData.TrackpY;
	LeftController->vBat = LeftCtrlData.vBat;

	LeftController->FingThumb = LeftCtrlData.FingThumb;
	LeftController->FingIndex = LeftCtrlData.FingIndex;
	LeftController->FingMiddl = LeftCtrlData.FingMiddl;
	LeftController->FingRing = LeftCtrlData.FingRing;
	LeftController->FingPinky = LeftCtrlData.FingPinky;
};

/**
	 Grabs Final Tracker data...
*/
void CdataHandler::GetTrackersData(TTracker* waistTracker, TTracker* leftTracker, TTracker* rightTracker)
{/*
	if (dataTransport->IsConnected()) {
		Quaternion TRKWaistQuat = SetOffsetQuat(TrackerWaistData.Rotation, WaistTrackerOffset, Quaternion::Identity());
		Quaternion TRKLeftQuat = SetOffsetQuat(TrackerLeftData.Rotation, LeftTrackerOffset, Quaternion::Identity());
		Quaternion TRKRightQuat = SetOffsetQuat(TrackerRightData.Rotation, RightTrackerOffset, Quaternion::Identity());

		waistTracker->Rotation = TRKWaistQuat;
		waistTracker->vBat = TrackerWaistData.vBat;

		leftTracker->Rotation = TRKLeftQuat;
		leftTracker->vBat = TrackerLeftData.vBat;

		rightTracker->Rotation = TRKRightQuat;
		rightTracker->vBat = TrackerRightData.vBat;
	}

	if (PSMConnected) {
		//todo: psm stuff
		waistTracker->Position = Vector3(0, 0, 0);
		leftTracker->Position = Vector3(0, 0, 0);
		rightTracker->Position = Vector3(0, 0, 0);

	}
	else {
		waistTracker->Position = Vector3(0, 0, 0);
		leftTracker->Position = Vector3(0, 0, 0);
		rightTracker->Position = Vector3(0, 0, 0);
	}*/
}

/**
	 Attempts to connect to PSMoveService on the default address and port.
	 if it succeeds it allocates listeners for Controller and HMDs and starts up the PSMoveUpdate thread which is used for position tracking.
*/
bool CdataHandler::connectToPSMOVE()
{
	DriverLog("[PsMoveData] Trying to connect to PSMS on ADDRESS %s and PORT %s", PSMOVESERVICE_DEFAULT_ADDRESS, PSMOVESERVICE_DEFAULT_PORT);
	int PSMstatus = PSM_Initialize(PSMOVESERVICE_DEFAULT_ADDRESS, PSMOVESERVICE_DEFAULT_PORT, 3000);
	bool bSuccess = (PSMstatus == PSMResult_Success);
	DriverLog("[PsMoveData] PSM status: %d", PSMstatus);
	PSMConnected = bSuccess;
	
	unsigned int data_stream_flags =
		PSMControllerDataStreamFlags::PSMStreamFlags_includePositionData |
		PSMControllerDataStreamFlags::PSMStreamFlags_includePhysicsData |
		PSMControllerDataStreamFlags::PSMStreamFlags_includeCalibratedSensorData |
		PSMControllerDataStreamFlags::PSMStreamFlags_includeRawTrackerData;

	if (PSMConnected) {

		DriverLog("[PsMoveData] PSMS connected!");

		memset(&hmdList, 0, sizeof(PSMHmdList));
		PSM_GetHmdList(&hmdList, PSM_DEFAULT_TIMEOUT);

		memset(&controllerList, 0, sizeof(PSMControllerList));
		PSM_GetControllerList(&controllerList, PSM_DEFAULT_TIMEOUT);

		DriverLog("[PsMoveData] PSM hmdCount: %d", hmdList.count);
		DriverLog("[PsMoveData] PSM ControllerCount: %d", controllerList.count);

	//hmd
	if (hmdList.count > 0) 
	{
		if (PSM_AllocateHmdListener(hmdList.hmd_id[0]) == PSMResult_Success && PSM_StartHmdDataStream(hmdList.hmd_id[0], data_stream_flags, PSM_DEFAULT_TIMEOUT) == PSMResult_Success) 
		{
			DriverLog("[PsMoveData] HMD Allocated successfully!");
			HMDAllocated = true;
		}
	}

	
	//controllers
	if (PSM_AllocateControllerListener(controllerList.controller_id[0]) == PSMResult_Success && PSM_StartControllerDataStream(controllerList.controller_id[0], data_stream_flags, PSM_DEFAULT_TIMEOUT) == PSMResult_Success)
	{
		DriverLog("[PsMoveData] Controller %d allocated successfully!", controllerList.controller_id[0]);
		ctrl1Allocated = true;
	}
	

	if (PSM_AllocateControllerListener(controllerList.controller_id[1]) == PSMResult_Success && PSM_StartControllerDataStream(controllerList.controller_id[1], data_stream_flags, PSM_DEFAULT_TIMEOUT) == PSMResult_Success)
	{
		DriverLog("[PsMoveData] Controller %d allocated successfully!", controllerList.controller_id[1]);
		ctrl2Allocated = true;
	}
	
		
	if (bSuccess)
		pPSMUpdatethread = new std::thread(this->PSMUpdateEnter,this);

	}
	else {
		DriverLog("[PsMoveData] PSMS not connected!");
		HMDAccelEnable = false;
		CtrlAccelEnable = false;
	}
	return bSuccess;

}

/**
	 Updates PSMoveService position tracking data. 
*/
void CdataHandler::PSMUpdate()
{
	std::chrono::steady_clock::time_point lastPSMSUpdate;

	while (PSMConnected) {

		PSM_Update();

		auto now = std::chrono::high_resolution_clock::now();
		deltatime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastPSMSUpdate).count() / 1000000.0f;
		lastPSMSUpdate = now;

		//TODO: refactor

		if (HMDAllocated) {
			PSM_GetHmdPosition(hmdList.hmd_id[0], &psmHmdPos);
			PSM_GetIsHmdTracking(hmdList.hmd_id[0], &HMDData.TrackingData.isTracked);
			if (HMDData.TrackingData.isTracked == true) {
				HMDData.TrackingData.wasTracked = true;
			}

			Vector3 PSMSHMDPos = Vector3((float)psmHmdPos.x * k_fScalePSMoveAPIToMeters, (float)psmHmdPos.z * k_fScalePSMoveAPIToMeters, (float)psmHmdPos.y * k_fScalePSMoveAPIToMeters);
			if (PSMSHMDPos != HMDData.TrackingData.LastCameraPos || !HMDData.TrackingData.isTracked)			//if position isn't old or if it's not being tracked
			{
				HMDKalman.updateMeasCam(PSMSHMDPos);																	//update filter
				HMDData.TrackingData.Position = HMDKalman.getEstimation();												//update position
				UpdateVelocity(HMDData.TrackingData, HMDData.TrackingData.wasTracked, PSMSHMDPos);						//update velocity
				if (enableDriftCorrection) { UpdateDriftCorrection(HMDData.TrackingData, driftLowVelThresold, driftHighVelThresold, false); }
				HMDData.TrackingData.wasTracked = false;
			}
		}
		if (ctrl1Allocated) {
			PSM_GetControllerPosition(controllerList.controller_id[0], &psmCtrlRightPos);
			PSM_GetIsControllerTracking(controllerList.controller_id[0], &RightCtrlData.TrackingData.isTracked);
			if (RightCtrlData.TrackingData.isTracked == true) {
				RightCtrlData.TrackingData.wasTracked = true;
			}

			Vector3 PSMSCtrlRightPos = Vector3((float)psmCtrlRightPos.x * k_fScalePSMoveAPIToMeters, (float)psmCtrlRightPos.z * k_fScalePSMoveAPIToMeters, (float)psmCtrlRightPos.y * k_fScalePSMoveAPIToMeters);
			if (PSMSCtrlRightPos != RightCtrlData.TrackingData.LastCameraPos || !RightCtrlData.TrackingData.isTracked)			//if position isn't old or if it's not being tracked
			{
				CtrlRightKalman.updateMeasCam(PSMSCtrlRightPos);																				//update filter
				RightCtrlData.TrackingData.Position = CtrlRightKalman.getEstimation();															//update position
				UpdateVelocity(RightCtrlData.TrackingData, RightCtrlData.TrackingData.wasTracked, PSMSCtrlRightPos);							//update velocity
				if (enableDriftCorrection) { UpdateDriftCorrection(RightCtrlData.TrackingData, driftLowVelThresold, driftHighVelThresold, false); }
				RightCtrlData.TrackingData.wasTracked = false;
			}
		}
		if (ctrl2Allocated) {
			PSM_GetControllerPosition(controllerList.controller_id[1], &psmCtrlLeftPos);
			PSM_GetIsControllerTracking(controllerList.controller_id[1], &LeftCtrlData.TrackingData.isTracked);
			if (LeftCtrlData.TrackingData.isTracked == true) {
				LeftCtrlData.TrackingData.wasTracked = true;
			}

			Vector3 PSMSCtrlLeftPos = Vector3((float)psmCtrlLeftPos.x * k_fScalePSMoveAPIToMeters, (float)psmCtrlLeftPos.z * k_fScalePSMoveAPIToMeters, (float)psmCtrlLeftPos.y * k_fScalePSMoveAPIToMeters);
			if (PSMSCtrlLeftPos != LeftCtrlData.TrackingData.LastCameraPos || !LeftCtrlData.TrackingData.isTracked)			//if position isn't old or if it's not being tracked
			{
				CtrlLeftKalman.updateMeasCam(PSMSCtrlLeftPos);																					//update filter
				LeftCtrlData.TrackingData.Position = CtrlLeftKalman.getEstimation();															//update position
				UpdateVelocity(LeftCtrlData.TrackingData, LeftCtrlData.TrackingData.wasTracked, PSMSCtrlLeftPos);								//update velocity
				if (enableDriftCorrection) { UpdateDriftCorrection(LeftCtrlData.TrackingData, driftLowVelThresold, driftHighVelThresold, false); }
				LeftCtrlData.TrackingData.wasTracked = false;																					//set to false once done calculating stuff for next cycle
			}
		}
		//no need to update this faster than we can capture the images.
		std::this_thread::sleep_for(std::chrono::milliseconds(psmsMillisecondPeriod));
	}
}

/**
	 Checks for the headset to be connected and if it is it starts an HID connection with it.
	 Once it does it creates the ReadHID thread and grabs offset calibration data, filter beta, jitter rejection coefficient and PSMS update rate.
	 Once done it attempts to connect to PSMoveService by calling connectToPSMOVE().
*/
void CdataHandler::StartData()
{
	if (!dataTransport.IsConnected()) {
		if (dataTransport.Start() != 0) {
			DriverLog("[DataStream] Failed to initialize data transport");
			return;
		}

		pTransportthread = new std::thread(this->ReadTransportEnter, this);

		//get config rotation offsets
		HMDData.TrackingData.RotationConfigOffset = Quaternion::FromEuler(vr::VRSettings()->GetFloat(k_pch_HMD_Section, k_pch_HMD_PitchOffset_Float) * M_PI / 180, vr::VRSettings()->GetFloat(k_pch_HMD_Section, k_pch_HMD_YawOffset_Float) * M_PI / 180, vr::VRSettings()->GetFloat(k_pch_HMD_Section, k_pch_HMD_RollOffset_Float) * M_PI / 180);
		
		RightCtrlData.TrackingData.RotationConfigOffset = Quaternion::FromEuler(vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_ControllerRight_PitchOffset_Float) * M_PI / 180, vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_ControllerRight_YawOffset_Float) * M_PI / 180, vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_ControllerRight_RollOffset_Float) * M_PI / 180);
		LeftCtrlData.TrackingData.RotationConfigOffset = Quaternion::FromEuler(vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_ControllerLeft_PitchOffset_Float) * M_PI / 180, vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_ControllerLeft_YawOffset_Float) * M_PI / 180, vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_ControllerLeft_RollOffset_Float) * M_PI / 180);
		
		//get config position offsets
		HMDData.TrackingData.PositionOffset = Vector3(vr::VRSettings()->GetFloat(k_pch_HMD_Section, k_pch_HMD_XOffset_Float), vr::VRSettings()->GetFloat(k_pch_HMD_Section, k_pch_HMD_YOffset_Float), vr::VRSettings()->GetFloat(k_pch_HMD_Section, k_pch_HMD_ZOffset_Float));

		RightCtrlData.TrackingData.PositionOffset = Vector3(vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_ControllerRight_XOffset_Float), vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_ControllerRight_YOffset_Float), vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_ControllerRight_ZOffset_Float));
		LeftCtrlData.TrackingData.PositionOffset = Vector3(vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_ControllerLeft_XOffset_Float), vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_ControllerLeft_YOffset_Float), vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_ControllerLeft_ZOffset_Float));


		//get calibration offsets
		HMDData.TrackingData.RotationUserOffset.W = vr::VRSettings()->GetFloat(k_pch_Calibration_Section, k_pch_Calibration_HMDW_Float);
		HMDData.TrackingData.RotationUserOffset.Y = vr::VRSettings()->GetFloat(k_pch_Calibration_Section, k_pch_Calibration_HMDY_Float);

		RightCtrlData.TrackingData.RotationUserOffset.W = vr::VRSettings()->GetFloat(k_pch_Calibration_Section, k_pch_Calibration_CONTRightW_Float);
		RightCtrlData.TrackingData.RotationUserOffset.Y = vr::VRSettings()->GetFloat(k_pch_Calibration_Section, k_pch_Calibration_CONTRightY_Float);

		LeftCtrlData.TrackingData.RotationUserOffset.W = vr::VRSettings()->GetFloat(k_pch_Calibration_Section, k_pch_Calibration_CONTLeftW_Float);
		LeftCtrlData.TrackingData.RotationUserOffset.Y = vr::VRSettings()->GetFloat(k_pch_Calibration_Section, k_pch_Calibration_CONTLeftY_Float);

		/*			TODO: IMPLEMENT
		WaistTrackerOffset.W = vr::VRSettings()->GetFloat(k_pch_Calibration_Section, k_pch_Calibration_TRKWaistW_Float);
		WaistTrackerOffset.Y = vr::VRSettings()->GetFloat(k_pch_Calibration_Section, k_pch_Calibration_TRKWaistY_Float);

		LeftTrackerOffset.W = vr::VRSettings()->GetFloat(k_pch_Calibration_Section, k_pch_Calibration_TRKLeftW_Float);
		LeftTrackerOffset.Y = vr::VRSettings()->GetFloat(k_pch_Calibration_Section, k_pch_Calibration_TRKLeftY_Float);

		RightTrackerOffset.W = vr::VRSettings()->GetFloat(k_pch_Calibration_Section, k_pch_Calibration_TRKRightW_Float);
		RightTrackerOffset.Y = vr::VRSettings()->GetFloat(k_pch_Calibration_Section, k_pch_Calibration_TRKRightY_Float);
		*/
		DriverLog("[Settings] Loaded Calibration settings");

		//get psms update rate
		psmsUpdateRate = (vr::VRSettings()->GetInt32(k_pch_Driver_Section, k_pch_PSMS_UPDATE_RATE_Int32)); //poll at the rate of camera refresh.
		psmsMillisecondPeriod = (int)((1.f / psmsUpdateRate) * 1000.f);
		DriverLog("[Settings] PSMS polling rate is hz: %i, with a period of %i milliseconds.", psmsUpdateRate, psmsMillisecondPeriod);
		
		minFilterBeta = vr::VRSettings()->GetFloat(k_pch_HMD_Section, k_pch_HMD_MinFilterBeta_Float);
		maxFilterBeta = vr::VRSettings()->GetFloat(k_pch_HMD_Section, k_pch_HMD_MaxFilterBeta_Float);

		//drift correction stuff.
		enableDriftCorrection = vr::VRSettings()->GetBool(k_pch_Experimental_Section, k_pch_EnableCorrection_Bool);
		driftMeasurementUncertainty = vr::VRSettings()->GetFloat(k_pch_Experimental_Section, k_pch_Drift_MeasurementUncertainty_Float);
		driftEstimationUncertainty = vr::VRSettings()->GetFloat(k_pch_Experimental_Section, k_pch_Drift_EstimationUncertainty_Float);
		driftHMDP_N = vr::VRSettings()->GetFloat(k_pch_Experimental_Section, k_pch_Drift_HMDP_Noise_Float);
		driftContP_N = vr::VRSettings()->GetFloat(k_pch_Experimental_Section, k_pch_Drift_ContP_Noise_Float);
		driftLowVelThresold = vr::VRSettings()->GetFloat(k_pch_Experimental_Section, k_pch_Drift_LowVelThreshold_Float);
		driftHighVelThresold = vr::VRSettings()->GetFloat(k_pch_Experimental_Section, k_pch_Drift_HighVelThreshold_Float);
		//load up filters
		if (enableDriftCorrection) {
			HMDData.TrackingData.DriftKalman.setSettings(driftMeasurementUncertainty, driftEstimationUncertainty, driftHMDP_N);
			RightCtrlData.TrackingData.DriftKalman.setSettings(driftMeasurementUncertainty, driftEstimationUncertainty, driftContP_N);
			LeftCtrlData.TrackingData.DriftKalman.setSettings(driftMeasurementUncertainty, driftEstimationUncertainty, driftContP_N);
		}


		//use accelerometers?
		CtrlAccelEnable = vr::VRSettings()->GetBool(k_pch_Controllers_Section, k_pch_Tracking_AccelEnable_Bool);
		HMDAccelEnable = vr::VRSettings()->GetBool(k_pch_HMD_Section, k_pch_Tracking_AccelEnable_Bool);

		//get tracker update rate and smoothness thing
		float CamK_measErr = vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_Camera_Kalman_Meas_err_Float);
		float CamK_estmErr = vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_Camera_Kalman_Estim_err_Float);
		float CamK_ProcNoise = vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_Camera_Kalman_Proc_noise_Float);

		float IMUK_measErr = vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_IMU_Kalman_Meas_err_Float);
		float IMUK_estmErr = vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_IMU_Kalman_Estim_err_Float);
		float IMUK_ProcNoise = vr::VRSettings()->GetFloat(k_pch_Controllers_Section, k_pch_IMU_Kalman_Proc_noise_Float);

		CtrlLeftKalman.setSettings(CamK_measErr, CamK_estmErr, CamK_ProcNoise, IMUK_measErr, IMUK_estmErr, IMUK_ProcNoise);
		CtrlRightKalman.setSettings(CamK_measErr, CamK_estmErr, CamK_ProcNoise, IMUK_measErr, IMUK_estmErr, IMUK_ProcNoise);

		float HMD_CamK_measErr = vr::VRSettings()->GetFloat(k_pch_HMD_Section, k_pch_Camera_Kalman_Meas_err_Float);
		float HMD_CamK_estmErr = vr::VRSettings()->GetFloat(k_pch_HMD_Section, k_pch_Camera_Kalman_Estim_err_Float);
		float HMD_CamK_ProcNoise = vr::VRSettings()->GetFloat(k_pch_HMD_Section, k_pch_Camera_Kalman_Proc_noise_Float);

		float HMD_IMUK_measErr = vr::VRSettings()->GetFloat(k_pch_HMD_Section, k_pch_IMU_Kalman_Meas_err_Float);
		float HMD_IMUK_estmErr = vr::VRSettings()->GetFloat(k_pch_HMD_Section, k_pch_IMU_Kalman_Estim_err_Float);
		float HMD_IMUK_ProcNoise = vr::VRSettings()->GetFloat(k_pch_HMD_Section, k_pch_IMU_Kalman_Proc_noise_Float);

		HMDKalman.setSettings(HMD_CamK_measErr, HMD_CamK_estmErr, HMD_CamK_ProcNoise, HMD_IMUK_measErr, HMD_IMUK_estmErr, HMD_IMUK_ProcNoise);

		//set initial states for controllers and hmd.
		ResetPos(true, true);
		//Attempt to connect to psmoveservice
		connectToPSMOVE();
	}
}

void CdataHandler::StopData() 
{
	if (dataTransport.IsConnected()) {
		dataTransport.Stop();
		if (pTransportthread) {
			pTransportthread->join();
			delete pTransportthread;
			pTransportthread = nullptr;
		}
	}

	if (PSMConnected) {
		PSMConnected = false;
		PSM_Shutdown();
		if (pPSMUpdatethread) {
			pPSMUpdatethread->join();
			delete pPSMUpdatethread;
			pPSMUpdatethread = nullptr;
		}
	}

	//kill test thread
	if (pTestThread) {
		pTestThread->join();
		delete pTestThread;
		pTestThread = nullptr;
	}
}