[@react.component]
let make = () => {
  let (triggerTargets, setTriggerTargets) = React.useState(() => []);
  let (audioContext, setAudioContext) = React.useState(() => None);

  let addToTriggerTargets = (envelope: Envelope.t): unit => {
    setTriggerTargets(targets => [envelope, ...targets]);
  };
  let removeFromTriggerTargets = (envelope: Envelope.t): unit => {
    setTriggerTargets(targets => targets |> List.filter(e => e != envelope));
  };

  let createAudioContext = (): unit => {
    setAudioContext(_ => Some(AudioContext.createAudioContext()));
  };

  <AppContextProvider
    value=AppContextProvider.{
      audioContext,
      triggerTargets,
      addToTriggerTargets,
      removeFromTriggerTargets,
    }>
    <div
      style={ReactDOMRe.Style.make(
        ~position="absolute",
        ~top="0",
        ~right="0",
        (),
      )}>
      <Switch toggle=createAudioContext initialState=false>
        {React.string("Power")}
      </Switch>
    </div>
    {switch (audioContext) {
     | Some(_) =>
       <>
         <OscillatorUnit name="Oscillator One" targetOutput=None />
         <OscillatorUnit name="Oscillator Two" targetOutput=None />
       </>
     | None => React.null
     }}
    <Keyboard />
  </AppContextProvider>;
};
