all:
    clang --target=wasm32 -nostdlib -Wl,--no-entry --no-standard-libraries -Wl,--export-all -Wl,--allow-undefined  -o src/main.wasm src/main.c
