type lfo = {
  oscillator: Oscillator.t,
  lfo: GainNode.t,
};

type t = lfo;

let defaultFrequency = 3.0;

let make = (audioCtx: AudioContext.t): lfo => {
  let paramOscillator = AudioContext.createGain(audioCtx);
  paramOscillator->GainNode.gain->AudioParam.setValue(0.5);

  let oscillator = Oscillator.make(~oscillatorType=Sine, audioCtx);
  oscillator.oscillatorNode
  ->OscillatorNode.frequency
  ->AudioParam.setValue(defaultFrequency);
  Oscillator.start(oscillator) |> ignore;

  let constantSourceNode = AudioContext.createConstantSource(audioCtx);

  oscillator |> Oscillator.connect(~target=paramOscillator) |> ignore;
  constantSourceNode |> ConstantSourceNode.connect(paramOscillator);

  let lfo = AudioContext.createGain(audioCtx);
  paramOscillator |> GainNode.connectToAudioParam(GainNode.gain(lfo));

  {lfo, oscillator};
};

let connect = (~target: AudioNode.audioNode_like('a), lfo: lfo) => {
  lfo.lfo |> GainNode.connect(target);
};

let setFrequency = (~frequency: float, lfo: lfo) => {
  lfo.oscillator |> Oscillator.setFrequency(~frequency);
};
