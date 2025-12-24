import { WebContainer } from 'https://cdn.jsdelivr.net/npm/@webcontainer/api/dist/index.js';

let wc;

document.addEventListener('DOMContentLoaded', async () => {
    const out = document.getElementById('out');
    const codeEl = document.getElementById('code-editor');

    wc = await WebContainer.boot({ coep: 'require-corp' });

    const runner = new Worker('./run-worker.js', { type: 'module' });

    runner.onmessage = (m) => {
        const { stdout, stderr, exitCode } = m.data || {};
        out.textContent += stdout + (stderr ? '\n[stderr]\n' + stderr : '') + '\n[exit ' + exitCode + ']';
    };

    document.getElementById('run').onclick = async () => {
        try {
            out.textContent = 'Compiling...\n';
            const code = codeEl.value || '#include <iostream>\nint main(){std::cout<<"Hi\\n";}\n';

            await wc.mount({
                'package.json': {
                    file: {
                        contents: JSON.stringify({
                            name: 'cpp-wasm',
                            scripts: { build: 'emcc main.cpp -sSTANDALONE_WASM=1 -O2 -o a.wasm' },
                            devDependencies: { emscripten: 'latest' }
                        })
                    }
                },
                'main.cpp': {
                    file: { contents: code }
                }
            });

            // 1) npm install with logging
            out.textContent += 'Installing emscripten...\n';
            const install = await wc.spawn('npm', ['i']);
            install.output.pipeTo(new WritableStream({
                write(chunk) {
                    console.log('npm install:', chunk);
                }
            }));
            const installCode = await install.exit;
            console.log('npm i exit code:', installCode);

            // 2) npm run build with logging
            out.textContent += 'Building WASM...\n';
            const build = await wc.spawn('npm', ['run', 'build']);
            build.output.pipeTo(new WritableStream({
                write(chunk) {
                    console.log('npm build:', chunk);
                }
            }));
            const buildCode = await build.exit;
            console.log('npm run build exit code:', buildCode);

            // optionally list root dir
            const rootFiles = await wc.fs.readdir('/');
            console.log('root files:', rootFiles);

            // 3) now try to read a.wasm
            const fsData = await wc.fs.readFile('/a.wasm');
            const buf = fsData.buffer.slice(fsData.byteOffset, fsData.byteOffset + fsData.byteLength);

            out.textContent += 'Running...\n';
            runner.postMessage({ type: 'runWasi', wasm: buf }, [buf]);
        } catch (err) {
            out.textContent += 'Compile error: ' + String(err) + '\n';
            console.error(err);
        }
    };
    // your editor helpers unchanged
    const INDENT = '    ';
    const normalizeQuote = (ch) => (ch === '‘' || ch === '’') ? "'" : (ch === '“' || ch === '”') ? '"' : ch;

    document.addEventListener('keydown', (e) => {
        const ta = e.target;
        if (!(ta instanceof HTMLTextAreaElement) || !ta.matches('.code-editor')) return;

        const nextChar = () => ta.value.slice(ta.selectionStart, ta.selectionStart + 1);
        const key = normalizeQuote(e.key);
        const next = normalizeQuote(nextChar());

        if ('}])\'"'.includes(key) && next === key) {
            e.preventDefault();
            ta.selectionStart = ta.selectionEnd = ta.selectionStart + 1;
            return;
        }

        const pairs = { '{': '}', '[': ']', '(': ')', '"': '"', "'": "'" };
        if (pairs[key]) {
            e.preventDefault();
            const { selectionStart: s, selectionEnd: epos, value } = ta;
            const open = key, close = pairs[key];
            if (s !== epos) {
                const sel = value.slice(s, epos);
                ta.value = value.slice(0, s) + open + sel + close + value.slice(epos);
                ta.selectionStart = s + 1;
                ta.selectionEnd = epos + 1;
            } else {
                ta.value = value.slice(0, s) + open + close + value.slice(epos);
                ta.selectionStart = ta.selectionEnd = s + 1;
            }
            return;
        }

        if (e.key === 'Tab') {
            e.preventDefault();
            const { selectionStart: s, selectionEnd: epos, value } = ta;
            ta.value = value.slice(0, s) + INDENT + value.slice(epos);
            ta.selectionStart = ta.selectionEnd = s + INDENT.length;
            return;
        }

        if (e.key === 'Enter') {
            e.preventDefault();
            const { selectionStart: s, selectionEnd: epos, value } = ta;
            const lineStart = value.lastIndexOf('\n', s - 1) + 1;
            const line = value.slice(lineStart, s);
            const baseIndent = (line.match(/^[ \t]*/) || [''])[0];
            const trimmed = line.trimEnd();
            const addBlockIndent = /[{:]$/.test(trimmed) ? INDENT : '';
            const insert = '\n' + baseIndent + addBlockIndent;
            const pos = s + insert.length;

            ta.value = value.slice(0, s) + insert + value.slice(epos);
            ta.selectionStart = ta.selectionEnd = pos;

            if (ta.value.slice(pos, pos + 1) === '}') {
                const fix = '\n' + baseIndent;
                ta.value = ta.value.slice(0, pos) + fix + ta.value.slice(pos);
                ta.selectionStart = ta.selectionEnd = pos;
            }
        }
    });
});