[@react.component]
let make = () => {
  let appContext = React.useContext(AppContextProvider.appContext);
  let (sequencer, setSequencer) = React.useState(_ => Array.make(8, false));
  let (sequencerOn, setSequencerOn) = React.useState(_ => false);
  let (_activeStep, setActiveStep) = React.useState(_ => 0);
  let (_, setKeyPress) = React.useState(() => false);

  let toggleSequencer = index => {
    setSequencer(s => {
      s->Array.set(index, !s[index]);
      s->Array.copy;
    });
  };

  let toggleSequencerOn = _ => {
    setSequencerOn(isOn =>
      if (isOn == true) {
        setActiveStep(_ => 0);
        false;
      } else {
        true;
      }
    );
  };

  let trigger = (e: Webapi.Dom.KeyboardEvent.t) =>
    if (Webapi.Dom.KeyboardEvent.key(e) == "a") {
      setKeyPress(key =>
        if (key == false) {
          appContext.triggerTargets
          |> List.iter(env => env |> Envelope.trigger);
          true;
        } else {
          true;
        }
      );
    };

  let endTrigger = (e: Webapi.Dom.KeyboardEvent.t) =>
    if (Webapi.Dom.KeyboardEvent.key(e) == "a") {
      setKeyPress(_ => {
        appContext.triggerTargets
        |> List.iter(env => env |> Envelope.endTrigger);
        false;
      });
    };

  React.useEffect1(
    () => {
      Webapi.Dom.document
      |> Webapi.Dom.Document.addKeyDownEventListener(trigger);
      Webapi.Dom.document
      |> Webapi.Dom.Document.addKeyUpEventListener(endTrigger);
      Some(
        () => {
          Webapi.Dom.document
          |> Webapi.Dom.Document.removeKeyDownEventListener(trigger);
          Webapi.Dom.document
          |> Webapi.Dom.Document.removeKeyDownEventListener(endTrigger);
        },
      );
    },
    [|appContext.triggerTargets|],
  );

  React.useEffect2(
    () =>
      if (sequencerOn == true) {
        let interval =
          Js_global.setInterval(
            _ => {
              appContext.triggerTargets
              |> List.iter(env => env |> Envelope.trigger);
              Js_global.setTimeout(
                _ => {
                  appContext.triggerTargets
                  |> List.iter(env => env |> Envelope.endTrigger)
                },
                120,
              )
              |> ignore;
            },
            500,
          );
        Some(_ => Js_global.clearInterval(interval));
      } else {
        None;
      },
    (sequencerOn, sequencer),
  );

  <div className="unit-group-container">
    <h2 className="unit-label"> {React.string("SEQUENCER")} </h2>
    <div className="row-group-container">
      <div className="unit-container">
        <Switch isOn=sequencerOn toggle=toggleSequencerOn>
          {React.string("START")}
        </Switch>
      </div>
      <div className="unit-container">
        {sequencer
         |> Array.mapi((ind, value) => {
              <div
                key={string_of_int(ind)}
                onClick={_ => toggleSequencer(ind)}
                style={ReactDOMRe.Style.make(
                  ~margin="5px",
                  ~backgroundColor=
                    value ? ColorPalette.black : ColorPalette.white,
                  ~display="inline-block",
                  ~width="40px",
                  ~height="50px",
                  (),
                )}
              />
            })
         |> ReasonReact.array}
      </div>
    </div>
  </div>;
};
