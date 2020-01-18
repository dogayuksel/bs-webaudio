// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Pervasives from "bs-platform/lib/es6/pervasives.js";
import * as Belt_Option from "bs-platform/lib/es6/belt_Option.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Knob$WebAudio from "./Knob.bs.js";
import * as Slider$WebAudio from "./Slider.bs.js";
import * as Switch$WebAudio from "./Switch.bs.js";
import * as Envelope$WebAudio from "../Envelope/Envelope.bs.js";
import * as Oscillator$WebAudio from "../Oscillator/Oscillator.bs.js";
import * as WaveSampler$WebAudio from "./WaveSampler.bs.js";
import * as ColorPalette$WebAudio from "../ColorPalette.bs.js";
import * as EnvelopeUnit$WebAudio from "./EnvelopeUnit.bs.js";
import * as AppContextProvider$WebAudio from "./AppContextProvider.bs.js";

function OscillatorUnit(Props) {
  var name = Props.name;
  var targetOutput = Props.targetOutput;
  var match = Props.alone;
  var alone = match !== undefined ? match : false;
  var appContext = React.useContext(AppContextProvider$WebAudio.appContext);
  var match$1 = React.useState((function () {
          return false;
        }));
  var setOscillatorOn = match$1[1];
  var oscillatorOn = match$1[0];
  var oscillator = React.useRef(undefined);
  var envelope = React.useRef(undefined);
  var cleanUp = function (param) {
    Belt_Option.map(oscillator.current, Oscillator$WebAudio.cleanUp);
    Belt_Option.map(envelope.current, appContext.removeFromTriggerTargets);
    return /* () */0;
  };
  var toggleOscillator = React.useCallback((function (param) {
          if (oscillatorOn === false) {
            var match = appContext.audioContext;
            if (match !== undefined) {
              var audioContext = Caml_option.valFromOption(match);
              var target = targetOutput !== undefined ? Caml_option.valFromOption(targetOutput) : audioContext.destination;
              var osc = Oscillator$WebAudio.start(Oscillator$WebAudio.connect(target, (function (eta) {
                            return Oscillator$WebAudio.make(undefined, eta);
                          })(audioContext)));
              oscillator.current = osc;
              var env = Envelope$WebAudio.make(Oscillator$WebAudio.getEnvelopeGain(osc), audioContext);
              Curry._1(appContext.addToTriggerTargets, env);
              envelope.current = env;
              Curry._1(setOscillatorOn, (function (param) {
                      return true;
                    }));
              return /* () */0;
            } else {
              console.log("Missing Audio Context");
              return /* () */0;
            }
          } else {
            cleanUp(/* () */0);
            return Curry._1(setOscillatorOn, (function (param) {
                          return false;
                        }));
          }
        }), /* tuple */[
        oscillatorOn,
        appContext.audioContext,
        targetOutput
      ]);
  React.useEffect((function () {
          if (alone) {
            Curry._1(toggleOscillator, /* () */0);
          }
          return (function (param) {
                    return cleanUp(/* () */0);
                  });
        }), ([]));
  var match$2 = oscillator.current;
  var match$3 = envelope.current;
  var tmp;
  if (match$2 !== undefined && match$3 !== undefined) {
    var osc = match$2;
    tmp = React.createElement(React.Fragment, undefined, React.createElement(WaveSampler$WebAudio.make, {
              setWaveCallback: (function (wave) {
                  return Oscillator$WebAudio.setOscillatorType(/* Custom */[wave], osc);
                })
            }), React.createElement("div", {
              className: "unit-container"
            }, React.createElement(Knob$WebAudio.make, {
                  name: "FREQUENCY",
                  config: {
                    minValue: 1.0,
                    maxValue: 18000.0,
                    scale: /* Logarithmic */1,
                    size: 120
                  },
                  initialParamValue: Oscillator$WebAudio.getFrequency(osc).value,
                  setParamValue: (function (frequency) {
                      return Oscillator$WebAudio.setFrequency(frequency, osc);
                    })
                }), React.createElement(Slider$WebAudio.make, {
                  name: "GAIN",
                  param: Oscillator$WebAudio.getOscillatorGain(osc),
                  config: {
                    minValue: Pervasives.epsilon_float,
                    maxValue: 1.0
                  }
                })), React.createElement(EnvelopeUnit$WebAudio.make, {
              envelope: match$3
            }));
  } else {
    tmp = null;
  }
  return React.createElement("div", {
              style: {
                backgroundColor: ColorPalette$WebAudio.green
              }
            }, React.createElement("h3", {
                  className: "unit-label"
                }, name), React.createElement("div", {
                  className: "unit-container"
                }, React.createElement(Switch$WebAudio.make, {
                      isOn: oscillatorOn,
                      toggle: toggleOscillator,
                      children: "START"
                    })), tmp);
}

var make = OscillatorUnit;

export {
  make ,
  
}
/* react Not a pure module */
