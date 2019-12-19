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
let periodicWave =
  AudioContext.createPeriodicWave(
    audioCtx,
    real,
    imag,
    {"disableNormalization": false},
  );
oscillator |> OscillatorNode.setPeriodicWave(periodicWave);
oscillator->OscillatorNode.connect(biquadFilter);

biquadFilter->BiquadFilterNode.setType(Lowpass);
biquadFilter->BiquadFilterNode.connect(gain);

gain->GainNode.connect(AudioContext.getDestination(audioCtx));

oscillator |> OscillatorNode.start();
oscillator |> OscillatorNode.stopAt(4.5);

OscillatorNode.frequency(oscillator)
|> AudioParam.setValueCurveAtTime(
     ~curve=[|240.0, 370.0, 240.0|],
     ~startTime=2.0,
     ~duration=2.5,
   );

BiquadFilterNode.frequency(biquadFilter)->AudioParam.setValue(170.0);
BiquadFilterNode.frequency(biquadFilter)
|> AudioParam.setTargetAtTime(~target=50.0, ~startTime=2.0, ~timeConstant=1.0);
