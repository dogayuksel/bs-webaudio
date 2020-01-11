let knobSensitivityFactor = 4;
let sizeInPixels = (x: int) => string_of_int(x) ++ "px";

// Range of degrees displayed
let knobMin = 30.0;
let knobMax = 330.0;

type knobScale =
  | Linear
  | Logarithmic;

type knobConfig = {
  minValue: float,
  maxValue: float,
  scale: knobScale,
  size: int,
};

let clamp = (value: float, config: knobConfig) => {
  let value = value < config.minValue ? config.minValue : value;
  let value = value > config.maxValue ? config.maxValue : value;
  value;
};

let mapValue = (~from: (float, float), ~target: (float, float), value) => {
  let (xmin, xmax) = from;
  let (ymin, ymax) = target;
  (value -. xmin) /. (xmax -. xmin) *. (ymax -. ymin) +. ymin;
};

[@react.component]
let make =
    (
      ~name,
      ~config: knobConfig,
      ~initialParamValue: float,
      ~setParamValue: float => unit,
    ) => {
  let knobDomainInPixels =
    React.useMemo1(
      () => float_of_int(config.size * knobSensitivityFactor),
      [|config.size|],
    );
  let mapParam = mapValue(~from=(config.minValue, config.maxValue));
  let mapToParam = mapValue(~target=(config.minValue, config.maxValue));
  let mapToDegrees = mapValue(~target=(knobMin, knobMax));

  let mapValueToDegrees = (value: float): string => {
    let degrees =
      switch (config.scale) {
      | Linear => value |> mapParam(~target=(knobMin, knobMax))
      | Logarithmic =>
        /* log10(1)=0 */
        /* log10(10)=1 */
        value
        |> mapParam(~target=(1.0, 10.0))
        |> log10
        |> mapToDegrees(~from=(0.0, 1.0))
      };
    Js.Float.toString(degrees) ++ "deg";
  };

  let (value, setValue) = React.useState(() => initialParamValue);
  let lastY = React.useRef(0);

  let handleMouseMove = (event: Webapi.Dom.MouseEvent.t): unit => {
    let clientY = Webapi.Dom.MouseEvent.clientY(event);
    setValue(value => {
      let change =
        React.Ref.current(lastY)
        |> (x => x - clientY)
        |> float_of_int
        |> mapValue(~from=(0.0, knobDomainInPixels), ~target=(0.0, 1.0));
      let newValue =
        switch (config.scale) {
        | Linear =>
          value
          |> mapParam(~target=(0.0, 1.0))
          |> (+.)(change)
          |> mapToParam(~from=(0.0, 1.0))
        | Logarithmic =>
          /* log10(1)=0  <--> 10**0=1  */
          /* log10(10)=1 <--> 10**1=10 */
          value
          |> mapParam(~target=(1.0, 10.0))
          |> log10
          |> (+.)(change)
          |> (x => 10.0 ** x)
          |> mapToParam(~from=(1.0, 10.0))
        };
      let clampedValue = clamp(newValue, config);
      setParamValue(clampedValue);
      React.Ref.setCurrent(lastY, clientY);
      clampedValue;
    });
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
    React.Ref.setCurrent(lastY, clientY);
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
      ~display="inline-block",
      ~padding="10px 20px",
      (),
    )}>
    <h3 style={ReactDOMRe.Style.make(~textAlign="center", ())}>
      {React.string(name)}
    </h3>
    <div
      onMouseDown=handleMouseDown
      style={ReactDOMRe.Style.make(
        ~backgroundColor="#839264",
        ~width=sizeInPixels(config.size),
        ~height=sizeInPixels(config.size),
        ~margin="0 20px",
        ~borderRadius=sizeInPixels(config.size),
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
    <h3 style={ReactDOMRe.Style.make(~textAlign="center", ())}>
      {React.string(string_of_int(int_of_float(value)))}
    </h3>
  </div>;
};
