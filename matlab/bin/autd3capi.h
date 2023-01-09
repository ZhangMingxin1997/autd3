// This file was automatically generated from header file

typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
#ifdef WIN32
typedef long long int64_t;
typedef unsigned long long uint64_t;
#else
typedef long int64_t;
typedef unsigned long uint64_t;
#endif

void AUTDSetLogLevel(int32_t level);
void AUTDSetDefaultLogger(void* out, void* flush);
void AUTDCreateController(void** out);
bool AUTDOpenController(void* handle, void* link);
bool AUTDAddDevice(void* handle, double x, double y, double z, double rz1, double ry, double rz2);
bool AUTDAddDeviceQuaternion(void* handle, double x, double y, double z, double qw, double qx, double qy, double qz);
bool AUTDClose(void* handle);
void AUTDFreeController(void* handle);
bool AUTDIsOpen(void* handle);
bool AUTDGetForceFan(void* handle);
bool AUTDGetReadsFPGAInfo(void* handle);
uint64_t AUTDGetAckCheckTimeout(void* handle);
uint64_t AUTDGetSendInterval(void* handle);
void AUTDSetReadsFPGAInfo(void* handle, bool reads_fpga_info);
void AUTDSetAckCheckTimeout(void* handle, uint64_t timeout);
void AUTDSetSendInterval(void* handle, uint64_t interval);
void AUTDSetForceFan(void* handle, bool force);
double AUTDGetSoundSpeed(void* handle);
void AUTDSetSoundSpeed(void* handle, double sound_speed);
void AUTDSetSoundSpeedFromTemp(void* handle, double temp, double k, double r, double m);
double AUTDGetTransFrequency(void* handle, int32_t trans_idx);
void AUTDSetTransFrequency(void* handle, int32_t trans_idx, double frequency);
uint16_t AUTDGetTransCycle(void* handle, int32_t trans_idx);
void AUTDSetTransCycle(void* handle, int32_t trans_idx, uint16_t cycle);
double AUTDGetWavelength(void* handle, int32_t trans_idx);
double AUTDGetAttenuation(void* handle);
void AUTDSetAttenuation(void* handle, double attenuation);
bool AUTDGetFPGAInfo(void* handle, uint8_t* out);
int32_t AUTDNumTransducers(void* handle);
int32_t AUTDNumDevices(void* handle);
void AUTDGeometryCenter(void* handle, double* x, double* y, double* z);
void AUTDGeometryCenterOf(void* handle, int32_t dev_idx, double* x, double* y, double* z);
void AUTDTransPosition(void* handle, int32_t trans_idx, double* x, double* y, double* z);
void AUTDTransXDirection(void* handle, int32_t trans_idx, double* x, double* y, double* z);
void AUTDTransYDirection(void* handle, int32_t trans_idx, double* x, double* y, double* z);
void AUTDTransZDirection(void* handle, int32_t trans_idx, double* x, double* y, double* z);
int32_t AUTDGetFirmwareInfoListPointer(void* handle, void** out);
void AUTDGetFirmwareInfo(void* p_firm_info_list, int32_t index, int8_t* info);
void AUTDFreeFirmwareInfoListPointer(void* p_firm_info_list);
void AUTDGainNull(void** gain);
void AUTDGainGrouped(void** gain);
void AUTDGainGroupedAdd(void* grouped_gain, int32_t device_id, void* gain);
void AUTDGainFocus(void** gain, double x, double y, double z, double amp);
void AUTDGainBesselBeam(void** gain, double x, double y, double z, double n_x, double n_y, double n_z, double theta_z, double amp);
void AUTDGainPlaneWave(void** gain, double n_x, double n_y, double n_z, double amp);
void AUTDGainTransducerTest(void** gain);
void AUTDGainTransducerTestSet(void* gain, int32_t tr_idx, double amp, double phase);
void AUTDGainCustom(void** gain, double* amp, double* phase, uint64_t size);
void AUTDDeleteGain(void* gain);
void AUTDModulationStatic(void** mod, double amp);
void AUTDModulationSine(void** mod, int32_t freq, double amp, double offset);
void AUTDModulationSineSquared(void** mod, int32_t freq, double amp, double offset);
void AUTDModulationSineLegacy(void** mod, double freq, double amp, double offset);
void AUTDModulationSquare(void** mod, int32_t freq, double low, double high, double duty);
void AUTDModulationLPF(void** mod, void* mod_in);
void AUTDModulationCustom(void** mod, uint8_t* buffer, uint64_t size, uint32_t freq_div);
uint32_t AUTDModulationSamplingFrequencyDivision(void* mod);
void AUTDModulationSetSamplingFrequencyDivision(void* mod, uint32_t freq_div);
double AUTDModulationSamplingFrequency(void* mod);
void AUTDDeleteModulation(void* mod);
void AUTDFocusSTM(void** out);
void AUTDGainSTM(void** out);
void AUTDFocusSTMAdd(void* stm, double x, double y, double z, uint8_t shift);
void AUTDGainSTMAdd(void* stm, void* gain);
uint16_t AUTDGetGainSTMMode(void* stm);
void AUTDSetGainSTMMode(void* stm, uint16_t mode);
double AUTDSTMSetFrequency(void* stm, double freq);
int32_t AUTDSTMGetStartIdx(void* stm);
int32_t AUTDSTMGetFinishIdx(void* stm);
void AUTDSTMSetStartIdx(void* stm, int32_t start_idx);
void AUTDSTMSetFinishIdx(void* stm, int32_t finish_idx);
double AUTDSTMFrequency(void* stm);
double AUTDSTMSamplingFrequency(void* stm);
uint32_t AUTDSTMSamplingFrequencyDivision(void* stm);
void AUTDSTMSetSamplingFrequencyDivision(void* stm, uint32_t freq_div);
void AUTDDeleteSTM(void* stm);
void AUTDSynchronize(void** out);
void AUTDClear(void** out);
void AUTDUpdateFlags(void** out);
void AUTDStop(void** out);
void AUTDModDelayConfig(void** out);
void AUTDDeleteSpecialData(void* data);
void AUTDCreateSilencer(void** out, uint16_t step, uint16_t cycle);
void AUTDDeleteSilencer(void* config);
bool AUTDSend(void* handle, void* header, void* body);
bool AUTDSendSpecial(void* handle, void* special);
void AUTDSendAsync(void* handle, void* header, void* body);
void AUTDSendSpecialAsync(void* handle, void* special);
uint16_t AUTDGetModDelay(void* handle, int32_t trans_idx);
void AUTDSetModDelay(void* handle, int32_t trans_idx, uint16_t delay);
void AUTDCreateAmplitudes(void** out, double amp);
void AUTDDeleteAmplitudes(void* amplitudes);
void AUTDSetMode(void* handle, uint8_t mode);
void AUTDSoftwareSTM(void** out);
void AUTDSoftwareSTMSetStrategy(void* stm, uint8_t strategy);
void AUTDSoftwareSTMAdd(void* stm, void* gain);
void AUTDSoftwareSTMStart(void** handle, void* stm, void* cnt);
void AUTDSoftwareSTMFinish(void* handle);
double AUTDSoftwareSTMSetFrequency(void* stm, double freq);
double AUTDSoftwareSTMFrequency(void* stm);
uint64_t AUTDSoftwareSTMPeriod(void* stm);
double AUTDSoftwareSTMSamplingFrequency(void* stm);
uint64_t AUTDSoftwareSTMSamplingPeriod(void* stm);
void AUTDSoftwareSTMSetSamplingPeriod(void* stm, uint64_t period);
void AUTDDeleteSoftwareSTM(void* stm);
