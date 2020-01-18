// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as ColorPalette$WebAudio from "../ColorPalette.bs.js";

function sizeInPixels(x) {
  return String(x) + "px";
}

function clamp(value, config) {
  var match = value < config.minValue;
  var value$1 = match ? config.minValue : value;
  var match$1 = value$1 > config.maxValue;
  if (match$1) {
    return config.maxValue;
  } else {
    return value$1;
  }
}

function mapValue(from, target, value) {
  var ymin = target[0];
  var xmin = from[0];
  return (value - xmin) / (from[1] - xmin) * (target[1] - ymin) + ymin;
}

function Knob(Props) {
  var name = Props.name;
  var config = Props.config;
  var initialParamValue = Props.initialParamValue;
  var setParamValue = Props.setParamValue;
  var knobDomainInPixels = React.useMemo((function () {
          return (config.size << 2);
        }), /* array */[config.size]);
  var partial_arg_000 = config.minValue;
  var partial_arg_001 = config.maxValue;
  var partial_arg = /* tuple */[
    partial_arg_000,
    partial_arg_001
  ];
  var mapParam = function (param, param$1) {
    return mapValue(partial_arg, param, param$1);
  };
  var arg_000 = config.minValue;
  var arg_001 = config.maxValue;
  var arg = /* tuple */[
    arg_000,
    arg_001
  ];
  var arg$1 = /* tuple */[
    30.0,
    330.0
  ];
  var indicatorPrecission = React.useMemo((function () {
          var logRange = Math.log10(config.maxValue - config.minValue);
          if (logRange > 3.0) {
            return 0;
          } else if (logRange > 0.8) {
            return 1;
          } else {
            return 2;
          }
        }), /* tuple */[
        config.minValue,
        config.maxValue
      ]);
  var mapValueToDegrees = function (value) {
    var match = config.scale;
    var degrees = match ? mapValue(/* tuple */[
            0.0,
            1.0
          ], arg$1, Math.log10(Curry._2(mapParam, /* tuple */[
                    1.0,
                    10.0
                  ], value))) : Curry._2(mapParam, /* tuple */[
            30.0,
            330.0
          ], value);
    return degrees.toString() + "deg";
  };
  var match = React.useState((function () {
          return initialParamValue;
        }));
  var setValue = match[1];
  var value = match[0];
  var lastY = React.useRef(0);
  var handleMouseMove = function ($$event) {
    var clientY = $$event.clientY;
    Curry._1(setValue, (function (value) {
            var change = mapValue(/* tuple */[
                  0.0,
                  knobDomainInPixels
                ], /* tuple */[
                  0.0,
                  1.0
                ], lastY.current - clientY | 0);
            var match = config.scale;
            var newValue = match ? mapValue(/* tuple */[
                    1.0,
                    10.0
                  ], arg, Math.pow(10.0, change + Math.log10(Curry._2(mapParam, /* tuple */[
                                1.0,
                                10.0
                              ], value)))) : mapValue(/* tuple */[
                    0.0,
                    1.0
                  ], arg, change + Curry._2(mapParam, /* tuple */[
                        0.0,
                        1.0
                      ], value));
            var clampedValue = clamp(newValue, config);
            Curry._1(setParamValue, clampedValue);
            lastY.current = clientY;
            return clampedValue;
          }));
    return /* () */0;
  };
  var handleMouseUp = function (param) {
    document.removeEventListener("mousemove", handleMouseMove);
    return /* () */0;
  };
  var handleMouseDown = function ($$event) {
    var clientY = $$event.clientY;
    lastY.current = clientY;
    document.addEventListener("mousemove", handleMouseMove);
    document.addEventListener("mouseup", handleMouseUp, {
          capture: false,
          once: true,
          passive: true
        });
    return /* () */0;
  };
  return React.createElement("div", {
              style: {
                backgroundColor: ColorPalette$WebAudio.blue,
                display: "inline-block",
                padding: "5px 10px"
              }
            }, React.createElement("h5", {
                  className: "knob-label",
                  style: {
                    color: ColorPalette$WebAudio.white
                  }
                }, name), React.createElement("div", {
                  style: {
                    backgroundColor: ColorPalette$WebAudio.silver,
                    border: "1px solid " + ColorPalette$WebAudio.white,
                    display: "flex",
                    height: String(config.size) + "px",
                    margin: "0 auto",
                    width: String(config.size) + "px",
                    borderRadius: String(config.size) + "px",
                    justifyContent: "center",
                    transform: "rotate(" + (mapValueToDegrees(value) + ")")
                  },
                  onMouseDown: handleMouseDown
                }, React.createElement("div", {
                      style: {
                        borderRight: "5px solid transparent",
                        borderBottom: "12px solid " + ColorPalette$WebAudio.black,
                        borderLeft: "5px solid transparent",
                        height: "0",
                        width: "0"
                      }
                    })), React.createElement("h5", {
                  className: "knob-label",
                  style: {
                    color: ColorPalette$WebAudio.white
                  }
                }, value.toFixed(indicatorPrecission)));
}

var knobSensitivityFactor = 4;

var knobMin = 30.0;

var knobMax = 330.0;

var make = Knob;

export {
  knobSensitivityFactor ,
  sizeInPixels ,
  knobMin ,
  knobMax ,
  clamp ,
  mapValue ,
  make ,
  
}
/* react Not a pure module */
