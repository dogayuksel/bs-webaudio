type oscillator = {
  audioContext: AudioContext.t,
  oscillatorNode: OscillatorNode.t,
  oscillatorType: OscillatorNode.oscillatorNodeType,
  oscillatorGain: GainNode.t,
};

type t = oscillator;

let sampleRandomWave = (): array(float) => {
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

let setFrequency = (~frequency: float, oscillator: oscillator): unit => {
  oscillator.oscillatorNode
  ->OscillatorNode.frequency
  ->AudioParam.setValue(frequency);
};

let getFrequency = (oscillator: oscillator): AudioParam.t => {
  oscillator.oscillatorNode->OscillatorNode.frequency;
};

let getGain = (oscillator: oscillator): AudioParam.t => {
  oscillator.oscillatorGain |> GainNode.gain;
};

let start = (oscillator: t): oscillator => {
  oscillator.oscillatorNode |> OscillatorNode.start();
  oscillator;
};

let connect =
    (~target: AudioNode.audioNode_like('a), oscillator: t): oscillator => {
  oscillator.oscillatorGain |> GainNode.connect(target);
  oscillator;
};

let setOscillatorType =
    (~oscillatorType: OscillatorNode.oscillatorNodeType, oscillator: t): unit => {
  oscillator.oscillatorNode
  |> OscillatorNode.setOscillatorNodeType(oscillatorType);
};

let make =
    (
      ~oscillatorType: OscillatorNode.oscillatorNodeType=Sine,
      audioCtx: AudioContext.t,
    )
    : oscillator => {
  let oscillatorNode = audioCtx->AudioContext.createOscillator;
  let oscillatorGain = audioCtx->AudioContext.createGain;
  oscillatorNode |> OscillatorNode.connect(oscillatorGain);
  let oscillator = {
    audioContext: audioCtx,
    oscillatorNode,
    oscillatorType,
    oscillatorGain,
  };
  oscillator |> setOscillatorType(~oscillatorType);
  oscillator;
};

let makeFromRandom = (audioCtx: AudioContext.t) => {
  let oscillator = audioCtx->make;
  let periodicWave =
    audioCtx |> AudioContext.makePeriodicWave(~samples=sampleRandomWave());
  oscillator |> setOscillatorType(~oscillatorType=Custom(periodicWave));
  oscillator;
};
