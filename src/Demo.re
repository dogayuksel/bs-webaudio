let audioCtx = AudioContext.createAudioContext();

let lfo = audioCtx |> LFO.make;
lfo |> LFO.setFrequency(~frequency=10.0);

lfo |> LFO.connect(~target=AudioContext.getDestination(audioCtx));

let oscOne =
  audioCtx |> Oscillator.makeFromRandom |> Oscillator.connect(~target=lfo.lfo);

oscOne.oscillatorGain->GainNode.gain->AudioParam.setValue(epsilon_float);
oscOne |> Oscillator.start;

let oscTwo = audioCtx |> Oscillator.make(~oscillatorType=Sawtooth);
let oscTwoFilter = AudioContext.createBiquadFilter(audioCtx);

oscTwoFilter->BiquadFilterNode.setType(Lowpass);
BiquadFilterNode.frequency(oscTwoFilter)->AudioParam.setValue(370.0);
BiquadFilterNode.frequency(oscTwoFilter)
|> AudioParam.setTargetAtTime(
     ~target=300.0,
     ~startTime=2.0,
     ~timeConstant=3.0,
   );

oscTwo |> Oscillator.connect(~target=oscTwoFilter);
oscTwoFilter |> BiquadFilterNode.connect(lfo.lfo);
oscTwo.oscillatorGain->GainNode.gain->AudioParam.setValue(epsilon_float);
oscTwo |> Oscillator.start;

module Keyboard = {
  type state = {mutable a: bool};
  let state = {a: false};
};

let trigger = (e: Webapi.Dom.KeyboardEvent.t) =>
  if (Keyboard.state.a == false && Webapi.Dom.KeyboardEvent.key(e) == "a") {
    Keyboard.state.a = true;
    let currentTime = audioCtx |> AudioContext.getOutputTimestamp();
    oscOne.oscillatorGain |> Envelope.trigger(currentTime);
    oscTwo.oscillatorGain |> Envelope.trigger(currentTime);
  };

let endTrigger = (e: Webapi.Dom.KeyboardEvent.t) =>
  if (Webapi.Dom.KeyboardEvent.key(e) == "a") {
    Keyboard.state.a = false;
    let currentTime = audioCtx |> AudioContext.getOutputTimestamp();
    oscOne.oscillatorGain |> Envelope.endTrigger(currentTime);
    oscTwo.oscillatorGain |> Envelope.endTrigger(currentTime);
  };

Webapi.Dom.document
|> Webapi.Dom.Document.addKeyDownEventListener(e => trigger(e));

Webapi.Dom.document
|> Webapi.Dom.Document.addKeyUpEventListener(e => endTrigger(e));

ReactDOMRe.renderToElementWithId(
  <Knob
    name="Frequency"
    param={oscOne |> Oscillator.getFrequency}
    config={minValue: 1.0, maxValue: 22500.0, scale: Logarithmic}
  />,
  "app",
);
