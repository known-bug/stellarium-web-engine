# Modifications from upstream

This file documents the differences between this Knownbug fork and the
upstream [Stellarium Web Engine](https://github.com/Stellarium/stellarium-web-engine).

Published under [GNU AGPL-3.0](LICENSE-AGPL-3.0.txt) § 5(a) ("Carry prominent
notices stating that you modified it, and giving a relevant date").

---

## Maintainer

Knownbug Ltd — company no. 17087487, registered in England & Wales.

## Fork date

12 May 2026

## Original copyright

All original Stellarium Web Engine copyright notices belong to Stellarium
Labs SRL and contributors. They are preserved in the source files; no
upstream attribution has been removed.

## Modifications

The following changes have been applied on top of the upstream codebase.
All are presentation-layer / UX changes that do not alter the engine's
astronomical calculations, data sources, or public API. Original source
files are preserved with their copyright headers intact.

### Commit `4a030f9b` — visual customisations

- **`src/modules/planets.c`** — appended each planet's apparent altitude
  (in degrees) to its rendered label. A planet that previously rendered
  as `"Mars"` now renders as `"Mars (45.3°)"`. Implementation converts
  the planet's position from `FRAME_ICRF` to `FRAME_OBSERVED` per render
  to compute altitude, then formats it into the label string passed to
  `labels_add_3d`. Affects only label text; positions, rendering geometry,
  and data sources are untouched.

- **`src/modules/pointer.c`** — replaced the original four-stroke
  selection-pointer rendering with a single pulsating red concentric
  circle that expands outward from the object edge and fades to
  transparent over a 1.5-second cycle. The original four-stroke
  implementation is preserved under an `#if 0` block in the same file
  (renamed to `pointer_render_old`) so the change is easy to revert if
  needed. Affects only the on-screen selection indicator; selection
  semantics and engine API are unchanged.

### Dependency upgrades

The remaining commits ahead of upstream are routine dependency-version
bumps (Dependabot-style) inside `apps/web-frontend`. They track upstream
package versions and do not constitute material modifications to the
engine's behaviour. Not listed individually here.

## How to build the deployed version

Follow the build instructions in `README.md` ("Build the javascript version").
The artifact running at <https://knownbug.app> is produced from the `main`
branch of this repository.

## Reporting compliance issues

If you believe this fork is not in compliance with the AGPL-3.0 obligations
(missing source, broken links, undocumented modifications, etc.), please
contact <hello@knownbug.app>. We aim to respond within seven days.
