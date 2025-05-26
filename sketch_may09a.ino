#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <FS.h>

IPAddress local_ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

const char* ssid = "ESP8266-Chat";
const char* password = "123456789";

const char* roomPasswords[] = { "pass1", "pass2", "pass3", "pass4", "pass5" };

ESP8266WebServer server(80);
WebSocketsServer webSockets[] = {
  WebSocketsServer(81), WebSocketsServer(82),
  WebSocketsServer(83), WebSocketsServer(84),
  WebSocketsServer(85)
};

String messages[5][6];
int msgCounts[5] = {0};

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  WiFi.config(local_ip, gateway, subnet);
  SPIFFS.begin();

  Serial.println("ESP8266 Multi-Chat Server Started");
  Serial.println("IP Address: " + WiFi.localIP().toString());

  server.on("/", HTTP_GET, serveHomePage);
  server.on("/login", HTTP_POST, handleLogin);

  for (int i = 1; i <= 5; i++) {
    server.on("/room" + String(i), HTTP_GET, [i]() { serveChatPage(i); });
  }

  for (int i = 0; i < 5; i++) {
    webSockets[i].begin();
    webSockets[i].onEvent([i](uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
      handleChat(i, payload, length);
    });
  }

  server.begin();
}

void serveHomePage() {
  String html = "<html><head><style>";
  html += "body {background: black; color: white; text-align: center; font-family: Arial;}";
  html += "input, button {padding: 10px; margin: 5px; background-color: blue; color: white; border: none; border-radius: 5px;}";
  html += "</style></head><body>";
  html += "<h1>ESP8266 Multi-Chat</h1>";
  html += "<p>Enter Room Number (1-5) and Password:</p>";
  html += "<form action='/login' method='POST'>";
  html += "<input type='number' name='room' min='1' max='5' required><br>";
  html += "<input type='password' name='password' required><br>";
  html += "<button type='submit'>Enter</button></form></body></html>";
  server.send(200, "text/html", html);
}

void handleLogin() {
  if (server.hasArg("room") && server.hasArg("password")) {
    int room = server.arg("room").toInt();
    String inputPass = server.arg("password");
    if (room >= 1 && room <= 5 && inputPass == roomPasswords[room - 1]) {
      server.sendHeader("Location", "/room" + String(room));
      server.send(302, "text/plain", "Redirecting...");
    } else {
      server.send(403, "text/plain", "Access Denied! Incorrect Password.");
    }
  } else {
    server.send(400, "text/plain", "Bad Request.");
  }
}

void serveChatPage(int room) {
  String html = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1'><style>";
  html += "body {background: black; color: white; font-family: Arial; text-align: center;}";
  html += "#messages {max-height: 300px; overflow-y: auto; border: 1px solid white; padding: 10px; margin-bottom: 10px; text-align: left;}";
  html += "input, button {padding: 10px; background-color: blue; color: white; border: none; border-radius: 5px;}";
  html += "#messageBox {width: 70%;}";
  html += "</style></head><body>";
  html += "<h2>Chat Room " + String(room) + "</h2>";
  html += "<div id='messages'></div>";
  html += "<input type='text' id='messageBox' placeholder='Type a message...'>";
  html += "<button onclick='sendMessage();'>Send</button>";
  html += "<script>";
  html += "var ws = new WebSocket('ws://' + location.hostname + ':" + String(80 + room) + "');";
  html += "ws.onmessage = function(evt) { document.getElementById('messages').innerHTML = evt.data; };";
  html += "function sendMessage() { var msg = document.getElementById('messageBox').value;";
  html += "if(msg.trim() != '') { ws.send(msg); document.getElementById('messageBox').value=''; } }";
  html += "</script></body></html>";
  server.send(200, "text/html", html);
}

void handleChat(int roomIndex, uint8_t* payload, size_t length) {
  String message = String((char*)payload);
  if (message.length() == 0) return;

  if (msgCounts[roomIndex] >= 6) {
    for (int i = 1; i < 6; i++) {
      messages[roomIndex][i - 1] = messages[roomIndex][i];
    }
    msgCounts[roomIndex] = 5;
  }

  messages[roomIndex][msgCounts[roomIndex]++] = message;

  String allMessages = "";
  for (int i = 0; i < msgCounts[roomIndex]; i++) {
    allMessages += "<p>" + messages[roomIndex][i] + "</p>";
  }

  webSockets[roomIndex].broadcastTXT(allMessages);
}

void loop() {
  server.handleClient();
  for (int i = 0; i < 5; i++) {
    webSockets[i].loop();
  }
}
