var isOn = true;
var sync = true;
var theme = true;
var d = document;
var last = null;
var lastC = null;
var json = null;
var c = { r: 0, g: 0, b: 0 };
var b = 120;
var f = 0;
var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
var slider = d.getElementById("sliderBri");
var color_storage = { "c1": "#000000", "c2": "#000000", "c3": "#000000" };
var colorIndicator = document.getElementById('color-indicator');
var colorPicker = new iro.ColorPicker("#color-picker", {
  width: 180, color: '#fff',
  layout: [{
    component: iro.ui.Wheel,
    options: {}
  }, {
    component: iro.ui.Slider,
    options: {
      sliderType: 'value'
    }
  }, {
    component: iro.ui.Slider,
    options: {
      sliderType: 'kelvin',
      minTemperature: 2100,
      maxTemperature: 10000
    }
  }]
});
function initWebSocket() {
  console.log('Trying to open a WebSocket connection...');
  websocket = new WebSocket(gateway);
  websocket.onopen = onOpen;
  websocket.onclose = onClose;
  websocket.onmessage = onMessage; // <-- add this line
}
function onOpen(event) {
  console.log('Connection opened');
}

function onClose(event) {
  console.log('Connection closed');
  setTimeout(initWebSocket, 2000);
}
function onMessage(event) {
  var state;
  if (event.data == "1") {
    state = "ON";
  }
  else {
    state = "OFF";
  }
  console.log("State", state);
}
window.addEventListener('load', onLoad);
function onLoad(event) {
  initWebSocket();
  initButton();
}

function initButton() {
  console.log("Button")
}
function toggle() {
  websocket.send('toggle');
}
function loadPreset() {
  if (localStorage.getItem('color') !== null) {
    var color_stor = JSON.parse(localStorage.getItem('color'));
    for (let i in color_stor) {
      d.getElementById(i).style.backgroundColor = color_stor[i];
      console.log("Es geht", color_stor[i]);
      color_storage[i] = color_stor[i];
    }
  }
}
loadPreset();
slider.onchange = function () {
  b = { "b": parseInt(this.value) };
  posting(b);
};

colorPicker.on("color:change", function (color) {
  colorIndicator.style.backgroundColor = color.hexString;
});
colorPicker.on("input:end", function (input) {
  c = input.rgb;
  posting({ "c": c });
  /*let rgb = colorPicker.color.rgb;*/
  if (lastC !== null) {
    d.getElementById(lastC).style.backgroundColor = input.hexString;
    color_storage[lastC] = input.hexString;
    /*console.log(color_storage);*/
    localStorage.setItem('color', JSON.stringify(color_storage));
    json = JSON.parse(localStorage.getItem('color'));
    /*console.log(json);*/

  }
});
function posting(arg) {
  console.log("Fetch", arg);
  /*requestJSON(arg);*/
}
/* Funktion um JSON zu übermitteln */
function requestJSON(arg) {
  console.log(arg);
  fetch('/json', {
    method: 'post',
    headers: {
      'Accept': 'application/json',
    },
    body: JSON.stringify(arg)
  })

}

function sCol(na, col) {
  d.documentElement.style.setProperty(na, col);
}

function toggleSync() {
  sync = !sync;
  d.getElementById('buttonSync').className = (sync) ? "active" : "";
  posting({ "s": sync });
}
function togglePower() {
  isOn = !isOn;
  d.getElementById('buttonPower').className = (isOn) ? "active" : "";
  posting({ "p": isOn });
}
function toggleTheme() {
  theme = !theme;
  console.log(theme);
}

function selectButton(button, number) {
  posting({ "f": number });
  if (last !== null) {
    d.getElementById(last).className = "inactive";
  }
  d.getElementById(button).className = "active";
  last = button;

}
function defColor(arg) {
  var color2 = { r: 0, g: 0, b: 0 };
  var rgb = ["r", "g", "b"];

  let col = d.getElementById(arg).style.backgroundColor;
  /*console.log(`Color ist ${col}`); */
  let newcol = col.slice(4, -1);
  newcol = newcol.split(",");
  for (let x in newcol) color2[rgb[x]] = parseInt(newcol[x]);
  posting({ "c": color2 });
  colorPicker.color.set(col);

  if (lastC == arg) {
    d.getElementById(arg).className = "inactive";
    lastC = null;
    return;
  }
  if (lastC !== null) {
    d.getElementById(lastC).className = "inactive";
  }
  d.getElementById(arg).className = "active";
  lastC = arg;
}
