type audioNode_like('a);

module AudioParam = {
  type audioParam;
  [@bs.get] external defaultValue: audioParam => float = "defaultValue";
  [@bs.get] external maxValue: audioParam => float = "maxValue";
  [@bs.get] external minValue: audioParam => float = "minValue";
  [@bs.get] external getValue: audioParam => float = "value";
  [@bs.set] external setValue: (audioParam, float) => unit = "value";
};

module AudioNode = {
  module Impl = (T: {type t;}) => {
    [@bs.send]
    external connect: (T.t, audioNode_like('a)) => unit = "connect";
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

module PeriodicWave = {
  type periodicWave;
};

module OscillatorNode = {
  type oscillatorNode_tag;
  type oscillatorNode = audioNode_like(oscillatorNode_tag);
  module Impl = (T: {type t;}) => {
    [@bs.new] external createOscillator: unit => T.t = "OscillatorNode";
    [@bs.send] external start: T.t => unit = "start";
    [@bs.send] external stop: T.t => unit = "stop";
    [@bs.send.pipe: T.t] external stopAt: float => unit = "stop";
    [@bs.get] external frequency: T.t => AudioParam.audioParam = "frequency";
    [@bs.send]
    external setPeriodicWave: (T.t, PeriodicWave.periodicWave) => unit =
      "setPeriodicWave";
  };
  include AudioNode.Impl({
    type nonrec t = oscillatorNode;
  });
  include Impl({
    type t = oscillatorNode;
  });
};

type filter =
  | Lowpass
  | Highpass
  | Bandpass
  | Lowshelf
  | Highself
  | Peaking
  | Notch
  | Allpass;

module BiquadFilterNode = {
  type biquadFilterNode_tag;
  type biquadFilterNode = audioNode_like(biquadFilterNode_tag);
  [@bs.set]
  external assignfilterType: (biquadFilterNode, string) => unit = "type";
  [@bs.get]
  external frequency: biquadFilterNode => AudioParam.audioParam = "frequency";
  let setType = (filterNode: biquadFilterNode, filterType: filter) =>
    switch (filterType) {
    | Lowpass => assignfilterType(filterNode, "lowpass")
    | Highpass => assignfilterType(filterNode, "highpass")
    | Bandpass => assignfilterType(filterNode, "bandpass")
    | _ => Js.log("Filter type not implemented yet")
    };
  include AudioNode.Impl({
    type t = biquadFilterNode;
  });
};

type audioTimeStamp = {
  contextTime: float,
  performanceTime: float,
};

module AudioContext = {
  type audioContext;
  [@bs.new] external createAudioContext: unit => audioContext = "AudioContext";
  [@bs.send]
  external createOscillator: audioContext => OscillatorNode.oscillatorNode =
    "createOscillator";
  [@bs.send]
  external createGain: audioContext => GainNode.gainNode = "createGain";
  [@bs.send]
  external createBiquadFilter:
    audioContext => BiquadFilterNode.biquadFilterNode =
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
};

let audioCtx = AudioContext.createAudioContext();
let oscillator = AudioContext.createOscillator(audioCtx);
let biquadFilter = AudioContext.createBiquadFilter(audioCtx);
BiquadFilterNode.setType(biquadFilter, Lowpass);
BiquadFilterNode.frequency(biquadFilter)->AudioParam.setValue(170.0);
OscillatorNode.connect(oscillator, biquadFilter);
let gain = AudioContext.createGain(audioCtx);
BiquadFilterNode.connect(biquadFilter, gain);

let real = Js_typed_array.Float32Array.fromLength(5);
let imag = Js_typed_array.Float32Array.fromLength(5);
Js_typed_array2.Float32Array.unsafe_set(real, 0, 0.0);
Js_typed_array2.Float32Array.unsafe_set(real, 1, 1.0);
Js_typed_array2.Float32Array.unsafe_set(real, 2, 1.0);
Js_typed_array2.Float32Array.unsafe_set(real, 3, 0.5);
Js_typed_array2.Float32Array.unsafe_set(real, 4, 0.2);
Js_typed_array2.Float32Array.unsafe_set(imag, 0, 0.0);
Js_typed_array2.Float32Array.unsafe_set(imag, 1, 0.0);
Js_typed_array2.Float32Array.unsafe_set(imag, 2, 0.0);
Js_typed_array2.Float32Array.unsafe_set(imag, 3, 0.2);
Js_typed_array2.Float32Array.unsafe_set(imag, 4, 0.4);
let periodicWave =
  AudioContext.createPeriodicWave(
    audioCtx,
    real,
    imag,
    {"disableNormalization": true},
  );
OscillatorNode.setPeriodicWave(oscillator, periodicWave);

GainNode.connect(gain, AudioContext.getDestination(audioCtx));
OscillatorNode.start(oscillator);

Js.Global.setTimeout(
  () => {
    BiquadFilterNode.frequency(biquadFilter)->AudioParam.setValue(320.0);
    let timestamp = audioCtx |> AudioContext.getOutputTimestamp();
    Js.log(timestamp.contextTime);
    Js.log(OscillatorNode.frequency(oscillator) |> AudioParam.defaultValue);
    OscillatorNode.frequency(oscillator) |> AudioParam.setValue(_, 240.0);
    oscillator |> OscillatorNode.stopAt(timestamp.contextTime +. 2.0);
  },
  2500,
);
