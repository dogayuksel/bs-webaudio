let defaultAttack = 0.2;
let defaultDecay = 0.3;
let defaultSustain = 0.1;
let defaultRelease = 1.0;

type envelopeParams = {
  mutable attack: float,
  mutable decay: float,
  mutable sustain: float,
  mutable release: float,
};

type envelope = {
  envelopeParams,
  targetParam: AudioParam.t,
  audioContext: AudioContext.t,
};

type t = envelope;

let trigger = (envelope: t): unit => {
  let {attack, decay, sustain} = envelope.envelopeParams;
  let currentTime = envelope.audioContext |> AudioContext.getOutputTimestamp();
  let attackTime = currentTime.contextTime +. attack;
  envelope.targetParam
  |> AudioParam.cancelScheduledValues(~startTime=currentTime.contextTime);
  envelope.targetParam
  |> AudioParam.setTargetAtTime(
       ~target=1.0,
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
  let {release} = envelope.envelopeParams;
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

type envelopeParam =
  | Attack(float)
  | Decay(float)
  | Sustain(float)
  | Release(float);

let update = (~param: envelopeParam, envelope: t): unit => {
  let {envelopeParams} = envelope;
  switch (param) {
  | Attack(value) => envelopeParams.attack = value
  | Decay(value) => envelopeParams.decay = value
  | Sustain(value) => envelopeParams.sustain = value
  | Release(value) => envelopeParams.release = value
  };
};

let make = (targetParam: AudioParam.t, audioCtx: AudioContext.t): t => {
  targetParam->AudioParam.setValue(epsilon_float);
  let envelopeParams = {
    attack: defaultAttack,
    decay: defaultDecay,
    sustain: defaultSustain,
    release: defaultRelease,
  };
  {envelopeParams, targetParam, audioContext: audioCtx};
};
