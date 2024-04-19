# 💶 Graphical Financial Calculator in C++
> [!NOTE]
> English version is down below.

# 🇩🇪 German Version
Dieses Projekt ist Teil meines Studiums und die Studienleistung für das Modul `Programmieren in C++`. Ich habe mich dazu entschieden einen grafischen Finanzrechner zu programmieren.
Dieser kann Pendlerpauschale, Zinsen, Rendite in Prozent und andere Prozentrechnungen berechnen. 
## 🚗 Pendlerpauschale
Arbeitnehmer in Deutschland können ihre Fahrtkosten von der Steuer absetzen und somit bereits gezahlte Lohnsteuern am Ende eines Steuerjahres zurückbekommen.<br/>
Dies geschieht über die sogenannte Pendlerpauschale, früher Kilometerpauschale genannt, welche eine Pauschale pro gefahrenen Kilometer festlegt.
Momentan liegt diese Pauschale bei **30ct** pro Kilometer bis **20** Kilometer Arbeitsweg. Ab dem **21.** Kilometer Arbeitsweg wird eine Pauschale von **38ct** berechnet.<br/>
Jedoch wird diese Pauschale nur für den kürzesten Anfahrtweg berechnet. Dabei ist egal, ob der Arbeitnehmer diesen Weg als täglichen Arbeitsweg verwendet.
### Wie wird die Pendlerpauschale vom Programm berechnet?
Bis zum einschließlich 20. Kilometer wird die folgende Formel zu Berechnung verwendet:
```
Pendlerpauschale = 0,30 * Anzahl an Arbeitstagen * Kilometer für kürzesten Anfahrtweg
```
Ab dem 21. Kilometer wird diese Formel verwendet:
```
Pendlerpauschale = 0,38 * Anzahl an Arbeitstagen * (Kilometer für kürzesten Anfahrtweg - 20)
```
Wenn der Anfahrtsweg nun über 20 Kilometer lang ist werden beide Formeln verwendet, um den letztendlichen Betrag der Pendlerpauschale zu berechnen.
Beide Ergebnisse werden miteinander addiert und der Gesamtbetrag der Pendlerpauschale entsteht.

## 💰 Renditerechner
Mit dem Renditerechner kann man die Rendite über einen bestimmten jährlichen Zeitraum berechnen. Dazu benötigt der Rechner Angaben zu Start- und Endkapital, sowie Start- und Endjahr. Dabei ist mit dem Startjahr und dem Startwert meist die Kauf-Order beziehunsweise Kauf-Transaktion gemeint. Dementsprechend ist der Endwert und das Endjahr die Verkaufsorder beziehungsweise Verkaufstransaktion.
Die Rendite für ein Jahr wird wie folgt ausgerechnet:
```
Rendite p.a. = pow(1.0 + Performance, 1.0 / Jahre) - 1.0
```
`pow` ist eine Funktion mit der man Potenzen in C++ berechnen kann. Dabei gibt das zweite Argument die Potenz an.
Die Gesamtrendite wird wie folgt berechnet:
```
Gesamtrendite = Endwert / Startwert - 1.0
```
## ％ Prozentrechner
Zudem gibt es noch einen Prozentrechner, der drei verschiedene Komponenten ausrechnen kann. Diese sind zum einen der Startwert, der Endwert, sowie der Prozentsatz. Die Anwendung wird, je nachdem welches Feld nicht ausgefüllt wurde, die verschiedenen Komponenten ausrechnen.

> **Disclaimer:** Bei den Berechnungen wird generell davon ausgegangen, dass Prozentsatz noch nicht durch 100 dividiert wurde.
 
