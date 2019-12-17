type audioNode_like('a);

module Impl = (T: {type t;}) => {
  [@bs.send] external connect: (T.t, audioNode_like('a)) => unit = "connect";
  [@bs.send] external disconnect: T.t => unit = "disconnect";
};
type audioNode_tag;
type t = audioNode_like(audioNode_tag);
include Impl({
  type nonrec t = t;
});
