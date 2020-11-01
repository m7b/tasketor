### Tabelle `tEvents`
Events

cId | cEvent | cEventDetails | cRepeat       | cWeekdays
----|--------|---------------|---------------|-----------------------
  0 | Ev-A   |  9:30 -  9:45 | Täglich       | Mo, Di, Mi, Do, Fr, Sa
  1 | Ev-B   | 19:15 - 21:00 | Wöchentlich   | Mi
  2 | Ev-C   | 18:30 - 20:15 | Wöchentlich   | Sa


### Tabelle `tEventReplacementPlan`
Ausfall-/Ersatzplan für Events

cId | cEventId  | cPlan      | cReplacement | cReason
----|-----------|------------|--------------|-----------------------
  0 |       1   | 21.10.2020 | 20.10.2020   | Außerplanmäßiger Grund
  1 |       2   | 14.11.2020 | <entfällt>   | Außerplanmäßiger Grund


### Tabelle tTasks
Aufgaben für alle Events

cId | cTask  | cDescription  | cPeriodId (Personenbindung)
----|--------|---------------|----------------------------
  0 | Ta-A   | Host          | Jedes mal
  1 | Ta-B   | Co-Host       | Jedes mal
  2 | Ta-C   | Vorsitz       | Jedes mal
  3 | Ta-D   | Leser         | Jedes mal
  4 | Ta-E   | Host TP       | Jedes mal


### Tabelle tCommitmentPeriod
Die Personenbindung einer Aufgabe

cId | cPeriod       | cDescription
----|---------------|-------------
  0 | Jedes mal     |
  1 | täglich       |  
  2 | wöchentlich   |
  3 | 2-wöchentlich |
  4 | monatlich     |


### Zuteilung der Aufgaben zu den Events

Event | Ta-A | Ta-B | Ta-C | Ta-D | Ta-E
------|------|------|------|------|-----
Ev-A  |      |      |      |      |   X
Ev-B  |   X  |   X  |      |      |
Ev-C  |   X  |   X  |   X  |   X  |


### Aufgabenmatrix, welche Aufgaben gleichzeizig zugewiesen werden können

Ta/Ta | Ta-A | Ta-B | Ta-C | Ta-D | Ta-E
------|------|------|------|------|-----
Ta-A  |   X  |      |      |      |
Ta-B  |      |   X  |   X  |   X  |
Ta-C  |      |   X  |   X  |      |
Ta-D  |      |   X  |      |   X  |
Ta-E  |      |      |      |      |   X


### Wer kann welche Aufgaben durchführen/übernehmen

Person    | Ta-A | Ta-B | Ta-C | Ta-D | Ta-D
----------|------|------|------|------|-----
Edgar     |   X  |   X  |   X  |   X  |
Eber      |      |   X  |      |   X  |
Braftaler |   X  |   X  |   X  |   X  |   X
Burbs     |   X  |   X  |   X  |   X  |
Grumml    |      |      |      |   X  |   X
Eufers    |      |      |   X  |   X  |
Siffel    |      |      |   X  |   X  |


### Abwesenheitsliste der Personen

Person    | Abwesenheit von | Abwesenheit bis
----------|-----------------|----------------
Edgar     | 26.10.2020      | 01.11.2020
Braftaler | 31.10.2020      |


### Grober Ablauf für die Erstellung der Aufgabenliste

Erstelle Planung <von Datum> <bis Datum>

 1. Füge planmäßige Events in Kalender
 2. Verändere planmäßige Events in Kalender unter Berücksichtigung eines Ersatztermins
 3. Erstelle Spaltenanordnung der Tasks.
    - Task mit größte Personenbindung ganz links.
	- Abnehmende Personenbindung nach rechts anordnen.
 3. Erstelle Liste mit anwesenden Personen je Event
 4. Zuweisung Personen zu den Aufgaben zu jedem Event