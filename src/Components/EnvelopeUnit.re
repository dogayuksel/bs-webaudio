[@react.component]
let make = (~envelope: Envelope.t) => {
  <div
    style={ReactDOMRe.Style.make(
      ~display="inline-block",
      ~backgroundColor=ColorPalette.blue,
      ~padding="0 20px",
      ~margin="10px",
      ~border="3px solid " ++ ColorPalette.white,
      ~borderRadius="20px",
      (),
    )}>
    <div>
      <Knob
        name="ATTACK"
        initialParamValue={envelope.envelopeParams.attack}
        setParamValue={value =>
          envelope |> Envelope.update(~param=Attack(value))
        }
        config={
          minValue: epsilon_float,
          maxValue: 2.0,
          scale: Linear,
          size: 50,
        }
      />
      <Knob
        name="DECAY"
        initialParamValue={envelope.envelopeParams.decay}
        setParamValue={value =>
          envelope |> Envelope.update(~param=Decay(value))
        }
        config={
          minValue: epsilon_float,
          maxValue: 5.0,
          scale: Linear,
          size: 50,
        }
      />
    </div>
    <div>
      <Knob
        name="SUSTAIN"
        initialParamValue={envelope.envelopeParams.sustain}
        setParamValue={value =>
          envelope |> Envelope.update(~param=Sustain(value))
        }
        config={
          minValue: epsilon_float,
          maxValue: 1.0,
          scale: Linear,
          size: 50,
        }
      />
      <Knob
        name="RELEASE"
        initialParamValue={envelope.envelopeParams.release}
        setParamValue={value =>
          envelope |> Envelope.update(~param=Release(value))
        }
        config={
          minValue: epsilon_float,
          maxValue: 5.0,
          scale: Linear,
          size: 50,
        }
      />
    </div>
  </div>;
};
