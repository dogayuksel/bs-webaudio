[@react.component]
let make =
    (
      ~name: string,
      ~targetOutput: option(AudioNode.audioNode_like('a)),
      ~alone: bool=false,
    ) => {
  let appContext = React.useContext(AppContextProvider.appContext);
  let (oscillatorOn, setOscillatorOn) = React.useState(() => false);
  let oscillator = React.useRef(None);
  let envelope = React.useRef(None);

  let cleanUp = (): unit => {
    oscillator
    ->React.Ref.current
    ->Belt.Option.map(Oscillator.cleanUp)
    ->ignore;
    envelope
    ->React.Ref.current
    ->Belt.Option.map(appContext.removeFromTriggerTargets)
    ->ignore;
  };

  let toggleOscillator = _: unit =>
    if (oscillatorOn == false) {
      switch (appContext.audioContext) {
      | Some(audioContext) =>
        let target =
          switch (targetOutput) {
          | Some(target) => target
          | None => audioContext |> AudioContext.getDestination
          };
        let osc =
          audioContext
          |> Oscillator.make
          |> Oscillator.connect(~target)
          |> Oscillator.start;
        oscillator->React.Ref.setCurrent(Some(osc));
        let env =
          audioContext |> Envelope.make(Oscillator.getEnvelopeGain(osc));
        env |> appContext.addToTriggerTargets;
        envelope->React.Ref.setCurrent(Some(env));
        setOscillatorOn(_ => true);
        ();
      | None => Js.log("Missing Audio Context")
      };
    } else {
      cleanUp();
      setOscillatorOn(_ => false);
    };

  React.useEffect0(() => {
    if (alone) {
      toggleOscillator();
    };
    Some(() => cleanUp());
  });

  <div style={ReactDOMRe.Style.make(~backgroundColor=ColorPalette.green, ())}>
    <h3
      style={ReactDOMRe.Style.make(~color=ColorPalette.white, ())}
      className="knob-label">
      {React.string(name)}
    </h3>
    <div
      style={ReactDOMRe.Style.make(~display="inline-block", ())}
      onClick=toggleOscillator>
      <Switch isOn=oscillatorOn> {React.string("START")} </Switch>
    </div>
    {switch (React.Ref.current(oscillator), React.Ref.current(envelope)) {
     | (Some(osc), Some(env)) =>
       <>
         <WaveSampler
           setWaveCallback={wave =>
             Oscillator.setOscillatorType(~oscillatorType=Custom(wave), osc)
           }
         />
         <div
           style={ReactDOMRe.Style.make(
             ~display="inline-block",
             ~backgroundColor=ColorPalette.blue,
             ~padding="0 20px",
             ~margin="10px",
             ~border="3px solid " ++ ColorPalette.white,
             ~borderRadius="20px",
             (),
           )}>
           <Knob
             name="FREQUENCY"
             initialParamValue={
               osc |> Oscillator.getFrequency |> AudioParam.getValue
             }
             setParamValue={frequency =>
               osc |> Oscillator.setFrequency(~frequency)
             }
             config={
               minValue: 1.0,
               maxValue: 18000.0,
               scale: Logarithmic,
               size: 120,
             }
           />
           <Slider
             name="GAIN"
             param={osc |> Oscillator.getOscillatorGain}
             config={minValue: epsilon_float, maxValue: 1.0}
           />
         </div>
         <EnvelopeUnit envelope=env />
       </>
     | _ => ReasonReact.null
     }}
  </div>;
};
