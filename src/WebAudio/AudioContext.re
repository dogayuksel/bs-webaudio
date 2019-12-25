type audioTimeStamp = {
  contextTime: float,
  performanceTime: float,
};

type audioContext;
type t = audioContext;

[@bs.new] external createAudioContext: unit => t = "AudioContext";

[@bs.send]
external createOscillator: t => OscillatorNode.t = "createOscillator";

[@bs.send] external createGain: t => GainNode.t = "createGain";

[@bs.send]
external createBiquadFilter: t => BiquadFilterNode.t = "createBiquadFilter";

[@bs.send]
external createConstantSource: t => ConstantSourceNode.t =
  "createConstantSource";

[@bs.get] external getDestination: t => AudioDestinationNode.t = "destination";

[@bs.send.pipe: t]
external getOutputTimestamp: unit => audioTimeStamp = "getOutputTimestamp";

[@bs.send.pipe: t]
external createPeriodicWave:
  (
    Js_typed_array.Float32Array.typed_array(float),
    Js_typed_array.Float32Array.typed_array(float),
    {.. "disableNormalization": bool}
  ) =>
  PeriodicWave.t =
  "createPeriodicWave";