Um den Startwert zu ermitteln benötigt der Rechner den Endwert sowie den Prozentsatz. Dabei ist zu beachten, dass der Endwert nicht gleich 0 sein darf! Die Berechnung sieht wie folgt aus:
```
Startwert = Endwert / ((Prozentsatz + 100) / 100)
```
Weiter geht es mit dem Endwert. Dieser wird mithilfe von Startwert und Prozentsatz berechnet. Auch hierbei soll der Startwert nicht gleich 0 sein! Die Berechnung ist hier zu finden:
```
Endwert = Startwert + (Startwert * (Prozentsatz / 100))
```
Letztendlich wird der Prozentsatz wie folgt errechnet:
```
Prozentsatz = (Endwert - Startwert) / Startwert
```
# 🇬🇧 English Version
This project is part of my studies and an example replacement for the `Programming in C++` module. Within this module, I decided to create a simple financial calculator that can calculate three different topics.
## 🚗 Commuter Benefit (German: Pendlerpauschale) 
Employees in Germany can deduct travel costs from their taxes and thus get back the income tax they have already paid at the end of a tax year.<br/>
This is done via the so-called commuter allowance, formerly known as the kilometer allowance, which sets a flat rate per kilometer driven.
Currently, this flat rate is **30ct** per kilometer up to **20** kilometers to work. From **21** kilometers to work, a flat rate of **38ct** is charged.<br/>
However, this flat rate is only charged for the shortest route. It does not matter whether the employee uses this route as a daily commute.
### How does the application calculate the Commuter Benefit?
Until the 21st kilometer the following formula is applied:
```
Commuter Benefit = 0,30 * Amount of Kilometers * Amount of days worked
```
After the 21st kilometer the formula is as follows:
```
Commuter Benefit = 0,38 * Amount of Kilometers * Amount of days worked
```
If the commute is now over 20 kilometers, both formulas are used to calculate the final amount of the commuter allowance.
Both results are added together and the total amount of the commuter allowance is calculated.
## 💰 Yield calculator
The yield calculator can calculate the yield over a specific annual period. To do this, the calculator requires information on the start and end capital, as well as the start and end year. The start year and the start value usually refer to the buy order or buy transaction. Accordingly, the end value and the end year refer to the sell order or sell transaction.
The return for a year is calculated as follows:
```
Yield p.a. = pow(1.0 + Performance, 1.0 / Years) - 1.0
```
`pow` is a function for calculating powers in C++. The second argument specifies the power.
The total return is calculated as follows:
```
Total Return = End value / Start value - 1.0
```
## ％ Percentage calculator
There is also a percentage calculator that can calculate three different components: the start value, the end value, and the percentage. The application will calculate the different components depending on which field has not been filled.

> **Disclaimer:** The calculations are generally based on the assumption that the percentage has not yet been divided by 100.
 
To determine the starting value, the calculator requires the final value and the percentage. Please note that the final value must not be 0! The calculation is as follows:
```
Start value = End value / ((Percentage + 100) / 100)
```
The next step is the final value. This is calculated using the start value and percentage. Here too, the start value should not be 0! The calculation can be found here:
```
End value = Start value + (Start value * (Percentage / 100))
```
Ultimately, the percentage is calculated as follows:
```
Percentage = (End value - Start value) / Start value
```

# 🎨 Style Guide
I used my own code styling, similar to the code styling used in TypeScript. 
If you're not familiar with the TypeScript code style, don't worry. The following table displays all code styling used in this project.
|Category|Style|Example|
|--|--|--|
|Constants|Upper Snake Case|`THIS_IS_A_CONSTANT`|
|Variables|Camel Case|`startValue`|
|Methods|Camel Case|`performTask()`|
|Classes|Pascal Case|`CommuterBenefit`|

## How this works

This template searches for the wxWidgets library using `FindPackage`. If not found, it downloads the library source from GitHub, compiles it, and links it with the main project. 

The super build pattern with `ExternalProject_Add` is used to achieve this.

## Requirements

This works on Windows, Mac, and Linux. You'll need `cmake` and a C++ compiler (tested on `clang`, `gcc`, and MSVC).

Linux builds require the GTK3 library and headers installed in the system.

## Building

To build the project, use:

```bash
cmake -S. -Bbuild
cmake --build build
```

This will create a directory named `build` and create all build artifacts there. The main executable can be found in the `build/subprojects/Build/wx_cmake_template_core` folder.

## Notes

For details, see the [blog post](https://www.lukesdevtutorials.com/post/wxwidgets-cmake/) and the [video](https://www.youtube.com/watch?v=MfuBS9n5_aY) tutorial showcasing the installation on Linux, Windows, and Mac OS X. 

---
Check out the blog for more! [www.lukesdevtutorials.com](https://www.lukesdevtutorials.com)
---


