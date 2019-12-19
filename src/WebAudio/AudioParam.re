type audioParam;

[@bs.get] external defaultValue: audioParam => float = "defaultValue";
[@bs.get] external maxValue: audioParam => float = "maxValue";
[@bs.get] external minValue: audioParam => float = "minValue";
[@bs.get] external getValue: audioParam => float = "value";
[@bs.set] external setValue: (audioParam, float) => unit = "value";

[@bs.send.pipe: audioParam]
external setValueAtTime: (~value: float, ~startTime: float) => unit =
  "setValueAtTime";

[@bs.send.pipe: audioParam]
external linearRampToValueAtTime: (~value: float, ~endTime: float) => unit =
  "linearRampToValueAtTime";

[@bs.send.pipe: audioParam]
external exponentialRampToValueAtTime: (~value: float, ~endTime: float) => unit =
  "exponentialRampToValueAtTime";

[@bs.send.pipe: audioParam]
external setTargetAtTime:
  (~target: float, ~startTime: float, ~timeConstant: float) => unit =
  "setTargetAtTime";

[@bs.send.pipe: audioParam]
external setValueCurveAtTime:
  (~curve: array(float), ~startTime: float, ~duration: float) => unit =
  "setValueCurveAtTime";

[@bs.send.pipe: audioParam]
external cancelScheduledValues: (~startTime: float) => unit =
  "cancelScheduledValues";

[@bs.send.pipe: audioParam]
external cancelAndHoldAtTime: (~cancelTime: float) => unit =
  "cancelAndHoldAtTime";
