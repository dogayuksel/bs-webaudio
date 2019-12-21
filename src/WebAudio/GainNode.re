type gainNode_tag;
type gainNode = AudioNode.audioNode_like(gainNode_tag);

type t = gainNode;

include AudioNode.Impl({
  type nonrec t = gainNode;
});

[@bs.new] external createGainNode: unit => gainNode = "GainNode";
[@bs.get] external gain: t => AudioParam.t = "gain";
