type filter =
  | Lowpass
  | Highpass
  | Bandpass
  | Lowshelf
  | Highself
  | Peaking
  | Notch
  | Allpass;

type biquadFilterNode_tag;
type biquadFilterNode = AudioNode.audioNode_like(biquadFilterNode_tag);

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
