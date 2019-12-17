let audioCtx = AudioContext.createAudioContext();
let oscillator = AudioContext.createOscillator(audioCtx);
let biquadFilter = AudioContext.createBiquadFilter(audioCtx);
BiquadFilterNode.setType(biquadFilter, Lowpass);
BiquadFilterNode.frequency(biquadFilter)->AudioParam.setValue(170.0);
OscillatorNode.connect(oscillator, biquadFilter);
let gain = AudioContext.createGain(audioCtx);
BiquadFilterNode.connect(biquadFilter, gain);

let real = Js_typed_array.Float32Array.fromLength(5);
let imag = Js_typed_array.Float32Array.fromLength(5);
Js_typed_array2.Float32Array.unsafe_set(real, 0, 0.0);
Js_typed_array2.Float32Array.unsafe_set(real, 1, 1.0);
Js_typed_array2.Float32Array.unsafe_set(real, 2, 1.0);
Js_typed_array2.Float32Array.unsafe_set(real, 3, 0.5);
Js_typed_array2.Float32Array.unsafe_set(real, 4, 0.2);
Js_typed_array2.Float32Array.unsafe_set(imag, 0, 0.0);
Js_typed_array2.Float32Array.unsafe_set(imag, 1, 0.0);
Js_typed_array2.Float32Array.unsafe_set(imag, 2, 0.0);
Js_typed_array2.Float32Array.unsafe_set(imag, 3, 0.2);
Js_typed_array2.Float32Array.unsafe_set(imag, 4, 0.4);
let periodicWave =
  AudioContext.createPeriodicWave(
    audioCtx,
    real,
    imag,
    {"disableNormalization": true},
  );
OscillatorNode.setPeriodicWave(oscillator, periodicWave);

GainNode.connect(gain, AudioContext.getDestination(audioCtx));
OscillatorNode.start(oscillator);

Js.Global.setTimeout(
  () => {
    BiquadFilterNode.frequency(biquadFilter)->AudioParam.setValue(320.0);
    let timestamp = audioCtx |> AudioContext.getOutputTimestamp();
    Js.log(timestamp.contextTime);
    Js.log(OscillatorNode.frequency(oscillator) |> AudioParam.defaultValue);
    OscillatorNode.frequency(oscillator) |> AudioParam.setValue(_, 240.0);
    oscillator |> OscillatorNode.stopAt(timestamp.contextTime +. 2.0);
  },
  2500,
);
