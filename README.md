# 🤖 SHIZO

### A Personal AI System Built to Do More Than Just Talk.

<p align="center">
  <b>Understand. Think. Act. Interact.</b>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Status-In%20Development-orange?style=for-the-badge" />
  <img src="https://img.shields.io/badge/AI-Generative%20AI-blue?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Hardware-ESP8266%20%2F%20ESP32-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Interface-Web%20%2B%20OLED-purple?style=for-the-badge" />
</p>

---

## 🧠 What is SHIZO?

**SHIZO is a personal AI system designed to do more than just answer questions.**

The idea is to build an AI system that can understand what the user wants, process the request, decide what needs to be done, use the required tools or services, and return the result.

The physical SHIZO is a **stationary hardware interface** for this AI system.

It does not need to walk around.

The main goal is not movement.

The main goal is **capability**.

SHIZO is being developed to combine:

- 🤖 Artificial Intelligence
- 🧠 Reasoning and decision making
- 💬 Natural conversation
- 🎤 Voice interaction
- 👁️ Computer vision
- 🌐 Internet and APIs
- 🛠️ Tool usage
- ⚙️ Task execution
- 📱 Web control
- 🔌 IoT
- 🖥️ Physical hardware
- 🎭 Personality and emotions
- 🔔 Notifications
- 🎵 Music and sound reactions
- 🔄 Automation

> Some of these capabilities are currently under development and are part of the long-term vision.

---

# 💡 The Core Idea

A normal assistant can work like:

