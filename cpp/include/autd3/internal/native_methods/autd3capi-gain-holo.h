#pragma once

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <cstdint>

namespace autd3::internal::native_methods {

extern "C" {

[[nodiscard]] double AUTDGainHoloSPLToPascal(double value);

[[nodiscard]] double AUTDGainHoloPascalToSPL(double value);

[[nodiscard]] EmissionConstraintPtr AUTDGainHoloConstraintDotCare();

[[nodiscard]] EmissionConstraintPtr AUTDGainHoloConstraintNormalize();

[[nodiscard]] EmissionConstraintPtr AUTDGainHoloConstraintUniform(uint8_t intensity);

[[nodiscard]] EmissionConstraintPtr AUTDGainHoloConstraintClamp(uint8_t min_v, uint8_t max_v);

[[nodiscard]] GainPtr AUTDGainHoloGreedy(const double *points, const double *amps, uint64_t size);

[[nodiscard]]
GainPtr AUTDGainHoloGreedyWithConstraint(GainPtr holo,
                                         EmissionConstraintPtr constraint);

[[nodiscard]] GainPtr AUTDGainHoloGreedyWithPhaseDiv(GainPtr holo, uint32_t div);

[[nodiscard]]
GainPtr AUTDGainHoloGS(BackendPtr backend,
                       const double *points,
                       const double *amps,
                       uint64_t size);

[[nodiscard]] GainPtr AUTDGainHoloGSWithConstraint(GainPtr holo, EmissionConstraintPtr constraint);

[[nodiscard]] GainPtr AUTDGainHoloGSWithRepeat(GainPtr holo, uint32_t repeat);

[[nodiscard]]
GainPtr AUTDGainHoloGSPAT(BackendPtr backend,
                          const double *points,
                          const double *amps,
                          uint64_t size);

[[nodiscard]]
GainPtr AUTDGainHoloGSPATWithConstraint(GainPtr holo,
                                        EmissionConstraintPtr constraint);

[[nodiscard]] GainPtr AUTDGainHoloGSPATWithRepeat(GainPtr holo, uint32_t repeat);

[[nodiscard]]
GainPtr AUTDGainHoloLM(BackendPtr backend,
                       const double *points,
                       const double *amps,
                       uint64_t size);

[[nodiscard]] GainPtr AUTDGainHoloLMWithConstraint(GainPtr holo, EmissionConstraintPtr constraint);

[[nodiscard]] GainPtr AUTDGainHoloLMWithEps1(GainPtr holo, double eps);

[[nodiscard]] GainPtr AUTDGainHoloLMWithEps2(GainPtr holo, double eps);

[[nodiscard]] GainPtr AUTDGainHoloLMWithTau(GainPtr holo, double tau);

[[nodiscard]] GainPtr AUTDGainHoloLMWithKMax(GainPtr holo, uint32_t k_max);

[[nodiscard]]
GainPtr AUTDGainHoloLMWithInitial(GainPtr holo,
                                  const double *initial_ptr,
                                  uint64_t len);

[[nodiscard]]
GainPtr AUTDGainHoloNaive(BackendPtr backend,
                          const double *points,
                          const double *amps,
                          uint64_t size);

[[nodiscard]]
GainPtr AUTDGainHoloNaiveWithConstraint(GainPtr holo,
                                        EmissionConstraintPtr constraint);

[[nodiscard]] BackendPtr AUTDNalgebraBackend();

void AUTDDeleteNalgebraBackend(BackendPtr backend);

[[nodiscard]]
GainPtr AUTDGainHoloSDP(BackendPtr backend,
                        const double *points,
                        const double *amps,
                        uint64_t size);

[[nodiscard]] GainPtr AUTDGainHoloSDPWithConstraint(GainPtr holo, EmissionConstraintPtr constraint);

[[nodiscard]] GainPtr AUTDGainHoloSDPWithAlpha(GainPtr holo, double alpha);

[[nodiscard]] GainPtr AUTDGainHoloSDPWithLambda(GainPtr holo, double lambda);

[[nodiscard]] GainPtr AUTDGainHoloSDPWithRepeat(GainPtr holo, uint32_t repeat);

} // extern "C"

} // namespace autd3::internal::native_methods
