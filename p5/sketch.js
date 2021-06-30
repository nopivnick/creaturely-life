/**
 * Noah Pivnick
 * Final Project, 2018 Fall
 * Intro to Computational Media 2233.004 (Mimi Yin)
 * Intro to Physical Computing 2301.003 (Tom Igoe)

 * Acknowledgements:
 * - Michael Joyce, friend and mentor, writer and poet, for sharing with me his unpublished poems
 * - Giwon Park for help with code and urging me to use p5.dom
 * - Allison Parish for sharing with me a crucial example of creating arrays of spans by character
 * - Brent Baily for helping me sort out logic that correctly iterated through the fragment playlist
 * - Ashley Lewis for walking me through state machines
 * - Mimi Yin, Tom Igoe, and Mithru Vigneshwara for their instruction, critique, and patience

 * Instructions to run this sketch on a localhost using two browser windows, one of which is fullcreen on an external monitor:
 * - If running Arduino IDE, make sure serial monitor is closed
 * - Run P5.serialcontrol.app
 * - Select serial port w/ Arduino from dropdown menu
 * - Open serial port
 * - Enable serial port
 * - Check P5.serialcontrol.app for the IP address assigned to the laptop
 * - Confirm `serial = new p5.SerialPort("<arduino-serial-port-IP>")` in function setup() is set correctly
 * - Save sketch in P5 web editor
 * - P5 web editor » File menu » Download sketch files to Desktop
 * - Change directory name to something appropriate
 * - Connect external monitor
 * - System Preferences » Displays » Arrangement » turn mirroring *off*
 * - Open Terminal
 * - $ cd ./<directory name>
 * - $ python -m SimpleHTTPServer
 * - Open two Chrome windows and enter http://<arduino-serial-port-IP>:8000 in each
 * - Push one Chrome window to external display and make fullscreen (Cmd+Shift+F )
 */

// p5.serialcontrol stuff
let serial; // declare a global variable for serial class
let portName = '/dev/cu.usbmodem1411';
let currentCount;
let previousCount = 0;
let waitCount; // variable to set how many crank rotations over serial before starting text effect

// p5.dom stuff
let header; // to hold the name / number of the poem / state
let paragraph; // to hold the body of the poem
let footer; // to hold the prompt

