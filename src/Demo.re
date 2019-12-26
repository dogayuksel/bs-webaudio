let audioCtx = AudioContext.createAudioContext();

let lfo = audioCtx |> LFO.make;
lfo |> LFO.setFrequency(~frequency=10.0);

lfo |> LFO.connect(~target=AudioContext.getDestination(audioCtx));

let oscOne =
  audioCtx
  |> Oscillator.make(~oscillatorType=Custom(Oscillator.sampleRandomWave()));
let oscOneGain = AudioContext.createGain(audioCtx);
oscOne |> Oscillator.connect(~target=oscOneGain);

oscOneGain |> GainNode.connect(lfo.lfo);
oscOneGain->GainNode.gain->AudioParam.setValue(epsilon_float);
oscOne |> Oscillator.start;

oscOne
|> Oscillator.getFrequency
|> AudioParam.setValueCurveAtTime(
     ~curve=[|470.0, 370.0, 470.0|],
     ~startTime=2.0,
     ~duration=2.5,
   );

let oscTwo = audioCtx |> Oscillator.make(~oscillatorType=Sawtooth);
let oscTwoFilter = AudioContext.createBiquadFilter(audioCtx);
let oscTwoGain = AudioContext.createGain(audioCtx);

oscTwoFilter->BiquadFilterNode.setType(Lowpass);
BiquadFilterNode.frequency(oscTwoFilter)->AudioParam.setValue(370.0);
BiquadFilterNode.frequency(oscTwoFilter)
|> AudioParam.setTargetAtTime(
     ~target=300.0,
     ~startTime=2.0,
     ~timeConstant=3.0,
   );

oscTwo |> Oscillator.connect(~target=oscTwoFilter);
oscTwoFilter |> BiquadFilterNode.connect(oscTwoGain);

oscTwoGain |> GainNode.connect(lfo.lfo);
oscTwoGain->GainNode.gain->AudioParam.setValue(epsilon_float);
oscTwo |> Oscillator.start;

module Keyboard = {
  type state = {mutable a: bool};
  let state = {a: false};
};

let trigger = (e: Webapi.Dom.KeyboardEvent.t) =>
  if (Keyboard.state.a == false && Webapi.Dom.KeyboardEvent.key(e) == "a") {
    Keyboard.state.a = true;
    let currentTime = audioCtx |> AudioContext.getOutputTimestamp();
    oscOneGain |> Envelope.trigger(currentTime);
    oscTwoGain |> Envelope.trigger(currentTime);
  };

let endTrigger = (e: Webapi.Dom.KeyboardEvent.t) =>
  if (Webapi.Dom.KeyboardEvent.key(e) == "a") {
    Keyboard.state.a = false;
    let currentTime = audioCtx |> AudioContext.getOutputTimestamp();
    oscOneGain |> Envelope.endTrigger(currentTime);
    oscTwoGain |> Envelope.endTrigger(currentTime);
  };

Webapi.Dom.document
|> Webapi.Dom.Document.addKeyDownEventListener(e => trigger(e));

Webapi.Dom.document
|> Webapi.Dom.Document.addKeyUpEventListener(e => endTrigger(e));
