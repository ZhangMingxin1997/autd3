#pragma once

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <cstdint>

namespace autd3::internal::native_methods {

struct ControllerBuilderPtr {
  void* _0;
};

struct ResultFirmwareInfoList {
  FirmwareInfoListPtr result;
  uint32_t err_len;
  void* err;
};

struct ResultGroupKVMap {
  GroupKVMapPtr result;
  uint32_t err_len;
  void* err;
};

struct LinkAuditBuilderPtr {
  void* _0;
};

struct ResultCache {
  CachePtr result;
  uint32_t err_len;
  void* err;
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
ResultController AUTDControllerOpenWith(ControllerBuilderPtr builder,
                                        LinkBuilderPtr link_builder);

[[nodiscard]] ResultI32 AUTDControllerClose(ControllerPtr cnt);

void AUTDControllerDelete(ControllerPtr cnt);

[[nodiscard]] ResultI32 AUTDControllerFPGAInfo(ControllerPtr cnt, uint8_t *out);

[[nodiscard]] ResultFirmwareInfoList AUTDControllerFirmwareInfoListPointer(ControllerPtr cnt);

void AUTDControllerFirmwareInfoGet(FirmwareInfoListPtr p_info_list, uint32_t idx, char *info);

void AUTDControllerFirmwareInfoListPointerDelete(FirmwareInfoListPtr p_info_list);

void AUTDFirmwareLatest(char *latest);

[[nodiscard]] DatagramPtr AUTDDatagramSynchronize();

[[nodiscard]] DatagramPtr AUTDDatagramClear();

[[nodiscard]] DatagramPtr AUTDDatagramUpdateFlags();

[[nodiscard]] DatagramSpecialPtr AUTDDatagramStop();

[[nodiscard]] DatagramPtr AUTDDatagramConfigureModDelay();

[[nodiscard]] ResultDatagram AUTDDatagramSilencer(uint16_t step_intensity, uint16_t step_phase);

[[nodiscard]]
ResultI32 AUTDControllerSend(ControllerPtr cnt,
                             DatagramPtr d1,
                             DatagramPtr d2,
                             int64_t timeout_ns);

[[nodiscard]]
ResultI32 AUTDControllerSendSpecial(ControllerPtr cnt,
                                    DatagramSpecialPtr special,
                                    int64_t timeout_ns);

[[nodiscard]] GroupKVMapPtr AUTDControllerGroupCreateKVMap();

[[nodiscard]]
ResultGroupKVMap AUTDControllerGroupKVMapSet(GroupKVMapPtr map,
                                             int32_t key,
                                             DatagramPtr d1,
                                             DatagramPtr d2,
                                             int64_t timeout_ns);

[[nodiscard]]
ResultGroupKVMap AUTDControllerGroupKVMapSetSpecial(GroupKVMapPtr map,
                                                    int32_t key,
                                                    DatagramSpecialPtr special,
                                                    int64_t timeout_ns);

[[nodiscard]]
ResultI32 AUTDControllerGroup(ControllerPtr cnt,
                              const int32_t *map,
                              GroupKVMapPtr kv_map);

[[nodiscard]] DatagramPtr AUTDGainIntoDatagram(GainPtr gain);

[[nodiscard]] ResultGainCalcDrivesMap AUTDGainCalc(GainPtr gain, GeometryPtr geometry);

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

[[nodiscard]] GainPtr AUTDGainBesselWithIntensity(GainPtr bessel, uint8_t intensity);

[[nodiscard]] GainPtr AUTDGainCustom();

[[nodiscard]]
GainPtr AUTDGainCustomSet(GainPtr custom,
                          uint32_t dev_idx,
                          const Drive *ptr,
                          uint32_t len);

[[nodiscard]] GainPtr AUTDGainFocus(double x, double y, double z);

[[nodiscard]] GainPtr AUTDGainFocusWithIntensity(GainPtr focus, uint8_t intensity);

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

[[nodiscard]] GainPtr AUTDGainPlaneWithIntensity(GainPtr plane, uint8_t intensity);

[[nodiscard]] GainPtr AUTDGainTransducerTest();

[[nodiscard]]
GainPtr AUTDGainTransducerTestSet(GainPtr trans_test,
                                  TransducerPtr tr,
                                  double phase,
                                  uint8_t intensity);

[[nodiscard]] GainPtr AUTDGainUniform(uint8_t intensity);

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

[[nodiscard]] uint16_t AUTDLinkAuditFpgaSilencerStepIntensity(LinkPtr audit, uint32_t idx);

[[nodiscard]] uint16_t AUTDLinkAuditFpgaSilencerStepPhase(LinkPtr audit, uint32_t idx);

void AUTDLinkAuditFpgaModDelays(LinkPtr audit, uint32_t idx, uint16_t *delay);

[[nodiscard]] uint32_t AUTDLinkAuditFpgaStmFrequencyDivision(LinkPtr audit, uint32_t idx);

[[nodiscard]] uint32_t AUTDLinkAuditFpgaStmCycle(LinkPtr audit, uint32_t idx);

[[nodiscard]] uint32_t AUTDLinkAuditFpgaSoundSpeed(LinkPtr audit, uint32_t idx);

[[nodiscard]] int32_t AUTDLinkAuditFpgaStmStartIdx(LinkPtr audit, uint32_t idx);

[[nodiscard]] int32_t AUTDLinkAuditFpgaStmFinishIdx(LinkPtr audit, uint32_t idx);

[[nodiscard]] uint32_t AUTDLinkAuditFpgaModulationFrequencyDivision(LinkPtr audit, uint32_t idx);

[[nodiscard]] uint32_t AUTDLinkAuditFpgaModulationCycle(LinkPtr audit, uint32_t idx);

void AUTDLinkAuditFpgaModulation(LinkPtr audit, uint32_t idx, uint8_t *data);

void AUTDLinkAuditFpgaIntensitiesAndPhases(LinkPtr audit,
                                           uint32_t idx,
                                           uint32_t stm_idx,
                                           uint8_t *intensities,
                                           uint8_t *phases);

[[nodiscard]] LinkBuilderPtr AUTDLinkNop();

[[nodiscard]] SamplingConfiguration AUTDModulationSamplingConfig(ModulationPtr m);

[[nodiscard]] DatagramPtr AUTDModulationIntoDatagram(ModulationPtr m);

[[nodiscard]] ResultI32 AUTDModulationSize(ModulationPtr m);

[[nodiscard]] ResultCache AUTDModulationWithCache(ModulationPtr m);

uint32_t AUTDModulationCacheGetBufferLen(CachePtr m);

void AUTDModulationCacheGetBuffer(CachePtr m, uint8_t *buf);

[[nodiscard]] ModulationPtr AUTDModulationCacheIntoModulation(CachePtr m);

void AUTDModulationCacheDelete(CachePtr m);

[[nodiscard]]
ModulationPtr AUTDModulationCustom(SamplingConfiguration config,
                                   const uint8_t *ptr,
                                   uint64_t len);

[[nodiscard]] ModulationPtr AUTDModulationFourier(ModulationPtr m);

[[nodiscard]]
ModulationPtr AUTDModulationFourierAddComponent(ModulationPtr fourier,
                                                ModulationPtr m);

[[nodiscard]] ModulationPtr AUTDModulationWithRadiationPressure(ModulationPtr m);

[[nodiscard]] ModulationPtr AUTDModulationSine(uint32_t freq);

[[nodiscard]]
ModulationPtr AUTDModulationSineWithSamplingConfig(ModulationPtr m,
                                                   SamplingConfiguration config);

[[nodiscard]] ModulationPtr AUTDModulationSineWithAmp(ModulationPtr m, double amp);

[[nodiscard]] ModulationPtr AUTDModulationSineWithPhase(ModulationPtr m, double phase);

[[nodiscard]] ModulationPtr AUTDModulationSineWithOffset(ModulationPtr m, double offset);

[[nodiscard]] ModulationPtr AUTDModulationSquare(uint32_t freq);

[[nodiscard]] ModulationPtr AUTDModulationSquareWithLow(ModulationPtr m, uint8_t low);

[[nodiscard]] ModulationPtr AUTDModulationSquareWithHigh(ModulationPtr m, uint8_t high);

[[nodiscard]] ModulationPtr AUTDModulationSquareWithDuty(ModulationPtr m, double duty);

[[nodiscard]]
ModulationPtr AUTDModulationSquareWithSamplingConfig(ModulationPtr m,
                                                     SamplingConfiguration config);

[[nodiscard]] ModulationPtr AUTDModulationStatic();

[[nodiscard]] ModulationPtr AUTDModulationStaticWithAmp(ModulationPtr m, uint8_t intensity);

[[nodiscard]] ModulationPtr AUTDModulationWithTransform(ModulationPtr m, void* f, void* context);

[[nodiscard]] STMPropsPtr AUTDSTMPropsNew(double freq);

[[nodiscard]] STMPropsPtr AUTDSTMPropsNewWithPeriod(uint64_t p);

[[nodiscard]] STMPropsPtr AUTDSTMPropsNewWithSamplingConfig(SamplingConfiguration config);

[[nodiscard]] STMPropsPtr AUTDSTMPropsWithStartIdx(STMPropsPtr props, int32_t idx);

[[nodiscard]] STMPropsPtr AUTDSTMPropsWithFinishIdx(STMPropsPtr props, int32_t idx);

[[nodiscard]] double AUTDSTMPropsFrequency(STMPropsPtr props, uint64_t size);

[[nodiscard]] uint64_t AUTDSTMPropsPeriod(STMPropsPtr props, uint64_t size);

[[nodiscard]] ResultSamplingConfig AUTDSTMPropsSamplingConfig(STMPropsPtr props, uint64_t size);

[[nodiscard]] int32_t AUTDSTMPropsStartIdx(STMPropsPtr props);

[[nodiscard]] int32_t AUTDSTMPropsFinishIdx(STMPropsPtr props);

[[nodiscard]]
ResultDatagram AUTDSTMFocus(STMPropsPtr props,
                            const double *points,
                            const uint8_t *intensities,
                            uint64_t size);

[[nodiscard]]
ResultDatagram AUTDSTMGain(STMPropsPtr props,
                           const GainPtr *gains,
                           uint32_t size,
                           GainSTMMode mode);

[[nodiscard]] ResultDatagram AUTDSTMGainAddGain(DatagramPtr stm, GainPtr gain);

} // extern "C"

} // namespace autd3::internal::native_methods
