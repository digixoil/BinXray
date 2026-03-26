# Vendor Dependencies

## Dear ImGui

- Purpose: immediate-mode desktop UI framework for BinXray.
- Location: `src/vendor/imgui`
- Source origin: mirrored from the local `XpressFormula` project vendor folder for initial skeleton bootstrap.

## Notes

- Keep vendor code isolated under `src/vendor`.
- App project compiles required ImGui core and backend translation units directly.
- During phase 2, formalize vendor update policy and pin exact upstream commit.
