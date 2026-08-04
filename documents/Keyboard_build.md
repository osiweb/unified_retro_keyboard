# Keyboard build notes
## Preparing the Keyboard PCB
I recommend installing the diodes and resistors at ALL switch positions.  Doing so will allow you to install additional switches later, and will give you flexibility to modify the keymap.  Installing the components is easiest before the switches are installed.

1. The keyboard is too big for most PCB holders. To keep the components flat as
   you insert them, I suggest taping the keyboard PCB to the edge of your bench,
   and install two rows at a time.

   <img alt="Secure the PCB with space for the leads" src="build-images/Tape_to_table.jpg" height=50% width=50%>

1. Using a lead-bender will help speed up the process and can help produce a
   neater result. However, neatness is not critical, as the diodes will be
   mostly hidden.
   
   <img alt="Lead bending tool" src="build-images/bend_leads.jpg" height=50% width=50%>

1. Check that the diodes are all facing the same (correct) direction.

   <img alt="" src="build-images/Install_Diodes.jpg" height=50% width=50%>

1. Once the diodes are inserted, I suggest using a piece of painters tape to
   keep then in place when you flip over the board for soldering.

   <img alt="Use Painters' tape to secure components" src="build-images/Tape_parts_in_place.jpg" height=50% width=50%>

1. After installing the diodes, install all the through-hole resistors.

   <img alt="All parts installed" src="build-images/All_TH_parts_installed.jpg" height=50% width=50%>

1. Finally, flip over the PCB and install the 40-pin connector on the back side
   (opposite side from the diodes and resistors).
   
   <img alt="Connector is opposite side fromg the through-hole components"
   src="build-images/Connector_on_back.jpg" height=50% width=50%>

1. It's important that the connector is seated flat to the PCB. To ensure a
   properly seated connector, first tack pins on opposite corners of the
   connector. Then, applying heat to one tacked pin, press the connector flat
   onto the PCB. You will feel a small "snap" as the connector seats. Repeat for
   the other tacked pin.

   <img alt="Tack corners of connector for flush install" src="build-images/Install_resistors.jpg" height=50% width=50%>


## Preparing the Aligner (futaba)

## Combining the PCB and aligner (futaba switches)
For futaba switches, no standoffs are required between the aligner and PCB,
   since the futaba switches provide sufficently sturdy mechanical support.
   
1. For the futaba aligners, the simplest way to assemble is to install all the
   key switches in the aligner by press-fitting them into place. Install the
   switches necessary for the keyboard you plan to build. Shown below is the
   switch configuration for the Apple II+ keyboard.
   
1. Install the cherry MX PCB-mount stabilizers onto the PCB.

   <img alt="Install the stabilizers" src="build-images/pcb_mount_stabilizers.jpg" height=50% width=50%>

1. Line up the pins of the switches in the aligner assembly with the PCB. The
   two assemblies should "zip" together easily. If you feel resistance, take the
   assemblies apart and check the pins on all the switches to make sure none are
   bent.

1. Once the assemblies are combined, it's important to make sure that the
   switches are seated flush on the PCB. To do this, first tack ONE pin on each
   of the four switches at the corners of the keyboard.
   
1. Now, one by one, reheat each tacked pin while pressing the corresponding
   switch tightly against the PCB. You should feel a small "snap" as the key
   seats. Remove the heat, and repeat for the pins on all four corners. Finally,
   solder the second pin on each of the four corner keys.

1. Repeat the above for the spacebar and the middle key on the top row.

   <img alt="Tack down switches at the edges first" src="build-images/solder_switches.jpg" height=7% width=75%>


1. Now, solder in all the other keys.



### The Spacebar Stabilizer
#### Cherry MX keys
##### Stabilizer hardware
The keyboard is designed to accommodate PCB-mounted Cherry-MX compatible Spacebar aligner hardware.  Most standard aligner kits come with pre-bend rods for a 6.25u spacebar.  Since the 8u spacebar in the retro-keyboards, you will need to bend your own rod.  I have included some sources for the rods below (1).
##### Bending the stabilizer rod
The aligner PCB includes a guide for bending the stabilizer.

