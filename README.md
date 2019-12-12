## Universal ASCII Keyboard

This project aims to provide a (near) universal ASCII keyboard for vintage computers.  Home computers of the 1970's typically either polled a switch matrix, or interfaced to a parallel ASCII keyboard via a parallel port.

The keyboard will allow use of Cherry MX keys, or Futaba MD-4PCS keys.

The keyboard supports diodes per-switch for true N-key rollover, or 
per-row (like the OSI).

The keyboard is designed using KiCad in order to be the most useful for anybody wishing to modify the keyboard for more specific uses, or to add to the project.

Goals for the keyboard:

- Drop in replacement for Ohio Scientific polled keyboards
-- Done: drop in for OSI 542 (untested). 
-- Done: keycap set available
-- To do: module for advanced 542B/C features

- Drop in replacement for Apple II keyboard
--To do: Add-in ASCII module required
--To do: Add power light and power light cover
--To do: Special Apple keycaps needed.

- Standard ASCII parallel keyboard
-- Done: Keycap set available
-- To do: Add-in ASCII keyboard
