set auto-load safe-path /
target remote:3333
b main
set disassemble-next-line on
monitor reset halt
c