type envelope = {
  envelopeGain: GainNode.t,
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
  let gainParam = envelope.envelopeGain |> GainNode.gain;
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

let endTrigger = (envelope: t): unit => {
  let currentTime = envelope.audioContext |> AudioContext.getOutputTimestamp();
  let gainParam = envelope.envelopeGain |> GainNode.gain;
  gainParam
  |> AudioParam.cancelScheduledValues(~startTime=currentTime.contextTime);
  gainParam
  |> AudioParam.setTargetAtTime(
       ~target=epsilon_float,
       ~startTime=currentTime.contextTime,
       ~timeConstant=release /. 3.0,
     );
};

let connect = (~target: AudioNode.audioNode_like('a), envelope: t): envelope => {
  envelope.envelopeGain |> GainNode.connect(target);
  envelope;
};

let make = (audioCtx: AudioContext.t): t => {
  let envelopeGain = AudioContext.createGain(audioCtx);
  envelopeGain->GainNode.gain->AudioParam.setValue(epsilon_float);
  {envelopeGain, audioContext: audioCtx};
};
