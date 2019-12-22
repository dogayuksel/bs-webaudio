type envelope;

type t = envelope;

let attack = 0.3;
let decay = 0.7;
let sustain = 0.5;
let release = 1.2;

let trigger =
    (currentTime: AudioContext.audioTimeStamp, gainNode: GainNode.t): unit => {
  let attackTime = currentTime.contextTime +. attack;
  let gainParam = gainNode |> GainNode.gain;
  gainParam
  |> AudioParam.cancelScheduledValues(~startTime=currentTime.contextTime);
  gainParam
  |> AudioParam.setTargetAtTime(
       ~target=0.99,
       ~startTime=currentTime.contextTime +. 0.001,
       ~timeConstant=attack /. 3.0,
     );
  gainParam
  |> AudioParam.setTargetAtTime(
       ~target=sustain,
       ~startTime=attackTime,
       ~timeConstant=decay /. 3.0,
     );
};

let endTrigger =
    (currentTime: AudioContext.audioTimeStamp, gainNode: GainNode.t): unit => {
  let gainParam = gainNode |> GainNode.gain;
  gainParam
  |> AudioParam.cancelScheduledValues(~startTime=currentTime.contextTime);
  gainParam
  |> AudioParam.setTargetAtTime(
       ~target=0.0005,
       ~startTime=currentTime.contextTime,
       ~timeConstant=release /. 3.0,
     );
};