```text
User
  ↓
Question
  ↓
AI
  ↓
Answer

SHIZO is being designed around a larger idea:
User
  ↓
SHIZO
  ↓
Understand the request
  ↓
Think / Decide
  ↓
Choose the required tool or action
  ↓
Perform the task
  ↓
Process the result
  ↓
Respond to the user

The goal is to move from:
"Here is how you can do it."

towards:
"I understand. I'll handle it."

🧩 System Architecture
The long-term SHIZO system is planned around several layers:
                         ┌──────────────────┐
                         │      USER        │
                         └────────┬─────────┘
                                  │
                           Text / Voice
                                  │
                                  ▼
                         ┌──────────────────┐
                         │      SHIZO       │
                         │     AI CORE      │
                         └────────┬─────────┘
                                  │
                                  ▼
                         ┌──────────────────┐
                         │ Understand Intent│
                         └────────┬─────────┘
                                  │
                                  ▼
                         ┌──────────────────┐
                         │  Think / Decide  │
                         └────────┬─────────┘
                                  │
                 ┌────────────────┼────────────────┐
                 │                │                │
                 ▼                ▼                ▼
              Respond           Tools            Actions
                                  │                │
                                  ▼                │
                            APIs / Services        │
                                  │                │
                                  └────────┬───────┘
                                           │
                                           ▼
                                  ┌──────────────────┐
                                  │ Personality /    │
                                  │ Emotion System   │
                                  └────────┬─────────┘
                                           │
                                           ▼
                                  ┌──────────────────┐
                                  │ SHIZO Interface  │
                                  │                  │
                                  │ OLED / Web /     │
                                  │ Voice / Hardware │
                                  └──────────────────┘

⚡ Current Working Prototype
The current prototype focuses on establishing the hardware and communication foundation.
Currently working / tested
- ESP-based hardware
- OLED display
- Wi-Fi connectivity
- SHIZO Wi-Fi network
- Local web server
- Phone connectivity
- Web-based control
- Emotion states
- OLED expressions
- Basic device logic
The current prototype can create a local Wi-Fi network and provide a web interface that can be accessed from a connected phone or laptop.
Example local address:
192.168.4.1

🌐 Web Interface
The current SHIZO prototype includes a local web interface.
The basic communication flow is:
Phone / Laptop
      │
      │ Wi-Fi
      ▼
   SHIZO ESP
      │
      ▼
 Local Web Server

The web interface is currently being used to test and control parts of the SHIZO system.
It provides a foundation for future controls such as:
- AI interaction
- Device state
- Emotions
- Settings
- Hardware controls
- Connected services
- Notifications
The interface will continue to evolve as SHIZO develops.
🖥️ OLED Face
The OLED display acts as SHIZO's visual face.
Different states can be represented through simple expressions.
Example:
┌───────────────────────┐
│                       │
│       ◉       ◉       │
│                       │
│          ───          │
│                       │
└───────────────────────┘

Current / tested emotion states include:
HAPPY
SAD
ANGRY
SLEEPY
SURPRISED
THINKING
NORMAL

The expression system allows the physical device to react visually instead of behaving like a normal screen.
🎭 Personality & Behaviour
One of the main ideas behind SHIZO is giving the system its own personality.
The personality layer is being developed to influence:
- Responses
- Emotions
- Reactions
- Conversation style
- Visual expressions
- Sleep / wake behaviour
- Event reactions
For example:
User interacts with SHIZO
          ↓
       AI Brain
          ↓
     Understands input
          ↓
    Personality Layer
          ↓
       Emotion
          ↓
     OLED Expression
          ↓
       SHIZO reacts

The goal is to make SHIZO feel more like a personal AI character rather than a completely emotionless assistant.
🧠 AI Brain
The AI brain is intended to become the central intelligence of SHIZO.
Its purpose is not simply to generate text.
The planned flow is:
Input
  ↓
Understand
  ↓
Identify Intent
  ↓
Check Context
  ↓
Decide What To Do
  ↓
Choose Tool / Action
  ↓
Execute
  ↓
Process Result
  ↓
Generate Response
  ↓
Apply Personality
  ↓
Respond

The AI layer is being developed separately from the physical hardware so that the system can evolve without being limited to one device.
🎤 Voice Interaction
Voice is planned as one of the main interfaces for SHIZO.
The intended flow is:
User
  ↓
Microphone
  ↓
Speech Recognition
  ↓
SHIZO AI
  ↓
Decision / Response
  ↓
Text-to-Speech
  ↓
Speaker
  ↓
User

Future voice capabilities include:
- Voice commands
- Speech recognition
- Natural voice conversations
- Text-to-speech
- Voice-based task execution
👁️ Computer Vision
Computer vision is planned as another input for SHIZO.
A camera could provide visual information to the AI system.
Camera
   ↓
Image
   ↓
Vision Model
   ↓
Object / Scene Information
   ↓
SHIZO AI
   ↓
Decision
   ↓
Response / Action

Planned capabilities include:
- Object recognition
- Visual understanding
- Recognizing objects
- Understanding the environment
- Reacting to visual events
🔌 IoT & Physical Interaction
SHIZO is designed to eventually connect AI with the physical world.
The long-term idea is:
SHIZO AI
   │
   ▼
Tool / API
   │
   ▼
ESP / IoT Controller
   │
   ├── LEDs
   ├── Sensors
   ├── Displays
   ├── Switches
   └── Other Devices

This could allow SHIZO to perform physical actions based on user requests or detected events.
🛠️ Hardware
The current hardware development includes:
- ESP8266 / ESP32
- OLED SSD1306 128×64
- LEDs
- Push buttons
- Sensors
- Wi-Fi
- Battery system
- Charging hardware
- Audio hardware
- Camera hardware
Hardware may change as the project develops.
💻 Software & Technology
Embedded
- Arduino
- C / C++
- ESP8266
- ESP32
AI
- Generative AI
- AI APIs
- Natural Language Processing
- AI agents
- Computer Vision
- Speech Recognition
- Text-to-Speech
Web
- HTML
- CSS
- JavaScript
- Local Web Server
- REST-style communication
Backend / Logic
- Python
- APIs
- Automation
- Data processing
🚀 Roadmap
Phase 1 — Hardware Foundation
- [x] ESP setup
- [x] OLED display
- [x] Basic device states
- [x] Wi-Fi setup
- [x] Local web server
- [x] Phone connection
- [x] Basic web control
Phase 2 — Personality & Expressions
- [x] Emotion states
- [x] OLED expressions
- [x] User-controlled emotions
- [ ] More expressions
- [ ] Dynamic reactions
- [ ] Sleep / wake behaviour
- [ ] Context-based emotions
- [ ] Improved personality system
Phase 3 — AI Brain
- [x] Initial AI experimentation
- [ ] AI integration with physical device
- [ ] Natural conversation
- [ ] Context handling
- [ ] Intent detection
- [ ] Tool selection
- [ ] Task execution
- [ ] Long-term memory
Phase 4 — Voice
- [ ] Microphone
- [ ] Speech recognition
- [ ] Voice commands
- [ ] Text-to-speech
- [ ] Speaker
- [ ] Full voice conversation
Phase 5 — Vision
- [ ] Camera
- [ ] Object recognition
- [ ] Visual understanding
- [ ] Vision-based reactions
- [ ] Vision + AI integration
Phase 6 — Tools & Automation
- [ ] Internet tools
- [ ] External APIs
- [ ] File operations
- [ ] Computer interaction
- [ ] Website interaction
- [ ] Application control
- [ ] Notifications
- [ ] Automated workflows
Phase 7 — IoT
- [ ] IoT device control
- [ ] Smart device integration
- [ ] Sensor integration
- [ ] External ESP devices
- [ ] Smart-home interaction
- [ ] Physical-world actions
🏗️ Development Approach
SHIZO is being developed incrementally.
Each major component is tested separately before being connected to the larger system.
Hardware
   ↓
Display
   ↓
Wi-Fi
   ↓
Web Interface
   ↓
Expressions
   ↓
Personality
   ↓
AI
   ↓
Voice
   ↓
Vision
   ↓
Tools
   ↓
Automation
   ↓
IoT

This approach makes it easier to test, debug and improve each part of the system.
🔐 User Control
Since SHIZO is designed to eventually perform tasks, user control and permissions are important.
Future capabilities may require permission to access:
- Files
- Applications
- Websites
- APIs
- Online services
- IoT devices
The goal is to keep the user in control of what SHIZO can access and what actions it can perform.
🎯 Long-Term Vision
The long-term vision is to make SHIZO a personal AI system capable of understanding and performing useful work.
Not simply:
Ask → Answer

but:
Ask
 ↓
Understand
 ↓
Think
 ↓
Plan
 ↓
Use Tools
 ↓
Act
 ↓
Verify
 ↓
Respond

For example:
User:
"Turn on the light."

        ↓

SHIZO understands the request

        ↓

Checks the connected device

        ↓

Sends the IoT command

        ↓

Light turns on

        ↓

SHIZO confirms the action

Another example:
User:
"Find something useful for me."

        ↓

SHIZO understands the request

        ↓

Uses available tools

        ↓

Processes the information

        ↓

Returns the useful result

The exact capabilities will depend on the tools, APIs, hardware and permissions available to SHIZO.
📊 Project Status
🟡 ACTIVE DEVELOPMENT
SHIZO is currently an experimental personal AI project.
The hardware and communication foundation is being built and tested, while the larger AI, voice, vision, automation and tool-use capabilities are being developed progressively.
Some features in this README are part of the planned roadmap and are not yet fully implemented.
👨‍💻 Developer
Yugal Arora
B.Tech Computer Science & Engineering
Lovely Professional University
🔗 Links
- 🌐 Portfolio: https://yarora5.github.io/YArora5/
- 💻 GitHub: https://github.com/YArora5
- 🔗 LinkedIn: https://www.linkedin.com/in/yugal15/
⭐ Final Thought
SHIZO is not just a robot.
It is not just a chatbot.
It is not just an ESP project.
It is an attempt to build a personal AI system that can understand, communicate, use tools, perform tasks and eventually interact with the physical world.
The physical device is only one interface for the larger system.
The goal isn't to make SHIZO walk.
The goal is to make SHIZO capable. 🤖
