<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Fingerprint Door Lock Circuit</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
            background: #f5f5f5;
        }
        .container {
            max-width: 1200px;
            margin: 0 auto;
            background: white;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
        .circuit-diagram {
            background: white;
            border: 2px solid #333;
            padding: 20px;
            margin: 20px 0;
            border-radius: 5px;
        }
        svg {
            width: 100%;
            max-width: 1100px;
            height: auto;
        }
        .component {
            font-family: Arial, sans-serif;
            font-size: 12px;
        }
        .wire {
            stroke: #000;
            stroke-width: 2;
            fill: none;
        }
        .power-wire {
            stroke: #d32f2f;
            stroke-width: 3;
            fill: none;
        }
        .ground-wire {
            stroke: #000;
            stroke-width: 2;
            fill: none;
        }
        .signal-wire {
            stroke: #1976d2;
            stroke-width: 2;
            fill: none;
        }
        .component-box {
            fill: #f0f0f0;
            stroke: #333;
            stroke-width: 2;
        }
        .pin {
            fill: #333;
            r: 3;
        }
        .legend {
            background: #f9f9f9;
            padding: 15px;
            border-radius: 5px;
            margin: 20px 0;
        }
        .legend h3 {
            margin-top: 0;
            color: #333;
        }
        .legend-item {
            display: inline-block;
            margin: 5px 15px 5px 0;
        }
        .legend-line {
            display: inline-block;
            width: 30px;
            height: 3px;
            margin-right: 8px;
            vertical-align: middle;
        }
        .power { background: #d32f2f; }
        .ground { background: #000; }
        .signal { background: #1976d2; }
        .specifications {
            background: #e3f2fd;
            padding: 15px;
            border-radius: 5px;
            margin: 20px 0;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>ESP32 Fingerprint Door Lock Circuit Diagram</h1>
        
        <div class="circuit-diagram">
            <svg viewBox="0 0 1100 800">
                <!-- Power Supply -->
                <rect class="component-box" x="50" y="50" width="100" height="60"/>
                <text class="component" x="100" y="75" text-anchor="middle">12V DC</text>
                <text class="component" x="100" y="90" text-anchor="middle">Power Supply</text>
                <circle class="pin" cx="150" cy="70"/>
                <circle class="pin" cx="150" cy="90"/>
                <text class="component" x="160" y="75">+12V</text>
                <text class="component" x="160" y="95">GND</text>
                
                <!-- Relay -->
                <rect class="component-box" x="300" y="40" width="120" height="80"/>
                <text class="component" x="360" y="65" text-anchor="middle">5V Relay</text>
                <text class="component" x="360" y="80" text-anchor="middle">(Normally Closed)</text>
                <text class="component" x="360" y="95" text-anchor="middle">SPDT</text>
                
                <!-- Relay pins -->
                <circle class="pin" cx="300" cy="60"/>
                <circle class="pin" cx="300" cy="100"/>
                <circle class="pin" cx="420" cy="50"/>
                <circle class="pin" cx="420" cy="70"/>
                <circle class="pin" cx="420" cy="90"/>
                
                <text class="component" x="285" y="65">C1</text>
                <text class="component" x="285" y="105">C2</text>
                <text class="component" x="430" y="55">COM</text>
                <text class="component" x="430" y="75">NC</text>
                <text class="component" x="430" y="95">NO</text>
                
                <!-- Transistor (NPN) -->
                <g transform="translate(200,150)">
                    <circle cx="0" cy="0" r="15" fill="none" stroke="#333" stroke-width="2"/>
                    <line x1="-8" y1="-8" x2="8" y2="8" stroke="#333" stroke-width="2"/>
                    <line x1="-8" y1="8" x2="8" y2="-8" stroke="#333" stroke-width="2"/>
                    <line x1="-15" y1="0" x2="-8" y2="0" stroke="#333" stroke-width="2"/>
                    <line x1="8" y1="-8" x2="15" y2="-15" stroke="#333" stroke-width="2"/>
                    <line x1="8" y1="8" x2="15" y2="15" stroke="#333" stroke-width="2"/>
                    <polygon points="10,-5 15,-10 12,-12" fill="#333"/>
                    
                    <circle class="pin" cx="-15" cy="0"/>
                    <circle class="pin" cx="15" cy="-15"/>
                    <circle class="pin" cx="15" cy="15"/>
                    
                    <text class="component" x="0" y="-25" text-anchor="middle">2N2222</text>
                    <text class="component" x="-25" y="5">B</text>
                    <text class="component" x="20" y="-10">C</text>
                    <text class="component" x="20" y="20">E</text>
                </g>
                
                <!-- Base Resistor -->
                <rect x="120" y="145" width="50" height="10" fill="white" stroke="#333" stroke-width="2"/>
                <text class="component" x="145" y="140" text-anchor="middle">1kΩ</text>
                <circle class="pin" cx="120" cy="150"/>
                <circle class="pin" cx="170" cy="150"/>
                
                <!-- Flyback Diode -->
                <g transform="translate(360,130)">
                    <polygon points="0,0 10,10 -10,10" fill="none" stroke="#333" stroke-width="2"/>
                    <line x1="-10" y1="10" x2="10" y2="10" stroke="#333" stroke-width="2"/>
                    <circle class="pin" cx="-15" cy="10"/>
                    <circle class="pin" cx="15" cy="10"/>
                    <text class="component" x="0" y="-10" text-anchor="middle">1N4007</text>
                </g>
                
                <!-- ESP32 -->
                <rect class="component-box" x="50" y="250" width="150" height="100"/>
                <text class="component" x="125" y="275" text-anchor="middle" font-weight="bold">ESP32</text>
                <text class="component" x="125" y="290" text-anchor="middle">Development Board</text>
                
                <!-- ESP32 pins -->
                <circle class="pin" cx="50" cy="280"/>
                <circle class="pin" cx="50" cy="300"/>
                <circle class="pin" cx="50" cy="320"/>
                <circle class="pin" cx="200" cy="280"/>
                <circle class="pin" cx="200" cy="300"/>
                
                <text class="component" x="40" y="285">3.3V</text>
                <text class="component" x="40" y="305">GND</text>
                <text class="component" x="40" y="325">GPIO2</text>
                <text class="component" x="210" y="285">RX</text>
                <text class="component" x="210" y="305">TX</text>
                
                <!-- Fingerprint Sensor -->
                <rect class="component-box" x="300" y="250" width="120" height="80"/>
                <text class="component" x="360" y="275" text-anchor="middle">AS608</text>
                <text class="component" x="360" y="290" text-anchor="middle">Fingerprint</text>
                <text class="component" x="360" y="305" text-anchor="middle">Sensor</text>
                
                <!-- Sensor pins -->
                <circle class="pin" cx="300" cy="270"/>
                <circle class="pin" cx="300" cy="290"/>
                <circle class="pin" cx="300" cy="310"/>
                <circle class="pin" cx="300" cy="330"/>
                
                <text class="component" x="285" y="275">VCC</text>
                <text class="component" x="285" y="295">GND</text>
                <text class="component" x="285" y="315">TX</text>
                <text class="component" x="285" y="335">RX</text>
                
                <!-- Keypad -->
                <rect class="component-box" x="500" y="250" width="100" height="80"/>
                <text class="component" x="550" y="275" text-anchor="middle">4x4 Matrix</text>
                <text class="component" x="550" y="290" text-anchor="middle">Keypad</text>
                <text class="component" x="550" y="305" text-anchor="middle">(Optional)</text>
                
                <!-- Electric Lock -->
                <rect class="component-box" x="650" y="40" width="120" height="60"/>
                <text class="component" x="710" y="65" text-anchor="middle">Electric</text>
                <text class="component" x="710" y="80" text-anchor="middle">Bolt Lock</text>
                <text class="component" x="710" y="95" text-anchor="middle">12V DC</text>
                
                <circle class="pin" cx="650" cy="60"/>
                <circle class="pin" cx="650" cy="80"/>
                <text class="component" x="635" y="65">+</text>
                <text class="component" x="635" y="85">-</text>
                
                <!-- Status LED -->
                <g transform="translate(550,150)">
                    <circle cx="0" cy="0" r="8" fill="#ff4444" stroke="#333" stroke-width="2"/>
                    <circle class="pin" cx="-15" cy="0"/>
                    <circle class="pin" cx="15" cy="0"/>
                    <text class="component" x="0" y="-20" text-anchor="middle">Status LED</text>
                </g>
                
                <!-- LED Resistor -->
                <rect x="480" y="145" width="40" height="10" fill="white" stroke="#333" stroke-width="2"/>
                <text class="component" x="500" y="140" text-anchor="middle">220Ω</text>
                <circle class="pin" cx="480" cy="150"/>
                <circle class="pin" cx="520" cy="150"/>
                
                <!-- Buzzer -->
                <g transform="translate(650,150)">
                    <circle cx="0" cy="0" r="12" fill="none" stroke="#333" stroke-width="2"/>
                    <text class="component" x="0" y="5" text-anchor="middle">♪</text>
                    <circle class="pin" cx="-18" cy="0"/>
                    <circle class="pin" cx="18" cy="0"/>
                    <text class="component" x="0" y="-25" text-anchor="middle">Buzzer</text>
                </g>
                
                <!-- Power connections -->
                <line class="power-wire" x1="150" y1="70" x2="420" y2="70"/>
                <line class="power-wire" x1="420" y1="70" x2="650" y2="60"/>
                
                <!-- Ground connections -->
                <line class="ground-wire" x1="150" y1="90" x2="300" y2="90"/>
                <line class="ground-wire" x1="300" y1="90" x2="300" y2="100"/>
                <line class="ground-wire" x1="300" y1="90" x2="50" y2="300"/>
                <line class="ground-wire" x1="300" y1="90" x2="300" y2="290"/>
                <line class="ground-wire" x1="300" y1="90" x2="650" y2="80"/>
                <line class="ground-wire" x1="215" y1="165" x2="215" y2="200"/>
                <line class="ground-wire" x1="215" y1="200" x2="300" y2="200"/>
                <line class="ground-wire" x1="300" y1="200" x2="300" y2="90"/>
                
                <!-- Control signal connections -->
                <line class="signal-wire" x1="50" y1="320" x2="120" y2="150"/>
                <line class="signal-wire" x1="170" y1="150" x2="185" y2="150"/>
                <line class="signal-wire" x1="215" y1="135" x2="300" y2="60"/>
                
                <!-- Flyback diode connections -->
                <line class="wire" x1="300" y1="60" x2="345" y2="140"/>
                <line class="wire" x1="375" y1="140" x2="420" y2="50"/>
                
                <!-- Fingerprint sensor connections -->
                <line class="power-wire" x1="50" y1="280" x2="300" y2="270"/>
                <line class="signal-wire" x1="200" y1="280" x2="300" y2="330"/>
                <line class="signal-wire" x1="200" y1="300" x2="300" y2="310"/>
                
                <!-- Status LED connections -->
                <line class="signal-wire" x1="200" y1="350" x2="480" y2="150"/>
                <line class="signal-wire" x1="520" y1="150" x2="535" y2="150"/>
                <line class="ground-wire" x1="565" y1="150" x2="580" y2="200"/>
                
                <!-- Voltage labels -->
                <text class="component" x="250" y="65" fill="#d32f2f">+12V</text>
                <text class="component" x="250" y="105" fill="#000">GND</text>
            </svg>
        </div>
        
        <div class="legend">
            <h3>Wire Legend</h3>
            <div class="legend-item">
                <span class="legend-line power"></span>
                <span>+12V Power</span>
            </div>
            <div class="legend-item">
                <span class="legend-line ground"></span>
                <span>Ground</span>
            </div>
            <div class="legend-item">
                <span class="legend-line signal"></span>
                <span>Control Signals (3.3V)</span>
            </div>
        </div>
        
        <div class="specifications">
            <h3>Component Specifications</h3>
            <ul>
                <li><strong>Relay:</strong> 5V SPDT relay (normally closed configuration) - rated for 12V/10A minimum</li>
                <li><strong>Transistor:</strong> 2N2222 NPN transistor (or equivalent like BC547)</li>
                <li><strong>Base Resistor:</strong> 1kΩ (limits base current to ~3.3mA)</li>
                <li><strong>Flyback Diode:</strong> 1N4007 (protects against relay coil back-EMF)</li>
                <li><strong>LED Resistor:</strong> 220Ω for 3.3V operation</li>
                <li><strong>Power Supply:</strong> 12V DC, minimum 2A capacity</li>
            </ul>
        </div>
        
        <div class="specifications">
            <h3>Operation Sequence</h3>
            <ol>
                <li><strong>Normal State:</strong> GPIO2 is LOW, transistor OFF, relay coil not energized</li>
                <li><strong>Relay NC contacts closed:</strong> 12V power flows to lock (lock is CLOSED)</li>
                <li><strong>Valid fingerprint/PIN:</strong> ESP32 sets GPIO2 HIGH for 5 seconds</li>
                <li><strong>Transistor conducts:</strong> Relay coil energized, NC contacts open</li>
                <li><strong>Power cut to lock:</strong> Lock opens (fail-safe operation)</li>
                <li><strong>After 5 seconds:</strong> GPIO2 goes LOW, lock power restored, door locks again</li>
            </ol>
        </div>
        
        <div class="specifications">
            <h3>Safety Features</h3>
            <ul>
                <li><strong>Fail-Safe Operation:</strong> Power failure = door unlocks</li>
                <li><strong>Flyback Protection:</strong> Diode protects against relay switching spikes</li>
                <li><strong>Current Limiting:</strong> Base resistor protects ESP32 GPIO</li>
                <li><strong>Visual Feedback:</strong> Status LED indicates system state</li>
                <li><strong>Audio Feedback:</strong> Buzzer for access confirmation</li>
                <li><strong>Backup Method:</strong> Optional keypad for PIN entry</li>
            </ul>
        </div>
    </div>
</body>
</html>