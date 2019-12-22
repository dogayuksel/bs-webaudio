// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Envelope$WebAudio = require("./Envelope/Envelope.bs.js");
var Oscillator$WebAudio = require("./Oscillator/Oscillator.bs.js");
var BiquadFilterNode$WebAudio = require("./WebAudio/BiquadFilterNode.bs.js");

var audioCtx = new AudioContext();

var sineOscillator = Oscillator$WebAudio.make(/* Sine */0, audioCtx);

var biquadFilter = audioCtx.createBiquadFilter();

var sineGain = audioCtx.createGain();

sineOscillator.connect(biquadFilter);

BiquadFilterNode$WebAudio.setType(biquadFilter, /* Lowpass */0);

biquadFilter.connect(sineGain);

sineGain.connect(audioCtx.destination);

sineGain.gain.value = 0.0005;

sineOscillator.start();

sineOscillator.frequency.setValueCurveAtTime(/* array */[
      470.0,
      370.0,
      470.0
    ], 2.0, 2.5);

biquadFilter.frequency.value = 470.0;

biquadFilter.frequency.setTargetAtTime(450.0, 2.0, 1.0);

var sawOscillator = Oscillator$WebAudio.make(/* SawTooth */1, audioCtx);

var sawGain = audioCtx.createGain();

sawOscillator.connect(sawGain);

sawGain.connect(audioCtx.destination);

sawGain.gain.value = 0.0005;

sawOscillator.start();

var state = {
  a: false
};

var Keyboard = {
  state: state
};

function trigger(e) {
  if (state.a === false && e.key === "a") {
    state.a = true;
    var currentTime = audioCtx.getOutputTimestamp();
    Envelope$WebAudio.trigger(currentTime, sineGain);
    return Envelope$WebAudio.trigger(currentTime, sawGain);
  } else {
    return 0;
  }
}

function endTrigger(e) {
  if (e.key === "a") {
    state.a = false;
    var currentTime = audioCtx.getOutputTimestamp();
    Envelope$WebAudio.endTrigger(currentTime, sineGain);
    return Envelope$WebAudio.endTrigger(currentTime, sawGain);
  } else {
    return 0;
  }
}

document.addEventListener("keydown", trigger);

document.addEventListener("keyup", endTrigger);

exports.audioCtx = audioCtx;
exports.sineOscillator = sineOscillator;
exports.biquadFilter = biquadFilter;
exports.sineGain = sineGain;
exports.sawOscillator = sawOscillator;
exports.sawGain = sawGain;
exports.Keyboard = Keyboard;
exports.trigger = trigger;
exports.endTrigger = endTrigger;
/* audioCtx Not a pure module */