1. Start by creating a 90 degree bend about 2 cm from the end of the rod.  This allows enough room to clip the end down to the correct length later.

    <img alt="First Bend" src="build-images/rod_first_bend.jpg" height=50% width=50%>

1. Insert the bent end into one guide hole, and, keeping the rod as flat to the board as possible, use the second guide hole to estimate the position of the second bend.  Your estimate should be about 1mm short to allow for a bending radius.  Once you have the pliers positioned on the rod, make your 90 degree bend.

    <img alt="Insert Rod in Guide" src="build-images/rod_insert_first_arm.jpg" height=50% width=50%>

1. Look along the length of the rod to make sure that both "arms" are in line.  If necessary, align the two arms by twisting about the axis of the axis of the rod.

1. Test the fit of the rod by inserting it into the guide holes.  Adjust as needed.

    <img alt="Test Fit" src="build-images/test_fit_too_long.jpg" height=50% width=50%>

1. Clip the arms of the rod to about 11 mm.

    <img alt="Clip Arms to Length" src="build-images/stabilizer_rod_timmed_arms.jpg" height=50% width=50%>


1. Install the Cherry MX stabilizers to the board.

1. Install the spacebar and insert the rod.

#### Futaba MD4-PCS keys
##### Stabilizer hardware
See the Cherry MX section above for notes on installing the Cherry MX stabilizer hardware and bending the spacebar stabilizer rod.

##### Longer Stabilizer posts for Futaba

The Futaba aligner PCB includes two stabilizer posts, allowing the futaba keys to be used with the Cherry MX PCB-mount stabilizers.

<img alt="Futaba stabilizer adapter posts" src="build-images/pre-breakaway.jpg" height=50% width=50%>

1. Remove both posts from the PCB.  Newer revisions of the aligner board include perforations for easier break-away of the posts.

    <img alt="Break away posts from aligner" src="build-images/cutting_post.jpg" height=50% width=50%>

1. Be sure to file away any excess material from the breakaway tab.

    <img alt="Broken offfiling" src="build-images/futaba_posts_before_filing.jpg" height=38% width=38%> <img alt="Removed breakaway tabs" src="build-images/futaba_posts_breakaway_filed_off.jpg" height=38% width=38%>

1. File away the area marked "File to 1.5mm".  The aligner includes a thickness gauge to test fitting, but it turns out that manufacturing tolerances are not adequate, and the gauge is not reliable.  Use a spare key cap to test the thickness.  The post should require some pressure to inert into the keycap base.

1. The post should be just under 4mm wide.  The post in this example is an early revision that was specified at 4mm, and ended being a sliver too wide to fit the keycap base.  It required a alittle extra filing along one side to fit properly.  The posts on newer revs are thinner and should not require extra filing to narrow side-to-side width.

    <img alt="Posts before and after filing" src="build-images/futaba_posts_before_and_after.jpg" height=50% width=50%>

    <img alt="Posts ready to install" src="build-images/filed_futaba_posts.jpg" height=50% width=50%>

1. The posts should be just tight enough to require a pair of pliers to insert.  Use pliers to insert both posts fully.  Use a ruler or caliper to ensure the prodruding portions of both posts are the same length.

<img alt="Press the posts into the spacebar" src="build-images/futaba_posts_press_into_spacebar.jpg" height=50% width=50%>

1. Install the spacebar center mount on the spacebar key, aligning the posts so that they slide into the PCB-mounted stabilizers.

1. Holding down the spacebar, align the arms stabilizer rod with the holes in the posts, and then snap the rod into place at the front of the stabilizer mounts.

<img alt="Stabilizer installed" src="build-images/stabilizer_installed_futaba.jpg" height=50% width=50%>




