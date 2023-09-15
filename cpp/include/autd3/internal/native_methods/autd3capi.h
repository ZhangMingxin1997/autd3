#pragma once

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <cstdint>

namespace autd3::internal::native_methods {

struct ControllerBuilderPtr {
  void* _0;
};

struct FirmwareInfoListPtr {
  void* _0;
};

struct Drive {
  double phase;
  double amp;
};

extern "C" {

[[nodiscard]] ControllerBuilderPtr AUTDCreateControllerBuilder();

ControllerBuilderPtr AUTDAddDevice(ControllerBuilderPtr builder,
                                   double x,
                                   double y,
                                   double z,
                                   double rz1,
                                   double ry,
                                   double rz2);

ControllerBuilderPtr AUTDAddDeviceQuaternion(ControllerBuilderPtr builder,
                                             double x,
                                             double y,
                                             double z,
                                             double qw,
                                             double qx,
                                             double qy,
                                             double qz);

[[nodiscard]]
ControllerPtr AUTDControllerOpenWith(ControllerBuilderPtr builder,
                                     LinkPtr link,
                                     char *err);

[[nodiscard]] bool AUTDClose(ControllerPtr cnt, char *err);

void AUTDFreeController(ControllerPtr cnt);

[[nodiscard]] bool AUTDGetFPGAInfo(ControllerPtr cnt, uint8_t *out, char *err);

[[nodiscard]] FirmwareInfoListPtr AUTDGetFirmwareInfoListPointer(ControllerPtr cnt, char *err);

void AUTDGetFirmwareInfo(FirmwareInfoListPtr p_info_list, uint32_t idx, char *info);

void AUTDFreeFirmwareInfoListPointer(FirmwareInfoListPtr p_info_list);

void AUTDGetLatestFirmware(char *latest);

[[nodiscard]] DatagramPtr AUTDSynchronize();

[[nodiscard]] DatagramPtr AUTDClear();

[[nodiscard]] DatagramPtr AUTDUpdateFlags();

[[nodiscard]] DatagramSpecialPtr AUTDStop();

[[nodiscard]] DatagramPtr AUTDConfigureModDelay();

[[nodiscard]] DatagramPtr AUTDConfigureAmpFilter();

[[nodiscard]] DatagramPtr AUTDConfigurePhaseFilter();

[[nodiscard]] DatagramPtr AUTDCreateSilencer(uint16_t step);

[[nodiscard]] DatagramPtr AUTDCreateAmplitudes(double amp);

[[nodiscard]]
int32_t AUTDSend(ControllerPtr cnt,
                 TransMode mode,
                 DatagramPtr d1,
                 DatagramPtr d2,
                 int64_t timeout_ns,
                 char *err);

[[nodiscard]]
int32_t AUTDSendSpecial(ControllerPtr cnt,
                        TransMode mode,
                        DatagramSpecialPtr special,
                        int64_t timeout_ns,
                        char *err);

[[nodiscard]] GroupKVMapPtr AUTDGroupCreateKVMap();

[[nodiscard]]
GroupKVMapPtr AUTDGroupKVMapSet(GroupKVMapPtr map,
                                int32_t key,
                                DatagramPtr d1,
                                DatagramPtr d2,
                                TransMode mode,
                                int64_t timeout_ns,
                                char *err);

[[nodiscard]]
GroupKVMapPtr AUTDGroupKVMapSetSpecial(GroupKVMapPtr map,
                                       int32_t key,
                                       DatagramSpecialPtr special,
                                       TransMode mode,
                                       int64_t timeout_ns,
                                       char *err);

[[nodiscard]]
int32_t AUTDGroup(ControllerPtr cnt,
                  const int32_t *map,
                  GroupKVMapPtr kv_map,
                  char *err);

int32_t AUTDSoftwareSTM(ControllerPtr cnt,
                        void* callback,
                        void* context,
                        TimerStrategy timer_strategy,
                        uint64_t interval_ns,
                        char *err);

[[nodiscard]] DatagramPtr AUTDGainIntoDatagram(GainPtr gain);

[[nodiscard]]
int32_t AUTDGainCalc(GainPtr gain,
                     GeometryPtr geometry,
                     Drive *const *drives,
                     char *err);

[[nodiscard]]
GainPtr AUTDGainBessel(double x,
                       double y,
                       double z,
                       double nx,
                       double ny,
                       double nz,
                       double theta_z);

[[nodiscard]] GainPtr AUTDGainBesselWithAmp(GainPtr bessel, double amp);

[[nodiscard]] GainPtr AUTDGainCustom();

[[nodiscard]]
GainPtr AUTDGainCustomSet(GainPtr custom,
                          uint32_t dev_idx,
                          const Drive *ptr,
                          uint32_t len);

[[nodiscard]] GainPtr AUTDGainFocus(double x, double y, double z);

[[nodiscard]] GainPtr AUTDGainFocusWithAmp(GainPtr focus, double amp);

[[nodiscard]]
GroupGainMapPtr AUTDGainGroupCreateMap(const uint32_t *device_indices_ptr,
                                       uint32_t num_devices);

[[nodiscard]]
GroupGainMapPtr AUTDGainGroupMapSet(GroupGainMapPtr map,
                                    uint32_t dev_idx,
                                    const int32_t *map_data);

[[nodiscard]]
GainPtr AUTDGainGroup(GroupGainMapPtr map,
                      const int32_t *keys_ptr,
                      const GainPtr *values_ptr,
                      uint32_t kv_len);

[[nodiscard]] GainPtr AUTDGainNull();

[[nodiscard]] GainPtr AUTDGainPlane(double nx, double ny, double nz);

[[nodiscard]] GainPtr AUTDGainPlaneWithAmp(GainPtr plane, double amp);

[[nodiscard]] GainPtr AUTDGainTransducerTest();

[[nodiscard]]
GainPtr AUTDGainTransducerTestSet(GainPtr trans_test,
                                  uint32_t dev_idx,
                                  uint32_t tr_idx,
                                  double phase,
                                  double amp);

[[nodiscard]] GainPtr AUTDGainUniform(double amp);

[[nodiscard]] GainPtr AUTDGainUniformWithPhase(GainPtr uniform, double phase);

[[nodiscard]] GeometryPtr AUTDGetGeometry(ControllerPtr cnt);

[[nodiscard]] uint32_t AUTDGeometryNumDevices(GeometryPtr geo);

[[nodiscard]] DevicePtr AUTDGetDevice(GeometryPtr geo, uint32_t dev_idx);

[[nodiscard]] uint32_t AUTDDeviceNumTransducers(DevicePtr dev);

[[nodiscard]] double AUTDDeviceGetSoundSpeed(DevicePtr dev);

void AUTDDeviceSetSoundSpeed(DevicePtr dev, double value);

void AUTDDeviceSetSoundSpeedFromTemp(DevicePtr dev, double temp, double k, double r, double m);

[[nodiscard]] double AUTDDeviceGetAttenuation(DevicePtr dev);

void AUTDDeviceSetAttenuation(DevicePtr dev, double value);

void AUTDDeviceCenter(DevicePtr dev, double *center);

void AUTDDeviceTranslate(DevicePtr dev, double x, double y, double z);

void AUTDDeviceRotate(DevicePtr dev, double w, double i, double j, double k);

void AUTDDeviceAffine(DevicePtr dev,
                      double x,
                      double y,
                      double z,
                      double w,
                      double i,
                      double j,
                      double k);

void AUTDDeviceSetReadsFPGAInfo(DevicePtr dev, bool value);

void AUTDDeviceSetForceFan(DevicePtr dev, bool value);

[[nodiscard]] TransducerPtr AUTDGetTransducer(DevicePtr dev, uint32_t tr_idx);

void AUTDTransPosition(TransducerPtr tr, double *pos);

void AUTDTransRotation(TransducerPtr tr, double *rot);

void AUTDTransXDirection(TransducerPtr tr, double *dir);

void AUTDTransYDirection(TransducerPtr tr, double *dir);

void AUTDTransZDirection(TransducerPtr tr, double *dir);

[[nodiscard]] double AUTDGetTransFrequency(TransducerPtr tr);

[[nodiscard]] bool AUTDSetTransFrequency(TransducerPtr tr, double value, char *err);

[[nodiscard]] uint16_t AUTDGetTransCycle(TransducerPtr tr);

[[nodiscard]] bool AUTDSetTransCycle(TransducerPtr tr, uint16_t value, char *err);

[[nodiscard]] double AUTDGetWavelength(TransducerPtr tr, double sound_speed);

[[nodiscard]] uint16_t AUTDGetTransModDelay(TransducerPtr tr);

void AUTDSetTransModDelay(TransducerPtr tr, uint16_t delay);

[[nodiscard]] double AUTDGetTransAmpFilter(TransducerPtr tr);

void AUTDSetTransAmpFilter(TransducerPtr tr, double value);

[[nodiscard]] double AUTDGetTransPhaseFilter(TransducerPtr tr);

void AUTDSetTransPhaseFilter(TransducerPtr tr, double value);

[[nodiscard]] LinkPtr AUTDLinkBundle(LinkPtr main, LinkPtr sub);

[[nodiscard]] LinkPtr AUTDLinkDebug();

[[nodiscard]] LinkPtr AUTDLinkDebugWithLogLevel(LinkPtr debug, Level level);

[[nodiscard]] LinkPtr AUTDLinkDebugWithLogFunc(LinkPtr debug, void* out_func, void* flush_func);

[[nodiscard]] LinkPtr AUTDLinkDebugWithTimeout(LinkPtr debug, uint64_t timeout_ns);

[[nodiscard]] LinkPtr AUTDLinkLog(LinkPtr link);

[[nodiscard]] LinkPtr AUTDLinkLogWithLogLevel(LinkPtr log, Level level);

[[nodiscard]] LinkPtr AUTDLinkLogWithLogFunc(LinkPtr log, void* out_func, void* flush_func);

[[nodiscard]] uint32_t AUTDModulationSamplingFrequencyDivision(ModulationPtr m);

[[nodiscard]] DatagramPtr AUTDModulationIntoDatagram(ModulationPtr m);

[[nodiscard]] int32_t AUTDModulationSize(ModulationPtr m, char *err);

[[nodiscard]] int32_t AUTDModulationCalc(ModulationPtr m, double *buffer, char *err);

[[nodiscard]]
ModulationPtr AUTDModulationCustom(uint32_t freq_div,
                                   const double *ptr,
                                   uint64_t len);

[[nodiscard]]
ModulationPtr AUTDModulationWithLowPass(ModulationPtr m,
                                        uint32_t n_taps,
                                        double cutoff);

[[nodiscard]]
ModulationPtr AUTDModulationWithHighPass(ModulationPtr m,
                                         uint32_t n_taps,
                                         double cutoff);

[[nodiscard]]
ModulationPtr AUTDModulationWithBandPass(ModulationPtr m,
                                         uint32_t n_taps,
                                         double f_low,
                                         double f_high);

[[nodiscard]]
ModulationPtr AUTDModulationWithBandStop(ModulationPtr m,
                                         uint32_t n_taps,
                                         double f_low,
                                         double f_high);

[[nodiscard]] ModulationPtr AUTDModulationFourier();

[[nodiscard]]
ModulationPtr AUTDModulationFourierAddComponent(ModulationPtr fourier,
                                                ModulationPtr m);

[[nodiscard]] ModulationPtr AUTDModulationSine(uint32_t freq);

[[nodiscard]]
ModulationPtr AUTDModulationSineWithSamplingFrequencyDivision(ModulationPtr m,
                                                              uint32_t div);

[[nodiscard]] ModulationPtr AUTDModulationSineWithAmp(ModulationPtr m, double amp);

[[nodiscard]] ModulationPtr AUTDModulationSineWithPhase(ModulationPtr m, double phase);

[[nodiscard]] ModulationPtr AUTDModulationSineWithOffset(ModulationPtr m, double offset);

[[nodiscard]] ModulationPtr AUTDModulationSineLegacy(double freq);

[[nodiscard]] ModulationPtr AUTDModulationSineLegacyWithAmp(ModulationPtr m, double amp);

[[nodiscard]] ModulationPtr AUTDModulationSineLegacyWithOffset(ModulationPtr m, double offset);

[[nodiscard]]
ModulationPtr AUTDModulationSineLegacyWithSamplingFrequencyDivision(ModulationPtr m,
                                                                    uint32_t div);

[[nodiscard]] ModulationPtr AUTDModulationSquare(uint32_t freq);

[[nodiscard]] ModulationPtr AUTDModulationSquareWithLow(ModulationPtr m, double low);

[[nodiscard]] ModulationPtr AUTDModulationSquareWithHigh(ModulationPtr m, double high);

[[nodiscard]] ModulationPtr AUTDModulationSquareWithDuty(ModulationPtr m, double duty);

[[nodiscard]]
ModulationPtr AUTDModulationSquareWithSamplingFrequencyDivision(ModulationPtr m,
                                                                uint32_t div);

[[nodiscard]] ModulationPtr AUTDModulationStatic();

[[nodiscard]] ModulationPtr AUTDModulationStaticWithAmp(ModulationPtr m, double amp);

[[nodiscard]]
ModulationPtr AUTDModulationStaticWithSamplingFrequencyDivision(ModulationPtr m,
                                                                uint32_t div);

[[nodiscard]] STMPropsPtr AUTDSTMProps(double freq);

[[nodiscard]] STMPropsPtr AUTDSTMPropsWithSamplingFreq(double freq);

[[nodiscard]] STMPropsPtr AUTDSTMPropsWithSamplingFreqDiv(uint32_t div);

[[nodiscard]] STMPropsPtr AUTDSTMPropsWithSamplingPeriod(uint64_t period_ns);

[[nodiscard]] STMPropsPtr AUTDSTMPropsWithStartIdx(STMPropsPtr props, int32_t idx);

[[nodiscard]] STMPropsPtr AUTDSTMPropsWithFinishIdx(STMPropsPtr props, int32_t idx);

[[nodiscard]] double AUTDSTMPropsFrequency(STMPropsPtr props, uint64_t size);

[[nodiscard]] double AUTDSTMPropsSamplingFrequency(STMPropsPtr props, uint64_t size);

[[nodiscard]] uint32_t AUTDSTMPropsSamplingFrequencyDivision(STMPropsPtr props, uint64_t size);

[[nodiscard]] uint64_t AUTDSTMPropsSamplingPeriod(STMPropsPtr props, uint64_t size);

[[nodiscard]] int32_t AUTDSTMPropsStartIdx(STMPropsPtr props);

[[nodiscard]] int32_t AUTDSTMPropsFinishIdx(STMPropsPtr props);

[[nodiscard]]
DatagramPtr AUTDFocusSTM(STMPropsPtr props,
                         const double *points,
                         const uint8_t *shift,
                         uint64_t size);

[[nodiscard]]
DatagramPtr AUTDGainSTM(STMPropsPtr props,
                        const GainPtr *gains,
                        uint32_t size,
                        GainSTMMode mode);

[[nodiscard]] DatagramPtr AUTDGainSTMAddGain(DatagramPtr stm, GainPtr gain);

} // extern "C"

} // namespace autd3::internal::native_methods
