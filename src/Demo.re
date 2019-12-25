let audioCtx = AudioContext.createAudioContext();

let sineOscillator =
  Oscillator.make(Custom(Oscillator.sampleRandomWave()), audioCtx);
let sineGain = AudioContext.createGain(audioCtx);
sineOscillator |> OscillatorNode.connect(sineGain);

sineGain |> GainNode.connect(AudioContext.getDestination(audioCtx));
sineGain->GainNode.gain->AudioParam.setValue(epsilon_float);
sineOscillator |> OscillatorNode.start();

OscillatorNode.frequency(sineOscillator)
|> AudioParam.setValueCurveAtTime(
     ~curve=[|470.0, 370.0, 470.0|],
     ~startTime=2.0,
     ~duration=2.5,
   );

let sawOscillator = Oscillator.make(Sawtooth, audioCtx);
let biquadFilter = AudioContext.createBiquadFilter(audioCtx);
let sawGain = AudioContext.createGain(audioCtx);

biquadFilter->BiquadFilterNode.setType(Lowpass);
BiquadFilterNode.frequency(biquadFilter)->AudioParam.setValue(370.0);
BiquadFilterNode.frequency(biquadFilter)
|> AudioParam.setTargetAtTime(
     ~target=300.0,
     ~startTime=2.0,
     ~timeConstant=3.0,
   );

sawOscillator |> OscillatorNode.connect(biquadFilter);
biquadFilter |> BiquadFilterNode.connect(sawGain);

sawGain |> GainNode.connect(AudioContext.getDestination(audioCtx));
sawGain->GainNode.gain->AudioParam.setValue(epsilon_float);
sawOscillator |> OscillatorNode.start();

module Keyboard = {
  type state = {mutable a: bool};
  let state = {a: false};
};

let trigger = (e: Webapi.Dom.KeyboardEvent.t) =>
  if (Keyboard.state.a == false && Webapi.Dom.KeyboardEvent.key(e) == "a") {
    Keyboard.state.a = true;
    let currentTime = audioCtx |> AudioContext.getOutputTimestamp();
    sineGain |> Envelope.trigger(currentTime);
    sawGain |> Envelope.trigger(currentTime);
  };

let endTrigger = (e: Webapi.Dom.KeyboardEvent.t) =>
  if (Webapi.Dom.KeyboardEvent.key(e) == "a") {
    Keyboard.state.a = false;
    let currentTime = audioCtx |> AudioContext.getOutputTimestamp();
    sineGain |> Envelope.endTrigger(currentTime);
    sawGain |> Envelope.endTrigger(currentTime);
  };

Webapi.Dom.document
|> Webapi.Dom.Document.addKeyDownEventListener(e => trigger(e));

Webapi.Dom.document
|> Webapi.Dom.Document.addKeyUpEventListener(e => endTrigger(e));
