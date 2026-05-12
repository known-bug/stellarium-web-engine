Knownbug fork
=============

This repository is a fork of [Stellarium Web Engine](https://github.com/Stellarium/stellarium-web-engine)
maintained by **Knownbug Ltd** (company no. 17087487, registered in England &
Wales) for the version of the engine running at <https://knownbug.app>.

Published in compliance with [GNU AGPL-3.0](LICENSE-AGPL-3.0.txt) §§ 5 and 13.

- **Upstream**: <https://github.com/Stellarium/stellarium-web-engine> — the
  canonical source of truth. Issues with the engine itself should be filed
  there.
- **Modifications from upstream**: see [MODIFICATIONS.md](MODIFICATIONS.md)
  for the list.
- **Original Stellarium Web Engine copyright** by Stellarium Labs SRL and
  contributors. All original copyright notices in source files are preserved.

Issues specific to the Knownbug deployment can be filed in this repository.
For other matters, contact <hello@knownbug.app>.

---

Stellarium Web Engine
=====================

About
-----

Stellarium Web Engine is a JavaScript planetarium renderer using
WebGL that can be embedded into a website.

Features
--------

- Atmosphere simulation.
- Gaia stars database access (more than 1 billion stars).
- HiPS surveys rendering.
- High resolution planet textures.
- Constellations.
- Support for adding layers and shapes in the sky view.
- Landscapes.


Build the javascript version
----------------------------

You need to make sure you have both emscripten and sconstruct installed.

    # Setup emscripten path.
    source $PATH_TO_EMSDK/emsdk_env.sh

    # Build stellarium-web-engine.js and stellarium-web-engine.wasm
    # This will also copy the files into html/static/js
    make js

    # Now see apps/simple-html/ to try the library in a browser.


Contributing
------------

In order for your contribution to Stellarium Web Engine to be accepted, you have to sign the
[Stellarium Web Contributor License Agreement (CLA)](doc/cla/sign-cla.md).
