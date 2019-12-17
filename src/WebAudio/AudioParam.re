type audioParam;

[@bs.get] external defaultValue: audioParam => float = "defaultValue";
[@bs.get] external maxValue: audioParam => float = "maxValue";
[@bs.get] external minValue: audioParam => float = "minValue";
[@bs.get] external getValue: audioParam => float = "value";
[@bs.set] external setValue: (audioParam, float) => unit = "value";
