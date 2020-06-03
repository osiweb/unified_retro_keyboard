## Unified Retrocomputer Keyboard Project

This project aims to provide a (near) universal collection of keyboards for vintage computers.  Home computers of the 1970's typically either polled a switch matrix, or interfaced to a parallel ASCII keyboard via a parallel port.

The keyboard allows use of Cherry MX keys, or Futaba MD-4PCS (aka George Risk KBM-01-01) keys.

The keyboard is designed using KiCad in order to be the most useful for anybody wishing to modify the keyboard for more specific uses, or to add to the project.

This keyboard project so far consists of:
- A classic retro-style ASCII keyboard, modeled after the ADM-3A keyboard, which
  can be also be populated to fit perfectly in an Apple II/II+ case (with corresponding Apple II keymaps), or an OSI
  case (with OSI adapter).
- A Sol-20 compatible keyboard.
- Keyscan/decoder interface modules that can output parallel ASCII, and can be adapted for other protocols.  The interface modules support multiple keymaps (switch selectable) and can be used with the Classic and Sol-20 keybaords, and can also replace the Apple II/II+ keyboard encoder, or drive an OSI 542 keyboard.
- An OSI-compatible interface module.
