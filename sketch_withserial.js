var serial; // variable to hold an instance of the serialport library
var fromSerial = 0; //variable to hold the data
var playing = false;
var button;
var vidloop;
var vid0;
var vid2;
var vid4;
var vid12;
var vid11;
var vid5;
var vid1;
var vid6;
var vid10;
var vid9;
var vid3;
var vid7;
var vid8;
var song;
var currentVideo;
var vids = [];
var currentNode = 0;
var text;

function preload() {
  song = loadSound('jazzloop.mp3');
}


function setup() {
  // the videos in this demo are not in the canvas
  // so don't have one
  song.loop();
  song.setVolume(0.05);
  text = createElement('h1', 'Dating Stories: An Interactive Film');
  text.id('title');
  // text.position(height/2, width/2);
  // text.style("font-family", "monospace");
  // text.style("background-color", "#2f4f4f");
  // text.style("color", "#FFFFFF");
  // text.style("font-size", "18pt");
  // text.style("padding", "10px");


  noCanvas();
  serial = new p5.SerialPort(); // make a new instance of  serialport librar  
  serial.on('list', printList); // callback function for serialport list event
  serial.on('data', serialEvent); // callback for new data coming in  
  serial.list(); // list the serial ports
  serial.open("/dev/cu.usbmodem1411"); // open a port
  vidloop = createVideo('assets/vidloop.mp4')
  vid0  = createVideo('assets/vid0.mp4');
  vid0.hide();
  vid0.onended(videoEnded);
  vids.push(vid0);
  vid1  = createVideo('assets/vid2.mp4');
  vid1.hide();
  vid1.onended(videoEnded);
  vids.push(vid1);
  vid2  = createVideo('assets/vid1.mp4');
  vid2.hide();
  vid2.onended(videoEnded);
  vids.push(vid2);
  vid3 = createVideo('assets/vid3.mp4');
  vid3.hide();
  vid3.onended(videoEnded);
  vids.push(vid3);
  vid4  = createVideo('assets/vid4.mp4');
  vid4.hide();
  vid4.onended(videoEnded);
  vids.push(vid4);
  vid5  = createVideo('assets/vid5.mp4');
  vid5.hide();
  vid5.onended(videoEnded);
  vids.push(vid5);
  vid6  = createVideo('assets/vid6.mp4');
  vid6.hide();
  vid6.onended(videoEnded);
  vids.push(vid6);
  vid7 = createVideo('assets/vid7.mp4');
  vid7.hide();
  vid7.onended(videoEnded);
  vids.push(vid7);
  vid8 = createVideo('assets/vid8.mp4');
  vid8.hide();
  vid8.onended(videoEnded);
  vids.push(vid8);
  vid9  = createVideo('assets/vid9.mp4');
  vid9.hide();
  vid9.onended(videoEnded);
  vids.push(vid9);
  vid10  = createVideo('assets/vid10.mp4');
  vid10.hide();
  vid10.onended(videoEnded);
  vids.push(vid10);
  vid11  = createVideo('assets/vid11.mp4');
  vid11.hide();
  vid11.onended(videoEnded);
  vids.push(vid11);
  vid12  = createVideo('assets/vid12.mp4');
  vid12.hide();
  vid12.onended(videoEnded);
  vids.push(vid12);
  
  currentVideo = vidloop;
  currentVideo.size(1000, 700);
  currentVideo.loop();
  button = createButton('play');
  button.mousePressed(toggleVid); // attach button listener
  button.hide();
}

// plays or pauses the video depending on current state
function toggleVid() {
  if (playing) {
    currentVideo.pause();
    button.html('play');
    playing = false
  } else {
    currentVideo.play();
    button.html('pause');
    playing = true
  }
  //playing = !playing;
}
 
function switchVideo(newVideo) {
  // TODO This is where the text would be hidden .hide()
  currentVideo.stop();
  currentVideo.hide();
  currentVideo = newVideo;
  newVideo.size(1000, 700);
  currentVideo.show();
  currentVideo.play(0);
  button.html('pause');
  playing = true;
}

function keyPressed() {
//  console.log('I pressed ' + keyCode);

//   // serial.write(keyCode);

if (keyCode === 32) {
  currentVideo.play();
  }
}

//   	switchVideo(vid6);
//   }
//   else if (keyCode === 81) {
//   	switchVideo(vid10);
//   }
//   else if (keyCode === 80) {
//   	switchVideo(vid9);
//   }
// }


// get the list of ports:
function printList(portList) {
  for (var i = 0; i < portList.length; i++) {
    // Display the list the console:
    console.log(i + " " + portList[i]);
  }
}

function serialEvent() {
  var inString = serial.readLine();
  if (inString.length > 0) {

    vidNumber = Number(inString.trim());
    console.log(vidNumber)
    var newVideo = vids[vidNumber];
    currentNode = vidNumber;
    text.hide();
    console.log(newVideo)
    switchVideo(newVideo);
   }
}

function videoEnded() {
  console.log('VID ENDED');
  if (currentNode == 5 || currentNode === 7 || currentNode === 8 || currentNode === 9 || currentNode === 10 || currentNode === 11 || currentNode === 12) {
    serial.write(127);
    currentNode = 0;
    //switchVideo(vid0);
    switchVideo(vidloop);
    text.show();
    currentVideo.loop();

  } else {
    // TODO this is where the text would be shown .show()
    serial.write(0);
  }
}