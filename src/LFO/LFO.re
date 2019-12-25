let make = (audioCtx: AudioContext.t): GainNode.t => {
  let paramOscillator = AudioContext.createGain(audioCtx);
  paramOscillator->GainNode.gain->AudioParam.setValue(0.5);

  let oscillator = Oscillator.make(Sine, audioCtx);
  oscillator.oscillatorNode
  ->OscillatorNode.frequency
  ->AudioParam.setValue(3.0);
  Oscillator.start(oscillator) |> ignore;

  let constantSourceNode = AudioContext.createConstantSource(audioCtx);

  oscillator |> Oscillator.connect(paramOscillator) |> ignore;
  constantSourceNode |> ConstantSourceNode.connect(paramOscillator);

  let lfo = AudioContext.createGain(audioCtx);
  paramOscillator |> GainNode.connectToAudioParam(GainNode.gain(lfo));

  lfo;
};
