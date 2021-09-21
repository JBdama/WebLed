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
        function updatePreview() {
            var str = "linear-gradient(90deg,#ff0000,#00ff00,#0000f)";
            document.getElementById("canv").style.background = str;
        }
        function getLiveJson(event) {
            try {
                var json = JSON.parse(event.data);
            }
            catch (err) {
                console.error("Live Preview Error: ", error)
            }
        }
        var ws = top.windows.ws;
        if (ws && ws.readyState === WebSocket.OPEN) {
            console.info("Using WebSocket");
        } else {
            console.info("Peek WS Opening");
            ws = new WebSocket("ws://192.168.178.40/ws");
            ws.onopen = function () {
                console.info("Peek Ws Opened");
                ws.send("{lv: true}");
            }
        }
        ws.addEventListener("message", getLiveJson);
        var str = "linear-gradient(90deg,#ff0000,#00ff00,#0000f";
            document.getElementById("canv").style.background = str;
    </script>
</body>

</html>

    )rawliteral";