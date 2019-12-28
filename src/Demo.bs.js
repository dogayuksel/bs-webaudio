// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as Pervasives from "bs-platform/lib/es6/pervasives.js";
import * as ReactDOMRe from "reason-react/src/ReactDOMRe.js";
import * as LFO$WebAudio from "./LFO/LFO.bs.js";
import * as Knob$WebAudio from "./Components/Knob.bs.js";
import * as Envelope$WebAudio from "./Envelope/Envelope.bs.js";
import * as Oscillator$WebAudio from "./Oscillator/Oscillator.bs.js";
import * as BiquadFilterNode$WebAudio from "./WebAudio/BiquadFilterNode.bs.js";

var audioCtx = new AudioContext();

var lfo = LFO$WebAudio.make(audioCtx);

LFO$WebAudio.setFrequency(10.0, lfo);

LFO$WebAudio.connect(audioCtx.destination, lfo);

var oscOne = Oscillator$WebAudio.connect(lfo.lfo, Oscillator$WebAudio.makeFromRandom(audioCtx));

oscOne.oscillatorGain.gain.value = Pervasives.epsilon_float;

Oscillator$WebAudio.start(oscOne);

var oscTwo = Oscillator$WebAudio.make(/* Sawtooth */2, audioCtx);

var oscTwoFilter = audioCtx.createBiquadFilter();

BiquadFilterNode$WebAudio.setType(oscTwoFilter, /* Lowpass */0);

oscTwoFilter.frequency.value = 370.0;

oscTwoFilter.frequency.setTargetAtTime(300.0, 2.0, 3.0);

Oscillator$WebAudio.connect(oscTwoFilter, oscTwo);

oscTwoFilter.connect(lfo.lfo);

oscTwo.oscillatorGain.gain.value = Pervasives.epsilon_float;

Oscillator$WebAudio.start(oscTwo);

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
    Envelope$WebAudio.trigger(currentTime, oscOne.oscillatorGain);
    return Envelope$WebAudio.trigger(currentTime, oscTwo.oscillatorGain);
  } else {
    return 0;
  }
}

function endTrigger(e) {
  if (e.key === "a") {
    state.a = false;
    var currentTime = audioCtx.getOutputTimestamp();
    Envelope$WebAudio.endTrigger(currentTime, oscOne.oscillatorGain);
    return Envelope$WebAudio.endTrigger(currentTime, oscTwo.oscillatorGain);
  } else {
    return 0;
  }
}

document.addEventListener("keydown", trigger);

document.addEventListener("keyup", endTrigger);

ReactDOMRe.renderToElementWithId(React.createElement(Knob$WebAudio.make, {
          name: "Frequency",
          param: Oscillator$WebAudio.getFrequency(oscOne),
          config: {
            minValue: 1.0,
            maxValue: 22500.0,
            scale: /* Logarithmic */1
          }
        }), "app");

export {
  audioCtx ,
  lfo ,
  oscOne ,
  oscTwo ,
  oscTwoFilter ,
  Keyboard ,
  trigger ,
  endTrigger ,
  
}
/* audioCtx Not a pure module */
