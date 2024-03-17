
#include "hints.h"

//                                            | Max Newline Marker

/* COURSE 1 */
hint course_1_hints[] = {

{
"How did you manage to miss this star?\n\
It's literally right next to the hub pipe...\n\
You missed this one on purpose, didn't you?",
(0)
},

{
"Collect all the red coins in the main\n\
area near the hub pipe.",
(0)
},

{
"Cross the bronto burt bridges and climb\n\
the mountain to find the star.",
(0)
},

{
"Cut down all the heavy objects to activate\n\
the cannon. Enter the cannon to get launched\n\
to the star.",
(ABILITY_FLAG_CUTTER)
},

{
"In the jungle area of the cave, there is\n\
a star piece switch. Some star pieces are\n\
hidden in the air, so be sure to look up.",
(0)
},

{
"In the cave, there are some metal grilles.\n\
Take advantage of the Phasewalk jump to\n\
platform your way up to the star.",
(ABILITY_FLAG_PHASEWALK)
},

{
"In the jungle area of the cave, there are\n\
some colored arrows that point to buttons.\n\
Shoot every single button to get the star!",
(ABILITY_FLAG_SHOCK_ROCKET)
},

{
"Follow the rails to the end of the cave. You will\n\
need the Gadget Watch to open the gate. Throw\n\
anything & everything you got at the boss!",
(ABILITY_FLAG_GADGET_WATCH)
},

};

/* COURSE 2 */
hint course_2_hints[] = {
{
"Walk to the end of Jelly Fish Fields and collect\n\
the star near the taxi stop.",
(0)
},

{
"In Jelly Fish Fields, cut the Bubble Hat down\n\
from its cage. Use the Bubble Hat ability to\n\
platform your way to the star",
(ABILITY_FLAG_CUTTER|ABILITY_FLAG_BUBBLE_HAT)
},

{
"In the city, there are some yellow platforms.\n\
Jump on them and climb the buildings until you\n\
find the star.",
(0)
},

{
"In Jelly Fish Fields, break the tiki boxes with\n\
your Bubble Hat & Net ability. Bounce on the\n\
trampolines and collect all 8 red coins.",
(ABILITY_FLAG_BUBBLE_HAT),
},

{
"In the Krusty Krab, there are 5 concrete blocks.\n\
Destroy them all with a drill or a shotgun and\n\
touch the hidden secrets that were below.",
(ABILITY_FLAG_BIG_DADDY)
},

{
"In the city, there is a big barrel. Inside, there\n\
are lots of flipswitches. Use the Knight Suit and\n\
time your ground pounds right to get them all.",
(ABILITY_FLAG_KNIGHT)
},

{
"Behind the Chum Bucket, you'll find a star behind\n\
some bars. Use the Phasewalk's vanish properties\n\
to pass through the bars and get the star.",
(ABILITY_FLAG_PHASEWALK)
},

{
"In the city, there is a second taxi stop. This\n\
will take you to the boss fight. Remember to\n\
strike only when the boss is flashing white.",
(0)
},

};

hint * hintlist[] = {
    course_1_hints,
    course_2_hints,
    course_1_hints,
    course_1_hints,
    course_1_hints,
    course_1_hints,
    course_1_hints,
    course_1_hints,
    course_1_hints,
    course_1_hints,
    course_1_hints,
    course_1_hints,
    course_1_hints,
    course_1_hints,
    course_1_hints,
};