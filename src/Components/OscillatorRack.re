[@react.component]
let make = () => {
  let (oscillatorIndex, setOscillatorIndex) = React.useState(() => 1);
  let (oscillators, setOscillators) = React.useState(() => [1]);

  let addOscillator = () => {
    setOscillators(oList => {[oscillatorIndex + 1, ...oList]});
    setOscillatorIndex(idx => idx + 1);
  };

  let removeOscillator =
    React.useCallback0((osc: int, ()) => {
      setOscillators(oList => oList |> List.filter(o => o != osc))
    });

  <div>
    <button onClick={_ => addOscillator()} className="unit-container">
      {React.string("Add Oscillator")}
    </button>
    <div>
      {oscillators
       |> List.map(osc =>
            <div key={string_of_int(osc)}>
              <OscillatorUnit
                name={"OSCILLATOR " ++ string_of_int(osc)}
                targetOutput=None
                alone={oscillators |> List.length == 1}
                remove={removeOscillator(osc)}
              />
            </div>
          )
       |> Array.of_list
       |> ReasonReact.array}
    </div>
  </div>;
};