// poem content stuff
// let tutorial = "Turn the crank on the yarn ball winder to begin ...";
// let tutorialTitle = "How to";
let intro = "Creaturely Life explores the winding of yarn as a tactile, tangible interface for reading electronic text. The piece takes its name from a collection of poems by Michael Joyce, written in stream of consciousness from the perspective of a woman keeping vigil over her dying husband. In the final poem of the series, she recalls having found some small solace knitting beside his hospice bed.";
let introTitle = "To begin, turn the crank clockwise...";
let ireland = "In Ireland, the term 'bottom' means a clue or a ball of yarn. On Hallow-eve, young girls would make their way to a limekiln with a ball of yarn and, holding the loose end, throw it into the dark. If the string went taught as they rewound the length of yarn, they'd call out ‘who howlds my bottom of yarn?’ and expect to hear the name of the man they were to marry.";
let irelandTitle = "A clue, a ball of yarn..."
let title = "Creaturely life: twenty pre-elegies by Michael Joyce";
let titleTitle;
let poem01 = "It is how he lives that she watches she insists, for the dying will take care of itself, it has already become a thing for them, the dying, a disconsolate creature perched sometimes on the wide sill outside the window where yesterday a window washer swung from the canvas harness swiping interlaced crescents across the clouded glass as if a drab angel. But death, death takes the form of a monkey, the Mandrillus sphinx, the blue ridges of its muzzle fierce as a Maori tattoo below amber eyes, sitting propped on its magnificently multi-colored rump, the colors of cotton candy, sucking the flesh from a peach that someone has left on a tray, such a bounty gone to waste hereabouts, the dying having no appetite for such a damp, sweet lusciousness as a random peach. Watching him she longs for dampness once again, just one more what? One more anything, the feeling as he descends over her smooth belly to the place between her thighs, or the simple kiss of early lovers, before the mouth becomes perfunctory, dry, its crater swabbed with foam tipped swabs, which the bright young thing, the one who brings a smile to him, said “you can suck on like a lollipop.” It was hard not to hate her for her youth or begrudge an innocence that cannot suspect a graying (for she is still more raven than owl) woman of bawdy, let alone lasciviousness, that fucking monkey, death, let’s call it by its name, eating the conventional banana like a bewildered frau on an amateur porn site, wondering how has our marriage come to this? three minute segments of fellatio, pushing the hair back from your eyes awaiting the crowning moment, the fucking mandrill, sphinx, laughing in raucous cheeps his dreadful yellow teeth exposed between the nostrils and lips red as if it had just fed upon a plum or the still bloody corpse of a young antelope. And now she wants to know would you like to eat anything, this girl, “I can bring you a tray if you want to stay.” Yes, I want to eat you up, to suck the life from you until you moan not knowing whether you are coming or going, so to speak, feeding the sweet mush back to him, forcing my tongue between the dry lips like a swab, filling him like a mother bird her fledgling.";
let poem01Title = "(1)";
let poem02 = "Wrens flit upon the sill as well, land and peck and set off again as if feeding upon miniscule seeds, invisible pollen, or perhaps dander, the world being a swirl of dander according to the science pages, dust to dust and such, they come and go these tiny things five floors up above the forlorn park, so clearly just an annex to the vast parking lots row on row of SUVs that stretch out like gravestones along the LIE. We have grown into acronymic times and trucks disguised as passenger cars, great dark things you cannot see around or through, and so process along the expressway as if mourners en route to a stranger’s funeral or to Orient Beach along the North Fork on a summer weekend. With some things it is better at the end, in winter, cocooned in a hooded, black parka, making your way among the terns at the dull edge of the dirty tidal froth, or closer in at Southhold along the saltwater wetlands of Arshamomque Pond. Is it wrong to want to be off somewhere, to come and go as freely as these drab birds? She whispers this question, these questions, into his ear as he sleeps the sleep of the morphine drip, dire sister of the oxycontin dreams. Won’t you get up for just a little while and come with me, to the sea, the sea of love. I want to hold you, I want to tell you. Do you remember? Once you were my pet and now, I suppose, you are again. I watch you and think how lovely you are living just now, struggling against these hallucinatory dreams, waking a little disappointed not to have died, not to be free of all you have to do just now, all this business of sleeping and waking, landing and pecking and setting off.";
let poem02Title = "(2)";
// let poem03 = "What evidences of living she could say if asked (but by whom?) having made such observance her new science: the faint sway, for instance, of the feathery hairs within his nostril like a Japanese landscape in miniature, thin reeds upon a cavern pool raked by a breeze perfumed with apple blossoms. It is the scent of opiates she supposes, still he works at this, his is the engine of these breezes, although mostly when awake his eyes are indistinct, not so much dull as deep, the blue of beach glass, rocked and polished in the underlying tides, the rip beneath that swells the crests farther out where the boys await on their boards, slick as seals, paddling listlessly. These eyes not the terrifying countenance of the cows (nor the angels) at Duino, “who do not, if one touches them, fall apart into a heap of words,” but who persist, this Rilke does not write exactly to the Princess Marie von Thurn und Taxis, they persist in mystery, they are themselves mystery, this is their being, the terror before which one sits and stares, looking for him there like a bauble lost in a tidal pool, a pretty ring or a holy medal (are there any longer such things?) pinned to the dress of a boy at baptism or to the bib of a hospital gown (surely it is a misprision to call them so, what ceremony or ball masque calls for this rude covering “fastened behind”?)– I’ve lost my place, she thinks, in this inventory of living (not living things, mind you, but living!); when– there!– as if on cue by way of further evidence he kicks free the bottom of a leg from the sheet where they persist in tucking him in, kicking free a life-long habit she can attest to who’s slept a hundred times a hundred nights next to him more or less, but to say now less, no more, seems to her maudlin, sleeping here in the chair counts she insists (to whom, she realizes now, is herself) and twice this week has crawled in and curled with him there, like twin commas interposed, yin and yang. Kicks free the other just then (it’s him, really, who is the measure of her insistence), wishing all his life to be born from whatever enclosures, do you see? She does, she sees the irregular black ankle bracelet now into which the dog bite has healed after years, in the form of a black crown, the beast gripping the ankle in its powerful jaw, teeth sunk to the bone, not fate or destiny but a dumb instance of chance, an indifferent hound, not attacking him exactly, but rather the figure in black moving along the sidewalk beyond the chainlink fence the hound had smashed against a hundred times before this one time the gate gave in where the mad woman had failed to latch it.";
// let poem04 = "She feels no affinity for the stray cat that patrols the postage stamp park below, its scraggly tail (her language is reduced to this: stray and scraggly, some discomfort, breathing comfortably, and the like) like a wire– or not that, a bottle washer, do they still make those?; its color soot, at least from this high up, although she would like to think it the color of rich velvet, she who has no sympathy for cats, their solitariness and sinuosity not hers, not hers to wind among the furniture, back curled up like a cartoon feline, she all her life moving erect, a word reserved she supposes for matrons or sexual organs, his having almost turned blue, hooded and shrunken as if preparing to greet its maker, its modest retreat surely not intended for the aide who treats it like meat when she baths him, the bright silver bowl of suds propped against his hip, her sponge unexpectedly the fairest shade of lavender and worn like a courtesan’s glove, her smile likewise, asking her “Would you rather do this for him or take this moment to step out?” What choices else, she does not ask this fair haired child, freckles on her cheek and upper breast when she bends over him. There was a time when he would not have missed this, taking advantage of every gap and vista upon the rich plenitude of women’s bodies. It is he who is like a cat, of course, prowling crevice and remove even in this sleep.";
// let poem05 = "(5)";
let poem20 = "But you see it does not end, the living, even when the story has been lived and told; do you want to know what has happened to the birds upon the sill or the vagrant cat? Of course not, they remain there where they were left as well as where they first appeared, the shadow of the thing an equal to the thing itself under certain circumstance. And who she is now they have wiped from the tiny bathroom mirror just beyond the bed where she greeted it each morning and bid it good night when the corridor lights dimmed. Or perhaps not, perhaps he goes on breathing Bach while she knits beside the bed although in truth she has never seen much sense in it, the knitting, liking nonetheless the code of it, K on RS, P on WS, P5, turn, sl 1, K1, psso, K1, K2tog, turn, and so on as if the world’s purpose (this the apple tree pattern for a baby’s blanket) were a song.";
let poem20Title = "(20)";
let poemNext = "To continue, turn the poem selector one click to the right..."

