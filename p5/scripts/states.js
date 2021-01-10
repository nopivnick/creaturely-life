/**
 * A state for every poem
 */

// function stateTutorial() {
//   isAutoPlay = false;
//   alphaValue = 0;
//   isRevealed = false;
//   removeElements();
//   poemTitle = tutorialTitle;
//   poem = tutorial;
//   print("current poem: tutorial");
//   poemPlaylist = [
//     [0, 51], // entire poem
//   ];

//   print(poemPlaylist);
//   setupPoem();
//   setupLayout();
//   displayPoem();
// }

function stateIntro() {
  isAutoPlay = false;
  alphaValue = 0;
  isRevealed = false;
  removeElements();
  poem = intro;
  poemTitle = introTitle;
  print("current poem: describe");
  poemPlaylist = [
    // [0,    15], // "Creaturely Life "
    [47, 78], // "a tactile, tangible interface "
    [137, 176], // " a collection of poems by Michael Joyce"
    [236, 259], // " a woman keeping vigil "
    [358, 391] // " knitting beside his hospice bed."
    // [0, 390], // entire poem
  ];

  print(poemPlaylist);
  setupPoem();
  setupLayout();
  displayPoem();
}

function stateIreland() {
  isAutoPlay = false;
  alphaValue = 0;
  isRevealed = false;
  removeElements();
  poem = ireland;
  poemTitle = irelandTitle
  print("current poem: ireland");
  poemPlaylist = [
    [0, 10], // "In Ireland"
    [62, 75], // "On Hallow-eve"
    [148, 194], // " holding the loose end, throw it into the dark"
    [274, 305], // " ‘who howlds my bottom of yarn?’ "
    // [336, 363] // " the man they were to marry."
    // [0, 363], // entire poem
  ];

  print(poemPlaylist);
  setupPoem();
  setupLayout();
  displayPoem();
}

function stateTitle() {
  isAutoPlay = false;
  alphaValue = 0;
  isRevealed = false;
  removeElements();
  poem = title;
  poemTitle = titleTitle;
  print("current poem: title");
  poemPlaylist = [
    [0, 2204], // the entire poem
  ];

  print(poemPlaylist);
  setupPoem();
  setupLayout();
  displayPoem();
}

function state01() {
  isAutoPlay = false;
  alphaValue = 0;
  isRevealed = false;
  removeElements();
  poem = poem01;
  poemTitle = poem01Title
  print("current poem: 01");
  poemPlaylist = [
    [0, 35], // "It is how he lives that she watches "
    [1555, 1593], // " pushing the hair back from your eyes "
    [1489, 1521], // " has our marriage come to this? "
    [53, 87], // "the dying will take care of itself"
    [1016, 1057], // "its crater swabbed with foam tipped swabs"
    [88, 127], // " it has already become a thing for them"
    [1341, 1395], // " that fucking monkey, death, let’s call it by its name"
    [1661, 1714], // " in raucous cheeps his dreadful yellow teeth exposed "
    [171, 189], // " sometimes on the "
    [193, 207], // " sill outside "
    [298, 334], // " crescents across the clouded glass "
    [767, 795], // " Watching him she longs for "
    [815, 830], // " just one more "
    [602, 611], // " a peach "
    [1774, 1782], // " a plum "
    [721, 749], // " a damp, sweet lusciousness "
    [939, 972], // " the simple kiss of early lovers"
    // [1950, 1970], // "I want to eat you up"
    [1262, 1298], // "for she is still more raven than owl"
    [2158, 2204] // " filling him like a mother bird her fledgling."
    // [0, 2204], // the entire poem
  ];

  print(poemPlaylist);
  setupPoem();
  setupLayout();
  displayPoem();
}

function state02() {
  isAutoPlay = false;
  alphaValue = 0;
  isRevealed = false;
  removeElements();
  poem = poem02;
  poemTitle = poem02Title
  print("current poem: 02");
  poemPlaylist = [
    [0, 25], // "Wrens flit upon the sill "
    [1075, 1118], // " as he sleeps the sleep of the morphine drip"
    [691, 734], // " With some things it is better at the end"
    [262, 300], // " five floors up above the forlorn park"
    [1380, 1412], // " how lovely you are living just "
    [1520, 1548], // " free of all you have to do "
    [227, 263], // " they come and go these tiny things "
    [494, 527], // " great dark things you cannot see "
    [1245, 1265], // " I want to hold you "
    [204, 218], // " dust to dust "
    [1265, 1284], // " I want to tell you"
    [1202, 1216], // " come with me, "
    [795, 812], // " among the terns "
    [1285, 1303], // " Do you remember? "
    [1045, 1076], // " these questions, into his ear "
    [1302, 1333], // " Once you were my pet and now, "
    [1343, 1359], // " you are again"
    [1561, 1598], // " this business of sleeping and waking"
    [1479, 1511], // " disappointed not to have died, "
    [1599, 1636] // " landing and pecking and setting off."
    // [0, 1636], //  the entire poem
  ];

  print(poemPlaylist);
  setupPoem();
  setupLayout();
  displayPoem();
}

// TODO: add states 03 thru 19

function state20() {
  isAutoPlay = false;
  alphaValue = 0;
  isRevealed = false;
  removeElements();
  poem = poem20;
  poemTitle = poem20Title
  print("current poem: 20");
  poemPlaylist = [
    [0, 27], // "But you see it does not end"
    [703, 729], // "K on RS, P on WS, P5, turn"
    [51, 84], // "the story has been lived and told
    [731, 756], // "sl 1, K1, psso, K1, K2tog"
    [534, 567], // "perhaps he goes on breathing Bach"
    [703, 729], // "K on RS, P on WS, P5, turn"
    [553, 583], // "breathing Bach while she knits"
    [731, 756], // "sl 1, K1, psso, K1, K2tog"
    [106, 136], // "what has happened to the birds"
    [154, 170], // "the vagrant cat?"
    [703, 729], // "K on RS, P on WS, P5, turn"
    [186, 203], // "they remain there"
    [236, 261], // "where they first appeared"
    [731, 756], // "sl 1, K1, psso, K1, K2tog"
    [263, 286], // "the shadow of the thing"
    [344, 358], // "And who she is"
    [703, 729], // "K on RS, P on WS, P5, turn"
    [731, 756], // "sl 1, K1, psso, K1, K2tog"
    [534, 567], // "perhaps he goes on breathing Bach"
    [553, 583], // "breathing Bach while she knits"
    [703, 729], // "K on RS, P on WS, P5, turn"
    [731, 756], // "sl 1, K1, psso, K1, K2tog"
    // [625, 652], // "never seen much sense in it"
    [668, 701], // "liking nonetheless the code of it"
    [703, 729], // "K on RS, P on WS, P5, turn"
    [731, 756], // "sl 1, K1, psso, K1, K2tog"
    [774, 789], // "as if the world"
    [856, 863] // "a song."
    // [0,   863], // the entire poem
    // [86,  124], // "do you want to know what has happened"
    // [171, 184], // "Of course not"
    // [568, 598], // "while she knits beside the bed"
  ];
  setupPoem();
  setupLayout();
  displayPoem();
}