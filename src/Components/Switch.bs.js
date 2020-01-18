// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as ColorPalette$WebAudio from "../ColorPalette.bs.js";

function sizeInPixels(x) {
  return String(x) + "px";
}

function Switch(Props) {
  var isOn = Props.isOn;
  var children = Props.children;
  return React.createElement("div", {
              className: "control-container"
            }, React.createElement("h5", {
                  className: "control-label"
                }, children), React.createElement("div", {
                  style: {
                    backgroundColor: ColorPalette$WebAudio.black,
                    height: String(20) + "px",
                    margin: "10px 20px",
                    width: String(40) + "px"
                  }
                }, React.createElement("div", {
                      style: {
                        backgroundColor: ColorPalette$WebAudio.silver,
                        border: "1px solid " + ColorPalette$WebAudio.white,
                        height: String(20) + "px",
                        width: String(20) + "px",
                        transition: "transform 0.2s",
                        transform: "translateX(" + ((
                            isOn ? String(20) + "px" : "0"
                          ) + ")")
                      }
                    })));
}

var width = 40;

var height = 20;

var make = Switch;

export {
  width ,
  height ,
  sizeInPixels ,
  make ,
  
}
/* react Not a pure module */
