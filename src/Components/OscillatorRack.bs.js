// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as List from "bs-platform/lib/es6/list.js";
import * as $$Array from "bs-platform/lib/es6/array.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as OscillatorUnit$WebAudio from "./OscillatorUnit.bs.js";

function OscillatorRack(Props) {
  var match = React.useState((function () {
          return 1;
        }));
  var setOscillatorIndex = match[1];
  var oscillatorIndex = match[0];
  var match$1 = React.useState((function () {
          return /* :: */[
                  1,
                  /* [] */0
                ];
        }));
  var setOscillators = match$1[1];
  var oscillators = match$1[0];
  return React.createElement("div", undefined, React.createElement("div", {
                  style: {
                    backgroundColor: "#839264",
                    color: "#FFF3F5",
                    display: "inline-block",
                    margin: "10px 15px",
                    padding: "0 20px"
                  },
                  onClick: (function (param) {
                      Curry._1(setOscillators, (function (oList) {
                              return /* :: */[
                                      oscillatorIndex + 1 | 0,
                                      oList
                                    ];
                            }));
                      return Curry._1(setOscillatorIndex, (function (idx) {
                                    return idx + 1 | 0;
                                  }));
                    })
                }, React.createElement("h4", undefined, "Add Oscillator")), React.createElement("div", undefined, $$Array.of_list(List.map((function (osc) {
                            return React.createElement("div", {
                                        key: String(osc)
                                      }, React.createElement("div", {
                                            style: {
                                              backgroundColor: "#839264",
                                              color: "#FFF3F5",
                                              display: "inline-block",
                                              margin: "0 15px",
                                              padding: "0 20px"
                                            },
                                            onClick: (function (param) {
                                                var osc$1 = osc;
                                                return Curry._1(setOscillators, (function (oList) {
                                                              return List.filter((function (o) {
                                                                              return o !== osc$1;
                                                                            }))(oList);
                                                            }));
                                              })
                                          }, React.createElement("h4", undefined, "X")), React.createElement(OscillatorUnit$WebAudio.make, {
                                            name: "Oscillator " + String(osc),
                                            targetOutput: undefined,
                                            alone: List.length(oscillators) === 1
                                          }));
                          }), oscillators))));
}

var make = OscillatorRack;

export {
  make ,
  
}
/* react Not a pure module */
