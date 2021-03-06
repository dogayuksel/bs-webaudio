// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as List from "bs-platform/lib/es6/list.js";
import * as $$Array from "bs-platform/lib/es6/array.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Caml_array from "bs-platform/lib/es6/caml_array.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Knob$WebAudio from "./Knob.bs.js";
import * as Switch$WebAudio from "./Switch.bs.js";
import * as Envelope$WebAudio from "../Envelope/Envelope.bs.js";
import * as ColorPalette$WebAudio from "../ColorPalette.bs.js";
import * as AppContextProvider$WebAudio from "./AppContextProvider.bs.js";

function Sequencer(Props) {
  var appContext = React.useContext(AppContextProvider$WebAudio.appContext);
  var match = React.useState(function () {
        return Caml_array.caml_make_vect(8, false);
      });
  var setSequencer = match[1];
  var sequencer = match[0];
  var match$1 = React.useState(function () {
        return false;
      });
  var setSequencerOn = match$1[1];
  var sequencerOn = match$1[0];
  var match$2 = React.useState(function () {
        return -1;
      });
  var setActiveStep = match$2[1];
  var activeStep = match$2[0];
  var lastTrigger = React.useRef(undefined);
  var match$3 = React.useState(function () {
        return 120.0;
      });
  var setBpm = match$3[1];
  var bpm = match$3[0];
  var toggleSequencerOn = function (param) {
    return Curry._1(setSequencerOn, (function (isOn) {
                  if (isOn === true) {
                    Curry._1(setActiveStep, (function (param) {
                            return -1;
                          }));
                    lastTrigger.current = undefined;
                    return false;
                  } else {
                    return true;
                  }
                }));
  };
  var triggerTargets = function (targets) {
    List.iter(Envelope$WebAudio.trigger, targets);
    setTimeout((function (param) {
            return List.iter(Envelope$WebAudio.endTrigger, appContext.triggerTargets);
          }), 120);
    
  };
  React.useEffect((function () {
          var match = appContext.audioContext;
          if (match === undefined) {
            return ;
          }
          if (!sequencerOn) {
            return ;
          }
          var audioContext = Caml_option.valFromOption(match);
          var duration = 60.0 / bpm * 250.0;
          var interval = setInterval((function (param) {
                  var timeStamp = audioContext.getOutputTimestamp();
                  lastTrigger.current = timeStamp.performanceTime;
                  var sequencerLength = sequencer.length;
                  return Curry._1(setActiveStep, (function (step) {
                                var newStep = step >= (sequencerLength - 1 | 0) ? 0 : step + 1 | 0;
                                if (Caml_array.caml_array_get(sequencer, newStep) === true) {
                                  triggerTargets(appContext.triggerTargets);
                                }
                                return newStep;
                              }));
                }), duration | 0);
          return (function (param) {
                    clearInterval(interval);
                    
                  });
        }), [
        appContext.triggerTargets,
        sequencerOn,
        sequencer,
        bpm
      ]);
  var expandSequencer = function (param) {
    var currentLength = sequencer.length;
    var newSequence = Caml_array.caml_make_vect((currentLength << 1), false);
    $$Array.iteri((function (ind, value) {
            return Caml_array.caml_array_set(newSequence, ind, value);
          }), sequencer);
    Curry._1(setSequencer, (function (param) {
            return newSequence;
          }));
    
  };
  var shrinkSequencer = function (param) {
    var currentLength = sequencer.length;
    if (currentLength === 4) {
      return ;
    }
    var newSequence = Caml_array.caml_make_vect(currentLength / 2 | 0, false);
    $$Array.iteri((function (ind, param) {
            return Caml_array.caml_array_set(newSequence, ind, Caml_array.caml_array_get(sequencer, ind));
          }), newSequence);
    Curry._1(setSequencer, (function (param) {
            return newSequence;
          }));
    
  };
  return React.createElement("div", {
              className: "unit-group-container"
            }, React.createElement("h2", {
                  className: "unit-label"
                }, "SEQUENCER"), React.createElement("div", {
                  className: "row-group-container"
                }, React.createElement("div", undefined, React.createElement("div", {
                          className: "row-group-container"
                        }, React.createElement("div", {
                              className: "unit-container"
                            }, React.createElement(Switch$WebAudio.make, {
                                  isOn: sequencerOn,
                                  toggle: toggleSequencerOn,
                                  children: "START"
                                }))), React.createElement("div", {
                          className: "row-group-container"
                        }, React.createElement("div", {
                              className: "unit-container"
                            }, React.createElement(Knob$WebAudio.make, {
                                  name: "BPM",
                                  config: {
                                    minValue: 10.0,
                                    maxValue: 400.0,
                                    scale: /* Linear */0,
                                    size: 30
                                  },
                                  initialParamValue: bpm,
                                  setParamValue: (function (value) {
                                      return Curry._1(setBpm, (function (param) {
                                                    return value;
                                                  }));
                                    })
                                }))), React.createElement("div", {
                          className: "row-group-container"
                        }, React.createElement("div", {
                              className: "unit-container",
                              onClick: expandSequencer
                            }, React.createElement("div", {
                                  style: {
                                    fontWeight: "bold"
                                  }
                                }, "x2")), React.createElement("div", {
                              className: "unit-container",
                              onClick: shrinkSequencer
                            }, React.createElement("div", {
                                  style: {
                                    fontWeight: "bold"
                                  }
                                }, "/2")))), React.createElement("div", {
                      className: "unit-container",
                      style: {
                        display: "grid",
                        gridTemplateColumns: "repeat(8, auto)"
                      }
                    }, $$Array.mapi((function (ind, value) {
                            return React.createElement("div", {
                                        key: String(ind),
                                        style: {
                                          backgroundColor: value ? ColorPalette$WebAudio.black : ColorPalette$WebAudio.white,
                                          display: "flex",
                                          height: "50px",
                                          margin: "5px",
                                          width: "40px",
                                          alignItems: "center",
                                          justifyContent: "center"
                                        },
                                        onClick: (function (param) {
                                            return Curry._1(setSequencer, (function (s) {
                                                          Caml_array.caml_array_set(s, ind, !Caml_array.caml_array_get(s, ind));
                                                          return $$Array.copy(s);
                                                        }));
                                          })
                                      }, activeStep === ind ? React.createElement("div", {
                                              style: {
                                                backgroundColor: ColorPalette$WebAudio.green,
                                                height: "20px",
                                                width: "20px",
                                                borderRadius: "20px"
                                              }
                                            }) : null);
                          }), sequencer))));
}

var make = Sequencer;

export {
  make ,
  
}
/* react Not a pure module */
