[@react.component]
let make =
    (~name: string, ~targetOutput: option(AudioNode.audioNode_like('a))) => {
  let appContext = React.useContext(AppContextProvider.appContext);
  let (oscillatorOn, setOscillatorOn) = React.useState(() => false);
  let (oscillator, setOscillator) = React.useState(() => None);
  let (envelope, setEnvelope) = React.useState(() => None);

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
          |> Oscillator.make(~oscillatorType=Sine)
          |> Oscillator.connect(~target)
          |> Oscillator.start;
        setOscillator(_ => Some(osc));
        let env =
          audioContext |> Envelope.make(Oscillator.getEnvelopeGain(osc));
        env |> appContext.addToTriggerTargets;
        setEnvelope(_ => Some(env));
        setOscillatorOn(_ => true);
        ();
      | None => Js.log("Missing Audio Context")
      };
    } else {
      oscillator
      ->Belt.Option.map(Oscillator.stop)
      ->Belt.Option.map(Oscillator.disconnect)
      ->ignore;
      setOscillator(_ => None);
      envelope->Belt.Option.map(appContext.removeFromTriggerTargets)->ignore;
      setEnvelope(_ => None);
      setOscillatorOn(_ => false);
    };

  <div>
    <h2> {React.string(name)} </h2>
    <div onClick=toggleOscillator>
      <Switch isOn=oscillatorOn> {React.string("Start")} </Switch>
    </div>
    {switch (oscillator, envelope) {
     | (Some(osc), Some(env)) =>
       <>
         <WaveSampler
           setWaveCallback={wave =>
             Oscillator.setOscillatorType(~oscillatorType=Custom(wave), osc)
           }
         />
         <Knob
           name="Frequency"
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
           name="Gain"
           param={osc |> Oscillator.getOscillatorGain}
           config={minValue: epsilon_float, maxValue: 100.0}
         />
         <EnvelopeUnit envelope=env />
       </>
     | _ => ReasonReact.null
     }}
  </div>;
};
