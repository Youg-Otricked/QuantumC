- Variadic Generics (`class VaradicTypes<...Tys> { Tys elems; ...`) (not decided on syntax) 
- Operator.
- Function pointers
- Private/Protected inheritance
- Constexpr
- Debug
- Cqb lib in stl. Ci and build.
- qcheck (QC Lint(qc linter. duh)
- qconform (QC Formatter)
- `__attributes__((...))`
- const params/returns and const correct methods
- Copy VS Move assignment (no move only, im not rust), to make things faster.
- more error stuff if i feel like it
__qc_commit_hash() — exact git commit the compiler/runtime was built from, invaluable for bug reports since version numbers alone often don't pin down exactly which state of the code produced a binary
__qc_build_date() — timestamp of the build
__qc_target_triple() — what platform/arch this runtime was compiled for (x86_64-linux-gnu, wasm32-unknown-unknown, etc.) — relevant since your lesson context here is literally about compiling toward WASM/LLVM targets
__qc_llvm_version() — since you're LLVM-backed, knowing which LLVM version built a given binary matters a lot for debugging codegen-level bugs that are version-specific
__qc_debug_build() — a bool baked in at compile time indicating whether this was a debug or release build, so runtime error handlers can decide whether to print verbose diagnostics or not
- destructuring (eg `Pair {abc, def} = ...`, operator{} which is your destructure handler (multi return baby!) (maybe))
- tuples (like zig/rust tuples, .0 .1 .2 .3)
- user defined literals (macros baby!)
- user defined macro functions
- user defined metadata tags
- Compile-time assertions (assert, static_assert)
- Decltype (get type of expr)
- noexcept (funciton modifier) (same update as const on functions and stuff)
- change parent constructor and delegeating constructors
- dynamic field access
- has field, has method
- _generic- manal overloading
- rust like tags for enums
- cpp contracts
- has_method, has_field, at
- rule usertypes so userdefined const equiveleants and stuff
- conversion operators (operator int, .... I already have _eval (to bool) and _repr (to string))
- operator co_await once i add co_await
- operator cast

TOP PRIORITY:
1. Generics in header
2. Tuples + Destruturing
2. Function Pointers
2. Tagged enums
2. CQB
3. Other stuff (private/protected inheritance) + Variadic Generics, operator.
4. Metadata
?likely? - likely marked
?unlikely? - marked unlikely
?inline? - pls inline >-<
?inline(always)? - always inline
?inline(never)? -  NEVER inline
?nodiscard? - warn if discard result
?noreturn? - optimize away post-call cleanup
?deprecated(msg)? - warning with this message when used
?fully_deprecated(msg)? - ERROR with this message when used
?errordiscard? - nodiscard but errors not warns
?consteval? - evaluate at compile time
?qc_ver_eq(version)? - errors if qc ver is != version
?qc_ver_lt(version)? - errors if qc ver is >= version
?qc_ver_gt(version)? - errors if qc ver is <= version
?qc_ver_lte(version)? - errors if qc ver is > version
?qc_ver_gte(version)? - errors if qc ver is < version
?since(ver)? - states the version of the package this is for
?until(ver)? - states when this will be deprecated
?experimental? - states that this tool is janky, subject to change, or flaky/expremintal
?unstable? - states this tool is janky, flaky, or unstable, but api won't change
?sentinel(value, msg, value, msg....)? - states this tool returns sentinel values with special meaning
5. Preproccessers
#line - somthing idk
6. User-Defined metadata
7. User-Defined macro _functions_ (the only good thing in rust)
8. User defined literals
9. co_await
## 1\. Concurrency

### Stdlib

* Mutex \+ Condvar  
* Semaphore  
* CancelationToken  
*   
* RWMutex  
* Channel  
* Thread \- raw OS thread  
* GThread \- green threads  
* Async  
  * Promise \- writable  
  * Future \- readable  
  * async/await

### Library

* ZConcurrency \- Zig-style IO-based concurrency

## 2\. Manual Memory Management

### Stdlib

* Scratch Buffers  
* GPA (General Purpose Allocator)  
* Arenas  
* Allocator interface  
  * `.alloc`  
  * `.free`

## 3\. IO & Streams

### Stdlib

* BufferedReader  
* BufferedWriter  
* Pipe  
* MemoryStream  
* Stream primitives

## 4\. Networking

### Stdlib

* Socket  
* TCPSocket  
* UDPSocket  
* UnixSocket  
* Listener  
* SocketAddress  
* IPv4  
* IPv6  
* IPAddress  
* DNS

## 5\. HTTP & Web

### Stdlib

* Raw HTTP  
  * Socket  
  * Send  
  * Receive  
  * HTTP parsing  
* HTTPClient  
  * GET  
  * POST  
  * PUT  
  * PATCH  
  * DELETE  
  * HEAD  
  * OPTIONS  
* HTTP Stream  
  * Streaming HTTP data

### Library

* TLSocket / SecureSocket / HTTPSocket  
  * HTTPS wrapper around raw sockets  
* FetchClient  
  * Fetch API-style HTTP client  
  * HTTPS support  
* HTTPSClient  
  * Higher-level HTTPS client  
* HTTPServer  
  * Easy-to-use HTTP server  
  * Secure HTTPS mode  
* Router  
* Middleware  
* Cookies  
* Sessions  
* Authentication  
* WebSocket  
* SSE  
* Multipart  
* URL  
* FormData  
* Web Framework

## 6\. Messaging

### Library

* WebSocket  
* MQTT  
* AMQP  
* Kafka  
* NATS  
* Redis

---

## 7\. Cryptography

### Stdlib

* SHA-256  
* SHA-3  
* MD5  
* Crypto RNG

### Library

* AES  
* RSA  
* ChaCha20  
* Curve25519  
* Ed25519  
* HMAC  
* HKDF  
* Password Hashing  
* CRC32  
* TLS

---

## 8\. Error Handling

### Stdlib

* Result type  
  * Designed to work naturally with builtin multi-return  
* unwrap  
* assert  
* panic

---

## 9\. Data Structures

### Stdlib

* `Ordered::Map`  
* `Ordered::Set`  
* Queue  
* Deque  
* RB-Tree  
* B-Tree  
* Heap  
* Binary Heap  
* Min Heap  
* Max Heap  
* Trie  
* Graph  
* AdjacencyList  
* Hive  
* BitMap  
* MdSpan  
* Slice  
* StringView  
* StringBuilder

### Graph Algorithms

* Dijkstra's algorithm  
* BFS  
* DFS  
* topological sort  
* SCC  
* A\*  
* MST  
* cycle detection

---

## 10\. Algorithms & Iterators

### Stdlib

### Iterator

* Iterator concept  
* `sort`  
* `binary_search`  
* `find`  
* `find_if`  
* `find_first_of`  
* `reduce`  
* `fold`  
* `zip`  
* `all_of`  
* `any_of`  
* `none_of`  
* `swap`

---

## 11\. Time & Date

### Stdlib

* DateTime  
* Time  
* ATime  
* TimeZone  
* Constants

---

## 12\. Operating System & System APIs

### Stdlib

* Environment variables  
* Subprocess spawning  
* Signals  
* Filesystem  
* Filesystem path manipulation  
* File operations  
* Process APIs

---

## 13\. Text & Unicode

### Stdlib

* StringView  
* Slice  
* StringBuilder

### Library

* Unicode  
* Text  
  * String utilities  
  * Case conversion  
  * Split  
  * Join  
  * Trim  
  * Replace  
  * Normalize  
  * Grapheme iteration  
  * Word iteration  
  * Line iteration  
* Regex

---

## 14\. Data Formats & Serialization

### Libraries

* JSON  
* TOML  
* YAML  
* CSV  
* INI  
* XML  
* HTML  
* Markdown  
* MIME  
* MessagePack  
* Protobuf

---

## 15\. Compression & Archives

### Libraries

* Gzip  
* Zip  
* Brotli  
* Compression

---

## 16\. Images

### Library

* Image  
  * PNG  
  * JPEG  
  * GIF  
  * BMP  
  * WebP  
  * Image processing

---

## 17\. Audio & Video

### Libraries

* Audio  
* Video

---

## 18\. Database

### Library

### Database Drivers

* SQLite  
* MySQL  
* PostgreSQL

### QuantumC Database

* SQCL  
  * Turso-inspired  
  * Written in QuantumC

---

## 19\. Logging

### Library

* Logger  
* Level  
* Handler  
* Formatter  
* Structured logging  
* File handler  
* Console handler  
* JSON handler

---

## 20\. Telemetry

### Library

* Metrics  
* Tracing  
* Spans  
* Exporters

---

## 21\. Benchmarking

### Library

* `benchmark()`  
* Iterations  
* Warmup  
* Timing  
* Allocation tracking  
* Comparison

---

## 22\. Testing

### Library / CQB Integration

* Property Testing  
* Fuzzing  
* Unit testing  
* Integration testing  
* Code coverage

---

## 23\. Utility

### Library

* LRUCache  
* Cache  
* Memoization  
* Retry  
* Backoff  
* RateLimiter  
* Debouncer  
* Throttler

---

## 24\. TUI

### Library

* TUI framework  
* Terminal rendering  
* Widgets  
* Layout  
* Input handling  
* Colors  
* Styling  
* Tables  
* Lists  
* Trees  
* Panels  
* Modals  
* Progress bars  
* Spinners

---

## 25\. GUI

### Library

* GUI framework  
* Windows  
* Widgets  
* Layout  
* Events  
* Rendering

---

## 26\. QDoc

### Tool / Library

* API documentation  
* Markdown  
* Examples  
* Generated references  
* Cross references

---

## 27\. CQB

### QuantumC Build / CI / Testing System

CQB is a build system, CI system, and testing system written entirely in QuantumC.

All build configuration, CI configuration, and testing configuration are written in QuantumC.

### Build System

* Ninja-inspired build execution  
* Zig-inspired build ergonomics  
* Docker-style build output  
* Parallel builds  
* Dependency graphs  
* Incremental builds  
* Caching

### Testing

* Zig test-style output  
* Cargo test-style output  
* Go test `-v`\-style output  
* PITest-style testing capabilities  
* Vitest-style testing capabilities  
* Code coverage  
* Property testing  
* Fuzzing  
* Benchmarks

### CI

* CI pipelines written in QuantumC  
* Local CI execution  
* Remote CI execution  
* Build/test artifacts  
* Logs  
* Reports  
* Coverage  
* Beautiful terminal UI

---

## 28\. C Standard Library

### `libc`

The entire C standard library is implemented in QuantumC using a namespace structure such as:

namespace libc {  
    namespace stdint {  
        ...  
    }  
}

QuantumC provides the useful parts of the C standard library while excluding functionality already made unnecessary by the language itself, such as `stdbool`.

---

## 29\. Big Numbers & Identity

### Stdlib

* BigInt  
* UUID

