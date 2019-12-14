Js.log("Hello, BuckleScript and Reason!");

type audioNode_like ('a);

module AudioParam = {
  type audioParam;
  [@bs.get] external defaultValue: audioParam => float = "defaultValue";
  [@bs.get] external maxValue: audioParam => float = "maxValue";
  [@bs.get] external minValue: audioParam => float = "minValue";
  [@bs.get] external getValue: audioParam => float = "value";
  [@bs.set] external setValue: (audioParam, float) => unit = "value";
}

module AudioNode = {
  module Impl = (T: {type t;}) => {
    [@bs.send] external connect: (T.t, audioNode_like('a)) => unit = "connect";
    [@bs.send] external disconnect: T.t => unit = "disconnect";
  };
  type audioNode_tag;
  type t = audioNode_like(audioNode_tag);
  include Impl({
    type nonrec t = t;
  });
};

module AudioDestinationNode = {
  type audioDestinationNode_tag;
  type audioDestinationNode = audioNode_like(audioDestinationNode_tag);
  include AudioNode.Impl({
    type nonrec t = audioDestinationNode;
  });
};

module GainNode = {
  type gainNode_tag;
  type gainNode = audioNode_like(gainNode_tag);
  include AudioNode.Impl({
    type nonrec t = gainNode;
  });
  [@bs.new] external createGainNode: unit => gainNode = "GainNode";
};

module OscillatorNode = {
  type oscillatorNode_tag;
  type oscillatorNode = audioNode_like(oscillatorNode_tag);
  module Impl = (T: {type t;}) => {
    [@bs.new]
      external createOscillator: unit => oscillatorNode = "OscillatorNode";
    [@bs.send] external start: oscillatorNode => unit = "start";
    [@bs.get] external frequency: oscillatorNode => AudioParam.audioParam = "frequency";
  };
  include AudioNode.Impl({
    type nonrec t = oscillatorNode;
  });
  include Impl({
    type t = oscillatorNode;
  });
};

type audioTimeStamp = {
  contextTime: int,
  performanceTime: int,
};

module AudioContext = {
  type audioContext;
  [@bs.new] external createAudioContext: unit => audioContext = "AudioContext";
  [@bs.send]
    external createOscillator: audioContext => OscillatorNode.oscillatorNode =
    "createOscillator";
  [@bs.send]
    external createGain: audioContext => GainNode.gainNode = "createGain";
  [@bs.get]
    external getDestination:
    audioContext => AudioDestinationNode.audioDestinationNode =
    "destination";
  [@bs.send.pipe: audioContext] external getOutputTimestamp: unit => audioTimeStamp = "getOutputTimestamp";
};

let audioCtx = AudioContext.createAudioContext();
let oscillator = AudioContext.createOscillator(audioCtx);
let gain = AudioContext.createGain(audioCtx);
OscillatorNode.connect(oscillator, gain);
GainNode.connect(gain, AudioContext.getDestination(audioCtx));
OscillatorNode.start(oscillator);

Js.Global.setTimeout(() => {
  let timestamp = audioCtx |> AudioContext.getOutputTimestamp();
  Js.log(timestamp.contextTime);
  Js.log(OscillatorNode.frequency(oscillator) |> AudioParam.defaultValue);
  OscillatorNode.frequency(oscillator) |> AudioParam.setValue(_, 240.0);
}, 3500);
