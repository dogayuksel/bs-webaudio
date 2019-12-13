Js.log("Hello, BuckleScript and Reason!");

type audioDestinationNode;

type gainNode;
[@bs.new] external createGainNode: unit => gainNode = "GainNode";
[@bs.send] external connectDestination: (gainNode, audioDestinationNode) => unit = "connect";

type oscillatorNode;
[@bs.new] external createOscillatorNode: unit => oscillatorNode = "OscillatorNode";
[@bs.send] external start: oscillatorNode => unit = "start";
[@bs.send] external connectOscillator: (oscillatorNode, gainNode) => unit = "connect";

type audioContext;
[@bs.new] external createAudioContext: unit => audioContext = "AudioContext";
[@bs.send] external createOscillator: audioContext => oscillatorNode = "createOscillator";
[@bs.send] external createGain: audioContext => gainNode = "createGain";
[@bs.get] external get_destination: audioContext => audioDestinationNode = "destination";

let audioCtx = createAudioContext();
let oscillator = createOscillator(audioCtx);
let gain = createGain(audioCtx);
connectOscillator(oscillator, gain);
connectDestination(gain, get_destination(audioCtx));
start(oscillator);