let poem;
let poemTitle;

// playlist stuff
let playlist = []; // an array to store the current poem's playlist of poem fragments
let playlistIndex = []; // an array to store the current poem's playlist indexes
let fragmentIndex = []; // an array to store the current poem's current fragment's indexes
let fragmentInOut = []; // an array to store the current poem's current fragment's start and stop indexes

// poem reveal stuff
let alphaValue = 0;
let isRevealed = false;

// keyboard control stuff
let isAutoPlay = false;


/**
 * P5 sketch setup function
 */

function setup() {
  noCanvas();

  // p5.serialcontrol stuff
  serial = new p5.SerialPort("10.17.246.184"); // instantiate a new serial object
  serial.on('list', printList); // list the available serial ports
  serial.on('connected', serverConnected); // callback for connecting to the server
  serial.on('open', portOpen); // callback for the port opening
  serial.on('data', serialEvent); // callback for when new data arrives
  serial.on('error', serialError); // callback for errors
  serial.on('close', portClose); // callback for the port closing
  serial.open(portName);

  // p5.dom stuff
  stateIntro(); // the first state that begins the interaction
}


/**
 * P5 sketch draw loop
 */

function draw() {
  displayPoem();
  // print("function: draw()")
}

// // TODO: reset the current poem using the keyboard
// function resetPoem() {
// }

// // TODO: reset the entire piece using the keyboard
// function resetEntireSketch() {
// }


/**
 * Serial data coming from the Arduino
 */

function serialEvent() {
  // the Arduino should be sending ASCII over serial
  let serialIn = serial.readLine(); // declare a variable to store incoming serial data as a string

  // listen for a new rotary button press
  if (serialIn == "rotary button: pressed") {
    print("rotary button: pressed");
    stateIntro();

    // listen for a new rotary dial position
  } else if (serialIn == "rotary position: 1") {
    stateIntro();
    print("rotary position: 1");
  } else if (serialIn == "rotary position: 2") {
    stateIreland();
    print("rotary position: 2");
  } else if (serialIn == "rotary position: 3") {
    state01();
    print("rotary position: 3");
  } else if (serialIn == "rotary position: 4") {
    state02();
    print("rotary position: 4");

    // TODO: listen for rotary positions 5 - 19

  } else if (serialIn == "rotary position: 5") {
    state20();
    print("rotary position: 5");

    // listen for a new hall effect sensor tick
  } else if (serialIn.length > 0 && serialIn.length < 5) { // if the incoming serial string is between 1 - 4 characters
    currentCount = Number(serialIn); // translate incoming serial string to a number

    if (currentCount > previousCount) {
      previousCount = currentCount;
      fragmentIndexIncrease();
    } else if (currentCount < previousCount) {
      previousCount = currentCount;
      fragmentIndexDecrease();
    }
    // print("tick");
  }
  // print(currentCount);
}

