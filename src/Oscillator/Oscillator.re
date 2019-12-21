type oscillator;

type oscillatorType =
  | Sine
  | SawTooth
  | Triange
  | Square;

let toTypedArray = (floatArray: array(Complex.t)) => {
  let realCoefficients =
    Array.map((x: Complex.t) => x.re, floatArray)
    ->Js_typed_array.Float32Array.make;
  let imaginaryCoefficients =
    Array.map((x: Complex.t) => x.im, floatArray)
    ->Js_typed_array.Float32Array.make;
  (realCoefficients, imaginaryCoefficients);
};

let sampleSineWave = () => {
  let samples = Array.make(256, Complex.{re: 0.0, im: 0.0});
  for (x in 0 to 255) {
    let mapped =
      (float_of_int(x) /. 256.0 *. 2.0 *. Js.Math._PI +. Js.Math._PI)->sin;
    samples[x] = Complex.{re: mapped, im: 0.0};
  };
  FFT.fft(samples) |> toTypedArray;
};

let sampleSawTooth = () => {
  let samples = Array.make(256, Complex.{re: 0.0, im: 0.0});
  for (x in 0 to 255) {
    let mapped = float_of_int(x) /. 256.0 *. 2.0 -. 1.0;
    samples[x] = Complex.{re: mapped, im: 0.0};
  };
  FFT.fft(samples) |> toTypedArray;
};

let make = (oscillatorType: oscillatorType, audioCtx: AudioContext.t) => {
  let oscillator = AudioContext.createOscillator(audioCtx);
  let (realCoefficients, imaginaryCoefficients) =
    switch (oscillatorType) {
    | Sine => sampleSineWave()
    | SawTooth => sampleSawTooth()
    | _ => raise(Not_found)
    };
  let periodicWave =
    audioCtx
    |> AudioContext.createPeriodicWave(
         realCoefficients,
         imaginaryCoefficients,
         {"disableNormalization": false},
       );
  oscillator |> OscillatorNode.setPeriodicWave(periodicWave);
  oscillator;
};
