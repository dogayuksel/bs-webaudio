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
let oscOne =
  audioCtx
  |> Oscillator.make(~oscillatorType=Sine)
  |> Oscillator.connect(~target=lfo.outputGain);

let oscOneEnvelope =
  audioCtx |> Envelope.make(Oscillator.getEnvelopeGain(oscOne));

/******************/
/* OSCILLATOR TWO */
/******************/
let oscTwoFilter = AudioContext.createBiquadFilter(audioCtx);
oscTwoFilter->BiquadFilterNode.setType(Lowpass);
BiquadFilterNode.frequency(oscTwoFilter)->AudioParam.setValue(370.0);
BiquadFilterNode.frequency(oscTwoFilter)
|> AudioParam.setTargetAtTime(
     ~target=300.0,
     ~startTime=2.0,
     ~timeConstant=3.0,
   );
oscTwoFilter |> BiquadFilterNode.connect(lfo.outputGain);

let oscTwo =
  audioCtx
  |> Oscillator.make(~oscillatorType=Sawtooth)
  |> Oscillator.connect(~target=oscTwoFilter);

let oscTwoEnvelope =
  audioCtx |> Envelope.make(Oscillator.getEnvelopeGain(oscTwo));

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
  audioCtx |> AudioContext.resume;
  oscOne |> Oscillator.start |> ignore;
  oscTwo |> Oscillator.start |> ignore;
  lfo |> LFO.start |> ignore;
};

ReactDOMRe.renderToElementWithId(
  <>
    <div
      style={ReactDOMRe.Style.make(
        ~position="absolute",
        ~top="0",
        ~right="0",
        (),
      )}>
      <Switch toggle=startOscillators initialState=false>
        {React.string("Power")}
      </Switch>
    </div>
    <div>
      <h2> {React.string("Oscillator One")} </h2>
      <div>
        <Knob
          name="Frequency"
          initialParamValue={
            oscOne |> Oscillator.getFrequency |> AudioParam.getValue
          }
          setParamValue={frequency =>
            oscOne |> Oscillator.setFrequency(~frequency)
          }
          config={minValue: 1.0, maxValue: 18000.0, scale: Logarithmic}
        />
        <Slider
          name="Gain"
          param={oscOne |> Oscillator.getOscillatorGain}
          config={minValue: epsilon_float, maxValue: 100.0}
        />
      </div>
    </div>
    <div>
      <h2> {React.string("Oscillator Two")} </h2>
      <div>
        <Knob
          name="Frequency"
          initialParamValue={
            oscTwo |> Oscillator.getFrequency |> AudioParam.getValue
          }
          setParamValue={frequency =>
            oscTwo |> Oscillator.setFrequency(~frequency)
          }
          config={minValue: 1.0, maxValue: 18000.0, scale: Logarithmic}
        />
        <Slider
          name="Gain"
          param={oscTwo |> Oscillator.getOscillatorGain}
          config={minValue: epsilon_float, maxValue: 100.0}
        />
      </div>
    </div>
    <div>
      <h2> {React.string("LFO")} </h2>
      <div>
        <Knob
          name="Frequency"
          initialParamValue={
            lfo.oscillatorNode
            |> Oscillator.getFrequency
            |> AudioParam.getValue
          }
          setParamValue={frequency =>
            lfo.oscillatorNode |> Oscillator.setFrequency(~frequency)
          }
          config={minValue: 1.0, maxValue: 30.0, scale: Linear}
        />
      </div>
    </div>
  </>,
  "app",
);
