# llama.cpp/examples/snap-vm

This example program allows you to run LLaMA on SNAP-VM.

export RISCV_CROSS_COMPILE=1
export RISCV=1

make -j llama-snap-vm

./llama-snap-vm -m <model> -t 1 -p <prompt>

main.cpp execution trace:

-
