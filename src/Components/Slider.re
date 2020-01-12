let height = 120;
let width = 30;
let buttonHeight = 10;
let sizeInPixels = (x: int) => string_of_int(x) ++ "px";

type sliderConfig = {
  minValue: float,
  maxValue: float,
};

let clamp = (value: float, config: sliderConfig) => {
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
let make = (~name, ~param: AudioParam.t, ~config: sliderConfig) => {
  let mapParam = mapValue(~from=(config.minValue, config.maxValue));
  let mapToParam = mapValue(~target=(config.minValue, config.maxValue));

  let indicatorPrecission =
    React.useMemo2(
      (): int => {
        let logRange = log10(config.maxValue -. config.minValue);
        if (logRange > 3.0) {
          0;
        } else if (logRange > 0.8) {
          1;
        } else {
          2;
        };
      },
      (config.minValue, config.maxValue),
    );

  let mapValueToHeight = (value: float): string => {
    let height =
      value |> mapParam(~target=(float_of_int(height - buttonHeight), 0.0));
    Js.Float.toString(height) ++ "px";
  };

  let (value, setValue) = React.useState(() => param->AudioParam.getValue);
  let lastY = React.useRef(0);

  let handleMouseMove = (event: Webapi.Dom.MouseEvent.t): unit => {
    let clientY = Webapi.Dom.MouseEvent.clientY(event);
    setValue(value => {
      let change =
        React.Ref.current(lastY)
        |> (x => x - clientY)
        |> float_of_int
        |> mapValue(~from=(0.0, float_of_int(height)), ~target=(0.0, 1.0));
      let newValue =
        value
        |> mapParam(~target=(0.0, 1.0))
        |> (+.)(change)
        |> mapToParam(~from=(0.0, 1.0));
      let clampedValue = clamp(newValue, config);
      param->AudioParam.setValue(clampedValue);
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
        ~width=sizeInPixels(width),
        ~height=sizeInPixels(height),
        ~margin="0 20px",
        (),
      )}>
      <div
        style={ReactDOMRe.Style.make(
          ~width=sizeInPixels(width),
          ~height=sizeInPixels(buttonHeight),
          ~backgroundColor="#112211",
          ~transform="translateY(" ++ mapValueToHeight(value) ++ ")",
          (),
        )}
      />
    </div>
    <h3 style={ReactDOMRe.Style.make(~textAlign="center", ())}>
      {React.string(
         Js.Float.toFixedWithPrecision(~digits=indicatorPrecission, value),
       )}
    </h3>
  </div>;
};
