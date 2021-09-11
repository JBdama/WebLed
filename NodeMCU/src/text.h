class files {
	String get_html() {
		String message =F("<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="utf-8">
  <title>The Color Picker</title>
  <link rel="stylesheet" href="colorpicker.css">
  <link rel="stylesheet" href="slider.css">
  <link rel="stylesheet" href="main.css">
  <link rel="stylesheet" href="nav.css">
</head>

<body>
  <div class="Wrapper" id="top">
    <div class="tab top">
      <div class="buttonwrap">
        <button id="buttonPower" onclick="togglePower()" class="tgl"><i class="icons">&#xe08f;</i>
          <p class="tab-label">Power</p>
        </button>
        <button id="buttonSync" onclick="toggleSync()" class="tgl"><i class="icons">&#xe116;</i>
          <p class="tab-label">Sync</p>
        </button>
      </div>
      <div id="briwrap">
        <p class="hd">Brightness</p>
        <div class="il">
          <i class="icons slider-icon" onclick="toggleTheme()">&#xe2a6;</i>
          <div class=sliderwrap il>
            <input id="sliderBri" type="range" min="1" max="255" value="128" />
            <div class="sliderdisplay"></div>
          </div>
        </div>
      </div>
      <iframe id="liveview" src="about:blank"></iframe>
    </div>
  </div>
  <div class="fx_buttons left">
    <button class="inactive" onclick="selectButton('solid')" id="solid"> Solid </button>
    <button class="inactive" onclick="selectButton('rainbow')" id="rainbow">Rainbow </button>
    <button class="inactive" onclick="selectButton('glow')" id="glow"> Glow </button>
  </div>
  <div class="inpu centered">
    <div class="color-flex flex">
      <div class="color-picker"></div>
      <div id="color-indicator" class="color-indicator"></div>
      <div id="color-picker"></div>
    </div>
  </div>
  <div class="rgb_buttons right">
    <button class="inactive" onclick="defColor('c1')" id="c1">  </button>
    <button class="inactive" onclick="defColor('c2')" id="c2">  </button>
    <button class="inactive" onclick="defColor('c3')" id="c3">  </button>
  </div>
  <script src="https://cdn.jsdelivr.net/npm/@jaames/iro@5"></script>
</body>
<script src="logic.js"></script>
</html>");
		return message;
	}
};