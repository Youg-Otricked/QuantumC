// Filename: compile-worker.js
// Change the import path to the full URL
import { WebContainer } from 'https://cdn.jsdelivr.net/npm/@webcontainer/api/dist/index.js'; // <--- CRUCIAL CHANGE HERE

let wc;
self.onmessage = async (e) => {
  const code = e.data?.code || '#include <iostream>\nint main(){std::cout<<"Hi\\n";}\n';
  try {
    console.log("Worker: Starting message handler.");
    if (!wc) {
      console.log("Worker: Booting WebContainer...");
      wc = await WebContainer.boot({ coep: "require-corp" });
      console.log("Worker: WebContainer booted successfully.");
    }

    console.log("Worker: Mounting files...");
    await wc.mount({
      'package.json': {
        file: JSON.stringify({
          name: 'cpp-wasm',
          scripts: { build: 'emcc main.cpp -sSTANDALONE_WASM=1 -O2 -o a.wasm' },
          devDependencies: { emscripten: 'latest' }
        })
      },
      'main.cpp': { file: code }
    });
    console.log("Worker: Files mounted.");

    console.log("Worker: Installing npm dependencies (emscripten)...");
    const install = await wc.spawn('npm', ['i']);
    install.output.pipeTo(new WritableStream({
      write(chunk) {
        console.log("npm install output:", chunk);
      }
    }));
    await install.exit;
    console.log("Worker: npm dependencies installed.");

    console.log("Worker: Building WASM...");
    const build = await wc.spawn('npm', ['run', 'build']);
    build.output.pipeTo(new WritableStream({
      write(chunk) {
        console.log("npm build output:", chunk);
      }
    }));
    await build.exit;
    console.log("Worker: WASM built.");

    console.log("Worker: Reading compiled WASM...");
    const fs = await wc.fs.readFile('/a.wasm');
    const buf = fs.buffer.slice(fs.byteOffset, fs.byteOffset + fs.byteLength);

    const wasmCopy = buf.slice(0);
    console.log("Worker: WASM read and copied. Posting message back.");
    postMessage({ type: 'done', wasm: wasmCopy }, [wasmCopy]);

  } catch (err) {
    console.error("Worker: Error during compilation process:", err);
    postMessage({ type: 'error', message: String(err) });
  }
};