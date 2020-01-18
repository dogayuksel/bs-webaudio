[@react.component]
let make = () => {
  let (oscillatorIndex, setOscillatorIndex) = React.useState(() => 1);
  let (oscillators, setOscillators) = React.useState(() => [1]);

  let addOscillator = () => {
    setOscillators(oList => {[oscillatorIndex + 1, ...oList]});
    setOscillatorIndex(idx => idx + 1);
  };

  let removeOscillator = (osc: int) => {
    setOscillators(oList => oList |> List.filter(o => o != osc));
  };

  <div>
    <div
      onClick={_ => addOscillator()}
      style={ReactDOMRe.Style.make(
        ~display="inline-block",
        ~backgroundColor="#839264",
        ~color="#FFF3F5",
        ~margin="10px 15px",
        ~padding="0 20px",
        (),
      )}>
      <h4> {React.string("Add Oscillator")} </h4>
    </div>
    <div>
      {oscillators
       |> List.map(osc =>
            <div key={string_of_int(osc)}>
              <div
                onClick={_ => removeOscillator(osc)}
                style={ReactDOMRe.Style.make(
                  ~display="inline-block",
                  ~backgroundColor="#839264",
                  ~color="#FFF3F5",
                  ~margin="0 15px",
                  ~padding="0 20px",
                  (),
                )}>
                <h4> {React.string("X")} </h4>
              </div>
              <OscillatorUnit
                name={"Oscillator " ++ string_of_int(osc)}
                targetOutput=None
                alone={oscillators |> List.length == 1}
              />
            </div>
          )
       |> Array.of_list
       |> ReasonReact.array}
    </div>
  </div>;
};
