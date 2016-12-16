var playing = false;
var button;
var vid000;
var vid100;
var vid110;
var vid111;
var vid112;
var vid120;
var vid200;
var vid210;
var vid211;
var vid212;
var vid220;
var vid221;
var vid222;
var currentVideo;


function setup() {
  // the videos in this demo are not in the canvas
  // so don't have one
  noCanvas();
  // specify multiple formats for different browsers
  vid000  = createVideo('assets/vid000.mp4')
  vid100  = createVideo('assets/vid100.mp4')
  vid100.hide();
  vid110  = createVideo('assets/vid110.mp4')
  vid110.hide();
  vid111  = createVideo('assets/vid111.mp4')
  vid111.hide();
  vid112  = createVideo('assets/vid112.mp4')
  vid112.hide();
  vid120  = createVideo('assets/vid120.mp4')
  vid120.hide();
  vid200  = createVideo('assets/vid200.mp4')
  vid200.hide();
  vid210  = createVideo('assets/vid210.mp4')
  vid210.hide();
  vid211  = createVideo('assets/vid211.mp4')
  vid211.hide();
  vid212  = createVideo('assets/vid212.mp4')
  vid212.hide();
  vid220; = createVideo('assets/vid220.mp4')
  vid220.hide();
  vid221; = createVideo('assets/vid221.mp4')
  vid221.hide();
  vid222; = createVideo('assets/vid222.mp4')
  vid222.hide();
  currentVideo = vid000;
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
