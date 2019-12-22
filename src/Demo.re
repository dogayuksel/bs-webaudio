let audioCtx = AudioContext.createAudioContext();

let sineOscillator = Oscillator.make(Sine, audioCtx);
let biquadFilter = AudioContext.createBiquadFilter(audioCtx);
let sineGain = AudioContext.createGain(audioCtx);

sineOscillator |> OscillatorNode.connect(biquadFilter);

biquadFilter->BiquadFilterNode.setType(Lowpass);
biquadFilter |> BiquadFilterNode.connect(sineGain);

sineGain |> GainNode.connect(AudioContext.getDestination(audioCtx));
sineGain->GainNode.gain->AudioParam.setValue(0.0005);
sineOscillator |> OscillatorNode.start();

OscillatorNode.frequency(sineOscillator)
|> AudioParam.setValueCurveAtTime(
     ~curve=[|470.0, 370.0, 470.0|],
     ~startTime=2.0,
     ~duration=2.5,
   );

BiquadFilterNode.frequency(biquadFilter)->AudioParam.setValue(470.0);
BiquadFilterNode.frequency(biquadFilter)
|> AudioParam.setTargetAtTime(
     ~target=450.0,
     ~startTime=2.0,
     ~timeConstant=1.0,
   );

let sawOscillator = Oscillator.make(SawTooth, audioCtx);
let sawGain = AudioContext.createGain(audioCtx);
sawOscillator |> OscillatorNode.connect(sawGain);
sawGain |> GainNode.connect(AudioContext.getDestination(audioCtx));
sawGain->GainNode.gain->AudioParam.setValue(0.0005);
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
