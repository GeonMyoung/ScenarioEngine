#include <GitsnAsnUtilSampleMsg.h>
#include <dz1_gasn_support.h>

MapData* sample_map;										// DSRCmsgID = 18
SPAT* sample_spat;											// DSRCmsgID = 19
BasicSafetyMessage* sample_bsm;								// DSRCmsgID = 20

EmergencyVehicleAlert* sample_eva;							// DSRCmsgID = 22

ProbeVehicleData* sample_pvd;								// DSRCmsgID = 26
RoadSideAlert* sample_rsa;									// DSRCmsgID = 27

RTCMcorrections* sample_rtcm;								// DSRCmsgID = 28

SignalRequestMessage *sample_srm;							// DSRCmsgID = 29
SignalStatusMessage *sample_ssm;								// DSRCmsgID = 29

TravelerInformation* sample_tim;							// DSRCmsgID = 31

PersonalSafetyMessage* sample_psm;							// DSRCmsgID = 32

SensorDataSharingMessage* sample_sdsm;						// DSRCmsgID = 41

TLS* sample_tls;											// DSRCmsgID = 50; 
TrafficLightStatusMessage* sample_tlsm;						// DSRCmsgID = 50; 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Data Element
static MinuteOfTheYear sample_minute_of_the_year = 250101;
static MsgCount sample_msg_count = 0;
static ProbeSegmentNumber sample_probe_segment_number = 1;
static ASNUINT8 sample_ia5string[] = { 0x41, 0x42, 0x43, 0x44 };
static ASNUINT8 sample_descriptive_name[] = { 0x41, 0x42, 0x43, 0x44 };
static ASNUINT8 sample_vin_string[] = { 0x41, 0x42, 0x43, 0x44 };
static ASNUINT8 sample_temporary_id[] = { 0x41, 0x42, 0x43, 0x44 };
static StationID sample_station_id = 1;
static VehicleType sample_vehicle_type = VehicleType_unknown;
static VehicleGroupAffected sample_vehicle_group_affected = VehicleGroupAffected_all_vehicles;
static ResponderGroupAffected sample_responder_group_affected = ResponderGroupAffected_ambulance_units;
static IncidentResponseEquipment sample_incident_response_equipment = IncidentResponseEquipment_engine;
static DYear sample_d_year = 2025;
static DMonth sample_d_month = 1;
static DDay sample_d_day = 1;
static DHour sample_d_hour = 11;
static DMinute sample_d_minute = 11;
static DSecond sample_d_second = 0;
static DOffset sample_d_offset = 0;
static Latitude sample_latitude = 0;
static Longitude sample_longitude = 0;
static Elevation sample_elevation = 10;
static Heading sample_heading = 20;
static TimeConfidence sample_time_confidence = TimeConfidence_time_000_000_000_000_01;
static TransmissionState sample_transmission_state = TransmissionState_park;
static Velocity sample_velocity = 100;
static SemiMajorAxisAccuracy sample_semi_major_axis_accuracy = 100;
static SemiMinorAxisAccuracy sample_semi_minor_axis_accuracy = 10;
static SemiMajorAxisOrientation sample_semi_major_axis_orientation = 50;
static PositionConfidence sample_position_confidence = PositionConfidence_a1m;
static ElevationConfidence sample_elevation_confidence = ElevationConfidence_elev_000_10;
static HeadingConfidence sample_heading_confidence = HeadingConfidence_prec0_01deg;
static SpeedConfidence sample_speed_confidence = SpeedConfidence_prec0_1ms;
static ThrottleConfidence sample_throttle_confidence = ThrottleConfidence_prec1percent;
static BasicVehicleClass sample_basic_vehicle_class = 5;
static BasicVehicleRole sample_basic_vehicle_role = BasicVehicleRole_none_unknown;
static Iso3833VehicleType sample_iso_3833_vehicle_type = 0;
static FuelType sample_fuel_type = 0;
static ASNUINT8 sample_vehicle_event_flags[] = { 0b10011000, 0b00010000 };
static ASNUINT8 sample_gnss_status[] = { 0b10110011, 0b00000000 };
static Offset_B10 sample_offset_b09 = 0;
static Offset_B10 sample_offset_b10 = 0;
static Offset_B12 sample_offset_b11 = 0;
static Offset_B12 sample_offset_b12 = 0;
static Offset_B12 sample_offset_b13 = 0;
static Offset_B14 sample_offset_b14 = 0;
static Offset_B16 sample_offset_b16 = 0;
static OffsetLL_B12 sample_offset_ll_b12 = 0;
static OffsetLL_B14 sample_offset_ll_b14 = 0;
static OffsetLL_B16 sample_offset_ll_b16 = 0;
static OffsetLL_B18 sample_offset_ll_b18 = 0;
static OffsetLL_B22 sample_offset_ll_b22 = 0;
static OffsetLL_B24 sample_offset_ll_b24 = 0;
static VertOffset_B12 sample_vert_offset_b12 = 0;
static TimeOffset sample_time_offset = 10;
static Speed sample_speed = 10;
static CoarseHeading sample_coarse_heading = 10;
static ASNUINT8 sample_exterior_lights[] = { 0b10010100, 0b00000000 }; // SIZE 9
static LightbarInUse sample_light_bar_in_use = LightbarInUse_notInUse;
static WiperStatus sample_wiper_status = WiperStatus_off;
static WiperRate sample_wiper_rate = 5;
static ASNUINT8 sample_brake_applied_status[] = { 0b10100000 };
static TractionControlStatus sample_traction_control_status = TractionControlStatus_on;
static AntiLockBrakeStatus sample_anti_lock_brake_status = AntiLockBrakeStatus_on;
static StabilityControlStatus sample_stability_control_status = StabilityControlStatus_on;
static BrakeBoostApplied sample_brake_boost_applied = BrakeBoostApplied_on;
static AuxiliaryBrakeStatus sample_auxiliary_brake_status = AuxiliaryBrakeStatus_on;
static BrakeAppliedPressure sample_brake_applied_pressure = BrakeAppliedPressure_minPressure;
static CoefficientOfFriction sample_coefficient_of_friction = 5;
static SunSensor sample_sun_sensor = 10;
static RainSensor sample_rain_sensor = RainSensor_none;
static AmbientAirTemperature sample_ambient_air_temperature = 2;
static AmbientAirPressure sample_ambient_air_pressure = 20;

static SteeringWheelAngle sample_steering_wheel_angle = 0;
static SteeringWheelAngleConfidence sample_steering_wheel_angle_confidence = SteeringWheelAngleConfidence_prec1deg;
static SteeringWheelAngleRateOfChange sample_steering_wheel_angle_rate_of_change = 0;
static DrivingWheelAngle sample_driving_wheel_angle = 0;
static VerticalAcceleration sample_vertical_acceleration = 0;
static YawRate sample_yaw_rate = 0;
static ASNUINT8 sample_vertical_acceleration_threshold[] = { 0b10100000 };
static YawRateConfidence sample_yaw_rate_confidence = YawRateConfidence_degSec_000_01;
static AccelerationConfidence sample_acceleration_confidence = AccelerationConfidence_accl_000_01;
static ObstacleDistance sample_obstacle_distance = 12;
static Angle sample_angle = 5;
static ThrottlePosition sample_throttle_position = 30;
static VehicleHeight sample_vehicle_height = 100;
static VehicleMass sample_vehicle_mass = 81;
static TrailerWeight sample_trailer_weight = 300;
static BumperHeight sample_bumper_height = 40;

static TireLocation sample_tire_location = 20;
static TirePressure sample_tire_pressure = 30;
static TireTemp sample_tire_temp = 200;
static WheelSensorStatus sample_wheel_sensor_status = WheelSensorStatus_on;
static WheelEndElectFault sample_wheel_end_elect_fault = WheelEndElectFault_isOk;
static TireLeakageRate sample_tire_leakage_rate = 100;
static TirePressureThresholdDetection sample_tire_pressure_threshold_detection = TirePressureThresholdDetection_noData;
static AxleLocation sample_axle_location = 40;
static AxleWeight sample_axle_weight = 120;

static CargoWeight sample_cargo_weight = 200;
static SteeringAxleTemperature sample_steering_axle_temperature = 30;
static DriveAxleLocation sample_drive_axle_location = 20;
static DriveAxleLiftAirPressure sample_drive_axle_lift_air_pressure = 20;
static DriveAxleTemperature sample_drive_axle_temperature = 30;
static DriveAxleLubePressure sample_drive_axle_lube_pressure = 20;
static SteeringAxleLubePressure sample_steering_axle_lube_pressure = 20;

static EssPrecipYesNo sample_ess_precip_yes_no = EssPrecipYesNo_noPrecip;
static EssPrecipRate sample_ess_precip_rate = 10000;
static EssPrecipSituation sample_ess_precip_situation = EssPrecipSituation_noPrecipitation;
static EssSolarRadiation sample_ess_solar_radiation = 100;
static EssMobileFriction sample_ess_mobile_friction = 10;

static RadiusOfCurvature sample_radius_of_curvature = 0;
static Confidence sample_confidence = 50;
static LayerType sample_layer_type = LayerType_mixedContent;
static LayerID sample_layer_id = 3;
static RoadRegulatorID  sample_road_regulator_id = 5;
static RoadSegmentID sample_road_segment_id = 5;
static IntersectionID sample_intersection_id = 100;
static SpeedLimitType sample_speed_limit_type = SpeedLimitType_vehicleMinSpeed;

static ASNUINT8 sample_lane_direction[] = { 0b10000000 };
static ASNUINT8 sample_lane_sharing[] = { 0b11000101, 0b10000000 };

static ASNUINT8 sample_lane_type_attributes_vehicle[] = { 0b10000000, 0b00000000 };			// size 8 ~
static ASNUINT8 sample_lane_type_attributes_crosswalk[] = { 0b10000000, 0b00000000 };		// size 16
static ASNUINT8 sample_lane_type_attributes_bike[] = { 0b10000000, 0b00000000 };			// size 16
static ASNUINT8 sample_lane_type_attributes_sidewalk[] = { 0b10000000, 0b00000000 };		// size 16
static ASNUINT8 sample_lane_type_attributes_barrier[] = { 0b10000000, 0b00000000 };			// size 16
static ASNUINT8 sample_lane_type_attributes_striping[] = { 0b10000000, 0b00000000 };		// size 16
static ASNUINT8 sample_lane_type_attributes_tracked_vehicle[] = { 0b10000000, 0b00000000 };	// size 16
static ASNUINT8 sample_lane_type_attributes_parking[] = { 0b10000000, 0b00000000 };			// size 16

static NodeAttributeXY sample_node_attribute_xy = NodeAttributeXY_reserved;
static SegmentAttributeXY sample_segment_attribute_xy = SegmentAttributeXY_reserved;

static DeltaAngle sample_delta_angle = 0;
static DrivenLineOffsetSm sample_driven_line_offset_sm = 0;
static DrivenLineOffsetLg sample_driven_line_offset_lg = 10;
static Scale_B12 sample_scale_b_12 = 0;
static LaneID sample_lane_id = 0;
static ApproachID sample_approach_id = 0;

static ASNUINT8 sample_allowed_maneuvers[] = { 0b10010011, 0b10000000 }; // size 12
static ASNUINT8 sample_ig_relative_position[] = { 0b10000000, 0b00000000 }; // size 9
static LaneWidth sample_lane_width = 100;

static RestrictionAppliesTo sample_restriction_applies_to = RestrictionAppliesTo_none;
static RestrictionClassID sample_restriction_class_id = 0;
static ASNUINT8 sample_intersection_status_object[] = { 0b11000001, 0b10010000 };	// size 16
static SignalGroupID sample_signal_group_id = 4;

static MovementPhaseState sample_movement_phase_state = MovementPhaseState_dark;
static TimeMark sample_time_mark = 12345;
static TimeIntervalConfidence sample_time_interval_confidence = 0;

static AdvisorySpeedType sample_advisory_speed_type = AdvisorySpeedType_none;
static SpeedAdvice sample_speed_advice = 130;
static ZoneLength sample_zone_length = 30;
static LaneConnectionID sample_lane_connection_id = 15;
static WaitOnStopline sample_wait_on_stopline = TRUE;
static PedestrianBicycleDetect sample_pedestrian_bicycle_detect = FALSE;

static VehicleWidth sample_vehicle_width = 400;
static VehicleLength sample_vehicle_length = 300;

static ITIScodes sample_itis_codes = 111;
static ASNUINT8 sample_priority[] = { 0x41 };
static ASNUINT8 sample_heading_slice[] = { 0b11000001, 0b10010000 };	// size 16
static Extent sample_extent = Extent_forever;
static ASNUINT8 sample_further_info_id[] = { 0x41, 0x42 };
static ASNUINT8 sample_unique_msg_id[] = { 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49 };
static ASNUINT8 sample_url_base[] = { 0x55, 0x52, 0x4C };
static ASNUINT8 sample_url_short[] = { 0x75, 0x72, 0x6C };
static SSPindex sample_ssp_index = 0;
static TravelerInfoType sample_traveler_info_type = TravelerInfoType_unknown;
static MUTCDCode sample_mutcd_code = MUTCDCode_none;
static ASNUINT8 sample_msg_crc[] = { 0x41, 0x42 };
static MinutesDuration sample_minutes_duration = 60;
static SignPriority sample_sign_priority = 2;
static DirectionOfUse sample_direction_of_use = DirectionOfUse_both;
static Zoom sample_zoom = 0;
static NodeAttributeLL sample_node_attribute_ll = NodeAttributeLL_reserved;
static SegmentAttributeLL sample_segment_attribute_ll = SegmentAttributeLL_reserved;
static Radius_B12 sample_radius_b12 = 10;
static DistanceUnits sample_distance_units = DistanceUnits_centimeter;
static ASNUINT8 sample_itis_text[] = { 0x41, 0x42, 0x43, 0x44 };


// sdsm
static ObjectType sample_object_type = ObjectType_unknown;
static ClassificationConfidence sample_classification_confidence = 10;
static ObjectID sample_object_id = 2;
static MeasurementTimeOffset sample_measurement_time_offset = 100;
static EquipmentType sample_equipment_type = EquipmentType_rsu;
static ObjectDistance sample_object_distance = 0;

static PitchDetected sample_pitch_detected = 60;
static RollDetected sample_roll_detected = 70;
static YawDetected sample_yaw_detected = 80;

static PitchRate sample_pitch_rate = 100;
static RollRate sample_roll_rate = 100;

static PitchRateConfidence sample_pitch_rate_confidence = PitchRateConfidence_degSec_000_01;
static RollRateConfidence sample_roll_rate_confidence = RollRateConfidence_degSec_000_01;

static SizeValueConfidence sample_size_value_confidence = SizeValueConfidence_size_000_02;
static PersonalDeviceUserType sample_personal_device_user_type = PersonalDeviceUserType_aPedestrian;
static Attachment sample_attachment = Attachment_stroller;
static AttachmentRadius sample_attachment_radius = 20;
static HumanPropelledType sample_human_propelled_type = HumanPropelledType_onFoot;
static AnimalPropelledType sample_animal_propelled_type = AnimalPropelledType_animalDrawnCarriage;
static MotorizedPropelledType sample_motorized_propelled_type = MotorizedPropelledType_scooter;
static SizeValue sample_size_value = 40;

// tls
static INTEGER sample_integer = 1234;
static ASNUINT32 sample_oid[] = { 1, 2, 3, 4 };
static ASNUINT8 sample_traffic_light_operation_status[] = {0b01011000};			// SIZE 8, ...
static ASNUINT8 sample_traffic_light_controller_status[] = {0b01011000};		// SIZE 8, ...
static TimeInSecond_B16 sample_time_in_second_b16 = 16;							// (0..65535)
static TrafficLightType sample_traffic_light_type = TrafficLightType_reserved;
static ConsecutiveTrafficLight sample_consecutive_traffic_light = ConsecutiveTrafficLight_first;
static TrafficLightIntervalType sample_traffic_light_interval_type = TrafficLightIntervalType_static;
static PedestrianCall sample_pedestrian_call = FALSE;
static ActuatedInterval sample_actuated_interval = FALSE;
static PermissiveNonProtected sample_permissive_non_protected = PermissiveNonProtected_none;
static TrafficLightingStatus sample_traffic_lighting_status = TrafficLightingStatus_off;
static TimeInSecond_B8 sample_time_in_second_b8 = 8;							// 0..255
static TrafficLightDirectionCode sample_traffic_light_direction_code = 10;		// (0..359)
static ReservedBit sample_reserved_bit = FALSE;

// eva
static ResponseType sample_response_type = ResponseType_emergency;
static SirenInUse sample_siren_in_use = SirenInUse_reserved;
static MultiVehicleResponse sample_multi_vehicle_response = MultiVehicleResponse_reserved;
static ASNUINT8 sample_privileged_event_flags[] = { 0b11010000, 0b00000000 };	// size 16

// rtcm
static RTCM_Revision sample_rtcm_revision = RTCM_Revision_reserved;
static ASNUINT8 sample_rtcm_message_data[] = { 0xAA, 0xBB };

static RTCMmessage sample_rtcm_message = { 2, sample_rtcm_message_data };

// srm
static RequestID sample_request_id = 1;
static PriorityRequestType sample_priority_request_type = PriorityRequestType_priorityRequest;
static RequestSubRole sample_request_sub_role = RequestSubRole_requestSubRole1;
static RequestImportanceLevel sample_request_importance_level = RequestImportanceLevel_requestImportanceLevel1;
static ASNUINT8 sample_transit_vehicle_status[] = { 0b11000000,};	// size 8
static TransitVehicleOccupancy sample_transit_vehicle_occupancy = TransitVehicleOccupancy_occupancyFull;
static DeltaTime sample_delta_time = 0;
static PrioritizationResponseStatus sample_prioritization_response_status = PrioritizationResponseStatus_rejected;

