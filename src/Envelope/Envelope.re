type envelope = {
  targetParam: AudioParam.t,
  audioContext: AudioContext.t,
};

type t = envelope;

let attack = 0.2;
let decay = 0.3;
let sustain = 1.5;
let release = 1.0;

let trigger = (envelope: t): unit => {
  let currentTime = envelope.audioContext |> AudioContext.getOutputTimestamp();
  let attackTime = currentTime.contextTime +. attack;
  envelope.targetParam
  |> AudioParam.cancelScheduledValues(~startTime=currentTime.contextTime);
  envelope.targetParam
  |> AudioParam.setTargetAtTime(
       ~target=10.0,
       ~startTime=currentTime.contextTime +. epsilon_float,
       ~timeConstant=attack /. 3.0,
     );
  envelope.targetParam
  |> AudioParam.setTargetAtTime(
       ~target=sustain,
       ~startTime=attackTime,
       ~timeConstant=decay /. 3.0,
     );
};

let endTrigger = (envelope: t): unit => {
  let currentTime = envelope.audioContext |> AudioContext.getOutputTimestamp();
  envelope.targetParam
  |> AudioParam.cancelScheduledValues(~startTime=currentTime.contextTime);
  envelope.targetParam
  |> AudioParam.setTargetAtTime(
       ~target=epsilon_float,
       ~startTime=currentTime.contextTime,
       ~timeConstant=release /. 3.0,
     );
};

let make = (targetParam: AudioParam.t, audioCtx: AudioContext.t): t => {
  targetParam->AudioParam.setValue(epsilon_float);
  {targetParam, audioContext: audioCtx};
};
