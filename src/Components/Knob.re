let size = 80;
let sizeInPixels = (x: int) => string_of_int(x) ++ "px";

[@react.component]
let make = (~name, ~param: AudioParam.t) => {
  let mapValueToDegrees = value => {
    /* 0 to 20000 maps to -180 to 180 */
    Js.Float.toString(Js.Math.log10(value) *. 36.0) ++ "deg";
  };

  let (value, setValue) = React.useState(() => param |> AudioParam.getValue);
  let (initialY, setInitialY) = React.useState(() => 0);
  let (currentY, setCurrentY) = React.useState(() => 0);

  React.useEffect2(
    () => {
      let newValue = value +. float_of_int(initialY - currentY);
      Js.log("effect: new value => " ++ Js.Float.toString(newValue));
      param->AudioParam.setValue(newValue);
      setValue(_ => newValue);
      None;
    },
    (initialY, currentY),
  );

  let handleMouseMove = (event: Webapi.Dom.MouseEvent.t): unit => {
    Js.log(event);
    let currentY = Webapi.Dom.MouseEvent.clientY(event);
    setCurrentY(_ => currentY);
  };

  let handleMouseUp = _: unit => {
    Webapi.Dom.EventTarget.removeMouseMoveEventListener(
      handleMouseMove,
      Webapi.Dom.Document.asEventTarget(Webapi.Dom.document),
    );
  };

  let handleMouseDown = (event: ReactEvent.Mouse.t) => {
    let clientY = ReactEvent.Mouse.clientY(event);
    setInitialY(_ => clientY);
    setCurrentY(_ => clientY);
    Webapi.Dom.EventTarget.addMouseMoveEventListener(
      handleMouseMove,
      Webapi.Dom.Document.asEventTarget(Webapi.Dom.document),
    );
    Webapi.Dom.EventTarget.addMouseUpEventListenerWithOptions(
      handleMouseUp,
      {"capture": false, "once": true, "passive": true},
      Webapi.Dom.Document.asEventTarget(Webapi.Dom.document),
    );
  };

  <div
    style={ReactDOMRe.Style.make(
      ~padding="10px",
      ~width=sizeInPixels(size + 20 + 200),
      ~fontFamily="sans-serif",
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
      {React.string(Js.Float.toString(value))}
    </div>
    <p> {React.string("DEBUG: " ++ mapValueToDegrees(value))} </p>
  </div>;
};