// psm
static ASNUINT8 sample_personal_device_usage_state[] = { 0b01100000, 0b00000000 };		// size 9,...
static PersonalCrossingRequest sample_personal_crossing_request = TRUE;
static PersonalCrossingInProgress sample_personal_crossing_in_progress = TRUE;
static NumberOfParticipantsInCluster sample_number_of_participants_in_cluster = NumberOfParticipantsInCluster_small;
static PersonalClusterRadius sample_personal_cluster_radius = 0;
static PublicSafetyEventResponderWorkerType sample_public_safety_event_responder_worker_type = PublicSafetyEventResponderWorkerType_otherPersonnel;
static ASNUINT8 sample_public_safety_and_road_worker_activity[] = { 0b01100000 };		// size 6,...
static ASNUINT8 sample_public_safety_directing_traffic_sub_type[] = { 0b01100000 };		// size 7,...
static ASNUINT8 sample_personal_assitive[] = { 0b01100000 };		// size 6,...
static ASNUINT8 sample_user_size_and_behavior[] = { 0b01100000 };		// size 5,...
static AnimalType sample_animal_type = AnimalType_pet;
// Data Element
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static VehicleID* sample_vehicle_id;
static bool_t init_sample_vehicle_id(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_vehicle_id != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_vehicle_id = (VehicleID*)mpool_malloc(ws.Pmemory, sizeof(VehicleID));
		memset(sample_vehicle_id, 0, sizeof(VehicleID));
		if (0) {}
		else if (ASN1_SET_VehicleID_entityID(&ws, sample_vehicle_id, sample_temporary_id, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_VehicleID_stationID(&ws, sample_vehicle_id, sample_station_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static VehicleIdent_vehicleClass* sample_vehicle_ident_vehicle_class;
static bool_t init_sample_vehicle_ident_vehicle_class(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_vehicle_ident_vehicle_class != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_vehicle_ident_vehicle_class = (VehicleIdent_vehicleClass*)mpool_malloc(ws.Pmemory, sizeof(VehicleIdent_vehicleClass));
		memset(sample_vehicle_ident_vehicle_class, 0, sizeof(VehicleIdent_vehicleClass));
		if (0) {}
		else if (ASN1_SET_VehicleIdent_vehicleClass_vGroup(&ws, sample_vehicle_ident_vehicle_class, sample_vehicle_group_affected) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_VehicleIdent_vehicleClass_rGroup(&ws, sample_vehicle_ident_vehicle_class, sample_responder_group_affected) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_VehicleIdent_vehicleClass_rEquip(&ws, sample_vehicle_ident_vehicle_class, sample_incident_response_equipment) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static VehicleIdent* sample_vehicle_ident;
static bool_t init_sample_vehicle_ident(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_vehicle_ident != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_vehicle_ident = (VehicleIdent*)mpool_malloc(ws.Pmemory, sizeof(VehicleIdent));
		memset(sample_vehicle_ident, 0, sizeof(VehicleIdent));

		if (0) {}
		else if (ASN1_SET_VehicleIdent_name(&ws, sample_vehicle_ident, sample_descriptive_name, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleIdent_vin(&ws, sample_vehicle_ident, sample_vin_string, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleIdent_ownerCode(&ws, sample_vehicle_ident, sample_ia5string, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleIdent_id(&ws, sample_vehicle_ident, sample_vehicle_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleIdent_vehicleType(&ws, sample_vehicle_ident, sample_vehicle_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleIdent_vehicleClass(&ws, sample_vehicle_ident, sample_vehicle_ident_vehicle_class) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static DDateTime* sample_d_date_time;
static bool_t init_sample_d_date_time(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_d_date_time != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_d_date_time = (DDateTime*)mpool_malloc(ws.Pmemory, sizeof(DDateTime));
		memset(sample_d_date_time, 0, sizeof(DDateTime));
		if (0) {}
		else if (ASN1_SET_DDateTime_year(&ws, sample_d_date_time, sample_d_year) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DDateTime_month(&ws, sample_d_date_time, sample_d_hour) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DDateTime_day(&ws, sample_d_date_time, sample_d_day) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DDateTime_hour(&ws, sample_d_date_time, sample_d_hour) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DDateTime_minute(&ws, sample_d_date_time, sample_d_minute) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DDateTime_second(&ws, sample_d_date_time, sample_d_second) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DDateTime_offset(&ws, sample_d_date_time, sample_d_offset) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static TransmissionAndSpeed* sample_transmission_and_speed;
static bool_t init_sample_transmission_and_speed(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_transmission_and_speed != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_transmission_and_speed = (TransmissionAndSpeed*)mpool_malloc(ws.Pmemory, sizeof(TransmissionAndSpeed));
		memset(sample_transmission_and_speed, 0, sizeof(TransmissionAndSpeed));

		if (0) {}
		else if (ASN1_SET_TransmissionAndSpeed_transmisson(&ws, sample_transmission_and_speed, sample_transmission_state) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TransmissionAndSpeed_speed(&ws, sample_transmission_and_speed, sample_velocity) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static PositionalAccuracy* sample_positional_accuracy;
static bool_t init_sample_positional_accuracy(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_positional_accuracy != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_positional_accuracy = (PositionalAccuracy*)mpool_malloc(ws.Pmemory, sizeof(PositionalAccuracy));
		memset(sample_positional_accuracy, 0, sizeof(PositionalAccuracy));

		if (0) {}
		else if (ASN1_SET_PositionalAccuracy_semiMajor(&ws, sample_positional_accuracy, sample_semi_major_axis_accuracy) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PositionalAccuracy_semiMinor(&ws, sample_positional_accuracy, sample_semi_minor_axis_accuracy) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PositionalAccuracy_orientation(&ws, sample_positional_accuracy, sample_semi_major_axis_orientation) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static PositionConfidenceSet* sample_position_confidence_set;
static bool_t init_sample_position_confidence_set(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_position_confidence_set != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_position_confidence_set = (PositionConfidenceSet*)mpool_malloc(ws.Pmemory, sizeof(PositionConfidenceSet));
		memset(sample_position_confidence_set, 0, sizeof(PositionConfidenceSet));

		if (0) {}
		else if (ASN1_SET_PositionConfidenceSet_pos(&ws, sample_position_confidence_set, sample_position_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PositionConfidenceSet_elevation(&ws, sample_position_confidence_set, sample_elevation_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static SpeedandHeadingandThrottleConfidence* sample_speed_and_heading_and_throttle_confidence;
static bool_t init_sample_speed_and_heading_and_throttle_confidence(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_speed_and_heading_and_throttle_confidence != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);

		sample_speed_and_heading_and_throttle_confidence = (SpeedandHeadingandThrottleConfidence*)mpool_malloc(ws.Pmemory, sizeof(SpeedandHeadingandThrottleConfidence));
		memset(sample_speed_and_heading_and_throttle_confidence, 0, sizeof(SpeedandHeadingandThrottleConfidence));

		if (0) {}
		else if (ASN1_SET_SpeedandHeadingandThrottleConfidence_heading(&ws, sample_speed_and_heading_and_throttle_confidence, sample_heading_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_SpeedandHeadingandThrottleConfidence_speed(&ws, sample_speed_and_heading_and_throttle_confidence, sample_speed_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_SpeedandHeadingandThrottleConfidence_throttle(&ws, sample_speed_and_heading_and_throttle_confidence, sample_throttle_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code);(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static FullPositionVector* sample_full_position_vector;
static bool_t init_sample_full_position_vector(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_full_position_vector != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_full_position_vector = (FullPositionVector*)mpool_malloc(ws.Pmemory, sizeof(FullPositionVector));
		memset(sample_full_position_vector, 0, sizeof(FullPositionVector));

		if (0) {}
		else if (ASN1_SET_FullPositionVector_utcTime(&ws, sample_full_position_vector, sample_d_date_time) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_FullPositionVector_lat(&ws, sample_full_position_vector, sample_latitude) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_FullPositionVector_lon(&ws, sample_full_position_vector, sample_longitude) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_FullPositionVector_elevation(&ws, sample_full_position_vector, sample_elevation) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_FullPositionVector_heading(&ws, sample_full_position_vector, sample_heading) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_FullPositionVector_speed(&ws, sample_full_position_vector, sample_transmission_and_speed) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_FullPositionVector_posAccuracy(&ws, sample_full_position_vector, sample_positional_accuracy) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_FullPositionVector_timeConfidence(&ws, sample_full_position_vector, sample_time_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_FullPositionVector_posConfidence(&ws, sample_full_position_vector, sample_position_confidence_set) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_FullPositionVector_speedConfidence(&ws, sample_full_position_vector, sample_speed_and_heading_and_throttle_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static VehicleClassification* sample_vehicle_classification;
static bool_t init_sample_vehicle_classification(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_vehicle_classification != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_vehicle_classification = (VehicleClassification*)mpool_malloc(ws.Pmemory, sizeof(VehicleClassification));
		memset(sample_vehicle_classification, 0, sizeof(VehicleClassification));
		if (0) {}
		else if (ASN1_SET_VehicleClassification_keyType(&ws, sample_vehicle_classification, sample_basic_vehicle_class) < 0)ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleClassification_role(&ws, sample_vehicle_classification, sample_basic_vehicle_role) < 0)ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleClassification_iso3883(&ws, sample_vehicle_classification, sample_iso_3833_vehicle_type) < 0)ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleClassification_hpmsType(&ws, sample_vehicle_classification, sample_vehicle_type) < 0)ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleClassification_vehicleType(&ws, sample_vehicle_classification, sample_vehicle_group_affected) < 0)ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleClassification_responseEquip(&ws, sample_vehicle_classification, sample_incident_response_equipment) < 0)ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleClassification_responderType(&ws, sample_vehicle_classification, sample_responder_group_affected) < 0)ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleClassification_fuelType(&ws, sample_vehicle_classification, sample_fuel_type) < 0)ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_VehicleClassification_regional(&ws, sample_vehicle_classification, ) < 0 )ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static PathHistoryPoint* sample_path_history_point;
static bool_t init_sample_path_history_point(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_path_history_point != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_path_history_point = (PathHistoryPoint*)mpool_malloc(ws.Pmemory, sizeof(PathHistoryPoint));
		memset(sample_path_history_point, 0, sizeof(PathHistoryPoint));

		if (0) {}
		else if (ASN1_SET_PathHistoryPoint_latOffset(&ws, sample_path_history_point, sample_offset_ll_b18) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PathHistoryPoint_lonOffset(&ws, sample_path_history_point, sample_offset_ll_b18) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PathHistoryPoint_elevationOffset(&ws, sample_path_history_point, sample_vert_offset_b12) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PathHistoryPoint_timeOffset(&ws, sample_path_history_point, sample_time_offset) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PathHistoryPoint_speed(&ws, sample_path_history_point, sample_heading) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PathHistoryPoint_posAccuracy(&ws, sample_path_history_point, sample_positional_accuracy) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PathHistoryPoint_heading(&ws, sample_path_history_point, sample_coarse_heading) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static PathHistoryPointList* sample_path_history_point_list;
static bool_t init_sample_path_history_point_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_path_history_point_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_path_history_point_list = (PathHistoryPointList*)mpool_malloc(ws.Pmemory, sizeof(PathHistoryPointList));
		memset(sample_path_history_point_list, 0, sizeof(PathHistoryPointList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_path_history_point_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_path_history_point_list, sample_path_history_point) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); //(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static PathHistory* sample_path_history;
static bool_t init_sample_path_history(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_path_history != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_path_history = (PathHistory*)mpool_malloc(ws.Pmemory, sizeof(PathHistory));
		memset(sample_path_history, 0, sizeof(PathHistory));

		if (0) {}
		else if (ASN1_SET_PathHistory_initialPosition(&ws, sample_path_history, sample_full_position_vector) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PathHistory_currGNSSstatus(&ws, sample_path_history, sample_gnss_status, 8) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PathHistory_crumbData(&ws, sample_path_history, sample_path_history_point_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static PathPrediction* sample_path_prediction;
static bool_t init_sample_path_prediction(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_path_prediction != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_path_prediction = (PathPrediction*)mpool_malloc(ws.Pmemory, sizeof(PathPrediction));
		memset(sample_path_prediction, 0, sizeof(PathPrediction));

		if (0) {}
		else if (ASN1_SET_PathPrediction_radiusOfCurve(&ws, sample_path_prediction, sample_radius_of_curvature) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PathPrediction_confidence(&ws, sample_path_prediction, sample_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static VehicleSafetyExtensions* sample_vehicle_safety_extension;
static bool_t init_sample_vehicle_safety_extension(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_vehicle_safety_extension != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_vehicle_safety_extension = (VehicleSafetyExtensions*)mpool_malloc(ws.Pmemory, sizeof(VehicleSafetyExtensions));
		memset(sample_vehicle_safety_extension, 0, sizeof(VehicleSafetyExtensions));

		if (0) {}
		else if (ASN1_SET_VehicleSafetyExtensions_events(&ws, sample_vehicle_safety_extension, sample_vehicle_event_flags, 13) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleSafetyExtensions_pathHistory(&ws, sample_vehicle_safety_extension, sample_path_history) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleSafetyExtensions_pathPrediction(&ws, sample_vehicle_safety_extension, sample_path_prediction) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleSafetyExtensions_lights(&ws, sample_vehicle_safety_extension, sample_exterior_lights, 9) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static WiperSet* sample_wiper_set;
static bool_t init_sample_wiper_set(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_wiper_set != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_wiper_set = (WiperSet*)mpool_malloc(ws.Pmemory, sizeof(WiperSet));
		memset(sample_wiper_set, 0, sizeof(WiperSet));
		if (0) {}
		else if (ASN1_SET_WiperSet_statusFront(&ws, sample_wiper_set, sample_wiper_status) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_WiperSet_rateFront(&ws, sample_wiper_set, sample_wiper_rate) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_WiperSet_statusRear(&ws, sample_wiper_set, sample_wiper_status) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_WiperSet_rateRear(&ws, sample_wiper_set, sample_wiper_rate) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static BrakeSystemStatus* sample_brake_system_status;
static bool_t init_sample_brake_system_status(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_brake_system_status != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_brake_system_status = (BrakeSystemStatus*)mpool_malloc(ws.Pmemory, sizeof(BrakeSystemStatus));
		memset(sample_brake_system_status, 0, sizeof(BrakeSystemStatus));
		if (0) {}
		else if (ASN1_SET_BrakeSystemStatus_wheelBrakes(&ws, sample_brake_system_status, sample_brake_applied_status, 5) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BrakeSystemStatus_traction(&ws, sample_brake_system_status, sample_traction_control_status) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BrakeSystemStatus_abs(&ws, sample_brake_system_status, sample_anti_lock_brake_status) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BrakeSystemStatus_scs(&ws, sample_brake_system_status, sample_stability_control_status) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BrakeSystemStatus_brakeBoost(&ws, sample_brake_system_status, sample_brake_boost_applied) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BrakeSystemStatus_auxBrakes(&ws, sample_brake_system_status, sample_auxiliary_brake_status) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static VehicleStatus_steering* sample_vehicle_status_steering;
static bool_t init_sample_vehicle_status_steering(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_vehicle_status_steering != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_vehicle_status_steering = (VehicleStatus_steering*)mpool_malloc(ws.Pmemory, sizeof(VehicleStatus_steering));
		memset(sample_vehicle_status_steering, 0, sizeof(VehicleStatus_steering));

		if (0) {}
		else if (ASN1_SET_VehicleStatus_steering_angle(&ws, sample_vehicle_status_steering, sample_steering_wheel_angle) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_steering_confidence(&ws, sample_vehicle_status_steering, sample_steering_wheel_angle_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_steering_rate(&ws, sample_vehicle_status_steering, sample_steering_wheel_angle_rate_of_change) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_steering_wheels(&ws, sample_vehicle_status_steering, sample_driving_wheel_angle) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static AccelerationSet4Way* sample_acceleration_set_4_way;
static bool_t init_sample_acceleration_set_4_way(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_acceleration_set_4_way != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_acceleration_set_4_way = (AccelerationSet4Way*)mpool_malloc(ws.Pmemory, sizeof(AccelerationSet4Way));
		memset(sample_acceleration_set_4_way, 0, sizeof(AccelerationSet4Way));

		if (0) {}
		else if (ASN1_SET_AccelerationSet4Way_lon(&ws, sample_acceleration_set_4_way, sample_longitude) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_AccelerationSet4Way_lat(&ws, sample_acceleration_set_4_way, sample_latitude) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_AccelerationSet4Way_vert(&ws, sample_acceleration_set_4_way, sample_vertical_acceleration) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_AccelerationSet4Way_yaw(&ws, sample_acceleration_set_4_way, sample_yaw_rate) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static AccelSteerYawRateConfidence* sample_accel_steer_yaw_rate_confidence;
static bool_t init_sample_accel_steer_yaw_rate_confidence(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_accel_steer_yaw_rate_confidence != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_accel_steer_yaw_rate_confidence = (AccelSteerYawRateConfidence*)mpool_malloc(ws.Pmemory, sizeof(AccelSteerYawRateConfidence));
		memset(sample_accel_steer_yaw_rate_confidence, 0, sizeof(AccelSteerYawRateConfidence));

		if (0) {}
		else if (ASN1_SET_AccelSteerYawRateConfidence_yawRate(&ws, sample_accel_steer_yaw_rate_confidence, sample_yaw_rate_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_AccelSteerYawRateConfidence_acceleration(&ws, sample_accel_steer_yaw_rate_confidence, sample_acceleration_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_AccelSteerYawRateConfidence_steeringWheelAngle(&ws, sample_accel_steer_yaw_rate_confidence, sample_steering_wheel_angle_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static ConfidenceSet* sample_confidence_set;
static bool_t init_sample_confidence_set(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_confidence_set != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_confidence_set = (ConfidenceSet*)mpool_malloc(ws.Pmemory, sizeof(ConfidenceSet));
		memset(sample_confidence_set, 0, sizeof(ConfidenceSet));
		if (0) {}
		else if (ASN1_SET_ConfidenceSet_accelConfidence(&ws, sample_confidence_set, sample_accel_steer_yaw_rate_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ConfidenceSet_speedConfidence(&ws, sample_confidence_set, sample_speed_and_heading_and_throttle_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ConfidenceSet_timeConfidence(&ws, sample_confidence_set, sample_time_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ConfidenceSet_posConfidence(&ws, sample_confidence_set, sample_position_confidence_set) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ConfidenceSet_steerConfidence(&ws, sample_confidence_set, sample_steering_wheel_angle_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ConfidenceSet_headingConfidence(&ws, sample_confidence_set, sample_heading_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ConfidenceSet_throttleConfidence(&ws, sample_confidence_set, sample_throttle_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static VehicleStatus_accelSets* sample_vehicle_status_accel_sets;
static bool_t init_sample_vehicle_status_accel_sets(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_vehicle_status_accel_sets != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_vehicle_status_accel_sets = (VehicleStatus_accelSets*)mpool_malloc(ws.Pmemory, sizeof(VehicleStatus_accelSets));
		memset(sample_vehicle_status_accel_sets, 0, sizeof(VehicleStatus_accelSets));
		// ~~~

		if (0) {}
		else if (ASN1_SET_VehicleStatus_accelSets_accel4way(&ws, sample_vehicle_status_accel_sets, sample_acceleration_set_4_way) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_accelSets_vertAccelThres(&ws, sample_vehicle_status_accel_sets, sample_vertical_acceleration_threshold, 5) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_accelSets_yawRateCon(&ws, sample_vehicle_status_accel_sets, sample_yaw_rate_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_accelSets_hozAccelCon(&ws, sample_vehicle_status_accel_sets, sample_acceleration_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_accelSets_confidenceSet(&ws, sample_vehicle_status_accel_sets, sample_confidence_set) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static VehicleStatus_object* sample_vehicle_status_object;
static bool_t init_sample_vehicle_status_object(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_vehicle_status_object != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_vehicle_status_object = (VehicleStatus_object*)mpool_malloc(ws.Pmemory, sizeof(VehicleStatus_object));
		memset(sample_vehicle_status_object, 0, sizeof(VehicleStatus_object));

		if (0) {}
		else if (ASN1_SET_VehicleStatus_object_obDist(&ws, sample_vehicle_status_object, sample_obstacle_distance) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_object_obDirect(&ws, sample_vehicle_status_object, sample_angle) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_object_dateTime(&ws, sample_vehicle_status_object, sample_d_date_time) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static BumperHeights* sample_bumper_heights;
static bool_t init_sample_bumper_heights(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_bumper_heights != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_bumper_heights = (BumperHeights*)mpool_malloc(ws.Pmemory, sizeof(BumperHeights));
		memset(sample_bumper_heights, 0, sizeof(BumperHeights));

		if (0) {}
		else if (ASN1_SET_BumperHeights_front(&ws, sample_bumper_heights, sample_bumper_height) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BumperHeights_rear(&ws, sample_bumper_heights, sample_bumper_height) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static VehicleStatus_vehicleData* sample_vehicle_status_vehicle_data;
static bool_t init_sample_vehicle_status_vehicle_data(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_vehicle_status_vehicle_data != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_vehicle_status_vehicle_data = (VehicleStatus_vehicleData*)mpool_malloc(ws.Pmemory, sizeof(VehicleStatus_vehicleData));
		memset(sample_vehicle_status_vehicle_data, 0, sizeof(VehicleStatus_vehicleData));

		if (0) {}
		else if (ASN1_SET_VehicleStatus_vehicleData_height(&ws, sample_vehicle_status_vehicle_data, sample_vehicle_height) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_vehicleData_bumpers(&ws, sample_vehicle_status_vehicle_data, sample_bumper_heights) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_vehicleData_mass(&ws, sample_vehicle_status_vehicle_data, sample_vehicle_mass) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_vehicleData_trailerWeight(&ws, sample_vehicle_status_vehicle_data, sample_trailer_weight) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_vehicleData_type(&ws, sample_vehicle_status_vehicle_data, sample_vehicle_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static TireData* sample_tire_data;
static bool_t init_sample_tire_data(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_tire_data != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_tire_data = (TireData*)mpool_malloc(ws.Pmemory, sizeof(TireData));
		memset(sample_tire_data, 0, sizeof(TireData));

		if (0) {}
		else if (ASN1_SET_TireData_location(&ws, sample_tire_data, sample_tire_location) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TireData_pressure(&ws, sample_tire_data, sample_tire_pressure) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TireData_temp(&ws, sample_tire_data, sample_tire_temp) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TireData_wheelSensorStatus(&ws, sample_tire_data, sample_wheel_sensor_status) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TireData_wheelEndElectFault(&ws, sample_tire_data, sample_wheel_end_elect_fault) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TireData_leakageRate(&ws, sample_tire_data, sample_tire_leakage_rate) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TireData_detection(&ws, sample_tire_data, sample_tire_pressure_threshold_detection) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static TireDataList* sample_tire_data_list;
static bool_t init_sample_tire_data_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_tire_data_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_tire_data_list = (TireDataList*)mpool_malloc(ws.Pmemory, sizeof(TireDataList));
		memset(sample_tire_data_list, 0, sizeof(TireDataList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_tire_data_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_tire_data_list, sample_tire_data) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static AxleWeightSet* sample_axle_weight_set;
static bool_t init_sample_axle_weight_set(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_axle_weight_set != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_axle_weight_set = (AxleWeightSet*)mpool_malloc(ws.Pmemory, sizeof(AxleWeightSet));
		memset(sample_axle_weight_set, 0, sizeof(AxleWeightSet));
		if (0) {}
		else if (ASN1_SET_AxleWeightSet_location(&ws, sample_axle_weight_set, sample_axle_location) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_AxleWeightSet_weight(&ws, sample_axle_weight_set, sample_axle_weight) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static AxleWeightList* sample_axle_weight_list;
static bool_t init_sample_axle_weight_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_axle_weight_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_axle_weight_list = (AxleWeightList*)mpool_malloc(ws.Pmemory, sizeof(AxleWeightList));
		memset(sample_axle_weight_list, 0, sizeof(AxleWeightList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_axle_weight_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_axle_weight_list, sample_axle_weight_set) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static J1939DataItems* sample_j1939_data_items;
static bool_t init_sample_j1939_data_items(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_j1939_data_items != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_j1939_data_items = (J1939DataItems*)mpool_malloc(ws.Pmemory, sizeof(J1939DataItems));
		memset(sample_j1939_data_items, 0, sizeof(J1939DataItems));
		if (0) {}
		else if (ASN1_SET_J1939DataItems_tires(&ws, sample_j1939_data_items, sample_tire_data_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_J1939DataItems_axles(&ws, sample_j1939_data_items, sample_axle_weight_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_J1939DataItems_trailerWeight(&ws, sample_j1939_data_items, sample_trailer_weight) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_J1939DataItems_cargoWeight(&ws, sample_j1939_data_items, sample_cargo_weight) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_J1939DataItems_steeringAxleTemperature(&ws, sample_j1939_data_items, sample_steering_axle_temperature) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_J1939DataItems_driveAxleLocation(&ws, sample_j1939_data_items, sample_drive_axle_location) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_J1939DataItems_driveAxleLiftAirPressure(&ws, sample_j1939_data_items, sample_drive_axle_lift_air_pressure) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_J1939DataItems_driveAxleTemperature(&ws, sample_j1939_data_items, sample_drive_axle_temperature) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_J1939DataItems_driveAxleLubePressure(&ws, sample_j1939_data_items, sample_drive_axle_lube_pressure) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_J1939DataItems_steeringAxleLubePressure(&ws, sample_j1939_data_items, sample_steering_axle_lube_pressure) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static VehicleStatus_weatherReport* sample_vehicle_status_weather_report;
static bool_t init_sample_vehicle_status_weather_report(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_vehicle_status_weather_report != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_vehicle_status_weather_report = (VehicleStatus_weatherReport*)mpool_malloc(ws.Pmemory, sizeof(VehicleStatus_weatherReport));
		memset(sample_vehicle_status_weather_report, 0, sizeof(VehicleStatus_weatherReport));

		if (0) {}
		else if (ASN1_SET_VehicleStatus_weatherReport_isRaining(&ws, sample_vehicle_status_weather_report, sample_ess_precip_yes_no) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_weatherReport_rainRate(&ws, sample_vehicle_status_weather_report, sample_ess_precip_rate) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_weatherReport_precipSituation(&ws, sample_vehicle_status_weather_report, sample_ess_precip_situation) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_weatherReport_solarRadiation(&ws, sample_vehicle_status_weather_report, sample_ess_solar_radiation) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_weatherReport_friction(&ws, sample_vehicle_status_weather_report, sample_ess_mobile_friction) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}



static VehicleStatus* sample_vehicle_status;
static bool_t init_sample_vehicle_status(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_vehicle_status != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_vehicle_status = (VehicleStatus*)mpool_malloc(ws.Pmemory, sizeof(VehicleStatus));
		memset(sample_vehicle_status, 0, sizeof(VehicleStatus));

		if (0) {}
		else if (ASN1_SET_VehicleStatus_lights(&ws, sample_vehicle_status, sample_exterior_lights, 9) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_lightBar(&ws, sample_vehicle_status, sample_light_bar_in_use) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_wipers(&ws, sample_vehicle_status, sample_wiper_set) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_brakeStatus(&ws, sample_vehicle_status, sample_brake_system_status) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_brakePressure(&ws, sample_vehicle_status, sample_brake_applied_pressure) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_roadFriction(&ws, sample_vehicle_status, sample_coefficient_of_friction) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_sunData(&ws, sample_vehicle_status, sample_sun_sensor) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_rainData(&ws, sample_vehicle_status, sample_rain_sensor) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_airTemp(&ws, sample_vehicle_status, sample_ambient_air_temperature) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_airPres(&ws, sample_vehicle_status, sample_ambient_air_pressure) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_steering(&ws, sample_vehicle_status, sample_vehicle_status_steering) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_accelSets(&ws, sample_vehicle_status, sample_vehicle_status_accel_sets) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_object(&ws, sample_vehicle_status, sample_vehicle_status_object) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_fullPos(&ws, sample_vehicle_status, sample_full_position_vector) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_throttlePos(&ws, sample_vehicle_status, sample_throttle_position) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_speedHeadC(&ws, sample_vehicle_status, sample_speed_and_heading_and_throttle_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_speedC(&ws, sample_vehicle_status, sample_speed_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_vehicleData(&ws, sample_vehicle_status, sample_vehicle_status_vehicle_data) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_vehicleIdent(&ws, sample_vehicle_status, sample_vehicle_ident) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_j1939data(&ws, sample_vehicle_status, sample_j1939_data_items) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_weatherReport(&ws, sample_vehicle_status, sample_vehicle_status_weather_report) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleStatus_gnssStatus(&ws, sample_vehicle_status, sample_gnss_status, 8) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static Snapshot* sample_snapshot;
static bool_t init_sample_snapshot(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_snapshot != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_snapshot = (Snapshot*)mpool_malloc(ws.Pmemory, sizeof(Snapshot));
		memset(sample_snapshot, 0, sizeof(Snapshot));

		if (0) {}
		else if (ASN1_SET_Snapshot_thePosition(&ws, sample_snapshot, sample_full_position_vector) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Snapshot_safetyExt(&ws, sample_snapshot, sample_vehicle_safety_extension) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Snapshot_dataSet(&ws, sample_snapshot, sample_vehicle_status) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static ProbeVehicleData_snapshots* sample_pvd_snapshots;
static bool_t init_sample_pvd_snapshots(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_pvd_snapshots != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_pvd_snapshots = (ProbeVehicleData_snapshots*)mpool_malloc(ws.Pmemory, sizeof(ProbeVehicleData_snapshots));
		memset(sample_pvd_snapshots, 0, sizeof(ProbeVehicleData_snapshots));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_pvd_snapshots) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_pvd_snapshots, sample_snapshot) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static IntersectionReferenceID* sample_intersection_reference_id;
static bool_t init_sample_intersection_reference_id(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_intersection_reference_id != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_intersection_reference_id = (IntersectionReferenceID*)mpool_malloc(ws.Pmemory, sizeof(IntersectionReferenceID));
		memset(sample_intersection_reference_id, 0, sizeof(IntersectionReferenceID));

		if (0) {}
		else if (ASN1_SET_IntersectionReferenceID_region(&ws, sample_intersection_reference_id, sample_road_regulator_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_IntersectionReferenceID_id(&ws, sample_intersection_reference_id, sample_intersection_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static Position3D* sample_position_3d;
static bool_t init_sample_position_3d(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_position_3d != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_position_3d = (Position3D*)mpool_malloc(ws.Pmemory, sizeof(Position3D));
		memset(sample_position_3d, 0, sizeof(Position3D));

		if (0) {}
		else if (ASN1_SET_Position3D_lat(&ws, sample_position_3d, sample_latitude) < 0)ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Position3D_lon(&ws, sample_position_3d, sample_longitude) < 0)ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Position3D_elevation(&ws, sample_position_3d, sample_elevation) < 0)ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_Position3D_regional(&ws, sample_position_3d, sanm) < 0 )ERR_SET_OUT(errp,EFAULT); // region ¿µ¿ª

		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static RegulatorySpeedLimit* sample_regulatory_speed_limit;
static bool_t init_sample_regulatory_speed_limit(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_regulatory_speed_limit != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_regulatory_speed_limit = (RegulatorySpeedLimit*)mpool_malloc(ws.Pmemory, sizeof(RegulatorySpeedLimit));
		memset(sample_regulatory_speed_limit, 0, sizeof(RegulatorySpeedLimit));

		if (0) {}
		else if (ASN1_SET_RegulatorySpeedLimit_type(&ws, sample_regulatory_speed_limit, sample_speed_limit_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RegulatorySpeedLimit_speed(&ws, sample_regulatory_speed_limit, sample_velocity) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static SpeedLimitList* sample_speed_limit_list;
static bool_t init_sample_speed_limit_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_speed_limit_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_speed_limit_list = (SpeedLimitList*)mpool_malloc(ws.Pmemory, sizeof(SpeedLimitList));
		memset(sample_speed_limit_list, 0, sizeof(SpeedLimitList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_speed_limit_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_speed_limit_list, sample_regulatory_speed_limit) < 0)ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}


	return ERR_IS_SUCCESS(errp);
}

static LaneTypeAttributes* sample_lane_type_attributes;
static bool_t init_sample_lane_type_attributes(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_lane_type_attributes != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_lane_type_attributes = (LaneTypeAttributes*)mpool_malloc(ws.Pmemory, sizeof(LaneTypeAttributes));
		memset(sample_lane_type_attributes, 0, sizeof(LaneTypeAttributes));

		if (0) {}
		else if (ASN1_SET_LaneTypeAttributes_vehicle(&ws, sample_lane_type_attributes, sample_lane_type_attributes_vehicle, 8) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_LaneTypeAttributes_crosswalk(&ws, sample_lane_type_attributes, sample_lane_type_attributes_crosswalk, 16) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_LaneTypeAttributes_bikeLane(&ws, sample_lane_type_attributes, sample_lane_type_attributes_bike, 16) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_LaneTypeAttributes_sidewalk(&ws, sample_lane_type_attributes, sample_lane_type_attributes_sidewalk, 16) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_LaneTypeAttributes_median(&ws, sample_lane_type_attributes, sample_lane_type_attributes_barrier, 16) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_LaneTypeAttributes_striping(&ws, sample_lane_type_attributes, sample_lane_type_attributes_striping, 16) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_LaneTypeAttributes_trackedVehicle(&ws, sample_lane_type_attributes, sample_lane_type_attributes_tracked_vehicle, 16) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_LaneTypeAttributes_parking(&ws, sample_lane_type_attributes, sample_lane_type_attributes_parking, 16) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static LaneAttributes* sample_lane_attributes;
static bool_t init_sample_lane_attributes(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_lane_attributes != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_lane_attributes = (LaneAttributes*)mpool_malloc(ws.Pmemory, sizeof(LaneAttributes));
		memset(sample_lane_attributes, 0, sizeof(LaneAttributes));

		if (0) {}
		else if (ASN1_SET_LaneAttributes_directionalUse(&ws, sample_lane_attributes, sample_lane_direction, 2) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_LaneAttributes_sharedWith(&ws, sample_lane_attributes, sample_lane_sharing, 10) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_LaneAttributes_laneType(&ws, sample_lane_attributes, sample_lane_type_attributes) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_LaneAttributes_regional(&ws, sample_lane_attributes, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static Node_XY_20b* sample_node_xy_20_b;
static Node_XY_22b* sample_node_xy_22_b;
static Node_XY_24b* sample_node_xy_24_b;
static Node_XY_26b* sample_node_xy_26_b;
static Node_XY_28b* sample_node_xy_28_b;
static Node_XY_32b* sample_node_xy_32_b;
static Node_LLmD_64b* sample_node_llmd_64_b;

static bool_t init_sample_node_xy_20_b(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_xy_20_b != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_xy_20_b = (Node_XY_20b*)mpool_malloc(ws.Pmemory, sizeof(Node_XY_20b));
		memset(sample_node_xy_20_b, 0, sizeof(Node_XY_20b));

		if (0) {}
		else if (ASN1_SET_Node_XY_20b_x(&ws, sample_node_xy_20_b, sample_offset_b10) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Node_XY_20b_y(&ws, sample_node_xy_20_b, sample_offset_b10) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_node_xy_22_b(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_xy_22_b != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_xy_22_b = (Node_XY_22b*)mpool_malloc(ws.Pmemory, sizeof(Node_XY_22b));
		memset(sample_node_xy_22_b, 0, sizeof(Node_XY_22b));

		if (0) {}
		else if (ASN1_SET_Node_XY_22b_x(&ws, sample_node_xy_22_b, sample_offset_b11) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Node_XY_22b_y(&ws, sample_node_xy_22_b, sample_offset_b11) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_node_xy_24_b(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_xy_24_b != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_xy_24_b = (Node_XY_24b*)mpool_malloc(ws.Pmemory, sizeof(Node_XY_24b));
		memset(sample_node_xy_24_b, 0, sizeof(Node_XY_24b));

		if (0) {}
		else if (ASN1_SET_Node_XY_24b_x(&ws, sample_node_xy_24_b, sample_offset_b12) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Node_XY_24b_y(&ws, sample_node_xy_24_b, sample_offset_b12) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_node_xy_26_b(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_xy_26_b != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_xy_26_b = (Node_XY_26b*)mpool_malloc(ws.Pmemory, sizeof(Node_XY_26b));
		memset(sample_node_xy_26_b, 0, sizeof(Node_XY_26b));

		if (0) {}
		else if (ASN1_SET_Node_XY_26b_x(&ws, sample_node_xy_26_b, sample_offset_b13) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Node_XY_26b_y(&ws, sample_node_xy_26_b, sample_offset_b13) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_node_xy_28_b(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_xy_28_b != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_xy_28_b = (Node_XY_28b*)mpool_malloc(ws.Pmemory, sizeof(Node_XY_28b));
		memset(sample_node_xy_28_b, 0, sizeof(Node_XY_28b));

		if (0) {}
		else if (ASN1_SET_Node_XY_28b_x(&ws, sample_node_xy_28_b, sample_offset_b14) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Node_XY_28b_y(&ws, sample_node_xy_28_b, sample_offset_b14) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_node_xy_32_b(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_xy_32_b != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_xy_32_b = (Node_XY_32b*)mpool_malloc(ws.Pmemory, sizeof(Node_XY_32b));
		memset(sample_node_xy_32_b, 0, sizeof(Node_XY_32b));

		if (0) {}
		else if (ASN1_SET_Node_XY_32b_x(&ws, sample_node_xy_32_b, sample_offset_b16) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Node_XY_32b_y(&ws, sample_node_xy_32_b, sample_offset_b16) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_node_llmd_64_b(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_llmd_64_b != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_llmd_64_b = (Node_LLmD_64b*)mpool_malloc(ws.Pmemory, sizeof(Node_LLmD_64b));
		memset(sample_node_llmd_64_b, 0, sizeof(Node_LLmD_64b));

		if (0) {}
		else if (ASN1_SET_Node_LLmD_64b_lon(&ws, sample_node_llmd_64_b, sample_longitude) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Node_LLmD_64b_lat(&ws, sample_node_llmd_64_b, sample_latitude) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static NodeOffsetPointXY* sample_node_offset_point_xy;
static bool_t init_sample_node_offset_point_xy(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_offset_point_xy != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_offset_point_xy = (NodeOffsetPointXY*)mpool_malloc(ws.Pmemory, sizeof(NodeOffsetPointXY));
		memset(sample_node_offset_point_xy, 0, sizeof(NodeOffsetPointXY));

		if (0) {}
		else if (ASN1_SET_NodeOffsetPointXY_node_XY1(&ws, sample_node_offset_point_xy, sample_node_xy_20_b) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_NodeOffsetPointXY_node_XY2(&ws, sample_node_offset_point_xy, sample_node_xy_22_b) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_NodeOffsetPointXY_node_XY3(&ws, sample_node_offset_point_xy, sample_node_xy_24_b) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_NodeOffsetPointXY_node_XY4(&ws, sample_node_offset_point_xy, sample_node_xy_26_b) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_NodeOffsetPointXY_node_XY5(&ws, sample_node_offset_point_xy, sample_node_xy_28_b) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_NodeOffsetPointXY_node_XY6(&ws, sample_node_offset_point_xy, sample_node_xy_32_b) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_NodeOffsetPointXY_node_LatLon(&ws, sample_node_offset_point_xy, sample_node_llmd_64_b) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_NodeOffsetPointXY_regional(&ws, sample_node_offset_point_xy, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static NodeAttributeXYList* sample_node_attribute_xy_list;
static bool_t init_sample_node_attribute_xy_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_node_attribute_xy_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_attribute_xy_list = (NodeAttributeXYList*)mpool_malloc(ws.Pmemory, sizeof(NodeAttributeXYList));
		memset(sample_node_attribute_xy_list, 0, sizeof(NodeAttributeXYList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_node_attribute_xy_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_node_attribute_xy_list, (ASNVoid*)&sample_node_attribute_xy) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static SegmentAttributeXYList* sample_segment_attribute_xy_list;
static bool_t init_sample_segment_attribute_xy_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_segment_attribute_xy_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_segment_attribute_xy_list = (SegmentAttributeXYList*)mpool_malloc(ws.Pmemory, sizeof(SegmentAttributeXYList));
		memset(sample_segment_attribute_xy_list, 0, sizeof(SegmentAttributeXYList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_segment_attribute_xy_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_segment_attribute_xy_list, (ASNVoid*)&sample_segment_attribute_xy));
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static LaneDataAttribute* sample_lane_data_attribute;
static bool_t init_sample_lane_data_attribute(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_lane_data_attribute != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_lane_data_attribute = (LaneDataAttribute*)mpool_malloc(ws.Pmemory, sizeof(LaneDataAttribute));
		memset(sample_lane_data_attribute, 0, sizeof(LaneDataAttribute));

		if (0) {}
		else if (ASN1_SET_LaneDataAttribute_pathEndPointAngle(&ws, sample_lane_data_attribute, sample_delta_angle) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_LaneDataAttribute_laneCrownPointCenter(&ws, sample_lane_data_attribute, SAMPLE_ROADWAY_CROWN_ANGLE) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_LaneDataAttribute_laneCrownPointLeft(&ws, sample_lane_data_attribute, SAMPLE_ROADWAY_CROWN_ANGLE) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_LaneDataAttribute_laneCrownPointRight(&ws, sample_lane_data_attribute, SAMPLE_ROADWAY_CROWN_ANGLE) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_LaneDataAttribute_laneAngle(&ws, sample_lane_data_attribute, SAMPLE_MERGE_DIVERGE_NODE_ANGLE) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_LaneDataAttribute_speedLimits(&ws, sample_lane_data_attribute, sample_speed_limit_list) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_LaneDataAttribute_regional(&ws, sample_lane_data_attribute, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static LaneDataAttributeList* sample_lane_data_attribute_list;
static bool_t init_sample_lane_data_attribute_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_lane_data_attribute_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_lane_data_attribute_list = (LaneDataAttributeList*)mpool_malloc(ws.Pmemory, sizeof(LaneDataAttributeList));
		memset(sample_lane_data_attribute_list, 0, sizeof(LaneDataAttributeList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_lane_data_attribute_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_lane_data_attribute_list, sample_lane_data_attribute) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static NodeAttributeSetXY* sample_node_attribute_set_xy;
static bool_t init_sample_node_attribute_set_xy(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_node_attribute_set_xy != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_attribute_set_xy = (NodeAttributeSetXY*)mpool_malloc(ws.Pmemory, sizeof(NodeAttributeSetXY));
		memset(sample_node_attribute_set_xy, 0, sizeof(NodeAttributeSetXY));

		if (0) {}
		else if (ASN1_SET_NodeAttributeSetXY_localNode(&ws, sample_node_attribute_set_xy, sample_node_attribute_xy_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_NodeAttributeSetXY_disabled(&ws, sample_node_attribute_set_xy, sample_segment_attribute_xy_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_NodeAttributeSetXY_enabled(&ws, sample_node_attribute_set_xy, sample_segment_attribute_xy_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_NodeAttributeSetXY_data(&ws, sample_node_attribute_set_xy, sample_lane_data_attribute_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_NodeAttributeSetXY_dWidth(&ws, sample_node_attribute_set_xy, sample_offset_b10) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_NodeAttributeSetXY_dElevation(&ws, sample_node_attribute_set_xy, sample_offset_b10) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_NodeAttributeSetXY_regional(&ws, sample_node_attribute_set_xy, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static NodeXY* sample_node_xy_1;
static NodeXY* sample_node_xy_2;
static bool_t init_sample_node_xy_1(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_xy_1 != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_xy_1 = (NodeXY*)mpool_malloc(ws.Pmemory, sizeof(NodeXY));
		memset(sample_node_xy_1, 0, sizeof(NodeXY));

		if (0) {}
		else if (ASN1_SET_NodeXY_delta(&ws, sample_node_xy_1, sample_node_offset_point_xy) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_NodeXY_attributes(&ws, sample_node_xy_1, sample_node_attribute_set_xy) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_node_xy_2(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_xy_2 != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_xy_2 = (NodeXY*)mpool_malloc(ws.Pmemory, sizeof(NodeXY));
		memset(sample_node_xy_2, 0, sizeof(NodeXY));

		if (0) {}
		else if (ASN1_SET_NodeXY_delta(&ws, sample_node_xy_2, sample_node_offset_point_xy) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_NodeXY_attributes(&ws, sample_node_xy_2, sample_node_attribute_set_xy) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static NodeSetXY* sample_node_set_xy;
static bool_t init_sample_node_set_xy(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_set_xy != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_set_xy = (NodeSetXY*)mpool_malloc(ws.Pmemory, sizeof(NodeSetXY));
		memset(sample_node_set_xy, 0, sizeof(NodeSetXY));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_node_set_xy) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_node_set_xy, sample_node_xy_1) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_node_set_xy, sample_node_xy_2) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static ComputedLane_offsetXaxis* sample_computed_lane_offset_x_axis;
static bool_t init_sample_computed_lane_offset_x_axis(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_computed_lane_offset_x_axis != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_computed_lane_offset_x_axis = (ComputedLane_offsetXaxis*)mpool_malloc(ws.Pmemory, sizeof(ComputedLane_offsetXaxis));
		memset(sample_computed_lane_offset_x_axis, 0, sizeof(ComputedLane_offsetXaxis));

		if (0) {}
		else if (ASN1_SET_ComputedLane_offsetXaxis_small(&ws, sample_computed_lane_offset_x_axis, sample_driven_line_offset_sm) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_ComputedLane_offsetXaxis_large(&ws, sample_computed_lane_offset_x_axis, SAMPLE_DRIVEN_LINE_OFFSET_LG) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static ComputedLane_offsetYaxis* sample_computed_lane_offset_y_axis;
static bool_t init_sample_computed_lane_offset_y_axis(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_computed_lane_offset_y_axis != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_computed_lane_offset_y_axis = (ComputedLane_offsetYaxis*)mpool_malloc(ws.Pmemory, sizeof(ComputedLane_offsetYaxis));
		memset(sample_computed_lane_offset_y_axis, 0, sizeof(ComputedLane_offsetYaxis));

		if (0) {}
		else if (ASN1_SET_ComputedLane_offsetYaxis_small(&ws, sample_computed_lane_offset_y_axis, sample_driven_line_offset_sm) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_ComputedLane_offsetYaxis_large(&ws, sample_computed_lane_offset_x_axis, SAMPLE_DRIVEN_LINE_OFFSET_LG) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static ComputedLane* sample_computed_lane;
static bool_t init_sample_computed_lane(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_computed_lane != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_computed_lane = (ComputedLane*)mpool_malloc(ws.Pmemory, sizeof(ComputedLane));
		memset(sample_computed_lane, 0, sizeof(ComputedLane));

		if (0) {}
		else if (ASN1_SET_ComputedLane_referenceLaneId(&ws, sample_computed_lane, sample_lane_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ComputedLane_offsetXaxis(&ws, sample_computed_lane, sample_computed_lane_offset_x_axis) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ComputedLane_offsetYaxis(&ws, sample_computed_lane, sample_computed_lane_offset_y_axis) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ComputedLane_rotateXY(&ws, sample_computed_lane, sample_angle) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ComputedLane_scaleXaxis(&ws, sample_computed_lane, sample_scale_b_12) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ComputedLane_scaleYaxis(&ws, sample_computed_lane, sample_scale_b_12) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_ComputedLane_regional(&ws, sample_computed_lane, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}


	return ERR_IS_SUCCESS(errp);
}

static NodeListXY* sample_node_list_xy;
static bool_t init_sample_node_list_xy(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_list_xy != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_list_xy = (NodeListXY*)mpool_malloc(ws.Pmemory, sizeof(NodeListXY));
		memset(sample_node_list_xy, 0, sizeof(NodeListXY));

		if (0) {}
		else if (ASN1_SET_NodeListXY_nodes(&ws, sample_node_list_xy, sample_node_set_xy) < 0)ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_NodeListXY_computed(&ws, sample_node_list_xy, sample_computed_lane) < 0)ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static ConnectingLane* sample_connecting_lane;
static bool_t init_sample_connecting_lane(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_connecting_lane != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_connecting_lane = (ConnectingLane*)mpool_malloc(ws.Pmemory, sizeof(ConnectingLane));
		memset(sample_connecting_lane, 0, sizeof(ConnectingLane));

		if (0) {}
		else if (ASN1_SET_ConnectingLane_lane(&ws, sample_connecting_lane, sample_lane_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ConnectingLane_maneuver(&ws, sample_connecting_lane, sample_allowed_maneuvers, 12) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static Connection* sample_connection;
static bool_t init_sample_connection(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_connection != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_connection = (Connection*)mpool_malloc(ws.Pmemory, sizeof(Connection));
		memset(sample_connection, 0, sizeof(Connection));

		if (0) {}
		else if (ASN1_SET_Connection_connectingLane(&ws, sample_connection, sample_connecting_lane) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_Connection_remoteIntersection(&ws, sample_connection, sample_intersection_reference_id) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_Connection_signalGroup(&ws, sample_connection, SAMPLE_SIGNAL_GROUP_ID) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_Connection_userClass(&ws, sample_connection, SAMPLE_RESTRICTION_CLASS_ID) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_Connection_connectionID(&ws, sample_connection, SAMPLE_LANE_CONNECTION_ID) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static ConnectsToList* sample_connects_to_list;
static bool_t init_sample_connects_to_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_connects_to_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_connects_to_list = (ConnectsToList*)mpool_malloc(ws.Pmemory, sizeof(ConnectsToList));
		memset(sample_connects_to_list, 0, sizeof(ConnectsToList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_connects_to_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_connects_to_list, sample_connection) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static OverlayLaneList* sample_overlay_lane_list;
static bool_t init_sample_overlay_lane_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_overlay_lane_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_overlay_lane_list = (OverlayLaneList*)mpool_malloc(ws.Pmemory, sizeof(OverlayLaneList));
		memset(sample_overlay_lane_list, 0, sizeof(OverlayLaneList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_overlay_lane_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_overlay_lane_list, (ASNVoid*)&sample_lane_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static GenericLane* sample_generic_lane;
static bool_t init_sample_generic_lane(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_generic_lane != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_generic_lane = (GenericLane*)mpool_malloc(ws.Pmemory, sizeof(GenericLane));
		memset(sample_generic_lane, 0, sizeof(GenericLane));

		if (0) {}
		else if (ASN1_SET_GenericLane_laneID(&ws, sample_generic_lane, sample_lane_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GenericLane_name(&ws, sample_generic_lane, sample_descriptive_name, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GenericLane_ingressApproach(&ws, sample_generic_lane, sample_approach_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GenericLane_egressApproach(&ws, sample_generic_lane, sample_approach_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GenericLane_laneAttributes(&ws, sample_generic_lane, sample_lane_attributes) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GenericLane_maneuvers(&ws, sample_generic_lane, sample_allowed_maneuvers, 12) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GenericLane_nodeList(&ws, sample_generic_lane, sample_node_list_xy) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GenericLane_connectsTo(&ws, sample_generic_lane, sample_connects_to_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GenericLane_overlays(&ws, sample_generic_lane, sample_overlay_lane_list) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if(ASN1_SET_GenericLane_regional(&ws, sample_generic_lane, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static LaneList* sample_lane_list;
static bool_t init_sample_lane_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_lane_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_lane_list = (LaneList*)mpool_malloc(ws.Pmemory, sizeof(LaneList));
		memset(sample_lane_list, 0, sizeof(LaneList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_lane_list) < 0)ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_lane_list, sample_generic_lane) < 0)ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static SignalControlZone* sample_signal_control_zone;
static bool_t init_sample_signal_control_zone(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_signal_control_zone != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_signal_control_zone = (SignalControlZone*)mpool_malloc(ws.Pmemory, sizeof(SignalControlZone));
		memset(sample_signal_control_zone, 0, sizeof(SignalControlZone));

		if (0) {}

		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}


	return ERR_IS_SUCCESS(errp);
}

static PreemptPriorityList* sample_preempt_priority_list;
static bool_t init_sample_preempt_priority_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_preempt_priority_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_preempt_priority_list = (PreemptPriorityList*)mpool_malloc(ws.Pmemory, sizeof(PreemptPriorityList));
		memset(sample_preempt_priority_list, 0, sizeof(PreemptPriorityList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_preempt_priority_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_preempt_priority_list, sample_signal_control_zone) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static IntersectionGeometry* sample_intersection_geometry;
static bool_t init_sample_intersection_geometry(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_intersection_geometry != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);

		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);

		sample_intersection_geometry = (IntersectionGeometry*)mpool_malloc(ws.Pmemory, sizeof(IntersectionGeometry));
		memset(sample_intersection_geometry, 0, sizeof(IntersectionGeometry));

		if (0) {}
		else if (ASN1_SET_IntersectionGeometry_name(&ws, sample_intersection_geometry, sample_descriptive_name, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_IntersectionGeometry_id(&ws, sample_intersection_geometry, sample_intersection_reference_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_IntersectionGeometry_revision(&ws, sample_intersection_geometry, sample_msg_count) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_IntersectionGeometry_refPoint(&ws, sample_intersection_geometry, sample_position_3d) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_IntersectionGeometry_laneWidth(&ws, sample_intersection_geometry, sample_lane_width) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_IntersectionGeometry_speedLimits(&ws, sample_intersection_geometry, sample_speed_limit_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_IntersectionGeometry_laneSet(&ws, sample_intersection_geometry, sample_lane_list) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_IntersectionGeometry_preemptPriorityData(&ws, sample_intersection_geometry, sample_preempt_priority_list) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_IntersectionGeometry_regional(&ws, sample_intersection_geometry, ) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_IntersectionGeometry_roadAuthorityID(&ws, sample_intersection_geometry, ) < 0) ERR_SET_OUT(errp,EFAULT);

		else Dz1Error_set(errp, 0);


		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static IntersectionGeometryList* sample_intersection_geometry_list;
static bool_t init_sample_intersection_geometry_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_intersection_geometry_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);

		sample_intersection_geometry_list = (IntersectionGeometryList*)mpool_malloc(ws.Pmemory, sizeof(IntersectionGeometryList));
		memset(sample_intersection_geometry_list, 0, sizeof(IntersectionGeometryList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_intersection_geometry_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_intersection_geometry_list, sample_intersection_geometry) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static RoadSegmentReferenceID* sample_road_segment_reference_id;
static bool_t init_sample_road_segment_reference_id(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_road_segment_reference_id != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_road_segment_reference_id = (RoadSegmentReferenceID*)mpool_malloc(ws.Pmemory, sizeof(RoadSegmentReferenceID));
		memset(sample_road_segment_reference_id, 0, sizeof(RoadSegmentReferenceID));

		if (0) {}
		else if (ASN1_SET_RoadSegmentReferenceID_region(&ws, sample_road_segment_reference_id, sample_road_regulator_id) < 0)ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSegmentReferenceID_id(&ws, sample_road_segment_reference_id, sample_road_segment_id) < 0)ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}



static RoadLaneSetList* sample_road_lane_set_list;
static bool_t init_sample_road_lane_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_road_lane_set_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_road_lane_set_list = (RoadLaneSetList*)mpool_malloc(ws.Pmemory, sizeof(RoadLaneSetList));
		memset(sample_road_lane_set_list, 0, sizeof(RoadLaneSetList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_road_lane_set_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_road_lane_set_list, sample_generic_lane) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static RoadSegment* sample_road_segment;
static bool_t init_sample_road_segment(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_road_segment != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_road_segment = (RoadSegment*)mpool_malloc(ws.Pmemory, sizeof(RoadSegment));
		memset(sample_road_segment, 0, sizeof(RoadSegment));

		if (0) {}
		// ~~~ 
		else if (ASN1_SET_RoadSegment_name(&ws, sample_road_segment, sample_descriptive_name, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSegment_id(&ws, sample_road_segment, sample_road_segment_reference_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSegment_revision(&ws, sample_road_segment, sample_msg_count) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSegment_refPoint(&ws, sample_road_segment, sample_position_3d) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSegment_laneWidth(&ws, sample_road_segment, sample_lane_width) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSegment_speedLimits(&ws, sample_road_segment, sample_speed_limit_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSegment_roadLaneSet(&ws, sample_road_segment, sample_road_lane_set_list) < 0) ERR_SET_OUT(errp,EFAULT);
		// region
		else Dz1Error_set(errp, 0);


		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static RoadSegmentList* sample_road_segment_list;
static bool_t init_sample_road_segment_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_road_segment_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_road_segment_list = (RoadSegmentList*)mpool_malloc(ws.Pmemory, sizeof(RoadSegmentList));
		memset(sample_road_segment_list, 0, sizeof(RoadSegmentList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_road_segment_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_road_segment_list, sample_road_segment) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static DataParameters* sample_data_parameters;
static bool_t init_sample_data_parameters(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_data_parameters != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_data_parameters = (DataParameters*)mpool_malloc(ws.Pmemory, sizeof(DataParameters));
		memset(sample_data_parameters, 0, sizeof(DataParameters));

		if (0) {}
		else if (ASN1_SET_DataParameters_processMethod(&ws, sample_data_parameters, sample_ia5string, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DataParameters_processAgency(&ws, sample_data_parameters, sample_ia5string, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DataParameters_lastCheckedDate(&ws, sample_data_parameters, sample_ia5string, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DataParameters_geoidUsed(&ws, sample_data_parameters, sample_ia5string, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static RestrictionUserType* sample_restriction_user_type;
static bool_t init_sample_restriction_user_type(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_restriction_user_type != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_restriction_user_type = (RestrictionUserType*)mpool_malloc(ws.Pmemory, sizeof(RestrictionUserType));
		memset(sample_restriction_user_type, 0, sizeof(RestrictionUserType));

		if (0) {}
		else if (ASN1_SET_RestrictionUserType_basicType(&ws, sample_restriction_user_type, sample_restriction_applies_to) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_RestrictionUserType_regional(&ws, sample_restriction_user_type, ) < 0) ERR_SET_OUT(errp,EFAULT); // region
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static RestrictionUserTypeList* sample_restriction_user_type_list;
static bool_t init_sample_restriction_user_type_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_restriction_user_type_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_restriction_user_type_list = (RestrictionUserTypeList*)mpool_malloc(ws.Pmemory, sizeof(RestrictionUserTypeList));
		memset(sample_restriction_user_type_list, 0, sizeof(RestrictionUserTypeList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_restriction_user_type_list) < 0)ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_restriction_user_type_list, sample_restriction_user_type) < 0)ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static RestrictionClassAssignment* sample_restriction_class_assignment;
static bool_t init_sample_restriction_class_assignment(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_restriction_class_assignment != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_restriction_class_assignment = (RestrictionClassAssignment*)mpool_malloc(ws.Pmemory, sizeof(RestrictionClassAssignment));
		memset(sample_restriction_class_assignment, 0, sizeof(RestrictionClassAssignment));

		if (0) {}
		else if (ASN1_SET_RestrictionClassAssignment_id(&ws, sample_restriction_class_assignment, sample_restriction_class_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RestrictionClassAssignment_users(&ws, sample_restriction_class_assignment, sample_restriction_user_type_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static RestrictionClassList* sample_restriction_class_list;
static bool_t init_sample_restriction_class_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_restriction_class_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_restriction_class_list = (RestrictionClassList*)mpool_malloc(ws.Pmemory, sizeof(RestrictionClassList));
		memset(sample_restriction_class_list, 0, sizeof(RestrictionClassList));
		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_restriction_class_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_restriction_class_list, sample_restriction_class_assignment) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static EnabledLaneList* sample_enabled_lane_list;
static bool_t init_sample_enabled_lane_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_enabled_lane_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_enabled_lane_list = (EnabledLaneList*)mpool_malloc(ws.Pmemory, sizeof(EnabledLaneList));
		memset(sample_enabled_lane_list, 0, sizeof(EnabledLaneList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_enabled_lane_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_enabled_lane_list, (ASNVoid*)&sample_lane_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static TimeChangeDetails* sample_time_change_details;
static bool_t init_sample_time_change_details(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_time_change_details != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_time_change_details = (TimeChangeDetails*)mpool_malloc(ws.Pmemory, sizeof(TimeChangeDetails));
		memset(sample_time_change_details, 0, sizeof(TimeChangeDetails));
		if (0) {}
		else if (ASN1_SET_TimeChangeDetails_startTime(&ws, sample_time_change_details, sample_time_mark) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TimeChangeDetails_minEndTime(&ws, sample_time_change_details, sample_time_mark) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TimeChangeDetails_maxEndTime(&ws, sample_time_change_details, sample_time_mark) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TimeChangeDetails_likelyTime(&ws, sample_time_change_details, sample_time_mark) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TimeChangeDetails_confidence(&ws, sample_time_change_details, sample_time_interval_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TimeChangeDetails_nextTime(&ws, sample_time_change_details, sample_time_mark) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static AdvisorySpeed* sample_advisory_speed;
static bool_t init_sample_advisory_speed(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_advisory_speed != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_advisory_speed = (AdvisorySpeed*)mpool_malloc(ws.Pmemory, sizeof(AdvisorySpeed));
		memset(sample_advisory_speed, 0, sizeof(AdvisorySpeed));
		if (0) {}
		else if (ASN1_SET_AdvisorySpeed_type(&ws, sample_advisory_speed, sample_advisory_speed_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_AdvisorySpeed_speed(&ws, sample_advisory_speed, sample_speed_advice) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_AdvisorySpeed_confidence(&ws, sample_advisory_speed, sample_speed_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_AdvisorySpeed_distance(&ws, sample_advisory_speed, sample_zone_length) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_AdvisorySpeed_class(&ws, sample_advisory_speed, sample_restriction_class_id) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_AdvisorySpeed_regional(&ws, sample_advisory_speed, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static AdvisorySpeedList* sample_advisory_speed_list;
static bool_t init_sample_advisory_speed_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_advisory_speed_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_advisory_speed_list = (AdvisorySpeedList*)mpool_malloc(ws.Pmemory, sizeof(AdvisorySpeedList));
		memset(sample_advisory_speed_list, 0, sizeof(AdvisorySpeedList));
		if (0) {}
		if (ASN1_Creat_Init_List(&ws, sample_advisory_speed_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_advisory_speed_list, sample_advisory_speed) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static MovementEvent* sample_movement_event;
static bool_t init_sample_msovement_event(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_movement_event != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_movement_event = (MovementEvent*)mpool_malloc(ws.Pmemory, sizeof(MovementEvent));
		memset(sample_movement_event, 0, sizeof(MovementEvent));

		if (0) {}
		else if (ASN1_SET_MovementEvent_eventState(&ws, sample_movement_event, sample_movement_phase_state) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_MovementEvent_timing(&ws, sample_movement_event, sample_time_change_details) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_MovementEvent_speeds(&ws, sample_movement_event, sample_advisory_speed_list) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_MovementEvent_regional(&ws, sample_movement_event, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static MovementEventList* sample_movement_event_list;
static bool_t init_sample_movement_event_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_movement_event_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_movement_event_list = (MovementEventList*)mpool_malloc(ws.Pmemory, sizeof(MovementEventList));
		memset(sample_movement_event_list, 0, sizeof(MovementEventList));
		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_movement_event_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_movement_event_list, sample_movement_event) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static ConnectionManeuverAssist* sample_connection_maneuver_assist;
static bool_t init_sample_connection_maneuver_assist(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_connection_maneuver_assist != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_connection_maneuver_assist = (ConnectionManeuverAssist*)mpool_malloc(ws.Pmemory, sizeof(ConnectionManeuverAssist));
		memset(sample_connection_maneuver_assist, 0, sizeof(ConnectionManeuverAssist));

		if (0) {}
		else if (ASN1_SET_ConnectionManeuverAssist_connectionID(&ws, sample_connection_maneuver_assist, sample_lane_connection_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ConnectionManeuverAssist_queueLength(&ws, sample_connection_maneuver_assist, sample_zone_length) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ConnectionManeuverAssist_availableStorageLength(&ws, sample_connection_maneuver_assist, sample_zone_length) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ConnectionManeuverAssist_waitOnStop(&ws, sample_connection_maneuver_assist, sample_wait_on_stopline) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ConnectionManeuverAssist_pedBicycleDetect(&ws, sample_connection_maneuver_assist, sample_pedestrian_bicycle_detect) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_ConnectionManeuverAssist_regional(&ws, sample_connection_maneuver_assist, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static ManeuverAssistList* sample_maneuver_assist_list;
static bool_t init_sample_maneuver_assist_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_maneuver_assist_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_maneuver_assist_list = (ManeuverAssistList*)mpool_malloc(ws.Pmemory, sizeof(ManeuverAssistList));
		memset(sample_maneuver_assist_list, 0, sizeof(ManeuverAssistList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_maneuver_assist_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_maneuver_assist_list, sample_connection_maneuver_assist) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static MovementState* sample_movement_state;
static bool_t init_sample_movement_state(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_movement_state != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_movement_state = (MovementState*)mpool_malloc(ws.Pmemory, sizeof(MovementState));
		memset(sample_movement_state, 0, sizeof(MovementState));

		if (0) {}
		else if (ASN1_SET_MovementState_movementName(&ws, sample_movement_state, sample_descriptive_name, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_MovementState_signalGroup(&ws, sample_movement_state, sample_signal_group_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_MovementState_state_time_speed(&ws, sample_movement_state, sample_movement_event_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_MovementState_maneuverAssistList(&ws, sample_movement_state, sample_maneuver_assist_list) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_MovementState_regional(&ws, sample_movement_state, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static MovementList* sample_movement_list;
static bool_t init_sample_movement_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_movement_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_movement_list = (MovementList*)mpool_malloc(ws.Pmemory, sizeof(MovementList));
		memset(sample_movement_list, 0, sizeof(MovementList));
		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_movement_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_movement_list, sample_movement_state) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static IntersectionState* sample_intersection_state;
static bool_t init_sample_intersection_state(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_intersection_state != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_intersection_state = (IntersectionState*)mpool_malloc(ws.Pmemory, sizeof(IntersectionState));
		memset(sample_intersection_state, 0, sizeof(IntersectionState));

		if (0) {}
		else if (ASN1_SET_IntersectionState_name(&ws, sample_intersection_state, sample_descriptive_name, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_IntersectionState_id(&ws, sample_intersection_state, sample_intersection_reference_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_IntersectionState_revision(&ws, sample_intersection_state, sample_msg_count) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_IntersectionState_status(&ws, sample_intersection_state, sample_intersection_status_object, 16) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_IntersectionState_moy(&ws, sample_intersection_state, sample_minute_of_the_year) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_IntersectionState_timeStamp(&ws, sample_intersection_state, sample_d_second) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_IntersectionState_enabledLanes(&ws, sample_intersection_state, sample_enabled_lane_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_IntersectionState_states(&ws, sample_intersection_state, sample_movement_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_IntersectionState_maneuverAssistList(&ws, sample_intersection_state, sample_maneuver_assist_list) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_IntersectionState_regional(&ws, sample_intersection_state, ) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_IntersectionState_roadAuthorityID(&ws, sample_intersection_state, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static IntersectionStateList* sample_intersection_state_list;
static bool_t init_sample_intersection_state_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_intersection_state_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_intersection_state_list = (IntersectionStateList*)mpool_malloc(ws.Pmemory, sizeof(IntersectionStateList));
		memset(sample_intersection_state_list, 0, sizeof(IntersectionStateList));
		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_intersection_state_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_intersection_state_list, sample_intersection_state) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static VehicleSize* sample_vehicle_size;
static bool_t init_sample_vehicle_size(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_vehicle_size != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_vehicle_size = (VehicleSize*)mpool_malloc(ws.Pmemory, sizeof(VehicleSize));
		memset(sample_vehicle_size, 0, sizeof(VehicleSize));
		if (0) {}
		else if (ASN1_SET_VehicleSize_width(&ws, sample_vehicle_size, sample_vehicle_width) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleSize_length(&ws, sample_vehicle_size, sample_vehicle_length) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static BSMcoreData* sample_bsm_core_data;
static bool_t init_sample_bsm_core_data(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_bsm_core_data != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_bsm_core_data = (BSMcoreData*)mpool_malloc(ws.Pmemory, sizeof(BSMcoreData));
		memset(sample_bsm_core_data, 0, sizeof(BSMcoreData));

		if (0) {}
		else if (ASN1_SET_BSMcoreData_msgCnt(&ws, sample_bsm_core_data, sample_msg_count) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BSMcoreData_id(&ws, sample_bsm_core_data, sample_temporary_id, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BSMcoreData_secMark(&ws, sample_bsm_core_data, sample_d_second) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BSMcoreData_lat(&ws, sample_bsm_core_data, sample_latitude) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BSMcoreData_lon(&ws, sample_bsm_core_data, sample_longitude) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BSMcoreData_elev(&ws, sample_bsm_core_data, sample_elevation) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BSMcoreData_accuracy(&ws, sample_bsm_core_data, sample_positional_accuracy) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BSMcoreData_transmission(&ws, sample_bsm_core_data, sample_transmission_state) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BSMcoreData_speed(&ws, sample_bsm_core_data, sample_speed) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BSMcoreData_heading(&ws, sample_bsm_core_data, sample_heading) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BSMcoreData_angle(&ws, sample_bsm_core_data, sample_steering_wheel_angle) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BSMcoreData_accelSet(&ws, sample_bsm_core_data, sample_acceleration_set_4_way) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BSMcoreData_brakes(&ws, sample_bsm_core_data, sample_brake_system_status) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_BSMcoreData_size(&ws, sample_bsm_core_data, sample_vehicle_size) < 0) ERR_SET_OUT(errp,EFAULT);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static RoadSideAlert_description* sample_road_side_alert_description;
static bool_t init_sample_road_side_alert_description(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_road_side_alert_description != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_road_side_alert_description = (RoadSideAlert_description*)mpool_malloc(ws.Pmemory, sizeof(RoadSideAlert_description));
		memset(sample_road_side_alert_description, 0, sizeof(RoadSideAlert_description));
		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_road_side_alert_description) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_road_side_alert_description, (ASNVoid*)&sample_itis_codes) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static RoadSignID* sample_road_sign_id;
static bool_t init_sample_road_sign_id(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_road_sign_id != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_road_sign_id = (RoadSignID*)mpool_malloc(ws.Pmemory, sizeof(RoadSignID));
		memset(sample_road_sign_id, 0, sizeof(RoadSignID));
		if (0) {}
		else if (ASN1_SET_RoadSignID_position(&ws, sample_road_sign_id, sample_position_3d) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSignID_viewAngle(&ws, sample_road_sign_id, sample_heading_slice, 16) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSignID_mutcdCode(&ws, sample_road_sign_id, sample_mutcd_code) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSignID_crc(&ws, sample_road_sign_id, sample_msg_crc, 2) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static TravelerDataFrame_msgId* sample_traveler_data_frame_msg_id;
static bool_t init_sample_traveler_data_frame_msg_id(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_traveler_data_frame_msg_id != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_traveler_data_frame_msg_id = (TravelerDataFrame_msgId*)mpool_malloc(ws.Pmemory, sizeof(TravelerDataFrame_msgId));
		memset(sample_traveler_data_frame_msg_id, 0, sizeof(TravelerDataFrame_msgId));
		if (0) {}
		else if (ASN1_SET_TravelerDataFrame_msgId_furtherInfoID(&ws, sample_traveler_data_frame_msg_id, sample_further_info_id, 2) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if(ASN1_SET_TravelerDataFrame_msgId_roadSignID(&ws, sample_traveler_data_frame_msg_id, sample_road_sign_id) <0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static Node_LL_24B* sample_node_ll_24_b;
static Node_LL_28B* sample_node_ll_28_b;
static Node_LL_32B* sample_node_ll_32_b;
static Node_LL_36B* sample_node_ll_36_b;
static Node_LL_44B* sample_node_ll_44_b;
static Node_LL_48B* sample_node_ll_48_b;


static bool_t init_sample_node_ll_24_b(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_ll_24_b != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_ll_24_b = (Node_LL_24B*)mpool_malloc(ws.Pmemory, sizeof(Node_LL_24B));
		memset(sample_node_ll_24_b, 0, sizeof(Node_LL_24B));

		if (0) {}
		else if (ASN1_SET_Node_LL_24B_lon(&ws, sample_node_ll_24_b, sample_offset_ll_b12) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Node_LL_24B_lat(&ws, sample_node_ll_24_b, sample_offset_ll_b12) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static bool_t init_sample_node_ll_28_b(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_ll_28_b != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_ll_28_b = (Node_LL_28B*)mpool_malloc(ws.Pmemory, sizeof(Node_LL_28B));
		memset(sample_node_ll_28_b, 0, sizeof(Node_LL_28B));

		if (0) {}
		else if (ASN1_SET_Node_LL_28B_lon(&ws, sample_node_ll_28_b, sample_offset_ll_b14) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Node_LL_28B_lat(&ws, sample_node_ll_28_b, sample_offset_ll_b14) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_node_ll_32_b(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_ll_32_b != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_ll_32_b = (Node_LL_32B*)mpool_malloc(ws.Pmemory, sizeof(Node_LL_32B));
		memset(sample_node_ll_32_b, 0, sizeof(Node_LL_32B));

		if (0) {}
		else if (ASN1_SET_Node_LL_32B_lon(&ws, sample_node_ll_32_b, sample_offset_ll_b16) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Node_LL_32B_lat(&ws, sample_node_ll_32_b, sample_offset_ll_b16) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static bool_t init_sample_node_ll_36_b(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_ll_36_b != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_ll_36_b = (Node_LL_36B*)mpool_malloc(ws.Pmemory, sizeof(Node_LL_36B));
		memset(sample_node_ll_36_b, 0, sizeof(Node_LL_36B));

		if (0) {}
		else if (ASN1_SET_Node_LL_36B_lon(&ws, sample_node_ll_36_b, sample_offset_ll_b18) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Node_LL_36B_lat(&ws, sample_node_ll_36_b, sample_offset_ll_b18) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_node_ll_44_b(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_ll_44_b != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_ll_44_b = (Node_LL_44B*)mpool_malloc(ws.Pmemory, sizeof(Node_LL_44B));
		memset(sample_node_ll_44_b, 0, sizeof(Node_LL_44B));

		if (0) {}
		else if (ASN1_SET_Node_LL_44B_lon(&ws, sample_node_ll_44_b, sample_offset_ll_b22) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Node_LL_44B_lat(&ws, sample_node_ll_44_b, sample_offset_ll_b22) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_node_ll_48_b(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_ll_48_b != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_ll_48_b = (Node_LL_48B*)mpool_malloc(ws.Pmemory, sizeof(Node_LL_48B));
		memset(sample_node_ll_48_b, 0, sizeof(Node_LL_48B));

		if (0) {}
		else if (ASN1_SET_Node_LL_48B_lon(&ws, sample_node_ll_48_b, sample_offset_ll_b24) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Node_LL_48B_lat(&ws, sample_node_ll_48_b, sample_offset_ll_b24) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static NodeOffsetPointLL* sample_node_offset_point_ll;
static bool_t init_sample_node_offset_point_ll(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_offset_point_ll != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_offset_point_ll = (NodeOffsetPointLL*)mpool_malloc(ws.Pmemory, sizeof(NodeOffsetPointLL));
		memset(sample_node_offset_point_ll, 0, sizeof(NodeOffsetPointLL));

		if (0) {}
		else if (ASN1_SET_NodeOffsetPointLL_node_LL1(&ws, sample_node_offset_point_ll, sample_node_ll_24_b) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_NodeOffsetPointLL_node_LL2(&ws, sample_node_offset_point_ll, sample_node_ll_28_b) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_NodeOffsetPointLL_node_LL3(&ws, sample_node_offset_point_ll, sample_node_ll_32_b) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_NodeOffsetPointLL_node_LL4(&ws, sample_node_offset_point_ll, sample_node_ll_36_b) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_NodeOffsetPointLL_node_LL5(&ws, sample_node_offset_point_ll, sample_node_ll_44_b) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_NodeOffsetPointLL_node_LL6(&ws, sample_node_offset_point_ll, sample_node_ll_48_b) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_NodeOffsetPointLL_node_LatLon(&ws, sample_node_offset_point_ll, sample_node_llmd_64_b) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_NodeOffsetPointLL_regional(&ws, sample_node_offset_point_ll, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static NodeAttributeLLList* sample_node_attribute_ll_list;
static bool_t init_sample_node_attribute_ll_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_node_attribute_ll_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_attribute_ll_list = (NodeAttributeLLList*)mpool_malloc(ws.Pmemory, sizeof(NodeAttributeLLList));
		memset(sample_node_attribute_ll_list, 0, sizeof(NodeAttributeLLList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_node_attribute_ll_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_node_attribute_ll_list, (ASNVoid*)&sample_node_attribute_ll) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static SegmentAttributeLLList* sample_segment_attribute_ll_list;
static bool_t init_sample_segment_attribute_ll_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_segment_attribute_ll_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_segment_attribute_ll_list = (SegmentAttributeLLList*)mpool_malloc(ws.Pmemory, sizeof(SegmentAttributeLLList));
		memset(sample_segment_attribute_ll_list, 0, sizeof(SegmentAttributeLLList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_segment_attribute_ll_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_segment_attribute_ll_list, (ASNVoid*)&sample_segment_attribute_ll));
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static NodeAttributeSetLL* sample_node_attribute_set_ll;
static bool_t init_sample_node_attribute_set_ll(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_node_attribute_set_ll != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_attribute_set_ll = (NodeAttributeSetLL*)mpool_malloc(ws.Pmemory, sizeof(NodeAttributeSetLL));
		memset(sample_node_attribute_set_ll, 0, sizeof(NodeAttributeSetLL));

		if (0) {}
		else if (ASN1_SET_NodeAttributeSetLL_localNode(&ws, sample_node_attribute_set_ll, sample_node_attribute_ll_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_NodeAttributeSetLL_disabled(&ws, sample_node_attribute_set_ll, sample_segment_attribute_ll_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_NodeAttributeSetLL_enabled(&ws, sample_node_attribute_set_ll, sample_segment_attribute_ll_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_NodeAttributeSetLL_data(&ws, sample_node_attribute_set_ll, sample_lane_data_attribute_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_NodeAttributeSetLL_dWidth(&ws, sample_node_attribute_set_ll, sample_offset_b10) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_NodeAttributeSetLL_dElevation(&ws, sample_node_attribute_set_ll, sample_offset_b10) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_NodeAttributeSetLL_regional(&ws, sample_node_attribute_set_ll, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static NodeLL* sample_node_ll_1;
static NodeLL* sample_node_ll_2;
static bool_t init_sample_node_ll_1(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_ll_1 != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_ll_1 = (NodeLL*)mpool_malloc(ws.Pmemory, sizeof(NodeLL));
		memset(sample_node_ll_1, 0, sizeof(NodeLL));

		if (0) {}
		else if (ASN1_SET_NodeLL_delta(&ws, sample_node_ll_1, sample_node_offset_point_ll) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_NodeLL_attributes(&ws, sample_node_ll_1, sample_node_attribute_set_ll) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_node_ll_2(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_ll_2 != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_ll_2 = (NodeLL*)mpool_malloc(ws.Pmemory, sizeof(NodeLL));
		memset(sample_node_ll_2, 0, sizeof(NodeLL));

		if (0) {}
		else if (ASN1_SET_NodeLL_delta(&ws, sample_node_ll_2, sample_node_offset_point_ll) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_NodeLL_attributes(&ws, sample_node_ll_2, sample_node_attribute_set_ll) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}



static NodeSetLL* sample_node_set_ll;
static bool_t init_sample_node_set_ll(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_set_ll != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_set_ll = (NodeSetLL*)mpool_malloc(ws.Pmemory, sizeof(NodeSetLL));
		memset(sample_node_set_ll, 0, sizeof(NodeSetLL));
		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_node_set_ll) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_node_set_ll, sample_node_ll_1) < 0);
		else if (ASN1_Insert_Node(&ws, sample_node_set_ll, sample_node_ll_2) < 0);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static NodeListLL* sample_node_list_ll;
static bool_t init_sample_node_list_ll(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_node_list_ll != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_node_list_ll = (NodeListLL*)mpool_malloc(ws.Pmemory, sizeof(NodeListLL));
		memset(sample_node_list_ll, 0, sizeof(NodeListLL));
		if (0) {}
		else if (ASN1_SET_NodeListLL_nodes(&ws, sample_node_list_ll, sample_node_set_ll) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static OffsetSystem_offset* sample_offset_system_offset;
static bool_t init_sample_offset_system_offset(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_offset_system_offset != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_offset_system_offset = (OffsetSystem_offset*)mpool_malloc(ws.Pmemory, sizeof(OffsetSystem_offset));
		memset(sample_offset_system_offset, 0, sizeof(OffsetSystem_offset));
		if (0) {}
		else if (ASN1_SET_OffsetSystem_offset_xy(&ws, sample_offset_system_offset, sample_node_list_xy) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_OffsetSystem_offset_ll(&ws, sample_offset_system_offset, sample_node_list_ll) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static OffsetSystem* sample_offset_system;
static bool_t init_sample_offset_system(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_offset_system != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_offset_system = (OffsetSystem*)mpool_malloc(ws.Pmemory, sizeof(OffsetSystem));
		memset(sample_offset_system, 0, sizeof(OffsetSystem));
		if (0) {}
		else if (ASN1_SET_OffsetSystem_scale(&ws, sample_offset_system, sample_zoom) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_OffsetSystem_offset(&ws, sample_offset_system, sample_offset_system_offset) < 0) ERR_SET_OUT(errp,EFAULT);

		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static Circle* sample_circle;
static bool_t init_sample_circle(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_circle != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_circle = (Circle*)mpool_malloc(ws.Pmemory, sizeof(Circle));
		memset(sample_circle, 0, sizeof(Circle));
		if (0) {}
		else if (ASN1_SET_Circle_center(&ws, sample_circle, sample_position_3d) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Circle_radius(&ws, sample_circle, sample_radius_b12) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Circle_units(&ws, sample_circle, sample_distance_units) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static GeometricProjection* sample_geometric_projection;
static bool_t init_sample_geometric_projection(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_geometric_projection != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_geometric_projection = (GeometricProjection*)mpool_malloc(ws.Pmemory, sizeof(GeometricProjection));
		memset(sample_geometric_projection, 0, sizeof(GeometricProjection));

		if (0) {}
		else if (ASN1_SET_GeometricProjection_direction(&ws, sample_geometric_projection, sample_heading_slice, 16) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GeometricProjection_extent(&ws, sample_geometric_projection, sample_extent) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GeometricProjection_laneWidth(&ws, sample_geometric_projection, sample_lane_width) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GeometricProjection_circle(&ws, sample_geometric_projection, sample_circle) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_GeometricProjection_regional(&ws, sample_geometric_projection, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);



		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}



static ShapePointSet* sample_shape_point_set;
static bool_t init_sample_shape_point_set(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_shape_point_set != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_shape_point_set = (ShapePointSet*)mpool_malloc(ws.Pmemory, sizeof(ShapePointSet));
		memset(sample_shape_point_set, 0, sizeof(ShapePointSet));
		if (0) {}
		else if (ASN1_SET_ShapePointSet_anchor(&ws, sample_shape_point_set, sample_position_3d) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ShapePointSet_laneWidth(&ws, sample_shape_point_set, sample_lane_width) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ShapePointSet_directionality(&ws, sample_shape_point_set, sample_direction_of_use) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ShapePointSet_nodeList(&ws, sample_shape_point_set, sample_node_list_xy) < 0) ERR_SET_OUT(errp,EFAULT);

		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}
static RegionOffsets* sample_region_offsets;
static bool_t init_sample_region_offsets(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_region_offsets != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_region_offsets = (RegionOffsets*)mpool_malloc(ws.Pmemory, sizeof(RegionOffsets));
		memset(sample_region_offsets, 0, sizeof(RegionOffsets));
		if (0) {}
		else if (ASN1_SET_RegionOffsets_xOffset(&ws, sample_region_offsets, sample_offset_ll_b16) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RegionOffsets_yOffset(&ws, sample_region_offsets, sample_offset_ll_b16) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RegionOffsets_zOffset(&ws, sample_region_offsets, sample_offset_ll_b16) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}


static RegionList* sample_region_list;
static bool_t init_sample_region_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_region_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_region_list = (RegionList*)mpool_malloc(ws.Pmemory, sizeof(RegionList));
		memset(sample_region_list, 0, sizeof(RegionList));
		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_region_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_region_list, sample_region_offsets) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static RegionPointSet* sample_region_point_set;
static bool_t init_sample_region_point_set(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_region_point_set != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_region_point_set = (RegionPointSet*)mpool_malloc(ws.Pmemory, sizeof(RegionPointSet));
		memset(sample_region_point_set, 0, sizeof(RegionPointSet));
		if (0) {}
		else if (ASN1_SET_RegionPointSet_anchor(&ws, sample_region_point_set, sample_position_3d) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RegionPointSet_scale(&ws, sample_region_point_set, sample_zoom) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RegionPointSet_nodeList(&ws, sample_region_point_set, sample_region_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static ValidRegion_area* sample_valid_region_area;
static bool_t init_sample_valid_region_area(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_valid_region_area != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_valid_region_area = (ValidRegion_area*)mpool_malloc(ws.Pmemory, sizeof(ValidRegion_area));
		memset(sample_valid_region_area, 0, sizeof(ValidRegion_area));
		if (0) {}
		else if (ASN1_SET_ValidRegion_area_shapePointSet(&ws, sample_valid_region_area, sample_shape_point_set) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_ValidRegion_area_circle(&ws, sample_valid_region_area,sample_circle) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_ValidRegion_area_regionPointSet(&ws, sample_valid_region_area,) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static ValidRegion* sample_valid_region;
static bool_t init_sample_valid_region(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_valid_region != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_valid_region = (ValidRegion*)mpool_malloc(ws.Pmemory, sizeof(ValidRegion));
		memset(sample_valid_region, 0, sizeof(ValidRegion));
		if (0) {}
		else if (ASN1_SET_ValidRegion_direction(&ws, sample_valid_region, sample_heading_slice, 16) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ValidRegion_extent(&ws, sample_valid_region, sample_extent) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ValidRegion_area(&ws, sample_valid_region, sample_valid_region_area) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static GeographicalPath_description* sample_geographical_path_description;
static bool_t init_sample_geographical_path_description(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_geographical_path_description != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_geographical_path_description = (GeographicalPath_description*)mpool_malloc(ws.Pmemory, sizeof(GeographicalPath_description));
		memset(sample_geographical_path_description, 0, sizeof(GeographicalPath_description));
		if (0) {}
		else if (ASN1_SET_GeographicalPath_description_path(&ws, sample_geographical_path_description, sample_offset_system) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_GeographicalPath_description_geometry(&ws, sample_geographical_path_description, sample_geometric_projection) < 0) _OUT(errp);
		//else if (ASN1_SET_GeographicalPath_description_oldRegion(&ws, sample_geographical_path_description, sample_valid_region) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static GeographicalPath* sample_geographical_path;
static bool_t init_sample_geographical_path(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_geographical_path != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_geographical_path = (GeographicalPath*)mpool_malloc(ws.Pmemory, sizeof(GeographicalPath));
		memset(sample_geographical_path, 0, sizeof(GeographicalPath));
		if (0) {}
		else if (ASN1_SET_GeographicalPath_name(&ws, sample_geographical_path, sample_descriptive_name, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GeographicalPath_id(&ws, sample_geographical_path, sample_road_segment_reference_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GeographicalPath_anchor(&ws, sample_geographical_path, sample_position_3d) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GeographicalPath_laneWidth(&ws, sample_geographical_path, sample_lane_width) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GeographicalPath_directionality(&ws, sample_geographical_path, sample_direction_of_use) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GeographicalPath_closedPath(&ws, sample_geographical_path, TRUE) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GeographicalPath_direction(&ws, sample_geographical_path, sample_heading_slice, 16) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_GeographicalPath_description(&ws, sample_geographical_path, sample_geographical_path_description) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_GeographicalPath_regional(&ws, sample_geographical_path, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static TravelerDataFrame_regions* sample_traveler_data_frame_regions;
static init_sample_traveler_data_frame_regions(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_traveler_data_frame_regions != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_traveler_data_frame_regions = (TravelerDataFrame_regions*)mpool_malloc(ws.Pmemory, sizeof(TravelerDataFrame_regions));
		memset(sample_traveler_data_frame_regions, 0, sizeof(TravelerDataFrame_regions));
		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_traveler_data_frame_regions) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_traveler_data_frame_regions, sample_geographical_path) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static ITIScodesAndText_element_item* sample_itis_codes_and_text_element_item;
static bool_t init_sample_itis_codes_and_text_element_item(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_itis_codes_and_text_element_item != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_itis_codes_and_text_element_item = (ITIScodesAndText_element_item*)mpool_malloc(ws.Pmemory, sizeof(ITIScodesAndText_element_item));
		memset(sample_itis_codes_and_text_element_item, 0, sizeof(ITIScodesAndText_element_item));
		if (0) {}
		else if (ASN1_SET_ITIScodesAndText_element_item_itis(&ws, sample_itis_codes_and_text_element_item, sample_itis_codes) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_ITIScodesAndText_element_item_text(&ws, sample_itis_codes_and_text_element_item, sample_itis_text, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static ITIScodesAndText_element* sample_itis_codes_and_text_element;
static bool_t init_sample_itis_codes_and_text_element(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_itis_codes_and_text_element != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_itis_codes_and_text_element = (ITIScodesAndText_element*)mpool_malloc(ws.Pmemory, sizeof(ITIScodesAndText_element));
		memset(sample_itis_codes_and_text_element, 0, sizeof(ITIScodesAndText_element));
		if (0) {}
		else if (ASN1_SET_ITIScodesAndText_element_item(&ws, sample_itis_codes_and_text_element, sample_itis_codes_and_text_element_item) < 0)ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static ITIScodesAndText* sample_itis_codes_and_text;
static bool_t init_sample_itis_codes_and_text(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_itis_codes_and_text != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_itis_codes_and_text = (ITIScodesAndText*)mpool_malloc(ws.Pmemory, sizeof(ITIScodesAndText));
		memset(sample_itis_codes_and_text, 0, sizeof(ITIScodesAndText));
		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_itis_codes_and_text) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_itis_codes_and_text, sample_itis_codes_and_text_element) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}


static WorkZone_element_item* sample_work_zone_element_item;
static bool_t init_sample_work_zone_element_item(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_work_zone_element_item != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_work_zone_element_item = (WorkZone_element_item*)mpool_malloc(ws.Pmemory, sizeof(WorkZone_element_item));
		memset(sample_work_zone_element_item, 0, sizeof(WorkZone_element_item));
		if (0) {}
		else if (ASN1_SET_WorkZone_element_item_itis(&ws, sample_work_zone_element_item, sample_itis_codes) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_WorkZone_element_item_text(&ws, sample_work_zone_element_item, sample_itis_text, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static WorkZone_element* sample_work_zone_element;
static bool_t init_sample_work_zone_element(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_work_zone_element != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_work_zone_element = (WorkZone_element*)mpool_malloc(ws.Pmemory, sizeof(WorkZone_element));
		memset(sample_work_zone_element, 0, sizeof(WorkZone_element));
		if (0) {}
		else if (ASN1_SET_WorkZone_element_item(&ws, sample_work_zone_element, sample_work_zone_element_item) < 0)ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static WorkZone* sample_work_zone;
static bool_t init_sample_work_zone(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_work_zone != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_work_zone = (WorkZone*)mpool_malloc(ws.Pmemory, sizeof(WorkZone));
		memset(sample_work_zone, 0, sizeof(WorkZone));
		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_work_zone) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_work_zone, sample_work_zone_element) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static GenericSignage_element_item* sample_generic_signage_element_item;
static bool_t init_sample_generic_signage_element_item(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_generic_signage_element_item != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_generic_signage_element_item = (GenericSignage_element_item*)mpool_malloc(ws.Pmemory, sizeof(GenericSignage_element_item));
		memset(sample_generic_signage_element_item, 0, sizeof(GenericSignage_element_item));
		if (0) {}
		else if (ASN1_SET_GenericSignage_element_item_itis(&ws, sample_generic_signage_element_item, sample_itis_codes) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_GenericSignage_element_item_text(&ws, sample_generic_signage_element_item, sample_itis_text, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static GenericSignage_element* sample_generic_signage_element;
static bool_t init_sample_generic_signage_element(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_generic_signage_element != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_generic_signage_element = (GenericSignage_element*)mpool_malloc(ws.Pmemory, sizeof(GenericSignage_element));
		memset(sample_generic_signage_element, 0, sizeof(GenericSignage_element));
		if (0) {}
		else if (ASN1_SET_GenericSignage_element_item(&ws, sample_generic_signage_element, sample_generic_signage_element_item) < 0)ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static GenericSignage* sample_generic_signage;
static bool_t init_sample_generic_signage(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_generic_signage != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_generic_signage = (GenericSignage*)mpool_malloc(ws.Pmemory, sizeof(GenericSignage));
		memset(sample_generic_signage, 0, sizeof(GenericSignage));
		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_generic_signage) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_generic_signage, sample_generic_signage_element) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static SpeedLimit_element_item* sample_speed_limit_element_item;
static bool_t init_sample_speed_limit_element_item(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_speed_limit_element_item != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_speed_limit_element_item = (SpeedLimit_element_item*)mpool_malloc(ws.Pmemory, sizeof(SpeedLimit_element_item));
		memset(sample_speed_limit_element_item, 0, sizeof(SpeedLimit_element_item));
		if (0) {}
		else if (ASN1_SET_SpeedLimit_element_item_itis(&ws, sample_speed_limit_element_item, sample_itis_codes) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_SpeedLimit_element_item_text(&ws, sample_speed_limit_element_item, sample_itis_text, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static SpeedLimit_element* sample_speed_limit_element;
static bool_t init_sample_speed_limit_element(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_speed_limit_element != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_speed_limit_element = (SpeedLimit_element*)mpool_malloc(ws.Pmemory, sizeof(SpeedLimit_element));
		memset(sample_speed_limit_element, 0, sizeof(SpeedLimit_element));
		if (0) {}
		else if (ASN1_SET_SpeedLimit_element_item(&ws, sample_speed_limit_element, sample_speed_limit_element_item) < 0)ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static SpeedLimit* sample_speed_limit;
static bool_t init_sample_speed_limit(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_speed_limit != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_speed_limit = (SpeedLimit*)mpool_malloc(ws.Pmemory, sizeof(SpeedLimit));
		memset(sample_speed_limit, 0, sizeof(SpeedLimit));
		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_speed_limit) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_speed_limit, sample_speed_limit_element) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static ExitService_element_item* sample_exit_service_element_item;
static bool_t init_sample_exit_service_element_item(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_exit_service_element_item != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_exit_service_element_item = (ExitService_element_item*)mpool_malloc(ws.Pmemory, sizeof(ExitService_element_item));
		memset(sample_exit_service_element_item, 0, sizeof(ExitService_element_item));
		if (0) {}
		else if (ASN1_SET_ExitService_element_item_itis(&ws, sample_exit_service_element_item, sample_itis_codes) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_ExitService_element_item_text(&ws, sample_exit_service_element_item, sample_itis_text, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static ExitService_element* sample_exit_service_element;
static bool_t init_sample_exit_service_element(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_exit_service_element != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_exit_service_element = (ExitService_element*)mpool_malloc(ws.Pmemory, sizeof(ExitService_element));
		memset(sample_exit_service_element, 0, sizeof(ExitService_element));
		if (0) {}
		else if (ASN1_SET_ExitService_element_item(&ws, sample_exit_service_element, sample_exit_service_element_item) < 0)ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static ExitService* sample_exit_service;
static bool_t init_sample_exit_service(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_exit_service != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_exit_service = (ExitService*)mpool_malloc(ws.Pmemory, sizeof(ExitService));
		memset(sample_exit_service, 0, sizeof(ExitService));
		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_exit_service) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_exit_service, sample_exit_service_element) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}


static TravelerDataFrame_content* sample_traveler_data_frame_content;
static bool_t init_sample_traveler_data_frame_content(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_traveler_data_frame_content != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_traveler_data_frame_content = (TravelerDataFrame_content*)mpool_malloc(ws.Pmemory, sizeof(TravelerDataFrame_content));
		memset(sample_traveler_data_frame_content, 0, sizeof(TravelerDataFrame_content));
		if (0) {}
		else if (ASN1_SET_TravelerDataFrame_content_advisory(&ws, sample_traveler_data_frame_content, sample_itis_codes_and_text) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_TravelerDataFrame_content_workZone(&ws, sample_traveler_data_frame_content, sample_work_zone) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_TravelerDataFrame_content_genericSign(&ws, sample_traveler_data_frame_content, sample_generic_signage) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_TravelerDataFrame_content_speedLimit(&ws, sample_traveler_data_frame_content, sample_speed_limit) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_TravelerDataFrame_content_exitService(&ws, sample_traveler_data_frame_content, sample_exit_service) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (AASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static TravelerDataFrame* sample_traveler_data_frame;
static bool_t init_sample_traveler_data_frame(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_traveler_data_frame != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_traveler_data_frame = (TravelerDataFrame*)mpool_malloc(ws.Pmemory, sizeof(TravelerDataFrame));
		memset(sample_traveler_data_frame, 0, sizeof(TravelerDataFrame));
		if (0) {}
		else if (ASN1_SET_TravelerDataFrame_notUsed(&ws, sample_traveler_data_frame, sample_ssp_index) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TravelerDataFrame_frameType(&ws, sample_traveler_data_frame, sample_traveler_info_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TravelerDataFrame_msgId(&ws, sample_traveler_data_frame, sample_traveler_data_frame_msg_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TravelerDataFrame_startYear(&ws, sample_traveler_data_frame, sample_d_year) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TravelerDataFrame_startTime(&ws, sample_traveler_data_frame, sample_minute_of_the_year) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TravelerDataFrame_durationTime(&ws, sample_traveler_data_frame, sample_minutes_duration) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TravelerDataFrame_priority(&ws, sample_traveler_data_frame, sample_sign_priority) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TravelerDataFrame_notUsed1(&ws, sample_traveler_data_frame, sample_ssp_index) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TravelerDataFrame_regions(&ws, sample_traveler_data_frame, sample_traveler_data_frame_regions) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TravelerDataFrame_notUsed2(&ws, sample_traveler_data_frame, sample_ssp_index) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TravelerDataFrame_notUsed3(&ws, sample_traveler_data_frame, sample_ssp_index) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TravelerDataFrame_content(&ws, sample_traveler_data_frame, sample_traveler_data_frame_content) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TravelerDataFrame_url(&ws, sample_traveler_data_frame, sample_url_short, 3) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static TravelerDataFrameList* sample_traveler_data_frame_list;
static bool_t init_sample_traveler_data_frame_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_traveler_data_frame_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_traveler_data_frame_list = (TravelerDataFrameList*)mpool_malloc(ws.Pmemory, sizeof(TravelerDataFrameList));
		memset(sample_traveler_data_frame_list, 0, sizeof(TravelerDataFrameList));
		if (ASN1_Creat_Init_List(&ws, sample_traveler_data_frame_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_traveler_data_frame_list, sample_traveler_data_frame) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


// DF

// sdsm

static PositionOffsetXYZ* sample_position_offset_xyz;
static bool_t init_sample_position_offset_xyz(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_position_offset_xyz != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_position_offset_xyz = (PositionOffsetXYZ*)mpool_malloc(ws.Pmemory, sizeof(PositionOffsetXYZ));
		memset(sample_position_offset_xyz, 0, sizeof(PositionOffsetXYZ));

		if (0) {}
		else if (ASN1_SET_PositionOffsetXYZ_offsetX(&ws, sample_position_offset_xyz, sample_object_distance) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PositionOffsetXYZ_offsetY(&ws, sample_position_offset_xyz, sample_object_distance) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PositionOffsetXYZ_offsetZ(&ws, sample_position_offset_xyz, sample_object_distance) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static DetectedObjectCommonData* sample_detected_object_common_data;
static bool_t init_sample_detected_object_common_data(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_detected_object_common_data != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_detected_object_common_data = (DetectedObjectCommonData*)mpool_malloc(ws.Pmemory, sizeof(DetectedObjectCommonData));
		memset(sample_detected_object_common_data, 0, sizeof(DetectedObjectCommonData));

		if (0) {}
		else if (ASN1_SET_DetectedObjectCommonData_objType(&ws, sample_detected_object_common_data, sample_object_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_objTypeCfd(&ws, sample_detected_object_common_data, sample_classification_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_objectID(&ws, sample_detected_object_common_data, sample_object_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_measurementTime(&ws, sample_detected_object_common_data, sample_measurement_time_offset) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_timeConfidence(&ws, sample_detected_object_common_data, sample_time_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_pos(&ws, sample_detected_object_common_data, sample_position_offset_xyz) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_posConfidence(&ws, sample_detected_object_common_data, sample_position_confidence_set) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_speed(&ws, sample_detected_object_common_data, sample_speed) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_speedConfidence(&ws, sample_detected_object_common_data, sample_speed_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_speedZ(&ws, sample_detected_object_common_data, sample_speed) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_speedConfidenceZ(&ws, sample_detected_object_common_data, sample_speed_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_heading(&ws, sample_detected_object_common_data, sample_heading) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_headingConf(&ws, sample_detected_object_common_data, sample_heading_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_accel4way(&ws, sample_detected_object_common_data, sample_acceleration_set_4_way) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_accCfdX(&ws, sample_detected_object_common_data, sample_acceleration_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_accCfdY(&ws, sample_detected_object_common_data, sample_acceleration_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_accCfdZ(&ws, sample_detected_object_common_data, sample_acceleration_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectCommonData_accCfdYaw(&ws, sample_detected_object_common_data, sample_yaw_rate_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static Attitude* sample_attitude;
static bool_t init_sample_attitude(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_attitude != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_attitude = (Attitude*)mpool_malloc(ws.Pmemory, sizeof(Attitude));
		memset(sample_attitude, 0, sizeof(Attitude));
		if (0) {}
		else if (ASN1_SET_Attitude_pitch(&ws, sample_attitude, sample_pitch_detected) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Attitude_roll(&ws, sample_attitude, sample_roll_detected) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_Attitude_yaw(&ws, sample_attitude, sample_yaw_detected) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static AttitudeConfidence* sample_attitude_confidence;
static bool_t init_sample_attitude_confidence(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_attitude_confidence != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_attitude_confidence = (AttitudeConfidence*)mpool_malloc(ws.Pmemory, sizeof(AttitudeConfidence));
		memset(sample_attitude_confidence, 0, sizeof(AttitudeConfidence));

		if (0) {}
		else if (ASN1_SET_AttitudeConfidence_pitchConfidence(&ws, sample_attitude_confidence, sample_heading_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_AttitudeConfidence_rollConfidence(&ws, sample_attitude_confidence, sample_heading_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_AttitudeConfidence_yawConfidence(&ws, sample_attitude_confidence, sample_heading_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static AngularVelocity* sample_angular_velocity;
static bool_t init_sample_angular_velocity(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_angular_velocity != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_angular_velocity = (AngularVelocity*)mpool_malloc(ws.Pmemory, sizeof(AngularVelocity));
		memset(sample_angular_velocity, 0, sizeof(AngularVelocity));
		if (0) {}
		else if (ASN1_SET_AngularVelocity_pitchRate(&ws, sample_angular_velocity, sample_pitch_rate) < 0)ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_AngularVelocity_rollRate(&ws, sample_angular_velocity, sample_roll_rate) < 0)ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static AngularVelocityConfidence* sample_angular_velocity_confidence;
static bool_t init_sample_angular_velocity_confidence(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_angular_velocity_confidence != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_angular_velocity_confidence = (AngularVelocityConfidence*)mpool_malloc(ws.Pmemory, sizeof(AngularVelocityConfidence));
		memset(sample_angular_velocity_confidence, 0, sizeof(AngularVelocityConfidence));

		if (0) {}
		else if (ASN1_SET_AngularVelocityConfidence_pitchRateConfidence(&ws, sample_angular_velocity_confidence, sample_pitch_rate_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_AngularVelocityConfidence_rollRateConfidence(&ws, sample_angular_velocity_confidence, sample_roll_rate_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static VehicleSizeConfidence* sample_vehicle_size_confidence;
static bool_t init_sample_vehicle_size_confidence(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_vehicle_size_confidence != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_vehicle_size_confidence = (VehicleSizeConfidence*)mpool_malloc(ws.Pmemory, sizeof(VehicleSizeConfidence));
		memset(sample_vehicle_size_confidence, 0, sizeof(VehicleSizeConfidence));

		if (0) {}
		else if (ASN1_SET_VehicleSizeConfidence_vehicleWidthConfidence(&ws, sample_vehicle_size_confidence, sample_size_value_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleSizeConfidence_vehicleLengthConfidence(&ws, sample_vehicle_size_confidence, sample_size_value_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_VehicleSizeConfidence_vehicleHeightConfidence(&ws, sample_vehicle_size_confidence, sample_size_value_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static DetectedVehicleData* sample_detected_vehicle_data;
static bool_t init_sample_detected_vehicle_data(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_detected_vehicle_data != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_detected_vehicle_data = (DetectedVehicleData*)mpool_malloc(ws.Pmemory, sizeof(DetectedVehicleData));
		memset(sample_detected_vehicle_data, 0, sizeof(DetectedVehicleData));

		if (0) {}
		else if (ASN1_SET_DetectedVehicleData_lights(&ws, sample_detected_vehicle_data, sample_exterior_lights, 9) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedVehicleData_vehAttitude(&ws, sample_detected_vehicle_data, sample_attitude) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedVehicleData_vehAttitudeConfidence(&ws, sample_detected_vehicle_data, sample_attitude_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedVehicleData_vehAngVel(&ws, sample_detected_vehicle_data, sample_angular_velocity) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedVehicleData_vehAngVelConfidence(&ws, sample_detected_vehicle_data, sample_angular_velocity_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedVehicleData_size(&ws, sample_detected_vehicle_data, sample_vehicle_size) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedVehicleData_height(&ws, sample_detected_vehicle_data, sample_vehicle_height) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedVehicleData_vehicleSizeConfidence(&ws, sample_detected_vehicle_data, sample_vehicle_size_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedVehicleData_vehicleClass(&ws, sample_detected_vehicle_data, sample_basic_vehicle_class) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedVehicleData_classConf(&ws, sample_detected_vehicle_data, sample_classification_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static PropelledInformation* sample_propelled_information;
static bool_t init_sample_propelled_information(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_propelled_information != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_propelled_information = (PropelledInformation*)mpool_malloc(ws.Pmemory, sizeof(sample_propelled_information));
		memset(sample_propelled_information, 0, sizeof(sample_propelled_information));

		if (0) {}
		else if (ASN1_SET_PropelledInformation_human(&ws, sample_propelled_information, sample_human_propelled_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PropelledInformation_animal(&ws, sample_propelled_information, sample_animal_propelled_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PropelledInformation_motor(&ws, sample_propelled_information, sample_motorized_propelled_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static DetectedVRUData* sample_detected_vru_data;
static bool_t init_sample_detected_vru_data(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_detected_vru_data != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_detected_vru_data = (DetectedVRUData*)mpool_malloc(ws.Pmemory, sizeof(DetectedVRUData));
		memset(sample_detected_vru_data, 0, sizeof(DetectedVRUData));
		if (0) {}
		else if (ASN1_SET_DetectedVRUData_basicType(&ws, sample_detected_vru_data, sample_personal_device_user_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedVRUData_propulsion(&ws, sample_detected_vru_data, sample_propelled_information) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedVRUData_attachment(&ws, sample_detected_vru_data, sample_attachment) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedVRUData_radius(&ws, sample_detected_vru_data, sample_attachment_radius) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static ObstacleSize* sample_obstacle_size;
static bool_t init_sample_obstacle_size(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_obstacle_size != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_obstacle_size = (ObstacleSize*)mpool_malloc(ws.Pmemory, sizeof(ObstacleSize));
		memset(sample_obstacle_size, 0, sizeof(ObstacleSize));
		if (0) {}
		else if (ASN1_SET_ObstacleSize_width(&ws, sample_obstacle_size, sample_size_value) < 0)ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ObstacleSize_length(&ws, sample_obstacle_size, sample_size_value) < 0)ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ObstacleSize_height(&ws, sample_obstacle_size, sample_size_value) < 0)ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static ObstacleSizeConfidence* sample_obstacle_size_confidence;
static bool_t init_sample_obstacle_size_confidence(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_obstacle_size_confidence != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_obstacle_size_confidence = (ObstacleSizeConfidence*)mpool_malloc(ws.Pmemory, sizeof(ObstacleSizeConfidence));
		memset(sample_obstacle_size_confidence, 0, sizeof(ObstacleSizeConfidence));

		if (0) {}
		else if (ASN1_SET_ObstacleSizeConfidence_widthConfidence(&ws, sample_obstacle_size_confidence, sample_size_value_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ObstacleSizeConfidence_lengthConfidence(&ws, sample_obstacle_size_confidence, sample_size_value_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ObstacleSizeConfidence_heightConfidence(&ws, sample_obstacle_size_confidence, sample_size_value_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static DetectedObstacleData* sample_detected_obstacle_data;
static bool_t init_sample_detected_obstacle_data(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_detected_obstacle_data != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_detected_obstacle_data = (DetectedObstacleData*)mpool_malloc(ws.Pmemory, sizeof(DetectedObstacleData));
		memset(sample_detected_obstacle_data, 0, sizeof(DetectedObstacleData));

		if (0) {}
		else if (ASN1_SET_DetectedObstacleData_obstSize(&ws, sample_detected_obstacle_data, sample_obstacle_size) < 0)ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObstacleData_obstSizeConfidence(&ws, sample_detected_obstacle_data, sample_obstacle_size_confidence) < 0)ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static DetectedObjectOptionalData* sample_detected_object_optional_data;
static bool_t init_sample_detected_object_optional_data(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_detected_object_optional_data != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_detected_object_optional_data = (DetectedObjectOptionalData*)mpool_malloc(ws.Pmemory, sizeof(DetectedObjectOptionalData));
		memset(sample_detected_object_optional_data, 0, sizeof(DetectedObjectOptionalData));

		if (0) {}
		else if (ASN1_SET_DetectedObjectOptionalData_detVeh(&ws, sample_detected_object_optional_data, sample_detected_vehicle_data) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_DetectedObjectOptionalData_detVRU(&ws, sample_detected_object_optional_data, sample_detected_vru_data) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_DetectedObjectOptionalData_detObst(&ws, sample_detected_object_optional_data, sample_detected_obstacle_data) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static DetectedObjectData* sample_detected_object_data;
static bool_t init_sample_detected_object_data(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_detected_object_data != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_detected_object_data = (DetectedObjectData*)mpool_malloc(ws.Pmemory, sizeof(DetectedObjectData));
		memset(sample_detected_object_data, 0, sizeof(DetectedObjectData));

		if (0) {}
		else if (ASN1_SET_DetectedObjectData_detObjCommon(&ws, sample_detected_object_data, sample_detected_object_common_data) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_DetectedObjectData_detObjOptData(&ws, sample_detected_object_data, sample_detected_object_optional_data) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static DetectedObjectList* sample_detected_object_list;
static bool_t init_sample_detected_object_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_detected_object_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_detected_object_list = (DetectedObjectList*)mpool_malloc(ws.Pmemory, sizeof(DetectedObjectList));
		memset(sample_detected_object_list, 0, sizeof(DetectedObjectList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_detected_object_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_detected_object_list, sample_detected_object_data) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

// TLS
static TrafficLightID* sample_traffic_light_id;
static bool_t init_sample_traffic_light_id(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_traffic_light_id != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_traffic_light_id = (TrafficLightID*)mpool_malloc(ws.Pmemory, sizeof(TrafficLightID));
		memset(sample_traffic_light_id, 0, sizeof(TrafficLightID));

		if (0) {}
		else if (ASN1_SET_TrafficLightID_id(&ws, sample_traffic_light_id, sample_integer) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_TrafficLightID_oid(&ws, sample_traffic_light_id, sample_oid, 4) < 0 ) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);
		
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static TrafficLightStatus* sample_traffic_light_status;
static bool_t init_sample_traffic_light_status(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_traffic_light_status != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_traffic_light_status = (TrafficLightStatus*)mpool_malloc(ws.Pmemory, sizeof(TrafficLightStatus));
		memset(sample_traffic_light_status, 0, sizeof(TrafficLightStatus));

		if (0) {}
		else if (ASN1_SET_TrafficLightStatus_trafficLightType(&ws, sample_traffic_light_status, sample_traffic_light_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_consecutiveTrafficLight(&ws, sample_traffic_light_status, sample_consecutive_traffic_light) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_trafficLightIntervalType(&ws, sample_traffic_light_status, sample_traffic_light_interval_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_pedestrianCall(&ws, sample_traffic_light_status, sample_pedestrian_call) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_actuatedinterval(&ws, sample_traffic_light_status, sample_actuated_interval) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_permissiveNonProtected(&ws, sample_traffic_light_status, sample_permissive_non_protected) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_lightingStatus(&ws, sample_traffic_light_status, sample_traffic_lighting_status) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_maxIntervalLength(&ws, sample_traffic_light_status, sample_time_in_second_b8) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_remainingTime(&ws, sample_traffic_light_status, sample_time_in_second_b8) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_directionCode(&ws, sample_traffic_light_status, sample_traffic_light_direction_code) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_reserved(&ws, sample_traffic_light_status, sample_reserved_bit) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static TrafficLightStatusList* sample_traffic_light_status_list;		// size(1..255)
static bool_t init_sample_traffic_light_status_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_traffic_light_status_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_traffic_light_status_list = (TrafficLightStatusList*)mpool_malloc(ws.Pmemory, sizeof(TrafficLightStatusList));
		memset(sample_traffic_light_status_list, 0, sizeof(TrafficLightStatusList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_traffic_light_status_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_traffic_light_status_list, sample_traffic_light_status) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}



static TrafficLightStatus_KOR* sample_traffic_light_status_kor;
static bool_t init_sample_traffic_light_status_kor(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_traffic_light_status_kor != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_traffic_light_status_kor = (TrafficLightStatus_KOR*)mpool_malloc(ws.Pmemory, sizeof(TrafficLightStatus_KOR));
		memset(sample_traffic_light_status_kor, 0, sizeof(TrafficLightStatus_KOR));

		if (0) {}
		else if (ASN1_SET_TrafficLightStatus_KOR_trafficLightType(&ws, sample_traffic_light_status_kor, sample_traffic_light_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_KOR_consecutiveTrafficLight(&ws, sample_traffic_light_status_kor, sample_consecutive_traffic_light) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_KOR_trafficLightIntervalType(&ws, sample_traffic_light_status_kor, sample_traffic_light_interval_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_KOR_pedestrianCall(&ws, sample_traffic_light_status_kor, sample_pedestrian_call) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_KOR_actuatedinterval(&ws, sample_traffic_light_status_kor, sample_actuated_interval) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_KOR_permissiveNonProtected(&ws, sample_traffic_light_status_kor, sample_permissive_non_protected) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_KOR_lightingStatus(&ws, sample_traffic_light_status_kor, sample_traffic_lighting_status) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_KOR_maxIntervalLength(&ws, sample_traffic_light_status_kor, sample_time_in_second_b8) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_KOR_remainingTime(&ws, sample_traffic_light_status_kor, sample_time_in_second_b8) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_KOR_directionCode(&ws, sample_traffic_light_status_kor, sample_traffic_light_direction_code) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatus_KOR_reserved(&ws, sample_traffic_light_status_kor, sample_reserved_bit) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static TrafficLightStatusList_KOR* sample_traffic_light_status_list_kor;
static bool_t init_sample_traffic_light_status_list_kor(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_traffic_light_status_list_kor != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_traffic_light_status_list_kor = (TrafficLightStatusList_KOR*)mpool_malloc(ws.Pmemory, sizeof(TrafficLightStatusList_KOR));
		memset(sample_traffic_light_status_list_kor, 0, sizeof(TrafficLightStatusList_KOR));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_traffic_light_status_list_kor) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_traffic_light_status_list_kor, sample_traffic_light_status_kor) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

// EVA
static PrivilegedEvents* sample_privileged_events;
static bool_t init_sample_privileged_events(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_privileged_events != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_privileged_events = (PrivilegedEvents*)mpool_malloc(ws.Pmemory, sizeof(PrivilegedEvents));
		memset(sample_privileged_events, 0, sizeof(PrivilegedEvents));

		if (0) {}
		else if (ASN1_SET_PrivilegedEvents_doNotUse(&ws, sample_privileged_events, sample_ssp_index) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_PrivilegedEvents_event(&ws, sample_privileged_events, sample_privileged_event_flags,16 )<0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static EmergencyDetails* sample_emergency_details;
static bool_t init_sample_emergency_details(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_emergency_details != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_emergency_details = (EmergencyDetails*)mpool_malloc(ws.Pmemory, sizeof(EmergencyDetails));
		memset(sample_emergency_details, 0, sizeof(EmergencyDetails));

		if (0) {}
		else if (ASN1_SET_EmergencyDetails_doNotUse(&ws, sample_emergency_details, sample_ssp_index) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_EmergencyDetails_sirenUse(&ws, sample_emergency_details, sample_siren_in_use) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_EmergencyDetails_lightsUse(&ws, sample_emergency_details, sample_light_bar_in_use) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_EmergencyDetails_multi(&ws, sample_emergency_details, sample_multi_vehicle_response) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_EmergencyDetails_events(&ws, sample_emergency_details, sample_privileged_events) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_EmergencyDetails_responseType(&ws, sample_emergency_details, sample_response_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

// RTCM

static AntennaOffsetSet* sample_antenna_offset_set;
static bool_t init_sample_antenna_offset_set(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_antenna_offset_set != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_antenna_offset_set = (AntennaOffsetSet*)mpool_malloc(ws.Pmemory, sizeof(AntennaOffsetSet));
		memset(sample_antenna_offset_set, 0, sizeof(AntennaOffsetSet));

		if (0) {}
		else if (ASN1_SET_AntennaOffsetSet_antOffsetX(&ws, sample_antenna_offset_set, sample_offset_b12) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_AntennaOffsetSet_antOffsetY(&ws, sample_antenna_offset_set, sample_offset_b09) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_AntennaOffsetSet_antOffsetZ(&ws, sample_antenna_offset_set, sample_offset_b10) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static RTCMheader* sample_rtcm_header;
static bool_t init_sample_rtcm_header(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_rtcm_header != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_rtcm_header = (RTCMheader*)mpool_malloc(ws.Pmemory, sizeof(RTCMheader));
		memset(sample_rtcm_header, 0, sizeof(RTCMheader));

		if (0) {}

		else if (ASN1_SET_RTCMheader_status(&ws, sample_rtcm_header, sample_gnss_status, 8) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RTCMheader_offsetSet(&ws, sample_rtcm_header, sample_antenna_offset_set) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static RTCMmessageList* sample_rtcm_message_list;
static bool_t init_sample_rtcm_message_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_rtcm_message_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_rtcm_message_list = (RTCMmessageList*)mpool_malloc(ws.Pmemory, sizeof(RTCMmessageList));
		memset(sample_rtcm_message_list, 0, sizeof(RTCMmessageList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_rtcm_message_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_rtcm_message_list, (ASNVoid*)&sample_rtcm_message) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static IntersectionAccessPoint* sample_intersection_access_point;
static bool_t init_sample_intersection_access_point(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_intersection_access_point != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_intersection_access_point = (IntersectionAccessPoint*)mpool_malloc(ws.Pmemory, sizeof(IntersectionAccessPoint));
		memset(sample_intersection_access_point, 0, sizeof(IntersectionAccessPoint));

		if (0) {}
		else if (ASN1_SET_IntersectionAccessPoint_lane(&ws, sample_intersection_access_point, sample_lane_id) < 0) ERR_SET_OUT(errp, EFAULT);
		// else if (ASN1_SET_IntersectionAccessPoint_approach(&ws, sample_intersection_access_point, sample_approach_id) < 0) ERR_SET_OUT(errp, EFAULT);
		// else if (ASN1_SET_IntersectionAccessPoint_connection(&ws, sample_intersection_access_point, sample_lane_conection_id) < 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static SignalRequest* sample_signal_request;
static bool_t init_sample_signal_request(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_signal_request != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_signal_request = (SignalRequest*)mpool_malloc(ws.Pmemory, sizeof(SignalRequest));
		memset(sample_signal_request, 0, sizeof(SignalRequest));

		if (0) {}
		else if (ASN1_SET_SignalRequest_id(&ws, sample_signal_request, sample_intersection_reference_id) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalRequest_requestID(&ws, sample_signal_request, sample_request_id) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalRequest_requestType(&ws, sample_signal_request, sample_priority_request_type) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalRequest_inBoundLane(&ws, sample_signal_request, sample_intersection_access_point) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalRequest_outBoundLane(&ws, sample_signal_request, sample_intersection_access_point) < 0) ERR_SET_OUT(errp, EFAULT);
		// else if (ASN1_SET_SignalRequest_regional(&ws, sample_signal_request, ) < 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}



static SignalRequestPackage* sample_signal_request_package;
static bool_t init_sample_signal_request_package(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_signal_request_package != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_signal_request_package = (SignalRequestPackage*)mpool_malloc(ws.Pmemory, sizeof(SignalRequestPackage));
		memset(sample_signal_request_package, 0, sizeof(SignalRequestPackage));

		if (0) {}
		else if (ASN1_SET_SignalRequestPackage_request(&ws, sample_signal_request_package, sample_signal_request) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalRequestPackage_minute(&ws, sample_signal_request_package, sample_minute_of_the_year) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalRequestPackage_second(&ws, sample_signal_request_package, sample_d_second) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalRequestPackage_duration(&ws, sample_signal_request_package, sample_d_second) < 0) ERR_SET_OUT(errp, EFAULT);
		// else if (ASN1_SET_SignalRequestPackage_regional(&ws, sample_signal_request_package, ) < 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static SignalRequestList* sample_signal_request_list;
static bool_t init_sample_signal_request_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_signal_request_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_signal_request_list = (SignalRequestList*)mpool_malloc(ws.Pmemory, sizeof(SignalRequestList));
		memset(sample_signal_request_list, 0, sizeof(SignalRequestList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_signal_request_list) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_signal_request_list, (ASNVoid*)&sample_signal_request_package) < 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static RequestorType* sample_requestor_type;
static bool_t init_sample_requestor_type(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_requestor_type != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_requestor_type = (RequestorType*)mpool_malloc(ws.Pmemory, sizeof(RequestorType));
		memset(sample_requestor_type, 0, sizeof(RequestorType));

		if (0) {}
		else if (ASN1_SET_RequestorType_role(&ws, sample_requestor_type, sample_basic_vehicle_role) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_RequestorType_subrole(&ws, sample_requestor_type, sample_request_sub_role) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_RequestorType_request(&ws, sample_requestor_type, sample_request_importance_level) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_RequestorType_iso3883(&ws, sample_requestor_type, sample_iso_3833_vehicle_type) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_RequestorType_hpmsType(&ws, sample_requestor_type, sample_vehicle_type) < 0) ERR_SET_OUT(errp, EFAULT);
		// else if (ASN1_SET_RequestorType_regional(&ws, sample_requestor_type, ) < 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static RequestorPositionVector* sample_requestor_position_vector;
static bool_t init_sample_requestor_position_vector(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_requestor_position_vector != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_requestor_position_vector = (RequestorPositionVector*)mpool_malloc(ws.Pmemory, sizeof(RequestorPositionVector));
		memset(sample_requestor_position_vector, 0, sizeof(RequestorPositionVector));

		if (0) {}
		else if (ASN1_SET_RequestorPositionVector_position(&ws, sample_requestor_position_vector, sample_position_3d) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_RequestorPositionVector_heading(&ws, sample_requestor_position_vector, sample_angle) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_RequestorPositionVector_speed(&ws, sample_requestor_position_vector, sample_transmission_and_speed) < 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static RequestorDescription* sample_requestor_description;
static bool_t init_sample_requestor_description(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_requestor_description != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_requestor_description = (RequestorDescription*)mpool_malloc(ws.Pmemory, sizeof(RequestorDescription));
		memset(sample_requestor_description, 0, sizeof(RequestorDescription));

		if (0) {}
		else if (ASN1_SET_RequestorDescription_id(&ws, sample_requestor_description, sample_vehicle_id) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_RequestorDescription_type(&ws, sample_requestor_description, sample_requestor_type) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_RequestorDescription_position(&ws, sample_requestor_description, sample_requestor_position_vector) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_RequestorDescription_name(&ws, sample_requestor_description, sample_descriptive_name, 4) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_RequestorDescription_routeName(&ws, sample_requestor_description, sample_descriptive_name, 4) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_RequestorDescription_transitStatus(&ws, sample_requestor_description, sample_transit_vehicle_status, 8) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_RequestorDescription_transitOccupancy(&ws, sample_requestor_description, sample_transit_vehicle_occupancy) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_RequestorDescription_transitSchedule(&ws, sample_requestor_description, sample_delta_time) < 0) ERR_SET_OUT(errp, EFAULT);
		// else if (ASN1_SET_RequestorDescription_regional(&ws, sample_requestor_description, ) < 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static SignalRequesterInfo* sample_signal_requester_info;
static bool_t init_sample_signal_requester_info(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_signal_requester_info != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_signal_requester_info = (SignalRequesterInfo*)mpool_malloc(ws.Pmemory, sizeof(SignalRequesterInfo));
		memset(sample_signal_requester_info, 0, sizeof(SignalRequesterInfo));

		if (0) {}
		else if (ASN1_SET_SignalRequesterInfo_id(&ws, sample_signal_requester_info, sample_vehicle_id) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalRequesterInfo_request(&ws, sample_signal_requester_info, sample_request_id) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalRequesterInfo_sequenceNumber(&ws, sample_signal_requester_info, sample_msg_count) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalRequesterInfo_role(&ws, sample_signal_requester_info, sample_basic_vehicle_role) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalRequesterInfo_typeData(&ws, sample_signal_requester_info,sample_requestor_type ) < 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}


static SignalStatusPackage* sample_signal_status_package;
static bool_t init_sample_signal_status_package(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_signal_status_package != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_signal_status_package = (SignalStatusPackage*)mpool_malloc(ws.Pmemory, sizeof(SignalStatusPackage));
		memset(sample_signal_status_package, 0, sizeof(SignalStatusPackage));

		if (0) {}
		else if (ASN1_SET_SignalStatusPackage_requester(&ws, sample_signal_status_package, sample_signal_requester_info) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalStatusPackage_inboundOn(&ws, sample_signal_status_package, sample_intersection_access_point) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalStatusPackage_outboundOn(&ws, sample_signal_status_package, sample_intersection_access_point) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalStatusPackage_minute(&ws, sample_signal_status_package,sample_minute_of_the_year ) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalStatusPackage_second(&ws, sample_signal_status_package, sample_d_second) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalStatusPackage_duration(&ws, sample_signal_status_package, sample_d_second) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalStatusPackage_status(&ws, sample_signal_status_package, sample_prioritization_response_status) < 0) ERR_SET_OUT(errp, EFAULT);
		// else if (ASN1_SET_SignalStatusPackage_regional(&ws, sample_signal_status_package, ) < 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static SignalStatusPackageList* sample_signal_status_package_list;
static bool_t init_sample_signal_status_package_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_signal_status_package_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_signal_status_package_list = (SignalStatusPackageList*)mpool_malloc(ws.Pmemory, sizeof(SignalStatusPackageList));
		memset(sample_signal_status_package_list, 0, sizeof(SignalStatusPackageList));

		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_signal_status_package_list) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_signal_status_package_list, (ASNVoid*)&sample_signal_status_package) < 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static SignalStatus* sample_signal_status;
static bool_t init_sample_signal_status(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_signal_status != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_signal_status = (SignalStatus*)mpool_malloc(ws.Pmemory, sizeof(SignalStatus));
		memset(sample_signal_status, 0, sizeof(SignalStatus));

		if (0) {}
		else if (ASN1_SET_SignalStatus_sequenceNumber(&ws, sample_signal_status, sample_msg_count) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalStatus_id(&ws, sample_signal_status, sample_intersection_reference_id) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalStatus_sigStatus(&ws, sample_signal_status, sample_signal_status_package_list) < 0) ERR_SET_OUT(errp, EFAULT);
		// else if (ASN1_SET_SignalStatus_regional(&ws, sample_signal_status, ) < 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static SignalStatusList* sample_signal_status_list;
static bool_t init_sample_signal_status_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_signal_status_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_signal_status_list = (SignalStatusList*)mpool_malloc(ws.Pmemory, sizeof(SignalStatusList));
		memset(sample_signal_status_list, 0, sizeof(SignalStatusList));


		if (0) {}
		else if (ASN1_Creat_Init_List(&ws, sample_signal_status_list) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_Insert_Node(&ws, sample_signal_status_list, (ASNVoid*)&sample_signal_status) < 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}




// EAM
static bool_t init_sample_map(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_map != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_map = (MapData*)mpool_malloc(ws.Pmemory, sizeof(MapData));
		memset(sample_map, 0, sizeof(MapData));

		if (0) {}
		else if (ASN1_SET_MapData_timeStamp(&ws, sample_map, sample_minute_of_the_year) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_MapData_msgIssueRevision(&ws, sample_map, sample_msg_count) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_MapData_layerType(&ws, sample_map, sample_layer_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_MapData_layerID(&ws, sample_map, sample_layer_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_MapData_intersections(&ws, sample_map, sample_intersection_geometry_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_MapData_roadSegments(&ws, sample_map, sample_road_segment_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_MapData_dataParameters(&ws, sample_map, sample_data_parameters) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_MapData_restrictionList(&ws, sample_map, sample_restriction_class_list) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_MapData_regional(&ws, sample_map_data, ) < 0) ERR_SET_OUT(errp,EFAULT); // regional
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_spat(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_spat != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_spat = (SPAT*)mpool_malloc(ws.Pmemory, sizeof(SPAT));
		memset(sample_spat, 0, sizeof(SPAT));

		if (0) {}
		else if (ASN1_SET_SPAT_timeStamp(&ws, sample_spat, sample_minute_of_the_year) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_SPAT_name(&ws, sample_spat, sample_descriptive_name, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_SPAT_intersections(&ws, sample_spat, sample_intersection_state_list) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_SPAT_regional(&ws, sample_spat, ) < 0 ) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);


		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_bsm(Dz1Error* err)
{

	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_bsm != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_bsm = (BasicSafetyMessage*)mpool_malloc(ws.Pmemory, sizeof(BasicSafetyMessage));
		memset(sample_bsm, 0, sizeof(BasicSafetyMessage));
		if (0) {}
		else if (ASN1_SET_BasicSafetyMessage_coreData(&ws, sample_bsm, sample_bsm_core_data) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_BasicSafetyMessage_partII(&ws, sample_bsm, sample) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_BasicSafetyMessage_regional(&ws, sample_bsm, sample) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);


		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_pvd(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_pvd != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_pvd = (ProbeVehicleData*)mpool_malloc(ws.Pmemory, sizeof(ProbeVehicleData));
		memset(sample_pvd, 0, sizeof(ProbeVehicleData));


		if (0) {}
		else if (ASN1_SET_ProbeVehicleData_timeStamp(&ws, sample_pvd, sample_minute_of_the_year) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ProbeVehicleData_segNum(&ws, sample_pvd, sample_probe_segment_number) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ProbeVehicleData_probeID(&ws, sample_pvd, sample_vehicle_ident) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ProbeVehicleData_startVector(&ws, sample_pvd, sample_full_position_vector) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ProbeVehicleData_vehicleType(&ws, sample_pvd, sample_vehicle_classification) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_ProbeVehicleData_snapshots(&ws, sample_pvd, sample_pvd_snapshots) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_ProbeVehicleData_regional(&ws, sample_pvd, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_rsa(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_rsa != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_rsa = (RoadSideAlert*)mpool_malloc(ws.Pmemory, sizeof(RoadSideAlert));
		memset(sample_rsa, 0, sizeof(RoadSideAlert));
		if (0) {}
		else if (ASN1_SET_RoadSideAlert_msgCnt(&ws, sample_rsa, sample_msg_count) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSideAlert_timeStamp(&ws, sample_rsa, sample_minute_of_the_year) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSideAlert_typeEvent(&ws, sample_rsa, sample_itis_codes) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSideAlert_description(&ws, sample_rsa, sample_road_side_alert_description) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSideAlert_priority(&ws, sample_rsa, sample_priority, 1) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSideAlert_heading(&ws, sample_rsa, sample_heading_slice, 16) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSideAlert_extent(&ws, sample_rsa, sample_extent) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSideAlert_position(&ws, sample_rsa, sample_full_position_vector) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RoadSideAlert_furtherInfoID(&ws, sample_rsa, sample_further_info_id, 2) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_RoadSideAlert_regional(&ws, sample_rsa, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_tim(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_tim != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_tim = (TravelerInformation*)mpool_malloc(ws.Pmemory, sizeof(TravelerInformation));
		memset(sample_tim, 0, sizeof(TravelerInformation));
		if (0) {}
		else if (ASN1_SET_TravelerInformation_msgCnt(&ws, sample_tim, sample_msg_count) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TravelerInformation_timeStamp(&ws, sample_tim, sample_minute_of_the_year) < 0) ERR_SET_OUT(errp,EFAULT);
		//else if (ASN1_SET_TravelerInformation_packetID(&ws, sample_tim, sample_unique_msg_id, 9) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TravelerInformation_urlB(&ws, sample_tim, sample_url_base, 3) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TravelerInformation_dataFrames(&ws, sample_tim, sample_traveler_data_frame_list) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_TravelerInformation_regional(&ws, sample_tim, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_sdsm(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_sdsm != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_sdsm = (SensorDataSharingMessage*)mpool_malloc(ws.Pmemory, sizeof(SensorDataSharingMessage));
		memset(sample_sdsm, 0, sizeof(SensorDataSharingMessage));

		if (0) {}
		else if (ASN1_SET_SensorDataSharingMessage_msgCnt(&ws, sample_sdsm, sample_msg_count) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_SensorDataSharingMessage_sourceID(&ws, sample_sdsm, sample_temporary_id, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_SensorDataSharingMessage_equipmentType(&ws, sample_sdsm, sample_equipment_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_SensorDataSharingMessage_sDSMTimeStamp(&ws, sample_sdsm, sample_d_date_time) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_SensorDataSharingMessage_refPos(&ws, sample_sdsm, sample_position_3d) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_SensorDataSharingMessage_refPosXYConf(&ws, sample_sdsm, sample_positional_accuracy) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_SensorDataSharingMessage_refPosElConf(&ws, sample_sdsm, sample_elevation_confidence) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_SensorDataSharingMessage_objects(&ws, sample_sdsm, sample_detected_object_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_tls(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_tls != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_tls = (TLS*)mpool_malloc(ws.Pmemory, sizeof(TLS));
		memset(sample_tls, 0, sizeof(TLS));
		if (0) {}
		else if (ASN1_SET_TLS_trafficLightID(&ws, sample_tls, sample_traffic_light_id) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TLS_lon(&ws, sample_tls, sample_longitude) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TLS_lat(&ws, sample_tls, sample_latitude) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TLS_operationStatus(&ws, sample_tls, sample_traffic_light_operation_status, 8) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TLS_controllerStatus(&ws, sample_tls, sample_traffic_light_controller_status, 8) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TLS_cyclecounter(&ws, sample_tls, sample_time_in_second_b16) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TLS_cycletime(&ws, sample_tls, sample_time_in_second_b16) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TLS_currentTime(&ws, sample_tls, sample_d_date_time) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TLS_trafficLightStatus(&ws, sample_tls, sample_traffic_light_status_list) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);


		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}


	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_tlsm(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_tlsm != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_tlsm = (TrafficLightStatusMessage*)mpool_malloc(ws.Pmemory, sizeof(TrafficLightStatusMessage));
		memset(sample_tlsm, 0, sizeof(TrafficLightStatusMessage));
		if (0) {}
		else if (ASN1_SET_TrafficLightStatusMessage_traffiLightID(&ws, sample_tlsm, sample_integer) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatusMessage_lon(&ws, sample_tlsm, sample_longitude) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatusMessage_lat(&ws, sample_tlsm, sample_latitude) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatusMessage_operationStatus(&ws, sample_tlsm, sample_traffic_light_operation_status, 8) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatusMessage_controllerStatus(&ws, sample_tlsm, sample_traffic_light_controller_status, 8) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatusMessage_cycleCounter(&ws, sample_tlsm, sample_time_in_second_b16) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatusMessage_cycleTime(&ws, sample_tlsm, sample_time_in_second_b16) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatusMessage_currentTime(&ws, sample_tlsm, sample_d_date_time) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_TrafficLightStatusMessage_trafficLightStatus(&ws, sample_tlsm, sample_traffic_light_status_list_kor) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);


		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_eva(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_eva != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_eva = (EmergencyVehicleAlert*)mpool_malloc(ws.Pmemory, sizeof(EmergencyVehicleAlert));
		memset(sample_eva, 0, sizeof(EmergencyVehicleAlert));
		if (0) {}
		else if (ASN1_SET_EmergencyVehicleAlert_timeStamp(&ws, sample_eva, sample_minute_of_the_year) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_EmergencyVehicleAlert_id(&ws, sample_eva, sample_temporary_id, 4) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_EmergencyVehicleAlert_rsaMsg(&ws, sample_eva, sample_rsa) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_EmergencyVehicleAlert_responseType(&ws, sample_eva, sample_response_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_EmergencyVehicleAlert_details(&ws, sample_eva, sample_emergency_details) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_EmergencyVehicleAlert_mass(&ws, sample_eva, sample_vehicle_mass) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_EmergencyVehicleAlert_basicType(&ws, sample_eva, sample_vehicle_type) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_EmergencyVehicleAlert_vehicleType(&ws, sample_eva, sample_vehicle_group_affected) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_EmergencyVehicleAlert_responseEquip(&ws, sample_eva, sample_incident_response_equipment) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_EmergencyVehicleAlert_responderType(&ws, sample_eva, sample_responder_group_affected) < 0) ERR_SET_OUT(errp,EFAULT);
		// else if (ASN1_SET_EmergencyVehicleAlert_regional(&ws, sample_eva, ) < 0) ERR_SET_OUT(errp,EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_rtcm(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_rtcm != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_rtcm = (RTCMcorrections*)mpool_malloc(ws.Pmemory, sizeof(RTCMcorrections));
		memset(sample_rtcm, 0, sizeof(RTCMcorrections));

		if (0) {}
		else if (ASN1_SET_RTCMcorrections_msgCnt(&ws, sample_rtcm, sample_msg_count) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RTCMcorrections_rev(&ws, sample_rtcm, sample_rtcm_revision) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RTCMcorrections_timeStamp(&ws, sample_rtcm, sample_minute_of_the_year) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RTCMcorrections_anchorPoint(&ws, sample_rtcm, sample_full_position_vector) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RTCMcorrections_rtcmHeader(&ws, sample_rtcm, sample_rtcm_header) < 0) ERR_SET_OUT(errp,EFAULT);
		else if (ASN1_SET_RTCMcorrections_msgs(&ws, sample_rtcm, sample_rtcm_message_list) < 0) ERR_SET_OUT(errp,EFAULT);

		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_srm(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_srm != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_srm = (SignalRequestMessage*)mpool_malloc(ws.Pmemory, sizeof(SignalRequestMessage));
		memset(sample_srm, 0, sizeof(SignalRequestMessage));
		if (0) {}
		else if (ASN1_SET_SignalRequestMessage_timeStamp(&ws, sample_srm, sample_minute_of_the_year) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalRequestMessage_second(&ws, sample_srm, sample_d_second) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalRequestMessage_sequenceNumber(&ws, sample_srm, sample_msg_count) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalRequestMessage_requests(&ws, sample_srm, sample_signal_request_list) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalRequestMessage_requestor(&ws, sample_srm, sample_requestor_description) < 0) ERR_SET_OUT(errp, EFAULT);
		// else if (ASN1_SET_SignalRequestMessage_regional(&ws, sample_srm, ) < 0) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ASN1_Print_SignalRequestMessage(sample_srm, 0);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_ssm(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_ssm != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_ssm = (SignalStatusMessage*)mpool_malloc(ws.Pmemory, sizeof(SignalStatusMessage));
		memset(sample_ssm, 0, sizeof(SignalStatusMessage));

		if (0) {}
		else if (ASN1_SET_SignalStatusMessage_timeStamp(&ws, sample_ssm, sample_minute_of_the_year) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalStatusMessage_second(&ws, sample_ssm, sample_d_second) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalStatusMessage_sequenceNumber(&ws, sample_ssm, sample_msg_count) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_SignalStatusMessage_status(&ws, sample_ssm, sample_signal_status_list) < 0) ERR_SET_OUT(errp, EFAULT);
		// else if (ASN1_SET_SignalStatusMessage_regional(&ws, sample_ssm, ) < 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_psm(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_psm != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		sample_psm = (PersonalSafetyMessage*)mpool_malloc(ws.Pmemory, sizeof(PersonalSafetyMessage));
		memset(sample_psm, 0, sizeof(PersonalSafetyMessage));

		if (0) {}
		else if (ASN1_SET_PersonalSafetyMessage_basicType(&ws, sample_psm, sample_personal_device_user_type) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_secMark(&ws, sample_psm, sample_d_second) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_msgCnt(&ws, sample_psm, sample_msg_count) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_id(&ws, sample_psm, sample_temporary_id, 4) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_position(&ws, sample_psm, sample_position_3d) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_accuracy(&ws, sample_psm, sample_positional_accuracy) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_speed(&ws, sample_psm, sample_velocity) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_heading(&ws, sample_psm, sample_heading) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_accelSet(&ws, sample_psm, sample_acceleration_set_4_way) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_pathHistory(&ws, sample_psm, sample_path_history ) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_pathPrediction(&ws, sample_psm, sample_path_prediction) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_propulsion(&ws, sample_psm, sample_propelled_information) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_useState(&ws, sample_psm, sample_personal_device_usage_state, 9) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_crossRequest(&ws, sample_psm, sample_personal_crossing_request) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_crossState(&ws, sample_psm, sample_personal_crossing_in_progress) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_clusterSize(&ws, sample_psm, sample_number_of_participants_in_cluster) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_clusterRadius(&ws, sample_psm, sample_personal_cluster_radius) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_eventResponderType(&ws, sample_psm, sample_public_safety_event_responder_worker_type) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_activityType(&ws, sample_psm, sample_public_safety_and_road_worker_activity, 6) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_activitySubType(&ws, sample_psm, sample_public_safety_directing_traffic_sub_type,7 ) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_assistType(&ws, sample_psm, sample_personal_assitive, 6) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_sizing(&ws, sample_psm, sample_user_size_and_behavior, 5) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_attachment(&ws, sample_psm, sample_attachment) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_attachmentRadius(&ws, sample_psm,sample_attachment_radius ) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_SET_PersonalSafetyMessage_animalType(&ws, sample_psm, sample_animal_type) < 0) ERR_SET_OUT(errp, EFAULT);
		// else if (ASN1_SET_PersonalSafetyMessage_regional(&ws, sample_psm, ) < 0) ERR_SET_OUT(errp, EFAULT);

		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	}

	return ERR_IS_SUCCESS(errp);
}






bool_t GitsnAsnUtil_initSample(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) {}
	// df
	else if (init_sample_vehicle_id(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_vehicle_ident_vehicle_class(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_vehicle_ident(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_d_date_time(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_transmission_and_speed(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_positional_accuracy(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_position_confidence_set(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_speed_and_heading_and_throttle_confidence(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_full_position_vector(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_vehicle_classification(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_path_history_point(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_path_history_point_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_path_history(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);

	else if (init_sample_path_prediction(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_vehicle_safety_extension(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_wiper_set(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_brake_system_status(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_vehicle_status_steering(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_acceleration_set_4_way(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_accel_steer_yaw_rate_confidence(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_confidence_set(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_vehicle_status_accel_sets(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_vehicle_status_object(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_bumper_heights(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_vehicle_status_vehicle_data(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_tire_data(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_tire_data_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_axle_weight_set(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_axle_weight_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_j1939_data_items(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_vehicle_status_weather_report(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_vehicle_status(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_snapshot(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_pvd_snapshots(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_position_3d(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_intersection_reference_id(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_regulatory_speed_limit(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_speed_limit_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_lane_type_attributes(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_lane_attributes(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_xy_20_b(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_xy_22_b(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_xy_24_b(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_xy_26_b(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_xy_28_b(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_xy_32_b(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_llmd_64_b(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_offset_point_xy(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_attribute_xy_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_segment_attribute_xy_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_lane_data_attribute(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_lane_data_attribute_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_attribute_set_xy(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_xy_1(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_xy_2(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_set_xy(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_computed_lane_offset_x_axis(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_computed_lane_offset_y_axis(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_computed_lane(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_list_xy(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_connecting_lane(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_connection(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_connects_to_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_overlay_lane_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_generic_lane(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_lane_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_signal_control_zone(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_preempt_priority_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_intersection_geometry(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_intersection_geometry_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_road_segment_reference_id(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_road_lane_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_road_segment(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_road_segment_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_data_parameters(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_restriction_user_type(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_restriction_user_type_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_restriction_class_assignment(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_restriction_class_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_enabled_lane_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_time_change_details(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_advisory_speed(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_advisory_speed_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_msovement_event(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_movement_event_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_connection_maneuver_assist(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_maneuver_assist_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_movement_state(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_movement_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_intersection_state(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_intersection_state_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_vehicle_size(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_bsm_core_data(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_road_side_alert_description(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_road_sign_id(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_traveler_data_frame_msg_id(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_ll_24_b(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_ll_28_b(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_ll_32_b(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_ll_36_b(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_ll_44_b(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_ll_48_b(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_offset_point_ll(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_attribute_ll_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_segment_attribute_ll_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_attribute_set_ll(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_ll_1(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_ll_2(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_set_ll(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_node_list_ll(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_offset_system_offset(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_offset_system(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_circle(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_geometric_projection(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_region_offsets(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_region_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_region_point_set(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_shape_point_set(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_valid_region_area(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_valid_region(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_geographical_path_description(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_geographical_path(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_traveler_data_frame_regions(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_itis_codes_and_text_element_item(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_itis_codes_and_text_element(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_itis_codes_and_text(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_work_zone_element_item(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_work_zone_element(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_work_zone(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_generic_signage_element_item(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_generic_signage_element(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_generic_signage(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_speed_limit_element_item(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_speed_limit_element(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_speed_limit(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_exit_service_element_item(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_exit_service_element(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_exit_service(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_traveler_data_frame_content(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_traveler_data_frame(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_traveler_data_frame_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);

	else if (init_sample_position_offset_xyz(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_detected_object_common_data(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_attitude(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_attitude_confidence(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_angular_velocity(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_angular_velocity_confidence(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_vehicle_size_confidence(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_detected_vehicle_data(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_propelled_information(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_detected_vru_data(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);

	else if (init_sample_obstacle_size(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_obstacle_size_confidence(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_detected_obstacle_data(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_detected_object_optional_data(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_detected_object_data(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_detected_object_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	// tls
	else if (init_sample_traffic_light_id(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_traffic_light_status(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_traffic_light_status_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);

	else if (init_sample_traffic_light_status_kor(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_traffic_light_status_list_kor(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	// eva
	else if (init_sample_privileged_events(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_emergency_details(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	// rtcm
	else if (init_sample_antenna_offset_set(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_rtcm_header(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_rtcm_message_list(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	// srm
	else if (init_sample_intersection_access_point(errp) == FALSE) ERR_OUT(errp);
	else if (init_sample_signal_request(errp) == FALSE) ERR_OUT(errp);
	else if (init_sample_signal_request_package(errp) == FALSE) ERR_OUT(errp);
	else if (init_sample_signal_request_list(errp) == FALSE) ERR_SET_OUT(errp, EFAULT);
	else if (init_sample_requestor_type(errp) == FALSE) ERR_SET_OUT(errp, EFAULT);
	else if (init_sample_requestor_position_vector(errp) == FALSE) ERR_SET_OUT(errp, EFAULT);
	else if (init_sample_requestor_description(errp) == FALSE) ERR_OUT(errp);

	// ssm
	else if (init_sample_signal_requester_info(errp) == FALSE) ERR_OUT(errp);

	else if (init_sample_signal_status_package(errp) == FALSE) ERR_OUT(errp);
	else if (init_sample_signal_status_package_list(errp) == FALSE) ERR_OUT(errp);
	else if (init_sample_signal_status(errp) == FALSE) ERR_OUT(errp);
	else if (init_sample_signal_status_list(errp) == FALSE) ERR_OUT(errp);


	// eam
	else if (init_sample_map(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_bsm(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_pvd(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_spat(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_rsa(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_tim(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_sdsm(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_tls(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_tlsm(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	// else if (init_sample_eva(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_rtcm(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	// else if (init_sample_srm(errp) == FALSE) ERR_SET_OUT(errp,EFAULT);
	else if (init_sample_ssm(errp) == FALSE) ERR_SET_OUT(errp, EFAULT);
	else if (init_sample_psm(errp) == FALSE) ERR_OUT(errp);
	// tbd

	else
	{
		ASN1_Print_SPAT(sample_spat, 0);
		ASN1_Print_MapData(sample_map, 0);
		ASN1_Print_BasicSafetyMessage(sample_bsm, 0);
		ASN1_Print_ProbeVehicleData(sample_pvd, 0);
		ASN1_Print_RoadSideAlert(sample_rsa, 0);
		ASN1_Print_TravelerInformation(sample_tim, 0);
		ASN1_Print_SensorDataSharingMessage(sample_sdsm, 0);
		ASN1_Print_TLS(sample_tls, 0);
		ASN1_Print_TrafficLightStatusMessage(sample_tlsm, 0);
		// ASN1_Print_EmergencyVehicleAlert(sample_eva, 0);
		ASN1_Print_RTCMcorrections(sample_rtcm, 0);
		// ASN1_Print_SignalRequestMessage(sample_srm, 0);
		ASN1_Print_SignalStatusMessage(sample_ssm, 0);
		ASN1_Print_PersonalSafetyMessage(sample_psm, 0);

		Dz1Error_set(errp, 0);
	}

	return ERR_IS_SUCCESS(errp);
}
