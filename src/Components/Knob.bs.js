// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";

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

function Knob(Props) {
  var name = Props.name;
  var param = Props.param;
  var config = Props.config;
  var mapValueToDegrees = function (value) {
    var domain = config.maxValue - config.minValue;
    var value$1 = value - config.minValue;
    var match = value$1 === 0.0;
    var degrees;
    if (match) {
      degrees = 0.0;
    } else {
      var match$1 = config.scale;
      degrees = match$1 ? 300.0 / Math.log(domain) * Math.log(value$1) : 300.0 / domain * value$1;
    }
    return (degrees + 30.0).toString() + "deg";
  };
  var match = React.useState((function () {
          return param.value;
        }));
  var setValue = match[1];
  var value = match[0];
  var lastY = React.useRef(0);
  var handleMouseMove = function ($$event) {
    var clientY = $$event.clientY;
    Curry._1(setValue, (function (value) {
            var change = lastY.current - clientY | 0;
            var match = config.scale;
            var scaledChange;
            if (match) {
              var possibleValue = Math.pow(Math.abs(change), Math.log(value));
              var match$1 = possibleValue > value / 3.0;
              scaledChange = match$1 ? value / 3.0 : possibleValue;
            } else {
              scaledChange = Math.abs(change);
            }
            var match$2 = change > 0;
            var newValue = match$2 ? value + scaledChange : value - scaledChange;
            var clampedValue = clamp(newValue, config);
            param.value = clampedValue;
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
                display: "inline-block",
                padding: "10px",
                width: String(140) + "px"
              }
            }, React.createElement("div", {
                  style: {
                    backgroundColor: "#839264",
                    display: "flex",
                    height: String(120) + "px",
                    margin: "10px",
                    width: String(120) + "px",
                    borderRadius: String(120) + "px",
                    justifyContent: "center",
                    transform: "rotate(" + (mapValueToDegrees(value) + ")")
                  },
                  onMouseDown: handleMouseDown
                }, React.createElement("div", {
                      style: {
                        borderRight: "10px solid transparent",
                        borderBottom: "10px solid black",
                        borderLeft: "10px solid transparent",
                        height: "0",
                        width: "0"
                      }
                    })), React.createElement("div", {
                  style: {
                    display: "flex",
                    justifyContent: "center"
                  }
                }, name + ": ", String(value | 0)));
}

var size = 120;

var offset = 30.0;

var range = 300.0;

var make = Knob;

export {
  size ,
  sizeInPixels ,
  offset ,
  range ,
  clamp ,
  make ,
  
}
/* react Not a pure module */
