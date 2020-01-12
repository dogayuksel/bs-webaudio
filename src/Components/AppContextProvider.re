type appContext = {
  audioContext: option(AudioContext.t),
  triggerTargets: list(Envelope.t),
  addToTriggerTargets: Envelope.t => unit,
  removeFromTriggerTargets: Envelope.t => unit,
};

let appContext =
  React.createContext({
    audioContext: None,
    triggerTargets: [],
    addToTriggerTargets: _ => (),
    removeFromTriggerTargets: _ => (),
  });

let makeProps = (~value, ~children, ()) => {
  "value": value,
  "children": children,
};

let make = React.Context.provider(appContext);
