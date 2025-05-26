## 📡 ESP8266 Offline Multi-Room Chat System

### 💬 Real-Time Text Communication Without the Internet

This project enables **multiple devices to connect to a single ESP8266 module** via its built-in Wi-Fi hotspot and exchange **text messages in real-time—completely offline**. There's no need for an internet connection, router, or external server. Just upload the code to your ESP8266, and you have a **self-contained, multi-room chat server** in your pocket!

---

### ✨ Key Features

* 🔌 **No Internet Required** – All communication happens through the ESP8266’s Wi-Fi.
* 🧠 **5 Independent Chat Rooms** – Each room is protected by a separate password.
* 📱 **Multi-Device Communication** – Multiple users can join the same room and chat together.
* 💬 **Real-Time Messaging** – Instant message updates between connected users.
* 🧾 **Message Limit** – Each room stores the latest 6 messages (you can increase this in the code).
* ⚙️ **Fully Customizable** – Easily change SSID, passwords, message limit, and more.

---

### 🚀 How to Use

1. **Upload the Code**

   * Download the source code.
   * Open it in the **Arduino IDE**.
   * Upload it to your ESP8266 module.
![image](https://github.com/user-attachments/assets/81adcd57-552f-4179-af7a-55cfd3250c2e)
2. **Connect to the ESP8266 Wi-Fi**

   * After uploading, the ESP8266 will create a Wi-Fi hotspot named:
     `ESP8266 Chat`
   * Connect to it using the password:
     `123456789`
   * *(You can change both the SSID and password in the code if you wish.)*

3. **Open the Web Chat Interface**

   * Open a browser on your phone or PC.
   * Visit the local IP address:
     `http://192.168.4.1`
![image](https://github.com/user-attachments/assets/3885d65a-eb98-469f-9696-01afb573da9d)
    * You'll be taken to a web interface where you can:

     * Enter the **room password** to join a specific room.
       Available passwords:
       `pass1`, `pass2`, `pass3`, `pass4`, `pass5`
     * Start chatting with others in the same room.
![image](https://github.com/user-attachments/assets/d086379e-ad11-4595-b216-db8cb920c75c)
5. **Live User Counter**

   * A divide symbol ( `/` ) will appear for each user connected.
   * For example:

     * 1 user = `/`
     * 3 users = `///`

---

### 🛠️ Customization Tips

* Want more messages per room? Modify the message storage array size in the code.
* Need more rooms or unique names instead of numbers? Expand the room logic in the source.
* Prefer a different interface look? Edit the HTML/CSS section in the sketch.

---

This project is perfect for:

* Remote areas with no internet
* Classroom or event communications
* Fun offline experiments
* Learning embedded web development and networking

point: (chatgpt helped me a lot to create this)
