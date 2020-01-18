// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Block from "bs-platform/lib/es6/block.js";
import * as React from "react";
import * as Pervasives from "bs-platform/lib/es6/pervasives.js";
import * as Knob$WebAudio from "./Knob.bs.js";
import * as Envelope$WebAudio from "../Envelope/Envelope.bs.js";
import * as ColorPalette$WebAudio from "../ColorPalette.bs.js";

function EnvelopeUnit(Props) {
  var envelope = Props.envelope;
  return React.createElement("div", {
              style: {
                backgroundColor: ColorPalette$WebAudio.blue,
                border: "3px solid " + ColorPalette$WebAudio.white,
                display: "inline-block",
                margin: "10px",
                padding: "0 20px",
                borderRadius: "20px"
              }
            }, React.createElement("div", undefined, React.createElement(Knob$WebAudio.make, {
                      name: "ATTACK",
                      config: {
                        minValue: Pervasives.epsilon_float,
                        maxValue: 2.0,
                        scale: /* Linear */0,
                        size: 50
                      },
                      initialParamValue: envelope.envelopeParams.attack,
                      setParamValue: (function (value) {
                          return Envelope$WebAudio.update(/* Attack */Block.__(0, [value]), envelope);
                        })
                    }), React.createElement(Knob$WebAudio.make, {
                      name: "DECAY",
                      config: {
                        minValue: Pervasives.epsilon_float,
                        maxValue: 5.0,
                        scale: /* Linear */0,
                        size: 50
                      },
                      initialParamValue: envelope.envelopeParams.decay,
                      setParamValue: (function (value) {
                          return Envelope$WebAudio.update(/* Decay */Block.__(1, [value]), envelope);
                        })
                    })), React.createElement("div", undefined, React.createElement(Knob$WebAudio.make, {
                      name: "SUSTAIN",
                      config: {
                        minValue: Pervasives.epsilon_float,
                        maxValue: 1.0,
                        scale: /* Linear */0,
                        size: 50
                      },
                      initialParamValue: envelope.envelopeParams.sustain,
                      setParamValue: (function (value) {
                          return Envelope$WebAudio.update(/* Sustain */Block.__(2, [value]), envelope);
                        })
                    }), React.createElement(Knob$WebAudio.make, {
                      name: "RELEASE",
                      config: {
                        minValue: Pervasives.epsilon_float,
                        maxValue: 5.0,
                        scale: /* Linear */0,
                        size: 50
                      },
                      initialParamValue: envelope.envelopeParams.release,
                      setParamValue: (function (value) {
                          return Envelope$WebAudio.update(/* Release */Block.__(3, [value]), envelope);
                        })
                    })));
}

var make = EnvelopeUnit;

export {
  make ,
  
}
/* react Not a pure module */
