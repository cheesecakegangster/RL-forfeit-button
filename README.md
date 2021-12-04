# RL-forfeit-button
Rocket league forfeit button (macro button) made from a "bullshit" button. Designed for a bootleg Arduino pro micro (Atmega 32u4-based).

This exact "bullshit" button: https://www.amazon.com/simhoa-Bullshit-Button-Tabletop-Sounds/dp/B08JK9K1SQ/ (couldn't find the "real original" in my country of residence)
This exact Arduino Pro Micro: https://nl.aliexpress.com/item/32825006734.html?spm=a2g0s.9042311.0.0.27424c4d9X1Uxj

Necessary tools & hardware:
- 3D-printer
- Soldering iron
- Screw drivers (PH2 to take it apart + whatever you choose to do with the additional hardware)
- Probably drills: 2.5 mm, 3.0 mm, 3.5 mm, 5.5 mm
- M3 tap & tapping wrench
- If you want to use the original nut for the battery cover, I reckon 1x M2.5x20 or M2.5x25 screw. I ruined mine a little because I didn't have a screw long enough and a DIN912 M3 screw didn't fit, so I tried drilling to 5.5 mm to allow the cap to fit but ended up drilling through the whole thing lol. Ended up using an DIN7991 M3x16 and I tapped the hole of the battery cover to M3 and it worked.
- 2x M3x12 or M3x16 (DIN912)
- 1x M3x8 or M3x6 (ISO7380, you may also get away with DIN912, DIN7991 is probably also fine)
- M3x20 (DIN7991) in case you mess up like i did
- Glue with mild filling capability (PU expanding glue for example)

- Also possible perhaps to just make everything M2.5, then you wont need a tap. But who even has M2.5?

Basic instructions:
- Print the things

- Disassemble bullshit button (screws are under the rubber pads), leave the pcb and speaker in place, keep the screws and feet for re-assembly
- Align printed thing with bullshit button
- Drill 2.5mm through holes and into the bullshit button
- Tap M3 in the 3 holes in the bullshit button that align with the printed thing

- Solder coloured wire to pin 7
- Solder black wire to any GND
- Place arduino in the designated spot and use M3x8/x6 to screw it down. the tab is supposed to be angled; it pushes the arduino securely to the opposite side and locks it in place
- Guide wires through bullshit button battery compartment slots (where the battery cover hooks hook into)
- Solder wires diagonally from each other
- Lift the pin closest to the pushbutton, opposite of the side where the speaker is (use your soldering iron to force it out of the way)
- Upload code to arduino
- Test!
- Works? Assemble and wahoo it's done
