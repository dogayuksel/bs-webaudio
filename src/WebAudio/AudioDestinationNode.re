type audioDestinationNode_tag;
type audioDestinationNode =
  AudioNode.audioNode_like(audioDestinationNode_tag);

include AudioNode.Impl({
  type nonrec t = audioDestinationNode;
});
