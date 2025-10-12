```LaTex

\documentclass[10pt, letterpaper]{article}

% Packages:
\usepackage[
    ignoreheadfoot,
    top=2 cm,
    bottom=2 cm,
    left=2 cm,
    right=2 cm,
    footskip=1.0 cm,
]{geometry}
\usepackage{titlesec}
\usepackage{tabularx}
\usepackage{array}
\usepackage[dvipsnames]{xcolor}
\definecolor{primaryColor}{RGB}{0, 0, 0}
\usepackage{enumitem}
\usepackage{fontawesome5}
\usepackage{amsmath}
\usepackage[
    pdftitle={Suhan's CV},
    pdfauthor={Sansika Suhan Waduge},
    pdfcreator={LaTeX with RenderCV},
    colorlinks=true,
    urlcolor=primaryColor
]{hyperref}
\usepackage[pscoord]{eso-pic}
\usepackage{calc}
\usepackage{bookmark}
\usepackage{lastpage}
\usepackage{changepage}
\usepackage{paracol}
\usepackage{ifthen}
\usepackage{needspace}
\usepackage{iftex}

\ifPDFTeX
    \input{glyphtounicode}
    \pdfgentounicode=1
    \usepackage[T1]{fontenc}
    \usepackage[utf8]{inputenc}
    \usepackage{lmodern}
\fi

\usepackage{charter}

\raggedright
\AtBeginEnvironment{adjustwidth}{\partopsep0pt}
\pagestyle{empty}
\setcounter{secnumdepth}{0}
\setlength{\parindent}{0pt}
\setlength{\topskip}{0pt}
\setlength{\columnsep}{0.15cm}
\pagenumbering{gobble}

\titleformat{\section}{\needspace{4\baselineskip}\bfseries\large}{}{0pt}{}[\vspace{1pt}\titlerule]

\titlespacing{\section}{-1pt}{0.3 cm}{0.2 cm}

\renewcommand\labelitemi{$\vcenter{\hbox{\small$\bullet$}}$}
\newenvironment{highlights}{\begin{itemize}[topsep=0.10 cm, parsep=0.10 cm, partopsep=0pt, itemsep=0pt, leftmargin=0 cm + 10pt]}{\end{itemize}}
\newenvironment{highlightsforbulletentries}{\begin{itemize}[topsep=0.10 cm, parsep=0.10 cm, partopsep=0pt, itemsep=0pt, leftmargin=10pt]}{\end{itemize}}
\newenvironment{onecolentry}{\begin{adjustwidth}{0 cm + 0.00001 cm}{0 cm + 0.00001 cm}}{\end{adjustwidth}}
\newenvironment{twocolentry}[2][]{\onecolentry\def\secondColumn{#2}\setcolumnwidth{\fill, 4.5 cm}\begin{paracol}{2}}{\switchcolumn \raggedleft \secondColumn\end{paracol}\endonecolentry}

\begin{document}

\begin{header}
    \fontsize{25 pt}{25 pt}\selectfont Sansika Suhan Waduge

    \vspace{5 pt}

    \normalsize
    \mbox{Colombo, Sri Lanka |}%
    \kern 5.0 pt%
    \AND%
    \mbox{+94741224726  |}%
    \kern 5.0 pt%
    \AND%
    \kern 5.0 pt%
    \mbox{\href{mailto:sansikawaduge@gmail.com}{sansikawaduge@gmail.com} |}%
    \kern 5.0 pt%
    \AND%
    \kern 5.0 pt%
    \mbox{\href{https://github.com/Platinum-Saber}{Github}}%
\end{header}

\section{Education}

\begin{twocolentry}{2008 -- 2019}
\textbf{Nalanda College, Colombo 10}
\end{twocolentry}

\begin{onecolentry}
\begin{highlights}

    \item \textbf{2018:} Junior Science Olympiad Sri Lanka -- Gold Medal
    \item \textbf{2018:} G.C.E. Ordinary Level Examination 9A s.

\end{highlights}
\end{onecolentry}

\vspace{0.2 cm}

\begin{twocolentry}{2019 -- 2022}
\textbf{Royal College, Colombo 7}
\end{twocolentry}

\begin{onecolentry}
\begin{highlights}
    \item \textbf{2021:} G.C.E. Advanced Level Examination (Mathematics Stream) \\
    Z-Score: 2.662 \quad | \quad District Rank: 34 \quad | \quad Island Rank: 63 \\
    Subjects: Combined Mathematics -- A, Physics -- A, Chemistry -- A, General English -- A
\end{highlights}
\end{onecolentry}

\begin{twocolentry}{2022 -- Present}
\textbf{University of Moratuwa} -- BSc. Computer Science and Engineering
\begin{onecolentry}
\begin{highlights}

    \item \textbf{CGPA:} 3.49

\end{highlights}
\end{onecolentry}
\end{twocolentry}

\vspace{0.5 cm}

\section{Projects}

\begin{onecolentry}

\textbf{Embedded Systems and Robotics}
\begin{highlightsforbulletentries}
    \item \textbf{Autonomous Collaborative Terrain Mapping}
    \begin{highlightsforbulletentries}
        \item \textbf{Description:} Multi-robot system using LiDAR and odometry for 2D mapping, with data fusion on a coordinator robot over UDP/Wi-Fi.
        \item \textbf{Tech Stack:} ROS2 Foxy, UDP, LiDAR sensors, Raspberry Pi
    \end{highlightsforbulletentries}

    \item \textbf{Kobuki Robot Implementation}
    \begin{highlightsforbulletentries}
        \item \textbf{Description:} Control system for Kobuki mobile robot with Kinect vision integration.
        \item \textbf{Tech Stack:} Raspberry Pi, OpenCV, Kinect
    \end{highlightsforbulletentries}

    \item \textbf{MediBox – Smart Medicine Box}
    \begin{highlightsforbulletentries}
        \item \textbf{Description:} IoT-enabled pillbox with alarms, OLED display, and web dashboard.
        \item \textbf{Tech Stack:} ESP32, MQTT, Node-RED
    \end{highlightsforbulletentries}

    \item \textbf{Music-Reactive LED System (Group Project)}
    \begin{highlightsforbulletentries}
        \item \textbf{Description:} Real-time LED control based on audio beat detection.
        \item \textbf{Tech Stack:} ESP32, Python UDP Server
    \end{highlightsforbulletentries}

    \item \textbf{Nano Processor (Group Project)}
    \begin{highlightsforbulletentries}
        \item \textbf{Description:} Simple instruction set processor using VHDL.
        \item \textbf{Tech Stack:} VHDL, Vivado
    \end{highlightsforbulletentries}

    \item \textbf{Webots Simulation – Virtual Maze Solver}
    \begin{highlightsforbulletentries}
        \item \textbf{Description:} Maze-solving robot simulation using camera and IR sensors.
        \item \textbf{Tech Stack:} Webots, Python
    \end{highlightsforbulletentries}
\end{highlightsforbulletentries}

\vspace{0.7 cm}

\textbf{Web / Mobile Applications}
\begin{highlightsforbulletentries}
    \item \textbf{Banking System (Group Project)}
    \begin{highlightsforbulletentries}
        \item \textbf{Description:} Web application for managing bank accounts, transactions, and customer data.
        \item \textbf{Tech Stack:} React, Node.js/Express, REST APIs, MySQL
    \end{highlightsforbulletentries}

    \item \textbf{Nutri Mithu – Smart Nutrition Guide}
    \begin{highlightsforbulletentries}
        \item \textbf{Description:} Cross-platform mobile app for nutrition tracking with animated UI and local data storage.
        \item \textbf{Tech Stack:} Flutter, Firebase Firestore, SQLite
    \end{highlightsforbulletentries}

    \item \textbf{SLRMUN – Registration Portal}
    \begin{highlightsforbulletentries}
        \item \textbf{Description:} Event registration and payment portal with Google Drive integration.
        \item \textbf{Tech Stack:} Flutter, Firebase, Google Cloud Console
    \end{highlightsforbulletentries}
\end{highlightsforbulletentries}

\end{onecolentry}


\vspace{0.5 cm}

\section{Competitions \& Contributions}

\begin{onecolentry}
\begin{highlights}
    \item \textbf{IEEE Xtreme 2024:} Participated in the global 24-hour competitive programming event organized by IEEE.
    \item \textbf{Technovation Finalist:} Reached the finals with the Aththatu mobile app focused on empowering home entrepreneurs and connectivity.
    \item \textbf{IESL RoboGames Finalist:} Qualified for finals with a combination of Webots simulation and real-world Kobuki robot programming.
    \item \textbf{Brainstorm Finalist:} Recognized for the NutriMithu mobile app and smart meal box system integrating nutrition tracking and reminders.
    \item \textbf{HR Pillar Lead -- Enigma 2024:} Led the human resources coordination for the Enigma 2024 university-level tech competition.
    \item \textbf{General Secretary of IT -- SLRMUN 2025:} Oversaw IT operations and digital infrastructure for the Sri Lanka Model United Nations 2025 of University of Moratuwa.
    \item \textbf{IoT Workshop Volunteer:} Assisted and mentored students during hands-on IoT workshops at Visakha Vidyalaya and St. Bridget's College.
\end{highlights}
\end{onecolentry}

\vspace{0.5 cm}

\section{Skills}

\begin{onecolentry}
\textbf{Programming Languages :} C++, Python, JavaScript, Java, Dart, Rust, SQL, VHDL
\end{onecolentry}

\vspace{0.2 cm}

\begin{onecolentry}
\textbf{Frameworks \& Tools :} Flutter, Node.js, Next.js, React, ROS2 Jazzy, Gazebo, RViz, Node-RED, WordPress
\end{onecolentry}

\vspace{0.2 cm}

\begin{onecolentry}
\textbf{Database Systems :} Firebase, MySQL
\end{onecolentry}

\vspace{0.2 cm}

\begin{onecolentry}
\textbf{Software :} Microsoft Office Suite, EasyEDA, Figma, Arduino IDE, Vivado
\end{onecolentry}

\vspace{0.2 cm}

\begin{onecolentry}
\textbf{Hardware :} ESP32, Raspberry Pi 4/5, Arduino, ZigBee Modules, RPLidar, LDLidar
\end{onecolentry}

\vspace{0.2 cm}

\begin{onecolentry}
\textbf{DevOps :} Git, GitHub Actions, Docker
\end{onecolentry}

\vspace{0.2 cm}

\begin{onecolentry}
\textbf{Soft Skills :} Leadership, communication, teamwork
\end{onecolentry}

\vspace{0.5 cm}

\section{References}

\begin{twocolentry}{}
\textbf{Prof. Dulani Meedeniya} \\
Department of Computer Science and Engineering, University of Moratuwa
\begin{onecolentry}
\begin{highlights}
    \item Email: \href{mailto:dulani@cse.mrt.ac.lk}{dulani@cse.mrt.ac.lk}
    \item Phone: +94 71 393 5801
\end{highlights}
\end{onecolentry}
\end{twocolentry}

\vspace{0.3 cm}

\begin{twocolentry}{}
\textbf{Dr. Adeesha Wijayasiri} \\
Department of Computer Science and Engineering, University of Moratuwa
\begin{onecolentry}
\begin{highlights}
    \item Email: \href{mailto:adeeshaw@cse.mrt.ac.lk}{adeeshaw@cse.mrt.ac.lk}
    \item Phone: +94 71 629 1306
\end{highlights}
\end{onecolentry}
\end{twocolentry}


\end{document}
```
