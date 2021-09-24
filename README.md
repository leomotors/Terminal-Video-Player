# Terminal Video Player

RIP My Eyes, Low Resolution Video Player driven by ASCII Characters

Don't Expect Quality from Here

## ✨ Features

- Play any Video, Right in your terminal

- With audio!

- and Timestamp displaying in realtime

- with Resolution adjusted automatically depends on terminal window size!

## 🌿 Dependencies

- OpenCV 4.5.3
- CMake and Build Essentials that all Linux should have
- libmpg123 and libao

  `sudo apt install libmpg123-dev libao-dev`

- FFmpeg

  `sudo apt install ffmpeg`

## ⚙️ Compile & Install

- `git clone https://github.com/Leomotors/Terminal-Video-Player`

- `cd Terminal-Video-Player`

- `mkdir build && cd build`

- `cmake .. && make`

- `sudo make install`

- `tplay "Your Video File Name" [Optional: -lxx (See src/process.cpp for more detail)]`

## 🙏 Credits

- Audio Player is copied from [Here](http://hzqtc.github.io/2012/05/play-mp3-with-libmpg123-and-libao.html) Thank you for your Code!

- Misc Credits are in Source Code
