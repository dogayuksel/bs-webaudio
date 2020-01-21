// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as List from "bs-platform/lib/es6/list.js";
import * as $$Array from "bs-platform/lib/es6/array.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Caml_array from "bs-platform/lib/es6/caml_array.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Switch$WebAudio from "./Switch.bs.js";
import * as Envelope$WebAudio from "../Envelope/Envelope.bs.js";
import * as ColorPalette$WebAudio from "../ColorPalette.bs.js";
import * as AppContextProvider$WebAudio from "./AppContextProvider.bs.js";

function Keyboard(Props) {
  var appContext = React.useContext(AppContextProvider$WebAudio.appContext);
  var match = React.useState((function () {
          return Caml_array.caml_make_vect(8, false);
        }));
  var setSequencer = match[1];
  var sequencer = match[0];
  var match$1 = React.useState((function () {
          return false;
        }));
  var setSequencerOn = match$1[1];
  var sequencerOn = match$1[0];
  var match$2 = React.useState((function () {
          return -1;
        }));
  var setActiveStep = match$2[1];
  var activeStep = match$2[0];
  var match$3 = React.useState((function () {
          return false;
        }));
  var setKeyPress = match$3[1];
  var lastTrigger = React.useRef(undefined);
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
  var trigger = function (e) {
    if (e.key === "a") {
      return Curry._1(setKeyPress, (function (key) {
                    if (key === false) {
                      List.iter(Envelope$WebAudio.trigger, appContext.triggerTargets);
                      return true;
                    } else {
                      return true;
                    }
                  }));
    } else {
      return 0;
    }
  };
  var endTrigger = function (e) {
    if (e.key === "a") {
      return Curry._1(setKeyPress, (function (param) {
                    List.iter(Envelope$WebAudio.endTrigger, appContext.triggerTargets);
                    return false;
                  }));
    } else {
      return 0;
    }
  };
  React.useEffect((function () {
          document.addEventListener("keydown", trigger);
          document.addEventListener("keyup", endTrigger);
          return (function (param) {
                    document.removeEventListener("keydown", trigger);
                    document.removeEventListener("keydown", endTrigger);
                    return /* () */0;
                  });
        }), /* array */[appContext.triggerTargets]);
  var triggerTargets = function (targets) {
    List.iter(Envelope$WebAudio.trigger, targets);
    setTimeout((function (param) {
            return List.iter(Envelope$WebAudio.endTrigger, appContext.triggerTargets);
          }), 120);
    return /* () */0;
  };
  React.useEffect((function (param) {
          var match = appContext.audioContext;
          if (match !== undefined && sequencerOn) {
            var audioContext = Caml_option.valFromOption(match);
            var interval = setInterval((function (param) {
                    var timeStamp = audioContext.getOutputTimestamp();
                    lastTrigger.current = timeStamp.performanceTime;
                    return Curry._1(setActiveStep, (function (step) {
                                  var match = step === 7;
                                  var newStep = match ? 0 : step + 1 | 0;
                                  if (Caml_array.caml_array_get(sequencer, newStep) === true) {
                                    triggerTargets(appContext.triggerTargets);
                                  }
                                  return newStep;
                                }));
                  }), 500);
            return (function (param) {
                      clearInterval(interval);
                      return /* () */0;
                    });
          }
          
        }), /* tuple */[
        appContext.triggerTargets,
        sequencerOn,
        sequencer
      ]);
  return React.createElement("div", {
              className: "unit-group-container"
            }, React.createElement("h2", {
                  className: "unit-label"
                }, "SEQUENCER"), React.createElement("div", {
                  className: "row-group-container"
                }, React.createElement("div", {
                      className: "unit-container"
                    }, React.createElement(Switch$WebAudio.make, {
                          isOn: sequencerOn,
                          toggle: toggleSequencerOn,
                          children: "START"
                        })), React.createElement("div", {
                      className: "unit-container",
                      style: {
                        display: "flex"
                      }
                    }, $$Array.mapi((function (ind, value) {
                            var match = activeStep === ind;
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
                                            var index = ind;
                                            return Curry._1(setSequencer, (function (s) {
                                                          Caml_array.caml_array_set(s, index, !Caml_array.caml_array_get(s, index));
                                                          return $$Array.copy(s);
                                                        }));
                                          })
                                      }, match ? React.createElement("div", {
                                              style: {
                                                backgroundColor: ColorPalette$WebAudio.green,
                                                height: "20px",
                                                width: "20px",
                                                borderRadius: "20px"
                                              }
                                            }) : null);
                          }), sequencer))));
}

var make = Keyboard;

export {
  make ,
  
}
/* react Not a pure module */
