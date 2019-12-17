let audioCtx = AudioContext.createAudioContext();

let oscillator = AudioContext.createOscillator(audioCtx);
let biquadFilter = AudioContext.createBiquadFilter(audioCtx);
let gain = AudioContext.createGain(audioCtx);

let real = Js_typed_array.Float32Array.fromLength(3);
let imag = Js_typed_array.Float32Array.fromLength(3);
Js_typed_array2.Float32Array.unsafe_set(real, 0, 0.0);
Js_typed_array2.Float32Array.unsafe_set(real, 1, 1.0);
Js_typed_array2.Float32Array.unsafe_set(real, 2, 0.3);
Js_typed_array2.Float32Array.unsafe_set(imag, 0, 0.0);
Js_typed_array2.Float32Array.unsafe_set(imag, 1, 0.0);
Js_typed_array2.Float32Array.unsafe_set(imag, 2, 0.0);
AudioContext.createPeriodicWave(
  audioCtx,
  real,
  imag,
  {"disableNormalization": true},
)
->OscillatorNode.setPeriodicWave(oscillator);
OscillatorNode.connect(oscillator, biquadFilter);

BiquadFilterNode.setType(biquadFilter, Lowpass);
BiquadFilterNode.frequency(biquadFilter)->AudioParam.setValue(170.0);
BiquadFilterNode.connect(biquadFilter, gain);

AudioContext.getDestination(audioCtx) |> GainNode.connect(gain);

OscillatorNode.start(oscillator);

Js.Global.setTimeout(
  () => {
    BiquadFilterNode.frequency(biquadFilter)->AudioParam.setValue(320.0);
    let timestamp = audioCtx |> AudioContext.getOutputTimestamp();
    OscillatorNode.frequency(oscillator)->AudioParam.setValue(240.0);
    oscillator |> OscillatorNode.stopAt(timestamp.contextTime +. 2.0);
  },
  2500,
);
