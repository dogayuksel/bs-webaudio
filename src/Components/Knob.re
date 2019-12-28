let size = 120;
let sizeInPixels = (x: int) => string_of_int(x) ++ "px";

[@react.component]
let make = (~name, ~param: AudioParam.t) => {
  let mapValueToDegrees = value => {
    Js.Float.toString(Js.Math.log10(value) *. 60.0) ++ "deg";
  };

  let (value, setValue) = React.useState(() => param->AudioParam.getValue);
  let (previousY, setPreviousY) = React.useState(() => 0);
  let (nextY, setNextY) = React.useState(() => 0);

  React.useEffect3(
    () => {
      let newValue = value +. float_of_int(previousY - nextY);
      param->AudioParam.setValue(newValue);
      setValue(_ => newValue);
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
      {React.string(Js.Float.toString(value))}
    </div>
  </div>;
};
