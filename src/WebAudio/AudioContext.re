type audioTimeStamp = {
  contextTime: float,
  performanceTime: float,
};

type audioContext;

[@bs.new] external createAudioContext: unit => audioContext = "AudioContext";

[@bs.send]
external createOscillator: audioContext => OscillatorNode.oscillatorNode =
  "createOscillator";

[@bs.send]
external createGain: audioContext => GainNode.gainNode = "createGain";

[@bs.send]
external createBiquadFilter: audioContext => BiquadFilterNode.biquadFilterNode =
  "createBiquadFilter";

[@bs.get]
external getDestination:
  audioContext => AudioDestinationNode.audioDestinationNode =
  "destination";

[@bs.send.pipe: audioContext]
external getOutputTimestamp: unit => audioTimeStamp = "getOutputTimestamp";

[@bs.send]
external createPeriodicWave:
  (
    audioContext,
    Js_typed_array.Float32Array.typed_array(float),
    Js_typed_array.Float32Array.typed_array(float),
    {.. "disableNormalization": bool}
  ) =>
  PeriodicWave.periodicWave =
  "createPeriodicWave";
