const char message_lv[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1, minimum=scale=1">
    <meta charset="utf-8">
    <meta name="theme-color" , content="#222222">
    <title> Led Live Preview</title>
    <style>
        body {
            margin: 0;
        }

        #canv {
            background: black;
            filter: brightness(175%);
            width: 100%;
            height: 100%;
            position: absolute;
        }
    </style>
</head>

<body>
    <div id="canv" />
    <script>
        function updatePreview(leds) {
            /*var str = "linear-gradient(90deg,#ff0000,#00ff00,#0000ff)";*/
            var str = "linear-gradient(90deg";
            for (var i = 0; i < leds.length; i++) {
                str += ",#" + leds[i];
            }
            str += ")";
            document.getElementById("canv").style.background = str;
        }
        function getLiveJson(event) {
            try {
                var json = JSON.parse(event.data);
                if (json && json.leds) {
                    requestAnimationFrame(function () {updatePreview(json.leds);});
                }
            }
            catch (err) {
                console.error("Live Preview Error: ", err)
            }
        }

        var websocket = top.window.websocket;
        if (websocket && websocket.readyState === WebSocket.OPEN) {
            console.info("Using WebSocket");
            websocket.send("{'lv':true}");

        } else {
            console.info("Peek WS Opening");
            websocket = new WebSocket("ws://192.168.178.40/ws");
            websocket.onopen = function () {
                console.info("Peek Ws Opened");
                websocket.send("{lv: true}");
            }
        }
    
        /*websocket.addEventListener("message", getLiveJson);*/
        websocket.onmessage = getLiveJson;
        var str = "linear-gradient(90deg,#ff0000,#00ff00,#0000f)";
            document.getElementById("canv").style.background = str;
    </script>
</body>

</html>

    )rawliteral";