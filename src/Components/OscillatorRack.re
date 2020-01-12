[@react.component]
let make = () => {
  let (oscillators, setOscillators) = React.useState(() => [1]);

  let addOscillator = () => {
    setOscillators(oscs => [(oscs |> List.hd) + 1, ...oscs]);
  };

  <div>
    <div
      onClick={_ => addOscillator()}
      style={ReactDOMRe.Style.make(
        ~display="inline-block",
        ~backgroundColor="#839264",
        ~color="#FFF3F5",
        ~margin="10px 15px",
        ~padding="10px",
        (),
      )}>
      {React.string("Add Oscillator")}
    </div>
    <div>
      {oscillators
       |> List.map(osc =>
            <OscillatorUnit
              name={"Oscillator " ++ string_of_int(osc)}
              targetOutput=None
              key={string_of_int(osc)}
            />
          )
       |> Array.of_list
       |> ReasonReact.array}
    </div>
  </div>;
};
