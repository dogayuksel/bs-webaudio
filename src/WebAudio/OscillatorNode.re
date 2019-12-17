type oscillatorNode_tag;
type oscillatorNode = AudioNode.audioNode_like(oscillatorNode_tag);

module Impl = (T: {type t;}) => {
  [@bs.new] external createOscillator: unit => T.t = "OscillatorNode";
  [@bs.send] external start: T.t => unit = "start";
  [@bs.send] external stop: T.t => unit = "stop";
  [@bs.send.pipe: T.t] external stopAt: float => unit = "stop";
  [@bs.get] external frequency: T.t => AudioParam.audioParam = "frequency";
  [@bs.send.pipe: T.t]
  external setPeriodicWave: PeriodicWave.periodicWave => unit =
    "setPeriodicWave";
};

include AudioNode.Impl({
  type nonrec t = oscillatorNode;
});

include Impl({
  type t = oscillatorNode;
});
