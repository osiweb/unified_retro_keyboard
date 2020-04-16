## Unified ASCII Keyboard

This project aims to provide a (near) universal ASCII keyboard for vintage computers.  Home computers of the 1970's typically either polled a switch matrix, or interfaced to a parallel ASCII keyboard via a parallel port.

The keyboard allows use of Cherry MX keys, or Futaba MD-4PCS (aka George Risk KBM-01-01) keys.

The keyboard is designed using KiCad in order to be the most useful for anybody wishing to modify the keyboard for more specific uses, or to add to the project.

This keyboard project so far consists of:
- A classic retro-style ASCII keyboard, modeled after the ADM-3A keyboard, which
  can be also be populated to fit perfectly in an Apple II/II+ case (with corresponding Apple II keymaps), or an OSI
  case (with OSI adapter).
- A Sol-20 compatible keyboard.
- A keyscan/decoder interface module that can output parallel ASCII, and can be adapted for other protocols.
- An OSI-compatible interface module.
