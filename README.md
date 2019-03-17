# Sam's Virtual Console 🕹

Virtual console with integrated development editor.

☠️ Things in this repository are a work in progress and exist mainly to satisfy my curiosity, don't expect something stable ☠️.

## Goal

I'm experimenting with the idea of fantasy video game consoles (such as [PICO-8](https://www.lexaloffle.com/pico-8.php)) and retro game programming. With the Virtual Console project I explore the internal of old hardware (currently my focus is on the [6502](https://en.wikipedia.org/wiki/MOS_Technology_6502) and [Commodore 64](https://en.wikipedia.org/wiki/Commodore_64)) and attempt to create an environment in which programming can be fun. The long term vision is to have a way to create various virtual consoles each with their own set of constraints (memory, cpu, devices, etc) and to be able to run or develop games directly from an embedded editor.

## Development

```
$ make help
.———————————————————————————————————————.
| Sam's Virtual Console: build commands |
°———————————————————————————————————————°
Dependencies:
 - cmake
 - qmake (if building the editor)

Available tasks (default is marked by *):
*all			clean then build everything
 clean			remove files and directories generated during compilation
 samvirtassembler	compile samvirtassembler
 samvirtcpu		compile samvirtcpu
 samvirteditor		compile editor.app
 run-assembler		compile then run the samvirtassembler
 run-cpu 		compile then run the samvirtcpu
 run-editor		compile then run editor.app
 debug-assembler 	compile samvirtassembler then launch a debugger (lldb)
 debug-cpu		compile samvirtcpu then launch a debugger (lldb)
 format			format C++ source files
 help			show this help message
```

### Projects

- [Assembler](Assembler): 6502 assembler
- [CPU](CPU): 6502 emulator
- [Editor](Editor): Integrated development editor

### Ressources

- [MCS6500 Microcomputer Family Programming Manual](http://users.telenet.be/kim1-6502/6502/proman.html)
- [The Overflow (V) Flag Explained](http://www.6502.org/tutorials/vflag.html)
- [Wikibook 6502 Assembly](https://en.wikibooks.org/wiki/6502_Assembly)
- [Javascript 6502 assembler and simulator](https://skilldrick.github.io/easy6502/)
