/*
 * File: Fourier.cs
 * Project: Modulation
 * Created Date: 13/09/2023
 * Author: Shun Suzuki
 * -----
 * Last Modified: 13/09/2023
 * Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
 * -----
 * Copyright (c) 2023 Shun Suzuki. All rights reserved.
 * 
 */

using System.Collections.Generic;
using System.Linq;

namespace AUTD3Sharp.Modulation
{
    using Base = NativeMethods.Base;

    /// <summary>
    /// Multi-frequency sine wave modulation
    /// </summary>
    public sealed class Fourier : Internal.Modulation
    {
        private readonly List<Sine> _components;

        /// <summary>
        /// Constructor
        /// </summary>
        public Fourier()
        {
            _components = new List<Sine>();
        }

        public Fourier AddComponent(Sine sine)
        {
            _components.Add(sine);
            return this;
        }

        public Fourier AddComponentsFromIter(IEnumerable<Sine> iter)
        {
            return iter.Aggregate(this, (fourier, sine) => fourier.AddComponent(sine));
        }

        public static Fourier operator +(Fourier a, Sine b)
            => a.AddComponent(b);

        public override ModulationPtr ModulationPtr()
        {
            return _components.Aggregate(Base.AUTDModulationFourier(), (current, sine) => Base.AUTDModulationFourierAddComponent(current, sine.ModulationPtr()));
        }
    }
}