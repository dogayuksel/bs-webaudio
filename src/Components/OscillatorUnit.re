[@react.component]
let make =
    (~name: string, ~targetOutput: option(AudioNode.audioNode_like('a))) => {
  let appContext = React.useContext(AppContextProvider.appContext);
  let (oscillator, setOscillator) = React.useState(() => None);
  let (envelope, setEnvelope) = React.useState(() => None);

  React.useEffect0(() => {
    switch (appContext.audioContext) {
    | Some(audioCtx) =>
      let target =
        switch (targetOutput) {
        | Some(target) => target
        | None => audioCtx |> AudioContext.getDestination
        };
      let osc =
        audioCtx
        |> Oscillator.make(~oscillatorType=Sine)
        |> Oscillator.connect(~target);
      setOscillator(_ => Some(osc));
      let envelope =
        audioCtx |> Envelope.make(Oscillator.getEnvelopeGain(osc));
      setEnvelope(_ => Some(envelope));
      ();
    | None => Js.log("Missing Audio Context")
    };
    Some(
      () => {
        oscillator->Belt.Option.map(Oscillator.disconnect) |> ignore;
        envelope->Belt.Option.map(appContext.removeFromTriggerTargets)
        |> ignore;
      },
    );
  });

  let startOscillator = (envelope: option(Envelope.t), ()): unit => {
    oscillator->Belt.Option.map(Oscillator.start) |> ignore;
    envelope->Belt.Option.map(appContext.addToTriggerTargets) |> ignore;
  };

  <div>
    <h2> {React.string(name)} </h2>
    <Switch toggle={startOscillator(envelope)} initialState=false>
      {React.string("Start")}
    </Switch>
    {switch (oscillator, envelope) {
     | (Some(o), Some(e)) =>
       <>
         <Knob
           name="Frequency"
           initialParamValue={
             o |> Oscillator.getFrequency |> AudioParam.getValue
           }
           setParamValue={frequency =>
             o |> Oscillator.setFrequency(~frequency)
           }
           config={
             minValue: 1.0,
             maxValue: 18000.0,
             scale: Logarithmic,
             size: 120,
           }
         />
         <Slider
           name="Gain"
           param={o |> Oscillator.getOscillatorGain}
           config={minValue: epsilon_float, maxValue: 100.0}
         />
         <EnvelopeUnit envelope=e />
       </>
     | _ => ReasonReact.null
     }}
  </div>;
};
