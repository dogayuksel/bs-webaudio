let size = 120;
let sizeInPixels = (x: int) => string_of_int(x) ++ "px";

let offset = 30.0;
let range = 300.0;

type knobScale =
  | Linear
  | Logarithmic;

type knobConfig = {
  minValue: float,
  maxValue: float,
  scale: knobScale,
};

let clamp = (value: float, config: knobConfig) => {
  let value = value < config.minValue ? config.minValue : value;
  let value = value > config.maxValue ? config.maxValue : value;
  value;
};

[@react.component]
let make = (~name, ~param: AudioParam.t, ~config: knobConfig) => {
  let mapValueToDegrees = value => {
    let domain = config.maxValue -. config.minValue;
    let value = value -. config.minValue;
    let degrees =
      value === 0.0
        ? 0.0
        : (
          switch (config.scale) {
          | Linear => range /. domain *. value
          | Logarithmic =>
            range /. Js.Math.log10(domain) *. Js.Math.log10(value)
          }
        );
    Js.Float.toString(degrees +. offset) ++ "deg";
  };

  let (value, setValue) = React.useState(() => param->AudioParam.getValue);
  let (previousY, setPreviousY) = React.useState(() => 0);
  let (nextY, setNextY) = React.useState(() => 0);

  React.useEffect3(
    () => {
      let change = previousY - nextY;
      let scaledChange =
        switch (config.scale) {
        | Linear => float_of_int(Js.Math.abs_int(change))
        | Logarithmic =>
          float_of_int(Js.Math.abs_int(change)) ** Js.Math.log10(value)
        };
      let newValue =
        change > 0 ? value +. scaledChange : value -. scaledChange;
      let clampedValue = clamp(newValue, config);
      param->AudioParam.setValue(clampedValue);
      setValue(_ => clampedValue);
      setPreviousY(_ => nextY);
      None;
    },
    (value, previousY, nextY),
  );

  let handleMouseMove = (event: Webapi.Dom.MouseEvent.t): unit => {
    let clientY = Webapi.Dom.MouseEvent.clientY(event);
    setNextY(_ => clientY);
    ();
  };

  let handleMouseUp = _: unit => {
    Webapi.Dom.EventTarget.removeMouseMoveEventListener(
      handleMouseMove,
      Webapi.Dom.Document.asEventTarget(Webapi.Dom.document),
    );
    ();
  };

  let handleMouseDown = (event: ReactEvent.Mouse.t): unit => {
    let clientY = ReactEvent.Mouse.clientY(event);
    setNextY(_ => clientY);
    setPreviousY(_ => clientY);
    Webapi.Dom.EventTarget.addMouseMoveEventListener(
      handleMouseMove,
      Webapi.Dom.Document.asEventTarget(Webapi.Dom.document),
    );
    Webapi.Dom.EventTarget.addMouseUpEventListenerWithOptions(
      handleMouseUp,
      {"capture": false, "once": true, "passive": true},
      Webapi.Dom.Document.asEventTarget(Webapi.Dom.document),
    );
    ();
  };

  <div
    style={ReactDOMRe.Style.make(
      ~padding="10px",
      ~width=sizeInPixels(size + 20),
      (),
    )}>
    <div
      onMouseDown=handleMouseDown
      style={ReactDOMRe.Style.make(
        ~backgroundColor="#839264",
        ~width=sizeInPixels(size),
        ~height=sizeInPixels(size),
        ~borderRadius=sizeInPixels(size),
        ~margin="10px",
        ~display="flex",
        ~justifyContent="center",
        ~transform="rotate(" ++ mapValueToDegrees(value) ++ ")",
        (),
      )}>
      <div
        style={ReactDOMRe.Style.make(
          ~width="0",
          ~height="0",
          ~borderLeft="10px solid transparent",
          ~borderRight="10px solid transparent",
          ~borderBottom="10px solid black",
          (),
        )}
      />
    </div>
    <div
      style={ReactDOMRe.Style.make(
        ~display="flex",
        ~justifyContent="center",
        (),
      )}>
      {React.string(name ++ ": ")}
      {React.string(string_of_int(int_of_float(value)))}
    </div>
  </div>;
};
