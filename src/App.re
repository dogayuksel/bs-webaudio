[@react.component]
let make = () => {
  let (audioContextOn, setAudioContextOn) = React.useState(() => false);
  let (triggerTargets, setTriggerTargets) = React.useState(() => []);
  let (audioContext, setAudioContext) = React.useState(() => None);

  let addToTriggerTargets = (envelope: Envelope.t): unit => {
    setTriggerTargets(targets => [envelope, ...targets]);
  };
  let removeFromTriggerTargets = (envelope: Envelope.t): unit => {
    setTriggerTargets(targets => targets |> List.filter(e => e != envelope));
  };

  let toggleAudioContextOn = _ =>
    if (audioContextOn == false) {
      switch (audioContext) {
      | Some(audioCtx) =>
        audioCtx
        |> AudioContext.resume
        |> Js.Promise.then_(_ => {
             Js.Promise.resolve(setAudioContextOn(_ => true))
           })
        |> ignore
      | None =>
        setAudioContext(_ => Some(AudioContext.createAudioContext()));
        setAudioContextOn(_ => true);
      };
    } else {
      audioContext
      ->Belt.Option.map(AudioContext.suspend)
      ->Belt.Option.map(
          Js.Promise.then_(_ => {
            Js.Promise.resolve(setAudioContextOn(_ => false))
          }),
        )
      |> ignore;
    };

  <AppContextProvider
    value=AppContextProvider.{
      audioContext,
      triggerTargets,
      addToTriggerTargets,
      removeFromTriggerTargets,
    }>
    <div
      onClick=toggleAudioContextOn
      style={ReactDOMRe.Style.make(
        ~position="absolute",
        ~top="0",
        ~right="0",
        (),
      )}>
      <Switch isOn=audioContextOn> {React.string("POWER")} </Switch>
    </div>
    {switch (audioContext) {
     | Some(_) => <OscillatorRack />
     | None => React.null
     }}
    <Keyboard />
  </AppContextProvider>;
};
