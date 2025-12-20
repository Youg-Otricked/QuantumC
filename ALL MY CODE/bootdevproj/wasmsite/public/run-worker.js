self.onmessage = async (e) => {
    if (e.data.type !== 'runWasi') return;
    const wasm = e.data.wasm;
    const dec = new TextDecoder();
    let out = '';
    let inst;

    function fd_write(fd, iov, iovcnt, pnum) {
        const m = new DataView(inst.exports.memory.buffer);
        let n = 0;
        for (let i = 0; i < iovcnt; i++) {
            const p = m.getUint32(iov + i * 8, true);
            const l = m.getUint32(iov + i * 8 + 4, true);
            const bytes = new Uint8Array(inst.exports.memory.buffer, p, l);
            const t = dec.decode(bytes);
            if (fd === 1 || fd === 2) out += t;
            n += l;
        }
        m.setUint32(pnum, n, true);
        return 0;
    }

    const imports = {
        wasi_snapshot_preview1: {
            fd_write,
            fd_read: () => 0,
            fd_close: () => 0,
            fd_seek: () => 0,
            fd_fdstat_get: () => 0,
            environ_sizes_get: (pc, pb) => {
                const m = new DataView(inst.exports.memory.buffer);
                m.setUint32(pc, 0, true);
                m.setUint32(pb, 0, true);
                return 0;
            },
            environ_get: () => 0,
            args_sizes_get: (pc, pb) => {
                const m = new DataView(inst.exports.memory.buffer);
                m.setUint32(pc, 0, true);
                m.setUint32(pb, 0, true);
                return 0;
            },
            args_get: () => 0,
            clock_time_get: () => 0,
            random_get: (p, l) => {
                crypto.getRandomValues(new Uint8Array(inst.exports.memory.buffer, p, l));
                return 0;
            },
            proc_exit: (c) => { throw { _wasi_exit: true, code: c }; }
        }
    };

    try {
        const { instance } = await WebAssembly.instantiate(wasm, imports);
        inst = instance;
        let code = 0;
        try { (inst.exports._main || inst.exports.main)?.(); }
        catch (ex) { if (!(ex && ex._wasi_exit)) throw ex; code = ex.code >>> 0; }
        postMessage({ stdout: out, stderr: '', exitCode: code });
    } catch (err) {
        postMessage({ stdout: out, stderr: String(err), exitCode: 1 });
    }
};