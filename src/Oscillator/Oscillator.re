type oscillatorType =
  | Sine
  | Square
  | Sawtooth
  | Triange
  | Custom(array(float));

let sampleRandomWave = () => {
  let samples = Array.make(256, 0.0);
  let previousValue = ref(0.0);
  samples[0] = previousValue^;
  for (x in 1 to 255) {
    let newValue = previousValue^ +. Random.float(0.2) -. 0.1;
    samples[x] = newValue;
    previousValue := newValue;
  };
  samples;
};

let setOscillatorType =
    (
      oscillatorType: oscillatorType,
      oscillator: OscillatorNode.t,
      audioCtx: AudioContext.t,
    ) => {
  switch (oscillatorType) {
  | Sine => OscillatorNode.setOscillatorType(oscillator, "sine")
  | Square => OscillatorNode.setOscillatorType(oscillator, "square")
  | Sawtooth => OscillatorNode.setOscillatorType(oscillator, "sawtooth")
  | Triange => OscillatorNode.setOscillatorType(oscillator, "triange")
  | Custom(samples) =>
    let (realCoefficients, imaginaryCoefficients) =
      PeriodicWave.calculateCoefficients(samples);
    let periodicWave =
      AudioContext.createPeriodicWave(
        realCoefficients,
        imaginaryCoefficients,
        {"disableNormalization": false},
        audioCtx,
      );
    OscillatorNode.setPeriodicWave(periodicWave, oscillator);
  };
  oscillator;
};

let make = (oscillatorType: oscillatorType, audioCtx: AudioContext.t) => {
  AudioContext.createOscillator(audioCtx)
  |> setOscillatorType(oscillatorType, _, audioCtx);
};
