let audioCtx = AudioContext.createAudioContext();

let sineOscillator = Oscillator.make(Sine, audioCtx);
let biquadFilter = AudioContext.createBiquadFilter(audioCtx);
let sineGain = AudioContext.createGain(audioCtx);

sineOscillator |> OscillatorNode.connect(biquadFilter);

biquadFilter->BiquadFilterNode.setType(Lowpass);
biquadFilter |> BiquadFilterNode.connect(sineGain);

sineGain |> GainNode.connect(AudioContext.getDestination(audioCtx));

sineOscillator |> OscillatorNode.start();
sineOscillator |> OscillatorNode.stopAt(4.5);

OscillatorNode.frequency(sineOscillator)
|> AudioParam.setValueCurveAtTime(
     ~curve=[|240.0, 370.0, 240.0|],
     ~startTime=2.0,
     ~duration=2.5,
   );

BiquadFilterNode.frequency(biquadFilter)->AudioParam.setValue(470.0);
BiquadFilterNode.frequency(biquadFilter)
|> AudioParam.setTargetAtTime(~target=50.0, ~startTime=2.0, ~timeConstant=1.0);

let sawOscillator = Oscillator.make(SawTooth, audioCtx);
let sawGain = AudioContext.createGain(audioCtx);
sawOscillator |> OscillatorNode.connect(sawGain);
sawGain |> GainNode.connect(AudioContext.getDestination(audioCtx));
sawGain->GainNode.gain->AudioParam.setValue(0.005);
sawOscillator |> OscillatorNode.start();
sawOscillator |> OscillatorNode.stopAt(4.5);
