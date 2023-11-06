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

struct LinkAuditBuilderPtr {
  void* _0;
};

struct ModulationCachePtr {
  void* _0;
};

extern "C" {

[[nodiscard]] ControllerBuilderPtr AUTDControllerBuilder();

ControllerBuilderPtr AUTDControllerBuilderAddDevice(ControllerBuilderPtr builder,
                                                    double x,
                                                    double y,
                                                    double z,
                                                    double rz1,
                                                    double ry,
                                                    double rz2);

ControllerBuilderPtr AUTDControllerBuilderAddDeviceQuaternion(ControllerBuilderPtr builder,
                                                              double x,
                                                              double y,
                                                              double z,
                                                              double qw,
                                                              double qx,
                                                              double qy,
                                                              double qz);

[[nodiscard]]
ControllerPtr AUTDControllerOpenWith(ControllerBuilderPtr builder,
                                     LinkBuilderPtr link_builder,
                                     char *err);

[[nodiscard]] bool AUTDControllerClose(ControllerPtr cnt, char *err);

void AUTDControllerDelete(ControllerPtr cnt);

[[nodiscard]] bool AUTDControllerFPGAInfo(ControllerPtr cnt, uint8_t *out, char *err);

[[nodiscard]]
FirmwareInfoListPtr AUTDControllerFirmwareInfoListPointer(ControllerPtr cnt,
                                                          char *err);

void AUTDControllerFirmwareInfoGet(FirmwareInfoListPtr p_info_list, uint32_t idx, char *info);

void AUTDControllerFirmwareInfoListPointerDelete(FirmwareInfoListPtr p_info_list);

void AUTDFirmwareLatest(char *latest);

[[nodiscard]] DatagramPtr AUTDDatagramSynchronize();

[[nodiscard]] DatagramPtr AUTDDatagramClear();

[[nodiscard]] DatagramPtr AUTDDatagramUpdateFlags();

[[nodiscard]] DatagramSpecialPtr AUTDDatagramStop();

[[nodiscard]] DatagramPtr AUTDDatagramConfigureModDelay();

[[nodiscard]] DatagramPtr AUTDDatagramConfigureAmpFilter();

[[nodiscard]] DatagramPtr AUTDDatagramConfigurePhaseFilter();

[[nodiscard]] DatagramPtr AUTDDatagramSilencer(uint16_t step);

[[nodiscard]]
int32_t AUTDControllerSend(ControllerPtr cnt,
                           DatagramPtr d1,
                           DatagramPtr d2,
                           int64_t timeout_ns,
                           char *err);

[[nodiscard]]
int32_t AUTDControllerSendSpecial(ControllerPtr cnt,
                                  DatagramSpecialPtr special,
                                  int64_t timeout_ns,
                                  char *err);

[[nodiscard]] GroupKVMapPtr AUTDControllerGroupCreateKVMap();

[[nodiscard]]
GroupKVMapPtr AUTDControllerGroupKVMapSet(GroupKVMapPtr map,
                                          int32_t key,
                                          DatagramPtr d1,
                                          DatagramPtr d2,
                                          int64_t timeout_ns,
                                          char *err);

[[nodiscard]]
GroupKVMapPtr AUTDControllerGroupKVMapSetSpecial(GroupKVMapPtr map,
                                                 int32_t key,
                                                 DatagramSpecialPtr special,
                                                 int64_t timeout_ns,
                                                 char *err);

[[nodiscard]]
int32_t AUTDControllerGroup(ControllerPtr cnt,
                            const int32_t *map,
                            GroupKVMapPtr kv_map,
                            char *err);

[[nodiscard]] DatagramPtr AUTDGainIntoDatagram(GainPtr gain);

[[nodiscard]] GainCalcDrivesMapPtr AUTDGainCalc(GainPtr gain, GeometryPtr geometry, char *err);

void AUTDGainCalcGetResult(GainCalcDrivesMapPtr src, Drive *dst, uint32_t idx);

void AUTDGainCalcFreeResult(GainCalcDrivesMapPtr src);

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

[[nodiscard]] GeometryPtr AUTDGeometry(ControllerPtr cnt);

[[nodiscard]] uint32_t AUTDGeometryNumDevices(GeometryPtr geo);

[[nodiscard]] DevicePtr AUTDDevice(GeometryPtr geo, uint32_t dev_idx);

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

void AUTDDeviceEnableSet(DevicePtr dev, bool value);

[[nodiscard]] bool AUTDDeviceEnableGet(DevicePtr dev);

[[nodiscard]] TransducerPtr AUTDTransducer(DevicePtr dev, uint32_t tr_idx);

void AUTDTransducerPosition(TransducerPtr tr, double *pos);

void AUTDTransducerRotation(TransducerPtr tr, double *rot);

void AUTDTransducerDirectionX(TransducerPtr tr, double *dir);

void AUTDTransducerDirectionY(TransducerPtr tr, double *dir);

void AUTDTransducerDirectionZ(TransducerPtr tr, double *dir);

[[nodiscard]] double AUTDTransducerWavelength(TransducerPtr tr, double sound_speed);

[[nodiscard]] uint16_t AUTDTransducerModDelayGet(TransducerPtr tr);

void AUTDTransducerModDelaySet(TransducerPtr tr, uint16_t delay);

[[nodiscard]] double AUTDTransducerAmpFilterGet(TransducerPtr tr);

void AUTDTransducerAmpFilterSet(TransducerPtr tr, double value);

[[nodiscard]] double AUTDTransducerPhaseFilterGet(TransducerPtr tr);

void AUTDTransducerPhaseFilterSet(TransducerPtr tr, double value);

[[nodiscard]] LinkPtr AUTDLinkGet(ControllerPtr cnt);

[[nodiscard]] LinkAuditBuilderPtr AUTDLinkAudit();

[[nodiscard]]
LinkAuditBuilderPtr AUTDLinkAuditWithTimeout(LinkAuditBuilderPtr audit,
                                             uint64_t timeout_ns);

[[nodiscard]] LinkBuilderPtr AUTDLinkAuditIntoBuilder(LinkAuditBuilderPtr audit);

[[nodiscard]] bool AUTDLinkAuditIsOpen(LinkPtr audit);

[[nodiscard]] uint64_t AUTDLinkAuditTimeoutNs(LinkPtr audit);

[[nodiscard]] uint64_t AUTDLinkAuditLastTimeoutNs(LinkPtr audit);

void AUTDLinkAuditDown(LinkPtr audit);

void AUTDLinkAuditUp(LinkPtr audit);

void AUTDLinkAuditBreakDown(LinkPtr audit);

void AUTDLinkAuditRepair(LinkPtr audit);

void AUTDLinkAuditCpuUpdate(LinkPtr audit, uint32_t idx);

[[nodiscard]] uint32_t AUTDLinkAuditCpuIdx(LinkPtr audit, uint32_t idx);

[[nodiscard]] uint32_t AUTDLinkAuditCpuNumTransducers(LinkPtr audit, uint32_t idx);

[[nodiscard]] uint8_t AUTDLinkAuditCpuAck(LinkPtr audit, uint32_t idx);

[[nodiscard]] uint8_t AUTDLinkAuditCpuRxData(LinkPtr audit, uint32_t idx);

[[nodiscard]] uint8_t AUTDLinkAuditCpuFpgaFlags(LinkPtr audit, uint32_t idx);

void AUTDLinkAuditFpgaAssertThermalSensor(LinkPtr audit, uint32_t idx);

void AUTDLinkAuditFpgaDeassertThermalSensor(LinkPtr audit, uint32_t idx);

[[nodiscard]] bool AUTDLinkAuditFpgaIsForceFan(LinkPtr audit, uint32_t idx);

[[nodiscard]] bool AUTDLinkAuditFpgaIsStmMode(LinkPtr audit, uint32_t idx);

[[nodiscard]] bool AUTDLinkAuditFpgaIsStmGainMode(LinkPtr audit, uint32_t idx);

[[nodiscard]] uint16_t AUTDLinkAuditFpgaSilencerStep(LinkPtr audit, uint32_t idx);

void AUTDLinkAuditFpgaModDelays(LinkPtr audit, uint32_t idx, uint16_t *delay);

void AUTDLinkAuditFpgaDutyFilters(LinkPtr audit, uint32_t idx, int16_t *filters);

void AUTDLinkAuditFpgaPhaseFilters(LinkPtr audit, uint32_t idx, int16_t *filters);

[[nodiscard]] uint32_t AUTDLinkAuditFpgaStmFrequencyDivision(LinkPtr audit, uint32_t idx);

[[nodiscard]] uint32_t AUTDLinkAuditFpgaStmCycle(LinkPtr audit, uint32_t idx);

[[nodiscard]] uint32_t AUTDLinkAuditFpgaSoundSpeed(LinkPtr audit, uint32_t idx);

[[nodiscard]] int32_t AUTDLinkAuditFpgaStmStartIdx(LinkPtr audit, uint32_t idx);

[[nodiscard]] int32_t AUTDLinkAuditFpgaStmFinishIdx(LinkPtr audit, uint32_t idx);

[[nodiscard]] uint32_t AUTDLinkAuditFpgaModulationFrequencyDivision(LinkPtr audit, uint32_t idx);

[[nodiscard]] uint32_t AUTDLinkAuditFpgaModulationCycle(LinkPtr audit, uint32_t idx);

void AUTDLinkAuditFpgaModulation(LinkPtr audit, uint32_t idx, uint8_t *data);

void AUTDLinkAuditFpgaDutiesAndPhases(LinkPtr audit,
                                      uint32_t idx,
                                      uint32_t stm_idx,
                                      uint16_t *duties,
                                      uint16_t *phases);

[[nodiscard]] LinkBuilderPtr AUTDLinkNop();

[[nodiscard]] uint32_t AUTDModulationSamplingFrequencyDivision(ModulationPtr m);

[[nodiscard]] DatagramPtr AUTDModulationIntoDatagram(ModulationPtr m);

[[nodiscard]] int32_t AUTDModulationSize(ModulationPtr m, char *err);

[[nodiscard]] ModulationCachePtr AUTDModulationWithCache(ModulationPtr m, char *err);

[[nodiscard]] uint32_t AUTDModulationCacheGetBufferSize(ModulationCachePtr m);

void AUTDModulationCacheGetBuffer(ModulationCachePtr m, double *buf);

[[nodiscard]] ModulationPtr AUTDModulationCacheIntoModulation(ModulationCachePtr m);

void AUTDModulationCacheDelete(ModulationCachePtr m);

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

[[nodiscard]] ModulationPtr AUTDModulationFourier(ModulationPtr m);

[[nodiscard]]
ModulationPtr AUTDModulationFourierAddComponent(ModulationPtr fourier,
                                                ModulationPtr m);

[[nodiscard]] ModulationPtr AUTDModulationWithRadiationPressure(ModulationPtr m);

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

[[nodiscard]] ModulationPtr AUTDModulationWithTransform(ModulationPtr m, void* f, void* context);

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
DatagramPtr AUTDSTMFocus(STMPropsPtr props,
                         const double *points,
                         const uint8_t *shift,
                         uint64_t size);

[[nodiscard]]
DatagramPtr AUTDSTMGain(STMPropsPtr props,
                        const GainPtr *gains,
                        uint32_t size,
                        GainSTMMode mode);

[[nodiscard]] DatagramPtr AUTDSTMGainAddGain(DatagramPtr stm, GainPtr gain);

} // extern "C"

} // namespace autd3::internal::native_methods
