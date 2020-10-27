### Events

Events | Event Details | Wiederholend | Wochentag
-------|---------------|--------------|-----------------------
Ev-A   |  9:30 -  9:45 | Täglich      | Mo, Di, Mi, Do, Fr, Sa
Ev-B   | 19:15 - 21:00 | Wöchentlich  | Mi
Ev-C   | 18:30 - 20:15 | Wöchentlich  | Sa


### Ausfall-/Ersatzplan für Events

Event  | Planmäßig  | Ersatztermin | Grund
-------|------------|--------------|-----------------------
Ev-B   | 21.10.2020 | 20.10.2020   | Außerplanmäßiger Grund
Ev-C   | 14.11.2020 | <entfällt>   | Außerplanmäßiger Grund


### Aufgaben für alle Events

Tasks | Beschreibung | Periode (Personenbindung)
------|--------------|--------------------------
Ta-A  | Host         | Jedes mal
Ta-B  | Co-Host      | Jedes mal
Ta-C  | Vorsitz      | Jedes mal
Ta-D  | Leser        | Jedes mal
Ta-E  | Host TP      | Jedes mal

Die Personenbindung einer Aufgabe können auch folgende sein:
 - täglich
 - wöchentlich
 - 2-wöchentlich
 - monatlich


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