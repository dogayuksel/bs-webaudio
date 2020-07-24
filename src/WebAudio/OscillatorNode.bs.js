// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as AudioNode$WebAudio from "./AudioNode.bs.js";

function Impl(T) {
  return {};
}

AudioNode$WebAudio.Impl({});

function setOscillatorNodeType(oscillatorType, oscillatorNode) {
  if (typeof oscillatorType === "number") {
    switch (oscillatorType) {
      case /* Sine */0 :
          oscillatorNode.type = "sine";
          return ;
      case /* Square */1 :
          oscillatorNode.type = "square";
          return ;
      case /* Sawtooth */2 :
          oscillatorNode.type = "sawtooth";
          return ;
      case /* Triange */3 :
          oscillatorNode.type = "triangle";
          return ;
      
    }
  } else {
    oscillatorNode.setPeriodicWave(oscillatorType._0);
    return ;
  }
}

export {
  Impl ,
  setOscillatorNodeType ,
  
}
/*  Not a pure module */
