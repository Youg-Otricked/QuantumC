/*!
 * @wasmer/sdk
 * Wasmer Javascript SDK. It allows interacting with Wasmer Packages in Node.js and the Browser.
 *
 * @version v0.9.0
 * @author Wasmer Engineering Team <engineering@wasmer.io>
 * @homepage https://github.com/wasmerio/wasmer-js
 * @repository git+https://github.com/wasmerio/wasmer-js.git
 * @license MIT
 */
import{init as e,setWorkerUrl as r}from"./index.mjs";export{Atom,Command,DeployedApp,Directory,Instance,IntoUnderlyingByteSource,IntoUnderlyingSink,IntoUnderlyingSource,PublishPackageOutput,ReadableStreamSource,Runtime,ThreadPoolWorker,Trap,User,UserPackageDefinition,Volume,Wasmer,WasmerPackage,WritableStreamSink,initSync,initializeLogger,on_start,runWasix,setRegistry,setSDKUrl,wat2wasm}from"./index.mjs";const t=async r=>{if(r||(r={}),!r.module){let e="https://unpkg.com/@wasmer/sdk@0.9.0/dist/wasmer_js_bg.wasm";"undefined"!=typeof window&&(r.module=new URL(e))}return r.workerUrl||(r.workerUrl="https://unpkg.com/@wasmer/sdk@0.9.0/dist/index.mjs"),e(r)},n=()=>{r("https://unpkg.com/@wasmer/sdk@0.9.0/dist/index.mjs")};export{t as init,n as setDefaultWorkerUrl,r as setWorkerUrl};
