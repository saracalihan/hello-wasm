const canvasEl = document.getElementById('canvas');
const ctx = canvasEl.getContext('2d');

let w = null;
let wInstance = null;
let memmory = null;
let width =0;
let height=0;

async function initModule(){
  const frequency = new WebAssembly.Global({ value: "f64", mutable: false }, 1);
  w = await WebAssembly.instantiateStreaming(fetch('main.wasm'), {
    env: {
      log: (msg) => console.log(msg),
      sin: (a) => Math.sin(a),
      frequency
    },
    js: {
    }
  });

  wInstance = w.instance;
  memory = new Uint8Array(wInstance.exports.memory.buffer);
  width = wInstance.exports.width();
  height = wInstance.exports.height();
  console.log('Wasm module initialized',{
    w,
    wInstance,
    memory,
    width,
    height
  });
  }

function run(){
  wInstance.exports.draw();
  let arr = new Uint8ClampedArray(memory.buffer, wInstance.exports.get_pixels(), width*height *4);
  const image = new ImageData(arr, width);

  canvasEl.width = width;
  canvasEl.height = height;
  ctx.putImageData(image, 0, 0);
}

// Main task
(async()=>{
  await initModule();
  const freqEl = document.getElementById('freq');
  const ampEl = document.getElementById('amp');
  const phsEl = document.getElementById('phase');
  let phase = 0;
  setInterval(()=>{
    wInstance.exports.set_frequency(new Number(freqEl.value));
    wInstance.exports.set_amplitude(new Number(ampEl.value));
    phase+=Number(phsEl.value);
    wInstance.exports.set_phase(phase);

    run();
  }, 1000/60);
})();

