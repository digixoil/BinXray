# Bin X-ray Use Cases and Roadmap

## Practical Use Cases

### 1) Spot structure in unknown files

The byte-pair scatterplot acts like a local transition fingerprint. Even when
you do not know the format, structured regions often look visibly different
from high-entropy regions. With sliding-window scrubbing, this becomes useful
across large binaries because you can inspect structure region-by-region.

### 2) Find boundaries and repeated layouts

Firmware images, save files, packet captures, proprietary blobs, database pages,
and custom logs often contain recurring blocks. The ribbon + scatterplot pairing
is effective for "where does this section start/stop?" and "where does this
pattern repeat?" work.

### 3) Compare compressed/encrypted/plain regions

Without running formal entropy tooling first, you can still quickly distinguish
noise-like regions from more organized table/header/text-like regions and then
verify at byte level.

### 4) Jump from anomaly to exact offsets

The seek loop (hover pair -> get offsets -> jump to hex) turns visualization
into an actionable workflow, not just a static image.

### 5) Explore higher-order patterns

The 3D trigram plot helps when pairwise transitions are insufficient, revealing
clusters that can hint at repeated grammar-like byte behavior.

## Best Audience (Plain Terms)

- Reverse-engineering unknown file formats.
- Scanning firmware or memory dumps for behavioral region changes.
- Locating repeated records, framed data, or table-like structures.
- Triage of corruption or suspicious regions in large binaries.
- Fast visual comparison of "organized-looking" vs "random-looking" sections.

## Highest-Value Product Additions

### Region statistics strip

Per-window entropy, unique-byte count, top-N byte frequencies, printable ratio,
and zero-byte ratio would make visual inferences explicit and measurable.

### Bookmarks, annotations, named ranges

Real investigations are iterative. Analysts need persistent markers and notes.

### Exportable findings

Export offsets, screenshots, plots, and marked ranges to JSON/CSV/PNG for reports,
writeups, and bug/security tickets.

### Compare mode (two files or two ranges)

Side-by-side or overlaid transition views would strongly support malware variant
triage, firmware patch analysis, and before/after transform checks.

### Multi-scale transition analysis

Allow byte[i] -> byte[i+n] and dynamic window sizes to expose longer-period
structure and alignment effects.

### Histogram/frequency companion views

Complements transition maps with a quick "what dominates here?" signal.

### Periodicity/repetition detector

High value for fixed-size records, interleaving, padding, and protocol frames.

### Structured decoders/templates

A major step from exploratory visualization to practical production analysis.

### Search by visual feature

Example: "find other windows similar to this region's transition density map."

### Session persistence

Persist file context, ranges, transitions, view mode, and analyst notes.

## Recommended Build Priority

1. Bookmarks and annotations.
2. Entropy + histogram strip.
3. Compare mode.
4. Structured decoders/templates.
5. Periodicity detector.

## Positioning Note

Some conclusions (for example "this region is likely compressed/encrypted") are
best treated as strong visual inference, then validated with direct byte-level
inspection and supporting metrics.
