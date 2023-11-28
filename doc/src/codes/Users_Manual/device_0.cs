var dev = autd.Geometry[0];
var idx = dev.Idx;
dev.Enable = false;
dev.SoundSpeed = 340e3;
dev.SetSoundSpeedFromTemp(15);
dev.Attenuation = 0;
var t = new Vector3d(1, 0, 0);
var r = new Quaterniond(0, 0, 0, 1);
dev.Translate(t);
dev.Rotate(r);
dev.Affine(t, r);
dev.ForceFan = true;
dev.ReadsFPGAInfo = true;