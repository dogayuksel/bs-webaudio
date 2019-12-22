type envelope;

type t = envelope;

let attack = 0.2;
let decay = 0.3;
let sustain = 1.5;
let release = 1.0;

let trigger =
    (currentTime: AudioContext.audioTimeStamp, gainNode: GainNode.t): unit => {
  let attackTime = currentTime.contextTime +. attack;
  let gainParam = gainNode |> GainNode.gain;
  gainParam
  |> AudioParam.cancelScheduledValues(~startTime=currentTime.contextTime);
  gainParam
  |> AudioParam.setTargetAtTime(
       ~target=10.0,
       ~startTime=currentTime.contextTime +. epsilon_float,
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
       ~target=epsilon_float,
       ~startTime=currentTime.contextTime,
       ~timeConstant=release /. 3.0,
     );
};