function fragmentIndexIncrease() {
  fragmentIndex++;
  //print("fragmentIndex *in*creased")
}

function fragmentIndexDecrease() { // just a placeholder for the time being
  // print("fragmentIndex *de*creased")
}


/**
 * Every poem needs an array for its playlist and its in & out cues
 */

function setupPoem() {
  print("function: setupPoem()")
  playlistIndex = 0; // begin with the first fragment in the playlist
  fragmentIndex = 0; // begin with the first character in the fragment
  fragmentInOut = playlist[playlistIndex];
}


/**
 * Every poem uses the same layout in p5.dom
 */

function setupLayout() {
  print("function: setupLayout()")

  // create the first <p> to hold the title of the current poem / state
  header = createP();
  header.html(poemTitle);
  header.style('font-size', '36px');
  header.style('font-style', 'italic');
  header.style('color: rgba(100, 100, 100, 1)');
  // header.style('margin', '150px');
  header.style('margin-top', '150px');
  header.style('margin-bottom', '100px');
  header.style('margin-right', '150px');
  header.style('margin-left', '150px');

  // create the second <p> to hold the body of the current poem / state
  paragraph = createP();
  paragraph.style('font-size', '30px');
  // paragraph.style('margin', '150px');
  paragraph.style('margin-top', '100px');
  // paragraph.style('margin-bottom', '200px');
  paragraph.style('margin-right', '150px');
  paragraph.style('margin-left', '150px');
  paragraph.style('color: rgba(0, 0, 0, 0)');

  // create the third <p> to hold the proceed to next poem / state text
  footer = createP();
  footer.style('font-size', '26px');
  // footer.style('margin', '150px');
  footer.style('margin-top', '100px');
  // footer.style('margin-bottom', '200px');
  footer.style('margin-right', '150px');
  footer.style('margin-left', '150px');
  footer.style('color: rgba(0, 0, 0, 0)');

  // create an array filled with each character of the current poem wrapped in <span> tags
  for (let i = 0; i < poem.length; i++) {
    let character = poem.charAt(i); // variable for use with if statement to convert '\n' to '<br>'
    let span = createSpan(poem.charAt(i));
    // if (character == "\n") {
    //   character = '<br>'
    // }
    span.style('position: relative');
    span.style('color: rgba(0, 0, 0, 0)');
    paragraph.child(span); // make each <span>char</span> a child of the paragraph
  }
}


/**
 * This is the guts of the interaction, called from each state
 */

function displayPoem() {
  let children = selectAll('span', paragraph);
  if (fragmentIndex === 0) {
    fragmentIndex = fragmentInOut[0];
  }
  // if the current fragment reaches it's last character
  if (fragmentIndex === fragmentInOut[1]) {
    if (playlistIndex < playlist.length - 1) {
      // increment the index value for the ins & outs array
      playlistIndex++;
      for (let i = 0; i < children.length; i++) {
        // color wipe the current fragment
        children[i].style('color: rgba(0, 0, 0, 0)');
      }
      // move to next fragment in array of fragments
      fragmentInOut = playlist[playlistIndex];
      console.log('playlist index: ', playlistIndex);
      console.log('fragment in & out:', fragmentInOut);
      // reset fragmentIndex to the first index of the next fragment
      fragmentIndex = fragmentInOut[0];
    } else {

      // when you reach the end of the ins and outs array, reset
      // playlistIndex = 0;
      // fragmentInOut = playlist[playlistIndex];


      //       if(frameCount % 2 == 0 && alphaValue < 1){
      //         alphaValue += 0.01;

      //         console.log("alphaValue", alphaValue);
      //       }

      //         for (let i = 0; i < children.length; i++) {
      //           // color wipe the entire poem
      //           children[i].style('color: rgba(0, 0, 0, ' + alphaValue + ')');
      //         }

      isRevealed = true;
    }
  }
  //
  if (fragmentIndex >= fragmentInOut[0] && fragmentIndex < fragmentInOut[1]) {
    // print('here');
    children[fragmentIndex].style('color: black');
  }

  if (isAutoPlay == true) {
    if (frameCount % 4 == 0) { // to slow down the auto play, increase the modulus
      // print(frameCount, "MOVE");
      fragmentIndex++;
    }
  }

  if (isRevealed == true) {
    if (frameCount % 8 == 0) { // to slow down the reveal, increase the modulus
      if (alphaValue < 1) {
        alphaValue += 0.01;
        if (alphaValue >= 0.5) {
          print("alphaValue passed 0.5");
          footer.html(poemNext);
        }
      } else {
        /*
        //use below to reset the reveal animation
        // isRevealed = false;
        // alphaValue = 0;

        // use below to reset the entire interaction (inverted for some reason)
        playlistIndex = 0;
        fragmentIndex = 0;
        */
      }
      // print("alphaValue", alphaValue);
    }
    // fade-in the entire poem by incrementing the alphaValue
    for (let i = 0; i < children.length; i++) {
      children[i].style('color: rgba(0, 0, 0, ' + alphaValue + ')');
    }
  }
}


