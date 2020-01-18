let width = 40;
let height = 20;
let sizeInPixels = (x: int) => string_of_int(x) ++ "px";

[@react.component]
let make = (~isOn: bool, ~children) => {
  <div
    style={ReactDOMRe.Style.make(
      ~display="inline-block",
      ~padding="10px 20px",
      (),
    )}>
    <h5 style={ReactDOMRe.Style.make(~textAlign="center", ())}> children </h5>
    <div
      style={ReactDOMRe.Style.make(
        ~backgroundColor="#839264",
        ~width=sizeInPixels(width),
        ~height=sizeInPixels(height),
        ~margin="10px 20px",
        (),
      )}>
      <div
        style={ReactDOMRe.Style.make(
          ~backgroundColor="#112211",
          ~width=sizeInPixels(width / 2),
          ~height=sizeInPixels(height),
          ~transform=
            "translateX(" ++ (isOn ? sizeInPixels(width / 2) : "0") ++ ")",
          (),
        )}
      />
    </div>
  </div>;
};
