import { WasmerInitInput, InitOutput } from './index.mjs';
export { AppConfig, AppIdentifier, Atom, BaseAppConfig, Command, DeployedApp, DeployedIdApp, DirEntry, Directory, DirectoryInit, InitInput, Instance, IntoUnderlyingByteSource, IntoUnderlyingSink, IntoUnderlyingSource, NamedApp, Output, PackageCommand, PackageManifest, PublishPackageOutput, RunOptions, Runtime, RuntimeOptions, SpawnOptions, SyncInitInput, User, UserPackageDefinition, Volume, VolumeFile, VolumeFileData, VolumeFileDate, VolumeTree, Wasmer, WasmerPackage, WasmerRegistryConfig, initSync, initializeLogger, runWasix, setRegistry, setSDKUrl, setWorkerUrl, wat2wasm } from './index.mjs';

/**
 * Initialize the underlying WebAssembly module, defaulting to an embedded
 * copy of the `*.wasm` file.
 */
declare const init: (initValue?: WasmerInitInput) => Promise<InitOutput>;
/**
 * Set a deafult working Worker Url. Which in this case will be
 * an unpkg url that is set up at the SDK build time.
 */
declare const setDefaultWorkerUrl: () => void;

export { InitOutput, WasmerInitInput, init, setDefaultWorkerUrl };