/**
 * Hotkey settings for interacting w/ the sketch w/o serial input from the Arduino
 */

function keyPressed() {
  if (keyCode === UP_ARROW) {
    fragmentIndex++;

    // TODO: reverse step-thru-playlist currently not working

  } else if (keyCode === DOWN_ARROW) {
    fragmentIndex--;
  } else if (keyCode === 190) {
    if (isAutoPlay == true) {
      isAutoPlay = false;
    } else {
      isAutoPlay = true;
    }
  } else if (keyCode === 65) {
    print("key pressed: a");
    stateTutorial();
  } else if (keyCode === 83) {
    print("key pressed: s");
    stateIntro();
  } else if (keyCode === 68) {
    print("key pressed: d");
    stateIreland();
  } else if (keyCode === 70) {
    print("key pressed: f");
    stateTitle();
  } else if (keyCode === 49) {
    print("key pressed: 1");
    state01();
  } else if (keyCode === 50) {
    print("key pressed: 2");
    state02();
    // } else if (keyCode === 51) {
    //   print("key pressed: 3");
    //   state03();
    // } else if (keyCode === 52) {
    //   print("key pressed: 4");
    //   state04();

    // TODO: add states 05 thru 19

  } else if (keyCode === 80) {
    print("key pressed: p");
    state20();
  } else if (keyCode === 90) {
    print("key pressed: z");
    poemCharIndex();
  } else if (keyCode === 88) {
    print("key pressed: x");
    playlistCharIndex();
  }
  return false; // turns off any browser-specific default key
}


/**
 * Functions to help with strings and indexes
 */

//generate a text file that references each character in the poem to its index value
function poemCharIndex() {
  let poemCharCount = [];
  for (i = 0; i < poem.length; i++) {
    // print(poem[i] + " is at index [" + i + "]");
    poemCharCount.push(poem[i] + " - [" + i + "]");
  }
  print("generating char-index_" + poem + ".txt");
  saveStrings(poemCharCount, 'char-index_X.txt'); // print to .txt file
}

// print to console total number of characters in the current poem's playlist
function playlistCharIndex() {
  let playlistCharCount = 0;
  for (i = 0; i < playlist.length; i++) {
    playlistCharCount += (playlist[i][1] - playlist[i][0]);
  }
  print("total number of characters in playlist:", playlistCharCount);
  print(playlist);
}

// // TODO: calculate the In & Out indexes using search by fragment
// function findFragmentInOut() {
//   let fragment = "Visit sl 1, K1, psso, K1, K2tog, turn, and so on Rashida";
//   let search_term = "sl 1, K1, psso, K1, K2tog, turn, and so on";
//   let poemFragmentIn = fragment.search(search_term);
//   var poemFragmentInOut = fragment.slice(poemFragmentIn, poemFragmentIn + search_term.length);
//   print(fragment.slice(poemFragmentIn, poemFragmentIn + search_term.length));
// }


/**
 * Functions used in conjunction with p5.serialcontrol
 */

// get a list of serial port names and put them in an array called portList
function printList(portList) {
  // loop through the array of serial port names
  for (var i = 0; i < portList.length; i++) {
    // and print the list to console
    print(i + " " + portList[i]);
  }
}

function serverConnected() {
  print('connected to server.');
}

function portOpen() {
  print('the serial port opened.')
}

function serialError(err) {
  print('Something went wrong with the serial port. ' + err);
}

function portClose() {
  print('The serial port closed.');
}