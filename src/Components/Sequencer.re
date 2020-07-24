[@react.component]
let make = () => {
  let appContext = React.useContext(AppContextProvider.appContext);
  let (sequencer, setSequencer) = React.useState(_ => Array.make(8, false));
  let (sequencerOn, setSequencerOn) = React.useState(_ => false);
  let (activeStep, setActiveStep) = React.useState(_ => (-1));
  let lastTrigger = React.useRef(None);

  let toggleSequencer = index => {
    setSequencer(s => {
      s->Array.set(index, !s[index]);
      s->Array.copy;
    });
  };

  let toggleSequencerOn = _ => {
    setSequencerOn(isOn =>
      if (isOn == true) {
        setActiveStep(_ => (-1));
        lastTrigger.current = None;
        false;
      } else {
        true;
      }
    );
  };

  let triggerTargets = targets => {
    targets |> List.iter(env => env |> Envelope.trigger);
    Js_global.setTimeout(
      _ =>
        appContext.triggerTargets
        |> List.iter(env => env |> Envelope.endTrigger),
      120,
    )
    |> ignore;
  };

  React.useEffect3(
    () =>
      switch (appContext.audioContext, sequencerOn) {
      | (Some(audioContext), true) =>
        let interval =
          Js_global.setInterval(
            _ => {
              let timeStamp =
                audioContext |> AudioContext.getOutputTimestamp();
              lastTrigger.current = Some(timeStamp.performanceTime);
              setActiveStep(step => {
                let newStep = step === 7 ? 0 : step + 1;
                if (sequencer[newStep] == true) {
                  appContext.triggerTargets |> triggerTargets;
                };
                newStep;
              });
            },
            500,
          );
        Some(_ => Js_global.clearInterval(interval));
      | _ => None
      },
    (appContext.triggerTargets, sequencerOn, sequencer),
  );

  <div className="unit-group-container">
    <h2 className="unit-label"> {React.string("SEQUENCER")} </h2>
    <div className="row-group-container">
      <div className="unit-container">
        <Switch isOn=sequencerOn toggle=toggleSequencerOn>
          {React.string("START")}
        </Switch>
      </div>
      <div
        className="unit-container"
        style={ReactDOMRe.Style.make(~display="flex", ())}>
        {sequencer
         |> Array.mapi((ind, value) =>
              <div
                key={string_of_int(ind)}
                onClick={_ => toggleSequencer(ind)}
                style={ReactDOMRe.Style.make(
                  ~margin="5px",
                  ~backgroundColor=
                    value ? ColorPalette.black : ColorPalette.white,
                  ~width="40px",
                  ~height="50px",
                  ~display="flex",
                  ~justifyContent="center",
                  ~alignItems="center",
                  (),
                )}>
                {activeStep == ind
                   ? <div
                       style={ReactDOMRe.Style.make(
                         ~backgroundColor=ColorPalette.green,
                         ~width="20px",
                         ~height="20px",
                         ~borderRadius="20px",
                         (),
                       )}
                     />
                   : ReasonReact.null}
              </div>
            )
         |> ReasonReact.array}
      </div>
    </div>
  </div>;
};
