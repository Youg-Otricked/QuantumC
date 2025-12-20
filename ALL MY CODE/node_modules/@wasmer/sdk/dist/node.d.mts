import { WasmerInitInput, InitOutput, VolumeTree } from './index.mjs';
export { AppConfig, AppIdentifier, Atom, BaseAppConfig, Command, DeployedApp, DeployedIdApp, DirEntry, Directory, DirectoryInit, InitInput, Instance, IntoUnderlyingByteSource, IntoUnderlyingSink, IntoUnderlyingSource, NamedApp, Output, PackageCommand, PackageManifest, PublishPackageOutput, RunOptions, Runtime, RuntimeOptions, SpawnOptions, SyncInitInput, User, UserPackageDefinition, Volume, VolumeFile, VolumeFileData, VolumeFileDate, Wasmer, WasmerPackage, WasmerRegistryConfig, initSync, initializeLogger, runWasix, setRegistry, setSDKUrl, setWorkerUrl, wat2wasm } from './index.mjs';

/**
 * Initialize the underlying WebAssembly module, defaulting to an embedded
 * copy of the `*.wasm` file.
 */
declare const init: (initValue?: WasmerInitInput) => Promise<InitOutput>;
declare function walkDir(dir: string, result?: VolumeTree): Promise<VolumeTree>;

export { InitOutput, VolumeTree, WasmerInitInput, init, walkDir };
