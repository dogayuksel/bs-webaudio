let audioCtx = AudioContext.createAudioContext();

/*******/
/* LFO */
/*******/
let lfo =
  audioCtx
  |> LFO.make
  |> LFO.setFrequency(~frequency=10.0)
  |> LFO.connect(~target=AudioContext.getDestination(audioCtx));

/******************/
/* OSCILLATOR ONE */
/******************/
let oscOneEnvelope =
  audioCtx |> Envelope.make |> Envelope.connect(~target=lfo.lfoGain);

let oscOne =
  audioCtx
  |> Oscillator.make(~oscillatorType=Sine)
  |> Oscillator.connect(~target=oscOneEnvelope.envelopeGain);

/******************/
/* OSCILLATOR TWO */
/******************/
let oscTwoEnvelope =
  audioCtx |> Envelope.make |> Envelope.connect(~target=lfo.lfoGain);

let oscTwoFilter = AudioContext.createBiquadFilter(audioCtx);
oscTwoFilter->BiquadFilterNode.setType(Lowpass);
BiquadFilterNode.frequency(oscTwoFilter)->AudioParam.setValue(370.0);
BiquadFilterNode.frequency(oscTwoFilter)
|> AudioParam.setTargetAtTime(
     ~target=300.0,
     ~startTime=2.0,
     ~timeConstant=3.0,
   );
oscTwoFilter |> BiquadFilterNode.connect(oscTwoEnvelope.envelopeGain);

let oscTwo =
  audioCtx
  |> Oscillator.make(~oscillatorType=Sawtooth)
  |> Oscillator.connect(~target=oscTwoFilter);

/**********/
/* EVENTS */
/**********/
module Keyboard = {
  type state = {mutable a: bool};
  let state = {a: false};
};

let trigger = (e: Webapi.Dom.KeyboardEvent.t) =>
  if (Keyboard.state.a == false && Webapi.Dom.KeyboardEvent.key(e) == "a") {
    Keyboard.state.a = true;
    oscOneEnvelope |> Envelope.trigger;
    oscTwoEnvelope |> Envelope.trigger;
  };

let endTrigger = (e: Webapi.Dom.KeyboardEvent.t) =>
  if (Webapi.Dom.KeyboardEvent.key(e) == "a") {
    Keyboard.state.a = false;
    oscOneEnvelope |> Envelope.endTrigger;
    oscTwoEnvelope |> Envelope.endTrigger;
  };

Webapi.Dom.document
|> Webapi.Dom.Document.addKeyDownEventListener(e => trigger(e));

Webapi.Dom.document
|> Webapi.Dom.Document.addKeyUpEventListener(e => endTrigger(e));

let startOscillators = _event => {
  oscOne |> Oscillator.start |> ignore;
  oscTwo |> Oscillator.start |> ignore;
};

Webapi.Dom.document
|> Webapi.Dom.Document.getElementById("start")
|> Belt.Option.forEach(_, e =>
     Webapi.Dom.Element.addMouseDownEventListener(startOscillators, e)
   );

ReactDOMRe.renderToElementWithId(
  <>
    <div>
      <h1> {React.string("Oscillator One")} </h1>
      <div>
        <Knob
          name="Frequency"
          param={oscOne |> Oscillator.getFrequency}
          config={minValue: 1.0, maxValue: 18000.0, scale: Logarithmic}
        />
        <Knob
          name="Gain"
          param={oscOne |> Oscillator.getGain}
          config={minValue: epsilon_float, maxValue: 100.0, scale: Linear}
        />
      </div>
    </div>
    <div>
      <h1> {React.string("Oscillator Two")} </h1>
      <div>
        <Knob
          name="Frequency"
          param={oscTwo |> Oscillator.getFrequency}
          config={minValue: 1.0, maxValue: 18000.0, scale: Logarithmic}
        />
        <Knob
          name="Gain"
          param={oscTwo |> Oscillator.getGain}
          config={minValue: epsilon_float, maxValue: 100.0, scale: Linear}
        />
      </div>
    </div>
    <div>
      <h1> {React.string("LFO")} </h1>
      <div>
        <Knob
          name="Frequency"
          param={lfo.lfoOscillator |> Oscillator.getFrequency}
          config={minValue: 1.0, maxValue: 30.0, scale: Linear}
        />
      </div>
    </div>
  </>,
  "app",
);
