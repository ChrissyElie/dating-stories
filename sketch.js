var playing = false;
var button;
var vid210;
var vid211;
var vid212;
var currentVideo;


function setup() {
  // the videos in this demo are not in the canvas
  // so don't have one
  noCanvas();
  // specify multiple formats for different browsers
  vid210  = createVideo('assets/vid210.mp4')
  vid211  = createVideo('assets/vid211.mp4')
  vid211.hide();
  vid212  = createVideo('assets/vid212.mp4')
  vid212.hide();
  currentVideo = vid210;
  currentVideo.play();
  currentVideo.size(1000, 700);
  button = createButton('play');
  button.mousePressed(toggleVid); // attach button listener
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
  currentVideo.stop();
  currentVideo.hide();
  currentVideo = newVideo;
  newVideo.size(1000, 700);
  currentVideo.show();
  currentVideo.play();
  button.html('pause');
  playing = true;
}

function keyPressed() {
  if (keyCode === 32) {
  	switchVideo(vid210);
  }
  else if (keyCode === 81) {
  	switchVideo(vid211);
  }
  else if (keyCode === 80) {
  	switchVideo(vid212);
  }
}
