var slider = document.getElementById("myRange");
var isOn = true;
var sync = true;
var theme = true;
var d = document;
var lastC = null;
var json = null;
var color_storage = { "c1": "#000000", "c2": "#000000", "c3": "#000000" };
let colorIndicator = document.getElementById('color-indicator');
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
function loadPreset() {
  if (localStorage.getItem('color') !== null) {
    var color_stor = JSON.parse(localStorage.getItem('color'));
    for (let i in color_stor) {
      d.getElementById(i).style.backgroundColor = color_stor[i];
      console.log("Es geht", color_stor[i]);
      color_storage[i]  = color_stor[i];
    }
  }
}
loadPreset();

colorPicker.on("color:change", function (color) {
  colorIndicator.style.backgroundColor = color.hexString;

});
console.log(json);
colorPicker.on("input:end", function (input) {
  posting(input.rgb);
  let rgb = colorPicker.color.rgb;
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
  console.log("Es wird gefetched:",arg, typeof(arg));
  let x = null;
  /*requestJSON(arg);*/
}
/* Funktion um JSON zu übermitteln */
function requestJSON(arg) {
  console.log(arg);
  fetch('/post', {
    method: 'post',
    headers: {
      'Accept': 'application/json',
      'Content-Type': 'application/json'
    },
    body: JSON.stringify(arg)
  }).then(response => response.json())
    .then(data => {
      console.log(res);
    })
    .catch((error) => {
      console.error("Error", error);
    });

}

function sCol(na, col) {
  d.documentElement.style.setProperty(na, col);
}



function toggleSync() {
  sync = !sync;
  d.getElementById('buttonSync').className = (sync) ? "active" : "";
}
function toggleTheme() {
  theme = !theme;
  console.log(theme);
}
var last = null;
function selectButton(button) {
  console.log(last);
  if (last !== null) {
    d.getElementById(last).className = "inactive";
  }
  d.getElementById(button).className = "active"
  last = button;

}
function defColor(arg) {
  var color2 = {r:0, g:0, b:0};
  var rgb = ["r", "g", "b"];

  console.log(arg);
  let col = d.getElementById(arg).style.backgroundColor;
  /*console.log(`Color ist ${col}`); */
  let newcol = col.slice(4, -1);
  newcol = newcol.split(",");
  for (let x in newcol) color2[rgb[x]] = parseInt(newcol[x]);
  posting(color2);
  colorPicker.color.set(col);

  if (lastC == arg) {
    d.getElementById(arg).className = "inactive";
    console.log(";(");
    lastC = null;
    return;
  }
  if (lastC !== null) {
    d.getElementById(lastC).className = "inactive";
  }
  d.getElementById(arg).className = "active";
  lastC = arg;
}
