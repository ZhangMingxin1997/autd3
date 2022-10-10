// This file was automatically generated from header file

#ifdef C2NIM
#  dynlib dll
#  cdecl
#  if defined(windows)
#    define dll "bin/autd3capi.dll"
#  elif defined(macosx)
#    define dll "bin/libautd3capi.dylib"
#  else
#    define dll "bin/libautd3capi.so"
#  endif
#endif

int32 AUTDGetLastError(char* error);
void AUTDCreateController(void** out);
bool AUTDOpenController(void* handle, void* link);
int32 AUTDAddDevice(void* handle, float64 x, float64 y, float64 z, float64 rz1, float64 ry, float64 rz2);
int32 AUTDAddDeviceQuaternion(void* handle, float64 x, float64 y, float64 z, float64 qw, float64 qx, float64 qy, float64 qz);
int32 AUTDClose(void* handle);
int32 AUTDClear(void* handle);
int32 AUTDSynchronize(void* handle);
void AUTDFreeController(void* handle);
bool AUTDIsOpen(void* handle);
bool AUTDGetForceFan(void* handle);
bool AUTDGetReadsFPGAInfo(void* handle);
int32 AUTDGetCheckTrials(void* handle);
int32 AUTDGetSendInterval(void* handle);
void AUTDSetReadsFPGAInfo(void* handle, bool reads_fpga_info);
void AUTDSetCheckTrials(void* handle, int32 trials);
void AUTDSetSendInterval(void* handle, int32 interval);
void AUTDSetForceFan(void* handle, bool force);
float64 AUTDGetSoundSpeed(void* handle);
void AUTDSetSoundSpeed(void* handle, float64 sound_speed);
float64 AUTDGetTransFrequency(void* handle, int32 device_idx, int32 local_trans_idx);
void AUTDSetTransFrequency(void* handle, int32 device_idx, int32 local_trans_idx, float64 frequency);
uint16 AUTDGetTransCycle(void* handle, int32 device_idx, int32 local_trans_idx);
void AUTDSetTransCycle(void* handle, int32 device_idx, int32 local_trans_idx, uint16 cycle);
float64 AUTDGetWavelength(void* handle, int32 device_idx, int32 local_trans_idx);
float64 AUTDGetAttenuation(void* handle);
void AUTDSetAttenuation(void* handle, float64 attenuation);
bool AUTDGetFPGAInfo(void* handle, uint8* out);
int32 AUTDUpdateFlags(void* handle);
int32 AUTDNumDevices(void* handle);
void AUTDTransPosition(void* handle, int32 device_idx, int32 local_trans_idx, float64* x, float64* y, float64* z);
void AUTDTransXDirection(void* handle, int32 device_idx, int32 local_trans_idx, float64* x, float64* y, float64* z);
void AUTDTransYDirection(void* handle, int32 device_idx, int32 local_trans_idx, float64* x, float64* y, float64* z);
void AUTDTransZDirection(void* handle, int32 device_idx, int32 local_trans_idx, float64* x, float64* y, float64* z);
int32 AUTDGetFirmwareInfoListPointer(void* handle, void** out);
void AUTDGetFirmwareInfo(void* p_firm_info_list, int32 index, char* info);
void AUTDFreeFirmwareInfoListPointer(void* p_firm_info_list);
void AUTDGainNull(void** gain);
void AUTDGainGrouped(void** gain, void* handle);
void AUTDGainGroupedAdd(void* grouped_gain, int32 device_id, void* gain);
void AUTDGainFocus(void** gain, float64 x, float64 y, float64 z, float64 amp);
void AUTDGainBesselBeam(void** gain, float64 x, float64 y, float64 z, float64 n_x, float64 n_y, float64 n_z, float64 theta_z, float64 amp);
void AUTDGainPlaneWave(void** gain, float64 n_x, float64 n_y, float64 n_z, float64 amp);
void AUTDGainCustom(void** gain, float64* amp, float64* phase, uint64 size);
void AUTDDeleteGain(void* gain);
void AUTDModulationStatic(void** mod, float64 amp);
void AUTDModulationSine(void** mod, int32 freq, float64 amp, float64 offset);
void AUTDModulationSineSquared(void** mod, int32 freq, float64 amp, float64 offset);
void AUTDModulationSineLegacy(void** mod, float64 freq, float64 amp, float64 offset);
void AUTDModulationSquare(void** mod, int32 freq, float64 low, float64 high, float64 duty);
void AUTDModulationCustom(void** mod, uint8* buffer, uint64 size, uint32 freq_div);
uint32 AUTDModulationSamplingFrequencyDivision(void* mod);
void AUTDModulationSetSamplingFrequencyDivision(void* mod, uint32 freq_div);
float64 AUTDModulationSamplingFrequency(void* mod);
void AUTDDeleteModulation(void* mod);
void AUTDPointSTM(void** out);
void AUTDGainSTM(void** out, void* handle);
bool AUTDPointSTMAdd(void* stm, float64 x, float64 y, float64 z, uint8 shift);
bool AUTDGainSTMAdd(void* stm, void* gain);
uint16 AUTDGetGainSTMMode(void* stm);
void AUTDSetGainSTMMode(void* stm, uint16 mode);
float64 AUTDSTMSetFrequency(void* stm, float64 freq);
float64 AUTDSTMFrequency(void* stm);
float64 AUTDSTMSamplingFrequency(void* stm);
uint32 AUTDSTMSamplingFrequencyDivision(void* stm);
void AUTDSTMSetSamplingFrequencyDivision(void* stm, uint32 freq_div);
void AUTDDeleteSTM(void* stm);
int32 AUTDStop(void* handle);
void AUTDCreateSilencer(void** out, uint16 step, uint16 cycle);
void AUTDDeleteSilencer(void* config);
int32 AUTDSend(void* handle, void* header, void* body);
void AUTDSetModDelay(void* handle, int32 device_idx, int32 local_trans_idx, uint16 delay);
void AUTDCreateModDelayConfig(void** out);
void AUTDDeleteModDelayConfig(void* config);
void AUTDCreateAmplitudes(void** out, float64 amp);
void AUTDDeleteAmplitudes(void* amplitudes);
void AUTDSetMode(void* handle, uint8 mode);
void AUTDSoftwareSTM(void** out);
void AUTDSoftwareSTMSetStrategy(void* stm, uint8 strategy);
void AUTDSoftwareSTMAdd(void* stm, void* gain);
void AUTDSoftwareSTMStart(void** handle, void* stm, void* cnt);
void AUTDSoftwareSTMFinish(void** cnt, void* handle);
float64 AUTDSoftwareSTMSetFrequency(void* stm, float64 freq);
float64 AUTDSoftwareSTMFrequency(void* stm);
uint64 AUTDSoftwareSTMPeriod(void* stm);
float64 AUTDSoftwareSTMSamplingFrequency(void* stm);
uint64 AUTDSoftwareSTMSamplingPeriod(void* stm);
void AUTDSoftwareSTMSetSamplingPeriod(void* stm, uint64 period);
void AUTDDeleteSoftwareSTM(void* stm);