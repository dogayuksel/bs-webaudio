type lfo = {
  lfoOscillator: Oscillator.t,
  lfoGain: GainNode.t,
  audioContext: AudioContext.t,
};

type t = lfo;

let defaultFrequency = 3.0;

let make = (audioCtx: AudioContext.t): t => {
  let paramOscillator = AudioContext.createGain(audioCtx);
  paramOscillator->GainNode.gain->AudioParam.setValue(0.5);

  let lfoOscillator = Oscillator.make(~oscillatorType=Sine, audioCtx);
  lfoOscillator.oscillatorNode
  ->OscillatorNode.frequency
  ->AudioParam.setValue(defaultFrequency);
  Oscillator.start(lfoOscillator) |> ignore;

  let constantSourceNode = AudioContext.createConstantSource(audioCtx);

  lfoOscillator |> Oscillator.connect(~target=paramOscillator) |> ignore;
  constantSourceNode |> ConstantSourceNode.connect(paramOscillator);

  let lfoGain = AudioContext.createGain(audioCtx);
  paramOscillator |> GainNode.connectToAudioParam(GainNode.gain(lfoGain));

  {lfoGain, lfoOscillator, audioContext: audioCtx};
};

let connect = (~target: AudioNode.audioNode_like('a), lfo: t) => {
  lfo.lfoGain |> GainNode.connect(target);
  lfo;
};

let setFrequency = (~frequency: float, lfo: t) => {
  lfo.lfoOscillator |> Oscillator.setFrequency(~frequency);
  lfo;
};
