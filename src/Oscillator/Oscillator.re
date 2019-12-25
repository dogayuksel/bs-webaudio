type oscillatorType =
  | Sine
  | Square
  | Sawtooth
  | Triange
  | Custom(array(float));

type oscillator = {
  audioContext: AudioContext.t,
  oscillatorNode: OscillatorNode.t,
  oscillatorType,
};

type t = oscillator;

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

let setOscillatorNodeType =
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

let start = (oscillator: t): oscillator => {
  oscillator.oscillatorNode |> OscillatorNode.start();
  oscillator;
};

let connect =
    (target: AudioNode.audioNode_like('a), oscillator: t): oscillator => {
  oscillator.oscillatorNode |> OscillatorNode.connect(target);
  oscillator;
};

let make =
    (oscillatorType: oscillatorType, audioCtx: AudioContext.t): oscillator => {
  let oscillatorNode =
    AudioContext.createOscillator(audioCtx)
    |> setOscillatorNodeType(oscillatorType, _, audioCtx);
  {audioContext: audioCtx, oscillatorNode, oscillatorType};
};
