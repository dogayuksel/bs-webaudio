type gainNode_tag;
type gainNode = AudioNode.audioNode_like(gainNode_tag);

include AudioNode.Impl({
  type nonrec t = gainNode;
});
[@bs.new] external createGainNode: unit => gainNode = "GainNode";
