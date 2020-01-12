// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Random from "bs-platform/lib/es6/random.js";
import * as Caml_array from "bs-platform/lib/es6/caml_array.js";
import * as AudioContext$WebAudio from "../WebAudio/AudioContext.bs.js";
import * as OscillatorNode$WebAudio from "../WebAudio/OscillatorNode.bs.js";

function sampleRandomWave(param) {
  var samples = Caml_array.caml_make_vect(256, 0.0);
  var previousValue = 0.0;
  Caml_array.caml_array_set(samples, 0, previousValue);
  for(var x = 1; x <= 255; ++x){
    var newValue = previousValue + Random.$$float(0.2) - 0.1;
    Caml_array.caml_array_set(samples, x, newValue);
    previousValue = newValue;
  }
  return samples;
}

function setFrequency(frequency, oscillator) {
  oscillator.oscillatorNode.frequency.value = frequency;
  return /* () */0;
}

function getFrequency(oscillator) {
  return oscillator.oscillatorNode.frequency;
}

function getOscillatorGain(oscillator) {
  return oscillator.outputGain.gain;
}

function getEnvelopeGain(oscillator) {
  return oscillator.envelopeGain.gain;
}

function start(oscillator) {
  oscillator.oscillatorNode.start();
  return oscillator;
}

function connect(target, oscillator) {
  oscillator.outputGain.connect(target);
  return oscillator;
}

function disconnect(oscillator) {
  oscillator.outputGain.disconnect();
  return /* () */0;
}

function setOscillatorType(oscillatorType, oscillator) {
  return OscillatorNode$WebAudio.setOscillatorNodeType(oscillatorType, oscillator.oscillatorNode);
}

function make($staropt$star, audioCtx) {
  var oscillatorType = $staropt$star !== undefined ? $staropt$star : /* Sine */0;
  var oscillatorNode = audioCtx.createOscillator();
  var envelopeGain = audioCtx.createGain();
  oscillatorNode.connect(envelopeGain);
  var outputGain = audioCtx.createGain();
  envelopeGain.connect(outputGain);
  var oscillator = {
    audioContext: audioCtx,
    oscillatorNode: oscillatorNode,
    oscillatorType: oscillatorType,
    envelopeGain: envelopeGain,
    outputGain: outputGain
  };
  OscillatorNode$WebAudio.setOscillatorNodeType(oscillatorType, oscillatorNode);
  return oscillator;
}

function makeFromRandom(audioCtx) {
  var oscillator = make(undefined, audioCtx);
  var periodicWave = AudioContext$WebAudio.makePeriodicWave(sampleRandomWave(/* () */0), audioCtx);
  OscillatorNode$WebAudio.setOscillatorNodeType(/* Custom */[periodicWave], oscillator.oscillatorNode);
  return oscillator;
}

export {
  sampleRandomWave ,
  setFrequency ,
  getFrequency ,
  getOscillatorGain ,
  getEnvelopeGain ,
  start ,
  connect ,
  disconnect ,
  setOscillatorType ,
  make ,
  makeFromRandom ,
  
}
/* AudioContext-WebAudio Not a pure module */
