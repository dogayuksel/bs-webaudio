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

let setFrequency = (~frequency: float, oscillator: oscillator) => {
  oscillator.oscillatorNode
  ->OscillatorNode.frequency
  ->AudioParam.setValue(frequency);
};

let getFrequency = (oscillator: oscillator): AudioParam.t => {
  oscillator.oscillatorNode->OscillatorNode.frequency;
};

let start = (oscillator: t): oscillator => {
  oscillator.oscillatorNode |> OscillatorNode.start();
  oscillator;
};

let connect =
    (~target: AudioNode.audioNode_like('a), oscillator: t): oscillator => {
  oscillator.oscillatorNode |> OscillatorNode.connect(target);
  oscillator;
};

let make =
    (~oscillatorType: oscillatorType, audioCtx: AudioContext.t): oscillator => {
  let oscillatorNode = audioCtx->AudioContext.createOscillator;
  let setOscillatorNodeType =
    OscillatorNode.setOscillatorNodeType(_, oscillatorNode);
  let oscillatorNode =
    switch (oscillatorType) {
    | Sine => setOscillatorNodeType(DefaultWave("sine"))
    | Square => setOscillatorNodeType(DefaultWave("square"))
    | Sawtooth => setOscillatorNodeType(DefaultWave("sawtooth"))
    | Triange => setOscillatorNodeType(DefaultWave("triangle"))
    | Custom(samples) =>
      let periodicWave = AudioContext.makePeriodicWave(~samples, audioCtx);
      OscillatorNode.setOscillatorNodeType(
        CustomWave(periodicWave),
        oscillatorNode,
      );
    };
  {audioContext: audioCtx, oscillatorNode, oscillatorType};
};
